/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

namespace greaper
{
	class IPoolAllocator
	{
	public:
		virtual ~IPoolAllocator() = default;
		virtual void* Alloc() = 0;
		virtual void Dealloc(void* elem) = 0;
		virtual sizet GetElementSize()const = 0;
		virtual sizet GetElementsPerBlock()const = 0;
		virtual sizet GetAlignment()const = 0;
		virtual bool IsLocked()const = 0;
	};

	namespace Impl
	{
		template<sizet ElemSize, sizet Alignment>
		struct PoolAlignedValueSize_t
		{
			static constexpr sizet Value = ((ElemSize + Alignment - 1) / Alignment) * Alignment;
		};
		template<sizet ElemSize, sizet Alignment>
		constexpr inline sizet PoolAlignedValueSize = PoolAlignedValueSize_t<ElemSize, Alignment>::Value;

		template<sizet ElemSize, sizet ElemPerBlock, sizet Alignment>
		struct PoolMemBlock
		{
			uint8* Data;
			sizet LastPtr;
			sizet FreeElems;
			PoolMemBlock* NextBlock;

			INLINE PoolMemBlock(uint8* blockData)noexcept
				:Data(blockData)
				,LastPtr(0)
				,FreeElems(ElemPerBlock)
				,NextBlock(nullptr)
			{
				sizet offset = 0;
				for(sizet i = 0; i < ElemPerBlock; ++i)
				{
					auto entryPtr = (sizet*)&blockData[offset];

					offset += Impl::PoolAlignedValueSize<ElemSize, Alignment>;
					*entryPtr = offset;
				}
			}
			INLINE ~PoolMemBlock()noexcept
			{
				VerifyEqual(FreeElems, ElemPerBlock, "Trying to destroy a PoolMemBlock, but not all elements were deallocated.");
			}
			INLINE void* Alloc()noexcept
			{
				auto* freeEntry = &Data[LastPtr];
				LastPtr = *(sizet*)freeEntry;
				--FreeElems;

				return (void*)freeEntry;
			}
			INLINE void Dealloc(void* elem)noexcept
			{
				auto* entryPtr = (sizet*)elem;
				*entryPtr = LastPtr;
				++FreeElems;

				LastPtr = (sizet)(((uint8*)elem) - Data);
			}
		};
	}

	template<sizet ElemSize, sizet ElemPerBlock = 512, sizet Alignment = sizeof(ptruint), class _Allocator_ = GenericAllocator, bool Locked = true>
	class PoolAllocator : public IPoolAllocator
	{
	private:
		constexpr sizet BlockDataSize = Impl::PoolAlignedValueSize<ElemSize, Alignment> * ElemPerBlock;

	public:
		INLINE PoolAllocator()noexcept
			:m_FreeBlock(nullptr)
			,m_UsedBlocks(0)
			,m_TotalUsedElems(0)
		{
			static_assert(ElemSize >= sizeof(ptruint), "You must provide elements with more size.");
			static_assert(ElemPerBlock > 0, "Number of elements per block must be at least 1.");
			static_assert(ElemPerBlock * AlignedSize <= SIZE_MAX, "Pool containing too large objects or too many blocks.");
		}

		PoolAllocator(const PoolAllocator&) = delete;
		PoolAllocator& operator=(const PoolAllocator&) = delete;

		INLINE PoolAllocator(PoolAllocator&& other)noexcept
			:m_Mutex(other.m_Mutex)
			,m_FreeBlock(other.m_FreeBlock)
			,m_UsedBlocks(other.m_UsedBlocks)
			,m_TotalUsedElems(other.m_TotalUsedElems)
		{
			other.m_FreeBlock = nullptr;
			other.m_UsedBlocks = 0;
			other.m_TotalUsedElems = 0;
		}

		INLINE PoolAllocator& operator=(PoolAllocator&& other)noexcept
		{
			if(this != &other)
			{
				m_Mutex.lock();
				other.m_Mutex.lock();
				DestroySelf();
				
				m_FreeBlock = other.m_FreeBlock;
				m_UsedBlocks = other.m_UsedBlocks;
				m_TotalUsedElems = other.m_TotalUsedElems;

				other.m_FreeBlock = nullptr;
				other.m_UsedBlocks = 0;
				other.m_TotalUsedElems = 0;

				m_Mutex.unlock();
				other.m_Mutex.unlock();

				m_Mutex = other.m_Mutex;
			}
			return *this;
		}

		INLINE ~PoolAllocator()noexcept
		{
			LOCK(m_Mutex);
			DestroySelf();
		}

		INLINE void* Alloc()override
		{
			LOCK(m_Mutex);
			if(!m_FreeBlock || m_FreeBlock->FreeElems == 0)
				AllocBlock();

			++m_TotalUsedElems;
			return m_FreeBlock->Alloc();
		}

		template<class T, typename... Args>
		INLINE T* Construct(Args&&... args)noexcept
		{
			T* elem = (T*)Alloc();
			VerifyNotNull(elem, "Coudn't construct a nullptr elem!");

			new(elem)T(std::forward<Args>(args)...);

			return elem;
		}

		INLINE void Dealloc(void* elem)override
		{
			LOCK(m_Mutex);
			MemBlock_t* curBlock = m_FreeBlock;
			while(curBlock)
			{
				// Is elem inside the current block?
				if(elem >= curBlock->Data && elem < (curBlock->Data + BlockDataSize))
				{
					curBlock->Dealloc(elem);
					--m_TotalUsedElems;

					if(curBlock->FreeElems == 0 && curBlock->NextBlock)
					{
						const auto totalSpace = (m_UsedBlocks - 1) * ElemPerBlock;
						const auto freeSpace = totalSpace - m_TotalUsedElems;

						if(freeSpace > (ElemPerBlock / 2))
						{
							m_FreeBlock = curBlock->NextBlock;
							DeallocBlock(curBlock);
						}
					}
					return;
				}
				curBlock = curBlock->NextBlock;
			}
			Break("Trying to dealloc an elem from a PoolAllocator, but it was not found in any MemBlock!");
		}

		template<class T>
		INLINE void Destruct(T* elem)
		{
			elem->~T();
			this->Dealloc((void*)elem);
		}

		INLINE sizet GetElementSize()const override { return ElemSize; }

		INLINE sizet GetElementsPerBlock()const override { return ElemPerBlock; }

		INLINE sizet GetAlignment()const override { return Alignment; }

		INLINE bool IsLocked()const override { return Locked; }

	private:
		using MemBlock_t = Impl::PoolMemBlock<ElemSize, ElemPerBlock, Alignment>;

		TMutex<Locked> m_Mutex;
		MemBlock_t* m_FreeBlock;
		sizet m_UsedBlocks;
		sizet m_TotalUsedElems;

		INLINE void DestroySelf()noexcept
		{
			MemBlock_t* curBlock = m_FreeBlock;
			while(curBlock)
			{
				auto tmpBlock = curBlock->NextBlock;
				DeallocBlock(curBlock);
				curBlock = tmpBlock;
			}
		}

		INLINE MemBlock_t* AllocBlock()noexcept
		{
			MemBlock_t* nBlock = nullptr;
			MemBlock_t* curBlock = m_FreeBlock;
			
			/* Let's find if exists a block which has available space */
			while(curBlock)
			{
				auto nextBlock = curBlock->NextBlock;
				if (nextBlock && nextBlock->FreeElems > 0)
				{
					nBlock = nextBlock;
					curBlock->NextBlock = nBlock->NextBlock;
					break;
				}
				curBlock = nextBlock;
			}

			/* We haven't found any block with available space lets create one */
			if (!nBlock)
			{
				constexpr auto blockDataSize = Impl::PoolAlignedValueSize<ElemSize, Alignment> * ElemPerBlock;
				auto paddedBlockSize = blockDataSize + (Alignment - 1);
				
				//uint8* block = (uint8*)ALLOC(sizeof(MemBlock) + paddedBlockSize);
				uint8* block = (uint8*)_Alloc(sizeof(MemBlock) + paddedBlockSize);
				void* blockData = (void*)(block + sizeof(MemBlock));
				blockData = std::align(Alignment, blockDataSize, blockData, paddedBlockSize);
				nBlock = new((void*)block)MemBlock((uint8*)blockData);

				nBlock->NextBlock = m_FreeBlock;
			}
			m_FreeBlock = nBlock;
			++m_UsedBlocks;
			return nBlock;
		}

		INLINE void DeallocBlock(MemBlock_t* block)
		{
			block->~PoolMemBlock();
			greaper::Dealloc<_Allocator_>(block);
			--m_UsedBlocks;
		}
	};
}
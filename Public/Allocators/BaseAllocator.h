/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

namespace greaper
{
	template<class T>
	class MemoryAllocator
	{
	public:
		NODISCARD static void* Allocate(sizet byteSize);

		NODISCARD static void* AllocateAligned(sizet byteSize, sizet alignment);

		static void Deallocate(void* mem);

		static void DeallocateAligned(void* mem);
	};

	class GenericAllocator { };

	template<class _Alloc_ = GenericAllocator>
	NODISCARD INLINE void* Alloc(sizet byteSize)
	{
		return MemoryAllocator<_Alloc_>::Allocate(byteSize);
		//return malloc(byteSize);
	}

	template<class _Alloc_ = GenericAllocator>
	NODISCARD INLINE void* AllocAligned(sizet byteSize, sizet alignment)
	{
		return MemoryAllocator<_Alloc_>::AllocateAligned(byteSize, alignment);
	}

	template<class T, class _Alloc_ = GenericAllocator>
	NODISCARD INLINE T* AllocN(sizet N)
	{
		return static_cast<T*>(Alloc<_Alloc_>(sizeof(T) * N));
	}

	template<class T, class _Alloc_ = GenericAllocator>
	NODISCARD INLINE T* AllocAlignedN(sizet N, sizet alignment)
	{
		return static_cast<T*>(AllocAligned<_Alloc_>(sizeof(T) * N, alignment));
	}

	template<class T, class _Alloc_ = GenericAllocator>
	NODISCARD INLINE T* AllocT()
	{
		return AllocN<T, _Alloc_>(1);
	}

	template<class T, class _Alloc_ = GenericAllocator>
	NODISCARD INLINE T* AllocAlignedT(sizet alignment)
	{
		return AllocN<T, _Alloc_>(1, alignment);
	}

	template<class T, class _Alloc_ = GenericAllocator, class... Args>
	NODISCARD INLINE T* ConstructN(sizet count, Args&&... args)
	{
		T* mem = AllocN<T, _Alloc_>(count);
		for (sizet i = 0; i < count; ++i)
			new (reinterpret_cast<void*>(&mem[i]))T(std::forward<Args>(args)...);
		return mem;
	}

	template<class T, class _Alloc_ = GenericAllocator, class... Args>
	NODISCARD INLINE T* ConstructAlignedN(sizet count, sizet alignment, Args&&... args)
	{
		T* mem = AllocAlignedN<T, _Alloc_>(count, alignment);
		for (sizet i = 0; i < count; ++i)
			new (reinterpret_cast<void*>(&mem[i]))T(std::forward<Args>(args)...);
		return mem;
	}

	template<class T, class _Alloc_ = GenericAllocator, class... Args>
	NODISCARD INLINE T* Construct(Args&&... args)
	{
		return ConstructN<T, _Alloc_>(1, args...);
	}

	template<class T, class _Alloc_ = GenericAllocator, class... Args>
	NODISCARD INLINE T* ConstructAligned(sizet alignment, Args&&... args)
	{
		return ConstructAlignedN<T, _Alloc_>(1, alignment, args...);
	}
	
	template<class _Alloc_ = GenericAllocator>
	INLINE void Dealloc(void* mem)
	{
		MemoryAllocator<_Alloc_>::Deallocate(mem);
		//free(mem);
	}

	template<class _Alloc_ = GenericAllocator>
	INLINE void DeallocAligned(void* mem)
	{
		MemoryAllocator<_Alloc_>::DeallocateAligned(mem);
	}

	template<class T, class _Alloc_ = GenericAllocator>
	INLINE void Destroy(T* ptr, sizet count = 1)
	{
		for (sizet i = 0; i < count; ++i)
			ptr[i].~T();
		Dealloc<_Alloc_>(ptr);
	}

	template<class T, class _Alloc_ = GenericAllocator>
	INLINE void DestroyAligned(T* ptr, sizet count = 1)
	{
		for (sizet i = 0; i < count; ++i)
			ptr[i].~T();
		DeallocAligned<_Alloc_>(ptr);
	}

/**
 * @brief Makes a class friend of the base construction/destruction functions
 * 
 */
#define MemoryFriend() \
template<class _T_, class _Alloc_, class... Args> friend _T_* greaper::ConstructN(sizet, Args&&...); \
template<class _T_, class _Alloc_> friend void greaper::Destroy(_T_*, sizet)
}
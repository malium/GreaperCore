/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

namespace greaper
{
	template<class T>
	void* MemoryAllocator<T>::Allocate(sizet byteSize)
	{
	#if GREAPER_DEBUG_ALLOCATION
		if (byteSize == 0)
			return nullptr;

		void* mem = PlatformAlloc(byteSize);

		VerifyNotNull(mem, "Nullptr detected after asking to OS for %" PRIuPTR " bytes.", byteSize);
		return mem;
	#else
		return PlatformAlloc(byteSize);
	#endif
	}

	template<class T> 
	void* MemoryAllocator<T>::AllocateAligned(sizet byteSize, sizet alignment)
	{
	#if GREAPER_DEBUG_ALLOCATION
		if (byteSize == 0)
			return nullptr;
		if (alignment == 0)
			return Allocate(byteSize);

		void* mem = PlatformAlignedAlloc(byteSize, alignment);
		VerifyNotNull(mem, "Nullptr detected after asking to OS for %" PRIuPTR " bytes aligned %" PRIuPTR ".", byteSize, alignment);

		return mem;
	#else
		return PlatformAlignedAlloc(byteSize, alignment);
	#endif
	}

	template<class T>
	void MemoryAllocator<T>::Deallocate(void* mem)
	{
	#if GREAPER_DEBUG_ALLOCATION
	#if GREAPER_ENABLE_BREAK
		VerifyNotNull(mem, "Detected nullptr, maybe use after free.");
	#else
		if (mem == nullptr)
		{
			return;
		}
	#endif
	#endif
		PlatformDealloc(mem);
	}

	template<class T>
	void MemoryAllocator<T>::DeallocateAligned(void* mem)
	{
	#if GREAPER_DEBUG_ALLOCATION
	#if GREAPER_ENABLE_BREAK
		VerifyNotNull(mem, "Detected nullptr, maybe use after free.");
	#else
		if (mem == nullptr)
		{
			return;
		}
	#endif
	#endif
		PlatformAlignedDealloc(mem);
	}
}
/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

/* Function type macros */
#if COMPILER_MSVC
#define INLINE __forceinline									/** Forces code to be inlined */
#define NOINLINE __declspec(noinline)							/** Forces code to NOT be inlined */
#define FUNCTION_NO_RETURN_START __declspec(noreturn)			/** Indicate that the function never returns. */
#define FUNCTION_NO_RETURN_END
#define FUNCTION_FULL __FUNCSIG__
#else
#define INLINE __attribute__((always_inline))
#define NOINLINE __attribute__((noinline))
#define FUNCTION_NO_RETURN_START
#define FUNCTION_NO_RETURN_END __attribute__(noreturn)
#define FUNCTION_FULL __PRETTY_FUNCTION__
#endif

#define GREAPER_DLLEXT ".dll"

/* String constants */
#ifndef PATH_SEPARATOR
#define PATH_SEPARATOR '\\'
#endif
#ifndef PATH_SEPARATOR_WIDE
#define PATH_SEPARATOR_WIDE L'\\'
#endif

#ifndef DLLIMPORT
#define DLLIMPORT __declspec(dllimport)
#endif
#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#endif

#define PlatformAlloc(bytes) HeapAlloc(GetProcessHeap(), 0, bytes)
#define PlatformDealloc(mem) HeapFree(GetProcessHeap(), 0, mem)
#define PlatformAlignedAlloc(bytes, alignment) _aligned_malloc(bytes, alignment)
#define PlatformAlignedDealloc(mem) _aligned_free(mem)
#define DEBUG_OUTPUT(x) OutputDebugStringA(x)
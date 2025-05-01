/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

/***********************************************************************************************************************
 *                                                     VERSION                                                         *
 **********************************************************************************************************************/
/// Creates a 32 bit number from major, minor, patch and revision versions, each value has 8bit space.
#define VERSION_SETTER(major, minor, patch, rev) (((major & 0xFF) << 24) | ((minor & 0xFF) << 16) |                    \
												 ((patch & 0xFF) << 8) | (rev & 0xFF))
#define VERSION_GET_MAJOR(version) (((version & 0xFF000000) >> 24) & 0xFF)
#define VERSION_GET_MINOR(version) (((version & 0x00FF0000) >> 16) & 0xFF)
#define VERSION_GET_PATCH(version) (((version & 0x0000FF00) >> 8) & 0xFF)
#define VERSION_GET_REV(version) ((version & 0x000000FF) & 0xFF)

#ifdef GREAPER_CORE_VERSION
#undef GREAPER_CORE_VERSION
#endif
#define GREAPER_CORE_VERSION VERSION_SETTER(2, 0, 0, 0)

/***********************************************************************************************************************
 *                                              ENVIRONTMENT DETECTION                                                 *
 **********************************************************************************************************************/

#ifndef  __cplusplus
#error Greaper needs C++.
#endif

// We use at least C++23.
#if __cplusplus < 202302L
#if defined(_MSC_VER)
#if _MSC_VER < 1900
#error "Unsopported C++ version! Requires C++23!"
#endif
#else
#error "Unsopported C++ version! Requires C++23!"
#endif
#endif

#if (!defined(_68K_) && !defined(_MPPC_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && !defined(_ARM_)\
	&& defined(_M_AMD64)) || defined(__x86_64__)
#define ARCHITECTURE_X64 1
#else
#define ARCHITECTURE_X64 0
#endif

#if !ARCHITECTURE_X64
#error "Unsopported Architecture! Requires x64 architecture!"
#endif

#ifndef COMPILER_GCC
#if defined(__GNUC__) && !defined(COMPILER_VERSION)
#define COMPILER_GCC 1
#define COMPILER_VERSION __GNUC__
#ifndef __GXX_RTTI
#error "RTTI must be supported and enabled!"
#endif
#else
#define COMPILER_GCC 0
#endif
#endif

#ifndef COMPILER_MSVC
#if defined(_MSC_VER) && !defined(COMPILER_VERSION)
#define COMPILER_MSVC 1
#define COMPILER_VERSION _MSC_VER
#ifndef _CPPRTTI
#error "RTTI must be supported and enabled!"
#endif
#else
#define COMPILER_MSVC 0
#endif
#endif

#ifndef COMPILER_VERSION
#error "Unknown compiler! Your complier is unsupported, currently only gcc and MSVC are supported!"
#endif

#ifndef PLATFORM_WINDOWS
#if (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__))
#define PLT_WINDOWS 1
#define PLT_NAME "Win"
#else
#define PLT_WINDOWS 0
#endif
#endif

#ifndef PLT_LINUX
#if (defined(linux) || defined(__linux__) || defined(__linux))
#define PLT_LINUX 1
#define PLT_NAME "Lnx"
#else
#define PLT_LINUX 0
#endif
#endif

#if !PLT_WINDOWS && !PLT_LINUX
#error "Unsupported Platform! Only Windows and Linux-based platform are supported!"
#endif

// Cross-platform debug handler
#ifndef GREAPER_DEBUG
#if defined(_DEBUG) || defined(DEBUG)
#define GREAPER_DEBUG 1
#else
#define GREAPER_DEBUG 0
#endif
#endif

/* Greaper Library suffix name */
#define GREAPER_LIBRARY_SUFFIX_DBG "_Debug"
#define GREAPER_LIBRARY_SUFFIX_RLS "_Release"
#define GREAPER_LIBRARY_SUFFIX_RDI "_RelWithDebInfo"
#define GREAPER_LIBRARY_SUFFIX_RMS "_MinSizeRel"

// using cmake
#if defined(Debug)
#define GREAPER_LIBSUFFIX GREAPER_LIBRARY_SUFFIX_DBG
#elif defined(Release)
#define GREAPER_LIBSUFFIX GREAPER_LIBRARY_SUFFIX_RLS
#elif defined(RelWithDebInfo)
#define GREAPER_LIBSUFFIX GREAPER_LIBRARY_SUFFIX_RDI
#elif defined(MinSizeRel)
#define GREAPER_LIBSUFFIX GREAPER_LIBRARY_SUFFIX_RMS
#else // not using cmake
#if GREAPER_DEBUG
#define GREAPER_LIBSUFFIX GREAPER_LIBRARY_SUFFIX_DBG
#else
#define GREAPER_LIBSUFFIX GREAPER_LIBRARY_SUFFIX_RLS
#endif
#endif

/* Standard C function calling convention */
#ifndef CDECL
#if COMPILER_CLANG || COMPILER_GCC
#define CDECL __attribute__((cdecl))
#elif COMPILER_ICC || COMPILER_MSVC
#define CDECL __cdecl
#else
#define CDECL
#endif
#endif

/* Standard calling convention */
#ifndef STDCALL
#if COMPILER_CLANG || COMPILER_GCC
#define STDCALL __attribute__((stdcall))
#elif COMPILER_ICC || COMPILER_MSVC
#define STDCALL __stdcall
#else
#define STDCALL
#endif
#endif

/* Thread local variable declaration */
#ifndef GREAPER_THLOCAL
#if COMPILER_MSVC || (COMPILER_ICC && PLT_WINDOWS)
#define GREAPER_THLOCAL __declspec(thread)
#else
#define GREAPER_THLOCAL __thread
#endif
#endif

struct __GREAPER_BASIC_TYPES
{
	typedef unsigned char		uint8_t;
	typedef unsigned short		uint16_t;
	typedef unsigned int		uint32_t;
	typedef unsigned long long	uint64_t;
	typedef signed char			int8_t;
	typedef signed short		int16_t;
	typedef signed int			int32_t;
	typedef signed long long	int64_t;

	typedef char				ansichar;
	typedef wchar_t				widechar;
	typedef uint8_t				utf8char;
	typedef uint16_t			utf16char;
	typedef uint32_t			utf32char;
	typedef uint64_t			ptruint_t;
	typedef int64_t				ptrint_t;
	typedef ptruint_t			sizetype;
	typedef ptrint_t			ssizetype;
};

#if PLT_WINDOWS
#include <cstdio>
struct __GREAPER_WIN_TYPES : __GREAPER_BASIC_TYPES
{
	typedef unsigned __int64	uint64_t;
	typedef signed __int64		int64_t;
	typedef uint64_t			ptruint_t;
	typedef int64_t				ptrint_t;
	typedef uint64_t			sizetype;
	typedef int64_t				ssizetype;
};
typedef __GREAPER_WIN_TYPES __GREAPER_PLATFORM_TYPES;
#elif PLT_LINUX
#include <cstdlib>
struct __GREAPER_LNX_TYPES : __GREAPER_BASIC_TYPES
{
	typedef __SIZE_TYPE__ sizetype;
	typedef __SSIZE_T_TYPE ssizetype;
	typedef wchar_t widechar;
};
typedef __GREAPER_LNX_TYPES __GREAPER_PLATFORM_TYPES;
#endif

using uint8 = __GREAPER_PLATFORM_TYPES::uint8_t;
using uint16 = __GREAPER_PLATFORM_TYPES::uint16_t;
using uint32 = __GREAPER_PLATFORM_TYPES::uint32_t;
using uint64 = __GREAPER_PLATFORM_TYPES::uint64_t;
using int8 = __GREAPER_PLATFORM_TYPES::int8_t;
using int16 = __GREAPER_PLATFORM_TYPES::int16_t;
using int32 = __GREAPER_PLATFORM_TYPES::int32_t;
using int64 = __GREAPER_PLATFORM_TYPES::int64_t;
using achar = __GREAPER_PLATFORM_TYPES::ansichar;
using wchar = __GREAPER_PLATFORM_TYPES::widechar;
using u8char = __GREAPER_PLATFORM_TYPES::utf8char;
using u16char = __GREAPER_PLATFORM_TYPES::utf16char;
using u32char = __GREAPER_PLATFORM_TYPES::utf32char;
using ptruint = __GREAPER_PLATFORM_TYPES::ptruint_t;
using ptrint = __GREAPER_PLATFORM_TYPES::ptrint_t;
using sizet = __GREAPER_PLATFORM_TYPES::sizetype;
using ssizet = __GREAPER_PLATFORM_TYPES::ssizetype;

static_assert(sizeof(uint8) == 1 && sizeof(int8) == 1, "u/int8 should be 1 byte size");
static_assert(sizeof(uint16) == 2 && sizeof(int16) == 2, "u/int16 should be 2 byte size");
static_assert(sizeof(uint32) == 4 && sizeof(int32) == 4, "u/int32 should be 4 byte size");
static_assert(sizeof(uint64) == 8 && sizeof(int64) == 8, "u/int64 should be 8 byte size");
static_assert(sizeof(ptruint) == 8 && sizeof(ptrint) == 8, "pointers should be 8 byte size");
static_assert(sizeof(sizet) == 8 && sizeof(ssizet) == 8, "size types should be 8 byte size");

#if PLT_WINDOWS
#include "../Win/Prerequisites.hpp"
#elif PLT_LINUX
#include "../Lnx/Prerequisites.hpp"
#endif

#ifndef PlatformAlloc
#define PlatformAlloc(bytes) ::malloc(bytes)
#define PlatformDealloc(mem) ::free(mem)
#endif
#ifndef PlatformAlignedAlloc
#define PlatformAlignedAlloc(bytes, alignment) ::aligned_alloc(alignment, bytes)
#define PlatformAlignedDealloc(mem) ::free(mem)
#endif

/* Full function display */
#ifndef FUNCTION_FULL
#define FUNCTION_FULL
#endif
/* Dynamic Link Library extension */
#ifndef GREAPER_DLLEXT
#define GREAPER_DLLEXT ".so"
#endif
/* Dynamic Link library macro */
#ifndef DLLIMPORT
#define DLLIMPORT
#endif
#ifndef DLLEXPORT
#define DLLEXPORT
#endif
/* Force code to be inlined */
#ifndef INLINE
#define INLINE
#endif
/* Force code to NOT be inlined */
#ifndef NOINLINE
#define NOINLINE
#endif
/* String constants */
#ifndef PATH_SEPARATOR
#define PATH_SEPARATOR '/'
#endif
#ifndef PATH_SEPARATOR_WIDE
#define PATH_SEPARATOR_WIDE L'/'
#endif
/* Unreferenced Parameter warnings removal */
#ifndef UNUSED
#define UNUSED [[maybe_unused]]
#endif
/* Ensure return value utilization */
#ifndef NODISCARD
#define NODISCARD [[nodiscard]]
#endif
#ifndef MATH_TOLERANCE
#define MATH_TOLERANCE 0.0001
#endif

#include "Utils.hpp"

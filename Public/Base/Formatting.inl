/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#include <cstdarg>
#include <inttypes.h>

namespace greaper
{
	struct Snprintf
	{
		static int Fn(achar* buffer, size_t bufferLen, const achar* fmt, va_list argList)
		{
			return vsnprintf(buffer, bufferLen, fmt, argList);
		}
		static int Fn(wchar* buffer, size_t bufferLen, const wchar* fmt, va_list argList)
		{
			return vswprintf(buffer, bufferLen, fmt, argList);
		}
	};

	template<typename T, class _Alloc_ = GenericAllocator>
	NODISCARD BasicString<T, StdAlloc<T, _Alloc_>> Format(const T* fmt, ...) FUNCTION_VARARGS_END(1,2)
	{
		va_list argList;
		va_start(argList, fmt);

		const auto size = (ssizet)Snprintf::Fn((T*)nullptr, 0, fmt, argList);

		VerifyGreaterEqual(size, 0, "Error while formatting");

		va_end(argList);
		va_start(argList, fmt);

		BasicString<T, StdAlloc<T, _Alloc_>> str {};
		str.resize(size + 1, (T)0);

		Snprintf::Fn(str.data(), str.size(), fmt, argList);

		va_end(argList);

		return str;
	}

	template<typename T, class _Alloc_ = GenericAllocator>
	NODISCARD BasicString<T, StdAlloc<T, _Alloc_>> Format(const BasicString<T, _Alloc_>& fmt, ...)
	{
		va_list argList;
		va_start(argList, fmt.c_str());

		const auto size = (ssizet)Snprintf::Fn((T*)nullptr, 0, fmt.c_str(), argList);

		VerifyGreaterEqual(size, 0, "Error while formatting");

		va_end(argList);
		va_start(argList, fmt);

		BasicString<T, StdAlloc<T, _Alloc_>> str{};
		str.resize(size + 1, (T)0);

		Snprintf::Fn(str.data(), str.size(), fmt.c_str(), argList);

		va_end(argList);

		return str;
	}

#define I8_HEX_FMT "0x%02" PRIX8
#define I16_HEX_FMT "0x%04" PRIX16
#define I32_HEX_FMT "0x%08" PRIX32
#define I64_HEX_FMT "0x%016" PRIX64

#if ARCHITECTURE_X64
#define PTR_HEX_FMT I64_HEX_FMT
#else
#define PTR_HEX_FMT I32_HEX_FMT
#endif

}
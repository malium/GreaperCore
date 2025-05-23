/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// WINNT
typedef void* HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
typedef int32 HRESULT;

// WINERROR
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)
#define FAILED(hr) (((HRESULT)(hr)) < 0)

// ERR HANDLING API
DLLIMPORT int32 STDCALL GetLastError();

// MIN WIN DEF
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;
typedef HANDLE HLOCAL;

// WIN BASE
#define LMEM_FIXED          0x0000
#define LMEM_MOVEABLE       0x0002
#define LMEM_NOCOMPACT      0x0010
#define LMEM_NODISCARD      0x0020
#define LMEM_ZEROINIT       0x0040
#define LMEM_MODIFY         0x0080
#define LMEM_DISCARDABLE    0x0F00
#define LMEM_VALID_FLAGS    0x0F72
#define LMEM_INVALID_HANDLE 0x8000

#define LHND                (LMEM_MOVEABLE | LMEM_ZEROINIT)
#define LPTR                (LMEM_FIXED | LMEM_ZEROINIT)

#define NONZEROLHND         (LMEM_MOVEABLE)
#define NONZEROLPTR         (LMEM_FIXED)

#define LMEM_DISCARDED      0x4000
#define LMEM_LOCKCOUNT      0x00FF

DLLIMPORT __declspec(allocator) HLOCAL STDCALL LocalAlloc(uint32 uFlags, sizet uBytes);
DLLIMPORT HLOCAL STDCALL LocalFree(HLOCAL hMem);

// HEAP API
DLLIMPORT __declspec(allocator) void* STDCALL HeapAlloc(HANDLE hHeap, uint32 dwFlags, sizet dwBytes);

DLLIMPORT int32 STDCALL HeapFree(HANDLE hHeap, uint32 dwFlags, void* lpMem);

DLLIMPORT HANDLE STDCALL GetProcessHeap();

// SHELL API
DLLIMPORT wchar** STDCALL CommandLineToArgvW(const wchar* lpCmdLine, int32* pNumArgs);

// DEBUG API
DLLIMPORT void STDCALL DebugBreak();

DLLIMPORT void STDCALL OutputDebugStringA(const achar* lpOutputString);

DLLIMPORT void STDCALL OutputDebugStringW(const wchar* lpOutputString);

DLLIMPORT int32 STDCALL IsDebuggerPresent();

//LIB LOADER API
DLLIMPORT HMODULE STDCALL GetModuleHandleA(const achar* lpModuleName);

DLLIMPORT HMODULE STDCALL GetModuleHandleW(const wchar* lpModuleName);

// GUID DEF
typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;

// RPCDCE
#define UUID_DEFINED
typedef GUID UUID;

DLLIMPORT int32 STDCALL UuidCreate(UUID* Uuid);

// WIN NIS
#define CP_ACP                    0           // default to ANSI code page
#define CP_OEMCP                  1           // default to OEM  code page
#define CP_MACCP                  2           // default to MAC  code page
#define CP_THREAD_ACP             3           // current thread's ANSI code page
#define CP_SYMBOL                 42          // SYMBOL translations

#define CP_UTF7                   65000       // UTF-7 translation
#define CP_UTF8                   65001       // UTF-8 translation

#define MB_ERR_INVALID_CHARS      0x00000008  // error for invalid chars

// STRING API SET
DLLIMPORT int32 STDCALL MultiByteToWideChar(uint32 CodePage, uint32 dwFlags, const achar* lpMultiByteStr,
											int32 cbMultiByte, wchar* lpWideCharStr, int32 cchWideChar);

DLLIMPORT int32 STDCALL WideCharToMultiByte(uint32 CodePage, uint32 dwFlags, const wchar* lpWideCharStr,
											int32 cchWideChar, achar* lpMultiByteStr, int32 cbMultiByte,
											const achar* lpDefaultChar, int32* lpUsedDefaultChar);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

INLINE achar** CommandLineToArgvA(const achar* lpCmdLine, int32* pNumArgs) noexcept
{
	constexpr size_t BufferSize = 64;
	static char errorMsgBuffer[BufferSize];
	auto retVal = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, nullptr, 0);
	if (!SUCCEEDED(retVal))
	{
		// Error
		if (IsDebuggerPresent() == 1)
		{
			const auto errorCode = GetLastError();
			snprintf(errorMsgBuffer, BufferSize, "MultiByteToWideChar failed, error code: %d.", errorCode);

			DEBUG_OUTPUT(errorMsgBuffer);
			DebugBreak();
		}
		return nullptr;
	}

	auto lpWideCharStr = (wchar*)PlatformAlloc(retVal * sizeof(wchar_t));
	if (lpWideCharStr == nullptr)
	{
		if (IsDebuggerPresent() == 1)
		{
			snprintf(errorMsgBuffer, BufferSize, "PlatformAlloc couldn't allocate %zd bytes.", retVal * sizeof(wchar_t));
			DEBUG_OUTPUT(errorMsgBuffer);
			DebugBreak();
		}
		return nullptr;
	}

	retVal = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, lpWideCharStr, retVal);
	if (!SUCCEEDED(retVal))
	{
		if (IsDebuggerPresent() == 1)
		{
			const auto errorCode = GetLastError();
			snprintf(errorMsgBuffer, BufferSize, "MultiByteToWideChar failed, error code: %d.", errorCode);
			DEBUG_OUTPUT(errorMsgBuffer);
			DebugBreak();
		}
		PlatformDealloc(lpWideCharStr);
		return nullptr;
	}

	int numArgs;
	wchar** args = CommandLineToArgvW(lpWideCharStr, &numArgs);
	PlatformDealloc(lpWideCharStr);
	if (!args)
	{
		if (IsDebuggerPresent() == 1)
		{
			const auto errorCode = GetLastError();
			snprintf(errorMsgBuffer, BufferSize, "CommandLineToArgvW returned nullptr, error code: %d.", errorCode);
			DEBUG_OUTPUT(errorMsgBuffer);
			DebugBreak();
		}
		return nullptr;
	}

	int storage = numArgs * sizeof(achar);
	for (int i = 0; i < numArgs; ++i)
	{
		int32 lpUsedDefaultChar = 0;
		retVal = WideCharToMultiByte(CP_ACP, 0, args[i], -1, nullptr, 0,
			nullptr, &lpUsedDefaultChar);
		if (!SUCCEEDED(retVal))
		{
			if (IsDebuggerPresent() == 1)
			{
				const auto errorCode = GetLastError();
				snprintf(errorMsgBuffer, BufferSize, "WideCharToMultiByte failed, error code: %d.", errorCode);
				DEBUG_OUTPUT(errorMsgBuffer);
				DebugBreak();
			}
			LocalFree(args);
			return nullptr;
		}
		storage += retVal;
	}
	auto* result = (achar**)LocalAlloc(LMEM_FIXED, storage);
	if (!result)
	{
		LocalFree(args);
		if (IsDebuggerPresent() == 1)
		{
			const auto errorCode = GetLastError();
			snprintf(errorMsgBuffer, BufferSize, "LocalAlloc returned nullptr, error code: %d.", errorCode);
			DEBUG_OUTPUT(errorMsgBuffer);
			DebugBreak();
		}
		return nullptr;
	}

	int bufLen = storage - numArgs * sizeof(achar*);
	achar* buffer = ((achar*)result) + numArgs * sizeof(achar*);
	for (int i = 0; i < numArgs; ++i)
	{
		if (bufLen <= 0)
		{
			if (IsDebuggerPresent() == 1)
			{
				const auto errorCode = GetLastError();
				snprintf(errorMsgBuffer, BufferSize, "LocalAlloc returned nullptr, error code: %d.", errorCode);
				DEBUG_OUTPUT(errorMsgBuffer);
				DebugBreak();
			}
			LocalFree(result);
			LocalFree(args);
			return nullptr;
		}
		int32 lpUsedDefaultChar = 0;
		retVal = WideCharToMultiByte(CP_ACP, 0, args[i], -1, buffer, bufLen,
			nullptr, &lpUsedDefaultChar);
		if (!SUCCEEDED(retVal))
		{
			if (IsDebuggerPresent() == 1)
			{
				const auto errorCode = GetLastError();
				snprintf(errorMsgBuffer, BufferSize, "WideCharToMultiByte failed, error code: %d.", errorCode);
				DEBUG_OUTPUT(errorMsgBuffer);
				DebugBreak();
			}
			LocalFree(result);
			LocalFree(args);
			return nullptr;
		}

		result[i] = buffer;
		buffer += retVal;
		bufLen -= retVal;
	}

	LocalFree(args);
	*pNumArgs = numArgs;
	return result;
}

INLINE void FreeArgvA(achar** argv) noexcept
{
	if (argv == nullptr)
		return;
	LocalFree(argv);
}

#endif
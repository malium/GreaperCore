/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

INLINE void greaper::WinOSPlatform::Sleep(uint32 millis) noexcept
{
	::Sleep(millis);
}

inline greaper::String greaper::WinOSPlatform::GetExceptionMessage(PEXCEPTION_RECORD record)
{
	StringView errorType;
	switch (record->ExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		if (record->NumberParameters != 2)
		{
			return Format("Unhandled exception at " PTR_HEX_FMT ". Access violation.",
				(ptruint)record->ExceptionAddress);
		}
		errorType = 
			record->ExceptionInformation[0] == 0 ?	"reading"sv :
			record->ExceptionInformation[0] == 8 ?	"DEP"sv : 
													"writing"sv;

		return Format("Unhandled exception at " PTR_HEX_FMT ". Access violation %s " I64_HEX_FMT ".",
			(ptruint)record->ExceptionAddress, errorType.data(), record->ExceptionInformation[1]);
	case EXCEPTION_IN_PAGE_ERROR:
		if (record->NumberParameters != 3)
		{
			return Format("Unhandled exception at " PTR_HEX_FMT ". Page fault.",
				(ptruint)record->ExceptionAddress);
		}
		errorType =
			record->ExceptionInformation[0] == 0 ?	"reading"sv :
			record->ExceptionInformation[0] == 8 ?	"DEP"sv :
													"writing"sv;

		return Format("Unhandled exception at " PTR_HEX_FMT ". Page fault %s " I64_HEX_FMT " with code " I64_HEX_FMT ".",
			(ptruint)record->ExceptionAddress, errorType.data(), record->ExceptionInformation[1],
			record->ExceptionInformation[2]);
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Attempting to access an out of range array element.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_DATATYPE_MISALIGNMENT:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Attempting to access misaligned data.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_FLT_DENORMAL_OPERAND:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Floating point operand too small.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Floating point operation attempted to divide by zero.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_FLT_INVALID_OPERATION:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Floating point invalid operation.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_FLT_OVERFLOW:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Floating point overflow.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_FLT_UNDERFLOW:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Floating point underflow.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_FLT_STACK_CHECK:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Floating point stack overflow/underflow.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_ILLEGAL_INSTRUCTION:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Attempting to execute an illegal instruction.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Integer operation attempted to divide by zero.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_INT_OVERFLOW:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Integer overflow.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_STACK_OVERFLOW:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Stack overflow.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_INVALID_HANDLE:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Invalid Handle.",
			(ptruint)record->ExceptionAddress);
	case EXCEPTION_POSSIBLE_DEADLOCK:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Possible deadlock.",
			(ptruint)record->ExceptionAddress);
	default:
		return Format("Unhandled exception at " PTR_HEX_FMT ". Code: " I32_HEX_FMT ".",
			(ptruint)record->ExceptionAddress, record->ExceptionCode);
	}
}

INLINE void greaper::WinOSPlatform::WriteMiniDump(std::filesystem::path path, PEXCEPTION_POINTERS exceptionData)
{
	LOCK(m_Mutex);

	auto hFile = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		// something went wrong
		const auto errorCode = GetLastError();
		DEBUG_OUTPUT(Format("Something went wrong while creating the MiniDump file. Error code: " I32_HEX_FMT, errorCode).c_str());
		return;
	}

	MINIDUMP_EXCEPTION_INFORMATION dumpExceptionInfo;
	ClearMemory(dumpExceptionInfo);

	dumpExceptionInfo.ThreadId = GetCurrentThreadId();
	dumpExceptionInfo.ExceptionPointers = exceptionData;
	dumpExceptionInfo.ClientPointers = false;

	InitDbgHelp();

	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal,
		&dumpExceptionInfo, nullptr, nullptr);
	CloseHandle(hFile);
}

INLINE greaper::String greaper::WinOSPlatform::GetStackTrace()
{
	LOCK(m_Mutex);

	CONTEXT context;
	RtlCaptureContext(&context);

	InitPSAPI();
	InitDbgHelp();

	LoadSymbols();
	auto stackTrace = GetStackTrace(context, 1);
	UnloadSymbols();

	return stackTrace;
}

INLINE void greaper::WinOSPlatform::_PerThreadInit()
{
#if COMPILER_MSVC
	_set_se_translator(&WinOSPlatform::SETranslatorFn);
#endif
}

INLINE void greaper::WinOSPlatform::_PerLibraryInit()
{
	DetectWindowsVersion();
}

INLINE void greaper::WinOSPlatform::DetectWindowsVersion() noexcept
{
	auto IsWinVerOrGreater = [](WORD majorVer, WORD minorVer, WORD servicePackMajor)
	{
		OSVERSIONINFOEXW osvi;
		ClearMemory(osvi);
		osvi.dwOSVersionInfoSize = sizeof(osvi);
		const auto conditionMask = (DWORDLONG)VerSetConditionMask(
			VerSetConditionMask(
				VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL),
				VER_MINORVERSION, VER_GREATER_EQUAL),
			VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

		osvi.dwMajorVersion = majorVer;
		osvi.dwMinorVersion = minorVer;
		osvi.wServicePackMajor = servicePackMajor;

		return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, conditionMask) != FALSE;
	};

	if (IsWinVerOrGreater(HIBYTE(_WIN32_WINNT_WIN10), LOBYTE(_WIN32_WINNT_WIN10), 0))
	{
		WindowsVersion = WindowsVersion_t::Windows10;
		return;
	}
	if (IsWinVerOrGreater(HIBYTE(_WIN32_WINNT_WINBLUE), LOBYTE(_WIN32_WINNT_WINBLUE), 0))
	{
		WindowsVersion = WindowsVersion_t::Windows81;
		return;
	}
	if (IsWinVerOrGreater(HIBYTE(_WIN32_WINNT_WIN8), LOBYTE(_WIN32_WINNT_WIN8), 0))
	{
		WindowsVersion = WindowsVersion_t::Windows8;
		return;
	}
	if (IsWinVerOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0))
	{
		WindowsVersion = WindowsVersion_t::Windows7;
		return;
	}
	WindowsVersion = WindowsVersion_t::Unknown;
}

INLINE uint64 greaper::WinOSPlatform::GetPhysicalRAMAmountKB()noexcept
{
	ULONGLONG amount;
	const auto ret = GetPhysicallyInstalledSystemMemory(&amount);
	if (ret == TRUE)
		return amount;
	const auto err = GetLastError();
	DEBUG_OUTPUT(Format("Couldn't GetPhysicallyInstalledSystemMemory, error code: " I32_HEX_FMT, err).c_str());
	return 0ull;
}

INLINE greaper::DialogButton_t greaper::WinOSPlatform::CreateMessageBox(StringView title, StringView content, DialogChoice_t choice, DialogIcon_t icon)
{
	UINT uType = MB_SYSTEMMODAL;
	switch (choice)
	{
	case DialogChoice_t::OK: uType |= MB_OK; break;
	case DialogChoice_t::OK_CANCEL: uType |= MB_OKCANCEL; break;
	case DialogChoice_t::YES_NO: uType |= MB_YESNO; break;
	case DialogChoice_t::YES_NO_CANCEL: uType |= MB_YESNOCANCEL; break;
	case DialogChoice_t::RETRY_CANCEL: uType |= MB_RETRYCANCEL; break;
	case DialogChoice_t::ABORT_RETRY_IGNORE: uType |= MB_ABORTRETRYIGNORE; break;
	default: uType |= MB_OK; break;
	}

	switch (icon)
	{
	case DialogIcon_t::INFO: uType |= MB_ICONINFORMATION; break;
	case DialogIcon_t::WARNING: uType |= MB_ICONWARNING; break;
	case DialogIcon_t::ERROR: uType |= MB_ICONERROR; break;
	case DialogIcon_t::QUESTION: uType |= MB_ICONQUESTION; break;
	default: uType |= MB_ICONINFORMATION;
	}

	auto wstrings = AllocN<wchar>(title.length() + content.length() + 2);
	auto wtitle = wstrings;
	auto wcontent = wstrings + title.length() + 2;
	for(std::size_t i = 0; i < title.length(); ++i)
		wtitle[i] = static_cast<wchar>(title[i]);
	wtitle[title.length() + 1] = 0;

	for(std::size_t i = 0; i < content.length(); ++i)
		wcontent[i] = static_cast<wchar>(content[i]);
	wcontent[content.length() + 1] = 0;

	int32 rtn = MessageBoxW(nullptr, wcontent, wtitle, uType);

	Dealloc(wstrings);

	switch (rtn)
	{
	case IDOK: return DialogButton_t::OK;
	case IDCANCEL: return DialogButton_t::CANCEL;
	case IDABORT: return DialogButton_t::ABORT;
	case IDTRYAGAIN:
	case IDRETRY: return DialogButton_t::RETRY;
	case IDCONTINUE:
	case IDIGNORE: return DialogButton_t::IGNORE;
	case IDYES: return DialogButton_t::YES;
	case IDNO: return DialogButton_t::NO;
	default: return DialogButton_t::OK;
	}
}

#define LoadProc(lib, name, var)\
fnRes = lib.GetFunction(name); \
if(fnRes.IsOk()) { var = (decltype(var))fnRes.GetValue(); } \
else { var = nullptr; DEBUG_OUTPUT(fnRes.GetFailMessage().c_str()); }

INLINE void greaper::WinOSPlatform::InitPSAPI()
{
	if (PSAPI.IsOpen())
		return;

	PSAPI.Open(L"PSAPI.dll"sv);
	Verify(PSAPI.IsOpen(), "Couldn't load library PSAPI.dll!");

	TResult<FuncPtr> fnRes;
	LoadProc(PSAPI, "EnumProcessModules"sv, EnumProcessModules);
	LoadProc(PSAPI, "GetModuleBaseNameA"sv, GetModuleBaseName);
	LoadProc(PSAPI, "GetModuleFileNameExA"sv, GetModuleFileNameEx);
	LoadProc(PSAPI, "GetModuleInformation"sv, GetModuleInformation);
}

INLINE void greaper::WinOSPlatform::InitDbgHelp()
{
	if (DbgHelp.IsOpen())
		return;

	DbgHelp.Open(L"Dbghelp.dll"sv);
	Verify(PSAPI.IsOpen(), "Couldn't load library Dbghelp.dll!");

	TResult<FuncPtr> fnRes;
	LoadProc(DbgHelp, "MiniDumpWriteDump"sv, MiniDumpWriteDump);
	LoadProc(DbgHelp, "SymGetOptions"sv, SymGetOptions);
	LoadProc(DbgHelp, "SymSetOptions"sv, SymSetOptions);
	LoadProc(DbgHelp, "SymInitialize"sv, SymInitialize);
	LoadProc(DbgHelp, "SymSetSearchPath"sv, SymSetSearchPath);
	LoadProc(DbgHelp, "SymLoadModule64"sv, SymLoadModule64);
	LoadProc(DbgHelp, "SymGetModuleInfo64"sv, SymGetModuleInfo64);
	LoadProc(DbgHelp, "SymCleanup"sv, SymCleanup);
	LoadProc(DbgHelp, "StackWalk64"sv, StackWalk64);
	LoadProc(DbgHelp, "SymGetSymFromAddr64"sv, SymGetSymFromAddr64);
	LoadProc(DbgHelp, "SymGetLineFromAddr64"sv, SymGetLineFromAddr64);
}

#undef LoadProc

INLINE void greaper::WinOSPlatform::LoadSymbols()
{
	InitDbgHelp();
	auto hProcess = GetCurrentProcess();
	auto options = SymGetOptions();
	options |= (SYMOPT_LOAD_LINES | SYMOPT_EXACT_SYMBOLS | SYMOPT_UNDNAME | SYMOPT_FAIL_CRITICAL_ERRORS | SYMOPT_NO_PROMPTS);

	SymSetOptions(options);
	if (!SymInitialize(hProcess, nullptr, false))
	{
		// Something went wrong
		const auto errorCode = GetLastError();
		DEBUG_OUTPUT(Format("SymInitialize() failed. Error code: " I32_HEX_FMT, errorCode).c_str());
		return;
	}

	DWORD bufferSize;
	EnumProcessModules(hProcess, nullptr, 0, &bufferSize);

	const auto moduleCount = (uint32)(bufferSize / sizeof(HMODULE));

	auto* modules = AllocN<HMODULE>(moduleCount);
	EnumProcessModules(hProcess, modules, bufferSize, &bufferSize);

	std::array<achar, MAX_STACKTRACE_NAME_LENGTH> moduleName{};
	std::array<achar, MAX_STACKTRACE_NAME_LENGTH> imageName{};
	std::array<achar, MAX_STACKTRACE_NAME_LENGTH> pdbSearchPath{};

	MODULEINFO moduleInfo;
	achar* fileName;

	for (uint32 i = 0; i < moduleCount; ++i)
	{
		GetModuleInformation(hProcess, modules[i], &moduleInfo, sizeof(moduleInfo));
		GetModuleFileNameEx(hProcess, modules[i], imageName.data(), MAX_STACKTRACE_NAME_LENGTH);
		GetModuleBaseName(hProcess, modules[i], moduleName.data(), MAX_STACKTRACE_NAME_LENGTH);

		GetFullPathNameA(moduleName.data(), MAX_STACKTRACE_NAME_LENGTH, pdbSearchPath.data(), &fileName);

		SymSetSearchPath(hProcess, pdbSearchPath.data());

		auto moduleAddress = SymLoadModule64(hProcess, modules[i], imageName.data(),
			moduleName.data(), (DWORD64)moduleInfo.lpBaseOfDll, moduleInfo.SizeOfImage);

		if (moduleAddress != 0)
		{
			IMAGEHLP_MODULE64 imageInfo;
			ClearMemory(imageInfo);
			imageInfo.SizeOfStruct = sizeof(imageInfo);

			if (!SymGetModuleInfo64(hProcess, moduleAddress, &imageInfo))
			{
				// error
				const auto errorCode = GetLastError();
				DEBUG_OUTPUT(Format("Failed retrieving module information for module '%s'. Error code: " I32_HEX_FMT, moduleName.data(),
					errorCode).c_str());
				continue;
			}
		}
		else
		{
			// error
			const auto errorCode = GetLastError();
			DEBUG_OUTPUT(Format("Failed loading module '%s', Search path '%s', Image name '%s'. Error code: " I32_HEX_FMT, moduleName.data(),
				pdbSearchPath.data(), imageName.data(), errorCode).c_str());
			continue;
		}
	}

	Dealloc(modules);
}

INLINE void greaper::WinOSPlatform::UnloadSymbols()
{
	SymCleanup(GetCurrentProcess());
}

INLINE uint32 greaper::WinOSPlatform::GetRawStackTrace(CONTEXT context, std::array<DWORD64, MAX_STACKTRACE_DEPTH>& stackTrace)
{
	auto hProcess = GetCurrentProcess();
	auto hThread = GetCurrentThread();
	uint32 machineType;

	STACKFRAME64 stackFrame;
	ClearMemory(stackFrame);

	stackFrame.AddrPC.Mode = AddrModeFlat;
	stackFrame.AddrStack.Mode = AddrModeFlat;
	stackFrame.AddrFrame.Mode = AddrModeFlat;

#if ARCHITECTURE_X64
	stackFrame.AddrPC.Offset = context.Rip;
	stackFrame.AddrStack.Offset = context.Rip;
	stackFrame.AddrFrame.Offset = context.Rip;

	machineType = IMAGE_FILE_MACHINE_AMD64;
#else
	stackFrame.AddrPC.Offset = context.Eip;
	stackFrame.AddrStack.Offset = context.Eip;
	stackFrame.AddrFrame.Offset = context.Eip;

	machineType = IMAGE_FILE_MACHINE_I386;
#endif

	uint32 entryCount = 0;
	while (true)
	{
		if (!StackWalk64(machineType, hProcess, hThread, &stackFrame, &context,
			nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
			break;

		if (entryCount < MAX_STACKTRACE_DEPTH)
			stackTrace[entryCount] = stackFrame.AddrPC.Offset;

		++entryCount;

		if (stackFrame.AddrPC.Offset == 0 || stackFrame.AddrFrame.Offset == 0)
			break;
	}
	return entryCount;
}

INLINE greaper::String greaper::WinOSPlatform::GetStackTrace(CONTEXT context, uint32 skip)
{
	std::array<DWORD64, MAX_STACKTRACE_DEPTH> rawStackTrace;
	auto entryCount = GetRawStackTrace(context, rawStackTrace);

	entryCount = Min(entryCount, (uint32)MAX_STACKTRACE_DEPTH);

	constexpr auto symbolSize = sizeof(IMAGEHLP_SYMBOL64) + MAX_STACKTRACE_NAME_LENGTH;

	auto symbol = UPtr<IMAGEHLP_SYMBOL64>((PIMAGEHLP_SYMBOL64)Alloc(symbolSize), &Impl::CStrucDeleter<IMAGEHLP_SYMBOL64>);
	memset(symbol.Get(), 0, symbolSize);
	symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
	symbol->Size = symbolSize;
	symbol->MaxNameLength = MAX_STACKTRACE_NAME_LENGTH;

	auto hProcess = GetCurrentProcess();

	String output;

	std::array<achar, MAX_SYM_NAME + 1 + 8> fnName{};
	std::array<achar, MAX_PATH + 20 + 10 + 10 + 20> fileData{};
	std::array<achar, 256 + 12> moduleString{};
	DWORD64 dummy;
	DWORD column;

	for (decltype(entryCount) i = skip; i < entryCount; ++i)
	{
		if (i > skip)
			output += '\n';

		auto fnAddr = rawStackTrace[i];
		
		if (SymGetSymFromAddr64(hProcess, fnAddr, &dummy, symbol.Get()))
		{
			auto sz = snprintf(fnName.data(), fnName.size(), "%s() - ", symbol->Name);
			output.append(fnName.data(), (std::size_t)sz);
		}

		IMAGEHLP_LINE64 lineData;
		ClearMemory(lineData);
		lineData.SizeOfStruct = sizeof(lineData);

		if (SymGetLineFromAddr64(hProcess, fnAddr, &column, &lineData))
		{
			auto sz = snprintf(fileData.data(), fileData.size(), I64_HEX_FMT " File[%s:%d (%d)]",
				fnAddr, lineData.FileName, lineData.LineNumber, column);
			output.append(fileData.data(), (std::size_t)sz);
		}

		IMAGEHLP_MODULE64 moduleData;
		ClearMemory(moduleData);
		moduleData.SizeOfStruct = sizeof(moduleData);

		if (SymGetModuleInfo64(hProcess, fnAddr, &moduleData))
		{
			auto sz = snprintf(moduleString.data(), moduleString.size(), " Module[%s]", moduleData.ImageName);
			output.append(moduleString.data(), (std::size_t)sz);
		}
	}

	return output;
}

#if COMPILER_MSVC
INLINE void greaper::WinOSPlatform::SETranslatorFn(unsigned int se, _EXCEPTION_POINTERS* exceptPointers)
{
	throw SEHException(se, exceptPointers);
}
#endif
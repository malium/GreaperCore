/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H 1

#include "CorePrerequisites.h"
#define CJSON_IMPORT_SYMBOLS
#define CJSON_API_VISIBILITY
#include "../../cJSON/cJSON.h"

namespace greaper
{
	namespace EOSType
	{
		enum Type
		{
			Windows,
			Linux
		};
	}
	using OSType_t = EOSType::Type;

	namespace EDialogButton
	{
		enum Type
		{
			CANCEL,
			OK,
			YES,
			NO,
			ABORT,
			RETRY,
			IGNORE
		};
	}
	using DialogButton_t = EDialogButton::Type;

	namespace EDialogChoice
	{
		enum Type
		{
			OK,
			OK_CANCEL,
			YES_NO,
			YES_NO_CANCEL,
			RETRY_CANCEL,
			ABORT_RETRY_IGNORE
		};
	}
	using DialogChoice_t = EDialogChoice::Type;

	namespace EDialogIcon
	{
		enum Type
		{
			INFO,
			WARNING,
			ERROR,
			QUESTION
		};
	}
	using DialogIcon_t = EDialogIcon::Type;
}

#if PLT_WINDOWS
#include "Win/WinPlatform.h"
#include <intrin.h>
#define cpuid(out, x) __cpuidex(out, x, 0)
#elif PLT_LINUX
#include "Lnx/LnxPlatform.h"
#include <cpuid.h>
#define cpuid(out, x) __cpuid_count(x, 0, out[0], out[1], out[2], out[3])
#endif

namespace greaper
{
	class OSPlatform
#if PLT_WINDOWS
		final : public WinOSPlatform
#elif PLT_LINUX
		final : public LnxOSPlatform
#endif
	{
	public:
		static void PerThreadInit();

		static void PerLibraryInit();

		static const CPUInfo& GetCPUInfo()noexcept;

	private:
		static inline CPUInfo m_CPUInfo;

		static void InitCPUInfo()noexcept;
	};
}

#include "Base/Platform.inl"

#undef cpuid

#endif /* CORE_PLATFORM_H */

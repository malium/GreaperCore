/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_LNX_PLATFORM_H
#define CORE_LNX_PLATFORM_H 1

#include "../CorePrerequisites.h"
#include "../Base/CPUInfo.h"

namespace greaper
{
	class LnxOSPlatform
	{
		static void Sleep(uint32 millis) noexcept;

		static String GetStackTrace();

		static uint64 GetPhysicalRAMAmountKB()noexcept;

		static OSType_t GetOSType()noexcept { return OSType_t::Linux; }

		static DialogButton_t CreateMessageBox(StringView title, StringView content, DialogChoice_t choice = DialogChoice_t::OK, DialogIcon_t icon = DialogIcon_t::INFO);

		static Vector<String> CreateOpenFileDialog(StringView title, StringView defaultPath = ""sv, const Vector<StringView>& filters = { "All files"sv, "*"sv }, bool multiselect = false);

		static String CreateSaveFileDialog(StringView title, StringView defaultPath = ""sv, const Vector<StringView>& filters = { "All files"sv, "*"sv }, bool forceOverride = false);

		static Vector<String> CreateSelectDirectoryDialog(StringView title, StringView defaultPath = ""sv, bool multiselect = false);

	protected:
		static void _PerThreadInit();

		static void _PerLibraryInit();
	};
}

#include "LnxPlatform.inl"

#endif /* CORE_LNX_PLATFORM_H */
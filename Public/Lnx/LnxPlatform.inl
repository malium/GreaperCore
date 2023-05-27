/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#include <thread>
//#include "LnxPlatform.h"

INLINE void greaper::LnxOSPlatform::Sleep(uint32 millis) noexcept
{
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

INLINE greaper::String greaper::LnxOSPlatform::GetStackTrace()
{
	return {};
}

INLINE uint64 greaper::LnxOSPlatform::GetPhysicalRAMAmountKB() noexcept {
	return 0;
}

INLINE greaper::DialogButton_t greaper::LnxOSPlatform::CreateMessageBox(greaper::StringView title, greaper::StringView content,
																 greaper::DialogChoice_t choice,
																 greaper::DialogIcon_t icon) {
	return greaper::DialogButton_t::RETRY;
}

INLINE void greaper::LnxOSPlatform::_PerThreadInit()
{

}

INLINE void greaper::LnxOSPlatform::_PerLibraryInit()
{

}
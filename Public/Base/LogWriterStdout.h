/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_LOG_WRITER_STDOUT_H
#define CORE_LOG_WRITER_STDOUT_H 1

#include "../ILogManager.h"

namespace greaper
{
	class LogWriterStdout : ILogWriter
	{
		static constexpr const achar* gLevelName[] =
		{
			"VERB",
			"INFO",
			"WARN",
			"ERRO",
			"CRIT"
		};

	public:
		INLINE explicit LogWriterStdout()noexcept = default;
		INLINE bool WritePreviousMessages()const noexcept override { return true; }

		INLINE void WriteLog(const LogData& logData)noexcept override
		{
			static achar gTimeBuff[64];

			auto time = std::chrono::system_clock::to_time_t(logData.Time);
			std::strftime(gTimeBuff, ArraySize(gTimeBuff), "%H:%M:%S", std::localtime(&time));

			printf("[%s][%s][%s]: %s\n", gLevelName[(sizet)logData.Level], gTimeBuff, logData.LibraryName.data(), logData.Message.c_str());
		}
	};
}

#endif /* CORE_LOG_WRITER_STDOUT_H */
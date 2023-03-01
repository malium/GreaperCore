/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_THREAD_MANAGER_H
#define CORE_I_THREAD_MANAGER_H 1

#include "CorePrerequisites.h"
#include "Interface.h"
#include "Result.h"
#include "Event.h"

namespace greaper
{
	class IThreadManager : public TInterface<IThreadManager>
	{
	public:
		static constexpr Uuid InterfaceUUID = Uuid{ 0x284B5BAD, 0x9B004E76, 0x8B7F76DD, 0xB45D740F };
		static constexpr StringView InterfaceName = "ThreadManager"sv;

		using ThreadCreationEvent_t = Event<const PThread&>;
		using ThreadDestructionEvent_t = Event<const PThread&>;

		virtual ~IThreadManager()noexcept = default;

		virtual TResult<WThread> GetThread(ThreadID_t id)const noexcept = 0;

		virtual TResult<WThread> GetThread(const String& threadName)const noexcept = 0;

		virtual TResult<PThread> CreateThread(const ThreadConfig& config)noexcept = 0;

		virtual ThreadCreationEvent_t& GetThreadCreationEvent()const noexcept = 0;

		virtual ThreadDestructionEvent_t& GetThreadDestructionEvent()const noexcept = 0;

		virtual void AccessThreads(const std::function<void(CSpan<PThread>)>& accessFn)const noexcept = 0;
	};
}

#endif /* CORE_I_THREAD_MANAGER_H */
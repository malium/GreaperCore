/***********************************************************************************
*   Copyright 2022 Marcos S�nchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_SLIM_TASK_SCHEDULER_H
#define CORE_SLIM_TASK_SCHEDULER_H 1

#include "CorePrerequisites.h"
#include "Concurrency.h"
#include "IThreadManager.h"
#include "IApplication.h"
#include "Base/IThread.h"
#include "Result.h"
#include <future>

namespace greaper
{
	struct SlimTask
	{
		enum TaskState
		{
			READY,
			SCHEDULED,
			WORKING,
			DONE
		};

		std::function<void()> Task = nullptr;
		std::atomic_int State = DONE;
	};

	class SlimTaskScheduler
	{
	public:
		template<class _Alloc_ = GenericAllocator>
		static PSlimScheduler Create(WThreadManager threadMgr, StringView name, sizet workerCount, bool allowGrowth = true)noexcept;

		~SlimTaskScheduler()noexcept;

		SlimTaskScheduler(const SlimTaskScheduler&) = delete;
		SlimTaskScheduler& operator=(const SlimTaskScheduler&) = delete;

		sizet GetWorkerCount()const noexcept;
		EmptyResult SetWorkerCount(sizet count)noexcept;

		TResult<uint32> AddTask(std::function<void()> task)noexcept;

		void WaitUntilTaskFinished(uint32 taskID)const noexcept;

		void WaitUntilAllTasksFinished()const noexcept;

		const String& GetName()const noexcept;

		bool IsGrowthEnabled()const noexcept;
		void EnableGrowth(bool enable)noexcept;

	private:
		WThreadManager m_ThreadManager;
		String m_Name;

		Vector<PThread> m_TaskWorkers;
		mutable RWMutex m_TaskWorkersMutex;

		uint32 m_LastTaskSlotUsed;
		std::array<SlimTask, 256> m_TaskSlots;
		mutable Mutex m_TaskQueueMutex;
		mutable Signal m_TaskQueueSignal;
		//Deque<SlimTask*> m_TaskQueue;

		//Vector<SlimTask*> m_FreeTaskPool;
		//mutable Mutex m_FreeTaskPoolMutex;

		SPtr<SlimTaskScheduler> m_This;
		bool m_AllowGrowth;

		IInterface::ActivationEvt_t::HandlerType m_OnManagerActivation;
		IApplication::OnInterfaceActivationEvent_t::HandlerType m_OnNewManager;

		void OnNewManager(const PInterface& newInterface)noexcept;
		void OnManagerActivation(bool active, IInterface* oldInterface, const PInterface& newInterface)noexcept;

		void Stop()noexcept;

		bool AreThereAnyAvailableWorker()const noexcept;
		
		SlimTaskScheduler(WThreadManager threadMgr, StringView name, sizet workerCount, bool allowGrowth)noexcept;

		bool CanWorkerContinueWorking(sizet workerID)const noexcept;

		static void WorkerFn(SlimTaskScheduler& scheduler, sizet id)noexcept;

		bool IsTaskQueueEmpty()const noexcept;

		bool IsAnyTaskReady(uint32& queueTaskID, uint32 prevHandledTask = 0)const noexcept;
	};
}

#include "Base/SlimTaskScheduler.inl"

#endif /* CORE_SLIM_TASK_SCHEDULER_H */
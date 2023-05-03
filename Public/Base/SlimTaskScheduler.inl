/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

//#include "../SlimTaskScheduler.h"

namespace greaper
{
	template<class _Alloc_>
	INLINE PSlimScheduler SlimTaskScheduler::Create(WThreadManager threadMgr, StringView name, sizet workerCount, bool allowGrowth) noexcept
	{
		auto* ptr = AllocT<SlimTaskScheduler, _Alloc_>();
		new ((void*)ptr)SlimTaskScheduler(threadMgr, std::move(name), workerCount, allowGrowth);
		return SPtr<SlimTaskScheduler>((SlimTaskScheduler*)ptr, &Impl::DefaultDeleter<SlimTaskScheduler, _Alloc_>);
	}

	INLINE SlimTaskScheduler::~SlimTaskScheduler() noexcept
	{
		Stop();
		m_This.reset();
	}

	INLINE sizet SlimTaskScheduler::GetWorkerCount() const noexcept { auto lck = SharedLock(m_TaskWorkersMutex); return m_TaskWorkers.size(); }

	inline EmptyResult SlimTaskScheduler::SetWorkerCount(sizet count) noexcept
	{
		m_TaskWorkersMutex.lock();
		if (m_TaskWorkers.size() == count)
		{
			m_TaskWorkersMutex.unlock();
			return Result::CreateSuccess();
		}
		// Add new workers
		if (m_TaskWorkers.size() < count)
		{
			auto lck = Lock<decltype(m_TaskWorkersMutex)>(m_TaskWorkersMutex, AdoptLock{});
			
			if(!m_AllowGrowth)
				return Result::CreateFailure("Trying to add more workers to a SlimTaskScheduler, but it has forbidden the growth."sv);

			if (m_ThreadManager.expired())
				return Result::CreateFailure("Trying to add more workers to a SlimTaskScheduler, but the ThreadManager has expired."sv);

			auto thManager = m_ThreadManager.lock();
			for (sizet i = m_TaskWorkers.size(); i < count; ++i)
			{
				ThreadConfig cfg;
				auto name = Format("%s_%" PRIuPTR "", m_Name.c_str(), i);
				cfg.Name = name;
				cfg.ThreadFN = [this, i]() { WorkerFn(*this, i); };
				auto thRes = thManager->CreateThread(cfg);
				if (thRes.HasFailed())
					return Result::CopyFailure(thRes);
				m_TaskWorkers.push_back(thRes.GetValue());
			}
		}
		// Remove workers
		else
		{
			while (m_TaskWorkers.size() > count)
			{
				const auto sz = m_TaskWorkers.size();
				PThread th = m_TaskWorkers[sz - 1];
				m_TaskWorkers[sz - 1].reset();
				m_TaskWorkersMutex.unlock();
				while (th != nullptr)
				{
					if (th->TryJoin())
					{
						th.reset();
					}
					else
					{
						m_TaskQueueSignal.notify_all();
						THREAD_YIELD();
					}
				}
				m_TaskQueueMutex.lock();
				m_TaskWorkers.erase(m_TaskWorkers.begin() + (sz - 1));
			}
		}
		return Result::CreateSuccess();
	}
	
	inline TResult<uint32> SlimTaskScheduler::AddTask(std::function<void()> task) noexcept
	{
		if (task == nullptr)
			return Result::CreateFailure<uint32>("Trying to create a nullptr task."sv);

		auto wkLck = SharedLock(m_TaskWorkersMutex); // we keep the lock so if there's only 1 task worker and someone wants to remove it, we can still schedule this task
		if (!AreThereAnyAvailableWorker())
		{
			return Result::CreateFailure<uint32>("Couldn't add the task, no available workers."sv);
		}

		uint32 taskSlotIdx;
		{
			auto lck = UniqueLock<decltype(m_TaskQueueMutex)>(m_TaskQueueMutex);
			while (!IsNextTaskAvailable())
				m_TaskQueueSignal.wait(lck);

			taskSlotIdx = m_LastTaskSlotUsed++;
			if (m_LastTaskSlotUsed >= m_TaskSlots.size())
				taskSlotIdx = m_LastTaskSlotUsed = 0;
			auto& taskSlot = m_TaskSlots[taskSlotIdx];
			taskSlot.Task = std::move(task);
			taskSlot.State = SlimTask::READY;
		}

		/*m_TaskQueueMutex.lock();
		uint32 taskSlotIdx = m_LastTaskSlotUsed++;
		if (m_LastTaskSlotUsed >= m_TaskSlots.size())
			m_LastTaskSlotUsed = 0;
		auto& taskSlot = m_TaskSlots[taskSlotIdx];
		taskSlot.Task = std::move(task);
		taskSlot.State = SlimTask::READY;
		m_TaskQueueMutex.unlock();*/
		m_TaskQueueSignal.notify_one();

		//SlimTask* taskPtr;
		//{
		//	auto fpLck = Lock(m_FreeTaskPoolMutex);
		//	if (m_FreeTaskPool.empty())
		//	{
		//		taskPtr = AllocT<SlimTask>();
		//	}
		//	else
		//	{
		//		taskPtr = m_FreeTaskPool.back();
		//		m_FreeTaskPool.pop_back();
		//	}
		//}
		// All taskPtr will be uninitialized memory so we call the move constructor
		//new(taskPtr)SlimTask(std::move(task));
		//
		//m_TaskQueueMutex.lock();
		//m_TaskQueue.push_back(taskPtr);
		//m_TaskQueueMutex.unlock();
		//m_TaskQueueSignal.notify_one();
		
		return Result::CreateSuccess(taskSlotIdx);
	}

	INLINE void SlimTaskScheduler::WaitUntilTaskFinished(uint32 taskID)const noexcept
	{
		if (taskID >= m_TaskSlots.size())
			return; // Invalid ID

		// Don't add more tasks nor change the amount of workers
		auto wkLck = SharedLock(m_TaskWorkersMutex);

		// Wait until no more tasks
		//auto lck = UniqueLock<decltype(m_TaskQueueMutex)>(m_TaskQueueMutex);
		auto checkTask = [this](uint32 taskID)
		{
			LOCK(m_TaskQueueMutex);
			const auto& slot = m_TaskSlots[taskID];
			return slot.State != SlimTask::DONE && slot.Task != nullptr;
		};
		while (checkTask(taskID))
		{
			//m_TaskQueueSignal.wait(lck);
			m_TaskQueueSignal.notify_one();
			THREAD_YIELD();
		}
	}

	INLINE void SlimTaskScheduler::WaitUntilAllTasksFinished()const noexcept
	{
		// Don't add more tasks nor change the amount of workers
		auto wkLck = SharedLock(m_TaskWorkersMutex);

		// Wait until no more tasks
		//auto lck = UniqueLock<decltype(m_TaskQueueMutex)>(m_TaskQueueMutex);
		while (!IsTaskQueueEmpty())
		{
			//m_TaskQueueSignal.wait(lck);
			m_TaskQueueSignal.notify_one();
			THREAD_YIELD();
		}
	}

	INLINE const String& SlimTaskScheduler::GetName() const noexcept { return m_Name; }

	INLINE bool SlimTaskScheduler::IsGrowthEnabled() const noexcept
	{
		auto lck = SharedLock(m_TaskWorkersMutex);
		return m_AllowGrowth;
	}

	INLINE void SlimTaskScheduler::EnableGrowth(bool enable) noexcept
	{
		LOCK(m_TaskWorkersMutex);
		m_AllowGrowth = enable;
	}

	INLINE void SlimTaskScheduler::OnNewManager(const PInterface& newInterface) noexcept
	{
		auto lck = SharedLock(m_TaskWorkersMutex);
		if (newInterface == nullptr || newInterface->GetInterfaceUUID() != IThreadManager::InterfaceUUID)
			return;

		m_ThreadManager = (WThreadManager)newInterface;
		m_OnManagerActivation.Disconnect(); // double check we are not connected
		newInterface->GetActivationEvent().Connect(m_OnManagerActivation, [this](bool active, IInterface* oldInterface, const PInterface& newInterface) { OnManagerActivation(active, oldInterface, newInterface); });
		m_OnNewManager.Disconnect();
	}

	INLINE void SlimTaskScheduler::OnManagerActivation(bool active, IInterface* oldInterface, const PInterface& newInterface) noexcept
	{
		auto lck = SharedLock(m_TaskWorkersMutex);
		if (active)
			return;

		// Change of ThreadManager
		if (newInterface != nullptr)
		{
			const auto& newThreadMgr = (const PThreadManager&)newInterface;
			m_OnManagerActivation.Disconnect();
			newThreadMgr->GetActivationEvent().Connect(m_OnManagerActivation, [this](bool active, IInterface* oldManager, const PInterface& newManager) { OnManagerActivation(active, oldManager, newManager); });
			m_ThreadManager = (WThreadManager)newThreadMgr;
		}
		// ThreadManager deactivated, wait until a new one is active
		else
		{
			m_OnManagerActivation.Disconnect();
			const auto& libW = oldInterface->GetLibrary();
			VerifyNot(libW.expired(), "Trying to connect to InterfaceActivationEvent but GreaperLibrary was expired.");
			auto lib = libW.lock();
			auto appW = lib->GetApplication();
			VerifyNot(appW.expired(), "Trying to connect to InterfaceActivationEvent but Application was expired.");
			auto app = appW.lock();
			m_OnNewManager.Disconnect(); // double check we are not connected
			app->GetOnInterfaceActivationEvent().Connect(m_OnNewManager, [this](const PInterface& newManager) { OnNewManager(newManager); });
		}
	}

	INLINE void SlimTaskScheduler::Stop() noexcept
	{
		SetWorkerCount(0);

		for (auto& task : m_TaskSlots)
		{
			if (task.State == SlimTask::READY && task.Task != nullptr)
				task.Task();

			task.Task = nullptr;
			task.State = SlimTask::DONE;
		}
		
		//for (auto* task : m_TaskQueue)
		//{
		//	(*task)();
		//	Destroy(task);
		//}
		//m_TaskQueue.clear();
		//for (auto* task : m_FreeTaskPool)
		//	Dealloc(task);
	}

	INLINE bool SlimTaskScheduler::AreThereAnyAvailableWorker() const noexcept
	{
		if (m_TaskWorkers.empty())
			return false; // There are no workers!

		for (auto& worker : m_TaskWorkers)
		{
			if (worker != nullptr)
				return true; // An active worker found!
		}
		return false; // There is no active worker
	}

	INLINE SlimTaskScheduler::SlimTaskScheduler(WThreadManager threadMgr, StringView name, sizet workerCount, bool allowGrowth)noexcept
		:m_ThreadManager(std::move(threadMgr))
		,m_Name(name)
		,m_This(this, &Impl::EmptyDeleter<SlimTaskScheduler>)
		,m_AllowGrowth(true)
	{
		VerifyNot(m_ThreadManager.expired(), "Trying to initialize a SlimTaskScheduler, but an expired ThreadManager was given.");
		auto mgr = m_ThreadManager.lock();
		mgr->GetActivationEvent().Connect(m_OnManagerActivation, [this](bool active, IInterface* oldInterface, const PInterface& newInterface) { OnManagerActivation(active, oldInterface, newInterface); });

		SetWorkerCount(workerCount);
		m_AllowGrowth = allowGrowth;
	}

	INLINE bool SlimTaskScheduler::CanWorkerContinueWorking(sizet workerID)const noexcept
	{
		auto lck = SharedLock(m_TaskWorkersMutex);
		return m_TaskWorkers.size() > workerID && m_TaskWorkers[workerID] != nullptr;
	}

	INLINE void SlimTaskScheduler::WorkerFn(SlimTaskScheduler& scheduler, sizet id) noexcept
	{
		while (true)
		{
			uint32 prevHandledTask = 0;
			SlimTask* task;
			// Retrieve a task to do or check if we need to keep running
			{
				auto taskLck = UniqueLock<decltype(m_TaskQueueMutex)>(scheduler.m_TaskQueueMutex);
				bool canWork = scheduler.CanWorkerContinueWorking(id);
				
				uint32 queuedTaskID;
				// Wait for work or an stop request
				while (!scheduler.IsAnyTaskReady(queuedTaskID, prevHandledTask) && canWork)
				{
					scheduler.m_TaskQueueSignal.wait(taskLck);
					canWork = scheduler.CanWorkerContinueWorking(id);
				}

				// Stop working
				if (!canWork)
					break;

				// Retrieve one task
				//if (!scheduler.IsTaskQueueEmpty())
				//{
				//	task = scheduler.m_TaskQueue.front();
				//	scheduler.m_TaskQueue.pop_front();
				//}
				task = &scheduler.m_TaskSlots[queuedTaskID];
				task->State = SlimTask::SCHEDULED; // Avoid re-scheduling
				prevHandledTask = queuedTaskID;
			}

			// Do actual task work, and store the task memory on the free pool
			if (task != nullptr)
			{
				// Execute the task
				task->Task();
				scheduler.m_TaskQueueMutex.lock();
				task->State = SlimTask::DONE;
				task->Task = nullptr;
				scheduler.m_TaskQueueMutex.unlock();
				// all newly created tasks assume uninitialized memory so we need to call destructor now
				//task->~packaged_task();
				// Store the task on to the free task pool
				//{
				//	LOCK(scheduler.m_FreeTaskPoolMutex);
				//	scheduler.m_FreeTaskPool.push_back(task);
				//}

				task = nullptr;
				scheduler.m_TaskQueueSignal.notify_all();
			}
		}
	}
	
	INLINE bool SlimTaskScheduler::IsTaskQueueEmpty()const noexcept
	{
		LOCK(m_TaskQueueMutex);
		for(const auto& slot : m_TaskSlots)
		{
			if (slot.State != SlimTask::DONE && slot.Task != nullptr)
				return false;
		}
		return true;
	}

	INLINE bool SlimTaskScheduler::IsAnyTaskReady(uint32& queueTaskID, uint32 prevHandledTask)const noexcept
	{
#define SLOT_CHECK()\
const auto& slot = *it;\
if (slot.State == SlimTask::READY && slot.Task != nullptr) {\
	queueTaskID = static_cast<uint32>(std::distance(m_TaskSlots.begin(), it));\
	return true;}

		for (auto it = m_TaskSlots.begin() + prevHandledTask; it != m_TaskSlots.end(); ++it)
		{
			SLOT_CHECK();
		}

		for (auto it = m_TaskSlots.begin(); it != m_TaskSlots.begin() + prevHandledTask; ++it)
		{
			SLOT_CHECK();
		}

		return false;
	}

	INLINE bool SlimTaskScheduler::IsNextTaskAvailable()const noexcept
	{
		uint32 taskIdx = m_LastTaskSlotUsed + 1;
		if (taskIdx >= m_TaskSlots.size())
			taskIdx = 0;
		const auto& slot = m_TaskSlots[taskIdx];
		return slot.Task == nullptr && slot.State == SlimTask::DONE;
	}
}
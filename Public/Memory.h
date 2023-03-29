/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef GREAPER_CORE_MEMORY_H
#define GREAPER_CORE_MEMORY_H 1

#include <memory>
#include <functional>
#if PLT_LINUX
#include <iostream>
#endif

#include "Base/VerifyMacros.h"

#include "Allocators/BaseAllocator.h"
#include "Allocators/StdAllocator.h"

namespace greaper
{
	namespace Impl
	{
		void _LogBreak(const String& msg);
		void _TriggerBreak(const String& str);
		
		template<class T, class _Alloc_ = GenericAllocator>
		INLINE void DefaultDeleter(T* ptr)
		{
			Destroy<T, _Alloc_>(ptr);
		}
		template<class T>
		INLINE void EmptyDeleter(UNUSED T* ptr)
		{

		}
		template<class T, class _Alloc_ = GenericAllocator>
		INLINE void CStrucDeleter(T* ptr)
		{
			Dealloc<_Alloc_>(ptr);
		}
		template<class T>
		using SPtrDeleterFn_t = std::function<void(T*)>;
	}
}

#include "Base/Formatting.inl"
#include "Concurrency.h"

#include "Allocators/PoolAllocator.h"
#include "Result.h"

#include "Base/UPtr.h"
#include "Base/SPtr.h"
#include "Base/WPtr.h"

#include "Platform.h"

#include "Base/Span.h"

namespace greaper::Impl
{
	INLINE void _LogBreak(const String& str)
	{
		FILE* file = nullptr;
#if PLT_WINDOWS
		const auto res = fopen_s(&file, "ERROR.log", "w");
#elif PLT_LINUX
		uint32 res = 0;
		file = fopen("ERROR.log", "w");
#endif
		if(res == 0 && file != nullptr)
		{
			const auto written = fwrite(str.data(), sizeof(String::value_type), str.size(), file);
			if (written != str.size())
				DEBUG_OUTPUT("Couldn't write all ERROR.log contents.");

			fclose(file);
		}
	}
	
	INLINE void _TriggerBreak(const String& str)
	{
#if GREAPER_DEBUG_BREAK
		DialogChoice_t choice = DialogChoice_t::ABORT_RETRY_IGNORE;
#else
		DialogChoice_t choice = DialogChoice_t::OK;
#endif
		DialogButton_t retVal = greaper::OSPlatform::CreateMessageBox("Greaper Assertion"sv, StringView{ str }, choice, DialogIcon_t::ERROR);

		if (retVal == DialogButton_t::RETRY)
			TRIGGER_BREAKPOINT();
		else if(retVal == DialogButton_t::IGNORE)
			return;

#if GREAPER_DEBUG_BREAK
		TRIGGER_BREAKPOINT();
#endif
		_LogBreak(str);
		exit(EXIT_FAILURE);
	}
}

#include "Allocators/BaseAllocator.inl"
#include "Base/StdUtils.inl"

#endif /* GREAPER_CORE_MEMORY_H */
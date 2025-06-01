/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#include <unistd.h>
#include <dlfcn.h>
#include "../Base/BasePlatform.hpp"
#include "../Base/StringUtils.hpp"

namespace greaper
{
	class LnxPlatform
	{
	public:
		using LibraryHandle = void*;
		using FunctionPtr = void(*)();

		static void Sleep(uint32 millis) noexcept;
		
		static std::expected<LibraryHandle, String> LoadLibrary(StringView libraryName) noexcept;

		static std::expected<LibraryHandle, String> LoadLibrary(WStringView libraryName) noexcept;

		static std::expected<void, String> UnloadLibrary(LibraryHandle libraryHandle) noexcept;

		static std::expected<FunctionPtr, String> LoadFunction(LibraryHandle libraryHandle,
																StringView functionName) noexcept;
		
		template<class T>
		static std::expected<T*, String> LoadFunctionT(LibraryHandle libraryHandle,
														StringView functionName) noexcept;

		static OSType_t GetOSType() noexcept { return OSType_t::Linux; }
	};

	inline void LnxPlatform::Sleep(uint32 millis) noexcept
	{
		auto rtn = ::usleep(millis * 1000);
	}

    inline std::expected<LnxPlatform::LibraryHandle, String> LnxPlatform::LoadLibrary(StringView libraryName) noexcept
    {
		auto lib = ::dlopen(libraryName.data(), RTLD_LAZY | RTLD_LOCAL);
		if (lib != nullptr)
			return lib;
		return std::unexpected(std::format("Couldn't load the library '{}', error '{}'.", libraryName, dlerror()));
    }

    inline std::expected<LnxPlatform::LibraryHandle, String> LnxPlatform::LoadLibrary(WStringView libraryName) noexcept
    {
		return LoadLibrary(StringUtils::FromWIDE(libraryName));
    }

    inline std::expected<void, String> LnxPlatform::UnloadLibrary(LibraryHandle libraryHandle) noexcept
    {
		if(dlclose(libraryHandle) == 0)
			return {};
		return std::unexpected(std::format("Couldn't unload the library, error '{}'.", dlerror()));
    }

    inline std::expected<LnxPlatform::FunctionPtr, String> LnxPlatform::LoadFunction(LibraryHandle libraryHandle,
																					StringView functionName) noexcept
    {
		// Clear old error conditions
		dlerror();

		// obtain the procedure
		auto proc = dlsym(libraryHandle, functionName.data());

		// obtain the new error message
		auto error = dlerror();

		if(error == nullptr)
			return reinterpret_cast<FunctionPtr>(proc);
		return std::unexpected(std::format("Couldn't load the function '{}' from the library, error '{}'.",
											functionName, error));
    }
	
    template <class T>
    inline std::expected<T*, String> LnxPlatform::LoadFunctionT(LibraryHandle libraryHandle,
																StringView functionName) noexcept
    {
		auto ret = LoadFunction(libraryHandle, functionName);
		if (ret.has_value())
			return reinterpret_cast<T*>(ret.value());
		return std::unexpected(ret.error());
    }

    using OSPlatform = LnxPlatform;
}
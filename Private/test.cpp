/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#include "../Public/CorePrerequisites.hpp"
#include "../Public/OSPlatform.hpp"
#include <iostream>

static std::expected<void, greaper::String> TestLib() noexcept
{
	auto lib_ret = greaper::OSPlatform::LoadLibrary("mylib" GREAPER_DLLEXT);
	if (lib_ret)
	{
		auto fn_ret = greaper::OSPlatform::LoadFunction(lib_ret.value(), "myFn");
		if (fn_ret)
		{
			fn_ret.value()();
		}
		else
		{
			return std::unexpected(fn_ret.error());
		}

		auto cfn_ret = greaper::OSPlatform::LoadFunctionT<int(int)>(lib_ret.value(), "myOtherFn");
		if (cfn_ret)
		{
			auto ret = cfn_ret.value()(15);
		}
		else
		{
			return std::unexpected(cfn_ret.error());
		}
	}
	else
	{
		return std::unexpected(lib_ret.error());
	}
	return {};
}

int main()
{
	auto ret = TestLib();
	if (ret.has_value())
		std::cout << "TEST OK!" << std::endl;
	else
		std::cout << ret.error() << std::endl;
}
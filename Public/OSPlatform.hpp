/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_OS_PLATFORM_HPP
#define CORE_OS_PLATFORM_HPP 1

#include "CorePrerequisites.hpp"

#if PLT_WINDOWS
#include "Win/WinPlatform.hpp"
#elif PLT_LINUX
#include "Lnx/LnxPlatform.hpp"
#endif


#endif /* CORE_OS_PLATFORM_HPP */
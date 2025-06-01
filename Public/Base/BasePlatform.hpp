/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_BASE_PLATFORM_HPP
#define CORE_BASE_PLATFORM_HPP 1

#include "CorePrerequisites.hpp"

ENUMERATION(OSType, Windows, Linux);

ENUMERATION(DialogButton, OK, YES, NO, ABORT, RETRY, IGNORE, CANCEL);

ENUMERATION(DialogChoices, OK, OK_CANCEL, YES_NO, YES_NO_CANCEL, RETRY_CANCEL, ABORT_RETRY_IGNORE);

ENUMERATION(DialogIcon, QUESTION, INFO, WARNING, ERROR);

ENUMERATION(FDialogOption, DEFAULT, MULTISELECT, FORCE_SAVE);

#endif /* CORE_BASE_PLATFORM_HPP */
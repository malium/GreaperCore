/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_I_CONSOLE_H
#define CORE_I_CONSOLE_H 1

#include "../Memory.h"
#include "../Enumeration.h"
#include "../Event.h"
#include <future>

ENUMERATION(ConsoleType, VIRTUAL, EXTERNAL);

namespace greaper
{
    class IConsole
    {
    public:
        using ConsoleEvt_t = Event<const String&>;

        virtual ConsoleType_t GetConsoleType()const noexcept = 0;

        virtual void WriteToConsole(const String& msg)noexcept = 0;
        
        virtual std::future<String> ReadFromConsole()noexcept = 0;

        virtual ConsoleEvt_t* GetConsoleEvent()const noexcept = 0;

        virtual void SetCursorPosition(std::pair<int16, int16> position)noexcept = 0;

        virtual std::pair<int16, int16> GetCursorPosition()noexcept = 0;
    };
}

#endif /* CORE_I_CONSOLE_H */
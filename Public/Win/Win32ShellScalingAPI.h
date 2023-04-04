/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_WIN32_SHELL_SCALLING_API_H
#define CORE_WIN32_SHELL_SCALLING_API_H 1

#include "Win32Base.h"

#if WIN32_USE_GREAPER_HEADERS

extern "C" {

typedef /* [v1_enum] */
    enum DEVICE_SCALE_FACTOR
{
    DEVICE_SCALE_FACTOR_INVALID = 0,
    SCALE_100_PERCENT = 100,
    SCALE_120_PERCENT = 120,
    SCALE_125_PERCENT = 125,
    SCALE_140_PERCENT = 140,
    SCALE_150_PERCENT = 150,
    SCALE_160_PERCENT = 160,
    SCALE_175_PERCENT = 175,
    SCALE_180_PERCENT = 180,
    SCALE_200_PERCENT = 200,
    SCALE_225_PERCENT = 225,
    SCALE_250_PERCENT = 250,
    SCALE_300_PERCENT = 300,
    SCALE_350_PERCENT = 350,
    SCALE_400_PERCENT = 400,
    SCALE_450_PERCENT = 450,
    SCALE_500_PERCENT = 500
} 	DEVICE_SCALE_FACTOR;

#ifndef STDAPI
#define STDAPI                  EXTERN_C HRESULT STDAPICALLTYPE
#define STDAPI_(type)           EXTERN_C type STDAPICALLTYPE
#endif

typedef enum
{
    DEVICE_PRIMARY = 0,
    DEVICE_IMMERSIVE = 1,
} DISPLAY_DEVICE_TYPE;

typedef enum
{
    SCF_VALUE_NONE = 0x00,
    SCF_SCALE = 0x01,
    SCF_PHYSICAL = 0x02,
} SCALE_CHANGE_FLAGS;

#if (NTDDI_VERSION >= NTDDI_WIN8)

// Given a display device, return the preferred DEVICE_SCALE_FACTOR to be used for scaling values.
// Default is SCALE_100_PERCENT
STDAPI_(DEVICE_SCALE_FACTOR) GetScaleFactorForDevice(DISPLAY_DEVICE_TYPE deviceType);

// Register a window to receive callbacks when scaling information changes.  The uMsgNotify param specifies a message
// that will be posted to the requesting window.  The wParam for this message is a combination of SCALE_CHANGE_FLAGS
STDAPI RegisterScaleChangeNotifications(DISPLAY_DEVICE_TYPE displayDevice, HWND hwndNotify, UINT uMsgNotify, DWORD* pdwCookie);
STDAPI RevokeScaleChangeNotifications(DISPLAY_DEVICE_TYPE displayDevice, DWORD dwCookie);

#endif // (NTDDI_VERSION >= NTDDI_WIN8)

}

#else
#include <ShellScalingApi.h>
#pragma comment(lib, "Shcore.lib")
#endif

#endif /* CORE_WIN32_SHELL_SCALLING_API_H */
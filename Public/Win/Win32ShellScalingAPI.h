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

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C    extern "C"
#else
#define EXTERN_C    extern
#endif
#endif

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

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
STDAPI GetScaleFactorForMonitor(_In_ HMONITOR hMon, _Out_ DEVICE_SCALE_FACTOR* pScale);
STDAPI RegisterScaleChangeEvent(_In_ HANDLE hEvent, _Out_ DWORD_PTR* pdwCookie);
STDAPI UnregisterScaleChangeEvent(_In_ DWORD_PTR dwCookie);

#endif // (NTDDI_VERSION >= NTDDI_WINBLUE)

#ifndef DPI_ENUMS_DECLARED

typedef enum PROCESS_DPI_AWARENESS {
	PROCESS_DPI_UNAWARE = 0,
	PROCESS_SYSTEM_DPI_AWARE = 1,
	PROCESS_PER_MONITOR_DPI_AWARE = 2
} PROCESS_DPI_AWARENESS;

typedef enum MONITOR_DPI_TYPE {
	MDT_EFFECTIVE_DPI = 0,
	MDT_ANGULAR_DPI = 1,
	MDT_RAW_DPI = 2,
	MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;

#define DPI_ENUMS_DECLARED
#endif // (DPI_ENUMS_DECLARED)

#if (NTDDI_VERSION >= NTDDI_WINBLUE)

STDAPI SetProcessDpiAwareness(
	_In_ PROCESS_DPI_AWARENESS value);

STDAPI GetProcessDpiAwareness(
	_In_opt_ HANDLE hprocess,
	_Out_ PROCESS_DPI_AWARENESS* value);

STDAPI GetDpiForMonitor(
	_In_ HMONITOR hmonitor,
	_In_ MONITOR_DPI_TYPE dpiType,
	_Out_ UINT* dpiX,
	_Out_ UINT* dpiY);

#endif // (NTDDI_VERSION >= NTDDI_WINBLUE)

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

#ifndef SHELL_UI_COMPONENT_ENUMS_DECLARED

typedef enum
{
	SHELL_UI_COMPONENT_TASKBARS = 0,
	SHELL_UI_COMPONENT_NOTIFICATIONAREA = 1,
	SHELL_UI_COMPONENT_DESKBAND = 2,
} SHELL_UI_COMPONENT;

#define SHELL_UI_COMPONENT_ENUMS_DECLARED
#endif // (SHELL_UI_COMPONENT_ENUMS_DECLARED)

STDAPI_(UINT) GetDpiForShellUIComponent(
	_In_ SHELL_UI_COMPONENT);

#endif // (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

}

#else
#include <ShellScalingApi.h>
#pragma comment(lib, "Shcore.lib")
#endif

#endif /* CORE_WIN32_SHELL_SCALLING_API_H */
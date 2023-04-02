/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_WIN32_GDI_H
#define CORE_WIN32_GDI_H 1

#include "Win32Base.h"

#if WIN32_USE_GREAPER_HEADERS

#define WINGDIAPI DECLSPEC_IMPORT

extern "C" {
typedef struct _POINTFLOAT {
    FLOAT   x;
    FLOAT   y;
} POINTFLOAT, * PPOINTFLOAT;

/* Pixel format descriptor */
typedef struct tagPIXELFORMATDESCRIPTOR
{
    WORD  nSize;
    WORD  nVersion;
    DWORD dwFlags;
    BYTE  iPixelType;
    BYTE  cColorBits;
    BYTE  cRedBits;
    BYTE  cRedShift;
    BYTE  cGreenBits;
    BYTE  cGreenShift;
    BYTE  cBlueBits;
    BYTE  cBlueShift;
    BYTE  cAlphaBits;
    BYTE  cAlphaShift;
    BYTE  cAccumBits;
    BYTE  cAccumRedBits;
    BYTE  cAccumGreenBits;
    BYTE  cAccumBlueBits;
    BYTE  cAccumAlphaBits;
    BYTE  cDepthBits;
    BYTE  cStencilBits;
    BYTE  cAuxBuffers;
    BYTE  iLayerType;
    BYTE  bReserved;
    DWORD dwLayerMask;
    DWORD dwVisibleMask;
    DWORD dwDamageMask;
} PIXELFORMATDESCRIPTOR, * PPIXELFORMATDESCRIPTOR, FAR* LPPIXELFORMATDESCRIPTOR;

/* Layer plane descriptor */
typedef struct tagLAYERPLANEDESCRIPTOR { // lpd
    WORD  nSize;
    WORD  nVersion;
    DWORD dwFlags;
    BYTE  iPixelType;
    BYTE  cColorBits;
    BYTE  cRedBits;
    BYTE  cRedShift;
    BYTE  cGreenBits;
    BYTE  cGreenShift;
    BYTE  cBlueBits;
    BYTE  cBlueShift;
    BYTE  cAlphaBits;
    BYTE  cAlphaShift;
    BYTE  cAccumBits;
    BYTE  cAccumRedBits;
    BYTE  cAccumGreenBits;
    BYTE  cAccumBlueBits;
    BYTE  cAccumAlphaBits;
    BYTE  cDepthBits;
    BYTE  cStencilBits;
    BYTE  cAuxBuffers;
    BYTE  iLayerPlane;
    BYTE  bReserved;
    COLORREF crTransparent;
} LAYERPLANEDESCRIPTOR, * PLAYERPLANEDESCRIPTOR, FAR* LPLAYERPLANEDESCRIPTOR;

typedef struct _GLYPHMETRICSFLOAT {
    FLOAT       gmfBlackBoxX;
    FLOAT       gmfBlackBoxY;
    POINTFLOAT  gmfptGlyphOrigin;
    FLOAT       gmfCellIncX;
    FLOAT       gmfCellIncY;
} GLYPHMETRICSFLOAT, * PGLYPHMETRICSFLOAT, FAR* LPGLYPHMETRICSFLOAT;

WINGDIAPI BOOL  WINAPI SwapBuffers(HDC);

typedef struct _DISPLAY_DEVICEA {
    DWORD  cb;
    CHAR   DeviceName[32];
    CHAR   DeviceString[128];
    DWORD  StateFlags;
    CHAR   DeviceID[128];
    CHAR   DeviceKey[128];
} DISPLAY_DEVICEA, * PDISPLAY_DEVICEA, * LPDISPLAY_DEVICEA;
typedef struct _DISPLAY_DEVICEW {
    DWORD  cb;
    WCHAR  DeviceName[32];
    WCHAR  DeviceString[128];
    DWORD  StateFlags;
    WCHAR  DeviceID[128];
    WCHAR  DeviceKey[128];
} DISPLAY_DEVICEW, * PDISPLAY_DEVICEW, * LPDISPLAY_DEVICEW;

#define DISPLAY_DEVICE_ATTACHED_TO_DESKTOP      0x00000001
#define DISPLAY_DEVICE_MULTI_DRIVER             0x00000002
#define DISPLAY_DEVICE_PRIMARY_DEVICE           0x00000004
#define DISPLAY_DEVICE_MIRRORING_DRIVER         0x00000008
#define DISPLAY_DEVICE_VGA_COMPATIBLE           0x00000010
#define DISPLAY_DEVICE_REMOVABLE                0x00000020
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
#define DISPLAY_DEVICE_ACC_DRIVER               0x00000040
#endif
#define DISPLAY_DEVICE_MODESPRUNED              0x08000000
#define DISPLAY_DEVICE_RDPUDD                   0x01000000
#define DISPLAY_DEVICE_REMOTE                   0x04000000
#define DISPLAY_DEVICE_DISCONNECT               0x02000000
#define DISPLAY_DEVICE_TS_COMPATIBLE            0x00200000
#define DISPLAY_DEVICE_UNSAFE_MODES_ON          0x00080000

/* Child device state */
#define DISPLAY_DEVICE_ACTIVE              0x00000001
#define DISPLAY_DEVICE_ATTACHED            0x00000002

#ifndef CCHDEVICENAME
#define CCHDEVICENAME 32
#endif

#ifndef CCHFORMNAME
#define CCHFORMNAME 32
#endif

typedef struct _devicemodeA {
    BYTE   dmDeviceName[CCHDEVICENAME];
    WORD dmSpecVersion;
    WORD dmDriverVersion;
    WORD dmSize;
    WORD dmDriverExtra;
    DWORD dmFields;
    union {
        /* printer only fields */
        struct {
            short dmOrientation;
            short dmPaperSize;
            short dmPaperLength;
            short dmPaperWidth;
            short dmScale;
            short dmCopies;
            short dmDefaultSource;
            short dmPrintQuality;
        } ;
        /* display only fields */
        struct {
            POINTL dmPosition;
            DWORD  dmDisplayOrientation;
            DWORD  dmDisplayFixedOutput;
        } ;
    } ;
    short dmColor;
    short dmDuplex;
    short dmYResolution;
    short dmTTOption;
    short dmCollate;
    BYTE   dmFormName[CCHFORMNAME];
    WORD   dmLogPixels;
    DWORD  dmBitsPerPel;
    DWORD  dmPelsWidth;
    DWORD  dmPelsHeight;
    union {
        DWORD  dmDisplayFlags;
        DWORD  dmNup;
    } ;
    DWORD  dmDisplayFrequency;
    DWORD  dmICMMethod;
    DWORD  dmICMIntent;
    DWORD  dmMediaType;
    DWORD  dmDitherType;
    DWORD  dmReserved1;
    DWORD  dmReserved2;
    DWORD  dmPanningWidth;
    DWORD  dmPanningHeight;
} DEVMODEA, * PDEVMODEA, * NPDEVMODEA, * LPDEVMODEA;

typedef struct _devicemodeW {
    WCHAR  dmDeviceName[CCHDEVICENAME];
    WORD dmSpecVersion;
    WORD dmDriverVersion;
    WORD dmSize;
    WORD dmDriverExtra;
    DWORD dmFields;
    union {
        /* printer only fields */
        struct {
            short dmOrientation;
            short dmPaperSize;
            short dmPaperLength;
            short dmPaperWidth;
            short dmScale;
            short dmCopies;
            short dmDefaultSource;
            short dmPrintQuality;
        } ;
        /* display only fields */
        struct {
            POINTL dmPosition;
            DWORD  dmDisplayOrientation;
            DWORD  dmDisplayFixedOutput;
        } ;
    } ;
    short dmColor;
    short dmDuplex;
    short dmYResolution;
    short dmTTOption;
    short dmCollate;
    WCHAR  dmFormName[CCHFORMNAME];
    WORD   dmLogPixels;
    DWORD  dmBitsPerPel;
    DWORD  dmPelsWidth;
    DWORD  dmPelsHeight;
    union {
        DWORD  dmDisplayFlags;
        DWORD  dmNup;
    } ;
    DWORD  dmDisplayFrequency;
    DWORD  dmICMMethod;
    DWORD  dmICMIntent;
    DWORD  dmMediaType;
    DWORD  dmDitherType;
    DWORD  dmReserved1;
    DWORD  dmReserved2;
    DWORD  dmPanningWidth;
    DWORD  dmPanningHeight;
} DEVMODEW, * PDEVMODEW, * NPDEVMODEW, * LPDEVMODEW;

}

#else
#include <wingdi.h>
#endif

#endif /* CORE_WIN32_GDI_H */
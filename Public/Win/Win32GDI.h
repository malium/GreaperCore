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
}

#else
#include <wingdi.h>
#endif

#endif /* CORE_WIN32_GDI_H */
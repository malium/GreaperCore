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

#if COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 4201)
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
#if COMPILER_MSVC
#pragma warning(pop)
#endif

/* Device Parameters for GetDeviceCaps() */
#define DRIVERVERSION 0     /* Device driver version                    */
#define TECHNOLOGY    2     /* Device classification                    */
#define HORZSIZE      4     /* Horizontal size in millimeters           */
#define VERTSIZE      6     /* Vertical size in millimeters             */
#define HORZRES       8     /* Horizontal width in pixels               */
#define VERTRES       10    /* Vertical height in pixels                */
#define BITSPIXEL     12    /* Number of bits per pixel                 */
#define PLANES        14    /* Number of planes                         */
#define NUMBRUSHES    16    /* Number of brushes the device has         */
#define NUMPENS       18    /* Number of pens the device has            */
#define NUMMARKERS    20    /* Number of markers the device has         */
#define NUMFONTS      22    /* Number of fonts the device has           */
#define NUMCOLORS     24    /* Number of colors the device supports     */
#define PDEVICESIZE   26    /* Size required for device descriptor      */
#define CURVECAPS     28    /* Curve capabilities                       */
#define LINECAPS      30    /* Line capabilities                        */
#define POLYGONALCAPS 32    /* Polygonal capabilities                   */
#define TEXTCAPS      34    /* Text capabilities                        */
#define CLIPCAPS      36    /* Clipping capabilities                    */
#define RASTERCAPS    38    /* Bitblt capabilities                      */
#define ASPECTX       40    /* Length of the X leg                      */
#define ASPECTY       42    /* Length of the Y leg                      */
#define ASPECTXY      44    /* Length of the hypotenuse                 */

#define LOGPIXELSX    88    /* Logical pixels/inch in X                 */
#define LOGPIXELSY    90    /* Logical pixels/inch in Y                 */

#define SIZEPALETTE  104    /* Number of entries in physical palette    */
#define NUMRESERVED  106    /* Number of reserved entries in palette    */
#define COLORRES     108    /* Actual color resolution                  */

// Printing related DeviceCaps. These replace the appropriate Escapes

#define PHYSICALWIDTH   110 /* Physical Width in device units           */
#define PHYSICALHEIGHT  111 /* Physical Height in device units          */
#define PHYSICALOFFSETX 112 /* Physical Printable Area x margin         */
#define PHYSICALOFFSETY 113 /* Physical Printable Area y margin         */
#define SCALINGFACTORX  114 /* Scaling factor x                         */
#define SCALINGFACTORY  115 /* Scaling factor y                         */

// Display driver specific

#define VREFRESH        116  /* Current vertical refresh rate of the    */
							 /* display device (for displays only) in Hz*/
#define DESKTOPVERTRES  117  /* Horizontal width of entire desktop in   */
							 /* pixels                                  */
#define DESKTOPHORZRES  118  /* Vertical height of entire desktop in    */
							 /* pixels                                  */
#define BLTALIGNMENT    119  /* Preferred blt alignment                 */

#define SHADEBLENDCAPS  120  /* Shading and blending caps               */
#define COLORMGMTCAPS   121  /* Color Management caps                   */

WINGDIAPI int WINAPI GetDeviceCaps(HDC hdc, int index);

}

#else
#include <wingdi.h>
#endif

#pragma comment(lib, "Gdi32.lib")

#endif /* CORE_WIN32_GDI_H */
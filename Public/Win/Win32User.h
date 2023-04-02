/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#ifndef CORE_WIN32_USER_H
#define CORE_WIN32_USER_H 1

#include "Win32Base.h"

#if WIN32_USE_GREAPER_HEADERS

extern "C" {

#define WINUSERAPI DECLSPEC_IMPORT
#define HWND_TOP        ((HWND)0)
#define HWND_BOTTOM     ((HWND)1)
#define HWND_TOPMOST    ((HWND)-1)
#define HWND_NOTOPMOST  ((HWND)-2)

#define WS_OVERLAPPED 0x00000000L
#define WS_POPUP 0x80000000L
#define WS_CHILD 0x40000000L
#define WS_MINIMIZE 0x20000000L
#define WS_VISIBLE 0x10000000L
#define WS_DISABLED 0x08000000L
#define WS_CLIPSIBLINGS 0x04000000L
#define WS_CLIPCHILDREN 0x02000000L
#define WS_MAXIMIZE 0x01000000L
#define WS_CAPTION 0x00C00000L
#define WS_BORDER 0x00800000L
#define WS_DLGFRAME 0x00400000L
#define WS_VSCROLL 0x00200000L
#define WS_HSCROLL 0x00100000L
#define WS_SYSMENU 0x00080000L
#define WS_THICKFRAME 0x00040000L
#define WS_GROUP 0x00020000L
#define WS_TABSTOP 0x00010000L

#define WS_MINIMIZEBOX 0x00020000L
#define WS_MAXIMIZEBOX 0x00010000L

#define WS_TILED WS_OVERLAPPED
#define WS_ICONIC WS_MINIMIZE
#define WS_SIZEBOX WS_THICKFRAME
#define WS_TILEDWINDOW WS_OVERLAPPEDWINDOW

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

#define WS_POPUPWINDOW (WS_POPUP | WS_BORDER | WS_SYSMENU)

#define WS_CHILDWINDOW (WS_CHILD)

#define WS_EX_DLGMODALFRAME 0x00000001L
#define WS_EX_NOPARENTNOTIFY 0x00000004L
#define WS_EX_TOPMOST 0x00000008L
#define WS_EX_ACCEPTFILES 0x00000010L
#define WS_EX_TRANSPARENT 0x00000020L
#define WS_EX_MDICHILD 0x00000040L
#define WS_EX_TOOLWINDOW 0x00000080L
#define WS_EX_WINDOWEDGE 0x00000100L
#define WS_EX_CLIENTEDGE 0x00000200L
#define WS_EX_CONTEXTHELP 0x00000400L
#define WS_EX_RIGHT 0x00001000L
#define WS_EX_LEFT 0x00000000L
#define WS_EX_RTLREADING 0x00002000L
#define WS_EX_LTRREADING 0x00000000L
#define WS_EX_LEFTSCROLLBAR 0x00004000L
#define WS_EX_RIGHTSCROLLBAR 0x00000000L

#define WS_EX_CONTROLPARENT 0x00010000L
#define WS_EX_STATICEDGE 0x00020000L
#define WS_EX_APPWINDOW 0x00040000L

#define WS_EX_OVERLAPPEDWINDOW (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)
#define WS_EX_LAYERED 0x00080000
#define WS_EX_NOINHERITLAYOUT 0x00100000L
#define WS_EX_LAYOUTRTL 0x00400000L
#define WS_EX_COMPOSITED 0x02000000L
#define WS_EX_NOACTIVATE 0x08000000L

#define CS_VREDRAW 0x0001
#define CS_HREDRAW 0x0002
#define CS_DBLCLKS 0x0008
#define CS_OWNDC 0x0020
#define CS_CLASSDC 0x0040
#define CS_PARENTDC 0x0080
#define CS_NOCLOSE 0x0200
#define CS_SAVEBITS 0x0800
#define CS_BYTEALIGNCLIENT 0x1000
#define CS_BYTEALIGNWINDOW 0x2000
#define CS_GLOBALCLASS 0x4000
#define CS_IME 0x00010000
#define CS_DROPSHADOW 0x00020000

typedef struct tagHELPINFO      /* Structure pointed to by lParam of WM_HELP */
{
	UINT    cbSize;             /* Size in bytes of this struct  */
	int     iContextType;       /* Either HELPINFO_WINDOW or HELPINFO_MENUITEM */
	int     iCtrlId;            /* Control Id or a Menu item Id. */
	HANDLE  hItemHandle;        /* hWnd of control or hMenu.     */
	DWORD_PTR dwContextId;      /* Context Id associated with this item */
	POINT   MousePos;           /* Mouse Position in screen co-ordinates */
}  HELPINFO, FAR* LPHELPINFO;

typedef VOID(CALLBACK* MSGBOXCALLBACK)(LPHELPINFO lpHelpInfo);

typedef struct tagMSGBOXPARAMSA
{
	UINT        cbSize;
	HWND        hwndOwner;
	HINSTANCE   hInstance;
	LPCSTR      lpszText;
	LPCSTR      lpszCaption;
	DWORD       dwStyle;
	LPCSTR      lpszIcon;
	DWORD_PTR   dwContextHelpId;
	MSGBOXCALLBACK      lpfnMsgBoxCallback;
	DWORD       dwLanguageId;
} MSGBOXPARAMSA, * PMSGBOXPARAMSA, * LPMSGBOXPARAMSA;
typedef struct tagMSGBOXPARAMSW
{
	UINT        cbSize;
	HWND        hwndOwner;
	HINSTANCE   hInstance;
	LPCWSTR     lpszText;
	LPCWSTR     lpszCaption;
	DWORD       dwStyle;
	LPCWSTR     lpszIcon;
	DWORD_PTR   dwContextHelpId;
	MSGBOXCALLBACK      lpfnMsgBoxCallback;
	DWORD       dwLanguageId;
} MSGBOXPARAMSW, * PMSGBOXPARAMSW, * LPMSGBOXPARAMSW;

WINUSERAPI
int
WINAPI
MessageBoxA(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType);

WINUSERAPI
int
WINAPI
MessageBoxW(
	HWND hWnd,
	LPCWSTR lpText,
	LPCWSTR lpCaption,
	UINT uType);

WINUSERAPI
int
WINAPI
MessageBoxIndirectA(
	CONST MSGBOXPARAMSA* lpmbp);

WINUSERAPI
int
WINAPI
MessageBoxIndirectW(
	CONST MSGBOXPARAMSW* lpmbp);

WINUSERAPI
BOOL
WINAPI
SetWindowContextHelpId(
	HWND,
	DWORD);

WINUSERAPI
DWORD
WINAPI
GetWindowContextHelpId(
	HWND);

WINUSERAPI
BOOL
WINAPI
SetMenuContextHelpId(
	HMENU,
	DWORD);

WINUSERAPI
DWORD
WINAPI
GetMenuContextHelpId(
	HMENU);

WINUSERAPI
BOOL
WINAPI
PeekMessageA(
	LPMSG lpMsg,
	HWND hWnd,
	UINT wMsgFilterMin,
	UINT wMsgFilterMax,
	UINT wRemoveMsg);

WINUSERAPI
BOOL
WINAPI
PeekMessageW(
	LPMSG lpMsg,
	HWND hWnd,
	UINT wMsgFilterMin,
	UINT wMsgFilterMax,
	UINT wRemoveMsg);

#define PM_NOREMOVE         0x0000
#define PM_REMOVE           0x0001
#define PM_NOYIELD          0x0002

WINUSERAPI
DWORD
WINAPI
MsgWaitForMultipleObjects(
	DWORD nCount,
	CONST HANDLE* pHandles,
	BOOL fWaitAll,
	DWORD dwMilliseconds,
	DWORD dwWakeMask);

WINUSERAPI
DWORD
WINAPI
MsgWaitForMultipleObjectsEx(
	DWORD nCount,
	CONST HANDLE* pHandles,
	DWORD dwMilliseconds,
	DWORD dwWakeMask,
	DWORD dwFlags);

WINUSERAPI
BOOL
WINAPI
TranslateMessage(
	CONST MSG* lpMsg);

WINUSERAPI
LRESULT
WINAPI
DispatchMessageA(
	CONST MSG* lpMsg);

WINUSERAPI
LRESULT
WINAPI
DispatchMessageW(
	CONST MSG* lpMsg);

WINUSERAPI
HWND
WINAPI
CreateWindowExA(
	DWORD dwExStyle,
	LPCSTR lpClassName,
	LPCSTR lpWindowName,
	DWORD dwStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam);

WINUSERAPI
HWND
WINAPI
CreateWindowExW(
	DWORD dwExStyle,
	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam);

WINUSERAPI
BOOL
WINAPI
IsWindow(
	HWND hWnd);


WINUSERAPI
BOOL
WINAPI
IsMenu(
	HMENU hMenu);

WINUSERAPI
BOOL
WINAPI
IsChild(
	HWND hWndParent,
	HWND hWnd);


WINUSERAPI
BOOL
WINAPI
DestroyWindow(
	HWND hWnd);

WINUSERAPI
BOOL
WINAPI
ShowWindow(
	HWND hWnd,
	int nCmdShow);

WINUSERAPI
BOOL
WINAPI
ShowWindowAsync(
	HWND hWnd,
	int nCmdShow);

WINUSERAPI
BOOL
WINAPI
FlashWindow(
	HWND hWnd,
	BOOL bInvert);

typedef struct {
	UINT  cbSize;
	HWND  hwnd;
	DWORD dwFlags;
	UINT  uCount;
	DWORD dwTimeout;
} FLASHWINFO, * PFLASHWINFO;

WINUSERAPI
BOOL
WINAPI
FlashWindowEx(
	PFLASHWINFO pfwi);

#define FLASHW_STOP         0
#define FLASHW_CAPTION      0x00000001
#define FLASHW_TRAY         0x00000002
#define FLASHW_ALL          (FLASHW_CAPTION | FLASHW_TRAY)
#define FLASHW_TIMER        0x00000004
#define FLASHW_TIMERNOFG    0x0000000C

WINUSERAPI
BOOL
WINAPI
CloseWindow(
	HWND hWnd);

WINUSERAPI
BOOL
WINAPI
MoveWindow(
	HWND hWnd,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	BOOL bRepaint);

WINUSERAPI
BOOL
WINAPI
SetWindowPos(
	HWND hWnd,
	HWND hWndInsertAfter,
	int X,
	int Y,
	int cx,
	int cy,
	UINT uFlags);

#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send WM_NCCALCSIZE */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send WM_WINDOWPOSCHANGING */

#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER

#define SWP_DEFERERASE      0x2000
#define SWP_ASYNCWINDOWPOS  0x4000

typedef struct tagWINDOWPLACEMENT {
	UINT  length;
	UINT  flags;
	UINT  showCmd;
	POINT ptMinPosition;
	POINT ptMaxPosition;
	RECT  rcNormalPosition;
} WINDOWPLACEMENT;
typedef WINDOWPLACEMENT* PWINDOWPLACEMENT, * LPWINDOWPLACEMENT;

WINUSERAPI
BOOL
WINAPI
GetWindowPlacement(
	HWND hWnd,
	WINDOWPLACEMENT* lpwndpl);

WINUSERAPI
BOOL
WINAPI
SetWindowPlacement(
	HWND hWnd,
	CONST WINDOWPLACEMENT* lpwndpl);

WINUSERAPI
BOOL
WINAPI
IsWindowVisible(
	HWND hWnd);

WINUSERAPI
BOOL
WINAPI
IsIconic(
	HWND hWnd);

WINUSERAPI
BOOL
WINAPI
BringWindowToTop(
	HWND hWnd);

WINUSERAPI
HWND
WINAPI
SetFocus(
	HWND hWnd);

WINUSERAPI
HWND
WINAPI
GetActiveWindow(
	VOID);

WINUSERAPI
HWND
WINAPI
GetFocus(
	VOID);

WINUSERAPI
HWND
WINAPI
GetCapture(
	VOID);

WINUSERAPI
HWND
WINAPI
SetCapture(
	HWND hWnd);

WINUSERAPI
BOOL
WINAPI
ReleaseCapture(
	VOID);

WINUSERAPI
BOOL
WINAPI
EnableWindow(
	HWND hWnd,
	BOOL bEnable);

WINUSERAPI
BOOL
WINAPI
IsWindowEnabled(
	HWND hWnd);

/*
 * Clipboard Manager Functions
 */
WINUSERAPI
BOOL
WINAPI
OpenClipboard(
	HWND hWndNewOwner);

WINUSERAPI
BOOL
WINAPI
CloseClipboard(
	VOID);

WINUSERAPI
DWORD
WINAPI
GetClipboardSequenceNumber(
	VOID);

WINUSERAPI
HWND
WINAPI
GetClipboardOwner(
	VOID);

WINUSERAPI
HWND
WINAPI
SetClipboardViewer(
	HWND hWndNewViewer);

WINUSERAPI
HWND
WINAPI
GetClipboardViewer(
	VOID);

WINUSERAPI
BOOL
WINAPI
ChangeClipboardChain(
	HWND hWndRemove,
	HWND hWndNewNext);

WINUSERAPI
HANDLE
WINAPI
SetClipboardData(
	UINT uFormat,
	HANDLE hMem);

WINUSERAPI
HANDLE
WINAPI
GetClipboardData(
	UINT uFormat);

WINUSERAPI
UINT
WINAPI
RegisterClipboardFormatA(
	LPCSTR lpszFormat);

WINUSERAPI
UINT
WINAPI
RegisterClipboardFormatW(
	LPCWSTR lpszFormat);

WINUSERAPI
int
WINAPI
CountClipboardFormats(
	VOID);

WINUSERAPI
UINT
WINAPI
EnumClipboardFormats(
	UINT format);

WINUSERAPI
int
WINAPI
GetClipboardFormatNameA(
	UINT format,
	LPSTR lpszFormatName,
	int cchMaxCount);

WINUSERAPI
int
WINAPI
GetClipboardFormatNameW(
	UINT format,
	LPWSTR lpszFormatName,
	int cchMaxCount);

WINUSERAPI
BOOL
WINAPI
EmptyClipboard(
	VOID);

WINUSERAPI
BOOL
WINAPI
IsClipboardFormatAvailable(
	UINT format);

WINUSERAPI
int
WINAPI
GetPriorityClipboardFormat(
	UINT* paFormatPriorityList,
	int cFormats);

WINUSERAPI
HWND
WINAPI
GetOpenClipboardWindow(
	VOID);

WINUSERAPI
BOOL
WINAPI
AddClipboardFormatListener(
	HWND hwnd);

WINUSERAPI
BOOL
WINAPI
RemoveClipboardFormatListener(
	HWND hwnd);

WINUSERAPI
BOOL
WINAPI
GetUpdatedClipboardFormats(
	PUINT lpuiFormats,
	UINT cFormats,
	PUINT pcFormatsOut);



/*
 * GetSystemMetrics()
 */

#define SM_CXSCREEN             0
#define SM_CYSCREEN             1
#define SM_CXVSCROLL            2
#define SM_CYHSCROLL            3
#define SM_CYCAPTION            4
#define SM_CXBORDER             5
#define SM_CYBORDER             6
#define SM_CXDLGFRAME           7
#define SM_CYDLGFRAME           8
#define SM_CYVTHUMB             9
#define SM_CXHTHUMB             10
#define SM_CXICON               11
#define SM_CYICON               12
#define SM_CXCURSOR             13
#define SM_CYCURSOR             14
#define SM_CYMENU               15
#define SM_CXFULLSCREEN         16
#define SM_CYFULLSCREEN         17
#define SM_CYKANJIWINDOW        18
#define SM_MOUSEPRESENT         19
#define SM_CYVSCROLL            20
#define SM_CXHSCROLL            21
#define SM_DEBUG                22
#define SM_SWAPBUTTON           23
#define SM_RESERVED1            24
#define SM_RESERVED2            25
#define SM_RESERVED3            26
#define SM_RESERVED4            27
#define SM_CXMIN                28
#define SM_CYMIN                29
#define SM_CXSIZE               30
#define SM_CYSIZE               31
#define SM_CXFRAME              32
#define SM_CYFRAME              33
#define SM_CXMINTRACK           34
#define SM_CYMINTRACK           35
#define SM_CXDOUBLECLK          36
#define SM_CYDOUBLECLK          37
#define SM_CXICONSPACING        38
#define SM_CYICONSPACING        39
#define SM_MENUDROPALIGNMENT    40
#define SM_PENWINDOWS           41
#define SM_DBCSENABLED          42
#define SM_CMOUSEBUTTONS        43

#define SM_CXFIXEDFRAME           SM_CXDLGFRAME  /* ;win40 name change */
#define SM_CYFIXEDFRAME           SM_CYDLGFRAME  /* ;win40 name change */
#define SM_CXSIZEFRAME            SM_CXFRAME     /* ;win40 name change */
#define SM_CYSIZEFRAME            SM_CYFRAME     /* ;win40 name change */

#define SM_SECURE               44
#define SM_CXEDGE               45
#define SM_CYEDGE               46
#define SM_CXMINSPACING         47
#define SM_CYMINSPACING         48
#define SM_CXSMICON             49
#define SM_CYSMICON             50
#define SM_CYSMCAPTION          51
#define SM_CXSMSIZE             52
#define SM_CYSMSIZE             53
#define SM_CXMENUSIZE           54
#define SM_CYMENUSIZE           55
#define SM_ARRANGE              56
#define SM_CXMINIMIZED          57
#define SM_CYMINIMIZED          58
#define SM_CXMAXTRACK           59
#define SM_CYMAXTRACK           60
#define SM_CXMAXIMIZED          61
#define SM_CYMAXIMIZED          62
#define SM_NETWORK              63
#define SM_CLEANBOOT            67
#define SM_CXDRAG               68
#define SM_CYDRAG               69
#define SM_SHOWSOUNDS           70
#define SM_CXMENUCHECK          71   /* Use instead of GetMenuCheckMarkDimensions()! */
#define SM_CYMENUCHECK          72
#define SM_SLOWMACHINE          73
#define SM_MIDEASTENABLED       74
#define SM_MOUSEWHEELPRESENT    75
#define SM_XVIRTUALSCREEN       76
#define SM_YVIRTUALSCREEN       77
#define SM_CXVIRTUALSCREEN      78
#define SM_CYVIRTUALSCREEN      79
#define SM_CMONITORS            80
#define SM_SAMEDISPLAYFORMAT    81
#define SM_IMMENABLED           82
#define SM_CXFOCUSBORDER        83
#define SM_CYFOCUSBORDER        84
#define SM_TABLETPC             86
#define SM_MEDIACENTER          87
#define SM_STARTER              88
#define SM_SERVERR2             89
#define SM_MOUSEHORIZONTALWHEELPRESENT    91
#define SM_CXPADDEDBORDER       92
#define SM_DIGITIZER            94
#define SM_MAXIMUMTOUCHES       95
#define SM_CMETRICS             97
#define SM_REMOTESESSION        0x1000

#define SM_SHUTTINGDOWN           0x2000
#define SM_REMOTECONTROL          0x2001
#define SM_CARETBLINKINGENABLED   0x2002

#define SM_CONVERTIBLESLATEMODE   0x2003
#define SM_SYSTEMDOCKED           0x2004

WINUSERAPI
int
WINAPI
GetSystemMetrics(
	int nIndex);

#if(WINVER >= 0x0605)
WINUSERAPI
int
WINAPI
GetSystemMetricsForDpi(
	int nIndex,
	UINT dpi);

#endif /* WINVER >= 0x0605 */

WINUSERAPI
BOOL
WINAPI
UpdateWindow(
	HWND hWnd);

WINUSERAPI
HWND
WINAPI
SetActiveWindow(
	HWND hWnd);


WINUSERAPI
HWND
WINAPI
GetForegroundWindow(
	VOID);

WINUSERAPI
VOID
WINAPI
SwitchToThisWindow(
	HWND hwnd,
	BOOL fUnknown);

WINUSERAPI
BOOL
WINAPI
SetForegroundWindow(
	HWND hWnd);

WINUSERAPI
HWND
WINAPI
WindowFromDC(
	HDC hDC);

WINUSERAPI
HDC
WINAPI
GetDC(
	HWND hWnd);

WINUSERAPI
HDC
WINAPI
GetDCEx(
	HWND hWnd,
	HRGN hrgnClip,
	DWORD flags);

#define DCX_WINDOW           0x00000001L
#define DCX_CACHE            0x00000002L
#define DCX_NORESETATTRS     0x00000004L
#define DCX_CLIPCHILDREN     0x00000008L
#define DCX_CLIPSIBLINGS     0x00000010L
#define DCX_PARENTCLIP       0x00000020L
#define DCX_EXCLUDERGN       0x00000040L
#define DCX_INTERSECTRGN     0x00000080L
#define DCX_EXCLUDEUPDATE    0x00000100L
#define DCX_INTERSECTUPDATE  0x00000200L
#define DCX_LOCKWINDOWUPDATE 0x00000400L

#define DCX_VALIDATE         0x00200000L

WINUSERAPI
HDC
WINAPI
GetWindowDC(
	HWND hWnd);

WINUSERAPI
int
WINAPI
ReleaseDC(
	HWND hWnd,
	HDC hDC);

typedef struct tagPAINTSTRUCT {
	HDC         hdc;
	BOOL        fErase;
	RECT        rcPaint;
	BOOL        fRestore;
	BOOL        fIncUpdate;
	BYTE        rgbReserved[32];
} PAINTSTRUCT, * PPAINTSTRUCT, * NPPAINTSTRUCT, * LPPAINTSTRUCT;

WINUSERAPI
HDC
WINAPI
BeginPaint(
	HWND hWnd,
	LPPAINTSTRUCT lpPaint);

WINUSERAPI
BOOL
WINAPI
EndPaint(
	HWND hWnd,
	CONST PAINTSTRUCT* lpPaint);

WINUSERAPI
BOOL
WINAPI
GetUpdateRect(
	HWND hWnd,
	LPRECT lpRect,
	BOOL bErase);

WINUSERAPI
int
WINAPI
GetUpdateRgn(
	HWND hWnd,
	HRGN hRgn,
	BOOL bErase);

WINUSERAPI
int
WINAPI
SetWindowRgn(
	HWND hWnd,
	HRGN hRgn,
	BOOL bRedraw);

WINUSERAPI
int
WINAPI
GetWindowRgn(
	HWND hWnd,
	HRGN hRgn);

WINUSERAPI
int
WINAPI
GetWindowRgnBox(
	HWND hWnd,
	LPRECT lprc);

WINUSERAPI
int
WINAPI
ExcludeUpdateRgn(
	HDC hDC,
	HWND hWnd);

WINUSERAPI
BOOL
WINAPI
InvalidateRect(
	HWND hWnd,
	CONST RECT* lpRect,
	BOOL bErase);

WINUSERAPI
BOOL
WINAPI
ValidateRect(
	HWND hWnd,
	CONST RECT* lpRect);

WINUSERAPI
BOOL
WINAPI
InvalidateRgn(
	HWND hWnd,
	HRGN hRgn,
	BOOL bErase);

WINUSERAPI
BOOL
WINAPI
ValidateRgn(
	HWND hWnd,
	HRGN hRgn);

WINUSERAPI
BOOL
WINAPI
RedrawWindow(
	HWND hWnd,
	CONST RECT* lprcUpdate,
	HRGN hrgnUpdate,
	UINT flags);

#define RDW_INVALIDATE          0x0001
#define RDW_INTERNALPAINT       0x0002
#define RDW_ERASE               0x0004

#define RDW_VALIDATE            0x0008
#define RDW_NOINTERNALPAINT     0x0010
#define RDW_NOERASE             0x0020

#define RDW_NOCHILDREN          0x0040
#define RDW_ALLCHILDREN         0x0080

#define RDW_UPDATENOW           0x0100
#define RDW_ERASENOW            0x0200

#define RDW_FRAME               0x0400
#define RDW_NOFRAME             0x0800

WINUSERAPI
BOOL
WINAPI
LockWindowUpdate(
	HWND hWndLock);

WINUSERAPI
BOOL
WINAPI
ScrollWindow(
	HWND hWnd,
	int XAmount,
	int YAmount,
	CONST RECT* lpRect,
	CONST RECT* lpClipRect);

WINUSERAPI
BOOL
WINAPI
ScrollDC(
	HDC hDC,
	int dx,
	int dy,
	CONST RECT* lprcScroll,
	CONST RECT* lprcClip,
	HRGN hrgnUpdate,
	LPRECT lprcUpdate);

WINUSERAPI
int
WINAPI
ScrollWindowEx(
	HWND hWnd,
	int dx,
	int dy,
	CONST RECT* prcScroll,
	CONST RECT* prcClip,
	HRGN hrgnUpdate,
	LPRECT prcUpdate,
	UINT flags);

WINUSERAPI
int
WINAPI
SetScrollPos(
	HWND hWnd,
	int nBar,
	int nPos,
	BOOL bRedraw);

WINUSERAPI
int
WINAPI
GetScrollPos(
	HWND hWnd,
	int nBar);

WINUSERAPI
BOOL
WINAPI
SetScrollRange(
	HWND hWnd,
	int nBar,
	int nMinPos,
	int nMaxPos,
	BOOL bRedraw);

WINUSERAPI
BOOL
WINAPI
GetScrollRange(
	HWND hWnd,
	int nBar,
	LPINT lpMinPos,
	LPINT lpMaxPos);

WINUSERAPI
BOOL
WINAPI
ShowScrollBar(
	HWND hWnd,
	int wBar,
	BOOL bShow);

WINUSERAPI
BOOL
WINAPI
EnableScrollBar(
	HWND hWnd,
	UINT wSBflags,
	UINT wArrows);

#define ESB_ENABLE_BOTH     0x0000
#define ESB_DISABLE_BOTH    0x0003

#define ESB_DISABLE_LEFT    0x0001
#define ESB_DISABLE_RIGHT   0x0002

#define ESB_DISABLE_UP      0x0001
#define ESB_DISABLE_DOWN    0x0002

#define ESB_DISABLE_LTUP    ESB_DISABLE_LEFT
#define ESB_DISABLE_RTDN    ESB_DISABLE_RIGHT

typedef struct tagSCROLLINFO
{
	UINT    cbSize;
	UINT    fMask;
	int     nMin;
	int     nMax;
	UINT    nPage;
	int     nPos;
	int     nTrackPos;
}   SCROLLINFO, FAR* LPSCROLLINFO;
typedef SCROLLINFO CONST FAR* LPCSCROLLINFO;

WINUSERAPI
int
WINAPI
SetScrollInfo(
	HWND hwnd,
	int nBar,
	LPCSCROLLINFO lpsi,
	BOOL redraw);

WINUSERAPI
BOOL
WINAPI
GetScrollInfo(
	HWND hwnd,
	int nBar,
	LPSCROLLINFO lpsi);

typedef BOOL(CALLBACK* PROPENUMPROCA)(HWND, LPCSTR, HANDLE);
typedef BOOL(CALLBACK* PROPENUMPROCW)(HWND, LPCWSTR, HANDLE);

typedef BOOL(CALLBACK* PROPENUMPROCEXA)(HWND, LPSTR, HANDLE, ULONG_PTR);
typedef BOOL(CALLBACK* PROPENUMPROCEXW)(HWND, LPWSTR, HANDLE, ULONG_PTR);

WINUSERAPI
BOOL
WINAPI
SetPropA(
	HWND hWnd,
	LPCSTR lpString,
	HANDLE hData);

WINUSERAPI
BOOL
WINAPI
SetPropW(
	HWND hWnd,
	LPCWSTR lpString,
	HANDLE hData);

WINUSERAPI
HANDLE
WINAPI
GetPropA(
	HWND hWnd,
	LPCSTR lpString);

WINUSERAPI
HANDLE
WINAPI
GetPropW(
	HWND hWnd,
	LPCWSTR lpString);

WINUSERAPI
HANDLE
WINAPI
RemovePropA(
	HWND hWnd,
	LPCSTR lpString);

WINUSERAPI
HANDLE
WINAPI
RemovePropW(
	HWND hWnd,
	LPCWSTR lpString);

WINUSERAPI
int
WINAPI
EnumPropsExA(
	HWND hWnd,
	PROPENUMPROCEXA lpEnumFunc,
	LPARAM lParam);

WINUSERAPI
int
WINAPI
EnumPropsExW(
	HWND hWnd,
	PROPENUMPROCEXW lpEnumFunc,
	LPARAM lParam);

WINUSERAPI
int
WINAPI
EnumPropsA(
	HWND hWnd,
	PROPENUMPROCA lpEnumFunc);

WINUSERAPI
int
WINAPI
EnumPropsW(
	HWND hWnd,
	PROPENUMPROCW lpEnumFunc);

WINUSERAPI
BOOL
WINAPI
SetWindowTextA(
	HWND hWnd,
	LPCSTR lpString);

WINUSERAPI
BOOL
WINAPI
SetWindowTextW(
	HWND hWnd,
	LPCWSTR lpString);

WINUSERAPI
int
WINAPI
GetWindowTextA(
	HWND hWnd,
	LPSTR lpString,
	int nMaxCount);

WINUSERAPI
int
WINAPI
GetWindowTextW(
	HWND hWnd,
	LPWSTR lpString,
	int nMaxCount);

WINUSERAPI
int
WINAPI
GetWindowTextLengthA(
	HWND hWnd);

WINUSERAPI
int
WINAPI
GetWindowTextLengthW(
	HWND hWnd);

WINUSERAPI
BOOL
WINAPI
GetClientRect(
	HWND hWnd,
	LPRECT lpRect);

WINUSERAPI
BOOL
WINAPI
GetWindowRect(
	HWND hWnd,
	LPRECT lpRect);

WINUSERAPI
BOOL
WINAPI
AdjustWindowRect(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu);

WINUSERAPI
BOOL
WINAPI
AdjustWindowRectEx(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu,
	DWORD dwExStyle);

#if(WINVER >= 0x0605)
WINUSERAPI
BOOL
WINAPI
AdjustWindowRectExForDpi(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu,
	DWORD dwExStyle,
	UINT dpi);
#endif /* WINVER >= 0x0605 */

WINUSERAPI
int
WINAPI
ShowCursor(
	BOOL bShow);

WINUSERAPI
BOOL
WINAPI
SetCursorPos(
	int X,
	int Y);

#if(WINVER >= 0x0600)
WINUSERAPI
BOOL
WINAPI
SetPhysicalCursorPos(
	int X,
	int Y);
#endif /* WINVER >= 0x0600 */

WINUSERAPI
HCURSOR
WINAPI
SetCursor(
	HCURSOR hCursor);

WINUSERAPI
BOOL
WINAPI
GetCursorPos(
	LPPOINT lpPoint);

WINUSERAPI
BOOL
WINAPI
GetClipCursor(
	LPRECT lpRect);

WINUSERAPI
HCURSOR
WINAPI
GetCursor(
	VOID);

WINUSERAPI
BOOL
WINAPI
ClientToScreen(
	HWND hWnd,
	LPPOINT lpPoint);

WINUSERAPI
BOOL
WINAPI
ScreenToClient(
	HWND hWnd,
	LPPOINT lpPoint);

#if(WINVER >= 0x0600)
WINUSERAPI
BOOL
WINAPI
LogicalToPhysicalPoint(
	HWND hWnd,
	LPPOINT lpPoint);

WINUSERAPI
BOOL
WINAPI
PhysicalToLogicalPoint(
	HWND hWnd,
	LPPOINT lpPoint);

#endif /* WINVER >= 0x0600 */

#if(WINVER >= 0x0603)
WINUSERAPI
BOOL
WINAPI
LogicalToPhysicalPointForPerMonitorDPI(
	HWND hWnd,
	LPPOINT lpPoint);

WINUSERAPI
BOOL
WINAPI
PhysicalToLogicalPointForPerMonitorDPI(
	HWND hWnd,
	LPPOINT lpPoint);

#endif /* WINVER >= 0x0603 */

WINUSERAPI
int
WINAPI
MapWindowPoints(
	HWND hWndFrom,
	HWND hWndTo,
	LPPOINT lpPoints,
	UINT cPoints);

WINUSERAPI
HWND
WINAPI
WindowFromPoint(
	POINT Point);

#if(WINVER >= 0x0600)
WINUSERAPI
HWND
WINAPI
WindowFromPhysicalPoint(
	POINT Point);
#endif /* WINVER >= 0x0600 */

WINUSERAPI
HWND
WINAPI
ChildWindowFromPoint(
	HWND hWndParent,
	POINT Point);

WINUSERAPI
BOOL
WINAPI
ClipCursor(
	CONST RECT* lpRect);

#define CWP_ALL             0x0000
#define CWP_SKIPINVISIBLE   0x0001
#define CWP_SKIPDISABLED    0x0002
#define CWP_SKIPTRANSPARENT 0x0004

WINUSERAPI
HWND
WINAPI
ChildWindowFromPointEx(
	HWND hwnd,
	POINT pt,
	UINT flags);

#define DWL_MSGRESULT   0
#define DWL_DLGPROC     4
#define DWL_USER        8

#ifdef ARCHITECTURE_X64

#undef DWL_MSGRESULT
#undef DWL_DLGPROC
#undef DWL_USER

#endif /* ARCHITECTURE_X64 */

WINUSERAPI
WORD
WINAPI
GetWindowWord(
	HWND hWnd,
	int nIndex);

WINUSERAPI
WORD
WINAPI
SetWindowWord(
	HWND hWnd,
	int nIndex,
	WORD wNewWord);

WINUSERAPI
LONG
WINAPI
GetWindowLongA(
	HWND hWnd,
	int nIndex);

WINUSERAPI
LONG
WINAPI
GetWindowLongW(
	HWND hWnd,
	int nIndex);

WINUSERAPI
LONG
WINAPI
SetWindowLongA(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong);

WINUSERAPI
LONG
WINAPI
SetWindowLongW(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong);



#if ARCHITECTURE_X64

WINUSERAPI
LONG_PTR
WINAPI
GetWindowLongPtrA(
	HWND hWnd,
	int nIndex);

WINUSERAPI
LONG_PTR
WINAPI
GetWindowLongPtrW(
	HWND hWnd,
	int nIndex);

WINUSERAPI
LONG_PTR
WINAPI
SetWindowLongPtrA(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong);

WINUSERAPI
LONG_PTR
WINAPI
SetWindowLongPtrW(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong);

#define DWLP_MSGRESULT  0
#define DWLP_DLGPROC    DWLP_MSGRESULT + sizeof(LRESULT)
#define DWLP_USER       DWLP_DLGPROC + sizeof(DLGPROC)

#else  /* ARCHITECTURE_X64 */

#define GetWindowLongPtrA   GetWindowLongA
#define GetWindowLongPtrW   GetWindowLongW

#define SetWindowLongPtrA   SetWindowLongA
#define SetWindowLongPtrW   SetWindowLongW

#endif /* ARCHITECTURE_X64 */

WINUSERAPI
WORD
WINAPI
GetClassWord(
	HWND hWnd,
	int nIndex);

WINUSERAPI
WORD
WINAPI
SetClassWord(
	HWND hWnd,
	int nIndex,
	WORD wNewWord);

WINUSERAPI
DWORD
WINAPI
GetClassLongA(
	HWND hWnd,
	int nIndex);

WINUSERAPI
DWORD
WINAPI
GetClassLongW(
	HWND hWnd,
	int nIndex);

WINUSERAPI
DWORD
WINAPI
SetClassLongA(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong);

WINUSERAPI
DWORD
WINAPI
SetClassLongW(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong);

#if ARCHITECTURE_X64

WINUSERAPI
ULONG_PTR
WINAPI
GetClassLongPtrA(
	HWND hWnd,
	int nIndex);

WINUSERAPI
ULONG_PTR
WINAPI
GetClassLongPtrW(
	HWND hWnd,
	int nIndex);

WINUSERAPI
ULONG_PTR
WINAPI
SetClassLongPtrA(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong);

WINUSERAPI
ULONG_PTR
WINAPI
SetClassLongPtrW(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong);

#else  /* ARCHITECTURE_X64 */

#define GetClassLongPtrA    GetClassLongA
#define GetClassLongPtrW    GetClassLongW

#define SetClassLongPtrA    SetClassLongA
#define SetClassLongPtrW    SetClassLongW

#endif /* ARCHITECTURE_X64 */

WINUSERAPI
HWND
WINAPI
GetDesktopWindow(
	VOID);

WINUSERAPI
HWND
WINAPI
GetParent(
	HWND hWnd);

WINUSERAPI
HWND
WINAPI
SetParent(
	HWND hWndChild,
	HWND hWndNewParent);

typedef BOOL(CALLBACK* WNDENUMPROC)(HWND, LPARAM);
typedef LRESULT(CALLBACK* HOOKPROC)(int code, WPARAM wParam, LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
EnumChildWindows(
	HWND hWndParent,
	WNDENUMPROC lpEnumFunc,
	LPARAM lParam);

WINUSERAPI
HWND
WINAPI
FindWindowA(
	LPCSTR lpClassName,
	LPCSTR lpWindowName);

WINUSERAPI
HWND
WINAPI
FindWindowW(
	LPCWSTR lpClassName,
	LPCWSTR lpWindowName);

WINUSERAPI
HWND
WINAPI
FindWindowExA(
	HWND hWndParent,
	HWND hWndChildAfter,
	LPCSTR lpszClass,
	LPCSTR lpszWindow);

WINUSERAPI
HWND
WINAPI
FindWindowExW(
	HWND hWndParent,
	HWND hWndChildAfter,
	LPCWSTR lpszClass,
	LPCWSTR lpszWindow);

WINUSERAPI
BOOL
WINAPI
EnumWindows(
	WNDENUMPROC lpEnumFunc,
	LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
EnumThreadWindows(
	DWORD dwThreadId,
	WNDENUMPROC lpfn,
	LPARAM lParam);

WINUSERAPI
int
WINAPI
GetClassNameA(
	HWND hWnd,
	LPSTR lpClassName,
	int nMaxCount
);

WINUSERAPI
int
WINAPI
GetClassNameW(
	HWND hWnd,
	LPWSTR lpClassName,
	int nMaxCount
);

WINUSERAPI
HWND
WINAPI
GetTopWindow(
	HWND hWnd);

WINUSERAPI
DWORD
WINAPI
GetWindowThreadProcessId(
	HWND hWnd,
	LPDWORD lpdwProcessId);

#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#define GW_ENABLEDPOPUP     6
#define GW_MAX              6

WINUSERAPI
HWND
WINAPI
GetWindow(
	HWND hWnd,
	UINT uCmd);

#ifdef STRICT

WINUSERAPI
HHOOK
WINAPI
SetWindowsHookA(
	int nFilterType,
	HOOKPROC pfnFilterProc);

WINUSERAPI
HHOOK
WINAPI
SetWindowsHookW(
	int nFilterType,
	HOOKPROC pfnFilterProc);

#else /* !STRICT */

WINUSERAPI
HOOKPROC
WINAPI
SetWindowsHookA(
	int nFilterType,
	HOOKPROC pfnFilterProc);

WINUSERAPI
HOOKPROC
WINAPI
SetWindowsHookW(
	int nFilterType,
	HOOKPROC pfnFilterProc);

#endif /* !STRICT */

WINUSERAPI
BOOL
WINAPI
UnhookWindowsHook(
	int nCode,
	HOOKPROC pfnFilterProc);

WINUSERAPI
HHOOK
WINAPI
SetWindowsHookExA(
	int idHook,
	HOOKPROC lpfn,
	HINSTANCE hmod,
	DWORD dwThreadId);

WINUSERAPI
HHOOK
WINAPI
SetWindowsHookExW(
	int idHook,
	HOOKPROC lpfn,
	HINSTANCE hmod,
	DWORD dwThreadId);

WINUSERAPI
BOOL
WINAPI
UnhookWindowsHookEx(
	HHOOK hhk);

WINUSERAPI
LRESULT
WINAPI
CallNextHookEx(
	HHOOK hhk,
	int nCode,
	WPARAM wParam,
	LPARAM lParam);

#ifdef STRICT
#define DefHookProc(nCode, wParam, lParam, phhk)\
		CallNextHookEx(*phhk, nCode, wParam, lParam)
#else
#define DefHookProc(nCode, wParam, lParam, phhk)\
		CallNextHookEx((HHOOK)*phhk, nCode, wParam, lParam)
#endif /* STRICT */

WINUSERAPI
HBITMAP
WINAPI
LoadBitmapA(
	HINSTANCE hInstance,
	LPCSTR lpBitmapName);

WINUSERAPI
HBITMAP
WINAPI
LoadBitmapW(
	HINSTANCE hInstance,
	LPCWSTR lpBitmapName);

WINUSERAPI
HCURSOR
WINAPI
LoadCursorA(
	HINSTANCE hInstance,
	LPCSTR lpCursorName);

WINUSERAPI
HCURSOR
WINAPI
LoadCursorW(
	HINSTANCE hInstance,
	LPCWSTR lpCursorName);

WINUSERAPI
HCURSOR
WINAPI
LoadCursorFromFileA(
	LPCSTR lpFileName);

WINUSERAPI
HCURSOR
WINAPI
LoadCursorFromFileW(
	LPCWSTR lpFileName);

WINUSERAPI
HCURSOR
WINAPI
CreateCursor(
	HINSTANCE hInst,
	int xHotSpot,
	int yHotSpot,
	int nWidth,
	int nHeight,
	CONST VOID* pvANDPlane,
	CONST VOID* pvXORPlane);

WINUSERAPI
BOOL
WINAPI
DestroyCursor(
	HCURSOR hCursor);

#define IS_INTRESOURCE(_r) ((((ULONG_PTR)(_r)) >> 16) == 0)
#define MAKEINTRESOURCEA(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))
#define MAKEINTRESOURCEW(i) ((LPWSTR)((ULONG_PTR)((WORD)(i))))

#define MAKEINTRESOURCE  MAKEINTRESOURCEW

#define CopyCursor(pcur) ((HCURSOR)CopyIcon((HICON)(pcur)))

#define IDC_ARROW           MAKEINTRESOURCE(32512)
#define IDC_IBEAM           MAKEINTRESOURCE(32513)
#define IDC_WAIT            MAKEINTRESOURCE(32514)
#define IDC_CROSS           MAKEINTRESOURCE(32515)
#define IDC_UPARROW         MAKEINTRESOURCE(32516)
#define IDC_SIZE            MAKEINTRESOURCE(32640)  /* OBSOLETE: use IDC_SIZEALL */
#define IDC_ICON            MAKEINTRESOURCE(32641)  /* OBSOLETE: use IDC_ARROW */
#define IDC_SIZENWSE        MAKEINTRESOURCE(32642)
#define IDC_SIZENESW        MAKEINTRESOURCE(32643)
#define IDC_SIZEWE          MAKEINTRESOURCE(32644)
#define IDC_SIZENS          MAKEINTRESOURCE(32645)
#define IDC_SIZEALL         MAKEINTRESOURCE(32646)
#define IDC_NO              MAKEINTRESOURCE(32648) /*not in win3.1 */
#define IDC_HAND            MAKEINTRESOURCE(32649)
#define IDC_APPSTARTING     MAKEINTRESOURCE(32650) /*not in win3.1 */
#define IDC_HELP            MAKEINTRESOURCE(32651)
#if(WINVER >= 0x0606)
#define IDC_PIN            MAKEINTRESOURCE(32671)
#define IDC_PERSON         MAKEINTRESOURCE(32672)
#endif /* WINVER >= 0x0606 */

WINUSERAPI
BOOL
WINAPI
SetSystemCursor(
	HCURSOR hcur,
	DWORD id);

typedef struct _ICONINFO {
	BOOL    fIcon;
	DWORD   xHotspot;
	DWORD   yHotspot;
	HBITMAP hbmMask;
	HBITMAP hbmColor;
} ICONINFO;
typedef ICONINFO* PICONINFO;

WINUSERAPI
HICON
WINAPI
LoadIconA(
	HINSTANCE hInstance,
	LPCSTR lpIconName);

WINUSERAPI
HICON
WINAPI
LoadIconW(
	HINSTANCE hInstance,
	LPCWSTR lpIconName);

WINUSERAPI
HICON
WINAPI
CreateIcon(
	HINSTANCE hInstance,
	int nWidth,
	int nHeight,
	BYTE cPlanes,
	BYTE cBitsPixel,
	CONST BYTE* lpbANDbits,
	CONST BYTE* lpbXORbits);

WINUSERAPI
BOOL
WINAPI
DestroyIcon(
	HICON hIcon);

WINUSERAPI
int
WINAPI
LookupIconIdFromDirectory(
	PBYTE presbits,
	BOOL fIcon);

WINUSERAPI
int
WINAPI
LookupIconIdFromDirectoryEx(
	PBYTE presbits,
	BOOL fIcon,
	int cxDesired,
	int cyDesired,
	UINT Flags);

WINUSERAPI
HICON
WINAPI
CreateIconFromResource(
	PBYTE presbits,
	DWORD dwResSize,
	BOOL fIcon,
	DWORD dwVer);

WINUSERAPI
HICON
WINAPI
CreateIconFromResourceEx(
	PBYTE presbits,
	DWORD dwResSize,
	BOOL fIcon,
	DWORD dwVer,
	int cxDesired,
	int cyDesired,
	UINT Flags);

typedef struct tagCURSORSHAPE
{
	int     xHotSpot;
	int     yHotSpot;
	int     cx;
	int     cy;
	int     cbWidth;
	BYTE    Planes;
	BYTE    BitsPixel;
} CURSORSHAPE, FAR* LPCURSORSHAPE;

#define IMAGE_BITMAP        0
#define IMAGE_ICON          1
#define IMAGE_CURSOR        2
#define IMAGE_ENHMETAFILE   3

#define LR_DEFAULTCOLOR     0x00000000
#define LR_MONOCHROME       0x00000001
#define LR_COLOR            0x00000002
#define LR_COPYRETURNORG    0x00000004
#define LR_COPYDELETEORG    0x00000008
#define LR_LOADFROMFILE     0x00000010
#define LR_LOADTRANSPARENT  0x00000020
#define LR_DEFAULTSIZE      0x00000040
#define LR_VGACOLOR         0x00000080
#define LR_LOADMAP3DCOLORS  0x00001000
#define LR_CREATEDIBSECTION 0x00002000
#define LR_COPYFROMRESOURCE 0x00004000
#define LR_SHARED           0x00008000

WINUSERAPI
HANDLE
WINAPI
LoadImageA(
	HINSTANCE hInst,
	LPCSTR name,
	UINT type,
	int cx,
	int cy,
	UINT fuLoad);

WINUSERAPI
HANDLE
WINAPI
LoadImageW(
	HINSTANCE hInst,
	LPCWSTR name,
	UINT type,
	int cx,
	int cy,
	UINT fuLoad);

WINUSERAPI
HANDLE
WINAPI
CopyImage(
	HANDLE h,
	UINT type,
	int cx,
	int cy,
	UINT flags);

#define DI_MASK         0x0001
#define DI_IMAGE        0x0002
#define DI_NORMAL       0x0003
#define DI_COMPAT       0x0004
#define DI_DEFAULTSIZE  0x0008
#define DI_NOMIRROR     0x0010

WINUSERAPI BOOL WINAPI DrawIconEx(
	HDC hdc,
	int xLeft,
	int yTop,
	HICON hIcon,
	int cxWidth,
	int cyWidth,
	UINT istepIfAniCur,
	HBRUSH hbrFlickerFreeDraw,
	UINT diFlags);

WINUSERAPI
HICON
WINAPI
CreateIconIndirect(
	PICONINFO piconinfo);

WINUSERAPI
HICON
WINAPI
CopyIcon(
	HICON hIcon);

WINUSERAPI
BOOL
WINAPI
GetIconInfo(
	HICON hIcon,
	PICONINFO piconinfo);

#if(_WIN32_WINNT >= 0x0600)
typedef struct _ICONINFOEXA {
	DWORD   cbSize;
	BOOL    fIcon;
	DWORD   xHotspot;
	DWORD   yHotspot;
	HBITMAP hbmMask;
	HBITMAP hbmColor;
	WORD    wResID;
	CHAR    szModName[MAX_PATH];
	CHAR    szResName[MAX_PATH];
} ICONINFOEXA, * PICONINFOEXA;

typedef struct _ICONINFOEXW {
	DWORD   cbSize;
	BOOL    fIcon;
	DWORD   xHotspot;
	DWORD   yHotspot;
	HBITMAP hbmMask;
	HBITMAP hbmColor;
	WORD    wResID;
	WCHAR   szModName[MAX_PATH];
	WCHAR   szResName[MAX_PATH];
} ICONINFOEXW, * PICONINFOEXW;

WINUSERAPI
BOOL
WINAPI
GetIconInfoExA(
	HICON hicon,
	PICONINFOEXA piconinfo);

WINUSERAPI
BOOL
WINAPI
GetIconInfoExW(
	HICON hicon,
	PICONINFOEXW piconinfo);
#endif /* _WIN32_WINNT >= 0x0600 */

#define RES_ICON    1
#define RES_CURSOR  2

#define IDI_APPLICATION     MAKEINTRESOURCE(32512)
#define IDI_HAND            MAKEINTRESOURCE(32513)
#define IDI_QUESTION        MAKEINTRESOURCE(32514)
#define IDI_EXCLAMATION     MAKEINTRESOURCE(32515)
#define IDI_ASTERISK        MAKEINTRESOURCE(32516)
#define IDI_WINLOGO         MAKEINTRESOURCE(32517)
#if(WINVER >= 0x0600)
#define IDI_SHIELD          MAKEINTRESOURCE(32518)
#endif /* WINVER >= 0x0600 */
#define IDI_WARNING     IDI_EXCLAMATION
#define IDI_ERROR       IDI_HAND
#define IDI_INFORMATION IDI_ASTERISK

#define CDS_UPDATEREGISTRY           0x00000001
#define CDS_TEST                     0x00000002
#define CDS_FULLSCREEN               0x00000004
#define CDS_GLOBAL                   0x00000008
#define CDS_SET_PRIMARY              0x00000010
#define CDS_VIDEOPARAMETERS          0x00000020
#if(WINVER >= 0x0600)
#define CDS_ENABLE_UNSAFE_MODES      0x00000100
#define CDS_DISABLE_UNSAFE_MODES     0x00000200
#endif /* WINVER >= 0x0600 */
#define CDS_RESET                    0x40000000
#define CDS_RESET_EX                 0x20000000
#define CDS_NORESET                  0x10000000

#define DISP_CHANGE_SUCCESSFUL       0
#define DISP_CHANGE_RESTART          1
#define DISP_CHANGE_FAILED          -1
#define DISP_CHANGE_BADMODE         -2
#define DISP_CHANGE_NOTUPDATED      -3
#define DISP_CHANGE_BADFLAGS        -4
#define DISP_CHANGE_BADPARAM        -5
#if(_WIN32_WINNT >= 0x0501)
#define DISP_CHANGE_BADDUALVIEW     -6
#endif /* _WIN32_WINNT >= 0x0501 */

struct _devicemodeA;
typedef _devicemodeA DEVMODEA, * PDEVMODEA, * NPDEVMODEA, * LPDEVMODEA;
struct _devicemodeW;
typedef _devicemodeW DEVMODEW, * PDEVMODEW, * NPDEVMODEW, * LPDEVMODEW;

WINUSERAPI
LONG
WINAPI
ChangeDisplaySettingsA(
	DEVMODEA* lpDevMode,
	DWORD dwFlags);

WINUSERAPI
LONG
WINAPI
ChangeDisplaySettingsW(
	DEVMODEW* lpDevMode,
	DWORD dwFlags);

WINUSERAPI
LONG
WINAPI
ChangeDisplaySettingsExA(
	LPCSTR lpszDeviceName,
	DEVMODEA* lpDevMode,
	HWND hwnd,
	DWORD dwflags,
	LPVOID lParam);

WINUSERAPI
LONG
WINAPI
ChangeDisplaySettingsExW(
	LPCWSTR lpszDeviceName,
	DEVMODEW* lpDevMode,
	HWND hwnd,
	DWORD dwflags,
	LPVOID lParam);

#define ENUM_CURRENT_SETTINGS       ((DWORD)-1)
#define ENUM_REGISTRY_SETTINGS      ((DWORD)-2)

WINUSERAPI
BOOL
WINAPI
EnumDisplaySettingsA(
	LPCSTR lpszDeviceName,
	DWORD iModeNum,
	DEVMODEA* lpDevMode);

WINUSERAPI
BOOL
WINAPI
EnumDisplaySettingsW(
	LPCWSTR lpszDeviceName,
	DWORD iModeNum,
	DEVMODEW* lpDevMode);

#if(WINVER >= 0x0500)

WINUSERAPI
BOOL
WINAPI
EnumDisplaySettingsExA(
	_In_opt_ LPCSTR lpszDeviceName,
	_In_ DWORD iModeNum,
	_Inout_ DEVMODEA* lpDevMode,
	_In_ DWORD dwFlags);
WINUSERAPI
BOOL
WINAPI
EnumDisplaySettingsExW(
	_In_opt_ LPCWSTR lpszDeviceName,
	_In_ DWORD iModeNum,
	_Inout_ DEVMODEW* lpDevMode,
	_In_ DWORD dwFlags);

#define EDS_RAWMODE                   0x00000002
#define EDS_ROTATEDMODE               0x00000004

struct _DISPLAY_DEVICEA;
typedef _DISPLAY_DEVICEA* PDISPLAY_DEVICEA, * LPDISPLAY_DEVICEA;
struct _DISPLAY_DEVICEW;
typedef _DISPLAY_DEVICEW* PDISPLAY_DEVICEW, * LPDISPLAY_DEVICEW;

WINUSERAPI
BOOL
WINAPI
EnumDisplayDevicesA(
	LPCSTR lpDevice,
	DWORD iDevNum,
	PDISPLAY_DEVICEA lpDisplayDevice,
	DWORD dwFlags);

WINUSERAPI
BOOL
WINAPI
EnumDisplayDevicesW(
	LPCWSTR lpDevice,
	DWORD iDevNum,
	PDISPLAY_DEVICEW lpDisplayDevice,
	DWORD dwFlags);

/* Flags for EnumDisplayDevices */
#define EDD_GET_DEVICE_INTERFACE_NAME 0x00000001

#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0601)

WINUSERAPI
LONG
WINAPI
GetDisplayConfigBufferSizes(
	UINT32 flags,
	UINT32* numPathArrayElements,
	UINT32* numModeInfoArrayElements);

struct DISPLAYCONFIG_PATH_INFO;
struct DISPLAYCONFIG_MODE_INFO;
typedef enum DISPLAYCONFIG_TOPOLOGY_ID
{
	DISPLAYCONFIG_TOPOLOGY_INTERNAL = 0x00000001,
	DISPLAYCONFIG_TOPOLOGY_CLONE = 0x00000002,
	DISPLAYCONFIG_TOPOLOGY_EXTEND = 0x00000004,
	DISPLAYCONFIG_TOPOLOGY_EXTERNAL = 0x00000008,
	DISPLAYCONFIG_TOPOLOGY_FORCE_UINT32 = 0xFFFFFFFF
} DISPLAYCONFIG_TOPOLOGY_ID;
struct DISPLAYCONFIG_DEVICE_INFO_HEADER;

WINUSERAPI
LONG
WINAPI
SetDisplayConfig(
	UINT32 numPathArrayElements,
	DISPLAYCONFIG_PATH_INFO* pathArray,
	UINT32 numModeInfoArrayElements,
	DISPLAYCONFIG_MODE_INFO* modeInfoArray,
	UINT32 flags);

WINUSERAPI
LONG
WINAPI
QueryDisplayConfig(
	UINT32 flags,
	UINT32* numPathArrayElements,
	DISPLAYCONFIG_PATH_INFO* pathArray,
	UINT32* numModeInfoArrayElements,
	DISPLAYCONFIG_MODE_INFO* modeInfoArray,
	DISPLAYCONFIG_TOPOLOGY_ID* currentTopologyId);

WINUSERAPI
LONG
WINAPI
DisplayConfigGetDeviceInfo(
	DISPLAYCONFIG_DEVICE_INFO_HEADER* requestPacket);

WINUSERAPI
LONG
WINAPI
DisplayConfigSetDeviceInfo(
	DISPLAYCONFIG_DEVICE_INFO_HEADER* setPacket);

WINUSERAPI
BOOL
WINAPI
SystemParametersInfoA(
	UINT uiAction,
	UINT uiParam,
	PVOID pvParam,
	UINT fWinIni);

WINUSERAPI
BOOL
WINAPI
SystemParametersInfoW(
	UINT uiAction,
	UINT uiParam,
	PVOID pvParam,
	UINT fWinIni);

#endif /* WINVER >= 0x0601 */

#if(WINVER >= 0x0605)
WINUSERAPI
BOOL
WINAPI
SystemParametersInfoForDpi(
	UINT uiAction,
	UINT uiParam,
	PVOID pvParam,
	UINT fWinIni,
	UINT dpi);

#endif /* WINVER >= 0x0605 */

#define _DPI_AWARENESS_CONTEXTS_

DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

typedef enum DPI_AWARENESS {
	DPI_AWARENESS_INVALID = -1,
	DPI_AWARENESS_UNAWARE = 0,
	DPI_AWARENESS_SYSTEM_AWARE = 1,
	DPI_AWARENESS_PER_MONITOR_AWARE = 2
} DPI_AWARENESS;

#define DPI_AWARENESS_CONTEXT_UNAWARE               ((DPI_AWARENESS_CONTEXT)-1)
#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE          ((DPI_AWARENESS_CONTEXT)-2)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE     ((DPI_AWARENESS_CONTEXT)-3)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2  ((DPI_AWARENESS_CONTEXT)-4)
#define DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED     ((DPI_AWARENESS_CONTEXT)-5)

typedef enum DPI_HOSTING_BEHAVIOR {
	DPI_HOSTING_BEHAVIOR_INVALID = -1,
	DPI_HOSTING_BEHAVIOR_DEFAULT = 0,
	DPI_HOSTING_BEHAVIOR_MIXED = 1
} DPI_HOSTING_BEHAVIOR;

#if(WINVER >= 0x0500)

#define MONITOR_DEFAULTTONULL       0x00000000
#define MONITOR_DEFAULTTOPRIMARY    0x00000001
#define MONITOR_DEFAULTTONEAREST    0x00000002

WINUSERAPI
HMONITOR
WINAPI
MonitorFromPoint(
	POINT pt,
	DWORD dwFlags);

WINUSERAPI
HMONITOR
WINAPI
MonitorFromRect(
	LPCRECT lprc,
	DWORD dwFlags);

WINUSERAPI
HMONITOR
WINAPI
MonitorFromWindow(
	HWND hwnd,
	DWORD dwFlags);

#define MONITORINFOF_PRIMARY        0x00000001

#ifndef CCHDEVICENAME
#define CCHDEVICENAME 32
#endif

typedef struct tagMONITORINFO
{
	DWORD   cbSize;
	RECT    rcMonitor;
	RECT    rcWork;
	DWORD   dwFlags;
} MONITORINFO, * LPMONITORINFO;

#ifdef __cplusplus
}
typedef struct tagMONITORINFOEXA : public tagMONITORINFO
{
	CHAR        szDevice[CCHDEVICENAME];
} MONITORINFOEXA, * LPMONITORINFOEXA;
typedef struct tagMONITORINFOEXW : public tagMONITORINFO
{
	WCHAR       szDevice[CCHDEVICENAME];
} MONITORINFOEXW, * LPMONITORINFOEXW;

extern "C" {
#else // ndef __cplusplus
typedef struct tagMONITORINFOEXA
{
	MONITORINFO DUMMYSTRUCTNAME;
	CHAR        szDevice[CCHDEVICENAME];
} MONITORINFOEXA, * LPMONITORINFOEXA;
typedef struct tagMONITORINFOEXW
{
	MONITORINFO DUMMYSTRUCTNAME;
	WCHAR       szDevice[CCHDEVICENAME];
} MONITORINFOEXW, * LPMONITORINFOEXW;
#endif

WINUSERAPI
BOOL
WINAPI
GetMonitorInfoA(
	HMONITOR hMonitor,
	LPMONITORINFO lpmi);

WINUSERAPI
BOOL
WINAPI
GetMonitorInfoW(
	HMONITOR hMonitor,
	LPMONITORINFO lpmi);

typedef BOOL(CALLBACK* MONITORENUMPROC)(HMONITOR, HDC, LPRECT, LPARAM);

WINUSERAPI
BOOL
WINAPI
EnumDisplayMonitors(
	HDC hdc,
	LPCRECT lprcClip,
	MONITORENUMPROC lpfnEnum,
	LPARAM dwData);

#if(_WIN32_WINNT >= 0x0600)

#define USER_DEFAULT_SCREEN_DPI 96

WINUSERAPI
BOOL
WINAPI
SetProcessDPIAware(
	VOID);

WINUSERAPI
BOOL
WINAPI
IsProcessDPIAware(
	VOID);

#endif /* _WIN32_WINNT >= 0x0600 */

#if(WINVER >= 0x0605)
WINUSERAPI
DPI_AWARENESS_CONTEXT
WINAPI
SetThreadDpiAwarenessContext(
	DPI_AWARENESS_CONTEXT dpiContext);

WINUSERAPI
DPI_AWARENESS_CONTEXT
WINAPI
GetThreadDpiAwarenessContext(
	VOID);

WINUSERAPI
DPI_AWARENESS_CONTEXT
WINAPI
GetWindowDpiAwarenessContext(
	HWND hwnd);

WINUSERAPI
DPI_AWARENESS
WINAPI
GetAwarenessFromDpiAwarenessContext(
	DPI_AWARENESS_CONTEXT value);

WINUSERAPI
UINT
WINAPI
GetDpiFromDpiAwarenessContext(
	DPI_AWARENESS_CONTEXT value);

WINUSERAPI
BOOL
WINAPI
AreDpiAwarenessContextsEqual(
	DPI_AWARENESS_CONTEXT dpiContextA,
	DPI_AWARENESS_CONTEXT dpiContextB);

WINUSERAPI
BOOL
WINAPI
IsValidDpiAwarenessContext(
	DPI_AWARENESS_CONTEXT value);

WINUSERAPI
UINT
WINAPI
GetDpiForWindow(
	HWND hwnd);

WINUSERAPI
UINT
WINAPI
GetDpiForSystem(
	VOID);

WINUSERAPI
UINT
WINAPI
GetSystemDpiForProcess(
	HANDLE hProcess);

WINUSERAPI
BOOL
WINAPI
EnableNonClientDpiScaling(
	HWND hwnd);

WINUSERAPI
BOOL
WINAPI
InheritWindowMonitor(
	HWND hwnd,
	HWND hwndInherit);

#endif /* WINVER >= 0x0605 */

#if(WINVER >= 0x0605)
WINUSERAPI
BOOL
WINAPI
SetProcessDpiAwarenessContext(
	DPI_AWARENESS_CONTEXT value);

#endif /* WINVER >= 0x0605 */

#if (NTDDI_VERSION >= NTDDI_WIN10_19H1)

WINUSERAPI
DPI_AWARENESS_CONTEXT
WINAPI
GetDpiAwarenessContextForProcess(
	HANDLE hProcess);

#endif // NTDDI_VERSION >= NTDDI_WIN10_19H1

#if(WINVER >= 0x0606)

WINUSERAPI
DPI_HOSTING_BEHAVIOR
WINAPI
SetThreadDpiHostingBehavior(
	DPI_HOSTING_BEHAVIOR value);

WINUSERAPI
DPI_HOSTING_BEHAVIOR
WINAPI
GetThreadDpiHostingBehavior(VOID);

WINUSERAPI
DPI_HOSTING_BEHAVIOR
WINAPI
GetWindowDpiHostingBehavior(
	HWND hwnd);

#endif /* WINVER >= 0x0606 */

WINUSERAPI
UINT
WINAPI
GetWindowModuleFileNameA(
	HWND hwnd,
	LPSTR pszFileName,
	UINT cchFileNameMax);

WINUSERAPI
UINT
WINAPI
GetWindowModuleFileNameW(
	HWND hwnd,
	LPWSTR pszFileName,
	UINT cchFileNameMax);

typedef struct tagCURSORINFO
{
	DWORD   cbSize;
	DWORD   flags;
	HCURSOR hCursor;
	POINT   ptScreenPos;
} CURSORINFO, * PCURSORINFO, * LPCURSORINFO;

#define CURSOR_SHOWING     0x00000001
#if(WINVER >= 0x0602)
#define CURSOR_SUPPRESSED  0x00000002
#endif /* WINVER >= 0x0602 */

WINUSERAPI
BOOL
WINAPI
GetCursorInfo(
	PCURSORINFO pci);

typedef struct tagWINDOWINFO
{
	DWORD cbSize;
	RECT rcWindow;
	RECT rcClient;
	DWORD dwStyle;
	DWORD dwExStyle;
	DWORD dwWindowStatus;
	UINT cxWindowBorders;
	UINT cyWindowBorders;
	ATOM atomWindowType;
	WORD wCreatorVersion;
} WINDOWINFO, * PWINDOWINFO, * LPWINDOWINFO;

#define WS_ACTIVECAPTION    0x0001

WINUSERAPI
BOOL
WINAPI
GetWindowInfo(
	HWND hwnd,
	PWINDOWINFO pwi);

#define CCHILDREN_TITLEBAR              5
#define CCHILDREN_SCROLLBAR             5

typedef struct tagTITLEBARINFO
{
	DWORD cbSize;
	RECT rcTitleBar;
	DWORD rgstate[CCHILDREN_TITLEBAR + 1];
} TITLEBARINFO, * PTITLEBARINFO, * LPTITLEBARINFO;

WINUSERAPI
BOOL
WINAPI
GetTitleBarInfo(
	HWND hwnd,
	PTITLEBARINFO pti);

#if(WINVER >= 0x0600)
typedef struct tagTITLEBARINFOEX
{
	DWORD cbSize;
	RECT rcTitleBar;
	DWORD rgstate[CCHILDREN_TITLEBAR + 1];
	RECT rgrect[CCHILDREN_TITLEBAR + 1];
} TITLEBARINFOEX, * PTITLEBARINFOEX, * LPTITLEBARINFOEX;
#endif /* WINVER >= 0x0600 */

typedef struct tagMENUBARINFO
{
	DWORD cbSize;
	RECT rcBar;          // rect of bar, popup, item
	HMENU hMenu;         // real menu handle of bar, popup
	HWND hwndMenu;       // hwnd of item submenu if one
	BOOL fBarFocused : 1;  // bar, popup has the focus
	BOOL fFocused : 1;     // item has the focus
	BOOL fUnused : 30;     // reserved
} MENUBARINFO, * PMENUBARINFO, * LPMENUBARINFO;

WINUSERAPI
BOOL
WINAPI
GetMenuBarInfo(
	HWND hwnd,
	LONG idObject,
	LONG idItem,
	PMENUBARINFO pmbi);

typedef struct tagSCROLLBARINFO
{
	DWORD cbSize;
	RECT rcScrollBar;
	int dxyLineButton;
	int xyThumbTop;
	int xyThumbBottom;
	int reserved;
	DWORD rgstate[CCHILDREN_SCROLLBAR + 1];
} SCROLLBARINFO, * PSCROLLBARINFO, * LPSCROLLBARINFO;

WINUSERAPI
BOOL
WINAPI
GetScrollBarInfo(
	HWND hwnd,
	LONG idObject,
	PSCROLLBARINFO psbi);

#define     GA_PARENT       1
#define     GA_ROOT         2
#define     GA_ROOTOWNER    3

WINUSERAPI
HWND
WINAPI
GetAncestor(
	HWND hwnd,
	UINT gaFlags);

WINUSERAPI
HWND
WINAPI
RealChildWindowFromPoint(
	HWND hwndParent,
	POINT ptParentClientCoords);

WINUSERAPI
UINT
WINAPI
RealGetWindowClassA(
	HWND hwnd,
	LPSTR ptszClassName,
	UINT cchClassNameMax);

WINUSERAPI
UINT
WINAPI
RealGetWindowClassW(
	HWND hwnd,
	LPWSTR ptszClassName,
	UINT cchClassNameMax);

#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)

DECLARE_HANDLE(HRAWINPUT);

#define GET_RAWINPUT_CODE_WPARAM(wParam)    ((wParam) & 0xff)

#define RIM_INPUT       0
#define RIM_INPUTSINK   1

typedef struct tagRAWINPUTHEADER {
	DWORD dwType;
	DWORD dwSize;
	HANDLE hDevice;
	WPARAM wParam;
} RAWINPUTHEADER, * PRAWINPUTHEADER, * LPRAWINPUTHEADER;

#define RIM_TYPEMOUSE       0
#define RIM_TYPEKEYBOARD    1
#define RIM_TYPEHID         2
#define RIM_TYPEMAX         2

#if COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 4201)
#endif

typedef struct tagRAWMOUSE {
	/*
	 * Indicator flags.
	 */
	USHORT usFlags;

	/*
	 * The transition state of the mouse buttons.
	 */
	union {
		ULONG ulButtons;
		struct {
			USHORT  usButtonFlags;
			USHORT  usButtonData;
		};
	};


	/*
	 * The raw state of the mouse buttons.
	 */
	ULONG ulRawButtons;

	/*
	 * The signed relative or absolute motion in the X direction.
	 */
	LONG lLastX;

	/*
	 * The signed relative or absolute motion in the Y direction.
	 */
	LONG lLastY;

	/*
	 * Device-specific additional information for the event.
	 */
	ULONG ulExtraInformation;

} RAWMOUSE, * PRAWMOUSE, * LPRAWMOUSE;

#if COMPILER_MSVC
#pragma warning(pop)
#endif

#define RI_MOUSE_LEFT_BUTTON_DOWN   0x0001  // Left Button changed to down.
#define RI_MOUSE_LEFT_BUTTON_UP     0x0002  // Left Button changed to up.
#define RI_MOUSE_RIGHT_BUTTON_DOWN  0x0004  // Right Button changed to down.
#define RI_MOUSE_RIGHT_BUTTON_UP    0x0008  // Right Button changed to up.
#define RI_MOUSE_MIDDLE_BUTTON_DOWN 0x0010  // Middle Button changed to down.
#define RI_MOUSE_MIDDLE_BUTTON_UP   0x0020  // Middle Button changed to up.

#define RI_MOUSE_BUTTON_1_DOWN      RI_MOUSE_LEFT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_1_UP        RI_MOUSE_LEFT_BUTTON_UP
#define RI_MOUSE_BUTTON_2_DOWN      RI_MOUSE_RIGHT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_2_UP        RI_MOUSE_RIGHT_BUTTON_UP
#define RI_MOUSE_BUTTON_3_DOWN      RI_MOUSE_MIDDLE_BUTTON_DOWN
#define RI_MOUSE_BUTTON_3_UP        RI_MOUSE_MIDDLE_BUTTON_UP

#define RI_MOUSE_BUTTON_4_DOWN      0x0040
#define RI_MOUSE_BUTTON_4_UP        0x0080
#define RI_MOUSE_BUTTON_5_DOWN      0x0100
#define RI_MOUSE_BUTTON_5_UP        0x0200

#define RI_MOUSE_WHEEL              0x0400
#if(WINVER >= 0x0600)
#define RI_MOUSE_HWHEEL             0x0800
#endif /* WINVER >= 0x0600 */

#define MOUSE_MOVE_RELATIVE         0
#define MOUSE_MOVE_ABSOLUTE         1
#define MOUSE_VIRTUAL_DESKTOP    0x02  // the coordinates are mapped to the virtual desktop
#define MOUSE_ATTRIBUTES_CHANGED 0x04  // requery for mouse attributes
#if(WINVER >= 0x0600)
#define MOUSE_MOVE_NOCOALESCE    0x08  // do not coalesce mouse moves
#endif /* WINVER >= 0x0600 */

typedef struct tagRAWKEYBOARD {
	/*
	 * The "make" scan code (key depression).
	 */
	USHORT MakeCode;

	/*
	 * The flags field indicates a "break" (key release) and other
	 * miscellaneous scan code information defined in ntddkbd.h.
	 */
	USHORT Flags;

	USHORT Reserved;

	/*
	 * Windows message compatible information
	 */
	USHORT VKey;
	UINT   Message;

	/*
	 * Device-specific additional information for the event.
	 */
	ULONG ExtraInformation;


} RAWKEYBOARD, * PRAWKEYBOARD, * LPRAWKEYBOARD;

#define KEYBOARD_OVERRUN_MAKE_CODE    0xFF

#define RI_KEY_MAKE             0
#define RI_KEY_BREAK            1
#define RI_KEY_E0               2
#define RI_KEY_E1               4
#define RI_KEY_TERMSRV_SET_LED  8
#define RI_KEY_TERMSRV_SHADOW   0x10

typedef struct tagRAWHID {
	DWORD dwSizeHid;    // byte size of each report
	DWORD dwCount;      // number of input packed
	BYTE bRawData[1];
} RAWHID, * PRAWHID, * LPRAWHID;

typedef struct tagRAWINPUT {
	RAWINPUTHEADER header;
	union {
		RAWMOUSE    mouse;
		RAWKEYBOARD keyboard;
		RAWHID      hid;
	} data;
} RAWINPUT, * PRAWINPUT, * LPRAWINPUT;

#ifdef ARCHITECTURE_X64
#define RAWINPUT_ALIGN(x)   (((x) + sizeof(QWORD) - 1) & ~(sizeof(QWORD) - 1))
#else   // ARCHITECTURE_X64
#define RAWINPUT_ALIGN(x)   (((x) + sizeof(DWORD) - 1) & ~(sizeof(DWORD) - 1))
#endif  // ARCHITECTURE_X64

#define NEXTRAWINPUTBLOCK(ptr) ((PRAWINPUT)RAWINPUT_ALIGN((ULONG_PTR)((PBYTE)(ptr) + (ptr)->header.dwSize)))

#define RID_INPUT               0x10000003
#define RID_HEADER              0x10000005

WINUSERAPI
UINT
WINAPI
GetRawInputData(
	HRAWINPUT hRawInput,
	UINT uiCommand,
	LPVOID pData,
	PUINT pcbSize,
	UINT cbSizeHeader);

#define RIDI_PREPARSEDDATA      0x20000005
#define RIDI_DEVICENAME         0x20000007  // the return valus is the character length, not the byte size
#define RIDI_DEVICEINFO         0x2000000b

typedef struct tagRID_DEVICE_INFO_MOUSE {
	DWORD dwId;
	DWORD dwNumberOfButtons;
	DWORD dwSampleRate;
	BOOL  fHasHorizontalWheel;
} RID_DEVICE_INFO_MOUSE, * PRID_DEVICE_INFO_MOUSE;

typedef struct tagRID_DEVICE_INFO_KEYBOARD {
	DWORD dwType;
	DWORD dwSubType;
	DWORD dwKeyboardMode;
	DWORD dwNumberOfFunctionKeys;
	DWORD dwNumberOfIndicators;
	DWORD dwNumberOfKeysTotal;
} RID_DEVICE_INFO_KEYBOARD, * PRID_DEVICE_INFO_KEYBOARD;

typedef struct tagRID_DEVICE_INFO_HID {
	DWORD dwVendorId;
	DWORD dwProductId;
	DWORD dwVersionNumber;

	/*
	 * Top level collection UsagePage and Usage
	 */
	USHORT usUsagePage;
	USHORT usUsage;
} RID_DEVICE_INFO_HID, * PRID_DEVICE_INFO_HID;

typedef struct tagRID_DEVICE_INFO {
	DWORD cbSize;
	DWORD dwType;
	union {
		RID_DEVICE_INFO_MOUSE mouse;
		RID_DEVICE_INFO_KEYBOARD keyboard;
		RID_DEVICE_INFO_HID hid;
	} DUMMYUNIONNAME;
} RID_DEVICE_INFO, * PRID_DEVICE_INFO, * LPRID_DEVICE_INFO;

WINUSERAPI
UINT
WINAPI
GetRawInputDeviceInfoA(
	HANDLE hDevice,
	UINT uiCommand,
	LPVOID pData,
	PUINT pcbSize);

WINUSERAPI
UINT
WINAPI
GetRawInputDeviceInfoW(
	HANDLE hDevice,
	UINT uiCommand,
	LPVOID pData,
	PUINT pcbSize);

WINUSERAPI
UINT
WINAPI
GetRawInputBuffer(
	PRAWINPUT pData,
	PUINT pcbSize,
	UINT cbSizeHeader);

typedef struct tagRAWINPUTDEVICE {
	USHORT usUsagePage; // Toplevel collection UsagePage
	USHORT usUsage;     // Toplevel collection Usage
	DWORD dwFlags;
	HWND hwndTarget;    // Target hwnd. NULL = follows keyboard focus
} RAWINPUTDEVICE, * PRAWINPUTDEVICE, * LPRAWINPUTDEVICE;

typedef CONST RAWINPUTDEVICE* PCRAWINPUTDEVICE;

#define RIDEV_REMOVE            0x00000001
#define RIDEV_EXCLUDE           0x00000010
#define RIDEV_PAGEONLY          0x00000020
#define RIDEV_NOLEGACY          0x00000030
#define RIDEV_INPUTSINK         0x00000100
#define RIDEV_CAPTUREMOUSE      0x00000200  // effective when mouse nolegacy is specified, otherwise it would be an error
#define RIDEV_NOHOTKEYS         0x00000200  // effective for keyboard.
#define RIDEV_APPKEYS           0x00000400  // effective for keyboard.
#if(_WIN32_WINNT >= 0x0501)
#define RIDEV_EXINPUTSINK       0x00001000
#define RIDEV_DEVNOTIFY         0x00002000
#endif /* _WIN32_WINNT >= 0x0501 */
#define RIDEV_EXMODEMASK        0x000000F0

#define RIDEV_EXMODE(mode)  ((mode) & RIDEV_EXMODEMASK)

#define GIDC_ARRIVAL             1
#define GIDC_REMOVAL             2

#if (_WIN32_WINNT >= 0x0601)
#define GET_DEVICE_CHANGE_WPARAM(wParam)  (LOWORD(wParam))
#else
#define GET_DEVICE_CHANGE_LPARAM(lParam)  (LOWORD(lParam))
#endif /* (_WIN32_WINNT >= 0x0601) */

WINUSERAPI
BOOL
WINAPI
RegisterRawInputDevices(
	PCRAWINPUTDEVICE pRawInputDevices,
	UINT uiNumDevices,
	UINT cbSize);

WINUSERAPI
UINT
WINAPI
GetRegisteredRawInputDevices(
	PRAWINPUTDEVICE pRawInputDevices,
	PUINT puiNumDevices,
	UINT cbSize);


typedef struct tagRAWINPUTDEVICELIST {
	HANDLE hDevice;
	DWORD dwType;
} RAWINPUTDEVICELIST, * PRAWINPUTDEVICELIST;

WINUSERAPI
UINT
WINAPI
GetRawInputDeviceList(
	PRAWINPUTDEVICELIST pRawInputDeviceList,
	PUINT puiNumDevices,
	UINT cbSize);

WINUSERAPI
LRESULT
WINAPI
DefRawInputProc(
	PRAWINPUT* paRawInput,
	INT nInput,
	UINT cbSizeHeader);

#endif /* _WIN32_WINNT >= 0x0501 */

}
#else
#include <WinUser.h>
#endif

#endif /* CORE_WIN32_USER_H */
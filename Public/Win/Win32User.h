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

#define PRF_CHECKVISIBLE    0x00000001L
#define PRF_NONCLIENT       0x00000002L
#define PRF_CLIENT          0x00000004L
#define PRF_ERASEBKGND      0x00000008L
#define PRF_CHILDREN        0x00000010L
#define PRF_OWNED           0x00000020L

#define BDR_RAISEDOUTER 0x0001
#define BDR_SUNKENOUTER 0x0002
#define BDR_RAISEDINNER 0x0004
#define BDR_SUNKENINNER 0x0008

#define BDR_OUTER       (BDR_RAISEDOUTER | BDR_SUNKENOUTER)
#define BDR_INNER       (BDR_RAISEDINNER | BDR_SUNKENINNER)
#define BDR_RAISED      (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define BDR_SUNKEN      (BDR_SUNKENOUTER | BDR_SUNKENINNER)

#define EDGE_RAISED     (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define EDGE_SUNKEN     (BDR_SUNKENOUTER | BDR_SUNKENINNER)
#define EDGE_ETCHED     (BDR_SUNKENOUTER | BDR_RAISEDINNER)
#define EDGE_BUMP       (BDR_RAISEDOUTER | BDR_SUNKENINNER)

#define BF_LEFT         0x0001
#define BF_TOP          0x0002
#define BF_RIGHT        0x0004
#define BF_BOTTOM       0x0008

#define BF_TOPLEFT      (BF_TOP | BF_LEFT)
#define BF_TOPRIGHT     (BF_TOP | BF_RIGHT)
#define BF_BOTTOMLEFT   (BF_BOTTOM | BF_LEFT)
#define BF_BOTTOMRIGHT  (BF_BOTTOM | BF_RIGHT)
#define BF_RECT         (BF_LEFT | BF_TOP | BF_RIGHT | BF_BOTTOM)

#define BF_DIAGONAL     0x0010

#define BF_DIAGONAL_ENDTOPRIGHT     (BF_DIAGONAL | BF_TOP | BF_RIGHT)
#define BF_DIAGONAL_ENDTOPLEFT      (BF_DIAGONAL | BF_TOP | BF_LEFT)
#define BF_DIAGONAL_ENDBOTTOMLEFT   (BF_DIAGONAL | BF_BOTTOM | BF_LEFT)
#define BF_DIAGONAL_ENDBOTTOMRIGHT  (BF_DIAGONAL | BF_BOTTOM | BF_RIGHT)


#define BF_MIDDLE       0x0800  /* Fill in the middle */
#define BF_SOFT         0x1000  /* For softer buttons */
#define BF_ADJUST       0x2000  /* Calculate the space left over */
#define BF_FLAT         0x4000  /* For flat rather than 3D borders */
#define BF_MONO         0x8000  /* For monochrome borders */

WINUSERAPI
BOOL
WINAPI
DrawEdge(
	HDC hdc,
	LPRECT qrc,
	UINT edge,
	UINT grfFlags);

#define DFC_CAPTION             1
#define DFC_MENU                2
#define DFC_SCROLL              3
#define DFC_BUTTON              4
#define DFC_POPUPMENU           5

#define DFCS_CAPTIONCLOSE       0x0000
#define DFCS_CAPTIONMIN         0x0001
#define DFCS_CAPTIONMAX         0x0002
#define DFCS_CAPTIONRESTORE     0x0003
#define DFCS_CAPTIONHELP        0x0004

#define DFCS_MENUARROW          0x0000
#define DFCS_MENUCHECK          0x0001
#define DFCS_MENUBULLET         0x0002
#define DFCS_MENUARROWRIGHT     0x0004
#define DFCS_SCROLLUP           0x0000
#define DFCS_SCROLLDOWN         0x0001
#define DFCS_SCROLLLEFT         0x0002
#define DFCS_SCROLLRIGHT        0x0003
#define DFCS_SCROLLCOMBOBOX     0x0005
#define DFCS_SCROLLSIZEGRIP     0x0008
#define DFCS_SCROLLSIZEGRIPRIGHT 0x0010

#define DFCS_BUTTONCHECK        0x0000
#define DFCS_BUTTONRADIOIMAGE   0x0001
#define DFCS_BUTTONRADIOMASK    0x0002
#define DFCS_BUTTONRADIO        0x0004
#define DFCS_BUTTON3STATE       0x0008
#define DFCS_BUTTONPUSH         0x0010

#define DFCS_INACTIVE           0x0100
#define DFCS_PUSHED             0x0200
#define DFCS_CHECKED            0x0400
#define DFCS_TRANSPARENT        0x0800
#define DFCS_HOT                0x1000

#define DFCS_ADJUSTRECT         0x2000
#define DFCS_FLAT               0x4000
#define DFCS_MONO               0x8000

WINUSERAPI
BOOL
WINAPI
DrawFrameControl(
	HDC,
	LPRECT,
	UINT,
	UINT);

#define DC_ACTIVE           0x0001
#define DC_SMALLCAP         0x0002
#define DC_ICON             0x0004
#define DC_TEXT             0x0008
#define DC_INBUTTON         0x0010
#define DC_GRADIENT         0x0020
#define DC_BUTTONS          0x1000

WINUSERAPI
BOOL
WINAPI
DrawCaption(
	HWND hwnd,
	HDC hdc,
	CONST RECT* lprect,
	UINT flags);

#define IDANI_OPEN          1
#define IDANI_CAPTION       3

WINUSERAPI
BOOL
WINAPI
DrawAnimatedRects(
	HWND hwnd,
	int idAni,
	CONST RECT* lprcFrom,
	CONST RECT* lprcTo);

#define CF_TEXT             1
#define CF_BITMAP           2
#define CF_METAFILEPICT     3
#define CF_SYLK             4
#define CF_DIF              5
#define CF_TIFF             6
#define CF_OEMTEXT          7
#define CF_DIB              8
#define CF_PALETTE          9
#define CF_PENDATA          10
#define CF_RIFF             11
#define CF_WAVE             12
#define CF_UNICODETEXT      13
#define CF_ENHMETAFILE      14

#define CF_HDROP            15
#define CF_LOCALE           16

#define CF_DIBV5            17

#define CF_MAX              18

#define CF_OWNERDISPLAY     0x0080
#define CF_DSPTEXT          0x0081
#define CF_DSPBITMAP        0x0082
#define CF_DSPMETAFILEPICT  0x0083
#define CF_DSPENHMETAFILE   0x008E

#define CF_PRIVATEFIRST     0x0200
#define CF_PRIVATELAST      0x02FF

#define CF_GDIOBJFIRST      0x0300
#define CF_GDIOBJLAST       0x03FF

#define FVIRTKEY  TRUE          /* Assumed to be == TRUE */
#define FNOINVERT 0x02
#define FSHIFT    0x04
#define FCONTROL  0x08
#define FALT      0x10

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagWNDCLASSA {
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCSTR lpszMenuName;
	LPCSTR lpszClassName;
} WNDCLASSA, * PWNDCLASSA, * NPWNDCLASSA, * LPWNDCLASSA;

typedef struct tagWNDCLASSW {
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCWSTR lpszMenuName;
	LPCWSTR lpszClassName;
} WNDCLASSW, * PWNDCLASSW, * NPWNDCLASSW, * LPWNDCLASSW;

typedef struct tagWNDCLASSEXA {
	UINT cbSize;
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCSTR lpszMenuName;
	LPCSTR lpszClassName;
	HICON hIconSm;
} WNDCLASSEXA, * PWNDCLASSEXA, * NPWNDCLASSEXA, * LPWNDCLASSEXA;

typedef struct tagWNDCLASSEXW {
	UINT cbSize;
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCWSTR lpszMenuName;
	LPCWSTR lpszClassName;
	HICON hIconSm;
} WNDCLASSEXW, * PWNDCLASSEXW, * NPWNDCLASSEXW, * LPWNDCLASSEXW;

typedef struct tagMSG {
	HWND hwnd;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
	DWORD time;
	POINT pt;
} MSG, * PMSG, * NPMSG, * LPMSG;

#define POINTSTOPOINT(pt,pts) { (pt).x = (LONG)(SHORT)LOWORD(*(LONG*)&pts); (pt).y = (LONG)(SHORT)HIWORD(*(LONG*)&pts); }

#define POINTTOPOINTS(pt) (MAKELONG((short)((pt).x),(short)((pt).y)))
#define MAKEWPARAM(l,h) ((WPARAM)(DWORD)MAKELONG(l,h))
#define MAKELPARAM(l,h) ((LPARAM)(DWORD)MAKELONG(l,h))
#define MAKELRESULT(l,h) ((LRESULT)(DWORD)MAKELONG(l,h))

#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)
#define GWL_ID              (-12)
#if ARCHITECTURE_X86
#define GWL_WNDPROC         (-4)
#define GWL_HINSTANCE       (-6)
#define GWL_HWNDPARENT      (-8)
#define GWL_USERDATA        (-21)
#endif

#define GWLP_WNDPROC        (-4)
#define GWLP_HINSTANCE      (-6)
#define GWLP_HWNDPARENT     (-8)
#define GWLP_USERDATA       (-21)
#define GWLP_ID             (-12)

typedef struct tagACCEL {
	BYTE   fVirt;               /* Also called the flags field */
	WORD   key;
	WORD   cmd;
} ACCEL, * LPACCEL;

typedef struct tagCREATESTRUCTA {
	LPVOID      lpCreateParams;
	HINSTANCE   hInstance;
	HMENU       hMenu;
	HWND        hwndParent;
	int         cy;
	int         cx;
	int         y;
	int         x;
	LONG        style;
	LPCSTR      lpszName;
	LPCSTR      lpszClass;
	DWORD       dwExStyle;
} CREATESTRUCTA, * LPCREATESTRUCTA;

typedef struct tagCREATESTRUCTW {
	LPVOID      lpCreateParams;
	HINSTANCE   hInstance;
	HMENU       hMenu;
	HWND        hwndParent;
	int         cy;
	int         cx;
	int         y;
	int         x;
	LONG        style;
	LPCWSTR     lpszName;
	LPCWSTR     lpszClass;
	DWORD       dwExStyle;
} CREATESTRUCTW, * LPCREATESTRUCTW;

#define WPF_SETMINPOSITION          0x0001
#define WPF_RESTORETOMAXIMIZED      0x0002
#define WPF_ASYNCWINDOWPLACEMENT    0x0004

typedef struct tagNMHDR
{
	HWND      hwndFrom;
	UINT_PTR  idFrom;
	UINT      code;         // NM_ code
}   NMHDR;
typedef NMHDR FAR* LPNMHDR;

typedef struct tagSTYLESTRUCT
{
	DWORD   styleOld;
	DWORD   styleNew;
} STYLESTRUCT, * LPSTYLESTRUCT;

#define ODT_MENU        1
#define ODT_LISTBOX     2
#define ODT_COMBOBOX    3
#define ODT_BUTTON      4
#define ODT_STATIC      5

#define ODA_DRAWENTIRE  0x0001
#define ODA_SELECT      0x0002
#define ODA_FOCUS       0x0004

#define ODS_SELECTED    0x0001
#define ODS_GRAYED      0x0002
#define ODS_DISABLED    0x0004
#define ODS_CHECKED     0x0008
#define ODS_FOCUS       0x0010
#define ODS_DEFAULT         0x0020
#define ODS_COMBOBOXEDIT    0x1000
#define ODS_HOTLIGHT        0x0040
#define ODS_INACTIVE        0x0080
#define ODS_NOACCEL         0x0100
#define ODS_NOFOCUSRECT     0x0200

typedef struct tagMEASUREITEMSTRUCT {
	UINT       CtlType;
	UINT       CtlID;
	UINT       itemID;
	UINT       itemWidth;
	UINT       itemHeight;
	ULONG_PTR  itemData;
} MEASUREITEMSTRUCT, NEAR* PMEASUREITEMSTRUCT, FAR* LPMEASUREITEMSTRUCT;

typedef struct tagDRAWITEMSTRUCT {
	UINT        CtlType;
	UINT        CtlID;
	UINT        itemID;
	UINT        itemAction;
	UINT        itemState;
	HWND        hwndItem;
	HDC         hDC;
	RECT        rcItem;
	ULONG_PTR   itemData;
} DRAWITEMSTRUCT, NEAR* PDRAWITEMSTRUCT, FAR* LPDRAWITEMSTRUCT;

typedef struct tagDELETEITEMSTRUCT {
	UINT       CtlType;
	UINT       CtlID;
	UINT       itemID;
	HWND       hwndItem;
	ULONG_PTR  itemData;
} DELETEITEMSTRUCT, NEAR* PDELETEITEMSTRUCT, FAR* LPDELETEITEMSTRUCT;

typedef struct tagCOMPAREITEMSTRUCT {
	UINT        CtlType;
	UINT        CtlID;
	HWND        hwndItem;
	UINT        itemID1;
	ULONG_PTR   itemData1;
	UINT        itemID2;
	ULONG_PTR   itemData2;
	DWORD       dwLocaleId;
} COMPAREITEMSTRUCT, NEAR* PCOMPAREITEMSTRUCT, FAR* LPCOMPAREITEMSTRUCT;

WINUSERAPI
BOOL
WINAPI
GetMessageA(
	LPMSG lpMsg,
	HWND hWnd,
	UINT wMsgFilterMin,
	UINT wMsgFilterMax);

WINUSERAPI
BOOL
WINAPI
GetMessageW(
	LPMSG lpMsg,
	HWND hWnd,
	UINT wMsgFilterMin,
	UINT wMsgFilterMax);

#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
#define SW_FORCEMINIMIZE    11
#define SW_MAX              11

#define SW_PARENTCLOSING    1
#define SW_OTHERZOOM        2
#define SW_PARENTOPENING    3
#define SW_OTHERUNZOOM      4

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

#define MOD_ALT             0x0001
#define MOD_CONTROL         0x0002
#define MOD_SHIFT           0x0004
#define MOD_WIN             0x0008
#if(WINVER >= 0x0601)
#define MOD_NOREPEAT        0x4000
#endif /* WINVER >= 0x0601 */

WINUSERAPI
BOOL
WINAPI
PostMessageA(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
PostMessageW(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
PostThreadMessageA(
	DWORD idThread,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);

WINUSERAPI
BOOL
WINAPI
PostThreadMessageW(
	DWORD idThread,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);

#define HWND_BROADCAST  ((HWND)0xffff)

#if(WINVER >= 0x0500)
#define HWND_MESSAGE     ((HWND)-3)
#endif /* WINVER >= 0x0500 */

WINUSERAPI
BOOL
WINAPI
AttachThreadInput(
	DWORD idAttach,
	DWORD idAttachTo,
	BOOL fAttach);

WINUSERAPI
BOOL
WINAPI
ReplyMessage(
	LRESULT lResult);

WINUSERAPI
BOOL
WINAPI
WaitMessage(
	VOID);

WINUSERAPI
DWORD
WINAPI
WaitForInputIdle(
	HANDLE hProcess,
	DWORD dwMilliseconds);

WINUSERAPI
LRESULT
WINAPI
DefWindowProcA(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);

WINUSERAPI
LRESULT
WINAPI
DefWindowProcW(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);

WINUSERAPI
VOID
WINAPI
PostQuitMessage(
	int nExitCode);

#ifdef STRICT
WINUSERAPI
LRESULT
WINAPI
CallWindowProcA(
	WNDPROC lpPrevWndFunc,
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);

WINUSERAPI
LRESULT
WINAPI
CallWindowProcW(
	WNDPROC lpPrevWndFunc,
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);
#else /* !STRICT */
WINUSERAPI
LRESULT
WINAPI
CallWindowProcA(
	FARPROC lpPrevWndFunc,
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);

WINUSERAPI
LRESULT
WINAPI
CallWindowProcW(
	FARPROC lpPrevWndFunc,
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam);
#endif /* !STRICT */

WINUSERAPI
ATOM
WINAPI
RegisterClassA(
	CONST WNDCLASSA* lpWndClass);

WINUSERAPI
ATOM
WINAPI
RegisterClassW(
	CONST WNDCLASSW* lpWndClass);

WINUSERAPI
BOOL
WINAPI
UnregisterClassA(
	LPCSTR lpClassName,
	HINSTANCE hInstance);

WINUSERAPI
BOOL
WINAPI
UnregisterClassW(
	LPCWSTR lpClassName,
	HINSTANCE hInstance);

WINUSERAPI
BOOL
WINAPI
GetClassInfoA(
	HINSTANCE hInstance,
	LPCSTR lpClassName,
	LPWNDCLASSA lpWndClass);

WINUSERAPI
BOOL
WINAPI
GetClassInfoW(
	HINSTANCE hInstance,
	LPCWSTR lpClassName,
	LPWNDCLASSW lpWndClass);

WINUSERAPI
ATOM
WINAPI
RegisterClassExA(
	CONST WNDCLASSEXA*);

WINUSERAPI
ATOM
WINAPI
RegisterClassExW(
	CONST WNDCLASSEXW*);


WINUSERAPI
BOOL
WINAPI
GetClassInfoExA(
	HINSTANCE hInstance,
	LPCSTR lpszClass,
	LPWNDCLASSEXA lpwcx);

WINUSERAPI
BOOL
WINAPI
GetClassInfoExW(
	HINSTANCE hInstance,
	LPCWSTR lpszClass,
	LPWNDCLASSEXW lpwcx);

#define CW_USEDEFAULT       ((int)0x80000000)
#define HWND_DESKTOP        ((HWND)0)

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

#define CTLCOLOR_MSGBOX         0
#define CTLCOLOR_EDIT           1
#define CTLCOLOR_LISTBOX        2
#define CTLCOLOR_BTN            3
#define CTLCOLOR_DLG            4
#define CTLCOLOR_SCROLLBAR      5
#define CTLCOLOR_STATIC         6
#define CTLCOLOR_MAX            7

#define COLOR_SCROLLBAR         0
#define COLOR_BACKGROUND        1
#define COLOR_ACTIVECAPTION     2
#define COLOR_INACTIVECAPTION   3
#define COLOR_MENU              4
#define COLOR_WINDOW            5
#define COLOR_WINDOWFRAME       6
#define COLOR_MENUTEXT          7
#define COLOR_WINDOWTEXT        8
#define COLOR_CAPTIONTEXT       9
#define COLOR_ACTIVEBORDER      10
#define COLOR_INACTIVEBORDER    11
#define COLOR_APPWORKSPACE      12
#define COLOR_HIGHLIGHT         13
#define COLOR_HIGHLIGHTTEXT     14
#define COLOR_BTNFACE           15
#define COLOR_BTNSHADOW         16
#define COLOR_GRAYTEXT          17
#define COLOR_BTNTEXT           18
#define COLOR_INACTIVECAPTIONTEXT 19
#define COLOR_BTNHIGHLIGHT      20

#if(WINVER >= 0x0400)
#define COLOR_3DDKSHADOW        21
#define COLOR_3DLIGHT           22
#define COLOR_INFOTEXT          23
#define COLOR_INFOBK            24
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
#define COLOR_HOTLIGHT          26
#define COLOR_GRADIENTACTIVECAPTION 27
#define COLOR_GRADIENTINACTIVECAPTION 28
#if(WINVER >= 0x0501)
#define COLOR_MENUHILIGHT       29
#define COLOR_MENUBAR           30
#endif /* WINVER >= 0x0501 */
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0400)
#define COLOR_DESKTOP           COLOR_BACKGROUND
#define COLOR_3DFACE            COLOR_BTNFACE
#define COLOR_3DSHADOW          COLOR_BTNSHADOW
#define COLOR_3DHIGHLIGHT       COLOR_BTNHIGHLIGHT
#define COLOR_3DHILIGHT         COLOR_BTNHIGHLIGHT
#define COLOR_BTNHILIGHT        COLOR_BTNHIGHLIGHT
#endif /* WINVER >= 0x0400 */

WINUSERAPI
DWORD
WINAPI
GetSysColor(
	int nIndex);

WINUSERAPI
HBRUSH
WINAPI
GetSysColorBrush(
	int nIndex);

WINUSERAPI
BOOL
WINAPI
SetSysColors(
	int cElements,
	CONST INT* lpaElements,
	CONST COLORREF* lpaRgbValues);

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

#if(WINVER >= 0x0601)

#define MSGFLTINFO_NONE                         (0)
#define MSGFLTINFO_ALREADYALLOWED_FORWND        (1)
#define MSGFLTINFO_ALREADYDISALLOWED_FORWND     (2)
#define MSGFLTINFO_ALLOWED_HIGHER               (3)

typedef struct tagCHANGEFILTERSTRUCT {
	DWORD cbSize;
	DWORD ExtStatus;
} CHANGEFILTERSTRUCT, * PCHANGEFILTERSTRUCT;

#define MSGFLT_RESET                            (0)
#define MSGFLT_ALLOW                            (1)
#define MSGFLT_DISALLOW                         (2)

WINUSERAPI
BOOL
WINAPI
ChangeWindowMessageFilterEx(
	HWND hwnd,                                         // Window
	UINT message,                                      // WM_ message
	DWORD action,                                      // Message filter action value
	PCHANGEFILTERSTRUCT pChangeFilterStruct);   // Optional

#endif /* WINVER >= 0x0601 */

#define WM_NULL                         0x0000
#define WM_CREATE                       0x0001
#define WM_DESTROY                      0x0002
#define WM_MOVE                         0x0003
#define WM_SIZE                         0x0005

#define WM_ACTIVATE                     0x0006

#define     WA_INACTIVE     0
#define     WA_ACTIVE       1
#define     WA_CLICKACTIVE  2

#define WM_SETFOCUS                     0x0007
#define WM_KILLFOCUS                    0x0008
#define WM_ENABLE                       0x000A
#define WM_SETREDRAW                    0x000B
#define WM_SETTEXT                      0x000C
#define WM_GETTEXT                      0x000D
#define WM_GETTEXTLENGTH                0x000E
#define WM_PAINT                        0x000F
#define WM_CLOSE                        0x0010

#define WM_QUERYENDSESSION              0x0011
#define WM_QUERYOPEN                    0x0013
#define WM_ENDSESSION                   0x0016

#define WM_QUIT                         0x0012
#define WM_ERASEBKGND                   0x0014
#define WM_SYSCOLORCHANGE               0x0015
#define WM_SHOWWINDOW                   0x0018
#define WM_WININICHANGE                 0x001A

#define WM_SETTINGCHANGE                WM_WININICHANGE

#define WM_DEVMODECHANGE                0x001B
#define WM_ACTIVATEAPP                  0x001C
#define WM_FONTCHANGE                   0x001D
#define WM_TIMECHANGE                   0x001E
#define WM_CANCELMODE                   0x001F
#define WM_SETCURSOR                    0x0020
#define WM_MOUSEACTIVATE                0x0021
#define WM_CHILDACTIVATE                0x0022
#define WM_QUEUESYNC                    0x0023

#define WM_GETMINMAXINFO                0x0024

typedef struct tagMINMAXINFO {
	POINT ptReserved;
	POINT ptMaxSize;
	POINT ptMaxPosition;
	POINT ptMinTrackSize;
	POINT ptMaxTrackSize;
} MINMAXINFO, * PMINMAXINFO, * LPMINMAXINFO;

#define WM_PAINTICON                    0x0026
#define WM_ICONERASEBKGND               0x0027
#define WM_NEXTDLGCTL                   0x0028
#define WM_SPOOLERSTATUS                0x002A
#define WM_DRAWITEM                     0x002B
#define WM_MEASUREITEM                  0x002C
#define WM_DELETEITEM                   0x002D
#define WM_VKEYTOITEM                   0x002E
#define WM_CHARTOITEM                   0x002F
#define WM_SETFONT                      0x0030
#define WM_GETFONT                      0x0031
#define WM_SETHOTKEY                    0x0032
#define WM_GETHOTKEY                    0x0033
#define WM_QUERYDRAGICON                0x0037
#define WM_COMPAREITEM                  0x0039

#define WM_GETOBJECT                    0x003D

#define WM_COMPACTING                   0x0041
#define WM_COMMNOTIFY                   0x0044  /* no longer suported */
#define WM_WINDOWPOSCHANGING            0x0046
#define WM_WINDOWPOSCHANGED             0x0047

#define WM_POWER                        0x0048

#define WM_COPYDATA                     0x004A
#define WM_CANCELJOURNAL                0x004B

typedef struct tagCOPYDATASTRUCT {
	ULONG_PTR dwData;
	DWORD cbData;
	PVOID lpData;
} COPYDATASTRUCT, * PCOPYDATASTRUCT;

typedef struct tagMDINEXTMENU
{
	HMENU   hmenuIn;
	HMENU   hmenuNext;
	HWND    hwndNext;
} MDINEXTMENU, * PMDINEXTMENU, FAR* LPMDINEXTMENU;

#define WM_NOTIFY                       0x004E
#define WM_INPUTLANGCHANGEREQUEST       0x0050
#define WM_INPUTLANGCHANGE              0x0051
#define WM_TCARD                        0x0052
#define WM_HELP                         0x0053
#define WM_USERCHANGED                  0x0054
#define WM_NOTIFYFORMAT                 0x0055

#define WM_CONTEXTMENU                  0x007B
#define WM_STYLECHANGING                0x007C
#define WM_STYLECHANGED                 0x007D
#define WM_DISPLAYCHANGE                0x007E
#define WM_GETICON                      0x007F
#define WM_SETICON                      0x0080

#define WM_NCCREATE                     0x0081
#define WM_NCDESTROY                    0x0082
#define WM_NCCALCSIZE                   0x0083
#define WM_NCHITTEST                    0x0084
#define WM_NCPAINT                      0x0085
#define WM_NCACTIVATE                   0x0086
#define WM_GETDLGCODE                   0x0087

#define WM_SYNCPAINT                    0x0088

#define WM_NCMOUSEMOVE                  0x00A0
#define WM_NCLBUTTONDOWN                0x00A1
#define WM_NCLBUTTONUP                  0x00A2
#define WM_NCLBUTTONDBLCLK              0x00A3
#define WM_NCRBUTTONDOWN                0x00A4
#define WM_NCRBUTTONUP                  0x00A5
#define WM_NCRBUTTONDBLCLK              0x00A6
#define WM_NCMBUTTONDOWN                0x00A7
#define WM_NCMBUTTONUP                  0x00A8
#define WM_NCMBUTTONDBLCLK              0x00A9

#define WM_NCXBUTTONDOWN                0x00AB
#define WM_NCXBUTTONUP                  0x00AC
#define WM_NCXBUTTONDBLCLK              0x00AD

#define WM_INPUT_DEVICE_CHANGE          0x00FE

#define WM_INPUT                        0x00FF

#define WM_KEYFIRST                     0x0100
#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
#define WM_DEADCHAR                     0x0103
#define WM_SYSKEYDOWN                   0x0104
#define WM_SYSKEYUP                     0x0105
#define WM_SYSCHAR                      0x0106
#define WM_SYSDEADCHAR                  0x0107

#define WM_UNICHAR                      0x0109
#define WM_KEYLAST                      0x0109

#define WM_IME_STARTCOMPOSITION         0x010D
#define WM_IME_ENDCOMPOSITION           0x010E
#define WM_IME_COMPOSITION              0x010F
#define WM_IME_KEYLAST                  0x010F

#define WM_INITDIALOG                   0x0110
#define WM_COMMAND                      0x0111
#define WM_SYSCOMMAND                   0x0112
#define WM_TIMER                        0x0113
#define WM_HSCROLL                      0x0114
#define WM_VSCROLL                      0x0115
#define WM_INITMENU                     0x0116
#define WM_INITMENUPOPUP                0x0117

#if(WINVER >= 0x0601)
#define WM_GESTURE                      0x0119
#define WM_GESTURENOTIFY                0x011A
#endif /* WINVER >= 0x0601 */

#define WM_MENUSELECT                   0x011F
#define WM_MENUCHAR                     0x0120
#define WM_ENTERIDLE                    0x0121

#define WM_MENURBUTTONUP                0x0122
#define WM_MENUDRAG                     0x0123
#define WM_MENUGETOBJECT                0x0124
#define WM_UNINITMENUPOPUP              0x0125
#define WM_MENUCOMMAND                  0x0126

#define WM_CHANGEUISTATE                0x0127
#define WM_UPDATEUISTATE                0x0128
#define WM_QUERYUISTATE                 0x0129

#define UIS_SET                         1
#define UIS_CLEAR                       2
#define UIS_INITIALIZE                  3

#define UISF_HIDEFOCUS                  0x1
#define UISF_HIDEACCEL                  0x2

#define UISF_ACTIVE                     0x4

#define WM_CTLCOLORMSGBOX               0x0132
#define WM_CTLCOLOREDIT                 0x0133
#define WM_CTLCOLORLISTBOX              0x0134
#define WM_CTLCOLORBTN                  0x0135
#define WM_CTLCOLORDLG                  0x0136
#define WM_CTLCOLORSCROLLBAR            0x0137
#define WM_CTLCOLORSTATIC               0x0138
#define MN_GETHMENU                     0x01E1

#define WM_MOUSEFIRST                   0x0200
#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209

#define WM_MOUSEWHEEL                   0x020A

#define WM_XBUTTONDOWN                  0x020B
#define WM_XBUTTONUP                    0x020C
#define WM_XBUTTONDBLCLK                0x020D

#define WM_MOUSEHWHEEL                  0x020E

#define WM_MOUSELAST                    0x020E

#define WHEEL_DELTA                     120

#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))

#define WHEEL_PAGESCROLL                (UINT_MAX)

#define GET_KEYSTATE_WPARAM(wParam)     (LOWORD(wParam))
#define GET_NCHITTEST_WPARAM(wParam)    ((short)LOWORD(wParam))
#define GET_XBUTTON_WPARAM(wParam)      (HIWORD(wParam))

#define XBUTTON1      0x0001
#define XBUTTON2      0x0002

#define WM_PARENTNOTIFY                 0x0210
#define WM_ENTERMENULOOP                0x0211
#define WM_EXITMENULOOP                 0x0212

#define WM_NEXTMENU                     0x0213
#define WM_SIZING                       0x0214
#define WM_CAPTURECHANGED               0x0215
#define WM_MOVING                       0x0216

#define WM_POWERBROADCAST               0x0218

#define PBT_APMQUERYSUSPEND             0x0000
#define PBT_APMQUERYSTANDBY             0x0001

#define PBT_APMQUERYSUSPENDFAILED       0x0002
#define PBT_APMQUERYSTANDBYFAILED       0x0003

#define PBT_APMSUSPEND                  0x0004
#define PBT_APMSTANDBY                  0x0005

#define PBT_APMRESUMECRITICAL           0x0006
#define PBT_APMRESUMESUSPEND            0x0007
#define PBT_APMRESUMESTANDBY            0x0008

#define PBTF_APMRESUMEFROMFAILURE       0x00000001

#define PBT_APMBATTERYLOW               0x0009
#define PBT_APMPOWERSTATUSCHANGE        0x000A

#define PBT_APMOEMEVENT                 0x000B

#define PBT_APMRESUMEAUTOMATIC          0x0012

#ifndef PBT_POWERSETTINGCHANGE
#define PBT_POWERSETTINGCHANGE          0x8013

typedef struct {
	GUID PowerSetting;
	DWORD DataLength;
	UCHAR Data[1];
} POWERBROADCAST_SETTING, * PPOWERBROADCAST_SETTING;

#endif // PBT_POWERSETTINGCHANGE

#define WM_DEVICECHANGE                 0x0219

#define WM_MDICREATE                    0x0220
#define WM_MDIDESTROY                   0x0221
#define WM_MDIACTIVATE                  0x0222
#define WM_MDIRESTORE                   0x0223
#define WM_MDINEXT                      0x0224
#define WM_MDIMAXIMIZE                  0x0225
#define WM_MDITILE                      0x0226
#define WM_MDICASCADE                   0x0227
#define WM_MDIICONARRANGE               0x0228
#define WM_MDIGETACTIVE                 0x0229


#define WM_MDISETMENU                   0x0230
#define WM_ENTERSIZEMOVE                0x0231
#define WM_EXITSIZEMOVE                 0x0232
#define WM_DROPFILES                    0x0233
#define WM_MDIREFRESHMENU               0x0234

#if(WINVER >= 0x0602)
#define WM_POINTERDEVICECHANGE          0x238
#define WM_POINTERDEVICEINRANGE         0x239
#define WM_POINTERDEVICEOUTOFRANGE      0x23A
#endif /* WINVER >= 0x0602 */

#if(WINVER >= 0x0601)
#define WM_TOUCH                        0x0240
#endif /* WINVER >= 0x0601 */

#if(WINVER >= 0x0602)
#define WM_NCPOINTERUPDATE              0x0241
#define WM_NCPOINTERDOWN                0x0242
#define WM_NCPOINTERUP                  0x0243
#define WM_POINTERUPDATE                0x0245
#define WM_POINTERDOWN                  0x0246
#define WM_POINTERUP                    0x0247
#define WM_POINTERENTER                 0x0249
#define WM_POINTERLEAVE                 0x024A
#define WM_POINTERACTIVATE              0x024B
#define WM_POINTERCAPTURECHANGED        0x024C
#define WM_TOUCHHITTESTING              0x024D
#define WM_POINTERWHEEL                 0x024E
#define WM_POINTERHWHEEL                0x024F
#define DM_POINTERHITTEST               0x0250
#define WM_POINTERROUTEDTO              0x0251
#define WM_POINTERROUTEDAWAY            0x0252
#define WM_POINTERROUTEDRELEASED        0x0253
#endif /* WINVER >= 0x0602 */

#define WM_IME_SETCONTEXT               0x0281
#define WM_IME_NOTIFY                   0x0282
#define WM_IME_CONTROL                  0x0283
#define WM_IME_COMPOSITIONFULL          0x0284
#define WM_IME_SELECT                   0x0285
#define WM_IME_CHAR                     0x0286

#define WM_IME_REQUEST                  0x0288

#define WM_IME_KEYDOWN                  0x0290
#define WM_IME_KEYUP                    0x0291

#define WM_MOUSEHOVER                   0x02A1
#define WM_MOUSELEAVE                   0x02A3

#define WM_NCMOUSEHOVER                 0x02A0
#define WM_NCMOUSELEAVE                 0x02A2

#define WM_WTSSESSION_CHANGE            0x02B1

#define WM_TABLET_FIRST                 0x02c0
#define WM_TABLET_LAST                  0x02df

#if(WINVER >= 0x0601)
#define WM_DPICHANGED                   0x02E0
#endif /* WINVER >= 0x0601 */

#if(WINVER >= 0x0605)
#define WM_DPICHANGED_BEFOREPARENT      0x02E2
#define WM_DPICHANGED_AFTERPARENT       0x02E3
#define WM_GETDPISCALEDSIZE             0x02E4
#endif /* WINVER >= 0x0605 */

#define WM_CUT                          0x0300
#define WM_COPY                         0x0301
#define WM_PASTE                        0x0302
#define WM_CLEAR                        0x0303
#define WM_UNDO                         0x0304
#define WM_RENDERFORMAT                 0x0305
#define WM_RENDERALLFORMATS             0x0306
#define WM_DESTROYCLIPBOARD             0x0307
#define WM_DRAWCLIPBOARD                0x0308
#define WM_PAINTCLIPBOARD               0x0309
#define WM_VSCROLLCLIPBOARD             0x030A
#define WM_SIZECLIPBOARD                0x030B
#define WM_ASKCBFORMATNAME              0x030C
#define WM_CHANGECBCHAIN                0x030D
#define WM_HSCROLLCLIPBOARD             0x030E
#define WM_QUERYNEWPALETTE              0x030F
#define WM_PALETTEISCHANGING            0x0310
#define WM_PALETTECHANGED               0x0311
#define WM_HOTKEY                       0x0312

#define WM_PRINT                        0x0317
#define WM_PRINTCLIENT                  0x0318

#define WM_APPCOMMAND                   0x0319

#define WM_THEMECHANGED                 0x031A

#define WM_CLIPBOARDUPDATE              0x031D

#if(_WIN32_WINNT >= 0x0600)
#define WM_DWMCOMPOSITIONCHANGED        0x031E
#define WM_DWMNCRENDERINGCHANGED        0x031F
#define WM_DWMCOLORIZATIONCOLORCHANGED  0x0320
#define WM_DWMWINDOWMAXIMIZEDCHANGE     0x0321
#endif /* _WIN32_WINNT >= 0x0600 */

#if(_WIN32_WINNT >= 0x0601)
#define WM_DWMSENDICONICTHUMBNAIL           0x0323
#define WM_DWMSENDICONICLIVEPREVIEWBITMAP   0x0326
#endif /* _WIN32_WINNT >= 0x0601 */

#if(WINVER >= 0x0600)
#define WM_GETTITLEBARINFOEX            0x033F
#endif /* WINVER >= 0x0600 */

#define WM_HANDHELDFIRST                0x0358
#define WM_HANDHELDLAST                 0x035F

#define WM_AFXFIRST                     0x0360
#define WM_AFXLAST                      0x037F

#define WM_PENWINFIRST                  0x0380
#define WM_PENWINLAST                   0x038F

#define WM_APP                          0x8000

#define WM_USER                         0x0400

#define WMSZ_LEFT           1
#define WMSZ_RIGHT          2
#define WMSZ_TOP            3
#define WMSZ_TOPLEFT        4
#define WMSZ_TOPRIGHT       5
#define WMSZ_BOTTOM         6
#define WMSZ_BOTTOMLEFT     7
#define WMSZ_BOTTOMRIGHT    8

#define HTERROR             (-2)
#define HTTRANSPARENT       (-1)
#define HTNOWHERE           0
#define HTCLIENT            1
#define HTCAPTION           2
#define HTSYSMENU           3
#define HTGROWBOX           4
#define HTSIZE              HTGROWBOX
#define HTMENU              5
#define HTHSCROLL           6
#define HTVSCROLL           7
#define HTMINBUTTON         8
#define HTMAXBUTTON         9
#define HTLEFT              10
#define HTRIGHT             11
#define HTTOP               12
#define HTTOPLEFT           13
#define HTTOPRIGHT          14
#define HTBOTTOM            15
#define HTBOTTOMLEFT        16
#define HTBOTTOMRIGHT       17
#define HTBORDER            18
#define HTREDUCE            HTMINBUTTON
#define HTZOOM              HTMAXBUTTON
#define HTSIZEFIRST         HTLEFT
#define HTSIZELAST          HTBOTTOMRIGHT
#define HTOBJECT            19
#define HTCLOSE             20
#define HTHELP              21

#define SMTO_NORMAL         0x0000
#define SMTO_BLOCK          0x0001
#define SMTO_ABORTIFHUNG    0x0002
#define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
#define SMTO_ERRORONEXIT    0x0020

#define MA_ACTIVATE         1
#define MA_ACTIVATEANDEAT   2
#define MA_NOACTIVATE       3
#define MA_NOACTIVATEANDEAT 4

#define ICON_SMALL          0
#define ICON_BIG            1
#define ICON_SMALL2         2

WINUSERAPI
UINT
WINAPI
RegisterWindowMessageA(
	LPCSTR lpString);

WINUSERAPI
UINT
WINAPI
RegisterWindowMessageW(
	LPCWSTR lpString);

#define SIZE_RESTORED       0
#define SIZE_MINIMIZED      1
#define SIZE_MAXIMIZED      2
#define SIZE_MAXSHOW        3
#define SIZE_MAXHIDE        4

typedef struct tagWINDOWPOS {
	HWND    hwnd;
	HWND    hwndInsertAfter;
	int     x;
	int     y;
	int     cx;
	int     cy;
	UINT    flags;
} WINDOWPOS, * LPWINDOWPOS, * PWINDOWPOS;

typedef struct tagNCCALCSIZE_PARAMS {
	RECT       rgrc[3];
	PWINDOWPOS lppos;
} NCCALCSIZE_PARAMS, * LPNCCALCSIZE_PARAMS;

#define WVR_ALIGNTOP        0x0010
#define WVR_ALIGNLEFT       0x0020
#define WVR_ALIGNBOTTOM     0x0040
#define WVR_ALIGNRIGHT      0x0080
#define WVR_HREDRAW         0x0100
#define WVR_VREDRAW         0x0200
#define WVR_REDRAW         (WVR_HREDRAW | \
							WVR_VREDRAW)
#define WVR_VALIDRECTS      0x0400

#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010
#define MK_XBUTTON1         0x0020
#define MK_XBUTTON2         0x0040

#ifndef NOTRACKMOUSEEVENT

#define TME_HOVER       0x00000001
#define TME_LEAVE       0x00000002
#define TME_NONCLIENT   0x00000010
#define TME_QUERY       0x40000000
#define TME_CANCEL      0x80000000
#define HOVER_DEFAULT   0xFFFFFFFF

typedef struct tagTRACKMOUSEEVENT {
	DWORD cbSize;
	DWORD dwFlags;
	HWND  hwndTrack;
	DWORD dwHoverTime;
} TRACKMOUSEEVENT, * LPTRACKMOUSEEVENT;

WINUSERAPI
BOOL
WINAPI
TrackMouseEvent(
	LPTRACKMOUSEEVENT lpEventTrack);

#endif /* !NOTRACKMOUSEEVENT */


}
#else
#include <WinUser.h>
#endif

#ifndef WM_COPYGLOBALDATA
#define WM_COPYGLOBALDATA 0x0049
#endif


#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif

#endif /* CORE_WIN32_USER_H */
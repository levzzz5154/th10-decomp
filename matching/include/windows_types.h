#ifndef WINDOWS_TYPES_H
#define WINDOWS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================
 * Minimal Windows type definitions for MSVC 7.1 (Visual C++ 2003)
 * Covers all types used by th10.exe decompilation
 * ================================================================ */

/* --- Calling conventions --- */
#define WINAPI      __stdcall
#define CALLBACK    __stdcall
#define APIENTRY    __stdcall

#ifndef FAR
#define FAR
#endif
#ifndef NEAR
#define NEAR
#endif

/* --- Basic integer types --- */
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
typedef long                LONG;
typedef unsigned long       ULONG;
typedef int                 INT;
typedef unsigned int        UINT;
typedef short               SHORT;
typedef unsigned short      USHORT;
typedef char                CHAR;
typedef unsigned short      WCHAR;

typedef void                VOID;
typedef void *              PVOID;
typedef void *              LPVOID;
typedef const void *        LPCVOID;
typedef void *              HANDLE;
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name

/* --- Extended integer types --- */
typedef unsigned int        SIZE_T;
typedef int                 SSIZE_T;
typedef unsigned int        UINT_PTR;
typedef long                LONG_PTR;
typedef unsigned long       ULONG_PTR;
typedef ULONG_PTR           DWORD_PTR;
typedef LONG_PTR            INT_PTR;

/* --- Constants --- */
#ifndef NULL
#define NULL 0
#endif
#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define MAX_PATH 260

/* --- String pointer types --- */
typedef const CHAR *        LPCSTR;
typedef CHAR *              LPSTR;
typedef const WCHAR *       LPCWSTR;
typedef WCHAR *             LPWSTR;
typedef BYTE *              LPBYTE;

/* --- Handle types --- */
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE           HMODULE;
DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE(HCURSOR);
DECLARE_HANDLE(HICON);
DECLARE_HANDLE(HMENU);
DECLARE_HANDLE(HBRUSH);
DECLARE_HANDLE(HFONT);
DECLARE_HANDLE(HGDIOBJ);
DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HPALETTE);
DECLARE_HANDLE(HMONITOR);
DECLARE_HANDLE(HKEY);
typedef HKEY *              PHKEY;
DECLARE_HANDLE(HRGN);

/* --- Message/result types --- */
typedef LONG_PTR            LPARAM;
typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LRESULT;
typedef LONG                HRESULT;
typedef WORD                ATOM;

/* --- Security types --- */
typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

/* --- Critical section --- */
typedef void *              LPCRITICAL_SECTION;

/* --- DWORD pointer --- */
typedef DWORD *             LPDWORD;
typedef DWORD *             PDWORD;

/* --- REGSAM (registry access mask) --- */
typedef DWORD               REGSAM;
typedef DWORD               ACCESS_MASK;

/* --- Callback function types --- */
typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef INT_PTR (CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef VOID (CALLBACK *TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);

/* --- Structure types --- */
typedef struct tagRECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT, *LPRECT;

typedef struct tagPOINT {
    LONG x;
    LONG y;
} POINT, *LPPOINT;

typedef struct tagSIZE {
    LONG cx;
    LONG cy;
} SIZE, *LPSIZE;

typedef struct tagMSG {
    HWND   hwnd;
    UINT   message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD  time;
    POINT  pt;
} MSG, *LPMSG;

typedef struct tagWNDCLASSA {
    UINT      style;
    WNDPROC   lpfnWndProc;
    int       cbClsExtra;
    int       cbWndExtra;
    HINSTANCE hInstance;
    HICON     hIcon;
    HCURSOR   hCursor;
    HBRUSH    hbrBackground;
    LPCSTR    lpszMenuName;
    LPCSTR    lpszClassName;
} WNDCLASSA, *PWNDCLASSA;

typedef struct tagWNDCLASSEXA {
    UINT      cbSize;
    UINT      style;
    WNDPROC   lpfnWndProc;
    int       cbClsExtra;
    int       cbWndExtra;
    HINSTANCE hInstance;
    HICON     hIcon;
    HCURSOR   hCursor;
    HBRUSH    hbrBackground;
    LPCSTR    lpszMenuName;
    LPCSTR    lpszClassName;
    HICON     hIconSm;
} WNDCLASSEXA, *PWNDCLASSEXA;

typedef struct tagPAINTSTRUCT {
    HDC  hdc;
    BOOL fErase;
    RECT rcPaint;
    BOOL fRestore;
    BOOL fIncUpdate;
    BYTE rgbReserved[32];
} PAINTSTRUCT, *LPPAINTSTRUCT;

typedef struct _OSVERSIONINFOA {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    CHAR  szCSDVersion[128];
} OSVERSIONINFOA, *LPOSVERSIONINFOA;

typedef struct _STARTUPINFOA {
    DWORD  cb;
    LPSTR  lpReserved;
    LPSTR  lpDesktop;
    LPSTR  lpTitle;
    DWORD  dwX;
    DWORD  dwY;
    DWORD  dwXSize;
    DWORD  dwYSize;
    DWORD  dwXCountChars;
    DWORD  dwYCountChars;
    DWORD  dwFillAttribute;
    DWORD  dwFlags;
    WORD   wShowWindow;
    WORD   cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;

/* --- SystemParametersInfoA constants --- */
#define SPI_GETWORKAREA         0x0030
#define SPI_SETWORKAREA         0x002F
#define SPI_GETMOUSE            0x0003
#define SPI_SETMOUSE            0x0004
#define SPI_GETMOUSESPEED       0x0070
#define SPI_SETMOUSESPEED       0x0071
#define SPI_GETSCREENSAVETIMEOUT 0x000E
#define SPI_SETSCREENSAVETIMEOUT 0x000F
#define SPI_GETSCREENSAVEACTIVE 0x0010
#define SPI_SETSCREENSAVEACTIVE 0x0011
#define SPI_GETKEYBOARDDELAY    0x0016
#define SPI_SETKEYBOARDDELAY    0x0017
#define SPI_GETKEYBOARDSPEED    0x000A
#define SPI_SETKEYBOARDSPEED    0x000B
#define SPI_GETDOUBLECLICKTIME  0x0068
#define SPI_SETDOUBLECLICKTIME  0x0069
#define SPI_GETDOUBLECLKWIDTH   0x0074
#define SPI_SETDOUBLECLKWIDTH   0x0075
#define SPI_GETDOUBLECLKHEIGHT  0x0076
#define SPI_SETDOUBLECLKHEIGHT  0x0077
#define SPI_SETLOWPOWERACTIVE   0x0055
#define SPI_SETPOWEROFFACTIVE   0x0056
#define SPI_SETLOWPOWERTIMEOUT  0x004F
#define SPI_SETPOWEROFFTIMEOUT  0x0050
#define SPI_GETBEEP             0x0001
#define SPI_SETBEEP             0x0002

/* --- Window message constants --- */
#define WM_CLOSE                0x0010
#define WM_QUIT                 0x0012
#define WM_SETCURSOR            0x0020
#define WM_ACTIVATE             0x0006
#define WM_LBUTTONDOWN          0x0201
#define WM_DESTROY              0x0002
#define WM_SIZE                 0x0005
#define WM_SYSCOMMAND           0x0112
#define WM_ACTIVATEAPP          0x001C
#define WM_DEVICECHANGE         0x0219

/* --- Window style constants --- */
#define WS_OVERLAPPEDWINDOW     0x00CF0000
#define WS_POPUP                0x80000000
#define WS_VISIBLE              0x10000000

/* --- System metric constants --- */
#define SM_CXSCREEN             0
#define SM_CYSCREEN             1
#define SM_CXFULLSCREEN         16
#define SM_CYFULLSCREEN         17
#define SM_CXEDGE               45
#define SM_CYEDGE               46
#define SM_CXMIN                28
#define SM_CYMIN                29

/* --- Window messages used by ZUN --- */
#define SC_MONITORPOWER         0xF170
#define SC_SCREENSAVE           0xF140
#define WM_ENTERMENULOOP        0x0211
#define WM_EXITMENULOOP         0x0212

/* --- ShowWindow constants --- */
#define SW_HIDE                 0
#define SW_SHOWNORMAL           1
#define SW_SHOWMINIMIZED        2
#define SW_SHOWMAXIMIZED        3
#define SW_SHOWNOACTIVATE       4
#define SW_SHOW                 5
#define SW_MINIMIZE             6
#define SW_SHOWMINNOACTIVE      7
#define SW_SHOWNA               8
#define SW_RESTORE              9

/* --- MB_OK constants --- */
#define MB_OK                   0x00000000
#define MB_ICONERROR            0x00000010

/* --- IDI_APPLICATION --- */
#define IDI_APPLICATION         ((LPCSTR)32512)

/* --- COLOR constants for GetStockObject --- */
#define BLACK_BRUSH             4
#define WHITE_BRUSH             0
#define NULL_BRUSH              5
#define GRAY_BRUSH              2
#define LTGRAY_BRUSH            1
#define DKGRAY_BRUSH            3

/* --- Large integer (MSVC 7.1 uses __int64, not long long) --- */
typedef __int64             LONGLONG;
typedef unsigned __int64    ULONGLONG;
typedef union _LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG  HighPart;
    };
    LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

/* --- LCID type --- */
typedef DWORD LCID;

/* --- HLOCAL type --- */
typedef HANDLE HLOCAL;

/* --- PLONG pointer --- */
typedef LONG *PLONG;

/* --- Exception types --- */
typedef struct _EXCEPTION_POINTERS {
    void *ExceptionRecord;
    void *ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;

/* ================================================================
 * Windows API function declarations (CRT entry + GameMain usage)
 * ================================================================ */

/* kernel32 */
VOID WINAPI GetVersionExA(LPOSVERSIONINFOA lpVersionInfo);
HANDLE WINAPI GetModuleHandleA(LPCSTR lpModuleName);
LPSTR WINAPI GetCommandLineA(void);
VOID WINAPI GetStartupInfoA(LPSTARTUPINFOA lpStartupInfo);
VOID WINAPI Sleep(DWORD dwMilliseconds);
VOID WINAPI ExitProcess(UINT uExitCode);
HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize,
                           LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter,
                           DWORD dwCreationFlags, LPDWORD lpThreadId);
DWORD WINAPI WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
VOID WINAPI InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
VOID WINAPI DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
VOID WINAPI EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
VOID WINAPI LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
BOOL WINAPI CloseHandle(HANDLE hObject);
VOID WINAPI SetLastError(DWORD dwErrCode);
DWORD WINAPI GetLastError(void);
HANDLE WINAPI GetStdHandle(DWORD nStdHandle);
BOOL WINAPI PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
BOOL WINAPI TranslateMessage(const MSG *lpMsg);
LRESULT WINAPI DispatchMessageA(const MSG *lpMsg);
BOOL WINAPI GetSystemInfo(LPVOID lpSystemInfo);
BOOL WINAPI VirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
BOOL WINAPI VirtualQuery(LPCVOID lpAddress, LPVOID lpBuffer, SIZE_T dwLength);
BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
DWORD WINAPI GetTickCount(void);
DWORD WINAPI GetFileType(HANDLE hFile);
HANDLE WINAPI CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                          LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
                          DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
                     LPDWORD lpNumberOfBytesRead, LPVOID lpOverlapped);
BOOL WINAPI WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
                      LPDWORD lpNumberOfBytesWritten, LPVOID lpOverlapped);
DWORD WINAPI SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh,
                            DWORD dwMoveMethod);
DWORD WINAPI GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
BOOL WINAPI DeleteFileA(LPCSTR lpFileName);
DWORD WINAPI GetModuleFileNameA(HANDLE hModule, LPSTR lpFilename, DWORD nSize);
BOOL WINAPI CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine,
                           LPSECURITY_ATTRIBUTES lpProcessAttributes,
                           LPSECURITY_ATTRIBUTES lpThreadAttributes,
                           BOOL bInheritHandles, DWORD dwCreationFlags,
                           LPVOID lpEnvironment, LPCSTR lpCurrentDirectory,
                           LPSTARTUPINFOA lpStartupInfo, LPVOID lpProcessInformation);
BOOL WINAPI CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName);
HANDLE WINAPI CreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes, BOOL bManualReset,
                           BOOL bInitialState, LPCSTR lpName);
DWORD WINAPI ResumeThread(HANDLE hThread);
BOOL WINAPI IsValidCodePage(UINT CodePage);
BOOL WINAPI IsValidLocale(LCID Locale, DWORD dwFlags);
HANDLE WINAPI FindFirstFileA(LPCSTR lpFileName, LPVOID lpFindFileData);
BOOL WINAPI FindNextFileA(HANDLE hFindFile, LPVOID lpFindFileData);
BOOL WINAPI FindClose(HANDLE hFindFile);
LPVOID WINAPI LocalFree(HLOCAL hMem);
DWORD WINAPI FormatMessageA(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId,
                            LPSTR lpBuffer, DWORD nSize, LPVOID Arguments);

/* user32 */
ATOM WINAPI RegisterClassA(const WNDCLASSA *lpWndClass);
BOOL WINAPI UnregisterClassA(LPCSTR lpClassName, HINSTANCE hInstance);
HWND WINAPI CreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName,
                            DWORD dwStyle, int X, int Y, int nWidth, int nHeight,
                            HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
BOOL WINAPI DestroyWindow(HWND hWnd);
BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow);
BOOL WINAPI MoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint);
LRESULT WINAPI SendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL WINAPI GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
int WINAPI MessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
BOOL WINAPI SetForegroundWindow(HWND hWnd);
BOOL WINAPI SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
HCURSOR WINAPI LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName);
int WINAPI ShowCursor(BOOL bShow);
HCURSOR WINAPI SetCursor(HCURSOR hCursor);
HGDIOBJ WINAPI GetStockObject(int fnObject);
BOOL WINAPI SystemParametersInfoA(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni);
BOOL WINAPI WINNLSEnableIME(HWND hWnd, BOOL fEnable);
INT_PTR WINAPI DialogBoxParamA(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent,
                               DLGPROC lpDialogFunc, LPARAM dwInitParam);
int WINAPI GetSystemMetrics(int nIndex);

/* gdi32 */
int WINAPI GetDeviceCaps(HDC hdc, int nIndex);

/* --- CRT function declarations --- */
int __cdecl _heap_init(void);
int __cdecl _mtinit(void);
void __cdecl __RTC_Initialize(void);
int __cdecl _ioinit(void);
void __cdecl _amsg_exit(int errnum);
void __cdecl __cexit(void);
void __cdecl _exit(int status);
int __cdecl __setargv(void);
int __cdecl __setenvp(void);
int __cdecl _cinit(int);
void __cdecl _XcptFilter(unsigned long xcptnum, PEXCEPTION_POINTERS pxcptptrs);
LPSTR __cdecl ___crtGetEnvironmentStringsA(void);
LPSTR __cdecl __wincmdln(void);
void __cdecl fast_error_exit(int);

#ifdef __cplusplus
}
#endif

#endif /* WINDOWS_TYPES_H */

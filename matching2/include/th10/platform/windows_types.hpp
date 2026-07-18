// =============================================================================
// windows_types.hpp - Windows types required by the MSVC 7.1 decompilation
// Only types actually used by th10.exe (not full windows.h)
// =============================================================================
#pragma once

typedef unsigned int        DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef void*               HANDLE;
typedef HANDLE              HINSTANCE;
typedef HANDLE              HMODULE;
typedef HANDLE              HWND;
typedef const char*         LPCSTR;
typedef char*               LPSTR;
typedef void*               LPVOID;
typedef const void*         LPCVOID;
typedef DWORD*              LPDWORD;
typedef void*               LPSECURITY_ATTRIBUTES;
typedef HANDLE              HMENU;
typedef HANDLE              HCURSOR;
typedef HANDLE              HICON;
typedef HANDLE              HBRUSH;
typedef int                 INT_PTR;
typedef long                LONG;
typedef unsigned long       ULONG;
typedef unsigned int        UINT;
typedef long long           LONGLONG;
typedef unsigned long long  ULONGLONG;
typedef void*               HGDIOBJ;
typedef unsigned short      ATOM;
typedef long                LRESULT;
typedef void*               PVOID;
typedef int                 BOOL_;
typedef unsigned int        UINT_;
typedef unsigned int        WPARAM;
typedef long                LPARAM;
typedef LRESULT (__stdcall *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

struct WNDCLASSA {
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
};

struct STARTUPINFOA {
    DWORD cb;
    LPSTR lpReserved;
    LPSTR lpDesktop;
    LPSTR lpTitle;
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    BYTE* lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
};

struct PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
};

#define NULL    0
#define TRUE    1
#define FALSE   0
#define CALLBACK __stdcall
#define WINAPI   __stdcall

// MSVC security cookie
extern "C" DWORD __security_cookie;

// Windows API stubs
extern "C" {
    HANDLE  __stdcall CreateMutexA(void*, BOOL, LPCSTR);
    DWORD   __stdcall GetLastError(void);
    __declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HMODULE, LPSTR, DWORD);
    DWORD   __stdcall GetConsoleTitleA(LPSTR, DWORD);
    void    __stdcall GetStartupInfoA(void*);
    char*   __cdecl _strrchr(const char*, int);
    int     __cdecl __stricmp(const char*, const char*);
    BOOL    __stdcall SystemParametersInfoA(UINT, UINT, void*, UINT);
    BOOL    __stdcall QueryPerformanceFrequency(long long*);
    BOOL    __stdcall QueryPerformanceCounter(long long*);
    HGDIOBJ __stdcall GetStockObject(int);
    HCURSOR __stdcall LoadCursorA(HINSTANCE, LPCSTR);
    ATOM    __stdcall RegisterClassA(const WNDCLASSA*);
    HWND    __stdcall CreateWindowExA(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
    void*   __stdcall SendMessageA(HWND, UINT, DWORD, DWORD);
    void    __stdcall Sleep(DWORD);
    int     __stdcall GetSystemMetrics(int);
    void*   __stdcall Direct3DCreate9(UINT);
    BOOL    __stdcall CreateProcessA(LPCSTR, LPSTR, LPSECURITY_ATTRIBUTES,
                                    LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID,
                                    LPCSTR, STARTUPINFOA*, PROCESS_INFORMATION*);
    BOOL    __stdcall GetExitCodeProcess(HANDLE, LPDWORD);
}

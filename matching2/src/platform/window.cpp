// =============================================================================
// window.cpp - Window creation, WndProc, system initialization
// Functions: 0x004390E0 (WndProc), 0x00439730 (CreateWindow),
//            0x004392E0 (SaveSystemSettings), 0x00439FF0 (InstanceCheck)
// =============================================================================
#include "th10/platform/window.hpp"
#include "th10/platform/midi.hpp"

// Windows API - using __declspec(dllimport) for correct import call pattern
extern "C" {
    __declspec(dllimport) int     __stdcall SetForegroundWindow(void*);
    __declspec(dllimport) int     __stdcall ShowCursor(int);
    __declspec(dllimport) void*   __stdcall SetCursor(void*);
    __declspec(dllimport) LRESULT __stdcall DefWindowProcA(HWND, UINT, WPARAM, LPARAM);
    __declspec(dllimport) LONG    __stdcall CoInitialize(LPVOID reserved);
    __declspec(dllimport) LONG    __stdcall CoCreateInstance(const void* class_id,
                                                              void* outer,
                                                              DWORD context,
                                                              const void* interface_id,
                                                              void** object);
    __declspec(dllimport) void    __stdcall CoUninitialize();
    __declspec(dllimport) int     __stdcall MultiByteToWideChar(UINT code_page,
                                                                DWORD flags,
                                                                const char* source,
                                                                int source_length,
                                                                WORD* destination,
                                                                int destination_length);
    __declspec(dllimport) UINT    __stdcall timeKillEvent(UINT timer_id);
    __declspec(dllimport) UINT    __stdcall timeEndPeriod(UINT period);
    __declspec(dllimport) UINT    __stdcall midiOutUnprepareHeader(
        HANDLE output, MidiHeader* header, UINT header_size);
    __declspec(dllimport) UINT    __stdcall midiOutReset(HANDLE output);
    __declspec(dllimport) UINT    __stdcall midiOutClose(HANDLE output);
}

extern "C" void* operator_new(DWORD size);
extern "C" void __cdecl _free(void* allocation);

// Globals
extern BYTE     DAT_00491d65;    // fullscreen flag
extern DWORD    DAT_00492500;    // cursor visible flag
extern DWORD    DAT_004924fc;    // cursor state
extern void*    DAT_00491c70;    // HWND
extern void*    g_pWnd;
extern DWORD    DAT_00491ff4;    // status flags
extern MidiManager* DAT_00491fe8; // active MIDI manager
extern DWORD    DAT_0049251c;    // saved work area
extern DWORD    DAT_00492520;    // saved SPI_53
extern DWORD    DAT_00492524;    // saved SPI_54
extern LONGLONG DAT_00492508;    // perf frequency
extern LONGLONG DAT_00492510;    // perf counter
extern char     DAT_0046f66c[];  // window title
extern void*    DAT_00497ba8;    // mutex handle
extern BYTE     DAT_00492518;    // replay flag

void Platform_LogMessage(const char* msg);
int  File_ProbePath(const char* str);

struct Guid {
    DWORD data1;
    WORD data2;
    WORD data3;
    BYTE data4[8];
};

struct ShellLink;
struct PersistFile;

struct ShellLinkVtable {
    LONG (__stdcall *QueryInterface)(ShellLink*, const Guid*, void**);
    DWORD (__stdcall *AddRef)(ShellLink*);
    DWORD (__stdcall *Release)(ShellLink*);
    LONG (__stdcall *GetPath)(ShellLink*, char*, int, void*, DWORD);
};

struct ShellLink {
    ShellLinkVtable* vtable;
};

struct PersistFileVtable {
    LONG (__stdcall *QueryInterface)(PersistFile*, const Guid*, void**);
    DWORD (__stdcall *AddRef)(PersistFile*);
    DWORD (__stdcall *Release)(PersistFile*);
    LONG (__stdcall *GetClassID)(PersistFile*, Guid*);
    LONG (__stdcall *IsDirty)(PersistFile*);
    LONG (__stdcall *Load)(PersistFile*, const WORD*, DWORD);
};

struct PersistFile {
    PersistFileVtable* vtable;
};

static const Guid kShellLinkClass = {
    0x00021401, 0, 0, {0xC0, 0, 0, 0, 0, 0, 0, 0x46}
};
static const Guid kShellLinkInterface = {
    0x000214EE, 0, 0, {0xC0, 0, 0, 0, 0, 0, 0, 0x46}
};
static const Guid kPersistFileInterface = {
    0x0000010B, 0, 0, {0xC0, 0, 0, 0, 0, 0, 0, 0x46}
};

static BOOL Succeeded(LONG result) {
    return result >= 0;
}

static void CopyString(char* destination, const char* source) {
    while ((*destination++ = *source++) != '\0') {
    }
}

static BOOL StringsEqual(const char* left, const char* right) {
    while (*left == *right) {
        if (*left == '\0') {
            return TRUE;
        }
        ++left;
        ++right;
    }
    return FALSE;
}

// ============================================================================
// 0x004392E0 - Save System Settings + Init Performance Counters
// Saves current system settings (work area, screen save, power-off), then
// sets new values. Initializes high-resolution timer.
//
// Ghidra decompilation:
//   SystemParametersInfoA(0x10, 0, &DAT_0049251c, 0)  // SPI_GETWORKAREA
//   SystemParametersInfoA(0x53, 0, &DAT_00492520, 0)
//   SystemParametersInfoA(0x54, 0, &DAT_00492524, 0)
//   SystemParametersInfoA(0x11, 0, NULL, 2)           // SPI_SETWORKAREA
//   SystemParametersInfoA(0x55, 0, NULL, 2)
//   SystemParametersInfoA(0x56, 0, NULL, 2)
//   QueryPerformanceFrequency(&DAT_00492508)
//   QueryPerformanceCounter(&DAT_00492510)
// ============================================================================
void SaveSystemSettings(void) {
    SystemParametersInfoA(0x10, 0, &DAT_0049251c, 0);
    SystemParametersInfoA(0x53, 0, &DAT_00492520, 0);
    SystemParametersInfoA(0x54, 0, &DAT_00492524, 0);
    SystemParametersInfoA(0x11, 0, 0, 2);
    SystemParametersInfoA(0x55, 0, 0, 2);
    SystemParametersInfoA(0x56, 0, 0, 2);
    QueryPerformanceFrequency(&DAT_00492508);
    QueryPerformanceCounter(&DAT_00492510);
}

// ============================================================================
// 0x004390E0 - Window Procedure
// Handles WM_SETCURSOR (0x20), WM_CLOSE (0x10), WM_QUIT (0x14),
// WM_ENTERIDLE (0x1C), WM_LBUTTONDOWN (0x201), WM_DEVICECHANGE (0x3C9).
// Ghidra decompilation:
//   if (message > 0x20): check 0x201 (SetForeground) and
//   0x3C9/MM_MOM_DONE (release the completed MIDI header)
//   if (message == 0x20): show/hide cursor based on fullscreen flag
//   if (message == 0x10): set close flag (DAT_00491ff4 |= 0x80)
//   if (message == 0x14): return 1 (swallow WM_QUIT)
//   if (message == 0x1C): track cursor visibility
//   else: DefWindowProcA
// ============================================================================
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg > 0x20) {
        if (msg == 0x201) {
            SetForegroundWindow(hwnd);
        } else if (msg == 0x3C9 && DAT_00491fe8 != 0) {
            MidiHeaderRelease(DAT_00491fe8, (MidiHeader*)lParam);
            return DefWindowProcA(hwnd, 0x3C9, wParam, lParam);
        }
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }

    if (msg == 0x20) {  // WM_SETCURSOR
        if (DAT_00491d65 == 0 && DAT_00492500 == 0) {
            ShowCursor(0);
            SetCursor(0);
            return 1;
        }
        void* hCursor = LoadCursorA(0, (const char*)0x7F00);
        SetCursor(hCursor);
        ShowCursor(1);
        return 1;
    }

    if (msg == 0x10) {  // WM_CLOSE
        DAT_00491ff4 |= 0x80;
    } else if (msg != 0x14) {  // not WM_QUIT
        if (msg == 0x1C) {  // WM_ENTERIDLE
            DAT_00492500 = (wParam == 0);
            DAT_004924fc = wParam;
            return DefWindowProcA(hwnd, 0x1C, wParam, lParam);
        }
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    return 1;  // swallow WM_QUIT
}

// ============================================================================
// 0x00439730 - Create Game Window
// Registers "BASE" window class and creates the game window.
// Windowed mode: 640x480 with WS_VISIBLE|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX
// Fullscreen: extended borderless window using GetSystemMetrics for sizing.
// The retail caller supplied HINSTANCE in EBX; the readable interface makes it
// an ordinary explicit argument.
//
// Ghidra decompilation:
//   GetStockObject(4)  // NULL_BRUSH
//   LoadCursorA(NULL, IDC_ARROW)
//   window_class.lpfnWndProc = WindowProcedure (0x004390e0)
//   RegisterClassA(&window_class)
//   if (fullscreen):
//     CreateWindowExA(0, "BASE", title, 0x100A0000, ...)
//   else:
//     CreateWindowExA(0, "BASE", title, 0xCF0000, 0, 0, 640, 480, ...)
//   SendMessageA(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0)
//   Sleep(16)
//   SendMessageA(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0)
// ============================================================================
DWORD CreateGameWindow(HINSTANCE hInstance) {
    WNDCLASSA windowClass = {};
    windowClass.lpfnWndProc = WindowProcedure;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursorA(0, (const char*)0x7F00);
    windowClass.hbrBackground = (HBRUSH)GetStockObject(4);
    windowClass.lpszClassName = "BASE";
    DAT_004924fc = 1;
    DAT_00492500 = 0;
    RegisterClassA(&windowClass);

    if (DAT_00491d65 == 0) {
        // Windowed mode
        DAT_00491c70 = CreateWindowExA(
            0, "BASE", (const char*)&DAT_0046f66c,
            0xCF0000,  // WS_VISIBLE|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX
            0, 0, 0x280, 0x1E0,  // 640x480
            0, 0, hInstance, 0);
    } else {
        // Fullscreen mode
        int cx = GetSystemMetrics(7);  // SM_CXFULLSCREEN
        int cy = GetSystemMetrics(8);  // SM_CYFULLSCREEN
        int cyMenu = GetSystemMetrics(4);  // SM_CYMENU
        DAT_00491c70 = CreateWindowExA(
            0, "BASE", (const char*)&DAT_0046f66c,
            0x100A0000,  // WS_POPUP|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN
            (int)0x80000000, (int)0x80000000,
            cx * 2 + 0x280, cyMenu + 0x1E0 + cy * 2,
            0, 0, hInstance, 0);
    }

    g_pWnd = DAT_00491c70;
    if (DAT_00491c70 == 0) {
        return 1;
    }

    // Minimize then restore to force taskbar update
    SendMessageA(DAT_00491c70, 0x112, 0xF020, 0);  // WM_SYSCOMMAND, SC_MINIMIZE
    Sleep(0x10);
    SendMessageA(g_pWnd, 0x112, 0xF120, 0);  // WM_SYSCOMMAND, SC_RESTORE

    return 0;
}

// ============================================================================
// 0x0043AA60 - Release the MIDI file/buffer table
// Retail received manager in ESI.
// ============================================================================
void MidiBuffersRelease(MidiManager* manager) {
    if (manager == 0) {
        return;
    }

    for (int index = 0; index < manager->buffer_count; ++index) {
        void*& allocation = manager->buffers[index].allocation;
        if (allocation != 0) {
            _free(allocation);
            allocation = 0;
        }
    }

    if (manager->buffers != 0) {
        _free(manager->buffers);
    }
    manager->buffers = 0;
    manager->buffer_count = 0;
}

// ============================================================================
// 0x0043AEB0 - Retire a completed MIDI output header
// Retail received manager in EDX and header in ESI.
// ============================================================================
int MidiHeaderRelease(MidiManager* manager, MidiHeader* header) {
    if (manager == 0 || header == 0) {
        return -1;
    }

    int slot = 0;
    while (slot < 32 && manager->active_headers[slot] != header) {
        ++slot;
    }
    if (slot == 32) {
        return -1;
    }

    manager->active_headers[slot] = 0;
    midiOutUnprepareHeader(manager->output, header, sizeof(MidiHeader));
    if (header->data != 0) {
        _free(header->data);
        header->data = 0;
    }
    _free(header);
    return 0;
}

// ============================================================================
// 0x0043AE20 - Stop MIDI playback and release all queued headers
// Retail received manager in EDI.
// ============================================================================
int MidiManagerShutdown(MidiManager* manager) {
    if (manager == 0 || manager->buffers == 0) {
        return -1;
    }

    for (int slot = 0; slot < 32; ++slot) {
        MidiHeader* header = manager->active_headers[slot];
        if (header != 0) {
            MidiHeaderRelease(manager, header);
        }
    }

    if (manager->timer_event != 0) {
        timeKillEvent(manager->timer_event);
    }
    timeEndPeriod(manager->timer_period);
    manager->timer_event = 0;

    if (manager->output != 0) {
        midiOutReset(manager->output);
        midiOutClose(manager->output);
        manager->output = 0;
    }

    manager->state = -1;
    return 0;
}

// ============================================================================
// 0x0043A290 - Resolve a Windows shortcut
//
// Retail supplied target_path in EBX and target_capacity in EDI, leaving only
// shortcut_path on the stack.  The readable interface makes all three inputs
// explicit.  The COM calls and their cleanup order follow the retail body.
// ============================================================================
BOOL ResolveShortcutTarget(const char* shortcut_path, char* target_path,
                           DWORD target_capacity) {
    if (target_path == 0 || shortcut_path == 0 || target_capacity == 0) {
        return FALSE;
    }

    CoInitialize(0);

    ShellLink* shell_link = 0;
    PersistFile* persist_file = 0;
    BOOL resolved = FALSE;

    LONG result = CoCreateInstance(&kShellLinkClass, 0, 1,
                                   &kShellLinkInterface,
                                   (void**)&shell_link);
    if (Succeeded(result)) {
        result = shell_link->vtable->QueryInterface(
            shell_link, &kPersistFileInterface, (void**)&persist_file);
        if (Succeeded(result)) {
            WORD* wide_path = (WORD*)operator_new(target_capacity * sizeof(WORD));
            MultiByteToWideChar(0, 0, shortcut_path, -1, wide_path,
                                target_capacity);

            result = persist_file->vtable->Load(persist_file, wide_path, 0);
            if (Succeeded(result)) {
                // WIN32_FIND_DATAA is 320 bytes on the 32-bit target.  GetPath
                // accepts it as optional output; retail supplied stack storage.
                BYTE find_data[320];
                result = shell_link->vtable->GetPath(
                    shell_link, target_path, target_capacity, find_data, 0);
                resolved = Succeeded(result);
            }

            _free(wide_path);
            persist_file->vtable->Release(persist_file);
        }
        shell_link->vtable->Release(shell_link);
    }

    CoUninitialize();
    return resolved;
}

// ============================================================================
// 0x00439FF0 - Instance Check (Mutex + LNK Resolution)
// Creates a named mutex to prevent multiple instances. Checks if launched
// via a .lnk shortcut (for replay drag-drop support). Uses security cookie.
//
// Ghidra decompilation:
//   CreateMutexA(NULL, TRUE, "Touhou 10 App")
//   if (GetLastError() == ERROR_ALREADY_EXISTS):
//     Platform_LogMessage("already running message")
//     return -1
//   GetModuleFileNameA(NULL, path, 0x105)
//   GetConsoleTitleA(title, 0x105)
//   GetStartupInfoA(&si)
//   if (si.lpTitle == NULL):
//     DAT_00491ff4 |= 0x40
//   else:
//     Check if .lnk extension, resolve shortcut, compare paths
//     Set DAT_00492518 = 1 if launched from different path (replay)
//     DAT_00491ff4 &= ~0x40
//   return (mutex != NULL) - 1  // 0 if success, -1 if no mutex
// ============================================================================
int InstanceCheck(void) {
    DAT_00497ba8 = CreateMutexA(0, 1, "Touhou 10 App");
    DWORD err = GetLastError();
    if (err == 0xB7) {  // ERROR_ALREADY_EXISTS
        Platform_LogMessage("already running");
        return -1;
    }

    // STARTUPINFOA (0x44 bytes)
    STARTUPINFOA startupInfo = {};
    char modulePath[0x105];
    char consoleTitle[0x105];

    startupInfo.cb = sizeof(startupInfo);

    GetModuleFileNameA(0, modulePath, 0x105);
    GetConsoleTitleA(consoleTitle, 0x105);
    GetStartupInfoA(&startupInfo);

    char* lpTitle = startupInfo.lpTitle;

    if (lpTitle == 0) {
        DAT_00491ff4 |= 0x40;
    } else {
        char* extension = _strrchr(lpTitle, '.');
        if (File_ProbePath(lpTitle) && extension != 0) {
            if (__stricmp(extension, ".lnk") == 0) {
                const char* shortcut_path = lpTitle;
                do {
                    ResolveShortcutTarget(shortcut_path, consoleTitle, 0x104);
                    shortcut_path = consoleTitle;
                    extension = _strrchr(consoleTitle, '.');
                } while (extension != 0 &&
                         __stricmp(extension, ".lnk") == 0);
            } else {
                CopyString(consoleTitle, lpTitle);
            }

            if (!StringsEqual(modulePath, consoleTitle)) {
                DAT_00492518 = 1;
            }
        }
        DAT_00491ff4 &= 0xFFFFFFBF;
    }

    return (int)(DAT_00497ba8 != 0) - 1;
}

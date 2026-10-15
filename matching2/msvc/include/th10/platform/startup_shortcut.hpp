#pragma once

typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef long LONG;
typedef void* HANDLE;
struct StartupInfoA {
    DWORD cb;
    char *reserved, *desktop, *title;
    DWORD x, y, width, height, xChars, yChars, fillAttribute, flags;
    WORD showWindow, reservedSize;
    BYTE* reservedBytes;
    HANDLE stdInput, stdOutput, stdError;
};
struct FileTime { DWORD low, high; };
struct FindDataA {
    DWORD attributes;
    FileTime creation, access, write;
    DWORD sizeHigh, sizeLow, reserved0, reserved1;
    char name[260], alternateName[14];
};
typedef char StartupInfoHasSdkLayout[(sizeof(StartupInfoA) == 68) ? 1 : -1];
typedef char FindDataHasSdkLayout[(sizeof(FindDataA) == 320) ? 1 : -1];
struct Guid { DWORD a; WORD b, c; BYTE d[8]; };
struct ShellLink;
struct PersistFile;
struct ShellLinkVtable {
    LONG (__stdcall *QueryInterface)(ShellLink*, const Guid*, void**);
    DWORD (__stdcall *AddRef)(ShellLink*);
    DWORD (__stdcall *Release)(ShellLink*);
    LONG (__stdcall *GetPath)(ShellLink*, char*, int, FindDataA*, DWORD);
};
struct PersistFileVtable {
    LONG (__stdcall *QueryInterface)(PersistFile*, const Guid*, void**);
    DWORD (__stdcall *AddRef)(PersistFile*);
    DWORD (__stdcall *Release)(PersistFile*);
    LONG (__stdcall *GetClassID)(PersistFile*, Guid*);
    LONG (__stdcall *IsDirty)(PersistFile*);
    LONG (__stdcall *Load)(PersistFile*, const WORD*, DWORD);
};
struct ShellLink { ShellLinkVtable* vtable; };
struct PersistFile { PersistFileVtable* vtable; };
struct CriticalSection { unsigned char storage[24]; };
struct TextLog_0044b8e0 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* AppendLine(char* format, ...);
};
extern "C" {
__declspec(dllimport) HANDLE __stdcall CreateMutexA(void*, int, const char*);
__declspec(dllimport) DWORD __stdcall GetLastError();
__declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HANDLE, char*, DWORD);
__declspec(dllimport) DWORD __stdcall GetConsoleTitleA(char*, DWORD);
__declspec(dllimport) void __stdcall GetStartupInfoA(StartupInfoA*);
__declspec(dllimport) LONG __stdcall CoInitialize(void*);
__declspec(dllimport) LONG __stdcall CoCreateInstance(const Guid*, void*, DWORD, const Guid*, void**);
__declspec(dllimport) void __stdcall CoUninitialize();
__declspec(dllimport) int __stdcall MultiByteToWideChar(DWORD, DWORD, const char*, int, WORD*, int);
__declspec(dllimport) void __stdcall EnterCriticalSection(CriticalSection*);
__declspec(dllimport) void __stdcall LeaveCriticalSection(CriticalSection*);
__declspec(dllimport) int __stdcall CloseHandle(HANDLE);
int __cdecl asm_vsprintf_004524a6(char*, const char*, char*);
void* __cdecl Startup_New_00452493(unsigned int);
void __cdecl Startup_Free_004524a1(void*);
extern char startupMutexName[], startupAlreadyRunning[], startupLinkExtension[];
extern Guid shellLinkClass, shellLinkInterface, persistFileInterface;
extern HANDLE startupMutex;
extern DWORD startupFlags;
extern BYTE startupReplay;
extern TextLog_0044b8e0 startupLog;
extern CriticalSection g_text_log_lock, g_file_critical_section;
extern BYTE g_text_log_lock_depth, g_file_critical_depth;
extern void* imp_EnterCriticalSection;
extern void* imp_CreateFileA;
}
__declspec(noinline) int __stdcall asm_File_ProbeExists_0044b4d0(const char*);
// The complete real caller lets LTCG assign target to EBX and capacity to EDI.
// Only shortcut remains on the stack, cleaned by the callee's RET4.
__declspec(noinline) int __stdcall ResolveShortcutTarget(const char*, char*, DWORD);
// Public int(void) boundary; the real GameMain call supplies no data inputs.
extern "C" __declspec(noinline) int __cdecl Startup_InstanceCheck_00439ff0();

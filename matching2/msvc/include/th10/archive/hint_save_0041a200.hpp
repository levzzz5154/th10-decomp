#ifndef TH10_ARCHIVE_HINT_SAVE_0041A200_HPP
#define TH10_ARCHIVE_HINT_SAVE_0041A200_HPP

#include <stddef.h>
#include <time.h>
#include "th10/game/resource_cleanup.hpp"
#include "th10/game/hint_data.hpp"

// 0x0041A200 (_SaveHints@8): regenerate hint/hint_auto.txt from the eight
// per-stage tip lists of the resource manager. Called by the resource cleanup
// when a run recorded new tips. Always returns 0.
extern "C" __declspec(noinline) int __stdcall SaveHints(Manager_00419040* manager,
                                                        const char* path);

// 0x0044B740: write one block to the shared file; a short write closes the
// file and releases its lock. The declaration only names the region: native
// LTCG gives the body its retail private convention (buffer EDX, size ESI,
// result EAX, plain RET), which no standalone declaration can describe.
int __stdcall WriteShared_0044b740(const void* buffer, unsigned int size);

extern "C" {
// The shared-file helpers this writer sits on.
int __stdcall asm_File_OpenSharedWrite_0044b620(const char* path);
int __cdecl asm_FUN_00452abc_00452abc(const char* path);
int __cdecl asm_sprintf_00452ae8(char* destination, const char* format, ...);
void* __cdecl asm_malloc_00452706(unsigned int size);
void __cdecl asm_free_00452422(void* memory);
int __cdecl time_00452b71(int* output);

// KERNEL32 slots the retail layout binds under their thunks.
extern int (__stdcall* data_004660cc)(void* handle);              // CloseHandle
extern int (__stdcall* data_004660d4)(void* handle, const void* buffer,
    unsigned int size, unsigned int* written, void* overlapped);  // WriteFile
extern void (__stdcall* data_004660b4)(void* section);            // LeaveCriticalSection
extern void* data_00474c38;                                       // shared file handle
extern unsigned char data_0049231e;                               // file lock depth

// hint_auto.txt literals.
extern const char data_0046d320[];   // "StageEnd\r\n"
extern const char data_0046d32c[];   // "End\r\n\r\n"
extern const char data_0046d334[];   // "\tScale\t: %.1f\r\n"
extern const char data_0046d344[];   // "\tColor\t: %d, %d, %d\r\n"
extern const char data_0046d35c[];   // "\tAlpha\t: %d\r\n"
extern const char data_0046d36c[];   // "\tTime\t: %d\r\n"
extern const char data_0046d37c[];   // "\tAlign\t: %s\r\n"
extern const char data_0046d38c[];   // "\tBase\t: %s\r\n"
extern const char data_0046d39c[];   // "\tCount\t: %d\r\n"
extern const char data_0046d3ac[];   // "\tPos\t\t: %d, %d\r\n"
extern const char data_0046d3c0[];   // "\tText\t: \"%s\"\r\n"
extern const char data_0046d3d0[];   // "\tRemain\t: %d\r\n"
extern const char data_0046d3e0[];   // "Tips\r\n"
extern const char data_0046d3e8[];   // "Stage : %d\r\n\r\n"
extern const char data_0046d3f8[];   // "# ================================== \r\n"
extern const char data_0046d420[];   // "Version = %s\r\n\r\n"
extern const char data_0046d434[];   // "\r\n\r\n"
extern const char data_0046d440[];   // "#  ... Time-stamp: <%.4d/%.2d/%.2d %.2d:%.2d>\r\n"
extern const char data_0046d490[];   // "# \x81g ...\r\n" (edit another file)
extern const char data_0046d4d8[];   // "# ... \r\n" (generated, overwritten)
extern const char data_0046d50c[];   // "#\r\n"
extern const char data_0046d510[];   // "# \x93\x8c\x95\xfb ...\r\n" (hint file banner)
extern const char data_0046d534[];   // "# ===== ... \r\n"
extern const char data_0046d574[];   // "hint" (created once before writing)
extern const char data_0046d654[];   // "0.0" (hint format version)
}

// One {name, id} row of the tip attribute name tables.
struct HintNameEntry_0041a200 {
    const char* name;       // +0x00
    int id;                 // +0x04
};

extern "C" const HintNameEntry_0041a200 data_00474494[3];    // Align: center/left/right
extern "C" const HintNameEntry_0041a200 data_004744b0[61];   // Base: start/converse/boss names

#endif

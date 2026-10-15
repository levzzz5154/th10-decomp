#pragma once
#include <string.h>

#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

void __cdecl operator delete(void*);
void* __cdecl operator new(unsigned int size);
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE handle);

// The raw-pair release still lives in inline assembly, so it is called through its
// fixed retail prototype (one stack argument, callee cleans).
typedef void (__stdcall* RawPairReleaseFn)(void* pair);
// CRT heap release reached by the state teardown below.
extern "C" void __cdecl crt_free_startup(void* memory);

// 0x0040B940..0x0040B9A2: Recovery_CreateSmallState
// Allocate the small recovery state, register it in the global slot and hand it
// to the pair installer. When the installer rejects it the state is torn down
// through its own release entry and returned to the CRT heap.
struct RecoverySmallState {
    unsigned int flags;             // +0x00, bit 1 marks a registered state
    unsigned int reserved_04[9];    // +0x04..+0x27

    RecoverySmallState();
};


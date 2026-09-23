#include <string.h>

#include "asm_symbols.hpp"

struct AsciiManager_0043c8b0 {
    unsigned int flags;               // +0x00
    unsigned char reserved_004[0x3C]; // +0x04..+0x3F
    unsigned int flags_040;           // +0x40
};

typedef void (__stdcall *AsciiManagerSetupFn)(
    unsigned int arg0,
    unsigned int arg1,
    unsigned int arg2,
    unsigned int arg3,
    unsigned int arg4);

#pragma code_seg(".text$01accessor")

// 0x0043C8B0..0x0043C901: allocate and initialize the ASCII manager.
// The retail call to 0x0043C970 also carries the new object in ESI and keeps
// the caller's EBX value live as a dispatch input. The typed call below records
// the five stack arguments; those private register inputs remain unresolved.
extern "C" AsciiManager_0043c8b0* __stdcall AsciiManager_CreateRetail_0043c8b0(
    unsigned int arg0,
    unsigned int arg1,
    unsigned int arg2,
    unsigned int arg3,
    unsigned int arg4) {
    AsciiManager_0043c8b0* manager = new AsciiManager_0043c8b0;
    if (manager == 0) {
        return 0;
    }

    // Retail clears bit zero at +0x40 immediately before zeroing all 0x44
    // bytes, so the clear is overwritten by this initialization.
    memset(manager, 0, sizeof(*manager));
    manager->flags |= 2;

    AsciiManagerSetupFn setup = reinterpret_cast<AsciiManagerSetupFn>(
        &asm_FUN_0043c970_0043c970);
    setup(arg0, arg1, arg2, arg3, arg4);
    return manager;
}

#pragma code_seg()

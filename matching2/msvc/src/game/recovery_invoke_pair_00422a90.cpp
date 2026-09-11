#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00422A90..0x00422A99: Recovery_InvokePair
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InvokePair_00422a90() {
    __asm {
    L_00422a90:
        push esi
    L_00422a91:
        mov esi,ecx
    L_00422a93:
        call asm_FUN_004223f0_004223f0
    L_00422a98:
        pop esi
    L_00422a99:
        ret
    }
}

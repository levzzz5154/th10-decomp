#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x004198A0..0x004198A9: Recovery_InvokeVoid
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InvokeVoid_004198a0() {
    __asm {
    L_004198a0:
        push ebx
    L_004198a1:
        mov ebx,ecx
    L_004198a3:
        call asm_FUN_00419650_00419650
    L_004198a8:
        pop ebx
    L_004198a9:
        ret
    }
}

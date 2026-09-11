#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00427950..0x0042795B: Recovery_InvokeZero
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InvokeZero_00427950() {
    __asm {
    L_00427950:
        push esi
    L_00427951:
        mov esi,ecx
    L_00427953:
        call asm_FUN_00427960_00427960
    L_00427958:
        xor eax,eax
    L_0042795a:
        pop esi
    L_0042795b:
        ret
    }
}

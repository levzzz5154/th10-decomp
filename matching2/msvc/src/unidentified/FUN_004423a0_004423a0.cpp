#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004423A0..0x004423A5: FUN_004423a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004423a0_004423a0() {
    __asm {
    L_004423a0:
        mov ecx,dword ptr [eax]
    L_004423a2:
        mov dword ptr [edx+0Ch],ecx
    L_004423a5:
        ret
    }
}

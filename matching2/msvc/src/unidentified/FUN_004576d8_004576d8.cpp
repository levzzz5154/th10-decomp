#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004576D8..0x004576E5: FUN_004576d8
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004576d8_004576d8() {
    __asm {
    L_004576d8:
        cmp dword ptr [ebp+10h],edi
    L_004576db:
        je short L_004576e5
    L_004576dd:
        push 8
    L_004576df:
        call asm_FUN_00453b3f_00453b3f
    L_004576e4:
        pop ecx
    L_004576e5:
        ret
    }
}

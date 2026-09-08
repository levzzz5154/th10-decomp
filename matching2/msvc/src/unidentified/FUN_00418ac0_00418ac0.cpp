#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418AC0..0x00418ACE: FUN_00418ac0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418ac0_00418ac0() {
    __asm {
    L_00418ac0:
        mov dword ptr [eax+10h],0
    L_00418ac7:
        mov dword ptr [eax+0Ch],1
    L_00418ace:
        ret
    }
}

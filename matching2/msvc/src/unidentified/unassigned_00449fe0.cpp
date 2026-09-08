#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449FE0..0x00449FFF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449fe0() {
    __asm {
    L_00449fe0:
        xor eax,eax
    L_00449fe2:
        mov dword ptr [esi+8],eax
    L_00449fe5:
        mov dword ptr [esi+0Ch],eax
    L_00449fe8:
        mov dword ptr [esi+10h],eax
    L_00449feb:
        test byte ptr [esp+4],1
    L_00449ff0:
        je short L_00449ffb
    L_00449ff2:
        push esi
    L_00449ff3:
        call asm_free_004524a1
    L_00449ff8:
        add esp,4
    L_00449ffb:
        mov eax,esi
    L_00449ffd:
        ret 4
    }
}

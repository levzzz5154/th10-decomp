#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404CF0..0x00404D03: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404cf0() {
    __asm {
    L_00404cf0:
        fild dword ptr [eax+44h]
    L_00404cf3:
        push ecx
    L_00404cf4:
        mov ecx,dword ptr [eax+38h]
    L_00404cf7:
        mov eax,dword ptr [eax+48h]
    L_00404cfa:
        fstp dword ptr [esp]
    L_00404cfd:
        push ecx
    L_00404cfe:
        call asm_FUN_0044c350_0044c350
    L_00404d03:
        ret
    }
}

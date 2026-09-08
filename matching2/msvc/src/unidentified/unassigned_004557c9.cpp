#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004557C9..0x004557EF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004557c9() {
    __asm {
    L_004557c9:
        call asm_getptd_00456357
    L_004557ce:
        mov eax,dword ptr [eax+64h]
    L_004557d1:
        cmp eax,dword ptr [data_0047320c]
    L_004557d7:
        je short L_004557de
    L_004557d9:
        call asm_updatetlocinfo_00455ade
    L_004557de:
        push dword ptr [esp+8]
    L_004557e2:
        push dword ptr [esp+8]
    L_004557e6:
        push eax
    L_004557e7:
        call asm_isctype_mt_00455752
    L_004557ec:
        add esp,0Ch
    L_004557ef:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412E10..0x00412E23: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412e10() {
    __asm {
    L_00412e10:
        fild dword ptr [eax+34h]
    L_00412e13:
        push ecx
    L_00412e14:
        mov ecx,dword ptr [eax+28h]
    L_00412e17:
        mov eax,dword ptr [eax+38h]
    L_00412e1a:
        fstp dword ptr [esp]
    L_00412e1d:
        push ecx
    L_00412e1e:
        call asm_FUN_0044c350_0044c350
    L_00412e23:
        ret
    }
}

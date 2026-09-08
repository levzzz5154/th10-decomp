#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441D70..0x00441D83: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441d70() {
    __asm {
    L_00441d70:
        fild dword ptr [eax+44h]
    L_00441d73:
        push ecx
    L_00441d74:
        mov ecx,dword ptr [eax+38h]
    L_00441d77:
        mov eax,dword ptr [eax+48h]
    L_00441d7a:
        fstp dword ptr [esp]
    L_00441d7d:
        push ecx
    L_00441d7e:
        call asm_FUN_0044c350_0044c350
    L_00441d83:
        ret
    }
}

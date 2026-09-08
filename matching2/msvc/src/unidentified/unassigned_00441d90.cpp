#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441D90..0x00441DA3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441d90() {
    __asm {
    L_00441d90:
        fild dword ptr [eax+24h]
    L_00441d93:
        push ecx
    L_00441d94:
        mov ecx,dword ptr [eax+18h]
    L_00441d97:
        mov eax,dword ptr [eax+28h]
    L_00441d9a:
        fstp dword ptr [esp]
    L_00441d9d:
        push ecx
    L_00441d9e:
        call asm_FUN_0044c350_0044c350
    L_00441da3:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449F20..0x00449F53: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449f20() {
    __asm {
    L_00449f20:
        test esi,esi
    L_00449f22:
        je short L_00449f51
    L_00449f24:
        push 492274h
    L_00449f29:
        call dword ptr [data_004660b0]
    L_00449f2f:
        inc byte ptr [data_0049231c]
    L_00449f35:
        mov edx,dword ptr [esp+4]
    L_00449f39:
        mov ecx,esi
    L_00449f3b:
        call asm_Scheduler_Remove_00449f60
    L_00449f40:
        push 492274h
    L_00449f45:
        call dword ptr [data_004660b4]
    L_00449f4b:
        dec byte ptr [data_0049231c]
    L_00449f51:
        ret 4
    }
}

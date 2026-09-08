#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045721B..0x0045724F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045721b() {
    __asm {
    L_0045721b:
        push 8
    L_0045721d:
        push 46AAD0h
    L_00457222:
        call asm_SEH_prolog_00454bbc
    L_00457227:
        push 6
    L_00457229:
        call asm_lock_00453c0c
    L_0045722e:
        pop ecx
    L_0045722f:
        and dword ptr [ebp-4],0
    L_00457233:
        call asm_tzset_lk_00456be8
    L_00457238:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045723c:
        call asm_target_00457247
    L_00457241:
        call asm_SEH_epilog_00454bf7
    L_00457246:
        ret
    L_00457247:
        push 6
    L_00457249:
        call asm_FUN_00453b3f_00453b3f
    L_0045724e:
        pop ecx
    L_0045724f:
        ret
    }
}

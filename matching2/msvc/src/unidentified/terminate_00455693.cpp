#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455693..0x004556B7: terminate
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_terminate_00455693() {
    __asm {
    L_00455693:
        push 8
    L_00455695:
        push 46A808h
    L_0045569a:
        call asm_SEH_prolog_00454bbc
    L_0045569f:
        call asm_getptd_00456357
    L_004556a4:
        cmp dword ptr [eax+6Ch],0
    L_004556a8:
        TH10_REL8(0x74, 0x004556a8, VA_asm_target_004556c3)
    L_004556aa:
        and dword ptr [ebp-4],0
    L_004556ae:
        call asm_getptd_00456357
    L_004556b3:
        call dword ptr [eax+6Ch]
    L_004556b6:
        TH10_REL8(0xeb, 0x004556b6, VA_asm_terminate_part_004556bf)
    }
}

// 0x004556BF..0x004556C7: terminate
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_terminate_part_004556bf() {
    __asm {
    L_004556bf:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004556c3:
        jmp asm_abort_0045a245
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004597BA..0x004597E6: FUN_004597ba
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004597ba_004597ba() {
    __asm {
    L_004597ba:
        push 0Ch
    L_004597bc:
        push 46B058h
    L_004597c1:
        call asm_SEH_prolog_00454bbc
    L_004597c6:
        mov dword ptr [ebp-1Ch],471130h
    L_004597cd:
        cmp dword ptr [ebp-1Ch],471130h
    L_004597d4:
        TH10_REL8(0x73, 0x004597d4, VA_asm_target_004597f8)
    L_004597d6:
        and dword ptr [ebp-4],0
    L_004597da:
        mov eax,dword ptr [ebp-1Ch]
    L_004597dd:
        mov eax,dword ptr [eax]
    L_004597df:
        test eax,eax
    L_004597e1:
        TH10_REL8(0x74, 0x004597e1, VA_asm_FUN_004597ba_part_004597ee)
    L_004597e3:
        call eax
    L_004597e5:
        TH10_REL8(0xeb, 0x004597e5, VA_asm_FUN_004597ba_part_004597ee)
    }
}

// 0x004597EE..0x004597FD: FUN_004597ba
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004597ba_part_004597ee() {
    __asm {
    L_004597ee:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004597f2:
        add dword ptr [ebp-1Ch],4
    L_004597f6:
        TH10_REL8(0xeb, 0x004597f6, VA_asm_target_004597cd)
    L_004597f8:
        call asm_SEH_epilog_00454bf7
    L_004597fd:
        ret
    }
}

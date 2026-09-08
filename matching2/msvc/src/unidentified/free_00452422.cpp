#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452422..0x00452474: _free
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_free_00452422() {
    __asm {
    L_00452422:
        push 0Ch
    L_00452424:
        push 46A690h
    L_00452429:
        call asm_SEH_prolog_00454bbc
    L_0045242e:
        mov esi,dword ptr [ebp+8]
    L_00452431:
        test esi,esi
    L_00452433:
        TH10_REL8(0x74, 0x00452433, VA_asm_target_0045248d)
    L_00452435:
        cmp dword ptr [data_00499344],3
    L_0045243c:
        TH10_REL8(0x75, 0x0045243c, VA_asm_free_part_0045247e)
    L_0045243e:
        push 4
    L_00452440:
        call asm_lock_00453c0c
    L_00452445:
        pop ecx
    L_00452446:
        and dword ptr [ebp-4],0
    L_0045244a:
        push esi
    L_0045244b:
        call asm_sbh_find_block_00453c9a
    L_00452450:
        pop ecx
    L_00452451:
        mov dword ptr [ebp-1Ch],eax
    L_00452454:
        test eax,eax
    L_00452456:
        je short L_00452461
    L_00452458:
        push esi
    L_00452459:
        push eax
    L_0045245a:
        call asm_sbh_free_block_00453cc5
    L_0045245f:
        pop ecx
    L_00452460:
        pop ecx
    L_00452461:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00452465:
        call asm_FUN_00452475_00452475
    L_0045246a:
        cmp dword ptr [ebp-1Ch],0
    L_0045246e:
        TH10_REL8(0x75, 0x0045246e, VA_asm_target_0045248d)
    L_00452470:
        push dword ptr [ebp+8]
    L_00452473:
        TH10_REL8(0xeb, 0x00452473, VA_asm_target_0045247f)
    }
}

// 0x0045247E..0x00452492: _free
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_free_part_0045247e() {
    __asm {
    L_0045247e:
        push esi
    L_0045247f:
        push 0
    L_00452481:
        push dword ptr [data_00499340]
    L_00452487:
        call dword ptr [data_004661e8]
    L_0045248d:
        call asm_SEH_epilog_00454bf7
    L_00452492:
        ret
    }
}

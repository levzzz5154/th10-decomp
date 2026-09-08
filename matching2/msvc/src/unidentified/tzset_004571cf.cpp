#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004571CF..0x00457211: ___tzset
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_tzset_004571cf() {
    __asm {
    L_004571cf:
        push 8
    L_004571d1:
        push 46AAC0h
    L_004571d6:
        call asm_SEH_prolog_00454bbc
    L_004571db:
        xor esi,esi
    L_004571dd:
        cmp dword ptr [data_00477444],esi
    L_004571e3:
        jne short L_0045720c
    L_004571e5:
        push 6
    L_004571e7:
        call asm_lock_00453c0c
    L_004571ec:
        pop ecx
    L_004571ed:
        mov dword ptr [ebp-4],esi
    L_004571f0:
        cmp dword ptr [data_00477444],esi
    L_004571f6:
        jne short L_00457203
    L_004571f8:
        call asm_tzset_lk_00456be8
    L_004571fd:
        inc dword ptr [data_00477444]
    L_00457203:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00457207:
        call asm_FUN_00457212_00457212
    L_0045720c:
        call asm_SEH_epilog_00454bf7
    L_00457211:
        ret
    }
}

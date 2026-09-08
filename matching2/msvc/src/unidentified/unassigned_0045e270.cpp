#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E270..0x0045E2B4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045e270() {
    __asm {
    L_0045e270:
        push 0Ch
    L_0045e272:
        push 46C5A8h
    L_0045e277:
        call asm_SEH_prolog_00454bbc
    L_0045e27c:
        push dword ptr [ebp+0Ch]
    L_0045e27f:
        call asm_target_0045a06a
    L_0045e284:
        pop ecx
    L_0045e285:
        and dword ptr [ebp-4],0
    L_0045e289:
        push dword ptr [ebp+0Ch]
    L_0045e28c:
        push dword ptr [ebp+8]
    L_0045e28f:
        call asm_FID_conflict__ungetc_0045e204
    L_0045e294:
        pop ecx
    L_0045e295:
        pop ecx
    L_0045e296:
        mov dword ptr [ebp-1Ch],eax
    L_0045e299:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045e29d:
        call asm_target_0045e2ab
    L_0045e2a2:
        mov eax,dword ptr [ebp-1Ch]
    L_0045e2a5:
        call asm_SEH_epilog_00454bf7
    L_0045e2aa:
        ret
    L_0045e2ab:
        push dword ptr [ebp+0Ch]
    L_0045e2ae:
        call asm_unassigned_0045a0bc
    L_0045e2b3:
        pop ecx
    L_0045e2b4:
        ret
    }
}

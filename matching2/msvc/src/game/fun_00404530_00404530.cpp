#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404530..0x004045A6: FUN_00404530
// Naked body preserves the retail register/stack ABI.

// 0x00404530..0x004045A6: FUN_00404530
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404530_00404530() {
    __asm {
    L_00404530:
        push ebx
    L_00404531:
        push 0
    L_00404533:
        push 0
    L_00404535:
        push 0
    L_00404537:
        push 1Eh
    L_00404539:
        push 2
    L_0040453b:
        mov ebx,0Fh
    L_00404540:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_00404545:
        mov eax,dword ptr [esi+2A2Ch]
    L_0040454b:
        test al,1
    L_0040454d:
        pop ebx
    L_0040454e:
        jne short L_00404581
    L_00404550:
        or eax,1
    L_00404553:
        mov dword ptr [esi+2A20h],0
    L_0040455d:
        mov dword ptr [esi+2A1Ch],0FFF0BDC1h
    L_00404567:
        mov dword ptr [esi+2A24h],0
    L_00404571:
        mov dword ptr [esi+2A28h],476F78h
    L_0040457b:
        mov dword ptr [esi+2A2Ch],eax
    L_00404581:
        mov dword ptr [esi+2A20h],1Eh
    L_0040458b:
        mov dword ptr [esi+2A24h],41F00000h
    L_00404595:
        mov dword ptr [esi+2A1Ch],1Dh
    L_0040459f:
        or dword ptr [esi+2A18h],2
    L_004045a6:
        ret
    }
}
// D3603 BLOCKED (2026-09-22): native-LTCG readable model retained only in
// isolated probe. It emitted 13/119 matching bytes (106 differences), first
// diff 0x00404530, because the retail body supplies EBX=0x0f as a private
// argument to AsciiManager_Create before the five stack arguments. The
// ordinary readable call cannot express that ABI while the callee remains an
// external assembly symbol.
// variants_tested: ordinary typed member model; native-LTCG caller/context
// model with absolute AsciiManager/data bindings.
// next_lever: recover AsciiManager_Create in the same native-LTCG scope so
// LINK can allocate the private EBX argument.

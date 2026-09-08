#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408460..0x0040849D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408460() {
    __asm {
    L_00408460:
        push esi
    L_00408461:
        mov esi,eax
    L_00408463:
        push edi
    L_00408464:
        add esi,60h
    L_00408467:
        mov edi,7D0h
    L_0040846c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00408470:
        mov ax,word ptr [esi+446h]
    L_00408477:
        test ax,ax
    L_0040847a:
        je short L_00408492
    L_0040847c:
        cmp ax,3
    L_00408480:
        je short L_00408492
    L_00408482:
        test ebx,ebx
    L_00408484:
        je short L_0040848d
    L_00408486:
        mov eax,dword ptr [esi+4]
    L_00408489:
        test eax,eax
    L_0040848b:
        jne short L_00408492
    L_0040848d:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_00408492:
        add esi,7F0h
    L_00408498:
        dec edi
    L_00408499:
        jne short L_00408470
    L_0040849b:
        pop edi
    L_0040849c:
        pop esi
    L_0040849d:
        ret
    }
}

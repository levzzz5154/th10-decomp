#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452720..0x00452724: FUN_0046227b
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046227b_part_00452720() {
    __asm {
    L_00452720:
        lea eax,[edx-1]
    L_00452723:
        pop ebx
    L_00452724:
        ret
    }
}

// 0x0046227B..0x004622F5: FUN_0046227b
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046227b_0046227b() {
    __asm {
    L_0046227b:
        push ebp
    L_0046227c:
        mov ebp,esp
    L_0046227e:
        call asm_getptd_00456357
    L_00462283:
        mov eax,dword ptr [eax+60h]
    L_00462286:
        cmp eax,dword ptr [data_00497f94]
    L_0046228c:
        je short L_00462293
    L_0046228e:
        call asm_updatetmbcinfo_0045cf49
    L_00462293:
        cmp dword ptr [eax+8],0
    L_00462297:
        jne short L_0046229f
    L_00462299:
        pop ebp
    L_0046229a:
        jmp asm_FUN_00452730_00452730
    L_0046229f:
        mov ecx,dword ptr [ebp+8]
    L_004622a2:
        push ebx
    L_004622a3:
        push esi
    L_004622a4:
        jmp short L_004622d5
    L_004622a6:
        movzx esi,dl
    L_004622a9:
        test byte ptr [esi+eax+1Dh],4
    L_004622ae:
        je short L_004622cc
    L_004622b0:
        inc ecx
    L_004622b1:
        mov bl,byte ptr [ecx]
    L_004622b3:
        test bl,bl
    L_004622b5:
        je short L_004622f2
    L_004622b7:
        movzx edx,dx
    L_004622ba:
        movzx esi,bl
    L_004622bd:
        shl edx,8
    L_004622c0:
        or edx,esi
    L_004622c2:
        cmp dword ptr [ebp+0Ch],edx
    L_004622c5:
        jne short L_004622d4
    L_004622c7:
        lea eax,[ecx-1]
    L_004622ca:
        jmp short L_004622ee
    L_004622cc:
        movzx esi,dx
    L_004622cf:
        cmp dword ptr [ebp+0Ch],esi
    L_004622d2:
        je short L_004622de
    L_004622d4:
        inc ecx
    L_004622d5:
        movzx dx,byte ptr [ecx]
    L_004622d9:
        test dx,dx
    L_004622dc:
        jne short L_004622a6
    L_004622de:
        mov eax,dword ptr [ebp+0Ch]
    L_004622e1:
        movzx edx,dx
    L_004622e4:
        sub eax,edx
    L_004622e6:
        neg eax
    L_004622e8:
        sbb eax,eax
    L_004622ea:
        not eax
    L_004622ec:
        and eax,ecx
    L_004622ee:
        pop esi
    L_004622ef:
        pop ebx
    L_004622f0:
        pop ebp
    L_004622f1:
        ret
    L_004622f2:
        xor eax,eax
    L_004622f4:
        jmp short L_004622ee
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450470..0x004504F7: FUN_00450470
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00450470_00450470() {
    __asm {
    L_00450470:
        push ecx
    L_00450471:
        push ebx
    L_00450472:
        mov ebx,dword ptr [eax+8]
    L_00450475:
        push ebp
    L_00450476:
        push esi
    L_00450477:
        xor ebp,ebp
    L_00450479:
        dec ebx
    L_0045047a:
        push edi
    L_0045047b:
        js short L_004504db
    L_0045047d:
        mov eax,dword ptr [eax+8Ch]
    L_00450483:
        mov dword ptr [esp+10h],eax
    L_00450487:
        mov ecx,dword ptr [esp+10h]
    L_0045048b:
        mov eax,ebx
    L_0045048d:
        sub eax,ebp
    L_0045048f:
        cdq
    L_00450490:
        sub eax,edx
    L_00450492:
        mov edi,eax
    L_00450494:
        sar edi,1
    L_00450496:
        add edi,ebp
    L_00450498:
        mov esi,dword ptr [ecx+edi*8]
    L_0045049b:
        mov ecx,dword ptr [esp+18h]
    L_0045049f:
        nop
    L_004504a0:
        mov dl,byte ptr [ecx]
    L_004504a2:
        mov al,dl
    L_004504a4:
        cmp dl,byte ptr [esi]
    L_004504a6:
        jne short L_004504c4
    L_004504a8:
        test al,al
    L_004504aa:
        je short L_004504c0
    L_004504ac:
        mov dl,byte ptr [ecx+1]
    L_004504af:
        mov al,dl
    L_004504b1:
        cmp dl,byte ptr [esi+1]
    L_004504b4:
        jne short L_004504c4
    L_004504b6:
        add ecx,2
    L_004504b9:
        add esi,2
    L_004504bc:
        test al,al
    L_004504be:
        jne short L_004504a0
    L_004504c0:
        xor eax,eax
    L_004504c2:
        jmp short L_004504c9
    L_004504c4:
        sbb eax,eax
    L_004504c6:
        sbb eax,0FFFFFFFFh
    L_004504c9:
        test eax,eax
    L_004504cb:
        je short L_004504e5
    L_004504cd:
        jge short L_004504d4
    L_004504cf:
        lea ebx,[edi-1]
    L_004504d2:
        jmp short L_004504d7
    L_004504d4:
        lea ebp,[edi+1]
    L_004504d7:
        cmp ebp,ebx
    L_004504d9:
        jle short L_00450487
    L_004504db:
        pop edi
    L_004504dc:
        pop esi
    L_004504dd:
        pop ebp
    L_004504de:
        xor eax,eax
    L_004504e0:
        pop ebx
    L_004504e1:
        pop ecx
    L_004504e2:
        ret 4
    L_004504e5:
        mov eax,dword ptr [esp+10h]
    L_004504e9:
        mov eax,dword ptr [eax+edi*8+4]
    L_004504ed:
        pop edi
    L_004504ee:
        pop esi
    L_004504ef:
        pop ebp
    L_004504f0:
        add eax,10h
    L_004504f3:
        pop ebx
    L_004504f4:
        pop ecx
    L_004504f5:
        ret 4
    }
}


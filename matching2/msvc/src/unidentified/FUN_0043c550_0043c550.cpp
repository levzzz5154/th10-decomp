#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C550..0x0043C706: FUN_0043c550
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c550_0043c550() {
    __asm {
    L_0043c550:
        mov eax,dword ptr [data_004918a4]
    L_0043c555:
        sub esp,0Ch
    L_0043c558:
        test eax,eax
    L_0043c55a:
        push esi
    L_0043c55b:
        mov esi,ecx
    L_0043c55d:
        jne short L_0043c5b4
    L_0043c55f:
        mov edx,dword ptr [esi+34h]
    L_0043c562:
        mov ecx,dword ptr [esi+3Ch]
    L_0043c565:
        mov dword ptr [esi+30h],edx
    L_0043c568:
        fld dword ptr [ecx]
    L_0043c56a:
        fcomp dword ptr [data_00470b68]
    L_0043c570:
        fnstsw ax
    L_0043c572:
        test ah,41h
    L_0043c575:
        jne short L_0043c598
    L_0043c577:
        fld dword ptr [ecx]
    L_0043c579:
        fcomp dword ptr [data_00470b64]
    L_0043c57f:
        fnstsw ax
    L_0043c581:
        test ah,5
    L_0043c584:
        jp short L_0043c598
    L_0043c586:
        fld dword ptr [esi+38h]
    L_0043c589:
        inc edx
    L_0043c58a:
        fadd dword ptr [data_00470afc]
    L_0043c590:
        mov dword ptr [esi+34h],edx
    L_0043c593:
        fstp dword ptr [esi+38h]
    L_0043c596:
        jmp short L_0043c5a8
    L_0043c598:
        fld dword ptr [esi+38h]
    L_0043c59b:
        fadd dword ptr [ecx]
    L_0043c59d:
        fst dword ptr [esi+38h]
    L_0043c5a0:
        call asm_FUN_00463b2c_00463b2c
    L_0043c5a5:
        mov dword ptr [esi+34h],eax
    L_0043c5a8:
        mov eax,dword ptr [esi+1Ch]
    L_0043c5ab:
        cmp dword ptr [esi+34h],eax
    L_0043c5ae:
        mov dword ptr [esp+8],eax
    L_0043c5b2:
        jl short L_0043c5be
    L_0043c5b4:
        mov eax,7
    L_0043c5b9:
        pop esi
    L_0043c5ba:
        add esp,0Ch
    L_0043c5bd:
        ret
    L_0043c5be:
        mov eax,dword ptr [esi+20h]
    L_0043c5c1:
        mov ecx,dword ptr [esi+24h]
    L_0043c5c4:
        sub ecx,eax
    L_0043c5c6:
        mov dword ptr [esp+0Ch],eax
    L_0043c5ca:
        mov eax,dword ptr [data_004918b0]
    L_0043c5cf:
        xor eax,9630h
    L_0043c5d4:
        sub eax,6553h
    L_0043c5d9:
        xor edx,edx
    L_0043c5db:
        mov dx,ax
    L_0043c5de:
        shr dx,0Eh
    L_0043c5e2:
        shl eax,2
    L_0043c5e5:
        mov dword ptr [esp+4],ecx
    L_0043c5e9:
        fild dword ptr [esp+4]
    L_0043c5ed:
        xor ecx,ecx
    L_0043c5ef:
        fmul dword ptr [esi+38h]
    L_0043c5f2:
        mov esi,dword ptr [data_004918b4]
    L_0043c5f8:
        add edx,eax
    L_0043c5fa:
        mov word ptr [data_004918b0],dx
    L_0043c601:
        mov eax,dword ptr [data_004918b0]
    L_0043c606:
        xor eax,9630h
    L_0043c60b:
        sub eax,6553h
    L_0043c610:
        mov cx,ax
    L_0043c613:
        shr cx,0Eh
    L_0043c617:
        lea edx,[eax*4]
    L_0043c61e:
        fidiv dword ptr [esp+8]
    L_0043c622:
        inc esi
    L_0043c623:
        add ecx,edx
    L_0043c625:
        mov word ptr [data_004918b0],cx
    L_0043c62c:
        movzx ecx,cx
    L_0043c62f:
        mov eax,ecx
    L_0043c631:
        shl eax,10h
    L_0043c634:
        or eax,ecx
    L_0043c636:
        xor edx,edx
    L_0043c638:
        mov ecx,3
    L_0043c63d:
        div ecx
    L_0043c63f:
        inc esi
    L_0043c640:
        fiadd dword ptr [esp+0Ch]
    L_0043c644:
        sub edx,0
    L_0043c647:
        je short L_0043c663
    L_0043c649:
        dec edx
    L_0043c64a:
        je short L_0043c65b
    L_0043c64c:
        dec edx
    L_0043c64d:
        jne short L_0043c66d
    L_0043c64f:
        fld st(0)
    L_0043c651:
        fchs
    L_0043c653:
        fstp dword ptr [data_00491e64]
    L_0043c659:
        jmp short L_0043c66d
    L_0043c65b:
        fst dword ptr [data_00491e64]
    L_0043c661:
        jmp short L_0043c66d
    L_0043c663:
        mov dword ptr [data_00491e64],0
    L_0043c66d:
        mov eax,dword ptr [data_004918b0]
    L_0043c672:
        xor eax,9630h
    L_0043c677:
        sub eax,6553h
    L_0043c67c:
        xor edx,edx
    L_0043c67e:
        mov dx,ax
    L_0043c681:
        shr dx,0Eh
    L_0043c685:
        shl eax,2
    L_0043c688:
        xor ecx,ecx
    L_0043c68a:
        add edx,eax
    L_0043c68c:
        mov word ptr [data_004918b0],dx
    L_0043c693:
        mov eax,dword ptr [data_004918b0]
    L_0043c698:
        xor eax,9630h
    L_0043c69d:
        sub eax,6553h
    L_0043c6a2:
        mov cx,ax
    L_0043c6a5:
        shr cx,0Eh
    L_0043c6a9:
        lea edx,[eax*4]
    L_0043c6b0:
        inc esi
    L_0043c6b1:
        add ecx,edx
    L_0043c6b3:
        mov word ptr [data_004918b0],cx
    L_0043c6ba:
        movzx ecx,cx
    L_0043c6bd:
        mov eax,ecx
    L_0043c6bf:
        shl eax,10h
    L_0043c6c2:
        or eax,ecx
    L_0043c6c4:
        xor edx,edx
    L_0043c6c6:
        mov ecx,3
    L_0043c6cb:
        div ecx
    L_0043c6cd:
        inc esi
    L_0043c6ce:
        mov dword ptr [data_004918b4],esi
    L_0043c6d4:
        sub edx,0
    L_0043c6d7:
        je short L_0043c6f1
    L_0043c6d9:
        dec edx
    L_0043c6da:
        je short L_0043c6e1
    L_0043c6dc:
        dec edx
    L_0043c6dd:
        jne short L_0043c6fb
    L_0043c6df:
        fchs
    L_0043c6e1:
        fstp dword ptr [data_00491e68]
    L_0043c6e7:
        mov eax,1
    L_0043c6ec:
        pop esi
    L_0043c6ed:
        add esp,0Ch
    L_0043c6f0:
        ret
    L_0043c6f1:
        mov dword ptr [data_00491e68],0
    L_0043c6fb:
        fstp st(0)
    L_0043c6fd:
        mov eax,1
    L_0043c702:
        pop esi
    L_0043c703:
        add esp,0Ch
    L_0043c706:
        ret
    }
}

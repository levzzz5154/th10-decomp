#include "asm_encoding.hpp"
#include "asm_symbols.hpp"



// 0x00405620..0x004056A8: Recovery_ReleaseRawPairAndReset
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReleaseRawPairAndReset_00405620() {
    __asm {
    L_00405620:
        mov eax,dword ptr [esp+4]
    L_00405624:
        push ebx
    L_00405625:
        mov ebx,dword ptr [data_004660b0]
    L_0040562b:
        push ebp
    L_0040562c:
        mov ebp,dword ptr [data_004660b4]
    L_00405632:
        push esi
    L_00405633:
        mov esi,dword ptr [eax+8]
    L_00405636:
        test esi,esi
    L_00405638:
        push edi
    L_00405639:
        mov edi,dword ptr [data_00491be4]
    L_0040563f:
        je short L_00405664
    L_00405641:
        push 492274h
    L_00405646:
        call ebx
    L_00405648:
        inc byte ptr [data_0049231c]
    L_0040564e:
        mov ecx,esi
    L_00405650:
        mov edx,edi
    L_00405652:
        call asm_Scheduler_Remove_00449f60
    L_00405657:
        push 492274h
    L_0040565c:
        call ebp
    L_0040565e:
        dec byte ptr [data_0049231c]
    L_00405664:
        mov ecx,dword ptr [esp+14h]
    L_00405668:
        mov esi,dword ptr [ecx+0Ch]
    L_0040566b:
        test esi,esi
    L_0040566d:
        mov edi,dword ptr [data_00491be4]
    L_00405673:
        je short L_00405698
    L_00405675:
        push 492274h
    L_0040567a:
        call ebx
    L_0040567c:
        inc byte ptr [data_0049231c]
    L_00405682:
        mov ecx,esi
    L_00405684:
        mov edx,edi
    L_00405686:
        call asm_Scheduler_Remove_00449f60
    L_0040568b:
        push 492274h
    L_00405690:
        call ebp
    L_00405692:
        dec byte ptr [data_0049231c]
    L_00405698:
        pop edi
    L_00405699:
        pop esi
    L_0040569a:
        pop ebp
    L_0040569b:
        mov dword ptr [data_004776ec],0
    L_004056a5:
        pop ebx
    L_004056a6:
        ret 4
    }
}



// 0x004059F0..0x00405AB9: Player_HitTestRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_HitTestRetail_004059f0() {
    __asm {
    L_004059f0:
        mov edx,dword ptr [ecx+28h]
    L_004059f3:
        test edx,edx
    L_004059f5:
        jne short L_004059fa
    L_004059f7:
        xor eax,eax
    L_004059f9:
        ret
    L_004059fa:
        fld dword ptr [eax+4]
    L_004059fd:
        xor edx,edx
    L_004059ff:
        fsub dword ptr [ecx+34h]
    L_00405a02:
        fld dword ptr [eax]
    L_00405a04:
        fsub dword ptr [ecx+30h]
    L_00405a07:
        fld dword ptr [ecx+3Ch]
    L_00405a0a:
        fld st(1)
    L_00405a0c:
        fmul st,st(2)
    L_00405a0e:
        fld st(3)
    L_00405a10:
        fmul st,st(4)
    L_00405a12:
        faddp st(1),st
    L_00405a14:
        fld st(1)
    L_00405a16:
        fmul st,st(2)
    L_00405a18:
        fcompp
    L_00405a1a:
        fstp st(0)
    L_00405a1c:
        fnstsw ax
    L_00405a1e:
        fstp st(0)
    L_00405a20:
        test ah,41h
    L_00405a23:
        fstp st(0)
    L_00405a25:
        jne short L_00405a68
    L_00405a27:
        mov eax,dword ptr [ecx+44h]
    L_00405a2a:
        test eax,eax
    L_00405a2c:
        mov eax,dword ptr [data_004776f4]
    L_00405a31:
        mov cl,byte ptr [eax+378Ch]
    L_00405a37:
        jne short L_00405a46
    L_00405a39:
        test cl,1
    L_00405a3c:
        je short L_00405a53
    L_00405a3e:
        mov edx,3
    L_00405a43:
        mov eax,edx
    L_00405a45:
        ret
    L_00405a46:
        test cl,1
    L_00405a49:
        je short L_00405a53
    L_00405a4b:
        mov edx,26h
    L_00405a50:
        mov eax,edx
    L_00405a52:
        ret
    L_00405a53:
        mov eax,dword ptr [data_00477704]
    L_00405a58:
        mov edx,dword ptr [eax+10h]
    L_00405a5b:
        neg edx
    L_00405a5d:
        sbb edx,edx
    L_00405a5f:
        and edx,21h
    L_00405a62:
        add edx,5
    L_00405a65:
        mov eax,edx
    L_00405a67:
        ret
    L_00405a68:
        mov eax,dword ptr [data_004776f4]
    L_00405a6d:
        test byte ptr [eax+378Ch],1
    L_00405a74:
        je short L_00405a8f
    L_00405a76:
        cmp dword ptr [ecx+44h],1
    L_00405a7a:
        jne short L_00405ab7
    L_00405a7c:
        mov edx,dword ptr [data_00474c68]
    L_00405a82:
        neg edx
    L_00405a84:
        sbb edx,edx
    L_00405a86:
        and edx,0FFFFFFFDh
    L_00405a89:
        add edx,1Ah
    L_00405a8c:
        mov eax,edx
    L_00405a8e:
        ret
    L_00405a8f:
        mov eax,dword ptr [data_00477704]
    L_00405a94:
        push esi
    L_00405a95:
        mov esi,dword ptr [eax+10h]
    L_00405a98:
        test esi,esi
    L_00405a9a:
        pop esi
    L_00405a9b:
        je short L_00405ab7
    L_00405a9d:
        mov eax,dword ptr [ecx+44h]
    L_00405aa0:
        test eax,eax
    L_00405aa2:
        jne short L_00405ab7
    L_00405aa4:
        mov eax,dword ptr [data_00474c68]
    L_00405aa9:
        xor edx,edx
    L_00405aab:
        test eax,eax
    L_00405aad:
        sete dl
    L_00405ab0:
        lea edx,[edx*4+10h]
    L_00405ab7:
        mov eax,edx
    L_00405ab9:
        ret
    }
}


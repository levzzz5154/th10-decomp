#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C8C0..0x0041CA79: FUN_0041c8c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c8c0_0041c8c0() {
    __asm {
    L_0041c8c0:
        push ecx
    L_0041c8c1:
        push ebx
    L_0041c8c2:
        mov ebx,ecx
    L_0041c8c4:
        push ebp
    L_0041c8c5:
        push esi
    L_0041c8c6:
        mov esi,dword ptr [esp+14h]
    L_0041c8ca:
        push edi
    L_0041c8cb:
        lea ebp,[ebx+424h]
    L_0041c8d1:
        mov ecx,77h
    L_0041c8d6:
        mov edi,ebp
    L_0041c8d8:
        rep movsd
    L_0041c8da:
        movsx ecx,word ptr [ebx+448h]
    L_0041c8e1:
        movsx eax,word ptr [ebx+44Ah]
    L_0041c8e8:
        mov edi,2
    L_0041c8ed:
        mov dword ptr [ebx+0Ch],edi
    L_0041c8f0:
        add eax,dword ptr [ecx*4+474170h]
    L_0041c8f7:
        mov edx,dword ptr [data_0047781c]
    L_0041c8fd:
        mov ecx,dword ptr [edx+458h]
    L_0041c903:
        lea esi,[ebx+600h]
    L_0041c909:
        push ecx
    L_0041c90a:
        call asm_FUN_00404f30_00404f30
    L_0041c90f:
        push esi
    L_0041c910:
        mov word ptr [ebx+904h],di
    L_0041c917:
        call asm_FUN_0043ee30_0043ee30
    L_0041c91c:
        test byte ptr [ebx+44Ch],1
    L_0041c923:
        je short L_0041c937
    L_0041c925:
        mov edx,dword ptr [esi+35Ch]
    L_0041c92b:
        and edx,0FFFFFFDFh
    L_0041c92e:
        or edx,10h
    L_0041c931:
        mov dword ptr [esi+35Ch],edx
    L_0041c937:
        mov eax,dword ptr [ebx+95Ch]
    L_0041c93d:
        mov ecx,dword ptr [data_0047781c]
    L_0041c943:
        and eax,0FC63FFFFh
    L_0041c948:
        or eax,600000h
    L_0041c94d:
        mov dword ptr [ebx+95Ch],eax
    L_0041c953:
        movsx eax,word ptr [ebx+44Ah]
    L_0041c95a:
        mov edx,dword ptr [ecx+458h]
    L_0041c960:
        lea esi,[ebx+9ACh]
    L_0041c966:
        add eax,103h
    L_0041c96b:
        push edx
    L_0041c96c:
        call asm_FUN_00404f30_00404f30
    L_0041c971:
        push esi
    L_0041c972:
        mov word ptr [ebx+0CB0h],di
    L_0041c979:
        call asm_FUN_0043ee30_0043ee30
    L_0041c97e:
        mov eax,dword ptr [esi+35Ch]
    L_0041c984:
        and eax,0FFFFFFDFh
    L_0041c987:
        or eax,10h
    L_0041c98a:
        mov dword ptr [esi+35Ch],eax
    L_0041c990:
        mov ecx,dword ptr [ebx+0D08h]
    L_0041c996:
        and ecx,0FC7FFFFFh
    L_0041c99c:
        or ecx,400000h
    L_0041c9a2:
        mov dword ptr [ebx+0D08h],ecx
    L_0041c9a8:
        mov eax,dword ptr [ebx+420h]
    L_0041c9ae:
        xor ecx,ecx
    L_0041c9b0:
        test al,1
    L_0041c9b2:
        jne short L_0041c9dd
    L_0041c9b4:
        or eax,1
    L_0041c9b7:
        mov dword ptr [ebx+414h],ecx
    L_0041c9bd:
        mov dword ptr [ebx+410h],0FFF0BDC1h
    L_0041c9c7:
        mov dword ptr [ebx+418h],ecx
    L_0041c9cd:
        mov dword ptr [ebx+41Ch],476F78h
    L_0041c9d7:
        mov dword ptr [ebx+420h],eax
    L_0041c9dd:
        mov dword ptr [ebx+414h],1Eh
    L_0041c9e7:
        mov dword ptr [ebx+418h],41F00000h
    L_0041c9f1:
        mov dword ptr [ebx+410h],1Dh
    L_0041c9fb:
        fld dword ptr [ebx+438h]
    L_0041ca01:
        mov eax,dword ptr [ebp]
    L_0041ca04:
        fst dword ptr [ebx+40h]
    L_0041ca07:
        fld dword ptr [ebx+444h]
    L_0041ca0d:
        lea edx,[ebx+24h]
    L_0041ca10:
        fst dword ptr [esp+18h]
    L_0041ca14:
        mov dword ptr [edx],eax
    L_0041ca16:
        mov eax,dword ptr [ebp+4]
    L_0041ca19:
        fstp dword ptr [ebx+48h]
    L_0041ca1c:
        fld dword ptr [ebx+430h]
    L_0041ca22:
        mov dword ptr [edx+4],eax
    L_0041ca25:
        mov eax,dword ptr [ebp+8]
    L_0041ca28:
        fst dword ptr [esp+10h]
    L_0041ca2c:
        fstp dword ptr [ebx+3Ch]
    L_0041ca2f:
        mov dword ptr [edx+8],eax
    L_0041ca32:
        mov edx,dword ptr [ebx+440h]
    L_0041ca38:
        fcomp dword ptr [data_00470b04]
    L_0041ca3e:
        mov dword ptr [ebx+40Ch],18h
    L_0041ca48:
        mov dword ptr [ebx+44h],edx
    L_0041ca4b:
        fnstsw ax
    L_0041ca4d:
        test ah,41h
    L_0041ca50:
        jne short L_0041ca5b
    L_0041ca52:
        mov dword ptr [ebx+4Ch],3C23D70Ah
    L_0041ca59:
        jmp short L_0041ca5e
    L_0041ca5b:
        mov dword ptr [ebx+4Ch],ecx
    L_0041ca5e:
        mov eax,dword ptr [esp+18h]
    L_0041ca62:
        mov ecx,dword ptr [esp+10h]
    L_0041ca66:
        push eax
    L_0041ca67:
        push ecx
    L_0041ca68:
        lea ecx,[ebx+30h]
    L_0041ca6b:
        call asm_SetPolar_Vector2_0041f800
    L_0041ca70:
        pop edi
    L_0041ca71:
        pop esi
    L_0041ca72:
        pop ebp
    L_0041ca73:
        xor eax,eax
    L_0041ca75:
        pop ebx
    L_0041ca76:
        pop ecx
    L_0041ca77:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004067D0..0x004067E6: FUN_004067d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004067d0_004067d0() {
    __asm {
    L_004067d0:
        mov eax,dword ptr [esp+4]
    L_004067d4:
        mov ecx,dword ptr [esp+8]
    L_004067d8:
        sub esp,14h
    L_004067db:
        push ebp
    L_004067dc:
        mov ebp,dword ptr [eax+10h]
    L_004067df:
        push esi
    L_004067e0:
        push edi
    L_004067e1:
        xor edi,edi
    L_004067e3:
        xor esi,esi
    L_004067e5:
        TH10_REL8(0xeb, 0x004067e5, VA_asm_FUN_004067d0_part_004067f0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_004067f0:
        cmp word ptr [ebp+446h],di
    L_004067f7:
        je asm_target_004068ac
    L_004067fd:
        add ebp,7F0h
    L_00406803:
        mov edx,5
    L_00406808:
        cmp word ptr [ebp+446h],dx
    L_0040680f:
        jne short L_00406814
    L_00406811:
        lea ebp,[eax+60h]
    L_00406814:
        cmp word ptr [ebp+446h],di
    L_0040681b:
        je short L_0040689c
    L_0040681d:
        add ebp,7F0h
    L_00406823:
        cmp word ptr [ebp+446h],dx
    L_0040682a:
        jne short L_0040682f
    L_0040682c:
        lea ebp,[eax+60h]
    L_0040682f:
        cmp word ptr [ebp+446h],di
    L_00406836:
        je short L_0040689f
    L_00406838:
        add ebp,7F0h
    L_0040683e:
        cmp word ptr [ebp+446h],dx
    L_00406845:
        jne short L_0040684a
    L_00406847:
        lea ebp,[eax+60h]
    L_0040684a:
        cmp word ptr [ebp+446h],di
    L_00406851:
        je short L_004068a4
    L_00406853:
        add ebp,7F0h
    L_00406859:
        cmp word ptr [ebp+446h],dx
    L_00406860:
        jne short L_00406865
    L_00406862:
        lea ebp,[eax+60h]
    L_00406865:
        cmp word ptr [ebp+446h],di
    L_0040686c:
        je short L_004068a9
    L_0040686e:
        add ebp,7F0h
    L_00406874:
        cmp word ptr [ebp+446h],dx
    L_0040687b:
        jne short L_00406880
    L_0040687d:
        lea ebp,[eax+60h]
    L_00406880:
        add esi,edx
    L_00406882:
        cmp esi,7D0h
    L_00406888:
        jl asm_FUN_004067d0_part_004067f0
    L_0040688e:
        pop edi
    L_0040688f:
        pop esi
    L_00406890:
        mov eax,1
    L_00406895:
        pop ebp
    L_00406896:
        add esp,14h
    L_00406899:
        ret 10h
    L_0040689c:
        inc esi
    L_0040689d:
        jmp short L_004068ac
    L_0040689f:
        add esi,2
    L_004068a2:
        jmp short L_004068ac
    L_004068a4:
        add esi,3
    L_004068a7:
        jmp short L_004068ac
    L_004068a9:
        add esi,4
    L_004068ac:
        cmp esi,7D0h
    L_004068b2:
        jl short L_004068c2
    L_004068b4:
        pop edi
    L_004068b5:
        pop esi
    L_004068b6:
        mov eax,1
    L_004068bb:
        pop ebp
    L_004068bc:
        add esp,14h
    L_004068bf:
        ret 10h
    L_004068c2:
        mov ax,word ptr [ebx+1F6h]
    L_004068c9:
        cmp ax,1
    L_004068cd:
        mov dword ptr [esp+0Ch],0
    L_004068d5:
        jle short L_004068f8
    L_004068d7:
        fld dword ptr [ebx+18h]
    L_004068da:
        movsx eax,ax
    L_004068dd:
        fld st(0)
    L_004068df:
        mov dword ptr [esp+10h],eax
    L_004068e3:
        fsub dword ptr [ebx+1Ch]
    L_004068e6:
        fimul dword ptr [esp+2Ch]
    L_004068ea:
        fidiv dword ptr [esp+10h]
    L_004068ee:
        fsubr st,st(1)
    L_004068f0:
        fstp dword ptr [esp+10h]
    L_004068f4:
        fstp st(0)
    L_004068f6:
        jmp short L_004068ff
    L_004068f8:
        mov edx,dword ptr [ebx+18h]
    L_004068fb:
        mov dword ptr [esp+10h],edx
    L_004068ff:
        mov si,word ptr [ebx+1F8h]
    L_00406906:
        movzx eax,si
    L_00406909:
        cmp eax,8
    L_0040690c:
        ja asm_target_00406a7f
    L_00406912:
        jmp dword ptr [eax*4+406D58h]
    L_00406919:
        test byte ptr [ebx+1F4h],1
    L_00406920:
        je short L_00406934
    L_00406922:
        lea eax,[ecx+1]
    L_00406925:
        cdq
    L_00406926:
        sub eax,edx
    L_00406928:
        sar eax,1
    L_0040692a:
        mov dword ptr [esp+28h],eax
    L_0040692e:
        fild dword ptr [esp+28h]
    L_00406932:
        jmp short L_00406949
    L_00406934:
        mov eax,ecx
    L_00406936:
        cdq
    L_00406937:
        sub eax,edx
    L_00406939:
        sar eax,1
    L_0040693b:
        mov dword ptr [esp+28h],eax
    L_0040693f:
        fild dword ptr [esp+28h]
    L_00406943:
        fadd dword ptr [data_00470b0c]
    L_00406949:
        test cl,1
    L_0040694c:
        fmul dword ptr [ebx+14h]
    L_0040694f:
        je short L_00406957
    L_00406951:
        fmul dword ptr [data_00470b60]
    L_00406957:
        cmp si,di
    L_0040695a:
        jne short L_00406960
    L_0040695c:
        fadd dword ptr [esp+30h]
    L_00406960:
        fadd dword ptr [ebx+10h]
    L_00406963:
        fstp dword ptr [esp+0Ch]
    L_00406967:
        jmp asm_target_00406a7f
    L_0040696c:
        mov eax,dword ptr [esp+30h]
    L_00406970:
        mov dword ptr [esp+0Ch],eax
    L_00406974:
        fild dword ptr [esp+28h]
    L_00406978:
        movsx ecx,word ptr [ebx+1F4h]
    L_0040697f:
        mov dword ptr [esp+28h],ecx
    L_00406983:
        fmul dword ptr [data_00470b14]
    L_00406989:
        fidiv dword ptr [esp+28h]
    L_0040698d:
        fadd dword ptr [esp+0Ch]
    L_00406991:
        fild dword ptr [esp+2Ch]
    L_00406995:
        fmul dword ptr [ebx+14h]
    L_00406998:
        faddp st(1),st
    L_0040699a:
        fadd dword ptr [ebx+10h]
    L_0040699d:
        fstp dword ptr [esp+0Ch]
    L_004069a1:
        jmp asm_target_00406a7f
    L_004069a6:
        mov edx,dword ptr [esp+30h]
    L_004069aa:
        mov dword ptr [esp+0Ch],edx
    L_004069ae:
        movsx eax,word ptr [ebx+1F4h]
    L_004069b5:
        mov dword ptr [esp+30h],eax
    L_004069b9:
        fild dword ptr [esp+30h]
    L_004069bd:
        fld dword ptr [data_00470b18]
    L_004069c3:
        fdiv st,st(1)
    L_004069c5:
        fadd dword ptr [esp+0Ch]
    L_004069c9:
        fild dword ptr [esp+28h]
    L_004069cd:
        fmul dword ptr [data_00470b14]
    L_004069d3:
        fdiv st,st(2)
    L_004069d5:
        faddp st(1),st
    L_004069d7:
        fild dword ptr [esp+2Ch]
    L_004069db:
        fmul dword ptr [ebx+14h]
    L_004069de:
        faddp st(1),st
    L_004069e0:
        fadd dword ptr [ebx+10h]
    L_004069e3:
        fstp dword ptr [esp+0Ch]
    L_004069e7:
        fstp st(0)
    L_004069e9:
        jmp asm_target_00406a7f
    L_004069ee:
        fld dword ptr [ebx+10h]
    L_004069f1:
        mov ecx,4918B0h
    L_004069f6:
        fsub dword ptr [ebx+14h]
    L_004069f9:
        call asm_Rng_NextFloat_0044bb20
    L_004069fe:
        fmulp st(1),st
    L_00406a00:
        fadd dword ptr [ebx+14h]
    L_00406a03:
        fstp dword ptr [esp+0Ch]
    L_00406a07:
        jmp short L_00406a7f
    L_00406a09:
        fld dword ptr [ebx+18h]
    L_00406a0c:
        mov ecx,4918B0h
    L_00406a11:
        fsub dword ptr [ebx+1Ch]
    L_00406a14:
        call asm_Rng_NextFloat_0044bb20
    L_00406a19:
        movsx ecx,word ptr [ebx+1F4h]
    L_00406a20:
        fmulp st(1),st
    L_00406a22:
        fadd dword ptr [ebx+1Ch]
    L_00406a25:
        fstp dword ptr [esp+10h]
    L_00406a29:
        fild dword ptr [esp+28h]
    L_00406a2d:
        mov dword ptr [esp+28h],ecx
    L_00406a31:
        fmul dword ptr [data_00470b14]
    L_00406a37:
        fidiv dword ptr [esp+28h]
    L_00406a3b:
        fild dword ptr [esp+2Ch]
    L_00406a3f:
        fmul dword ptr [ebx+14h]
    L_00406a42:
        faddp st(1),st
    L_00406a44:
        fadd dword ptr [ebx+10h]
    L_00406a47:
        fstp dword ptr [esp+0Ch]
    L_00406a4b:
        jmp short L_00406a7f
    L_00406a4d:
        fld dword ptr [ebx+10h]
    L_00406a50:
        mov ecx,4918B0h
    L_00406a55:
        fsub dword ptr [ebx+14h]
    L_00406a58:
        call asm_Rng_NextFloat_0044bb20
    L_00406a5d:
        mov ecx,4918B0h
    L_00406a62:
        fmulp st(1),st
    L_00406a64:
        fadd dword ptr [ebx+14h]
    L_00406a67:
        fstp dword ptr [esp+0Ch]
    L_00406a6b:
        fld dword ptr [ebx+18h]
    L_00406a6e:
        fsub dword ptr [ebx+1Ch]
    L_00406a71:
        call asm_Rng_NextFloat_0044bb20
    L_00406a76:
        fmulp st(1),st
    L_00406a78:
        fadd dword ptr [ebx+1Ch]
    L_00406a7b:
        fstp dword ptr [esp+10h]
    L_00406a7f:
        or dword ptr [ebp],1
    L_00406a83:
        mov word ptr [ebp+446h],1
    L_00406a8c:
        mov eax,dword ptr [ebp+408h]
    L_00406a92:
        test al,1
    L_00406a94:
        mov esi,0FFF0BDC1h
    L_00406a99:
        mov edx,476F78h
    L_00406a9e:
        jne short L_00406ac1
    L_00406aa0:
        or eax,1
    L_00406aa3:
        mov dword ptr [ebp+3FCh],edi
    L_00406aa9:
        mov dword ptr [ebp+3F8h],esi
    L_00406aaf:
        mov dword ptr [ebp+400h],edi
    L_00406ab5:
        mov dword ptr [ebp+404h],edx
    L_00406abb:
        mov dword ptr [ebp+408h],eax
    L_00406ac1:
        or ecx,0FFFFFFFFh
    L_00406ac4:
        mov dword ptr [ebp+3FCh],edi
    L_00406aca:
        mov dword ptr [ebp+400h],edi
    L_00406ad0:
        mov dword ptr [ebp+3F8h],ecx
    L_00406ad6:
        mov eax,dword ptr [ebp+41Ch]
    L_00406adc:
        test al,1
    L_00406ade:
        jne short L_00406b01
    L_00406ae0:
        or eax,1
    L_00406ae3:
        mov dword ptr [ebp+410h],edi
    L_00406ae9:
        mov dword ptr [ebp+40Ch],esi
    L_00406aef:
        mov dword ptr [ebp+414h],edi
    L_00406af5:
        mov dword ptr [ebp+418h],edx
    L_00406afb:
        mov dword ptr [ebp+41Ch],eax
    L_00406b01:
        mov edx,dword ptr [esp+10h]
    L_00406b05:
        mov esi,dword ptr [esp+0Ch]
    L_00406b09:
        push edi
    L_00406b0a:
        mov dword ptr [ebp+40Ch],ecx
    L_00406b10:
        mov dword ptr [ebp+410h],edi
    L_00406b16:
        mov dword ptr [ebp+414h],edi
    L_00406b1c:
        push esi
    L_00406b1d:
        mov dword ptr [ebp+3D8h],edx
    L_00406b23:
        call asm_Angle_NormalizeSum_0044bc10
    L_00406b28:
        fstp dword ptr [ebp+3E4h]
    L_00406b2e:
        lea eax,[ebx+4]
    L_00406b31:
        mov edx,dword ptr [eax]
    L_00406b33:
        lea edi,[ebp+3B4h]
    L_00406b39:
        mov ecx,edi
    L_00406b3b:
        mov dword ptr [ecx],edx
    L_00406b3d:
        mov edx,dword ptr [eax+4]
    L_00406b40:
        mov dword ptr [ecx+4],edx
    L_00406b43:
        mov eax,dword ptr [eax+8]
    L_00406b46:
        mov edx,dword ptr [esp+10h]
    L_00406b4a:
        mov dword ptr [ecx+8],eax
    L_00406b4d:
        push edx
    L_00406b4e:
        lea ecx,[ebp+3C0h]
    L_00406b54:
        push esi
    L_00406b55:
        mov dword ptr [ebp+3BCh],3DCCCCCDh
    L_00406b5f:
        call asm_Score_SetPolarVector_00408750
    L_00406b64:
        mov eax,dword ptr [ebx+1FCh]
    L_00406b6a:
        mov dword ptr [ebp+43Ch],eax
    L_00406b70:
        mov cx,word ptr [ebx+2]
    L_00406b74:
        mov eax,dword ptr [ebp]
    L_00406b77:
        mov word ptr [ebp+7ECh],cx
    L_00406b7e:
        mov dx,word ptr [ebx]
    L_00406b81:
        and eax,0FFFFFFF3h
    L_00406b84:
        mov word ptr [ebp+7EAh],dx
    L_00406b8b:
        or eax,2
    L_00406b8e:
        mov dword ptr [ebp],eax
    L_00406b91:
        mov dword ptr [ebp+454h],0
    L_00406b9b:
        movsx ecx,word ptr [ebx]
    L_00406b9e:
        movsx eax,word ptr [ebx+2]
    L_00406ba2:
        add eax,dword ptr [ecx*4+474170h]
    L_00406ba9:
        mov edx,dword ptr [esp+24h]
    L_00406bad:
        mov ecx,dword ptr [edx+3E0B50h]
    L_00406bb3:
        lea esi,[ebp+8]
    L_00406bb6:
        push ecx
    L_00406bb7:
        call asm_FUN_00404f30_00404f30
    L_00406bbc:
        movsx edx,word ptr [ebx]
    L_00406bbf:
        mov eax,dword ptr [edx*4+4742C0h]
    L_00406bc6:
        cmp eax,4
    L_00406bc9:
        ja short L_00406c17
    L_00406bcb:
        jmp dword ptr [eax*4+406D7Ch]
    L_00406bd2:
        movsx eax,word ptr [ebx+2]
    L_00406bd6:
        lea ecx,[eax+eax+11h]
    L_00406bda:
        mov dword ptr [ebp+438h],ecx
    L_00406be0:
        jmp short L_00406c17
    L_00406be2:
        movsx edx,word ptr [ebx+2]
    L_00406be6:
        mov eax,dword ptr [edx*4+47432Ch]
    L_00406bed:
        mov dword ptr [ebp+438h],eax
    L_00406bf3:
        jmp short L_00406c17
    L_00406bf5:
        mov dword ptr [ebp+438h],0FFFFFFFFh
    L_00406bff:
        jmp short L_00406c17
    L_00406c01:
        mov dword ptr [ebp+438h],1Dh
    L_00406c0b:
        jmp short L_00406c17
    L_00406c0d:
        mov dword ptr [ebp+438h],13h
    L_00406c17:
        movsx ecx,word ptr [ebx]
    L_00406c1a:
        mov edx,dword ptr [ecx*4+474250h]
    L_00406c21:
        mov dword ptr [ebp+460h],edx
    L_00406c27:
        mov eax,dword ptr [ebx+204h]
    L_00406c2d:
        mov dword ptr [ebp+458h],eax
    L_00406c33:
        mov dword ptr [ebp+434h],0Ah
    L_00406c3d:
        movsx ecx,word ptr [ebx]
    L_00406c40:
        fld dword ptr [ecx*4+4741E0h]
    L_00406c47:
        fst dword ptr [ebp+3F4h]
    L_00406c4d:
        fstp dword ptr [ebp+3F0h]
    L_00406c53:
        mov eax,dword ptr [ebx+1FCh]
    L_00406c59:
        test al,2
    L_00406c5b:
        je short L_00406cb5
    L_00406c5d:
        mov word ptr [ebp+30Ch],7
    L_00406c66:
        mov word ptr [ebp+446h],2
    L_00406c6f:
        fld dword ptr [ebp+3C0h]
    L_00406c75:
        fmul dword ptr [data_00470c40]
    L_00406c7b:
        fld dword ptr [ebp+3C4h]
    L_00406c81:
        fmul dword ptr [data_00470c40]
    L_00406c87:
        fld dword ptr [ebp+3C8h]
    L_00406c8d:
        fmul dword ptr [data_00470c40]
    L_00406c93:
        fstp dword ptr [esp+1Ch]
    L_00406c97:
        fld dword ptr [edi]
    L_00406c99:
        fsub st,st(2)
    L_00406c9b:
        fstp dword ptr [edi]
    L_00406c9d:
        fld dword ptr [edi+4]
    L_00406ca0:
        fsub st,st(1)
    L_00406ca2:
        fstp dword ptr [edi+4]
    L_00406ca5:
        fstp st(0)
    L_00406ca7:
        fstp st(0)
    L_00406ca9:
        fld dword ptr [edi+8]
    L_00406cac:
        fsub dword ptr [esp+1Ch]
    L_00406cb0:
        fstp dword ptr [edi+8]
    L_00406cb3:
        jmp short L_00406cdc
    L_00406cb5:
        test al,4
    L_00406cb7:
        je short L_00406cc4
    L_00406cb9:
        mov word ptr [ebp+30Ch],8
    L_00406cc2:
        jmp short L_00406c66
    L_00406cc4:
        test al,8
    L_00406cc6:
        je short L_00406cd3
    L_00406cc8:
        mov word ptr [ebp+30Ch],9
    L_00406cd1:
        jmp short L_00406c66
    L_00406cd3:
        mov word ptr [ebp+30Ch],2
    L_00406cdc:
        lea esi,[ebx+20h]
    L_00406cdf:
        lea edi,[ebp+464h]
    L_00406ce5:
        mov ecx,6Ch
    L_00406cea:
        rep movsd
    L_00406cec:
        mov edx,dword ptr [ebx+1FCh]
    L_00406cf2:
        mov dword ptr [ebp+440h],edx
    L_00406cf8:
        mov dword ptr [ebp+43Ch],0
    L_00406d02:
        mov eax,dword ptr [ebx+208h]
    L_00406d08:
        mov ecx,ebp
    L_00406d0a:
        mov dword ptr [ebp+45Ch],eax
    L_00406d10:
        call asm_FUN_00406d90_00406d90
    L_00406d15:
        lea eax,[ebp+8]
    L_00406d18:
        push eax
    L_00406d19:
        call asm_FUN_0043ee30_0043ee30
    L_00406d1e:
        add ebp,7F0h
    L_00406d24:
        cmp word ptr [ebp+446h],5
    L_00406d2c:
        jne short L_00406d43
    L_00406d2e:
        mov eax,dword ptr [esp+24h]
    L_00406d32:
        pop edi
    L_00406d33:
        lea ecx,[eax+60h]
    L_00406d36:
        pop esi
    L_00406d37:
        mov dword ptr [eax+10h],ecx
    L_00406d3a:
        xor eax,eax
    L_00406d3c:
        pop ebp
    L_00406d3d:
        add esp,14h
    L_00406d40:
        ret 10h
    L_00406d43:
        mov edx,dword ptr [esp+24h]
    L_00406d47:
        pop edi
    L_00406d48:
        pop esi
    L_00406d49:
        mov dword ptr [edx+10h],ebp
    L_00406d4c:
        xor eax,eax
    L_00406d4e:
        pop ebp
    L_00406d4f:
        add esp,14h
    L_00406d52:
        ret 10h
        _emit 0x8d
        _emit 0x49
        _emit 0x00
        _emit 0x19
        _emit 0x69
        _emit 0x40
        _emit 0x00
        _emit 0x19
        _emit 0x69
        _emit 0x40
        _emit 0x00
        _emit 0x6c
        _emit 0x69
        _emit 0x40
        _emit 0x00
        _emit 0x74
        _emit 0x69
        _emit 0x40
        _emit 0x00
        _emit 0xa6
        _emit 0x69
        _emit 0x40
        _emit 0x00
        _emit 0xae
        _emit 0x69
        _emit 0x40
        _emit 0x00
        _emit 0xee
        _emit 0x69
        _emit 0x40
        _emit 0x00
        _emit 0x09
        _emit 0x6a
        _emit 0x40
        _emit 0x00
        _emit 0x4d
        _emit 0x6a
        _emit 0x40
        _emit 0x00
        _emit 0xd2
        _emit 0x6b
        _emit 0x40
        _emit 0x00
        _emit 0xe2
        _emit 0x6b
        _emit 0x40
        _emit 0x00
        _emit 0xf5
        _emit 0x6b
        _emit 0x40
        _emit 0x00
        _emit 0x01
        _emit 0x6c
        _emit 0x40
        _emit 0x00
        _emit 0x0d
        _emit 0x6c
        _emit 0x40
        _emit 0x00
    }
}

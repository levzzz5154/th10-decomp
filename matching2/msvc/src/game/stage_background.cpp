#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C3C0..0x0040C43D: StageBackground_RebindTextureRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageBackground_RebindTextureRetail_0040c3c0() {
    __asm {
    L_0040c3c0:
        mov eax,dword ptr [ebx+70h]
    L_0040c3c3:
        push esi
    L_0040c3c4:
        push edi
    L_0040c3c5:
        mov byte ptr [data_00497c38],0
    L_0040c3cc:
        mov esi,eax
    L_0040c3ce:
        mov edi,edi
    L_0040c3d0:
        mov cl,byte ptr [eax]
    L_0040c3d2:
        inc eax
    L_0040c3d3:
        test cl,cl
    L_0040c3d5:
        jne short L_0040c3d0
    L_0040c3d7:
        mov edi,497C38h
    L_0040c3dc:
        sub eax,esi
    L_0040c3de:
        dec edi
    L_0040c3df:
        nop
    L_0040c3e0:
        mov cl,byte ptr [edi+1]
    L_0040c3e3:
        inc edi
    L_0040c3e4:
        test cl,cl
    L_0040c3e6:
        jne short L_0040c3e0
    L_0040c3e8:
        mov edx,dword ptr [data_00491c10]
    L_0040c3ee:
        mov ecx,eax
    L_0040c3f0:
        shr ecx,2
    L_0040c3f3:
        rep movsd
    L_0040c3f5:
        mov ecx,eax
    L_0040c3f7:
        and ecx,3
    L_0040c3fa:
        rep movsb
    L_0040c3fc:
        mov eax,dword ptr [ebx+54h]
    L_0040c3ff:
        mov ecx,dword ptr [eax+4]
    L_0040c402:
        push 497C38h
    L_0040c407:
        add ecx,1Dh
    L_0040c40a:
        call asm_Recovery_LoadCachedResource_00447280
    L_0040c40f:
        mov ecx,dword ptr [ebx+54h]
    L_0040c412:
        mov edx,dword ptr [ecx+4]
    L_0040c415:
        mov esi,dword ptr [data_004776e0]
    L_0040c41b:
        mov dword ptr [ebx+edx*4+80h],eax
    L_0040c422:
        and dword ptr [ebx+74h],0FFFFFFFBh
    L_0040c426:
        add esi,89A4h
    L_0040c42c:
        mov eax,esi
    L_0040c42e:
        call asm_FUN_00409e50_00409e50
    L_0040c433:
        pop edi
    L_0040c434:
        mov dword ptr [esi],0
    L_0040c43a:
        xor eax,eax
    L_0040c43c:
        pop esi
    L_0040c43d:
        ret
    }
}

// 0x00427960..0x00427A09: FUN_00427960
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427960_00427960() {
    __asm {
    L_00427960:
        sub esp,0Ch
    L_00427963:
        mov eax,dword ptr [esi+88h]
    L_00427969:
        push ebx
    L_0042796a:
        push ebp
    L_0042796b:
        push edi
    L_0042796c:
        mov edi,dword ptr [data_00477834]
    L_00427972:
        mov ebx,dword ptr [edi+4474h]
    L_00427978:
        shl eax,6
    L_0042797b:
        test ebx,ebx
    L_0042797d:
        mov ecx,dword ptr [eax+edi+43ACh]
    L_00427984:
        lea eax,[eax+edi+43ACh]
    L_0042798b:
        mov dword ptr [esi+34h],ecx
    L_0042798e:
        mov edx,dword ptr [eax+4]
    L_00427991:
        mov dword ptr [esp+14h],ebx
    L_00427995:
        mov dword ptr [esi+38h],edx
    L_00427998:
        jne short L_004279b9
    L_0042799a:
        mov ebp,dword ptr [edi+3CCh]
    L_004279a0:
        mov eax,ecx
    L_004279a2:
        mov ecx,edx
    L_004279a4:
        mov edx,dword ptr [edi+3D0h]
    L_004279aa:
        sub eax,ebp
    L_004279ac:
        sub ecx,edx
    L_004279ae:
        mov dword ptr [esi+44h],eax
    L_004279b1:
        mov dword ptr [esi+48h],ecx
    L_004279b4:
        jmp asm_target_00427a9e
    L_004279b9:
        mov edx,dword ptr [esi+48h]
    L_004279bc:
        fld dword ptr [data_00470b90]
    L_004279c2:
        mov ecx,dword ptr [edi+3D0h]
    L_004279c8:
        mov ebp,dword ptr [esi+44h]
    L_004279cb:
        mov eax,dword ptr [edi+3CCh]
    L_004279d1:
        add ecx,edx
    L_004279d3:
        mov edx,dword ptr [esi+88h]
    L_004279d9:
        add eax,ebp
    L_004279db:
        shl edx,6
    L_004279de:
        lea edx,[edx+edi+43ACh]
    L_004279e5:
        mov dword ptr [edx],eax
    L_004279e7:
        mov dword ptr [edx+4],ecx
    L_004279ea:
        mov eax,dword ptr [esi+88h]
    L_004279f0:
        shl eax,3
    L_004279f3:
        lea ebp,[eax+1]
    L_004279f6:
        add eax,7
    L_004279f9:
        cmp ebp,eax
    L_004279fb:
        jg asm_target_00427a9c
    L_00427a01:
        lea ebx,[edi+ebp*8+4370h]
    L_00427a08:
        TH10_REL8(0xeb, 0x00427a08, VA_asm_FUN_00427960_part_00427a10)
    }
}

// 0x00427A10..0x00427AC6: FUN_00427960
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427960_part_00427a10() {
    __asm {
    L_00427a10:
        mov eax,dword ptr [esi+88h]
    L_00427a16:
        shl eax,6
    L_00427a19:
        mov ecx,dword ptr [eax+edi+436Ch]
    L_00427a20:
        mov edx,dword ptr [eax+edi+43ACh]
    L_00427a27:
        add eax,edi
    L_00427a29:
        sub edx,ecx
    L_00427a2b:
        mov dword ptr [esp+0Ch],edx
    L_00427a2f:
        fild dword ptr [esp+0Ch]
    L_00427a33:
        mov dword ptr [esp+10h],ecx
    L_00427a37:
        fmul st,st(1)
    L_00427a39:
        fiadd dword ptr [esp+10h]
    L_00427a3d:
        call asm_FUN_00463b2c_00463b2c
    L_00427a42:
        mov dword ptr [ebx-4],eax
    L_00427a45:
        mov eax,dword ptr [esi+88h]
    L_00427a4b:
        shl eax,6
    L_00427a4e:
        mov ecx,dword ptr [eax+edi+4370h]
    L_00427a55:
        mov edx,dword ptr [eax+edi+43B0h]
    L_00427a5c:
        add eax,edi
    L_00427a5e:
        sub edx,ecx
    L_00427a60:
        mov dword ptr [esp+10h],edx
    L_00427a64:
        fild dword ptr [esp+10h]
    L_00427a68:
        mov dword ptr [esp+0Ch],ecx
    L_00427a6c:
        fmul st,st(1)
    L_00427a6e:
        fiadd dword ptr [esp+0Ch]
    L_00427a72:
        call asm_FUN_00463b2c_00463b2c
    L_00427a77:
        fadd dword ptr [data_00470b90]
    L_00427a7d:
        mov dword ptr [ebx],eax
    L_00427a7f:
        mov eax,dword ptr [esi+88h]
    L_00427a85:
        inc ebp
    L_00427a86:
        lea ecx,[eax*8+7]
    L_00427a8d:
        add ebx,8
    L_00427a90:
        cmp ebp,ecx
    L_00427a92:
        jle asm_FUN_00427960_part_00427a10
    L_00427a98:
        mov ebx,dword ptr [esp+14h]
    L_00427a9c:
        fstp st(0)
    L_00427a9e:
        mov ebp,dword ptr [edi+3CCh]
    L_00427aa4:
        mov eax,dword ptr [esi+44h]
    L_00427aa7:
        mov edx,dword ptr [edi+3D0h]
    L_00427aad:
        mov ecx,dword ptr [esi+48h]
    L_00427ab0:
        add eax,ebp
    L_00427ab2:
        pop edi
    L_00427ab3:
        add ecx,edx
    L_00427ab5:
        mov dword ptr [esi+34h],eax
    L_00427ab8:
        mov dword ptr [esi+38h],ecx
    L_00427abb:
        pop ebp
    L_00427abc:
        mov dword ptr [esi+84h],ebx
    L_00427ac2:
        pop ebx
    L_00427ac3:
        add esp,0Ch
    L_00427ac6:
        ret
    }
}

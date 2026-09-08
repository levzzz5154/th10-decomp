#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004297D0..0x00429A23: FUN_004297d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004297d0_004297d0() {
    __asm {
    L_004297d0:
        mov eax,dword ptr [data_00477810]
    L_004297d5:
        xor edx,edx
    L_004297d7:
        cmp eax,edx
    L_004297d9:
        je asm_target_00429a1e
    L_004297df:
        cmp dword ptr [edi+10h],edx
    L_004297e2:
        push esi
    L_004297e3:
        jne asm_target_004298f6
    L_004297e9:
        mov ax,word ptr [data_00474e5c]
    L_004297ef:
        mov ecx,dword ptr [data_00474e30]
    L_004297f5:
        mov word ptr [data_00474e5e],ax
    L_004297fb:
        mov eax,dword ptr [data_00491d78]
    L_00429800:
        and ecx,1F7h
    L_00429806:
        test ah,2
    L_00429809:
        mov word ptr [data_00474e5c],cx
    L_00429810:
        je short L_00429849
    L_00429812:
        mov al,cl
    L_00429814:
        test al,1
    L_00429816:
        je short L_00429842
    L_00429818:
        mov ax,word ptr [data_00474e5a]
    L_0042981e:
        inc ax
    L_00429820:
        cmp ax,8
    L_00429824:
        mov word ptr [data_00474e5a],ax
    L_0042982a:
        jb short L_00429849
    L_0042982c:
        or cx,4
    L_00429830:
        mov word ptr [data_00474e5c],cx
    L_00429837:
        mov word ptr [data_00474e5a],8
    L_00429840:
        jmp short L_00429849
    L_00429842:
        mov word ptr [data_00474e5a],dx
    L_00429849:
        mov ecx,474E30h
    L_0042984e:
        call asm_UpdateInputState_0040ac20
    L_00429853:
        mov eax,dword ptr [edi+1C8h]
    L_00429859:
        cdq
    L_0042985a:
        mov ecx,1Eh
    L_0042985f:
        idiv ecx
    L_00429861:
        test edx,edx
    L_00429863:
        jne short L_004298a8
    L_00429865:
        mov edx,dword ptr [data_00477708]
    L_0042986b:
        fld dword ptr [edx+34h]
    L_0042986e:
        fadd dword ptr [data_00470b0c]
    L_00429874:
        fcom dword ptr [data_00470c34]
    L_0042987a:
        fnstsw ax
    L_0042987c:
        test ah,1
    L_0042987f:
        jne short L_0042988a
    L_00429881:
        fstp st(0)
    L_00429883:
        mov ecx,0FFh
    L_00429888:
        jmp short L_00429892
    L_0042988a:
        call asm_FUN_00463b2c_00463b2c
    L_0042988f:
        movzx ecx,al
    L_00429892:
        mov eax,dword ptr [edi+9Ch]
    L_00429898:
        mov eax,dword ptr [eax]
    L_0042989a:
        mov edx,dword ptr [eax+6274h]
    L_004298a0:
        mov byte ptr [edx],cl
    L_004298a2:
        inc dword ptr [eax+6274h]
    L_004298a8:
        mov eax,dword ptr [edi+9Ch]
    L_004298ae:
        mov eax,dword ptr [eax]
    L_004298b0:
        xor ecx,ecx
    L_004298b2:
        mov cx,word ptr [data_00474e64]
    L_004298b9:
        xor edx,edx
    L_004298bb:
        mov dx,word ptr [data_00474e62]
    L_004298c2:
        push ecx
    L_004298c3:
        push edx
    L_004298c4:
        mov edx,dword ptr [data_00474e5c]
    L_004298ca:
        call asm_Recovery_AppendPacket_0042a8a0
    L_004298cf:
        test eax,eax
    L_004298d1:
        je asm_target_00429a17
    L_004298d7:
        mov esi,dword ptr [edi+1D0h]
    L_004298dd:
        push edi
    L_004298de:
        call asm_LinkedPool_AllocateAndAppendRetail_0042aa50
    L_004298e3:
        mov dword ptr [edi+9Ch],eax
    L_004298e9:
        inc dword ptr [edi+1C8h]
    L_004298ef:
        pop esi
    L_004298f0:
        mov eax,1
    L_004298f5:
        ret
    L_004298f6:
        cmp dword ptr [edi+1D0h],edx
    L_004298fc:
        jl asm_target_00429a02
    L_00429902:
        mov ax,word ptr [data_00474e5c]
    L_00429908:
        mov word ptr [data_00474e5e],ax
    L_0042990e:
        mov eax,dword ptr [edi+1D0h]
    L_00429914:
        lea ecx,[eax+eax*8]
    L_00429917:
        mov esi,dword ptr [edi+ecx*4+0B0h]
    L_0042991e:
        lea ecx,[edi+ecx*4]
    L_00429921:
        push ebx
    L_00429922:
        mov ebx,dword ptr [esi+4]
    L_00429925:
        lea eax,[eax+eax*8+2Dh]
    L_00429929:
        mov eax,dword ptr [edi+eax*4]
    L_0042992c:
        cmp eax,ebx
    L_0042992e:
        pop ebx
    L_0042992f:
        jge asm_target_004299cb
    L_00429935:
        mov ecx,dword ptr [ecx+0A4h]
    L_0042993b:
        mov dx,word ptr [ecx]
    L_0042993e:
        mov word ptr [data_00474e5c],dx
    L_00429945:
        mov eax,dword ptr [edi+1D0h]
    L_0042994b:
        lea eax,[eax+eax*8]
    L_0042994e:
        mov ecx,dword ptr [edi+eax*4+0A4h]
    L_00429955:
        mov dx,word ptr [ecx+2]
    L_00429959:
        mov word ptr [data_00474e62],dx
    L_00429960:
        mov eax,dword ptr [edi+1D0h]
    L_00429966:
        lea eax,[eax+eax*8]
    L_00429969:
        mov ecx,dword ptr [edi+eax*4+0A4h]
    L_00429970:
        mov dx,word ptr [ecx+4]
    L_00429974:
        mov word ptr [data_00474e64],dx
    L_0042997b:
        mov eax,dword ptr [edi+1D0h]
    L_00429981:
        lea eax,[eax+eax*8]
    L_00429984:
        mov ecx,dword ptr [edi+eax*4+0ACh]
    L_0042998b:
        mov dl,byte ptr [ecx]
    L_0042998d:
        lea eax,[edi+eax*4]
    L_00429990:
        mov byte ptr [edi+1C4h],dl
    L_00429996:
        add dword ptr [eax+0A4h],6
    L_0042999d:
        mov eax,dword ptr [edi+1C8h]
    L_004299a3:
        cdq
    L_004299a4:
        mov ecx,1Eh
    L_004299a9:
        idiv ecx
    L_004299ab:
        test edx,edx
    L_004299ad:
        jne short L_004299e0
    L_004299af:
        mov eax,dword ptr [edi+1D0h]
    L_004299b5:
        lea edx,[eax+eax*8]
    L_004299b8:
        mov ecx,dword ptr [edi+edx*4+0ACh]
    L_004299bf:
        lea eax,[edi+edx*4+0ACh]
    L_004299c6:
        inc ecx
    L_004299c7:
        mov dword ptr [eax],ecx
    L_004299c9:
        jmp short L_004299e0
    L_004299cb:
        mov word ptr [data_00474e5c],dx
    L_004299d2:
        mov word ptr [data_00474e62],dx
    L_004299d9:
        mov word ptr [data_00474e64],dx
    L_004299e0:
        mov eax,dword ptr [edi+1D0h]
    L_004299e6:
        add eax,5
    L_004299e9:
        lea eax,[eax+eax*8]
    L_004299ec:
        mov ecx,dword ptr [edi+eax*4]
    L_004299ef:
        lea eax,[edi+eax*4]
    L_004299f2:
        inc ecx
    L_004299f3:
        mov dword ptr [eax],ecx
    L_004299f5:
        inc dword ptr [edi+1C8h]
    L_004299fb:
        pop esi
    L_004299fc:
        mov eax,1
    L_00429a01:
        ret
    L_00429a02:
        mov word ptr [data_00474e5c],dx
    L_00429a09:
        mov word ptr [data_00474e62],dx
    L_00429a10:
        mov word ptr [data_00474e64],dx
    L_00429a17:
        inc dword ptr [edi+1C8h]
    L_00429a1d:
        pop esi
    L_00429a1e:
        mov eax,1
    L_00429a23:
        ret
    }
}

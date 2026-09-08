#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004349E0..0x00434A1A: ?StageText_SkipLine@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageText_SkipLine_004349e0() {
    __asm {
    L_004349e0:
        mov cl,byte ptr [eax]
    L_004349e2:
        cmp cl,0Ah
    L_004349e5:
        je short L_004349fd
    L_004349e7:
        cmp cl,0Dh
    L_004349ea:
        je short L_004349fd
    L_004349ec:
        mov ecx,dword ptr [edx]
    L_004349ee:
        test ecx,ecx
    L_004349f0:
        je short L_00434a1a
    L_004349f2:
        inc eax
    L_004349f3:
        dec ecx
    L_004349f4:
        mov dword ptr [edx],ecx
    L_004349f6:
        mov cl,byte ptr [eax]
    L_004349f8:
        cmp cl,0Ah
    L_004349fb:
        jne short L_004349e7
    L_004349fd:
        cmp dword ptr [edx],0
    L_00434a00:
        je short L_00434a1a
    L_00434a02:
        mov cl,byte ptr [eax]
    L_00434a04:
        cmp cl,0Ah
    L_00434a07:
        je short L_00434a0e
    L_00434a09:
        cmp cl,0Dh
    L_00434a0c:
        jne short L_00434a1a
    L_00434a0e:
        mov ecx,dword ptr [edx]
    L_00434a10:
        test ecx,ecx
    L_00434a12:
        je short L_00434a1a
    L_00434a14:
        inc eax
    L_00434a15:
        dec ecx
    L_00434a16:
        mov dword ptr [edx],ecx
    L_00434a18:
        jmp short L_00434a02
    L_00434a1a:
        ret
    }
}

// 0x00434A20..0x00434A7B: ?StageText_ExtractLine@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageText_ExtractLine_00434a20() {
    __asm {
    L_00434a20:
        cmp byte ptr [ecx],0Ah
    L_00434a23:
        mov eax,ecx
    L_00434a25:
        je short L_00434a3b
    L_00434a27:
        cmp byte ptr [eax],0Dh
    L_00434a2a:
        je short L_00434a3b
    L_00434a2c:
        mov edx,dword ptr [edi]
    L_00434a2e:
        test edx,edx
    L_00434a30:
        je short L_00434a79
    L_00434a32:
        inc eax
    L_00434a33:
        dec edx
    L_00434a34:
        mov dword ptr [edi],edx
    L_00434a36:
        cmp byte ptr [eax],0Ah
    L_00434a39:
        jne short L_00434a27
    L_00434a3b:
        cmp dword ptr [edi],0
    L_00434a3e:
        je short L_00434a79
    L_00434a40:
        push esi
    L_00434a41:
        mov esi,dword ptr [esp+8]
    L_00434a45:
        mov byte ptr [eax],0
    L_00434a48:
        sub esi,ecx
    L_00434a4a:
        lea ebx,[ebx+force_disp32_zero]
    L_00434a50:
        mov dl,byte ptr [ecx]
    L_00434a52:
        mov byte ptr [esi+ecx],dl
    L_00434a55:
        inc ecx
    L_00434a56:
        test dl,dl
    L_00434a58:
        jne short L_00434a50
    L_00434a5a:
        mov ecx,dword ptr [edi]
    L_00434a5c:
        inc eax
    L_00434a5d:
        dec ecx
    L_00434a5e:
        mov dword ptr [edi],ecx
    L_00434a60:
        mov edx,ecx
    L_00434a62:
        pop esi
    L_00434a63:
        mov cl,byte ptr [eax]
    L_00434a65:
        cmp cl,0Ah
    L_00434a68:
        je short L_00434a6f
    L_00434a6a:
        cmp cl,0Dh
    L_00434a6d:
        jne short L_00434a79
    L_00434a6f:
        test edx,edx
    L_00434a71:
        je short L_00434a79
    L_00434a73:
        inc eax
    L_00434a74:
        dec edx
    L_00434a75:
        mov dword ptr [edi],edx
    L_00434a77:
        jmp short L_00434a63
    L_00434a79:
        ret 4
    }
}

// 0x00434A80..0x00434B4D: ?StageText_Initialize@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageText_Initialize_00434a80() {
    __asm {
    L_00434a80:
        push esi
    L_00434a81:
        mov esi,dword ptr [esp+8]
    L_00434a85:
        mov dword ptr [eax+0B4h],esi
    L_00434a8b:
        push edi
    L_00434a8c:
        mov edi,dword ptr [data_00491c14]
    L_00434a92:
        lea esi,[eax+88h]
    L_00434a98:
        mov dword ptr [esi],edi
    L_00434a9a:
        mov edi,dword ptr [data_00491c18]
    L_00434aa0:
        mov dword ptr [esi+4],edi
    L_00434aa3:
        mov edi,dword ptr [data_00491c1c]
    L_00434aa9:
        mov dword ptr [esi+8],edi
    L_00434aac:
        mov edi,dword ptr [data_00491c14]
    L_00434ab2:
        lea esi,[eax+94h]
    L_00434ab8:
        mov dword ptr [esi],edi
    L_00434aba:
        mov edi,dword ptr [data_00491c18]
    L_00434ac0:
        mov dword ptr [esi+4],edi
    L_00434ac3:
        mov edi,dword ptr [data_00491c1c]
    L_00434ac9:
        mov dword ptr [esi+8],edi
    L_00434acc:
        movzx esi,byte ptr [esp+10h]
    L_00434ad1:
        mov dword ptr [eax+0B8h],esi
    L_00434ad7:
        mov edi,dword ptr [edx]
    L_00434ad9:
        lea esi,[eax+70h]
    L_00434adc:
        mov dword ptr [esi],edi
    L_00434ade:
        mov edi,dword ptr [edx+4]
    L_00434ae1:
        mov dword ptr [esi+4],edi
    L_00434ae4:
        mov edx,dword ptr [edx+8]
    L_00434ae7:
        mov dword ptr [esi+8],edx
    L_00434aea:
        mov esi,dword ptr [ecx]
    L_00434aec:
        lea edx,[eax+7Ch]
    L_00434aef:
        mov dword ptr [edx],esi
    L_00434af1:
        mov esi,dword ptr [ecx+4]
    L_00434af4:
        mov dword ptr [edx+4],esi
    L_00434af7:
        mov ecx,dword ptr [ecx+8]
    L_00434afa:
        mov dword ptr [edx+8],ecx
    L_00434afd:
        mov ecx,dword ptr [eax+0B0h]
    L_00434b03:
        xor edx,edx
    L_00434b05:
        test cl,1
    L_00434b08:
        pop edi
    L_00434b09:
        pop esi
    L_00434b0a:
        jne short L_00434b35
    L_00434b0c:
        or ecx,1
    L_00434b0f:
        mov dword ptr [eax+0A4h],edx
    L_00434b15:
        mov dword ptr [eax+0A0h],0FFF0BDC1h
    L_00434b1f:
        mov dword ptr [eax+0A8h],edx
    L_00434b25:
        mov dword ptr [eax+0ACh],476F78h
    L_00434b2f:
        mov dword ptr [eax+0B0h],ecx
    L_00434b35:
        mov dword ptr [eax+0A4h],edx
    L_00434b3b:
        mov dword ptr [eax+0A8h],edx
    L_00434b41:
        mov dword ptr [eax+0A0h],0FFFFFFFFh
    L_00434b4b:
        ret 8
    }
}

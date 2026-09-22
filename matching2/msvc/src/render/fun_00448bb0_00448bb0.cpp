#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3507): closest_byte_count=0/268; first_diff=extent (readable typed unlink candidate emitted 278 bytes vs retail 268);
// residual_class=private-ESI/EDI ABI and member register preservation; the standalone cdecl candidate had to save ESI/EDI and could not consume the caller's private registers directly;
// variants_tested=retail naked baseline (268/268 exact), readable typed linked-list candidate (278-byte extent), live Ghidra FUN_00448bb0 decompile, and callers FUN_00446220/FUN_00448860/FUN_00448900;
// next_lever=native-LTCG cluster with the real animation-manager caller and production entity/list layouts, preserving ESI/EDI as private inputs.

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448BB0..0x00448CBB: FUN_00448bb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448bb0_00448bb0() {
    __asm {
    L_00448bb0:
        mov ecx,dword ptr [edi+72DAD8h]
    L_00448bb6:
        lea eax,[esi+4]
    L_00448bb9:
        cmp eax,ecx
    L_00448bbb:
        jne short L_00448bc6
    L_00448bbd:
        mov ecx,dword ptr [esi+0Ch]
    L_00448bc0:
        mov dword ptr [edi+72DAD8h],ecx
    L_00448bc6:
        cmp eax,dword ptr [edi+72DAD4h]
    L_00448bcc:
        jne short L_00448bd7
    L_00448bce:
        mov edx,dword ptr [esi+8]
    L_00448bd1:
        mov dword ptr [edi+72DAD4h],edx
    L_00448bd7:
        cmp eax,dword ptr [edi+72DAE0h]
    L_00448bdd:
        jne short L_00448be8
    L_00448bdf:
        mov ecx,dword ptr [esi+0Ch]
    L_00448be2:
        mov dword ptr [edi+72DAE0h],ecx
    L_00448be8:
        cmp eax,dword ptr [edi+72DADCh]
    L_00448bee:
        jne short L_00448bf9
    L_00448bf0:
        mov edx,dword ptr [esi+8]
    L_00448bf3:
        mov dword ptr [edi+72DADCh],edx
    L_00448bf9:
        mov ecx,dword ptr [eax+4]
    L_00448bfc:
        push ebx
    L_00448bfd:
        xor ebx,ebx
    L_00448bff:
        cmp ecx,ebx
    L_00448c01:
        je short L_00448c09
    L_00448c03:
        mov edx,dword ptr [eax+8]
    L_00448c06:
        mov dword ptr [ecx+8],edx
    L_00448c09:
        mov ecx,dword ptr [eax+8]
    L_00448c0c:
        cmp ecx,ebx
    L_00448c0e:
        je short L_00448c16
    L_00448c10:
        mov edx,dword ptr [eax+4]
    L_00448c13:
        mov dword ptr [ecx+4],edx
    L_00448c16:
        mov dword ptr [eax+4],ebx
    L_00448c19:
        mov dword ptr [eax+8],ebx
    L_00448c1c:
        mov eax,dword ptr [esi+14h]
    L_00448c1f:
        cmp eax,ebx
    L_00448c21:
        je short L_00448c29
    L_00448c23:
        mov ecx,dword ptr [esi+18h]
    L_00448c26:
        mov dword ptr [eax+8],ecx
    L_00448c29:
        mov eax,dword ptr [esi+18h]
    L_00448c2c:
        cmp eax,ebx
    L_00448c2e:
        je short L_00448c36
    L_00448c30:
        mov edx,dword ptr [esi+14h]
    L_00448c33:
        mov dword ptr [eax+4],edx
    L_00448c36:
        lea eax,[edi+68h]
    L_00448c39:
        cmp esi,eax
    L_00448c3b:
        mov dword ptr [esi+14h],ebx
    L_00448c3e:
        mov dword ptr [esi+18h],ebx
    L_00448c41:
        jb short L_00448c92
    L_00448c43:
        lea ecx,[edi+3AC068h]
    L_00448c49:
        cmp esi,ecx
    L_00448c4b:
        jae short L_00448c92
    L_00448c4d:
        mov ecx,esi
    L_00448c4f:
        sub ecx,edi
    L_00448c51:
        sub ecx,68h
    L_00448c54:
        mov eax,8B70344Bh
    L_00448c59:
        imul ecx
    L_00448c5b:
        add edx,ecx
    L_00448c5d:
        sar edx,9
    L_00448c60:
        mov eax,edx
    L_00448c62:
        shr eax,1Fh
    L_00448c65:
        add eax,edx
    L_00448c67:
        mov byte ptr [eax+edi+3AC068h],bl
    L_00448c6e:
        mov eax,dword ptr [esi+358h]
    L_00448c74:
        cmp eax,ebx
    L_00448c76:
        je short L_00448c81
    L_00448c78:
        push eax
    L_00448c79:
        call asm_free_00452422
    L_00448c7e:
        add esp,4
    L_00448c81:
        mov edx,esi
    L_00448c83:
        mov dword ptr [esi+358h],ebx
    L_00448c89:
        call asm_InitializeEntity_00401de0
    L_00448c8e:
        xor eax,eax
    L_00448c90:
        pop ebx
    L_00448c91:
        ret
    L_00448c92:
        cmp esi,ebx
    L_00448c94:
        je short L_00448cb8
    L_00448c96:
        mov eax,dword ptr [esi+358h]
    L_00448c9c:
        cmp eax,ebx
    L_00448c9e:
        je short L_00448ca9
    L_00448ca0:
        push eax
    L_00448ca1:
        call asm_free_00452422
    L_00448ca6:
        add esp,4
    L_00448ca9:
        push esi
    L_00448caa:
        mov dword ptr [esi+358h],ebx
    L_00448cb0:
        call asm_free_004524a1
    L_00448cb5:
        add esp,4
    L_00448cb8:
        xor eax,eax
    L_00448cba:
        pop ebx
    L_00448cbb:
        ret
    }
}

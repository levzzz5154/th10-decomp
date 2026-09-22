#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3201): closest_byte_count=51/399; first_diff=0x00409C00
// (standalone readable state model, authoritative probe extent 408 bytes).
// residual_class=private EAX receiver and ECX parameter, x87/integer
// evaluation order, and register ABIs for 00409E50, 004172E0, 0043DC90,
// and 00448D00.
// variants_tested=typed raw-offset end-state model with stack helper
// declarations; the candidate was restored after 348 differing bytes in the
// measured 399-byte prefix.
// next_lever=schema2 native-LTCG cluster with a real dispatch caller and
// those four helper anchors; retain this exact body until all 399 bytes match.
// 0x00409C00..0x00409D8E: FUN_00409c00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409c00_00409c00() {
    __asm {
    L_00409c00:
        push ecx
    L_00409c01:
        push esi
    L_00409c02:
        mov esi,eax
    L_00409c04:
        test byte ptr [esi+378Ch],1
    L_00409c0b:
        je asm_target_00409d8c
    L_00409c11:
        mov eax,dword ptr [data_004776e8]
    L_00409c16:
        push ebp
    L_00409c17:
        push edi
    L_00409c18:
        or dword ptr [eax+2A18h],1
    L_00409c1f:
        lea eax,[esi+768h]
    L_00409c25:
        call asm_FUN_00409e50_00409e50
    L_00409c2a:
        lea eax,[esi+76Ch]
    L_00409c30:
        call asm_FUN_00409e50_00409e50
    L_00409c35:
        lea eax,[esi+770h]
    L_00409c3b:
        call asm_FUN_00409e50_00409e50
    L_00409c40:
        mov edx,dword ptr [esi+378Ch]
    L_00409c46:
        mov ebp,dword ptr [data_00491c10]
    L_00409c4c:
        and edx,0FFFFFFFEh
    L_00409c4f:
        mov dword ptr [esi+378Ch],edx
    L_00409c55:
        mov eax,dword ptr [esi+774h]
    L_00409c5b:
        push eax
    L_00409c5c:
        mov edx,ebp
    L_00409c5e:
        call asm_AnimationManager_SetFlag_004492a0
    L_00409c63:
        mov dword ptr [esi+774h],0
    L_00409c6d:
        test byte ptr [esi+378Ch],2
    L_00409c74:
        je asm_target_00409d52
    L_00409c7a:
        mov ecx,dword ptr [esi+3790h]
    L_00409c80:
        mov eax,66666667h
    L_00409c85:
        imul ecx
    L_00409c87:
        mov eax,dword ptr [data_00474c44]
    L_00409c8c:
        sar edx,2
    L_00409c8f:
        mov ecx,edx
    L_00409c91:
        shr ecx,1Fh
    L_00409c94:
        add ecx,edx
    L_00409c96:
        add eax,ecx
    L_00409c98:
        cmp eax,3B9ACA00h
    L_00409c9d:
        mov dword ptr [data_00474c44],eax
    L_00409ca2:
        jl short L_00409cae
    L_00409ca4:
        mov dword ptr [data_00474c44],3B9AC9FFh
    L_00409cae:
        mov edx,dword ptr [esi+3790h]
    L_00409cb4:
        mov eax,dword ptr [data_0047770c]
    L_00409cb9:
        push edx
    L_00409cba:
        push eax
    L_00409cbb:
        xor eax,eax
    L_00409cbd:
        call asm_FUN_004172e0_004172e0
    L_00409cc2:
        mov ecx,dword ptr [data_00477838]
    L_00409cc8:
        cmp dword ptr [ecx+10h],1
    L_00409ccc:
        je short L_00409d3c
    L_00409cce:
        mov eax,dword ptr [data_00474c68]
    L_00409cd3:
        mov edx,dword ptr [data_00474c6c]
    L_00409cd9:
        lea ecx,[edx+eax*2]
    L_00409cdc:
        mov edx,dword ptr [data_0047783c]
    L_00409ce2:
        add ecx,eax
    L_00409ce4:
        mov eax,dword ptr [esi+3788h]
    L_00409cea:
        imul ecx,437Ch
    L_00409cf0:
        lea eax,[eax+eax*8]
    L_00409cf3:
        add ecx,edx
    L_00409cf5:
        shl eax,4
    L_00409cf8:
        lea eax,[eax+ecx+5A4h]
    L_00409cff:
        mov ecx,dword ptr [eax+80h]
    L_00409d05:
        cmp ecx,1869Fh
    L_00409d0b:
        jge short L_00409d14
    L_00409d0d:
        inc ecx
    L_00409d0e:
        mov dword ptr [eax+80h],ecx
    L_00409d14:
        mov esi,dword ptr [esi+3788h]
    L_00409d1a:
        lea ecx,[esi+esi*8]
    L_00409d1d:
        shl ecx,4
    L_00409d20:
        lea eax,[ecx+edx+19A8Ch]
    L_00409d27:
        mov ecx,dword ptr [eax+80h]
    L_00409d2d:
        cmp ecx,1869Fh
    L_00409d33:
        jge short L_00409d3c
    L_00409d35:
        inc ecx
    L_00409d36:
        mov dword ptr [eax+80h],ecx
    L_00409d3c:
        push 0
    L_00409d3e:
        mov edi,2Dh
    L_00409d43:
        mov ecx,492590h
    L_00409d48:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00409d4d:
        pop edi
    L_00409d4e:
        pop ebp
    L_00409d4f:
        pop esi
    L_00409d50:
        pop ecx
    L_00409d51:
        ret
    L_00409d52:
        mov edi,dword ptr [data_0047770c]
    L_00409d58:
        mov edx,dword ptr [edi+9E14h]
    L_00409d5e:
        lea esi,[edi+9E14h]
    L_00409d64:
        push edx
    L_00409d65:
        mov edx,ebp
    L_00409d67:
        call asm_AnimationManager_SetFlag_004492a0
    L_00409d6c:
        push 0Fh
    L_00409d6e:
        mov dword ptr [esi],0
    L_00409d74:
        mov eax,dword ptr [edi+9EC8h]
    L_00409d7a:
        push 48h
    L_00409d7c:
        push eax
    L_00409d7d:
        lea edi,[esp+18h]
    L_00409d81:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00409d86:
        mov ecx,dword ptr [eax]
    L_00409d88:
        pop edi
    L_00409d89:
        mov dword ptr [esi],ecx
    L_00409d8b:
        pop ebp
    L_00409d8c:
        pop esi
    L_00409d8d:
        pop ecx
    L_00409d8e:
        ret
    }
}

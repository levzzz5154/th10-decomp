// BLOCKED (D3407): closest_byte_count=0/325; first_diff=extent (readable cleanup candidate emitted 306 bytes vs retail 325 before byte comparison);
// residual_class=SEH/private-ABI; retail installs an fs:[0] registration and preserves the exact stdcall cleanup,
// while the bounded C++ model lacks the compiler's matching exception-frame schedule and private call receivers.
// variants_tested=retail naked baseline (325/325 exact), readable raw-offset cleanup model (306 bytes),
// live Ghidra FUN_00424ED0 decompile, and exact probe;
// next_lever=reconstruct the owning class/SEH scope and compile with the real cleanup callers in native LTCG.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// 0x00424ED0..0x00425014: FUN_00424ed0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00424ed0_00424ed0() {
    __asm {
    L_00424ed0:
        mov eax,dword ptr fs:[0]
    L_00424ed6:
        push 0FFFFFFFFh
    L_00424ed8:
        push 46528Bh
    L_00424edd:
        push eax
    L_00424ede:
        mov dword ptr fs:[0],esp
    L_00424ee5:
        push ebx
    L_00424ee6:
        mov ebx,dword ptr [esp+14h]
    L_00424eea:
        push ebp
    L_00424eeb:
        push esi
    L_00424eec:
        push edi
    L_00424eed:
        mov dword ptr [esp+18h],0
    L_00424ef5:
        mov esi,dword ptr [ebx+8]
    L_00424ef8:
        test esi,esi
    L_00424efa:
        mov edi,dword ptr [data_00491be4]
    L_00424f00:
        mov ebp,dword ptr [data_004660b0]
    L_00424f06:
        je short L_00424f2f
    L_00424f08:
        push 492274h
    L_00424f0d:
        call ebp
    L_00424f0f:
        inc byte ptr [data_0049231c]
    L_00424f15:
        mov ecx,esi
    L_00424f17:
        mov edx,edi
    L_00424f19:
        call asm_Scheduler_Remove_00449f60
    L_00424f1e:
        push 492274h
    L_00424f23:
        call dword ptr [data_004660b4]
    L_00424f29:
        dec byte ptr [data_0049231c]
    L_00424f2f:
        mov esi,dword ptr [ebx+0Ch]
    L_00424f32:
        test esi,esi
    L_00424f34:
        mov edi,dword ptr [data_00491be4]
    L_00424f3a:
        je short L_00424f63
    L_00424f3c:
        push 492274h
    L_00424f41:
        call ebp
    L_00424f43:
        inc byte ptr [data_0049231c]
    L_00424f49:
        mov ecx,esi
    L_00424f4b:
        mov edx,edi
    L_00424f4d:
        call asm_Scheduler_Remove_00449f60
    L_00424f52:
        push 492274h
    L_00424f57:
        call dword ptr [data_004660b4]
    L_00424f5d:
        dec byte ptr [data_0049231c]
    L_00424f63:
        test byte ptr [data_00474ca0],1
    L_00424f6a:
        mov dword ptr [data_00477834],0
    L_00424f74:
        je short L_00424f90
    L_00424f76:
        mov edx,dword ptr [ebx+10h]
    L_00424f79:
        mov eax,dword ptr [data_00491c10]
    L_00424f7e:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_00424f83:
        mov eax,dword ptr [ebx+45Ch]
    L_00424f89:
        mov dword ptr [data_00491bf0],eax
    L_00424f8e:
        jmp short L_00424fe3
    L_00424f90:
        mov esi,dword ptr [data_00491c10]
    L_00424f96:
        mov edi,dword ptr [esi+3AD08Ch]
    L_00424f9c:
        add esi,3AD08Ch
    L_00424fa2:
        test edi,edi
    L_00424fa4:
        je short L_00424fbc
    L_00424fa6:
        call asm_FUN_00447810_00447810
    L_00424fab:
        mov ecx,dword ptr [esi]
    L_00424fad:
        push ecx
    L_00424fae:
        call asm_free_004524a1
    L_00424fb3:
        add esp,4
    L_00424fb6:
        mov dword ptr [esi],0
    L_00424fbc:
        mov eax,dword ptr [ebx+45Ch]
    L_00424fc2:
        test eax,eax
    L_00424fc4:
        je short L_00424fd9
    L_00424fc6:
        push eax
    L_00424fc7:
        call asm_free_00452422
    L_00424fcc:
        add esp,4
    L_00424fcf:
        mov dword ptr [ebx+45Ch],0
    L_00424fd9:
        mov dword ptr [data_00491bf0],0
    L_00424fe3:
        mov eax,dword ptr [ebx+36Ch]
    L_00424fe9:
        test eax,eax
    L_00424feb:
        je short L_00424ff6
    L_00424fed:
        push eax
    L_00424fee:
        call asm_free_00452422
    L_00424ff3:
        add esp,4
    L_00424ff6:
        mov ecx,dword ptr [esp+10h]
    L_00424ffa:
        pop edi
    L_00424ffb:
        pop esi
    L_00424ffc:
        mov dword ptr [ebx+36Ch],0
    L_00425006:
        pop ebp
    L_00425007:
        mov dword ptr fs:[0],ecx
    L_0042500e:
        pop ebx
    L_0042500f:
        add esp,0Ch
    L_00425012:
        ret 4
    }
}

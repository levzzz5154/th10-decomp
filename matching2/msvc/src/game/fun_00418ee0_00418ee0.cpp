#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// 0x00418EE0..0x00419039: FUN_00418ee0
// BLOCKED: closest_byte_count=346/346; first_diff=none (retail assembly baseline);
// residual_class=caller-sensitive private register ABI for Scheduler_Remove
// plus compiler-generated stack-local ordering; variants_tested=typed raw-pointer
// cleanup loop (302-byte extent), cached lock/scheduler pointers with volatile
// counter (348-byte extent), delayed counter initialization and alternate local
// declaration order (348-byte extent); next_lever=co-compile this entry with
// its real caller and Scheduler_Remove in a schema-2 native-LTCG manifest.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418ee0_00418ee0() {
    __asm {
    L_00418ee0:
        push ecx
    L_00418ee1:
        mov edx,dword ptr [esp+8]
    L_00418ee5:
        push ebx
    L_00418ee6:
        mov ebx,dword ptr [data_004660b0]
    L_00418eec:
        push ebp
    L_00418eed:
        mov ebp,dword ptr [data_004660b4]
    L_00418ef3:
        push esi
    L_00418ef4:
        mov esi,dword ptr [edx+8]
    L_00418ef7:
        test esi,esi
    L_00418ef9:
        push edi
    L_00418efa:
        mov edi,dword ptr [data_00491be4]
    L_00418f00:
        je short L_00418f2f
    L_00418f02:
        push 492274h
    L_00418f07:
        call ebx
    L_00418f09:
        inc byte ptr [data_0049231c]
    L_00418f0f:
        mov ecx,esi
    L_00418f11:
        mov edx,edi
    L_00418f13:
        call asm_Scheduler_Remove_00449f60
    L_00418f18:
        push 492274h
    L_00418f1d:
        call ebp
    L_00418f1f:
        mov al,byte ptr [data_0049231c]
    L_00418f24:
        mov edx,dword ptr [esp+18h]
    L_00418f28:
        dec al
    L_00418f2a:
        mov byte ptr [data_0049231c],al
    L_00418f2f:
        mov esi,dword ptr [edx+0Ch]
    L_00418f32:
        test esi,esi
    L_00418f34:
        mov edi,dword ptr [data_00491be4]
    L_00418f3a:
        je short L_00418f69
    L_00418f3c:
        push 492274h
    L_00418f41:
        call ebx
    L_00418f43:
        inc byte ptr [data_0049231c]
    L_00418f49:
        mov ecx,esi
    L_00418f4b:
        mov edx,edi
    L_00418f4d:
        call asm_Scheduler_Remove_00449f60
    L_00418f52:
        push 492274h
    L_00418f57:
        call ebp
    L_00418f59:
        mov al,byte ptr [data_0049231c]
    L_00418f5e:
        mov edx,dword ptr [esp+18h]
    L_00418f62:
        dec al
    L_00418f64:
        mov byte ptr [data_0049231c],al
    L_00418f69:
        mov ebx,dword ptr [data_00491c10]
    L_00418f6f:
        lea esi,[edx+0DCh]
    L_00418f75:
        mov dword ptr [esp+10h],0Ah
    L_00418f7d:
        mov edi,4000000h
    L_00418f82:
        mov ecx,dword ptr [esi]
    L_00418f84:
        test ecx,ecx
    L_00418f86:
        je short L_00418ff1
    L_00418f88:
        mov eax,dword ptr [ebx+72DAD4h]
    L_00418f8e:
        test eax,eax
    L_00418f90:
        je short L_00418fa0
    L_00418f92:
        mov ebp,dword ptr [eax]
    L_00418f94:
        cmp dword ptr [ebp],ecx
    L_00418f97:
        je short L_00418fc0
    L_00418f99:
        mov eax,dword ptr [eax+4]
    L_00418f9c:
        test eax,eax
    L_00418f9e:
        jne short L_00418f92
    L_00418fa0:
        mov eax,dword ptr [ebx+72DADCh]
    L_00418fa6:
        test eax,eax
    L_00418fa8:
        je short L_00418ff1
    L_00418faa:
        lea ebx,[ebx+force_disp32_zero]
    L_00418fb0:
        mov ebp,dword ptr [eax]
    L_00418fb2:
        cmp dword ptr [ebp],ecx
    L_00418fb5:
        je short L_00418fc0
    L_00418fb7:
        mov eax,dword ptr [eax+4]
    L_00418fba:
        test eax,eax
    L_00418fbc:
        jne short L_00418fb0
    L_00418fbe:
        jmp short L_00418ff1
    L_00418fc0:
        mov eax,dword ptr [eax]
    L_00418fc2:
        test eax,eax
    L_00418fc4:
        je short L_00418ff1
    L_00418fc6:
        mov ebp,dword ptr [eax+35Ch]
    L_00418fcc:
        mov ecx,dword ptr [eax+18h]
    L_00418fcf:
        or ebp,edi
    L_00418fd1:
        test ecx,ecx
    L_00418fd3:
        mov dword ptr [eax+35Ch],ebp
    L_00418fd9:
        jne short L_00418ff1
    L_00418fdb:
        mov eax,dword ptr [eax+14h]
    L_00418fde:
        test eax,eax
    L_00418fe0:
        je short L_00418ff1
    L_00418fe2:
        mov ecx,dword ptr [eax]
    L_00418fe4:
        or dword ptr [ecx+35Ch],edi
    L_00418fea:
        mov eax,dword ptr [eax+4]
    L_00418fed:
        test eax,eax
    L_00418fef:
        jne short L_00418fe2
    L_00418ff1:
        mov eax,dword ptr [esp+10h]
    L_00418ff5:
        mov dword ptr [esi],0
    L_00418ffb:
        add esi,4
    L_00418ffe:
        dec eax
    L_00418fff:
        mov dword ptr [esp+10h],eax
    L_00419003:
        jne asm_target_00418f82
    L_00419009:
        cmp byte ptr [data_00491d6a],2
    L_00419010:
        pop edi
    L_00419011:
        pop esi
    L_00419012:
        pop ebp
    L_00419013:
        pop ebx
    L_00419014:
        jne short L_00419025
    L_00419016:
        push 46D6D8h
    L_0041901b:
        push edx
    L_0041901c:
        call asm_FUN_0041a200_0041a200
    L_00419021:
        mov edx,dword ptr [esp+8]
    L_00419025:
        mov eax,edx
    L_00419027:
        call asm_Recovery_ClearEightBuckets_00419040
    L_0041902c:
        mov dword ptr [data_00477814],0
    L_00419036:
        pop ecx
    L_00419037:
        ret 4
    }
}

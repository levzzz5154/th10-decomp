#include "asm_encoding.hpp"
#include "asm_symbols.hpp"


// BLOCKED (D3501): closest_byte_count=402/402; first_diff=none (retail
// assembly baseline only; no readable candidate retained);
// residual_class=SEH registration/handler frame, __thiscall receiver/register
// setup, three private Scheduler_Remove calls, and three EH vector-destructor
// helper ABIs with large object offsets.
// variants_tested=live Ghidra complete-function analysis with callers/callees,
// xrefs, disassembly, and variables; MSVC 13.10 scoped probe baseline exact;
// no readable candidate retained. next_lever=native-LTCG schema2 cluster with
// real 0x00408C90/0x00417C80 callers and vector-destructor helper contexts.

// 0x00408AF0..0x00408C81: FUN_00408af0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408af0_00408af0() {
    __asm {
    L_00408af0:
        push 0FFFFFFFFh
    L_00408af2:
        push 46560Fh
    L_00408af7:
        mov eax,dword ptr fs:[0]
    L_00408afd:
        push eax
    L_00408afe:
        mov dword ptr fs:[0],esp
    L_00408b05:
        push ecx
    L_00408b06:
        push ebx
    L_00408b07:
        push ebp
    L_00408b08:
        push esi
    L_00408b09:
        mov esi,dword ptr [esp+20h]
    L_00408b0d:
        push edi
    L_00408b0e:
        mov dword ptr [esp+1Ch],2
    L_00408b16:
        mov eax,dword ptr [esi+768h]
    L_00408b1c:
        mov edi,dword ptr [data_00491c10]
    L_00408b22:
        push eax
    L_00408b23:
        mov edx,edi
    L_00408b25:
        call asm_AnimationManager_SetFlag_004492a0
    L_00408b2a:
        xor ebx,ebx
    L_00408b2c:
        mov dword ptr [esi+768h],ebx
    L_00408b32:
        mov ecx,dword ptr [esi+76Ch]
    L_00408b38:
        push ecx
    L_00408b39:
        mov edx,edi
    L_00408b3b:
        call asm_AnimationManager_SetFlag_004492a0
    L_00408b40:
        mov dword ptr [esi+76Ch],ebx
    L_00408b46:
        mov edx,dword ptr [esi+770h]
    L_00408b4c:
        push edx
    L_00408b4d:
        mov edx,edi
    L_00408b4f:
        call asm_AnimationManager_SetFlag_004492a0
    L_00408b54:
        mov ebp,dword ptr [data_00491be4]
    L_00408b5a:
        mov dword ptr [esi+770h],ebx
    L_00408b60:
        mov edi,dword ptr [esi+8]
    L_00408b63:
        cmp edi,ebx
    L_00408b65:
        mov ebx,dword ptr [data_004660b0]
    L_00408b6b:
        je short L_00408b98
    L_00408b6d:
        push 492274h
    L_00408b72:
        call ebx
    L_00408b74:
        inc byte ptr [data_0049231c]
    L_00408b7a:
        mov ecx,edi
    L_00408b7c:
        mov edx,ebp
    L_00408b7e:
        call asm_Scheduler_Remove_00449f60
    L_00408b83:
        mov ebp,dword ptr [data_004660b4]
    L_00408b89:
        push 492274h
    L_00408b8e:
        call ebp
    L_00408b90:
        dec byte ptr [data_0049231c]
    L_00408b96:
        jmp short L_00408b9e
    L_00408b98:
        mov ebp,dword ptr [data_004660b4]
    L_00408b9e:
        mov edi,dword ptr [esi+0Ch]
    L_00408ba1:
        test edi,edi
    L_00408ba3:
        mov eax,dword ptr [data_00491be4]
    L_00408ba8:
        mov dword ptr [esp+10h],eax
    L_00408bac:
        je short L_00408bd3
    L_00408bae:
        push 492274h
    L_00408bb3:
        call ebx
    L_00408bb5:
        inc byte ptr [data_0049231c]
    L_00408bbb:
        mov edx,dword ptr [esp+10h]
    L_00408bbf:
        mov ecx,edi
    L_00408bc1:
        call asm_Scheduler_Remove_00449f60
    L_00408bc6:
        push 492274h
    L_00408bcb:
        call ebp
    L_00408bcd:
        dec byte ptr [data_0049231c]
    L_00408bd3:
        mov edi,dword ptr [esi+37ACh]
    L_00408bd9:
        test edi,edi
    L_00408bdb:
        mov ecx,dword ptr [data_00491be4]
    L_00408be1:
        mov dword ptr [esp+10h],ecx
    L_00408be5:
        je short L_00408c0c
    L_00408be7:
        push 492274h
    L_00408bec:
        call ebx
    L_00408bee:
        inc byte ptr [data_0049231c]
    L_00408bf4:
        mov edx,dword ptr [esp+10h]
    L_00408bf8:
        mov ecx,edi
    L_00408bfa:
        call asm_Scheduler_Remove_00449f60
    L_00408bff:
        push 492274h
    L_00408c04:
        call ebp
    L_00408c06:
        dec byte ptr [data_0049231c]
    L_00408c0c:
        push 401FF0h
    L_00408c11:
        push 5
    L_00408c13:
        push 3ACh
    L_00408c18:
        lea edx,[esi+24D8h]
    L_00408c1e:
        push edx
    L_00408c1f:
        mov dword ptr [data_004776f4],0
    L_00408c29:
        mov byte ptr [esp+2Ch],1
    L_00408c2e:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00408c33:
        push 401FF0h
    L_00408c38:
        push 8
    L_00408c3a:
        push 3ACh
    L_00408c3f:
        lea eax,[esi+778h]
    L_00408c45:
        push eax
    L_00408c46:
        mov byte ptr [esp+2Ch],0
    L_00408c4b:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00408c50:
        push 401FF0h
    L_00408c55:
        push 2
    L_00408c57:
        push 3ACh
    L_00408c5c:
        add esi,10h
    L_00408c5f:
        push esi
    L_00408c60:
        mov dword ptr [esp+2Ch],0FFFFFFFFh
    L_00408c68:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00408c6d:
        mov ecx,dword ptr [esp+14h]
    L_00408c71:
        pop edi
    L_00408c72:
        pop esi
    L_00408c73:
        pop ebp
    L_00408c74:
        pop ebx
    L_00408c75:
        mov dword ptr fs:[0],ecx
    L_00408c7c:
        add esp,10h
    L_00408c7f:
        ret 4
    }
}






// BLOCKED (D3501): closest_byte_count=1105/1105; first_diff=none (retail
// assembly baseline only; no readable candidate retained);
// residual_class=schema2 manager teardown with private register live-ins,
// twenty-two helper call contexts, shared global-state layouts, and SEH/EH
// vector-destructor sequencing.
// variants_tested=live Ghidra complete-function analysis with callers/callees,
// xrefs, disassembly, and variables; MSVC 13.10 scoped probe baseline exact;
// no readable candidate retained. next_lever=native-LTCG schema2 cluster with
// real 0x00418150/0x004203F0 callers and all teardown callees co-compiled.

// 0x00417C80..0x004180D0: FUN_00417c80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417c80_00417c80() {
    __asm {
    L_00417c80:
        sub esp,10h
    L_00417c83:
        push ebx
    L_00417c84:
        mov ebx,dword ptr [data_0047783c]
    L_00417c8a:
        push ebp
    L_00417c8b:
        push esi
    L_00417c8c:
        push edi
    L_00417c8d:
        call asm_FUN_0042b1e0_0042b1e0
    L_00417c92:
        mov edx,dword ptr [data_00474ca0]
    L_00417c98:
        mov eax,dword ptr [data_00491fb8]
    L_00417c9d:
        and edx,0FFFFFFFCh
    L_00417ca0:
        cmp eax,0Ah
    L_00417ca3:
        mov dword ptr [data_00474ca0],edx
    L_00417ca9:
        mov dword ptr [data_00476f78],3F800000h
    L_00417cb3:
        mov ebx,2
    L_00417cb8:
        jne short L_00417d26
    L_00417cba:
        mov ecx,dword ptr [data_004776e0]
    L_00417cc0:
        mov edx,dword ptr [ecx+89A4h]
    L_00417cc6:
        test edx,edx
    L_00417cc8:
        lea esi,[ecx+89A4h]
    L_00417cce:
        mov dword ptr [esp+14h],43F00000h
    L_00417cd6:
        mov dword ptr [esp+18h],43C40000h
    L_00417cde:
        mov dword ptr [esp+1Ch],0
    L_00417ce6:
        jne short L_00417d08
    L_00417ce8:
        mov eax,dword ptr [ecx+8994h]
    L_00417cee:
        push 6
    L_00417cf0:
        lea ecx,[esp+14h]
    L_00417cf4:
        push ecx
    L_00417cf5:
        push eax
    L_00417cf6:
        lea edi,[esp+20h]
    L_00417cfa:
        call asm_AnimationManager_CreatePositionedPrimary_00448d50
    L_00417cff:
        mov edx,dword ptr [eax]
    L_00417d01:
        mov dword ptr [esi],edx
    L_00417d03:
        mov eax,dword ptr [data_00491fb8]
    L_00417d08:
        mov ecx,dword ptr [data_00474c80]
    L_00417d0e:
        cmp ecx,dword ptr [data_00474c7c]
    L_00417d14:
        jne asm_target_00417db5
    L_00417d1a:
        or dword ptr [data_00474ca0],1
    L_00417d21:
        jmp asm_target_00417db5
    L_00417d26:
        cmp eax,0Bh
    L_00417d29:
        jne short L_00417d49
    L_00417d2b:
        mov esi,dword ptr [data_004776e0]
    L_00417d31:
        push 43D00000h
    L_00417d36:
        push 43600000h
    L_00417d3b:
        call asm_FUN_0040c540_0040c540
    L_00417d40:
        mov eax,dword ptr [data_00474ca0]
    L_00417d45:
        or eax,ebx
    L_00417d47:
        jmp short L_00417dab
    L_00417d49:
        cmp eax,4
    L_00417d4c:
        je short L_00417d53
    L_00417d4e:
        cmp eax,0Fh
    L_00417d51:
        jne short L_00417d6a
    L_00417d53:
        mov esi,dword ptr [data_004776e0]
    L_00417d59:
        push 43C40000h
    L_00417d5e:
        push 43F00000h
    L_00417d63:
        call asm_FUN_0040c540_0040c540
    L_00417d68:
        jmp short L_00417db0
    L_00417d6a:
        cmp eax,0Dh
    L_00417d6d:
        jne short L_00417db5
    L_00417d6f:
        mov esi,dword ptr [data_004776e0]
    L_00417d75:
        push 43C40000h
    L_00417d7a:
        push 43F00000h
    L_00417d7f:
        call asm_FUN_0040c540_0040c540
    L_00417d84:
        mov edx,dword ptr [data_00474c80]
    L_00417d8a:
        cmp edx,dword ptr [data_00474c7c]
    L_00417d90:
        je short L_00417da3
    L_00417d92:
        mov eax,474C40h
    L_00417d97:
        call asm_Score_IncrementCounterClampedNine_00418a90
    L_00417d9c:
        or dword ptr [data_00474ca0],8
    L_00417da3:
        mov eax,dword ptr [data_00474ca0]
    L_00417da8:
        or eax,1
    L_00417dab:
        mov dword ptr [data_00474ca0],eax
    L_00417db0:
        mov eax,dword ptr [data_00491fb8]
    L_00417db5:
        test byte ptr [data_00474ca0],bl
    L_00417dbb:
        jne asm_target_00417ee7
    L_00417dc1:
        cmp eax,0Eh
    L_00417dc4:
        je short L_00417de4
    L_00417dc6:
        cmp eax,0Fh
    L_00417dc9:
        je short L_00417de4
    L_00417dcb:
        mov esi,dword ptr [data_00477838]
    L_00417dd1:
        test esi,esi
    L_00417dd3:
        je short L_00417de4
    L_00417dd5:
        push esi
    L_00417dd6:
        call asm_FUN_004294a0_004294a0
    L_00417ddb:
        push esi
    L_00417ddc:
        call asm_free_004524a1
    L_00417de1:
        add esp,4
    L_00417de4:
        mov esi,dword ptr [data_004776e8]
    L_00417dea:
        test esi,esi
    L_00417dec:
        je short L_00417dfd
    L_00417dee:
        push esi
    L_00417def:
        call asm_DestroyGameState_00402440
    L_00417df4:
        push esi
    L_00417df5:
        call asm_free_004524a1
    L_00417dfa:
        add esp,4
    L_00417dfd:
        mov esi,dword ptr [data_004776e4]
    L_00417e03:
        test esi,esi
    L_00417e05:
        je short L_00417e16
    L_00417e07:
        push esi
    L_00417e08:
        call asm_DestroyGameState_00402440
    L_00417e0d:
        push esi
    L_00417e0e:
        call asm_free_004524a1
    L_00417e13:
        add esp,4
    L_00417e16:
        mov esi,dword ptr [data_00477830]
    L_00417e1c:
        test esi,esi
    L_00417e1e:
        je short L_00417e2f
    L_00417e20:
        push esi
    L_00417e21:
        call asm_FUN_00422220_00422220
    L_00417e26:
        push esi
    L_00417e27:
        call asm_free_004524a1
    L_00417e2c:
        add esp,4
    L_00417e2f:
        mov esi,dword ptr [data_0047770c]
    L_00417e35:
        test esi,esi
    L_00417e37:
        je short L_00417e48
    L_00417e39:
        push esi
    L_00417e3a:
        call asm_FUN_004145f0_004145f0
    L_00417e3f:
        push esi
    L_00417e40:
        call asm_free_004524a1
    L_00417e45:
        add esp,4
    L_00417e48:
        mov esi,dword ptr [data_00477834]
    L_00417e4e:
        test esi,esi
    L_00417e50:
        je short L_00417e61
    L_00417e52:
        push esi
    L_00417e53:
        call asm_FUN_00424ed0_00424ed0
    L_00417e58:
        push esi
    L_00417e59:
        call asm_free_004524a1
    L_00417e5e:
        add esp,4
    L_00417e61:
        mov esi,dword ptr [data_004776f0]
    L_00417e67:
        test esi,esi
    L_00417e69:
        je short L_00417e7a
    L_00417e6b:
        push esi
    L_00417e6c:
        call asm_ItemManager_DestroyRetail_00405f70
    L_00417e71:
        push esi
    L_00417e72:
        call asm_free_004524a1
    L_00417e77:
        add esp,4
    L_00417e7a:
        mov esi,dword ptr [data_00477818]
    L_00417e80:
        test esi,esi
    L_00417e82:
        je short L_00417e93
    L_00417e84:
        push esi
    L_00417e85:
        call asm_FUN_0041adf0_0041adf0
    L_00417e8a:
        push esi
    L_00417e8b:
        call asm_free_004524a1
    L_00417e90:
        add esp,4
    L_00417e93:
        mov esi,dword ptr [data_0047781c]
    L_00417e99:
        test esi,esi
    L_00417e9b:
        je short L_00417eac
    L_00417e9d:
        push esi
    L_00417e9e:
        call asm_ScoreExtendedObject_DestroyRetail_0041c1c0
    L_00417ea3:
        push esi
    L_00417ea4:
        call asm_free_004524a1
    L_00417ea9:
        add esp,4
    L_00417eac:
        mov esi,dword ptr [data_00477814]
    L_00417eb2:
        test esi,esi
    L_00417eb4:
        je short L_00417ec5
    L_00417eb6:
        push esi
    L_00417eb7:
        call asm_FUN_00418ee0_00418ee0
    L_00417ebc:
        push esi
    L_00417ebd:
        call asm_free_004524a1
    L_00417ec2:
        add esp,4
    L_00417ec5:
        mov esi,dword ptr [data_00477840]
    L_00417ecb:
        test esi,esi
    L_00417ecd:
        je asm_target_00417f80
    L_00417ed3:
        push esi
    L_00417ed4:
        call asm_FUN_0042b570_0042b570
    L_00417ed9:
        push esi
    L_00417eda:
        call asm_free_004524a1
    L_00417edf:
        add esp,4
    L_00417ee2:
        jmp asm_target_00417f80
    L_00417ee7:
        mov ebx,dword ptr [data_0047770c]
    L_00417eed:
        call asm_Recovery_ReleaseCompositeState_00414570
    L_00417ef2:
        mov esi,dword ptr [data_004776e4]
    L_00417ef8:
        test esi,esi
    L_00417efa:
        je short L_00417f0b
    L_00417efc:
        push esi
    L_00417efd:
        call asm_DestroyGameState_00402440
    L_00417f02:
        push esi
    L_00417f03:
        call asm_free_004524a1
    L_00417f08:
        add esp,4
    L_00417f0b:
        mov eax,dword ptr [data_004776e8]
    L_00417f10:
        mov dword ptr [data_004776e4],eax
    L_00417f15:
        mov eax,dword ptr [data_00477830]
    L_00417f1a:
        mov ecx,dword ptr [eax+8]
    L_00417f1d:
        test ecx,ecx
    L_00417f1f:
        mov edx,0FFFFFFFDh
    L_00417f24:
        je short L_00417f29
    L_00417f26:
        and dword ptr [ecx+4],edx
    L_00417f29:
        mov ecx,dword ptr [eax+0Ch]
    L_00417f2c:
        test ecx,ecx
    L_00417f2e:
        je short L_00417f35
    L_00417f30:
        mov eax,ecx
    L_00417f32:
        and dword ptr [eax+4],edx
    L_00417f35:
        mov eax,dword ptr [data_004776f0]
    L_00417f3a:
        mov ecx,dword ptr [eax+8]
    L_00417f3d:
        test ecx,ecx
    L_00417f3f:
        je short L_00417f44
    L_00417f41:
        and dword ptr [ecx+4],edx
    L_00417f44:
        mov ecx,dword ptr [eax+0Ch]
    L_00417f47:
        test ecx,ecx
    L_00417f49:
        je short L_00417f50
    L_00417f4b:
        mov eax,ecx
    L_00417f4d:
        and dword ptr [eax+4],edx
    L_00417f50:
        mov eax,dword ptr [data_00477838]
    L_00417f55:
        mov ecx,dword ptr [eax+1CCh]
    L_00417f5b:
        test ecx,ecx
    L_00417f5d:
        je short L_00417f62
    L_00417f5f:
        and dword ptr [ecx+4],edx
    L_00417f62:
        mov ecx,dword ptr [eax+0Ch]
    L_00417f65:
        test ecx,ecx
    L_00417f67:
        je short L_00417f6e
    L_00417f69:
        mov eax,ecx
    L_00417f6b:
        and dword ptr [eax+4],edx
    L_00417f6e:
        mov edi,dword ptr [data_00477818]
    L_00417f74:
        xor eax,eax
    L_00417f76:
        mov ecx,873A8h
    L_00417f7b:
        add edi,14h
    L_00417f7e:
        rep stosd
    L_00417f80:
        test byte ptr [data_00474ca0],9
    L_00417f87:
        jne short L_00417fa5
    L_00417f89:
        mov esi,dword ptr [data_00477704]
    L_00417f8f:
        test esi,esi
    L_00417f91:
        je short L_00417fb1
    L_00417f93:
        mov eax,esi
    L_00417f95:
        call asm_FUN_0040d530_0040d530
    L_00417f9a:
        push esi
    L_00417f9b:
        call asm_free_004524a1
    L_00417fa0:
        add esp,4
    L_00417fa3:
        jmp short L_00417fb1
    L_00417fa5:
        mov ecx,dword ptr [data_00477704]
    L_00417fab:
        push ecx
    L_00417fac:
        call asm_FUN_00409f90_00409f90
    L_00417fb1:
        mov esi,dword ptr [data_004776fc]
    L_00417fb7:
        test esi,esi
    L_00417fb9:
        je short L_00417fca
    L_00417fbb:
        push esi
    L_00417fbc:
        call asm_BulletManager_Release_0040af00
    L_00417fc1:
        push esi
    L_00417fc2:
        call asm_free_004524a1
    L_00417fc7:
        add esp,4
    L_00417fca:
        mov esi,dword ptr [data_004776ec]
    L_00417fd0:
        test esi,esi
    L_00417fd2:
        je short L_00417fe3
    L_00417fd4:
        push esi
    L_00417fd5:
        call asm_Recovery_ReleaseRawPairAndReset_00405620
    L_00417fda:
        push esi
    L_00417fdb:
        call asm_free_004524a1
    L_00417fe0:
        add esp,4
    L_00417fe3:
        mov esi,dword ptr [data_004776f4]
    L_00417fe9:
        test esi,esi
    L_00417feb:
        je short L_00417ffc
    L_00417fed:
        push esi
    L_00417fee:
        call asm_FUN_00408af0_00408af0
    L_00417ff3:
        push esi
    L_00417ff4:
        call asm_free_004524a1
    L_00417ff9:
        add esp,4
    L_00417ffc:
        mov edx,dword ptr [esp+24h]
    L_00418000:
        mov esi,dword ptr [edx+8]
    L_00418003:
        test esi,esi
    L_00418005:
        mov edi,dword ptr [data_00491be4]
    L_0041800b:
        mov ebx,dword ptr [data_004660b0]
    L_00418011:
        mov ebp,dword ptr [data_004660b4]
    L_00418017:
        je short L_0041803c
    L_00418019:
        push 492274h
    L_0041801e:
        call ebx
    L_00418020:
        inc byte ptr [data_0049231c]
    L_00418026:
        mov ecx,esi
    L_00418028:
        mov edx,edi
    L_0041802a:
        call asm_Scheduler_Remove_00449f60
    L_0041802f:
        push 492274h
    L_00418034:
        call ebp
    L_00418036:
        dec byte ptr [data_0049231c]
    L_0041803c:
        mov eax,dword ptr [esp+24h]
    L_00418040:
        mov esi,dword ptr [eax+0Ch]
    L_00418043:
        test esi,esi
    L_00418045:
        mov edi,dword ptr [data_00491be4]
    L_0041804b:
        je short L_00418070
    L_0041804d:
        push 492274h
    L_00418052:
        call ebx
    L_00418054:
        inc byte ptr [data_0049231c]
    L_0041805a:
        mov ecx,esi
    L_0041805c:
        mov edx,edi
    L_0041805e:
        call asm_Scheduler_Remove_00449f60
    L_00418063:
        push 492274h
    L_00418068:
        call ebp
    L_0041806a:
        dec byte ptr [data_0049231c]
    L_00418070:
        test byte ptr [data_00474ca0],22h
    L_00418077:
        pop edi
    L_00418078:
        pop esi
    L_00418079:
        pop ebp
    L_0041807a:
        mov dword ptr [data_00477810],0
    L_00418084:
        pop ebx
    L_00418085:
        jne short L_004180a7
    L_00418087:
        test byte ptr [data_00491d78],10h
    L_0041808e:
        mov edx,46DF98h
    L_00418093:
        push 0
    L_00418095:
        mov eax,492590h
    L_0041809a:
        je short L_004180a0
    L_0041809c:
        push 4
    L_0041809e:
        jmp short L_004180a2
    L_004180a0:
        push 3
    L_004180a2:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004180a7:
        mov eax,dword ptr [data_00474ca0]
    L_004180ac:
        and al,1
    L_004180ae:
        neg al
    L_004180b0:
        mov dword ptr [data_004918a4],1
    L_004180ba:
        sbb eax,eax
    L_004180bc:
        and eax,1000000h
    L_004180c1:
        add eax,0FF000000h
    L_004180c6:
        mov dword ptr [data_004923a8],eax
    L_004180cb:
        add esp,10h
    L_004180ce:
        ret 4
    }
}





// BLOCKED (D3501): closest_byte_count=311/311; first_diff=none (retail
// assembly baseline only; no readable candidate retained);
// residual_class=private Scheduler_Remove receiver/register ABI, linked-list
// node layout at +0x72DAD4/+0x72DADC, and child flag propagation through
// unresolved game-state structures.
// variants_tested=live Ghidra complete-function analysis with callers/callees,
// xrefs, disassembly, and variables; MSVC 13.10 scoped probe baseline exact;
// no readable candidate retained. next_lever=native-LTCG schema2 cluster with
// real 0x00422360/0x00417C80 callers and game-state node layouts.


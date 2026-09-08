#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455D53..0x00455FE6: FUN_00455d53
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00455d53_00455d53() {
    __asm {
    L_00455d53:
        push ebp
    L_00455d54:
        lea ebp,[esp-74h]
    L_00455d58:
        sub esp,1C0h
    L_00455d5e:
        mov eax,dword ptr [data_00473660]
    L_00455d63:
        push esi
    L_00455d64:
        lea ecx,[ebp-11Ch]
    L_00455d6a:
        push ecx
    L_00455d6b:
        lea ecx,[ebp-138h]
    L_00455d71:
        push ecx
    L_00455d72:
        xor eax,ebp
    L_00455d74:
        lea ecx,[ebp-14h]
    L_00455d77:
        mov dword ptr [ebp+70h],eax
    L_00455d7a:
        mov eax,dword ptr [ebp+7Ch]
    L_00455d7d:
        push ecx
    L_00455d7e:
        push eax
    L_00455d7f:
        call asm_FUN_00455bf3_00455bf3
    L_00455d84:
        add esp,14h
    L_00455d87:
        test eax,eax
    L_00455d89:
        je asm_target_00455fd8
    L_00455d8f:
        push ebx
    L_00455d90:
        lea ebx,[esi+esi*2]
    L_00455d93:
        shl ebx,2
    L_00455d96:
        push dword ptr [ebx+47334Ch]
    L_00455d9c:
        lea eax,[ebp-14h]
    L_00455d9f:
        push eax
    L_00455da0:
        call asm_strcmp_0045bf30
    L_00455da5:
        test eax,eax
    L_00455da7:
        pop ecx
    L_00455da8:
        pop ecx
    L_00455da9:
        jne short L_00455db6
    L_00455dab:
        mov eax,dword ptr [ebx+47334Ch]
    L_00455db1:
        jmp asm_target_00455fd7
    L_00455db6:
        lea eax,[ebp-14h]
    L_00455db9:
        push eax
    L_00455dba:
        call asm_strlen_00456720
    L_00455dbf:
        inc eax
    L_00455dc0:
        push eax
    L_00455dc1:
        call asm_malloc_00452706
    L_00455dc6:
        test eax,eax
    L_00455dc8:
        pop ecx
    L_00455dc9:
        pop ecx
    L_00455dca:
        mov dword ptr [ebp-124h],eax
    L_00455dd0:
        je asm_target_00455fd7
    L_00455dd6:
        mov eax,dword ptr [ebx+47334Ch]
    L_00455ddc:
        push edi
    L_00455ddd:
        mov dword ptr [ebp-120h],eax
    L_00455de3:
        lea edi,[esi*4+47764Ch]
    L_00455dea:
        mov eax,dword ptr [edi]
    L_00455dec:
        mov dword ptr [ebp-13Ch],eax
    L_00455df2:
        lea eax,[esi+esi*2]
    L_00455df5:
        lea eax,[eax*2+47766Ch]
    L_00455dfc:
        push 6
    L_00455dfe:
        push eax
    L_00455dff:
        mov dword ptr [ebp-118h],eax
    L_00455e05:
        lea eax,[ebp-14Ch]
    L_00455e0b:
        push eax
    L_00455e0c:
        call asm_memcpy_0045bfc0
    L_00455e11:
        mov eax,dword ptr [data_00477664]
    L_00455e16:
        mov dword ptr [ebp-128h],eax
    L_00455e1c:
        lea eax,[ebp-14h]
    L_00455e1f:
        push eax
    L_00455e20:
        push dword ptr [ebp-124h]
    L_00455e26:
        call asm_FUN_0045bd80_0045bd80
    L_00455e2b:
        mov dword ptr [ebx+47334Ch],eax
    L_00455e31:
        movzx eax,word ptr [ebp-138h]
    L_00455e38:
        mov dword ptr [edi],eax
    L_00455e3a:
        push 6
    L_00455e3c:
        lea eax,[ebp-138h]
    L_00455e42:
        push eax
    L_00455e43:
        push dword ptr [ebp-118h]
    L_00455e49:
        call asm_memcpy_0045bfc0
    L_00455e4e:
        add esp,20h
    L_00455e51:
        cmp esi,2
    L_00455e54:
        jne asm_target_00455f6f
    L_00455e5a:
        mov eax,dword ptr [ebp-11Ch]
    L_00455e60:
        mov ecx,dword ptr [data_00473230]
    L_00455e66:
        and dword ptr [ebp-118h],0
    L_00455e6d:
        mov dword ptr [data_00477664],eax
    L_00455e72:
        mov eax,dword ptr [data_00473234]
    L_00455e77:
        mov dword ptr [ebp-12Ch],eax
    L_00455e7d:
        mov eax,473210h
    L_00455e82:
        mov edx,dword ptr [ebp-11Ch]
    L_00455e88:
        cmp edx,dword ptr [eax]
    L_00455e8a:
        je short L_00455ec0
    L_00455e8c:
        mov edx,dword ptr [eax]
    L_00455e8e:
        inc dword ptr [ebp-118h]
    L_00455e94:
        mov dword ptr [eax],ecx
    L_00455e96:
        mov ecx,dword ptr [ebp-12Ch]
    L_00455e9c:
        mov dword ptr [ebp-144h],edx
    L_00455ea2:
        mov edx,dword ptr [eax+4]
    L_00455ea5:
        mov dword ptr [eax+4],ecx
    L_00455ea8:
        mov ecx,dword ptr [ebp-144h]
    L_00455eae:
        add eax,8
    L_00455eb1:
        cmp eax,473238h
    L_00455eb6:
        mov dword ptr [ebp-12Ch],edx
    L_00455ebc:
        jl short L_00455e82
    L_00455ebe:
        jmp short L_00455eed
    L_00455ec0:
        mov eax,dword ptr [ebp-118h]
    L_00455ec6:
        test eax,eax
    L_00455ec8:
        je short L_00455eed
    L_00455eca:
        lea eax,[eax*8+473210h]
    L_00455ed1:
        mov edx,dword ptr [eax]
    L_00455ed3:
        mov dword ptr [data_00473210],edx
    L_00455ed9:
        mov edx,dword ptr [eax+4]
    L_00455edc:
        mov dword ptr [data_00473214],edx
    L_00455ee2:
        mov dword ptr [eax],ecx
    L_00455ee4:
        mov ecx,dword ptr [ebp-12Ch]
    L_00455eea:
        mov dword ptr [eax+4],ecx
    L_00455eed:
        cmp dword ptr [ebp-118h],5
    L_00455ef4:
        jne short L_00455f65
    L_00455ef6:
        push 1
    L_00455ef8:
        push dword ptr [data_00477654]
    L_00455efe:
        lea eax,[ebp-114h]
    L_00455f04:
        push dword ptr [ebp-11Ch]
    L_00455f0a:
        push eax
    L_00455f0b:
        push 7Fh
    L_00455f0d:
        push 46A928h
    L_00455f12:
        push 1
    L_00455f14:
        call asm_crtGetStringTypeA_0045a25d
    L_00455f19:
        add esp,1Ch
    L_00455f1c:
        test eax,eax
    L_00455f1e:
        je short L_00455f50
    L_00455f20:
        xor eax,eax
    L_00455f22:
        and byte ptr [ebp+eax*2-113h],1
    L_00455f2a:
        inc eax
    L_00455f2b:
        cmp eax,7Fh
    L_00455f2e:
        jb short L_00455f22
    L_00455f30:
        push 0FEh
    L_00455f35:
        lea eax,[ebp-114h]
    L_00455f3b:
        push 46A828h
    L_00455f40:
        push eax
    L_00455f41:
        call asm_memcmp_0045cc10
    L_00455f46:
        add esp,0Ch
    L_00455f49:
        neg eax
    L_00455f4b:
        sbb eax,eax
    L_00455f4d:
        inc eax
    L_00455f4e:
        jmp short L_00455f52
    L_00455f50:
        xor eax,eax
    L_00455f52:
        mov ecx,dword ptr [data_00477664]
    L_00455f58:
        mov dword ptr [data_00473214],eax
    L_00455f5d:
        mov dword ptr [data_00473210],ecx
    L_00455f63:
        jmp short L_00455f6a
    L_00455f65:
        mov eax,dword ptr [data_00473214]
    L_00455f6a:
        mov dword ptr [data_00473ae0],eax
    L_00455f6f:
        cmp esi,1
    L_00455f72:
        jne short L_00455f7f
    L_00455f74:
        mov eax,dword ptr [ebp-11Ch]
    L_00455f7a:
        mov dword ptr [data_00477668],eax
    L_00455f7f:
        call dword ptr [ebx+473350h]
    L_00455f85:
        test eax,eax
    L_00455f87:
        je short L_00455fb8
    L_00455f89:
        mov eax,dword ptr [ebp-120h]
    L_00455f8f:
        push dword ptr [ebp-124h]
    L_00455f95:
        mov dword ptr [ebx+47334Ch],eax
    L_00455f9b:
        call asm_free_00452422
    L_00455fa0:
        mov eax,dword ptr [ebp-13Ch]
    L_00455fa6:
        mov dword ptr [edi],eax
    L_00455fa8:
        mov eax,dword ptr [ebp-128h]
    L_00455fae:
        mov dword ptr [data_00477664],eax
    L_00455fb3:
        pop ecx
    L_00455fb4:
        xor eax,eax
    L_00455fb6:
        jmp short L_00455fd6
    L_00455fb8:
        cmp dword ptr [ebp-120h],4731B0h
    L_00455fc2:
        je short L_00455fd0
    L_00455fc4:
        push dword ptr [ebp-120h]
    L_00455fca:
        call asm_free_00452422
    L_00455fcf:
        pop ecx
    L_00455fd0:
        mov eax,dword ptr [ebx+47334Ch]
    L_00455fd6:
        pop edi
    L_00455fd7:
        pop ebx
    L_00455fd8:
        mov ecx,dword ptr [ebp+70h]
    L_00455fdb:
        xor ecx,ebp
    L_00455fdd:
        call asm_security_check_cookie_00458ea5
    L_00455fe2:
        add ebp,74h
    L_00455fe5:
        leave
    L_00455fe6:
        ret
    }
}

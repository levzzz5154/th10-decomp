// BLOCKED (D3906): closest_byte_count=0/261; first_diff=0x0042BE20
// (no standalone readable body retained; the exact naked baseline remains
// the only compiled artifact).
// residual_class=private ESI receiver, stack-cookie frame, sprintf buffer
// lifetime, allocator/virtual-interface calls, and object layout spanning
// variants_tested=live IDA assembly and caller 0x0042BE10; no Ghidra
// pseudocode; MSVC 13.10 schema-2/native-LTCG feasibility review found no
// standalone readable candidate because the caller and all helper ABIs
// remain private-register assembly.
// next_lever=promote 0x0042BE10, this leaf, and the allocator/interface
// helpers as one schema-2 native-LTCG cluster with a production object
// layout, then replace the naked region only after an exact probe.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BE20..0x0042BF24: FUN_0042be20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042be20_0042be20() {
    __asm {
    L_0042be20:
        sub esp,108h
    L_0042be26:
        mov eax,dword ptr [data_00473660]
    L_0042be2b:
        mov ecx,dword ptr [esi+34h]
    L_0042be2e:
        xor eax,esp
    L_0042be30:
        mov dword ptr [esp+104h],eax
    L_0042be37:
        mov eax,dword ptr [esi+114h]
    L_0042be3d:
        mov edx,dword ptr [ecx+eax*4]
    L_0042be40:
        push ebx
    L_0042be41:
        push edx
    L_0042be42:
        lea eax,[esp+8]
    L_0042be46:
        push 46E1C8h
    L_0042be4b:
        push eax
    L_0042be4c:
        call asm_sprintf_00452ae8
    L_0042be51:
        mov ecx,dword ptr [esi+2DCh]
    L_0042be57:
        xor ebx,ebx
    L_0042be59:
        add esp,0Ch
    L_0042be5c:
        cmp ecx,ebx
    L_0042be5e:
        je short L_0042be6d
    L_0042be60:
        mov edx,dword ptr [ecx]
    L_0042be62:
        push 1
    L_0042be64:
        call dword ptr [edx+14h]
    L_0042be67:
        mov dword ptr [esi+2DCh],ebx
    L_0042be6d:
        mov eax,dword ptr [esi+2E0h]
    L_0042be73:
        cmp eax,ebx
    L_0042be75:
        mov dword ptr [esi+2DCh],ebx
    L_0042be7b:
        je short L_0042be8c
    L_0042be7d:
        push eax
    L_0042be7e:
        call asm_free_00452422
    L_0042be83:
        add esp,4
    L_0042be86:
        mov dword ptr [esi+2E0h],ebx
    L_0042be8c:
        push ebx
    L_0042be8d:
        push ebx
    L_0042be8e:
        lea eax,[esp+0Ch]
    L_0042be92:
        call asm_FUN_0044b360_0044b360
    L_0042be97:
        push 1098h
    L_0042be9c:
        mov dword ptr [esi+2E0h],eax
    L_0042bea2:
        call asm_operator_new_00452493
    L_0042bea7:
        mov edx,eax
    L_0042bea9:
        add esp,4
    L_0042beac:
        cmp edx,ebx
    L_0042beae:
        je short L_0042bed3
    L_0042beb0:
        push edi
    L_0042beb1:
        mov dword ptr [edx],46D0F0h
    L_0042beb7:
        mov ecx,426h
    L_0042bebc:
        xor eax,eax
    L_0042bebe:
        mov edi,edx
    L_0042bec0:
        mov dword ptr [edx+1090h],ebx
    L_0042bec6:
        mov dword ptr [edx+1094h],ebx
    L_0042becc:
        rep stosd
    L_0042bece:
        mov ecx,edx
    L_0042bed0:
        pop edi
    L_0042bed1:
        jmp short L_0042bed5
    L_0042bed3:
        xor ecx,ecx
    L_0042bed5:
        mov edx,dword ptr [esi+2E0h]
    L_0042bedb:
        mov dword ptr [esi+2D8h],ecx
    L_0042bee1:
        mov eax,dword ptr [ecx]
    L_0042bee3:
        push edx
    L_0042bee4:
        call dword ptr [eax]
    L_0042bee6:
        mov eax,dword ptr [esi+2D8h]
    L_0042beec:
        mov ecx,dword ptr [eax+8]
    L_0042beef:
        mov eax,ecx
    L_0042bef1:
        cmp eax,ebx
    L_0042bef3:
        mov dword ptr [esi+1F4h],ecx
    L_0042bef9:
        je short L_0042bf00
    L_0042befb:
        jg short L_0042bf00
    L_0042befd:
        lea ebx,[eax-1]
    L_0042bf00:
        mov ecx,dword ptr [esp+108h]
    L_0042bf07:
        mov dword ptr [esi+1ECh],ebx
    L_0042bf0d:
        pop ebx
    L_0042bf0e:
        xor ecx,esp
    L_0042bf10:
        mov dword ptr [esi+30h],1
    L_0042bf17:
        xor eax,eax
    L_0042bf19:
        call asm_security_check_cookie_00458ea5
    L_0042bf1e:
        add esp,108h
    L_0042bf24:
        ret
    }
}

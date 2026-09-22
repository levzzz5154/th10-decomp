#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3604): closest_byte_count=0/260; first_diff=unmeasured;
// residual_class=private EAX input plus caller-owned buffer/length ABI, with
// helper 0x00452730 and 0x0041A0A0 sequencing across the stage-tip parser.
// variants_tested=live Ghidra decompilation, caller 0x00419960, and exact
// retail wrapper baseline; readable public-ABI candidates cannot preserve the
// EAX live-in without a native caller cluster.
// next_lever=native-LTCG cluster joining 0x00419960, this reader, and the
// 0x00452730/0x0041A0A0 helper family.
// 0x00419F40..0x0041A043: FUN_00419f40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00419f40_00419f40() {
    __asm {
    L_00419f40:
        mov ecx,dword ptr [esp+0Ch]
    L_00419f44:
        push ebx
    L_00419f45:
        mov edx,ecx
    L_00419f47:
        push ebp
    L_00419f48:
        mov ebp,dword ptr [esp+0Ch]
    L_00419f4c:
        shr ecx,2
    L_00419f4f:
        push edi
    L_00419f50:
        mov ebx,eax
    L_00419f52:
        xor eax,eax
    L_00419f54:
        mov edi,ebp
    L_00419f56:
        rep stosd
    L_00419f58:
        mov ecx,edx
    L_00419f5a:
        and ecx,3
    L_00419f5d:
        rep stosb
    L_00419f5f:
        cmp byte ptr [ebp],0
    L_00419f63:
        jne asm_target_0041a03c
    L_00419f69:
        push esi
    L_00419f6a:
        lea ebx,[ebx+force_disp32_zero]
    L_00419f70:
        push 0Ah
    L_00419f72:
        push ebx
    L_00419f73:
        call asm_FUN_00452730_00452730
    L_00419f78:
        add esp,8
    L_00419f7b:
        test eax,eax
    L_00419f7d:
        jne short L_00419f92
    L_00419f7f:
        push 0Dh
    L_00419f81:
        push ebx
    L_00419f82:
        call asm_FUN_00452730_00452730
    L_00419f87:
        add esp,8
    L_00419f8a:
        test eax,eax
    L_00419f8c:
        je asm_target_0041a01d
    L_00419f92:
        mov edx,dword ptr [esp+1Ch]
    L_00419f96:
        mov ecx,eax
    L_00419f98:
        sub ecx,ebx
    L_00419f9a:
        dec edx
    L_00419f9b:
        cmp ecx,edx
    L_00419f9d:
        jl short L_00419fa1
    L_00419f9f:
        mov ecx,edx
    L_00419fa1:
        mov edx,ecx
    L_00419fa3:
        shr ecx,2
    L_00419fa6:
        mov esi,ebx
    L_00419fa8:
        mov edi,ebp
    L_00419faa:
        rep movsd
    L_00419fac:
        mov ecx,edx
    L_00419fae:
        and ecx,3
    L_00419fb1:
        rep movsb
    L_00419fb3:
        mov ecx,dword ptr [esp+18h]
    L_00419fb7:
        mov edx,dword ptr [ecx]
    L_00419fb9:
        sub ebx,eax
    L_00419fbb:
        add edx,ebx
    L_00419fbd:
        mov dword ptr [ecx],edx
    L_00419fbf:
        mov ebx,eax
    L_00419fc1:
        mov al,byte ptr [ebx]
    L_00419fc3:
        cmp al,0Ah
    L_00419fc5:
        je short L_00419fcb
    L_00419fc7:
        cmp al,0Dh
    L_00419fc9:
        jne short L_00419fd3
    L_00419fcb:
        mov eax,dword ptr [ecx]
    L_00419fcd:
        inc ebx
    L_00419fce:
        dec eax
    L_00419fcf:
        mov dword ptr [ecx],eax
    L_00419fd1:
        jmp short L_00419fc1
    L_00419fd3:
        push 23h
    L_00419fd5:
        push ebp
    L_00419fd6:
        call asm_FUN_00452730_00452730
    L_00419fdb:
        mov edx,eax
    L_00419fdd:
        add esp,8
    L_00419fe0:
        test edx,edx
    L_00419fe2:
        je short L_0041a003
    L_00419fe4:
        mov edi,dword ptr [esp+1Ch]
    L_00419fe8:
        mov ecx,ebp
    L_00419fea:
        sub ecx,edx
    L_00419fec:
        add ecx,edi
    L_00419fee:
        mov esi,ecx
    L_00419ff0:
        shr ecx,2
    L_00419ff3:
        xor eax,eax
    L_00419ff5:
        mov edi,edx
    L_00419ff7:
        rep stosd
    L_00419ff9:
        mov ecx,esi
    L_00419ffb:
        and ecx,3
    L_00419ffe:
        rep stosb
    L_0041a000:
        mov byte ptr [edx],0
    L_0041a003:
        mov eax,ebp
    L_0041a005:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_0041a00a:
        cmp byte ptr [ebp],0
    L_0041a00e:
        je asm_target_00419f70
    L_0041a014:
        pop esi
    L_0041a015:
        pop edi
    L_0041a016:
        pop ebp
    L_0041a017:
        mov eax,ebx
    L_0041a019:
        pop ebx
    L_0041a01a:
        ret 0Ch
    L_0041a01d:
        mov eax,dword ptr [esp+18h]
    L_0041a021:
        mov ecx,dword ptr [eax]
    L_0041a023:
        mov edx,ecx
    L_0041a025:
        shr ecx,2
    L_0041a028:
        mov esi,ebx
    L_0041a02a:
        mov edi,ebp
    L_0041a02c:
        rep movsd
    L_0041a02e:
        mov ecx,edx
    L_0041a030:
        and ecx,3
    L_0041a033:
        rep movsb
    L_0041a035:
        mov dword ptr [eax],0
    L_0041a03b:
        pop esi
    L_0041a03c:
        pop edi
    L_0041a03d:
        pop ebp
    L_0041a03e:
        mov eax,ebx
    L_0041a040:
        pop ebx
    L_0041a041:
        ret 0Ch
    }
}

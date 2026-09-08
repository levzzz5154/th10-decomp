#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CFB8..0x0045D14B: FUN_0045cfb8
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045cfb8_0045cfb8() {
    __asm {
    L_0045cfb8:
        push ebp
    L_0045cfb9:
        mov ebp,esp
    L_0045cfbb:
        sub esp,1Ch
    L_0045cfbe:
        mov eax,dword ptr [data_00473660]
    L_0045cfc3:
        push ebx
    L_0045cfc4:
        push esi
    L_0045cfc5:
        mov esi,dword ptr [ebp+8]
    L_0045cfc8:
        xor eax,ebp
    L_0045cfca:
        xor ebx,ebx
    L_0045cfcc:
        cmp esi,ebx
    L_0045cfce:
        mov dword ptr [ebp-4],eax
    L_0045cfd1:
        push edi
    L_0045cfd2:
        je asm_target_0045d12c
    L_0045cfd8:
        xor edx,edx
    L_0045cfda:
        xor eax,eax
    L_0045cfdc:
        cmp dword ptr [eax+473B08h],esi
    L_0045cfe2:
        je short L_0045d049
    L_0045cfe4:
        add eax,30h
    L_0045cfe7:
        inc edx
    L_0045cfe8:
        cmp eax,0F0h
    L_0045cfed:
        jb short L_0045cfdc
    L_0045cfef:
        lea eax,[ebp-18h]
    L_0045cff2:
        push eax
    L_0045cff3:
        push esi
    L_0045cff4:
        call dword ptr [data_00466064]
    L_0045cffa:
        cmp eax,1
    L_0045cffd:
        jne asm_target_0045d124
    L_0045d003:
        push 40h
    L_0045d005:
        xor eax,eax
    L_0045d007:
        cmp dword ptr [ebp-18h],1
    L_0045d00b:
        pop ecx
    L_0045d00c:
        mov edi,497FA0h
    L_0045d011:
        rep stosd
    L_0045d013:
        stosb
    L_0045d014:
        mov dword ptr [data_004980a4],esi
    L_0045d01a:
        mov dword ptr [data_00497f90],ebx
    L_0045d020:
        jbe asm_target_0045d112
    L_0045d026:
        cmp byte ptr [ebp-12h],0
    L_0045d02a:
        je asm_target_0045d0ea
    L_0045d030:
        lea ecx,[ebp-11h]
    L_0045d033:
        mov dl,byte ptr [ecx]
    L_0045d035:
        test dl,dl
    L_0045d037:
        je asm_target_0045d0ea
    L_0045d03d:
        movzx eax,byte ptr [ecx-1]
    L_0045d041:
        movzx edx,dl
    L_0045d044:
        jmp asm_target_0045d0da
    L_0045d049:
        push 40h
    L_0045d04b:
        xor eax,eax
    L_0045d04d:
        pop ecx
    L_0045d04e:
        mov edi,497FA0h
    L_0045d053:
        rep stosd
    L_0045d055:
        lea ecx,[edx+edx*2]
    L_0045d058:
        shl ecx,4
    L_0045d05b:
        mov dword ptr [ebp-1Ch],ebx
    L_0045d05e:
        stosb
    L_0045d05f:
        lea ebx,[ecx+473B18h]
    L_0045d065:
        mov al,byte ptr [ebx]
    L_0045d067:
        mov esi,ebx
    L_0045d069:
        jmp short L_0045d094
    L_0045d06b:
        mov dl,byte ptr [esi+1]
    L_0045d06e:
        test dl,dl
    L_0045d070:
        je short L_0045d098
    L_0045d072:
        movzx eax,al
    L_0045d075:
        movzx edi,dl
    L_0045d078:
        cmp eax,edi
    L_0045d07a:
        ja short L_0045d090
    L_0045d07c:
        mov edx,dword ptr [ebp-1Ch]
    L_0045d07f:
        mov dl,byte ptr [edx+473B00h]
    L_0045d085:
        or byte ptr [eax+497FA1h],dl
    L_0045d08b:
        inc eax
    L_0045d08c:
        cmp eax,edi
    L_0045d08e:
        jbe short L_0045d085
    L_0045d090:
        inc esi
    L_0045d091:
        inc esi
    L_0045d092:
        mov al,byte ptr [esi]
    L_0045d094:
        test al,al
    L_0045d096:
        jne short L_0045d06b
    L_0045d098:
        inc dword ptr [ebp-1Ch]
    L_0045d09b:
        add ebx,8
    L_0045d09e:
        cmp dword ptr [ebp-1Ch],4
    L_0045d0a2:
        jb short L_0045d065
    L_0045d0a4:
        mov eax,dword ptr [ebp+8]
    L_0045d0a7:
        mov dword ptr [data_004980a4],eax
    L_0045d0ac:
        mov dword ptr [data_00497f98],1
    L_0045d0b6:
        call asm_FUN_0045cd56_0045cd56
    L_0045d0bb:
        lea ecx,[ecx+473B0Ch]
    L_0045d0c1:
        mov esi,ecx
    L_0045d0c3:
        mov edi,4980B0h
    L_0045d0c8:
        movsd
    L_0045d0c9:
        movsd
    L_0045d0ca:
        mov dword ptr [data_00497f90],eax
    L_0045d0cf:
        movsd
    L_0045d0d0:
        jmp short L_0045d131
    L_0045d0d2:
        or byte ptr [eax+497FA1h],4
    L_0045d0d9:
        inc eax
    L_0045d0da:
        cmp eax,edx
    L_0045d0dc:
        jbe short L_0045d0d2
    L_0045d0de:
        inc ecx
    L_0045d0df:
        inc ecx
    L_0045d0e0:
        cmp byte ptr [ecx-1],0
    L_0045d0e4:
        jne asm_target_0045d033
    L_0045d0ea:
        xor ecx,ecx
    L_0045d0ec:
        inc ecx
    L_0045d0ed:
        mov eax,ecx
    L_0045d0ef:
        or byte ptr [eax+497FA1h],8
    L_0045d0f6:
        inc eax
    L_0045d0f7:
        cmp eax,0FFh
    L_0045d0fc:
        jb short L_0045d0ef
    L_0045d0fe:
        mov eax,esi
    L_0045d100:
        call asm_FUN_0045cd56_0045cd56
    L_0045d105:
        mov dword ptr [data_00497f90],eax
    L_0045d10a:
        mov dword ptr [data_00497f98],ecx
    L_0045d110:
        jmp short L_0045d118
    L_0045d112:
        mov dword ptr [data_00497f98],ebx
    L_0045d118:
        xor eax,eax
    L_0045d11a:
        mov edi,4980B0h
    L_0045d11f:
        stosd
    L_0045d120:
        stosd
    L_0045d121:
        stosd
    L_0045d122:
        jmp short L_0045d131
    L_0045d124:
        cmp dword ptr [data_00477690],ebx
    L_0045d12a:
        je short L_0045d13a
    L_0045d12c:
        call asm_setSBCS_0045cd85
    L_0045d131:
        call asm_FUN_0045cdae_0045cdae
    L_0045d136:
        xor eax,eax
    L_0045d138:
        jmp short L_0045d13d
    L_0045d13a:
        or eax,0FFFFFFFFh
    L_0045d13d:
        mov ecx,dword ptr [ebp-4]
    L_0045d140:
        pop edi
    L_0045d141:
        pop esi
    L_0045d142:
        xor ecx,ebp
    L_0045d144:
        pop ebx
    L_0045d145:
        call asm_security_check_cookie_00458ea5
    L_0045d14a:
        leave
    L_0045d14b:
        ret
    }
}

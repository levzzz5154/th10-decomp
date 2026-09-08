#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461ED0..0x00461F30: copy_environ
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_copy_environ_00461ed0() {
    __asm {
    L_00461ed0:
        push ebp
    L_00461ed1:
        mov ebp,esp
    L_00461ed3:
        push ecx
    L_00461ed4:
        xor ecx,ecx
    L_00461ed6:
        test edi,edi
    L_00461ed8:
        mov eax,edi
    L_00461eda:
        jne short L_00461ede
    L_00461edc:
        leave
    L_00461edd:
        ret
    L_00461ede:
        cmp dword ptr [edi],0
    L_00461ee1:
        je short L_00461eec
    L_00461ee3:
        add eax,4
    L_00461ee6:
        inc ecx
    L_00461ee7:
        cmp dword ptr [eax],0
    L_00461eea:
        jne short L_00461ee3
    L_00461eec:
        push ebx
    L_00461eed:
        lea eax,[ecx*4+4]
    L_00461ef4:
        push esi
    L_00461ef5:
        push eax
    L_00461ef6:
        call asm_malloc_00452706
    L_00461efb:
        mov esi,eax
    L_00461efd:
        test esi,esi
    L_00461eff:
        pop ecx
    L_00461f00:
        mov dword ptr [ebp-4],esi
    L_00461f03:
        jne short L_00461f0d
    L_00461f05:
        push 9
    L_00461f07:
        call asm_amsg_exit_0045373d
    L_00461f0c:
        pop ecx
    L_00461f0d:
        mov eax,dword ptr [edi]
    L_00461f0f:
        mov ebx,edi
    L_00461f11:
        jmp short L_00461f24
    L_00461f13:
        push eax
    L_00461f14:
        call asm_strdup_00462250
    L_00461f19:
        mov dword ptr [esi],eax
    L_00461f1b:
        add esi,4
    L_00461f1e:
        add ebx,4
    L_00461f21:
        mov eax,dword ptr [ebx]
    L_00461f23:
        pop ecx
    L_00461f24:
        test eax,eax
    L_00461f26:
        jne short L_00461f13
    L_00461f28:
        and dword ptr [esi],eax
    L_00461f2a:
        mov eax,dword ptr [ebp-4]
    L_00461f2d:
        pop esi
    L_00461f2e:
        pop ebx
    L_00461f2f:
        leave
    L_00461f30:
        ret
    }
}

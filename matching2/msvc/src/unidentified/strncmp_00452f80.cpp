#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452F80..0x00452FB8: _strncmp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strncmp_00452f80() {
    __asm {
    L_00452f80:
        push ebp
    L_00452f81:
        mov ebp,esp
    L_00452f83:
        push edi
    L_00452f84:
        push esi
    L_00452f85:
        push ebx
    L_00452f86:
        mov ecx,dword ptr [ebp+10h]
    L_00452f89:
        jecxz short L_00452fb2
    L_00452f8b:
        mov ebx,ecx
    L_00452f8d:
        mov edi,dword ptr [ebp+8]
    L_00452f90:
        mov esi,edi
    L_00452f92:
        xor eax,eax
    L_00452f94:
        repne scasb
    L_00452f96:
        neg ecx
    L_00452f98:
        add ecx,ebx
    L_00452f9a:
        mov edi,esi
    L_00452f9c:
        mov esi,dword ptr [ebp+0Ch]
    L_00452f9f:
        repe cmpsb
    L_00452fa1:
        mov al,byte ptr [esi-1]
    L_00452fa4:
        xor ecx,ecx
    L_00452fa6:
        cmp al,byte ptr [edi-1]
    L_00452fa9:
        ja short L_00452fb0
    L_00452fab:
        je short L_00452fb2
    L_00452fad:
        sub ecx,2
    L_00452fb0:
        not ecx
    L_00452fb2:
        mov eax,ecx
    L_00452fb4:
        pop ebx
    L_00452fb5:
        pop esi
    L_00452fb6:
        pop edi
    L_00452fb7:
        leave
    L_00452fb8:
        ret
    }
}

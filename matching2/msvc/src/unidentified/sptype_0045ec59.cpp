#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EC59..0x0045ECB3: __sptype
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sptype_0045ec59() {
    __asm {
    L_0045ec59:
        push ebp
    L_0045ec5a:
        mov ebp,esp
    L_0045ec5c:
        xor edx,edx
    L_0045ec5e:
        cmp dword ptr [ebp+0Ch],7FF00000h
    L_0045ec65:
        jne short L_0045ec71
    L_0045ec67:
        cmp dword ptr [ebp+8],edx
    L_0045ec6a:
        jne short L_0045ec83
    L_0045ec6c:
        xor eax,eax
    L_0045ec6e:
        inc eax
    L_0045ec6f:
        pop ebp
    L_0045ec70:
        ret
    L_0045ec71:
        cmp dword ptr [ebp+0Ch],0FFF00000h
    L_0045ec78:
        jne short L_0045ec83
    L_0045ec7a:
        cmp dword ptr [ebp+8],edx
    L_0045ec7d:
        jne short L_0045ec83
    L_0045ec7f:
        push 2
    L_0045ec81:
        jmp short L_0045ecad
    L_0045ec83:
        mov ecx,dword ptr [ebp+0Eh]
    L_0045ec86:
        mov eax,7FF8h
    L_0045ec8b:
        and ecx,eax
    L_0045ec8d:
        cmp cx,ax
    L_0045ec90:
        jne short L_0045ec96
    L_0045ec92:
        push 3
    L_0045ec94:
        jmp short L_0045ecad
    L_0045ec96:
        cmp cx,7FF0h
    L_0045ec9b:
        jne short L_0045ecb0
    L_0045ec9d:
        test dword ptr [ebp+0Ch],7FFFFh
    L_0045eca4:
        jne short L_0045ecab
    L_0045eca6:
        cmp dword ptr [ebp+8],edx
    L_0045eca9:
        je short L_0045ecb0
    L_0045ecab:
        push 4
    L_0045ecad:
        pop eax
    L_0045ecae:
        pop ebp
    L_0045ecaf:
        ret
    L_0045ecb0:
        xor eax,eax
    L_0045ecb2:
        pop ebp
    L_0045ecb3:
        ret
    }
}

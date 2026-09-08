#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454E81..0x00454EB7: write_string
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_write_string_00454e81() {
    __asm {
    L_00454e81:
        test byte ptr [edi+0Ch],40h
    L_00454e85:
        push ebx
    L_00454e86:
        push esi
    L_00454e87:
        mov esi,eax
    L_00454e89:
        mov ebx,ecx
    L_00454e8b:
        je short L_00454eae
    L_00454e8d:
        cmp dword ptr [edi+8],0
    L_00454e91:
        jne short L_00454eae
    L_00454e93:
        mov eax,dword ptr [esp+0Ch]
    L_00454e97:
        add dword ptr [esi],eax
    L_00454e99:
        jmp short L_00454eb5
    L_00454e9b:
        mov al,byte ptr [ebx]
    L_00454e9d:
        dec dword ptr [esp+0Ch]
    L_00454ea1:
        mov ecx,edi
    L_00454ea3:
        call asm_write_char_00454e2a
    L_00454ea8:
        inc ebx
    L_00454ea9:
        cmp dword ptr [esi],0FFFFFFFFh
    L_00454eac:
        je short L_00454eb5
    L_00454eae:
        cmp dword ptr [esp+0Ch],0
    L_00454eb3:
        jg short L_00454e9b
    L_00454eb5:
        pop esi
    L_00454eb6:
        pop ebx
    L_00454eb7:
        ret
    }
}

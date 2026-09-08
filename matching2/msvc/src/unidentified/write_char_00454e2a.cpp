#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454E2A..0x00454E5C: write_char
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_write_char_00454e2a() {
    __asm {
    L_00454e2a:
        test byte ptr [ecx+0Ch],40h
    L_00454e2e:
        je short L_00454e36
    L_00454e30:
        cmp dword ptr [ecx+8],0
    L_00454e34:
        je short L_00454e5a
    L_00454e36:
        dec dword ptr [ecx+4]
    L_00454e39:
        js short L_00454e46
    L_00454e3b:
        mov edx,dword ptr [ecx]
    L_00454e3d:
        mov byte ptr [edx],al
    L_00454e3f:
        inc dword ptr [ecx]
    L_00454e41:
        movzx eax,al
    L_00454e44:
        jmp short L_00454e52
    L_00454e46:
        movsx eax,al
    L_00454e49:
        push ecx
    L_00454e4a:
        push eax
    L_00454e4b:
        call asm_flsbuf_00454d11
    L_00454e50:
        pop ecx
    L_00454e51:
        pop ecx
    L_00454e52:
        cmp eax,0FFFFFFFFh
    L_00454e55:
        jne short L_00454e5a
    L_00454e57:
        or dword ptr [esi],eax
    L_00454e59:
        ret
    L_00454e5a:
        inc dword ptr [esi]
    L_00454e5c:
        ret
    }
}

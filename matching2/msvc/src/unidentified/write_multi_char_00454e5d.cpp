#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454E5D..0x00454E80: write_multi_char
// The CRT helper's ABI is not expressible as an ordinary MSVC C++ function:
// EAX carries the output-count pointer, while its other three arguments are
// on the stack. It also forwards that pointer to write_char through ESI.
extern "C" __declspec(naked) void __cdecl asm_write_multi_char_00454e5d() {
    __asm {
    L_00454e5d:
        push ebp
    L_00454e5e:
        mov ebp,esp
    L_00454e60:
        push esi
    L_00454e61:
        mov esi,eax
    L_00454e63:
        jmp short L_00454e78
    L_00454e65:
        mov ecx,dword ptr [ebp+10h]
    L_00454e68:
        mov al,byte ptr [ebp+8]
    L_00454e6b:
        dec dword ptr [ebp+0Ch]
    L_00454e6e:
        call asm_write_char_00454e2a
    L_00454e73:
        cmp dword ptr [esi],0FFFFFFFFh
    L_00454e76:
        je short L_00454e7e
    L_00454e78:
        cmp dword ptr [ebp+0Ch],0
    L_00454e7c:
        jg short L_00454e65
    L_00454e7e:
        pop esi
    L_00454e7f:
        pop ebp
    L_00454e80:
        ret
    }
}

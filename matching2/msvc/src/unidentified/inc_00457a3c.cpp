#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457A3C..0x00457A51: __inc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_inc_00457a3c() {
    __asm {
    L_00457a3c:
        dec dword ptr [edx+4]
    L_00457a3f:
        js short L_00457a4a
    L_00457a41:
        mov ecx,dword ptr [edx]
    L_00457a43:
        movzx eax,byte ptr [ecx]
    L_00457a46:
        inc ecx
    L_00457a47:
        mov dword ptr [edx],ecx
    L_00457a49:
        ret
    L_00457a4a:
        push edx
    L_00457a4b:
        call asm_filbuf_0045e123
    L_00457a50:
        pop ecx
    L_00457a51:
        ret
    }
}

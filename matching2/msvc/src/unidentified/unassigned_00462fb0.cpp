#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462FB0..0x00462FC0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462fb0() {
    __asm {
    L_00462fb0:
        xor eax,eax
    L_00462fb2:
        cmp byte ptr [ebp+0Ch],al
    L_00462fb5:
        setne al
    L_00462fb8:
        ret
    L_00462fb9:
        mov esp,dword ptr [ebp-18h]
    L_00462fbc:
        jmp asm_terminate_00455693
    }
}

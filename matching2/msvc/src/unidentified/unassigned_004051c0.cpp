#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004051C0..0x004051CD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004051c0() {
    __asm {
    L_004051c0:
        mov edx,dword ptr [ecx+390h]
    L_004051c6:
        xor eax,eax
    L_004051c8:
        test edx,edx
    L_004051ca:
        setne al
    L_004051cd:
        ret
    }
}

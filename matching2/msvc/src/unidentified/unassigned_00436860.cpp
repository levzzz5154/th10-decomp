#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436860..0x0043686D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436860() {
    __asm {
    L_00436860:
        mov edx,dword ptr [ecx+11Ch]
    L_00436866:
        xor eax,eax
    L_00436868:
        test edx,edx
    L_0043686a:
        setne al
    L_0043686d:
        ret
    }
}

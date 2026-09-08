#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C5F0..0x0040C5F9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c5f0() {
    __asm {
    L_0040c5f0:
        mov edx,dword ptr [ecx+4]
    L_0040c5f3:
        push eax
    L_0040c5f4:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0040c5f9:
        ret
    }
}

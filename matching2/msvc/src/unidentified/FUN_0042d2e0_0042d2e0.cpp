#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042D2E0..0x0042D2E6: FUN_0042d2e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042d2e0_0042d2e0() {
    __asm {
    L_0042d2e0:
        mov eax,ecx
    L_0042d2e2:
        jmp asm_FUN_0042cdf0_0042cdf0
    }
}

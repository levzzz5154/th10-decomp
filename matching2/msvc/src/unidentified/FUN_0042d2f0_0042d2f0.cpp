#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042D2F0..0x0042D2F6: FUN_0042d2f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042d2f0_0042d2f0() {
    __asm {
    L_0042d2f0:
        mov eax,ecx
    L_0042d2f2:
        jmp asm_FUN_0042d260_0042d260
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046241D..0x00462427: FUN_0046241d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046241d_0046241d() {
    __asm {
    L_0046241d:
        mov dword ptr [ecx],46CA00h
    L_00462423:
        jmp asm_FUN_00462371_00462371
    }
}

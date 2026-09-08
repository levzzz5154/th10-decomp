#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004458D0..0x004458D2: FUN_004458d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004458d0_004458d0() {
    __asm {
    L_004458d0:
        mov eax,ecx
    L_004458d2:
        ret
    }
}

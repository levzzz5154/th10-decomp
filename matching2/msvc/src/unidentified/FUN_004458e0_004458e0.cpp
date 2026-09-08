#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004458E0..0x004458E2: FUN_004458e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004458e0_004458e0() {
    __asm {
    L_004458e0:
        mov eax,ecx
    L_004458e2:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045598D..0x0045598F: FUN_0045598d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045598d_0045598d() {
    __asm {
    L_0045598d:
        xor eax,eax
    L_0045598f:
        ret
    }
}

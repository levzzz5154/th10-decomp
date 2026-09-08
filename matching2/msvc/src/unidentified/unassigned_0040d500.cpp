#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D500..0x0040D502: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040d500() {
    __asm {
    L_0040d500:
        xor eax,eax
    L_0040d502:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424EB0..0x00424EB2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424eb0() {
    __asm {
    L_00424eb0:
        xor eax,eax
    L_00424eb2:
        ret
    }
}

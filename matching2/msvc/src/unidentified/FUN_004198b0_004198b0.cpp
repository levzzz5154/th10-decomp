#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004198B0..0x004198B5: FUN_004198b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004198b0_004198b0() {
    __asm {
    L_004198b0:
        mov eax,1
    L_004198b5:
        ret
    }
}

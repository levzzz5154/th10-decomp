#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004200C0..0x004200C5: FUN_004200c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004200c0_004200c0() {
    __asm {
    L_004200c0:
        mov eax,1
    L_004200c5:
        ret
    }
}

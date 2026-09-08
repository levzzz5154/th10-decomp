#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004557F6..0x004557FB: FUN_004557f6
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004557f6_004557f6() {
    __asm {
    L_004557f6:
        mov eax,49931Ch
    L_004557fb:
        ret
    }
}

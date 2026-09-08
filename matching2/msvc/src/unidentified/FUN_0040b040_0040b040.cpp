#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B040..0x0040B045: FUN_0040b040
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b040_0040b040() {
    __asm {
    L_0040b040:
        mov eax,1
    L_0040b045:
        ret
    }
}

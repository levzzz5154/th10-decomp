#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B050..0x0040B055: FUN_0040b050
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b050_0040b050() {
    __asm {
    L_0040b050:
        mov eax,1
    L_0040b055:
        ret
    }
}

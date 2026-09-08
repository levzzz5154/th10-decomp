#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B060..0x0040B065: FUN_0040b060
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b060_0040b060() {
    __asm {
    L_0040b060:
        mov eax,1
    L_0040b065:
        ret
    }
}

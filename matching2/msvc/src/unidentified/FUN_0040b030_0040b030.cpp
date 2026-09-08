#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B030..0x0040B035: FUN_0040b030
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b030_0040b030() {
    __asm {
    L_0040b030:
        mov eax,1
    L_0040b035:
        ret
    }
}

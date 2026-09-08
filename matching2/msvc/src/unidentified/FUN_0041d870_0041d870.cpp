#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041D870..0x0041D872: FUN_0041d870
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041d870_0041d870() {
    __asm {
    L_0041d870:
        xor eax,eax
    L_0041d872:
        ret
    }
}

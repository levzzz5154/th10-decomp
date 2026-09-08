#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C690..0x0040C694: FUN_0040c690
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c690_0040c690() {
    __asm {
    L_0040c690:
        xor eax,eax
    L_0040c692:
        ret 4
    }
}

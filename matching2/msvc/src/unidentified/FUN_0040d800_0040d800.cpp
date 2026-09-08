#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D800..0x0040D805: FUN_0040d800
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d800_0040d800() {
    __asm {
    L_0040d800:
        mov eax,1
    L_0040d805:
        ret
    }
}

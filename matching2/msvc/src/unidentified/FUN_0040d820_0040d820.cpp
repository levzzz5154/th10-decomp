#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D820..0x0040D825: FUN_0040d820
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d820_0040d820() {
    __asm {
    L_0040d820:
        mov eax,1
    L_0040d825:
        ret
    }
}

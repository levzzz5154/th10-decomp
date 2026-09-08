#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BF90..0x0043BF92: FUN_0043bf90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043bf90_0043bf90() {
    __asm {
    L_0043bf90:
        mov eax,ecx
    L_0043bf92:
        ret
    }
}

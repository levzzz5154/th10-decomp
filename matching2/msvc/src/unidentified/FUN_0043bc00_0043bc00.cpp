#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BC00..0x0043BC03: FUN_0043bc00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043bc00_0043bc00() {
    __asm {
    L_0043bc00:
        mov dword ptr [eax+0Ch],ecx
    L_0043bc03:
        ret
    }
}

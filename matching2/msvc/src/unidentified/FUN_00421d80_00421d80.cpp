#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421D80..0x00421D87: FUN_00421d80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421d80_00421d80() {
    __asm {
    L_00421d80:
        mov byte ptr [eax+3ADA6Ah],0FFh
    L_00421d87:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421D90..0x00421D97: FUN_00421d90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421d90_00421d90() {
    __asm {
    L_00421d90:
        mov byte ptr [eax+3ADA6Eh],0FFh
    L_00421d97:
        ret
    }
}

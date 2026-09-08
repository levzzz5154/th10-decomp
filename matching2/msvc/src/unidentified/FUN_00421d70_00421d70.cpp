#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421D70..0x00421D73: FUN_00421d70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421d70_00421d70() {
    __asm {
    L_00421d70:
        mov word ptr [eax],cx
    L_00421d73:
        ret
    }
}

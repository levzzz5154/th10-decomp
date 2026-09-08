#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418B60..0x00418B64: FUN_00418b60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418b60_00418b60() {
    __asm {
    L_00418b60:
        mov word ptr [eax+8],cx
    L_00418b64:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401CB0..0x00401CB6: FUN_00401cb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401cb0_00401cb0() {
    __asm {
    L_00401cb0:
        mov byte ptr [eax+2FFh],cl
    L_00401cb6:
        ret
    }
}

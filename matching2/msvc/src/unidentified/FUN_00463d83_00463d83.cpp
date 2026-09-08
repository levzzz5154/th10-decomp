#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463D83..0x00463D89: FUN_00463d83
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00463d83_00463d83() {
    __asm {
    L_00463d83:
        and byte ptr [ebp-2C8h],0FEh
    }
}

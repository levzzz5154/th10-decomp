#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405850..0x00405855: FUN_00405850
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405850_00405850() {
    __asm {
    L_00405850:
        mov eax,1
    L_00405855:
        ret
    }
}

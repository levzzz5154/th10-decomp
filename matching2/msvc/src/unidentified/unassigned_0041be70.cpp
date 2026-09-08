#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BE70..0x0041BE77: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041be70() {
    __asm {
    L_0041be70:
        movsx eax,word ptr [eax+384h]
    L_0041be77:
        ret
    }
}

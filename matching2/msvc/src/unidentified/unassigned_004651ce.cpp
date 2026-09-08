#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004651CE..0x004651D7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004651ce() {
    __asm {
    L_004651ce:
        mov eax,471258h
    L_004651d3:
        jmp asm_CxxFrameHandler_0046276d
    }
}

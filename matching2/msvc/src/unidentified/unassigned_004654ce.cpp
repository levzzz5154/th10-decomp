#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004654CE..0x004654D7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004654ce() {
    __asm {
    L_004654ce:
        mov eax,471564h
    L_004654d3:
        jmp asm_CxxFrameHandler_0046276d
    }
}

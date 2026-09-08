#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004657E9..0x004657F2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004657e9() {
    __asm {
    L_004657e9:
        mov eax,4717C4h
    L_004657ee:
        jmp asm_CxxFrameHandler_0046276d
    }
}

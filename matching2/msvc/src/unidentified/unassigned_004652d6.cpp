#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004652D6..0x004652DF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004652d6() {
    __asm {
    L_004652d6:
        mov eax,471324h
    L_004652db:
        jmp asm_CxxFrameHandler_0046276d
    }
}

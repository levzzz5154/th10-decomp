#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004655AB..0x004655B4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004655ab() {
    __asm {
    L_004655ab:
        mov eax,471620h
    L_004655b0:
        jmp asm_CxxFrameHandler_0046276d
    }
}

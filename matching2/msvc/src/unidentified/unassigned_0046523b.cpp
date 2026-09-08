#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046523B..0x00465244: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046523b() {
    __asm {
    L_0046523b:
        mov eax,4712B0h
    L_00465240:
        jmp asm_CxxFrameHandler_0046276d
    }
}

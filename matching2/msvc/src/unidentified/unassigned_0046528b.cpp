#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046528B..0x00465294: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046528b() {
    __asm {
    L_0046528b:
        mov eax,4712F8h
    L_00465290:
        jmp asm_CxxFrameHandler_0046276d
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465225..0x0046522E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465225() {
    __asm {
    L_00465225:
        mov eax,47128Ch
    L_0046522a:
        jmp asm_CxxFrameHandler_0046276d
    }
}

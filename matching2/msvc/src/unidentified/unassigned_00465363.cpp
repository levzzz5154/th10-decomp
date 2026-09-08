#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465363..0x0046536C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465363() {
    __asm {
    L_00465363:
        mov eax,4713C4h
    L_00465368:
        jmp asm_CxxFrameHandler_0046276d
    }
}

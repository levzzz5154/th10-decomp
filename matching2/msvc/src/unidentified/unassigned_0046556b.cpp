#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046556B..0x00465574: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046556b() {
    __asm {
    L_0046556b:
        mov eax,4715D8h
    L_00465570:
        jmp asm_CxxFrameHandler_0046276d
    }
}

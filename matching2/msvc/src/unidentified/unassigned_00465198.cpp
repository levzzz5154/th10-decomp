#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465198..0x004651A1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465198() {
    __asm {
    L_00465198:
        mov eax,47113Ch
    L_0046519d:
        jmp asm_CxxFrameHandler_0046276d
    }
}

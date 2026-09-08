#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046541C..0x00465425: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046541c() {
    __asm {
    L_0046541c:
        mov eax,4714FCh
    L_00465421:
        jmp asm_CxxFrameHandler_0046276d
    }
}

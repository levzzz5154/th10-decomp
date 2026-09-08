#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046564B..0x00465654: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046564b() {
    __asm {
    L_0046564b:
        mov eax,47169Ch
    L_00465650:
        jmp asm_CxxFrameHandler_0046276d
    }
}

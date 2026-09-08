#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046582B..0x00465834: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046582b() {
    __asm {
    L_0046582b:
        mov eax,47180Ch
    L_00465830:
        jmp asm_CxxFrameHandler_0046276d
    }
}

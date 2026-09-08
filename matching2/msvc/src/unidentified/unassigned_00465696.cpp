#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465696..0x0046569F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465696() {
    __asm {
    L_00465696:
        mov eax,4716ECh
    L_0046569b:
        jmp asm_CxxFrameHandler_0046276d
    }
}

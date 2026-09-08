#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046558B..0x00465594: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046558b() {
    __asm {
    L_0046558b:
        mov eax,4715FCh
    L_00465590:
        jmp asm_CxxFrameHandler_0046276d
    }
}

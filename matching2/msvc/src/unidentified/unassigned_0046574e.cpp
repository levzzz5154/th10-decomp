#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046574E..0x00465757: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046574e() {
    __asm {
    L_0046574e:
        mov eax,471740h
    L_00465753:
        jmp asm_CxxFrameHandler_0046276d
    }
}

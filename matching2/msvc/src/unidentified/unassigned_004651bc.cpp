#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004651BC..0x004651C5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004651bc() {
    __asm {
    L_004651bc:
        mov eax,4711F8h
    L_004651c1:
        jmp asm_CxxFrameHandler_0046276d
    }
}

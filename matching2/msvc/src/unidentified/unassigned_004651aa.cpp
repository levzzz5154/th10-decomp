#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004651AA..0x004651B3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004651aa() {
    __asm {
    L_004651aa:
        mov eax,4711D4h
    L_004651af:
        jmp asm_CxxFrameHandler_0046276d
    }
}

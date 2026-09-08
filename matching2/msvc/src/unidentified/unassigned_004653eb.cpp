#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004653EB..0x004653F4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004653eb() {
    __asm {
    L_004653eb:
        mov eax,4714D8h
    L_004653f0:
        jmp asm_CxxFrameHandler_0046276d
    }
}

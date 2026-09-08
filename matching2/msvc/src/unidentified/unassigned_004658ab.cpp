#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004658AB..0x004658B4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004658ab() {
    __asm {
    L_004658ab:
        mov eax,47189Ch
    L_004658b0:
        jmp asm_CxxFrameHandler_0046276d
    }
}

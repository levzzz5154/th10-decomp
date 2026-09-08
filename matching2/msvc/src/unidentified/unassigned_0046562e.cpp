#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046562E..0x00465637: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046562e() {
    __asm {
    L_0046562e:
        mov eax,471678h
    L_00465633:
        jmp asm_CxxFrameHandler_0046276d
    }
}

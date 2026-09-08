#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004654B5..0x004654BE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004654b5() {
    __asm {
    L_004654b5:
        mov eax,471540h
    L_004654ba:
        jmp asm_CxxFrameHandler_0046276d
    }
}

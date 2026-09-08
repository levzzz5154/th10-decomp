#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004245D0..0x004245E5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004245d0() {
    __asm {
    L_004245d0:
        mov eax,dword ptr [eax+8]
    L_004245d3:
        test eax,eax
    L_004245d5:
        je short L_004245e3
    L_004245d7:
        test byte ptr [eax+4],2
    L_004245db:
        je short L_004245e3
    L_004245dd:
        mov eax,1
    L_004245e2:
        ret
    L_004245e3:
        xor eax,eax
    L_004245e5:
        ret
    }
}

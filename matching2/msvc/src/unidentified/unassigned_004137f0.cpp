#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004137F0..0x004137FE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004137f0() {
    __asm {
    L_004137f0:
        mov eax,dword ptr [eax+2480h]
    L_004137f6:
        shr eax,4
    L_004137f9:
        not eax
    L_004137fb:
        and eax,1
    L_004137fe:
        ret
    }
}

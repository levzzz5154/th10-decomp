#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004245B0..0x004245BF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004245b0() {
    __asm {
    L_004245b0:
        mov edx,dword ptr [ecx]
    L_004245b2:
        mov ecx,dword ptr [esp+4]
    L_004245b6:
        xor eax,eax
    L_004245b8:
        cmp edx,ecx
    L_004245ba:
        sete al
    L_004245bd:
        ret 4
    }
}

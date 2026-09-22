#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004245B0..0x004245BF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2801): closest_byte_count=13/16; first_diff=0x004245B1
// (expected 8b 11, readable actual 8b 09); residual_class=register
// allocation tie-break (retail loads field to EDX and argument to ECX);
// variants_tested=const bool member Equals(int), reversed equality operands
// (extent 18), unsigned-int member (same 3-byte mismatch); next_lever=
// native-LTCG caller context or manifest promotion.
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

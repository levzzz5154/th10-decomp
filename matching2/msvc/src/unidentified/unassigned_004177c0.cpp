#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004177C0..0x004177D8: unassigned code fragment
// BLOCKED (M2702): closest_byte_count=25; first_diff=0x004177D2;
// residual_class=compiler_shape: readable member candidates preserve the
// animation receiver in ECX, while retail reloads the second slot through EAX
// (expected bytes 41 0C; candidates emitted 49 0C), changing the exact tail.
// variants_tested=7 source spellings plus the historical plain/native-LTCG
// matrix; none reproduced the retail reload and no readable candidate matched.
// next_lever=derive a shared two-slot native-LTCG cluster that constrains the
// EAX reload while retaining the existing ECX receiver entry.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004177c0() {
    __asm {
    L_004177c0:
        mov eax,dword ptr [ecx+8]
    L_004177c3:
        push esi
    L_004177c4:
        mov esi,dword ptr [eax+4]
    L_004177c7:
        mov edx,2
    L_004177cc:
        or esi,edx
    L_004177ce:
        mov dword ptr [eax+4],esi
    L_004177d1:
        mov eax,dword ptr [ecx+0Ch]
    L_004177d4:
        or dword ptr [eax+4],edx
    L_004177d7:
        pop esi
    L_004177d8:
        ret
    }
}

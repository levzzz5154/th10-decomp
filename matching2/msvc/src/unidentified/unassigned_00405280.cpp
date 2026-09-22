#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405280..0x00405290: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2702): closest_byte_count=14/17; first_diff=0x00405281;
// residual_class=private ABI/register allocation: the exact body consumes
// receiver ECX and argument [ESP+4], but a readable MSVC member emits the
// receiver field into ECX rather than the retail EDX live range.
// variants_tested=signed int-return and bool-return member comparisons,
// including a volatile field and an explicit local; all were nonexact.
// next_lever=native-LTCG context to anchor the retail EDX/ECX allocation, or
// manifest semantic migration for a cluster-owned method.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405280() {
    __asm {
    L_00405280:
        mov edx,dword ptr [ecx+4]
    L_00405283:
        mov ecx,dword ptr [esp+4]
    L_00405287:
        xor eax,eax
    L_00405289:
        cmp edx,ecx
    L_0040528b:
        setle al
    L_0040528e:
        ret 4
    }
}

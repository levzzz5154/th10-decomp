#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418A50..0x00418A60: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2702): closest_byte_count=14/17; first_diff=0x00418A51;
// residual_class=private ABI/register allocation: retail keeps the +0x04
// receiver field in EDX before loading [ESP+4] into ECX, while readable
// member equality compiles the field load into ECX (or spills through ESI).
// variants_tested=bool and int equality members, swapped operand order,
// explicit local, volatile field, and xor-based equality; none were exact.
// next_lever=native-LTCG context to anchor the retail EDX/ECX allocation, or
// manifest semantic migration for a cluster-owned method.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418a50() {
    __asm {
    L_00418a50:
        mov edx,dword ptr [ecx+4]
    L_00418a53:
        mov ecx,dword ptr [esp+4]
    L_00418a57:
        xor eax,eax
    L_00418a59:
        cmp edx,ecx
    L_00418a5b:
        sete al
    L_00418a5e:
        ret 4
    }
}

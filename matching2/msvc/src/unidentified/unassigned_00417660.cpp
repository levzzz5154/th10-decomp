// BLOCKED (M2803): closest_byte_count=13/16; first_diff=0x00417661;
// residual_class=private ABI/register allocation: the retail fragment uses
// ECX as the implicit receiver, loads its first word into EDX, then loads the
// stack operand into ECX before the branchless SETNE tail.  A readable MSVC
// member preserves the ABI and extent but allocates the field/argument as
// ECX/EDX instead.
// variants_tested=exact retail naked wrapper; readable bool and int members;
// reversed comparison order; explicit locals; volatile field; pointer/cast
// forms; and branch-shaped returns.  The direct member remained 3 bytes
// different, while reversed order expanded to 18 bytes.
// next_lever=native-LTCG context or semantic manifest migration that anchors
// the retail EDX/ECX live ranges; retain the exact wrapper in M2803.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417660..0x0041766F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417660() {
    __asm {
    L_00417660:
        mov edx,dword ptr [ecx]
    L_00417662:
        mov ecx,dword ptr [esp+4]
    L_00417666:
        xor eax,eax
    L_00417668:
        cmp edx,ecx
    L_0041766A:
        setne al
    L_0041766D:
        ret 4
    }
}

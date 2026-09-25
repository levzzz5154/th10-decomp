// BLOCKED (M2701): closest_byte_count=1; first_diff=0x00413051;
// residual_class=private ABI: retail receives the object in ECX and the
// comparison operand on the stack, but the fixed C symbol cannot express that
// compiler-private receiver convention.
// variants_tested=extern-C cdecl readable body (19-byte extent, first diff at
// byte 1); extern-C stdcall readable body (21-byte extent, first diff at byte
// 1); both were compiled with the project MSVC 13.10 profile and rejected.
// next_lever=native-LTCG cluster with a real C++ member-style body and a
// context that establishes ECX as the private receiver; manifest symbol
// ownership must also be migrated from _asm_unassigned_00413050.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413050..0x00413060: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413050() {
    __asm {
    L_00413050:
        mov edx,dword ptr [ecx+4]
    L_00413053:
        mov ecx,dword ptr [esp+4]
    L_00413057:
        xor eax,eax
    L_00413059:
        cmp edx,ecx
    L_0041305b:
        setl al
    L_0041305e:
        ret 4
    }
}

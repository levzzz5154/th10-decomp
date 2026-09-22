// BLOCKED (M2701): closest_byte_count=1; first_diff=0x00405191;
// residual_class=private ABI: retail receives its object in EAX and one
// argument on the stack, while the fixed C symbol cannot name that receiver.
// variants_tested=extern-C stdcall readable body (21-byte extent, first diff
// at byte 1), compiled with the project MSVC 13.10 profile and rejected.
// The cdecl form is not a valid RET 4 declaration for this target.
// next_lever=native-LTCG cluster with a context that pins the object in EAX
// while retaining the stack argument and RET 4 convention; manifest symbol
// ownership must migrate from _asm_unassigned_00405190.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405190..0x004051A0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405190() {
    __asm {
    L_00405190:
        mov ecx,dword ptr [esp+4]
    L_00405194:
        mov dword ptr [eax+3Ch],ecx
    L_00405197:
        or dword ptr [eax+35Ch],8
    L_0040519e:
        ret 4
    }
}

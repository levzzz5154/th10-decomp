// BLOCKED (M2704): closest_byte_count=0; first_diff=0x00405170;
// residual_class=abi: the native-LTCG member candidate emitted the two field
// updates exactly but promoted the stack value into ECX and ended with RET,
// while retail loads [esp+4] and uses RET 4.  A direct thiscall candidate
// also retained the argument in EDX and could not select the retail EAX
// receiver/stack argument tuple.
// variants_tested=direct readable member, __stdcall member, and volatile
// __stdcall member under a synthetic array-walking native-LTCG caller;
// closest body was 11 bytes (retail is 17 bytes).
// next_lever=retain an external/public caller boundary that preserves the
// callee-cleanup stack argument while separately forcing the private EAX receiver.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405170..0x00405180: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405170() {
    __asm {
    L_00405170:
        mov ecx,dword ptr [esp+4]
    L_00405174:
        mov dword ptr [eax+40h],ecx
    L_00405177:
        or dword ptr [eax+35Ch],8
    L_0040517e:
        ret 4
    }
}

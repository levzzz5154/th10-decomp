// BLOCKED (M2704): closest_byte_count=0; first_diff=0x0042BA70;
// residual_class=abi: the native-LTCG member candidate emitted both field
// updates exactly but selected a promoted ECX value and RET, not retail's
// [esp+4] load and RET 4.
// variants_tested=direct and __stdcall member candidates under a synthetic
// native-LTCG array caller; closest body was 11 bytes (retail is 17 bytes).
// next_lever=preserve a public callee-cleanup boundary while separately
// forcing the private EAX receiver.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BA70..0x0042BA80: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ba70() {
    __asm {
    L_0042ba70:
        mov ecx,dword ptr [esp+4]
    L_0042ba74:
        mov dword ptr [eax+4Ch],ecx
    L_0042ba77:
        or dword ptr [eax+35Ch],8
    L_0042ba7e:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DBD0..0x0044DBED: unassigned code fragment
// BLOCKED (M2702): closest_byte_count=30; first_diff=unmeasured;
// residual_class=abi: retail enters with the archive-cursor receiver in ESI,
// conditionally calls an indirect callback, and writes the sentinel back to
// the same object; an ordinary declaration cannot preserve this split ABI.
// variants_tested=exact retail overlay only; no readable candidate was measured;
// next_lever=compile the cursor close/reset member in a native-LTCG ESI-receiver
// cluster alongside ArchiveCursor_Open and ArchiveCursor_Read.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044dbd0() {
    __asm {
    L_0044dbd0:
        cmp dword ptr [esi+78h],1
    L_0044dbd4:
        jne short L_0044dbed
    L_0044dbd6:
        mov eax,dword ptr [esi+8Ch]
    L_0044dbdc:
        push eax
    L_0044dbdd:
        call dword ptr [data_004660cc]
    L_0044dbe3:
        mov dword ptr [esi+8Ch],0FFFFFFFFh
    L_0044dbed:
        ret
    }
}

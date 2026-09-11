#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/util/heap.hpp"

// 0x00418150..0x00418161: ?Heap_DestroyOwned@@
// Naked body preserves the retail register/stack ABI.

// 0x0042CDB0..0x0042CDC1: ?Heap_DestroyOwnedSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Heap_DestroyOwnedSecondary_0042cdb0() {
    __asm {
    L_0042cdb0:
        test esi,esi
    L_0042cdb2:
        je short L_0042cdc1
    L_0042cdb4:
        push esi
    L_0042cdb5:
        call asm_FUN_0042cb60_0042cb60
    L_0042cdba:
        push esi
    L_0042cdbb:
        call asm_free_004524a1
    L_0042cdc0:
        pop ecx
    L_0042cdc1:
        ret
    }
}

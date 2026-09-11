#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/util/heap.hpp"

// 0x00418150..0x00418161: ?Heap_DestroyOwned@@
// Naked body preserves the retail register/stack ABI.

// 0x00418150..0x00418161: ?Heap_DestroyOwned@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Heap_DestroyOwned_00418150() {
    __asm {
    L_00418150:
        test esi,esi
    L_00418152:
        je short L_00418161
    L_00418154:
        push esi
    L_00418155:
        call asm_FUN_00417c80_00417c80
    L_0041815a:
        push esi
    L_0041815b:
        call asm_free_004524a1
    L_00418160:
        pop ecx
    L_00418161:
        ret
    }
}

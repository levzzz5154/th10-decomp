#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00406140..0x00406151: FUN_00406140
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00406140_00406140() {
    __asm {
    L_00406140:
        test esi,esi
    L_00406142:
        je short L_00406151
    L_00406144:
        push esi
    L_00406145:
        call asm_ItemManager_DestroyRetail_00405f70
    L_0040614a:
        push esi
    L_0040614b:
        call asm_free_004524a1
    L_00406150:
        pop ecx
    L_00406151:
        ret
    }
}

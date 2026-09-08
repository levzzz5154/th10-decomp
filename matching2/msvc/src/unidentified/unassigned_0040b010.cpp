#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B010..0x0040B021: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b010() {
    __asm {
    L_0040b010:
        test esi,esi
    L_0040b012:
        je short L_0040b021
    L_0040b014:
        push esi
    L_0040b015:
        call asm_BulletManager_Release_0040af00
    L_0040b01a:
        push esi
    L_0040b01b:
        call asm_free_004524a1
    L_0040b020:
        pop ecx
    L_0040b021:
        ret
    }
}

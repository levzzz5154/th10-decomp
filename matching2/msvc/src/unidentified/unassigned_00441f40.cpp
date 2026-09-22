// BLOCKED (M2803): closest_byte_count=16/16; first_diff=relocation +0x9;
// residual_class=intrinsic-helper relocation: Ghidra identifies the retail
// call at 0x00463BBA as the fmod dispatch helper (its table at 0x00477010
// begins with "fmod"), while readable fmodf emits the same bytes with a
// __CIfmod relocation that has no manifest binding to _asm_FUN_00463bba.
// variants_tested=exact retail naked wrapper; readable atan2f (13-byte
// fpatan body); typed helper call (21-byte stack-call body); and readable
// fmodf (exact 16-byte body, unresolved relocation).
// next_lever=declare a legal COFF alias/binding from __CIfmod to the existing
// retail helper or migrate the region to a semantic manifest with that alias;
// retain the exact wrapper in M2803.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441F40..0x00441F4F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441f40() {
    __asm {
    L_00441f40:
        fld dword ptr [esp+4]
    L_00441f44:
        fld dword ptr [esp+8]
    L_00441f48:
        call asm_FUN_00463bba_00463bba
    L_00441f4d:
        ret 8
    }
}

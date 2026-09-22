#include <string.h>
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405D00..0x00405DD6: FUN_00405d00
// Naked body preserves the retail register/stack ABI.

// BLOCKED (D3501): closest_byte_count=43/43; first_diff=none (retail
// assembly baseline only; no readable candidate retained);
// residual_class=__usercall EAX receiver with no stack parameter, virtual
// release through [slot]+8, and compiler loop/register shape requiring the
// caller's native context.
// variants_tested=live Ghidra complete-function analysis with callers/callees,
// xrefs, disassembly, and variables; MSVC 13.10 scoped probe baseline exact;
// no readable candidate retained. next_lever=native-LTCG EAX-ABI cluster with
// real 0x004391F0/GameMain callers and the 32-slot owner layout.

// 0x00438A30..0x00438A5A: DestroyEntityList
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DestroyEntityList_00438a30() {
    __asm {
    L_00438a30:
        push esi
    L_00438a31:
        mov esi,eax
    L_00438a33:
        push edi
    L_00438a34:
        add esi,3AD4E0h
    L_00438a3a:
        mov edi,20h
    L_00438a3f:
        nop
    L_00438a40:
        mov eax,dword ptr [esi]
    L_00438a42:
        test eax,eax
    L_00438a44:
        je short L_00438a52
    L_00438a46:
        mov ecx,dword ptr [eax]
    L_00438a48:
        push eax
    L_00438a49:
        call dword ptr [ecx+8]
    L_00438a4c:
        mov dword ptr [esi],0
    L_00438a52:
        add esi,4
    L_00438a55:
        dec edi
    L_00438a56:
        jne short L_00438a40
    L_00438a58:
        pop edi
    L_00438a59:
        pop esi
    L_00438a5a:
        ret
    }
}

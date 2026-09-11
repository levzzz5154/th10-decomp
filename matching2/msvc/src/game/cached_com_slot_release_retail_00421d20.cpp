#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421C50..0x00421C68: SlotLockTable_LeaveRetail
// Naked body preserves the retail register/stack ABI.

// 0x00421D20..0x00421D34: CachedComSlot_ReleaseRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CachedComSlot_ReleaseRetail_00421d20() {
    __asm {
    L_00421d20:
        mov eax,dword ptr [esi+0Ch]
    L_00421d23:
        test eax,eax
    L_00421d25:
        je short L_00421d34
    L_00421d27:
        mov ecx,dword ptr [eax]
    L_00421d29:
        push eax
    L_00421d2a:
        call dword ptr [ecx+8]
    L_00421d2d:
        mov dword ptr [esi+0Ch],0
    L_00421d34:
        ret
    }
}

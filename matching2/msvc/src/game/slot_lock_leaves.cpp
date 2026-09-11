#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421C50..0x00421C68: SlotLockTable_LeaveRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_SlotLockTable_LeaveRetail_00421c50() {
    __asm {
    L_00421c50:
        lea eax,[esi+esi*2]
    L_00421c53:
        lea ecx,[edi+eax*8+64Ch]
    L_00421c5a:
        push ecx
    L_00421c5b:
        call dword ptr [data_004660b4]
    L_00421c61:
        dec byte ptr [esi+edi+6F4h]
    L_00421c68:
        ret
    }
}


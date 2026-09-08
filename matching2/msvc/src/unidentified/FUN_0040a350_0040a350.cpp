#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A350..0x0040A3B4: FUN_0040a350
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040a350_0040a350() {
    __asm {
    L_0040a350:
        push edi
    L_0040a351:
        call asm_Recovery_CreateLargeResourceState_00425020
    L_0040a356:
        call asm_FUN_00406060_00406060
    L_0040a35b:
        call asm_Recovery_CreateFixedState_004056b0
    L_0040a360:
        call asm_FUN_0041aed0_0041aed0
    L_0040a365:
        call asm_Recovery_CreateHugeResourceState_0042b660
    L_0040a36a:
        mov eax,dword ptr [esi+114h]
    L_0040a370:
        mov ecx,dword ptr [esi+34h]
    L_0040a373:
        mov edx,dword ptr [ecx+eax*4]
    L_0040a376:
        push edx
    L_0040a377:
        call asm_EnemyManager_CreateRetail_0040d6b0
    L_0040a37c:
        call asm_ItemManager_CreateRetail_00414830
    L_0040a381:
        mov eax,dword ptr [data_00477704]
    L_0040a386:
        mov ecx,dword ptr [eax+54h]
    L_0040a389:
        mov edx,dword ptr [ecx+8]
    L_0040a38c:
        lea edi,[esi+1ECh]
    L_0040a392:
        push 1
    L_0040a394:
        mov eax,edi
    L_0040a396:
        mov dword ptr [esi+1F4h],edx
    L_0040a39c:
        call asm_MenuCursor_Advance_0044bea0
    L_0040a3a1:
        push 0FFFFFFFFh
    L_0040a3a3:
        mov eax,edi
    L_0040a3a5:
        call asm_MenuCursor_Advance_0044bea0
    L_0040a3aa:
        mov dword ptr [esi+30h],1
    L_0040a3b1:
        xor eax,eax
    L_0040a3b3:
        pop edi
    L_0040a3b4:
        ret
    }
}

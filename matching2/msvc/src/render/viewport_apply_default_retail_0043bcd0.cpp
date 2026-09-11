#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421480..0x0042159E: Camera_ApplyRetail
// Naked body preserves the retail register/stack ABI.

// 0x0043BCD0..0x0043BD3B: Viewport_ApplyDefaultRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Viewport_ApplyDefaultRetail_0043bcd0() {
    __asm {
    L_0043bcd0:
        push esi
    L_0043bcd1:
        mov esi,dword ptr [data_00491c10]
    L_0043bcd7:
        test esi,esi
    L_0043bcd9:
        je short L_0043bce0
    L_0043bcdb:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0043bce0:
        mov eax,dword ptr [data_00491c30]
    L_0043bce5:
        push 491CF4h
    L_0043bcea:
        mov dword ptr [data_00491cf4],0
    L_0043bcf4:
        mov dword ptr [data_00491cf8],0
    L_0043bcfe:
        mov dword ptr [data_00491cfc],280h
    L_0043bd08:
        mov dword ptr [data_00491d00],1E0h
    L_0043bd12:
        mov dword ptr [data_00491d04],0
    L_0043bd1c:
        mov dword ptr [data_00491d08],3F800000h
    L_0043bd26:
        mov ecx,dword ptr [eax]
    L_0043bd28:
        push eax
    L_0043bd29:
        call dword ptr [ecx+0BCh]
    L_0043bd2f:
        mov esi,dword ptr [esp+8]
    L_0043bd33:
        call asm_Recovery_ResetDeviceStreams_0043bc40
    L_0043bd38:
        pop esi
    L_0043bd39:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449470..0x00449498: AnimationManager_SetStopFrameFromHandleRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetStopFrameFromHandleRetail_00449470() {
    __asm {
    L_00449470:
        mov eax,dword ptr [eax]
    L_00449472:
        mov edx,dword ptr [data_00491c10]
    L_00449478:
        push eax
    L_00449479:
        call asm_AnimationManager_Find_004491c0
    L_0044947e:
        test eax,eax
    L_00449480:
        TH10_REL8(0x74, 0x00449480, VA_asm_target_004494b0)
    L_00449482:
        mov ecx,dword ptr [eax+18h]
    L_00449485:
        test ecx,ecx
    L_00449487:
        mov word ptr [eax+304h],si
    L_0044948e:
        TH10_REL8(0x75, 0x0044948e, VA_asm_target_004494b0)
    L_00449490:
        mov eax,dword ptr [eax+14h]
    L_00449493:
        test eax,eax
    L_00449495:
        TH10_REL8(0x74, 0x00449495, VA_asm_target_004494b0)
    L_00449497:
        TH10_REL8(0xeb, 0x00449497, VA_asm_AnimationManager_SetStopFrameFromHandleRetail_part_004494a0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_004494a0:
        mov ecx,dword ptr [eax]
    L_004494a2:
        mov word ptr [ecx+304h],si
    L_004494a9:
        mov eax,dword ptr [eax+4]
    L_004494ac:
        test eax,eax
    L_004494ae:
        jne short L_004494a0
    L_004494b0:
        ret
    }
}

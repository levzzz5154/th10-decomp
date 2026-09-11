#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449590..0x004495D2: ?AnimationManager_SetFlagBit1@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetFlagBit1_00449590() {
    __asm {
    L_00449590:
        mov ecx,dword ptr [eax]
    L_00449592:
        mov edx,dword ptr [data_00491c10]
    L_00449598:
        push ecx
    L_00449599:
        call asm_AnimationManager_Find_004491c0
    L_0044959e:
        test eax,eax
    L_004495a0:
        je short L_004495d2
    L_004495a2:
        mov ecx,dword ptr [eax+35Ch]
    L_004495a8:
        mov edx,2
    L_004495ad:
        or ecx,edx
    L_004495af:
        mov dword ptr [eax+35Ch],ecx
    L_004495b5:
        mov ecx,dword ptr [eax+18h]
    L_004495b8:
        test ecx,ecx
    L_004495ba:
        jne short L_004495d2
    L_004495bc:
        mov eax,dword ptr [eax+14h]
    L_004495bf:
        test eax,eax
    L_004495c1:
        je short L_004495d2
    L_004495c3:
        mov ecx,dword ptr [eax]
    L_004495c5:
        or dword ptr [ecx+35Ch],edx
    L_004495cb:
        mov eax,dword ptr [eax+4]
    L_004495ce:
        test eax,eax
    L_004495d0:
        jne short L_004495c3
    L_004495d2:
        ret
    }
}

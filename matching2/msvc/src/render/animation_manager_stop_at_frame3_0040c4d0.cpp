#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x0040C4D0..0x0040C510: ?AnimationManager_StopAtFrame3@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_StopAtFrame3_0040c4d0() {
    __asm {
    L_0040c4d0:
        mov eax,dword ptr [eax]
    L_0040c4d2:
        mov edx,dword ptr [data_00491c10]
    L_0040c4d8:
        push eax
    L_0040c4d9:
        call asm_AnimationManager_Find_004491c0
    L_0040c4de:
        test eax,eax
    L_0040c4e0:
        je short L_0040c510
    L_0040c4e2:
        mov edx,dword ptr [eax+18h]
    L_0040c4e5:
        test edx,edx
    L_0040c4e7:
        mov ecx,3
    L_0040c4ec:
        mov word ptr [eax+304h],cx
    L_0040c4f3:
        jne short L_0040c510
    L_0040c4f5:
        mov eax,dword ptr [eax+14h]
    L_0040c4f8:
        test eax,eax
    L_0040c4fa:
        je short L_0040c510
    L_0040c4fc:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040c500:
        mov edx,dword ptr [eax]
    L_0040c502:
        mov word ptr [edx+304h],cx
    L_0040c509:
        mov eax,dword ptr [eax+4]
    L_0040c50c:
        test eax,eax
    L_0040c50e:
        jne short L_0040c500
    L_0040c510:
        ret
    }
}

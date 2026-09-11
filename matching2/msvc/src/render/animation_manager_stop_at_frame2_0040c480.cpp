#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_StopAtFrame2_0040c480() {
    __asm {
    L_0040c480:
        mov eax,dword ptr [eax]
    L_0040c482:
        mov edx,dword ptr [data_00491c10]
    L_0040c488:
        push eax
    L_0040c489:
        call asm_AnimationManager_Find_004491c0
    L_0040c48e:
        test eax,eax
    L_0040c490:
        je short L_0040c4c0
    L_0040c492:
        mov edx,dword ptr [eax+18h]
    L_0040c495:
        test edx,edx
    L_0040c497:
        mov ecx,2
    L_0040c49c:
        mov word ptr [eax+304h],cx
    L_0040c4a3:
        jne short L_0040c4c0
    L_0040c4a5:
        mov eax,dword ptr [eax+14h]
    L_0040c4a8:
        test eax,eax
    L_0040c4aa:
        je short L_0040c4c0
    L_0040c4ac:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040c4b0:
        mov edx,dword ptr [eax]
    L_0040c4b2:
        mov word ptr [edx+304h],cx
    L_0040c4b9:
        mov eax,dword ptr [eax+4]
    L_0040c4bc:
        test eax,eax
    L_0040c4be:
        jne short L_0040c4b0
    L_0040c4c0:
        ret
    }
}

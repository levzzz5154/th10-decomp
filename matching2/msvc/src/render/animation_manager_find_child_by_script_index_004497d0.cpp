#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x004497D0..0x00449815: ?AnimationManager_FindChildByScriptIndex@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_FindChildByScriptIndex_004497d0() {
    __asm {
    L_004497d0:
        mov eax,dword ptr [esi]
    L_004497d2:
        mov edx,dword ptr [data_00491c10]
    L_004497d8:
        push eax
    L_004497d9:
        call asm_AnimationManager_Find_004491c0
    L_004497de:
        test eax,eax
    L_004497e0:
        jne short L_004497e4
    L_004497e2:
        mov dword ptr [esi],eax
    L_004497e4:
        add eax,10h
    L_004497e7:
        je short L_00449804
    L_004497e9:
        lea esp,[esp+force_disp32_zero]
    L_004497f0:
        mov ecx,dword ptr [eax]
    L_004497f2:
        movsx edx,word ptr [ecx+38Ah]
    L_004497f9:
        cmp edx,ebx
    L_004497fb:
        je short L_0044980d
    L_004497fd:
        mov eax,dword ptr [eax+4]
    L_00449800:
        test eax,eax
    L_00449802:
        jne short L_004497f0
    L_00449804:
        mov dword ptr [edi],0
    L_0044980a:
        mov eax,edi
    L_0044980c:
        ret
    L_0044980d:
        mov eax,dword ptr [eax]
    L_0044980f:
        mov ecx,dword ptr [eax]
    L_00449811:
        mov dword ptr [edi],ecx
    L_00449813:
        mov eax,edi
    L_00449815:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x004495E0..0x00449622: ?AnimationManager_ClearFlag@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_ClearFlag_004495e0() {
    __asm {
    L_004495e0:
        mov ecx,dword ptr [eax]
    L_004495e2:
        mov edx,dword ptr [data_00491c10]
    L_004495e8:
        push ecx
    L_004495e9:
        call asm_AnimationManager_Find_004491c0
    L_004495ee:
        test eax,eax
    L_004495f0:
        je short L_00449622
    L_004495f2:
        mov ecx,dword ptr [eax+35Ch]
    L_004495f8:
        mov edx,0FFFFFFFDh
    L_004495fd:
        and ecx,edx
    L_004495ff:
        mov dword ptr [eax+35Ch],ecx
    L_00449605:
        mov ecx,dword ptr [eax+18h]
    L_00449608:
        test ecx,ecx
    L_0044960a:
        jne short L_00449622
    L_0044960c:
        mov eax,dword ptr [eax+14h]
    L_0044960f:
        test eax,eax
    L_00449611:
        je short L_00449622
    L_00449613:
        mov ecx,dword ptr [eax]
    L_00449615:
        and dword ptr [ecx+35Ch],edx
    L_0044961b:
        mov eax,dword ptr [eax+4]
    L_0044961e:
        test eax,eax
    L_00449620:
        jne short L_00449613
    L_00449622:
        ret
    }
}

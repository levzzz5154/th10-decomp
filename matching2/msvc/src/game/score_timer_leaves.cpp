#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418A90..0x00418AA3: Score_IncrementCounterClampedNine
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Score_IncrementCounterClampedNine_00418a90() {
    __asm {
    L_00418a90:
        mov ecx,dword ptr [eax+50h]
    L_00418a93:
        inc ecx
    L_00418a94:
        cmp ecx,0Ah
    L_00418a97:
        mov dword ptr [eax+50h],ecx
    L_00418a9a:
        jl short L_00418aa3
    L_00418a9c:
        mov dword ptr [eax+50h],9
    L_00418aa3:
        ret
    }
}

// 0x00418B80..0x00418BC8: ScoreGauge_SetTargetTenthAndDisableTimer
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreGauge_SetTargetTenthAndDisableTimer_00418b80() {
    __asm {
    L_00418b80:
        mov eax,66666667h
    L_00418b85:
        imul dword ptr [esp+4]
    L_00418b89:
        sar edx,2
    L_00418b8c:
        mov eax,edx
    L_00418b8e:
        shr eax,1Fh
    L_00418b91:
        add eax,edx
    L_00418b93:
        mov dword ptr [ecx+0Ch],eax
    L_00418b96:
        mov eax,dword ptr [ecx+24h]
    L_00418b99:
        xor edx,edx
    L_00418b9b:
        test al,1
    L_00418b9d:
        jne short L_00418bb9
    L_00418b9f:
        or eax,1
    L_00418ba2:
        mov dword ptr [ecx+18h],edx
    L_00418ba5:
        mov dword ptr [ecx+14h],0FFF0BDC1h
    L_00418bac:
        mov dword ptr [ecx+1Ch],edx
    L_00418baf:
        mov dword ptr [ecx+20h],476F78h
    L_00418bb6:
        mov dword ptr [ecx+24h],eax
    L_00418bb9:
        mov dword ptr [ecx+18h],edx
    L_00418bbc:
        mov dword ptr [ecx+1Ch],edx
    L_00418bbf:
        mov dword ptr [ecx+14h],0FFFFFFFFh
    L_00418bc6:
        ret 4
    }
}

// 0x0042C5C0..0x0042C612: ?GameState_DisableTimerWithOwner@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DisableTimerWithOwner_0042c5c0() {
    __asm {
    L_0042c5c0:
        xor edx,edx
    L_0042c5c2:
        mov dword ptr [eax+1Ch],ecx
    L_0042c5c5:
        mov dword ptr [eax+20h],edx
    L_0042c5c8:
        mov ecx,dword ptr [eax+2C0h]
    L_0042c5ce:
        test cl,1
    L_0042c5d1:
        jne short L_0042c5fc
    L_0042c5d3:
        or ecx,1
    L_0042c5d6:
        mov dword ptr [eax+2B4h],edx
    L_0042c5dc:
        mov dword ptr [eax+2B0h],0FFF0BDC1h
    L_0042c5e6:
        mov dword ptr [eax+2B8h],edx
    L_0042c5ec:
        mov dword ptr [eax+2BCh],476F78h
    L_0042c5f6:
        mov dword ptr [eax+2C0h],ecx
    L_0042c5fc:
        mov dword ptr [eax+2B4h],edx
    L_0042c602:
        mov dword ptr [eax+2B8h],edx
    L_0042c608:
        mov dword ptr [eax+2B0h],0FFFFFFFFh
    L_0042c612:
        ret
    }
}

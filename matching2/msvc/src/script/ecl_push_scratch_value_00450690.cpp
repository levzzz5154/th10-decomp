#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x00450690..0x004506CF: ?ECL_PushScratchValue@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_PushScratchValue_00450690() {
    __asm {
    L_00450690:
        mov edx,dword ptr [eax+1000h]
    L_00450696:
        add ecx,edx
    L_00450698:
        cmp ecx,1000h
    L_0045069e:
        jl short L_004506a4
    L_004506a0:
        or eax,0FFFFFFFFh
    L_004506a3:
        ret
    L_004506a4:
        push esi
    L_004506a5:
        lea esi,[ecx+4]
    L_004506a8:
        cmp esi,1000h
    L_004506ae:
        mov dword ptr [eax+1000h],ecx
    L_004506b4:
        jge short L_004506c6
    L_004506b6:
        mov esi,dword ptr [eax+1004h]
    L_004506bc:
        mov dword ptr [ecx+eax],esi
    L_004506bf:
        add dword ptr [eax+1000h],4
    L_004506c6:
        mov dword ptr [eax+1004h],edx
    L_004506cc:
        xor eax,eax
    L_004506ce:
        pop esi
    L_004506cf:
        ret
    }
}

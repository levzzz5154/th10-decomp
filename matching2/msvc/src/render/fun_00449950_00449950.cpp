#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449950..0x004499F0: FUN_00449950
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449950_00449950() {
    __asm {
    L_00449950:
        mov eax,dword ptr [esi+3AD068h]
    L_00449956:
        mov ecx,eax
    L_00449958:
        imul ecx,3ACh
    L_0044995e:
        push edi
    L_0044995f:
        lea edi,[ecx+esi+68h]
    L_00449963:
        mov cl,byte ptr [eax+esi+3AC068h]
    L_0044996a:
        test cl,cl
    L_0044996c:
        je short L_004499ca
    L_0044996e:
        inc eax
    L_0044996f:
        and eax,80000FFFh
    L_00449974:
        jns short L_0044997d
    L_00449976:
        dec eax
    L_00449977:
        or eax,0FFFFF000h
    L_0044997c:
        inc eax
    L_0044997d:
        mov edx,eax
    L_0044997f:
        imul edx,3ACh
    L_00449985:
        mov dword ptr [esi+3AD068h],eax
    L_0044998b:
        mov cl,byte ptr [eax+esi+3AC068h]
    L_00449992:
        test cl,cl
    L_00449994:
        lea edi,[edx+esi+68h]
    L_00449998:
        je short L_004499ca
    L_0044999a:
        push 3ACh
    L_0044999f:
        call asm_operator_new_00452493
    L_004499a4:
        add esp,4
    L_004499a7:
        test eax,eax
    L_004499a9:
        je short L_004499bd
    L_004499ab:
        mov ecx,eax
    L_004499ad:
        call asm_Entity_Constructor_00402050
    L_004499b2:
        mov edx,eax
    L_004499b4:
        mov edi,eax
    L_004499b6:
        call asm_InitializeEntity_00401de0
    L_004499bb:
        jmp short L_004499d2
    L_004499bd:
        xor eax,eax
    L_004499bf:
        mov edx,eax
    L_004499c1:
        mov edi,eax
    L_004499c3:
        call asm_InitializeEntity_00401de0
    L_004499c8:
        jmp short L_004499d2
    L_004499ca:
        mov byte ptr [eax+esi+3AC068h],1
    L_004499d2:
        mov eax,dword ptr [esi+3AD068h]
    L_004499d8:
        inc eax
    L_004499d9:
        and eax,80000FFFh
    L_004499de:
        jns short L_004499e7
    L_004499e0:
        dec eax
    L_004499e1:
        or eax,0FFFFF000h
    L_004499e6:
        inc eax
    L_004499e7:
        mov dword ptr [esi+3AD068h],eax
    L_004499ed:
        mov eax,edi
    L_004499ef:
        pop edi
    L_004499f0:
        ret
    }
}

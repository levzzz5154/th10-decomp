#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00447810..0x00447901: FUN_00447810
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00447810_00447810() {
    __asm {
    L_00447810:
        push ecx
    L_00447811:
        mov eax,dword ptr [edi+108h]
    L_00447817:
        push ebp
    L_00447818:
        xor ebp,ebp
    L_0044781a:
        cmp eax,ebp
    L_0044781c:
        je asm_target_004478ff
    L_00447822:
        mov eax,dword ptr [data_00491c10]
    L_00447827:
        mov edx,edi
    L_00447829:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_0044782e:
        cmp dword ptr [edi+10Ch],ebp
    L_00447834:
        mov dword ptr [esp+4],ebp
    L_00447838:
        jle short L_00447882
    L_0044783a:
        push ebx
    L_0044783b:
        push esi
    L_0044783c:
        xor ebx,ebx
    L_0044783e:
        mov edi,edi
    L_00447840:
        mov esi,dword ptr [edi+120h]
    L_00447846:
        mov eax,dword ptr [esi+ebx]
    L_00447849:
        add esi,ebx
    L_0044784b:
        cmp eax,ebp
    L_0044784d:
        je short L_00447857
    L_0044784f:
        mov ecx,dword ptr [eax]
    L_00447851:
        push eax
    L_00447852:
        call dword ptr [ecx+8]
    L_00447855:
        mov dword ptr [esi],ebp
    L_00447857:
        mov eax,dword ptr [esi+4]
    L_0044785a:
        cmp eax,ebp
    L_0044785c:
        je short L_0044786a
    L_0044785e:
        push eax
    L_0044785f:
        call asm_free_00452422
    L_00447864:
        add esp,4
    L_00447867:
        mov dword ptr [esi+4],ebp
    L_0044786a:
        mov eax,dword ptr [esp+0Ch]
    L_0044786e:
        mov ecx,dword ptr [edi+10Ch]
    L_00447874:
        inc eax
    L_00447875:
        add ebx,10h
    L_00447878:
        cmp eax,ecx
    L_0044787a:
        mov dword ptr [esp+0Ch],eax
    L_0044787e:
        jl short L_00447840
    L_00447880:
        pop esi
    L_00447881:
        pop ebx
    L_00447882:
        mov eax,dword ptr [edi+120h]
    L_00447888:
        cmp eax,ebp
    L_0044788a:
        je short L_0044789b
    L_0044788c:
        push eax
    L_0044788d:
        call asm_free_00452422
    L_00447892:
        add esp,4
    L_00447895:
        mov dword ptr [edi+120h],ebp
    L_0044789b:
        mov eax,dword ptr [edi+118h]
    L_004478a1:
        cmp eax,ebp
    L_004478a3:
        je short L_004478b4
    L_004478a5:
        push eax
    L_004478a6:
        call asm_free_00452422
    L_004478ab:
        add esp,4
    L_004478ae:
        mov dword ptr [edi+118h],ebp
    L_004478b4:
        mov eax,dword ptr [edi+11Ch]
    L_004478ba:
        cmp eax,ebp
    L_004478bc:
        je short L_004478cd
    L_004478be:
        push eax
    L_004478bf:
        call asm_free_00452422
    L_004478c4:
        add esp,4
    L_004478c7:
        mov dword ptr [edi+11Ch],ebp
    L_004478cd:
        mov eax,dword ptr [edi+12Ch]
    L_004478d3:
        cmp eax,ebp
    L_004478d5:
        je short L_004478e6
    L_004478d7:
        push eax
    L_004478d8:
        call asm_free_00452422
    L_004478dd:
        add esp,4
    L_004478e0:
        mov dword ptr [edi+12Ch],ebp
    L_004478e6:
        mov eax,dword ptr [edi+108h]
    L_004478ec:
        cmp eax,ebp
    L_004478ee:
        je short L_004478ff
    L_004478f0:
        push eax
    L_004478f1:
        call asm_free_00452422
    L_004478f6:
        add esp,4
    L_004478f9:
        mov dword ptr [edi+108h],ebp
    L_004478ff:
        pop ebp
    L_00447900:
        pop ecx
    L_00447901:
        ret
    }
}

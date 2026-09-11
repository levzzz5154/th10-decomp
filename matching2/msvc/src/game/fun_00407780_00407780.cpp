#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00407560..0x00407690: FUN_00407560
// Naked body preserves the retail register/stack ABI.

// 0x00407780..0x004078D1: FUN_00407780
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407780_00407780() {
    __asm {
    L_00407780:
        push ecx
    L_00407781:
        mov eax,dword ptr [esi+6D8h]
    L_00407787:
        cmp dword ptr [esi+6B4h],eax
    L_0040778d:
        mov dword ptr [esp],eax
    L_00407790:
        jl asm_target_0040783e
    L_00407796:
        push ebx
    L_00407797:
        push edi
    L_00407798:
        mov edi,dword ptr [esi+458h]
    L_0040779e:
        xor ebx,ebx
    L_004077a0:
        cmp edi,ebx
    L_004077a2:
        jl short L_004077af
    L_004077a4:
        push ebx
    L_004077a5:
        mov ecx,492590h
    L_004077aa:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004077af:
        mov edx,dword ptr [esi+6E0h]
    L_004077b5:
        mov ecx,dword ptr [esi+6DCh]
    L_004077bb:
        inc edx
    L_004077bc:
        mov eax,edx
    L_004077be:
        cmp eax,ecx
    L_004077c0:
        mov dword ptr [esi+6E0h],edx
    L_004077c6:
        jl short L_004077cf
    L_004077c8:
        and dword ptr [esi+43Ch],0FFFFFFBFh
    L_004077cf:
        fld dword ptr [esi+6C8h]
    L_004077d5:
        fadd dword ptr [esi+3E4h]
    L_004077db:
        fstp dword ptr [esi+3E4h]
    L_004077e1:
        fld dword ptr [esi+6C4h]
    L_004077e7:
        fst dword ptr [esi+3D8h]
    L_004077ed:
        mov eax,dword ptr [esi+6C0h]
    L_004077f3:
        test al,1
    L_004077f5:
        fstp dword ptr [esp+8]
    L_004077f9:
        jne short L_00407824
    L_004077fb:
        or eax,1
    L_004077fe:
        mov dword ptr [esi+6B4h],ebx
    L_00407804:
        mov dword ptr [esi+6B0h],0FFF0BDC1h
    L_0040780e:
        mov dword ptr [esi+6B8h],ebx
    L_00407814:
        mov dword ptr [esi+6BCh],476F78h
    L_0040781e:
        mov dword ptr [esi+6C0h],eax
    L_00407824:
        pop edi
    L_00407825:
        mov dword ptr [esi+6B4h],ebx
    L_0040782b:
        mov dword ptr [esi+6B8h],ebx
    L_00407831:
        mov dword ptr [esi+6B0h],0FFFFFFFFh
    L_0040783b:
        pop ebx
    L_0040783c:
        jmp short L_00407856
    L_0040783e:
        fld dword ptr [esi+3D8h]
    L_00407844:
        fld st(0)
    L_00407846:
        fmul dword ptr [esi+6B8h]
    L_0040784c:
        fidiv dword ptr [esp]
    L_0040784f:
        fsubr st,st(1)
    L_00407851:
        fstp dword ptr [esp]
    L_00407854:
        fstp st(0)
    L_00407856:
        mov eax,dword ptr [esp]
    L_00407859:
        mov ecx,dword ptr [esi+3E4h]
    L_0040785f:
        push eax
    L_00407860:
        push ecx
    L_00407861:
        lea ecx,[esi+3C0h]
    L_00407867:
        call asm_Score_SetPolarVector_00408750
    L_0040786c:
        mov edx,dword ptr [esi+6B4h]
    L_00407872:
        mov ecx,dword ptr [esi+6BCh]
    L_00407878:
        mov dword ptr [esi+6B0h],edx
    L_0040787e:
        fld dword ptr [ecx]
    L_00407880:
        fcomp dword ptr [data_00470b68]
    L_00407886:
        fnstsw ax
    L_00407888:
        test ah,41h
    L_0040788b:
        jne short L_004078b7
    L_0040788d:
        fld dword ptr [ecx]
    L_0040788f:
        fcomp dword ptr [data_00470b64]
    L_00407895:
        fnstsw ax
    L_00407897:
        test ah,5
    L_0040789a:
        jp short L_004078b7
    L_0040789c:
        fld dword ptr [esi+6B8h]
    L_004078a2:
        inc edx
    L_004078a3:
        fadd dword ptr [data_00470afc]
    L_004078a9:
        mov dword ptr [esi+6B4h],edx
    L_004078af:
        fstp dword ptr [esi+6B8h]
    L_004078b5:
        pop ecx
    L_004078b6:
        ret
    L_004078b7:
        fld dword ptr [ecx]
    L_004078b9:
        fadd dword ptr [esi+6B8h]
    L_004078bf:
        fst dword ptr [esi+6B8h]
    L_004078c5:
        call asm_FUN_00463b2c_00463b2c
    L_004078ca:
        mov dword ptr [esi+6B4h],eax
    L_004078d0:
        pop ecx
    L_004078d1:
        ret
    }
}

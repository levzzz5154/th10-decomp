#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x0043E710..0x0043E7DA: ?AnimationObject_LoadScript@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_LoadScript_0043e710() {
    __asm {
    L_0043e710:
        push ebp
    L_0043e711:
        push esi
    L_0043e712:
        mov esi,ecx
    L_0043e714:
        push edi
    L_0043e715:
        mov edi,eax
    L_0043e717:
        mov eax,dword ptr [esi+11Ch]
    L_0043e71d:
        mov ecx,dword ptr [eax+ebx*4]
    L_0043e720:
        xor ebp,ebp
    L_0043e722:
        cmp ecx,ebp
    L_0043e724:
        je asm_target_0043e7ce
    L_0043e72a:
        cmp dword ptr [esi+124h],ebp
    L_0043e730:
        jne asm_target_0043e7ce
    L_0043e736:
        mov edx,edi
    L_0043e738:
        call asm_InitializeEntity_00401de0
    L_0043e73d:
        mov edx,dword ptr [edi+35Ch]
    L_0043e743:
        mov word ptr [edi+38Ah],bx
    L_0043e74a:
        mov cx,word ptr [esi]
    L_0043e74d:
        and edx,0FFFFF9FFh
    L_0043e753:
        mov word ptr [edi+386h],cx
    L_0043e75a:
        mov dword ptr [edi+308h],esi
    L_0043e760:
        mov dword ptr [edi+35Ch],edx
    L_0043e766:
        mov edx,dword ptr [esi+11Ch]
    L_0043e76c:
        mov eax,dword ptr [edx+ebx*4]
    L_0043e76f:
        mov dword ptr [edi+38Ch],eax
    L_0043e775:
        mov dword ptr [edi+390h],eax
    L_0043e77b:
        mov eax,dword ptr [edi+6Ch]
    L_0043e77e:
        test al,1
    L_0043e780:
        jne short L_0043e79c
    L_0043e782:
        or eax,1
    L_0043e785:
        mov dword ptr [edi+60h],ebp
    L_0043e788:
        mov dword ptr [edi+5Ch],0FFF0BDC1h
    L_0043e78f:
        mov dword ptr [edi+64h],ebp
    L_0043e792:
        mov dword ptr [edi+68h],476F78h
    L_0043e799:
        mov dword ptr [edi+6Ch],eax
    L_0043e79c:
        mov dword ptr [edi+60h],ebp
    L_0043e79f:
        mov dword ptr [edi+64h],ebp
    L_0043e7a2:
        mov dword ptr [edi+5Ch],0FFFFFFFFh
    L_0043e7a9:
        mov esi,dword ptr [edi+35Ch]
    L_0043e7af:
        and esi,0FFFFFFFEh
    L_0043e7b2:
        push edi
    L_0043e7b3:
        mov dword ptr [edi+35Ch],esi
    L_0043e7b9:
        call asm_FUN_0043ee30_0043ee30
    L_0043e7be:
        mov eax,dword ptr [data_00491c10]
    L_0043e7c3:
        mov ecx,dword ptr [eax+4Ch]
    L_0043e7c6:
        pop edi
    L_0043e7c7:
        inc ecx
    L_0043e7c8:
        pop esi
    L_0043e7c9:
        mov dword ptr [eax+4Ch],ecx
    L_0043e7cc:
        pop ebp
    L_0043e7cd:
        ret
    L_0043e7ce:
        mov ecx,0EBh
    L_0043e7d3:
        xor eax,eax
    L_0043e7d5:
        rep stosd
    L_0043e7d7:
        pop edi
    L_0043e7d8:
        pop esi
    L_0043e7d9:
        pop ebp
    L_0043e7da:
        ret
    }
}

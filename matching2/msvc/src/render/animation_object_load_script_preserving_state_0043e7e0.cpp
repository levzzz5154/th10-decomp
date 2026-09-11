#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x0043E7E0..0x0043E8A1: ?AnimationObject_LoadScriptPreservingState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_LoadScriptPreservingState_0043e7e0() {
    __asm {
    L_0043e7e0:
        push ebx
    L_0043e7e1:
        push esi
    L_0043e7e2:
        mov esi,dword ptr [eax+11Ch]
    L_0043e7e8:
        mov ebx,dword ptr [esi+ecx*4]
    L_0043e7eb:
        push edi
    L_0043e7ec:
        mov edi,edx
    L_0043e7ee:
        xor edx,edx
    L_0043e7f0:
        cmp ebx,edx
    L_0043e7f2:
        je asm_target_0043e895
    L_0043e7f8:
        cmp dword ptr [eax+124h],edx
    L_0043e7fe:
        jne asm_target_0043e895
    L_0043e804:
        mov word ptr [edi+38Ah],cx
    L_0043e80b:
        mov si,word ptr [eax]
    L_0043e80e:
        mov word ptr [edi+386h],si
    L_0043e815:
        mov esi,dword ptr [edi+35Ch]
    L_0043e81b:
        and esi,0FFFFF9FFh
    L_0043e821:
        mov dword ptr [edi+308h],eax
    L_0043e827:
        mov dword ptr [edi+35Ch],esi
    L_0043e82d:
        mov eax,dword ptr [eax+11Ch]
    L_0043e833:
        mov eax,dword ptr [eax+ecx*4]
    L_0043e836:
        mov dword ptr [edi+38Ch],eax
    L_0043e83c:
        mov dword ptr [edi+390h],eax
    L_0043e842:
        mov eax,dword ptr [edi+6Ch]
    L_0043e845:
        test al,1
    L_0043e847:
        jne short L_0043e863
    L_0043e849:
        or eax,1
    L_0043e84c:
        mov dword ptr [edi+60h],edx
    L_0043e84f:
        mov dword ptr [edi+5Ch],0FFF0BDC1h
    L_0043e856:
        mov dword ptr [edi+64h],edx
    L_0043e859:
        mov dword ptr [edi+68h],476F78h
    L_0043e860:
        mov dword ptr [edi+6Ch],eax
    L_0043e863:
        mov dword ptr [edi+60h],edx
    L_0043e866:
        mov dword ptr [edi+64h],edx
    L_0043e869:
        mov dword ptr [edi+5Ch],0FFFFFFFFh
    L_0043e870:
        mov esi,dword ptr [edi+35Ch]
    L_0043e876:
        and esi,0FFFFFFFEh
    L_0043e879:
        push edi
    L_0043e87a:
        mov dword ptr [edi+35Ch],esi
    L_0043e880:
        call asm_FUN_0043ee30_0043ee30
    L_0043e885:
        mov eax,dword ptr [data_00491c10]
    L_0043e88a:
        mov ecx,dword ptr [eax+4Ch]
    L_0043e88d:
        pop edi
    L_0043e88e:
        inc ecx
    L_0043e88f:
        pop esi
    L_0043e890:
        mov dword ptr [eax+4Ch],ecx
    L_0043e893:
        pop ebx
    L_0043e894:
        ret
    L_0043e895:
        mov ecx,0EBh
    L_0043e89a:
        xor eax,eax
    L_0043e89c:
        rep stosd
    L_0043e89e:
        pop edi
    L_0043e89f:
        pop esi
    L_0043e8a0:
        pop ebx
    L_0043e8a1:
        ret
    }
}

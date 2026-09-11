#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448900..0x0044897A: ?AnimationManager_UpdateSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_UpdateSecondary_00448900() {
    __asm {
    L_00448900:
        push ebp
    L_00448901:
        push edi
    L_00448902:
        mov edi,eax
    L_00448904:
        mov eax,dword ptr [edi+72DADCh]
    L_0044890a:
        xor ecx,ecx
    L_0044890c:
        cmp eax,ecx
    L_0044890e:
        mov dword ptr [edi+7320C4h],ecx
    L_00448914:
        lea ebp,[edi+7320A8h]
    L_0044891a:
        mov dword ptr [edi+64h],ecx
    L_0044891d:
        je short L_00448973
    L_0044891f:
        push ebx
    L_00448920:
        push esi
    L_00448921:
        mov esi,dword ptr [eax]
    L_00448923:
        mov ebx,dword ptr [eax+4]
    L_00448926:
        test dword ptr [esi+35Ch],4000000h
    L_00448930:
        je short L_00448939
    L_00448932:
        call asm_FUN_00448bb0_00448bb0
    L_00448937:
        jmp short L_00448964
    L_00448939:
        mov eax,dword ptr [esi+398h]
    L_0044893f:
        test eax,eax
    L_00448941:
        je short L_00448947
    L_00448943:
        mov ecx,esi
    L_00448945:
        call eax
    L_00448947:
        push esi
    L_00448948:
        call asm_FUN_0043ee30_0043ee30
    L_0044894d:
        test eax,eax
    L_0044894f:
        je short L_00448958
    L_00448951:
        call asm_FUN_00448bb0_00448bb0
    L_00448956:
        jmp short L_00448964
    L_00448958:
        mov dword ptr [ebp+1Ch],esi
    L_0044895b:
        mov ebp,esi
    L_0044895d:
        mov dword ptr [esi+1Ch],0
    L_00448964:
        mov edx,dword ptr [edi+64h]
    L_00448967:
        inc edx
    L_00448968:
        test ebx,ebx
    L_0044896a:
        mov dword ptr [edi+64h],edx
    L_0044896d:
        mov eax,ebx
    L_0044896f:
        jne short L_00448921
    L_00448971:
        pop esi
    L_00448972:
        pop ebx
    L_00448973:
        pop edi
    L_00448974:
        mov eax,1
    L_00448979:
        pop ebp
    L_0044897a:
        ret
    }
}

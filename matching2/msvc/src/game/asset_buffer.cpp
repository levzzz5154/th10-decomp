#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B480..0x0040B4E9: FUN_0040b480
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b480_0040b480() {
    __asm {
    L_0040b480:
        push ebp
    L_0040b481:
        mov ebp,dword ptr [esp+8]
    L_0040b485:
        push esi
    L_0040b486:
        mov byte ptr [data_00497c38],0
    L_0040b48d:
        mov ecx,eax
    L_0040b48f:
        nop
    L_0040b490:
        mov dl,byte ptr [eax]
    L_0040b492:
        inc eax
    L_0040b493:
        test dl,dl
    L_0040b495:
        jne short L_0040b490
    L_0040b497:
        push edi
    L_0040b498:
        mov edi,497C38h
    L_0040b49d:
        sub eax,ecx
    L_0040b49f:
        mov esi,ecx
    L_0040b4a1:
        dec edi
    L_0040b4a2:
        mov cl,byte ptr [edi+1]
    L_0040b4a5:
        inc edi
    L_0040b4a6:
        test cl,cl
    L_0040b4a8:
        jne short L_0040b4a2
    L_0040b4aa:
        mov ecx,eax
    L_0040b4ac:
        shr ecx,2
    L_0040b4af:
        rep movsd
    L_0040b4b1:
        mov ecx,eax
    L_0040b4b3:
        push 0
    L_0040b4b5:
        and ecx,3
    L_0040b4b8:
        push 0
    L_0040b4ba:
        mov eax,497C38h
    L_0040b4bf:
        rep movsb
    L_0040b4c1:
        call asm_FUN_0044b360_0044b360
    L_0040b4c6:
        mov esi,eax
    L_0040b4c8:
        mov eax,dword ptr [ebp+14h]
    L_0040b4cb:
        test eax,eax
    L_0040b4cd:
        pop edi
    L_0040b4ce:
        je short L_0040b4e0
    L_0040b4d0:
        push eax
    L_0040b4d1:
        call asm_free_00452422
    L_0040b4d6:
        add esp,4
    L_0040b4d9:
        mov dword ptr [ebp+14h],0
    L_0040b4e0:
        mov dword ptr [ebp+14h],esi
    L_0040b4e3:
        mov eax,esi
    L_0040b4e5:
        pop esi
    L_0040b4e6:
        pop ebp
    L_0040b4e7:
        ret 4
    }
}

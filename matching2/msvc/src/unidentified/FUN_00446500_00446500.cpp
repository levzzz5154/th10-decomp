#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446500..0x0044652D: FUN_00446500
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00446500_00446500() {
    __asm {
    L_00446500:
        push ebx
    L_00446501:
        mov bl,byte ptr [ecx+3]
    L_00446504:
        test bl,bl
    L_00446506:
        je short L_0044652c
    L_00446508:
        mov ebx,dword ptr [eax+4]
    L_0044650b:
        push esi
    L_0044650c:
        movzx esi,byte ptr [ecx+2]
    L_00446510:
        add dword ptr [eax],esi
    L_00446512:
        movzx esi,byte ptr [ecx+1]
    L_00446516:
        add ebx,esi
    L_00446518:
        mov esi,dword ptr [eax+8]
    L_0044651b:
        mov dword ptr [eax+4],ebx
    L_0044651e:
        movzx ecx,byte ptr [ecx]
    L_00446521:
        add esi,ecx
    L_00446523:
        mov dword ptr [eax+8],esi
    L_00446526:
        mov eax,dword ptr [edx]
    L_00446528:
        inc eax
    L_00446529:
        mov dword ptr [edx],eax
    L_0044652b:
        pop esi
    L_0044652c:
        pop ebx
    L_0044652d:
        ret
    }
}

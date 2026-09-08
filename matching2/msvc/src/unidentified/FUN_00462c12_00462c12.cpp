#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462C12..0x00462C59: FUN_00462c12
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462c12_00462c12() {
    __asm {
    L_00462c12:
        push esi
    L_00462c13:
        push edi
    L_00462c14:
        mov edi,dword ptr [esp+0Ch]
    L_00462c18:
        mov esi,ecx
    L_00462c1a:
        mov dword ptr [esi],46CA68h
    L_00462c20:
        mov eax,dword ptr [edi]
    L_00462c22:
        test eax,eax
    L_00462c24:
        je short L_00462c48
    L_00462c26:
        push eax
    L_00462c27:
        call asm_strlen_00456720
    L_00462c2c:
        inc eax
    L_00462c2d:
        push eax
    L_00462c2e:
        call asm_malloc_00452706
    L_00462c33:
        test eax,eax
    L_00462c35:
        pop ecx
    L_00462c36:
        pop ecx
    L_00462c37:
        mov dword ptr [esi+4],eax
    L_00462c3a:
        je short L_00462c4c
    L_00462c3c:
        push dword ptr [edi]
    L_00462c3e:
        push eax
    L_00462c3f:
        call asm_FUN_0045bd80_0045bd80
    L_00462c44:
        pop ecx
    L_00462c45:
        pop ecx
    L_00462c46:
        jmp short L_00462c4c
    L_00462c48:
        and dword ptr [esi+4],0
    L_00462c4c:
        pop edi
    L_00462c4d:
        mov dword ptr [esi+8],1
    L_00462c54:
        mov eax,esi
    L_00462c56:
        pop esi
    L_00462c57:
        ret 4
    }
}

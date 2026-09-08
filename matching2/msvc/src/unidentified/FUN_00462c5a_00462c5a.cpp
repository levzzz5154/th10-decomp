#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462C5A..0x00462CAB: FUN_00462c5a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462c5a_00462c5a() {
    __asm {
    L_00462c5a:
        push esi
    L_00462c5b:
        mov esi,ecx
    L_00462c5d:
        push edi
    L_00462c5e:
        mov edi,dword ptr [esp+0Ch]
    L_00462c62:
        mov dword ptr [esi],46CA68h
    L_00462c68:
        mov eax,dword ptr [edi+8]
    L_00462c6b:
        mov dword ptr [esi+8],eax
    L_00462c6e:
        test eax,eax
    L_00462c70:
        mov eax,dword ptr [edi+4]
    L_00462c73:
        je short L_00462ca2
    L_00462c75:
        test eax,eax
    L_00462c77:
        je short L_00462c9c
    L_00462c79:
        push eax
    L_00462c7a:
        call asm_strlen_00456720
    L_00462c7f:
        inc eax
    L_00462c80:
        push eax
    L_00462c81:
        call asm_malloc_00452706
    L_00462c86:
        test eax,eax
    L_00462c88:
        pop ecx
    L_00462c89:
        pop ecx
    L_00462c8a:
        mov dword ptr [esi+4],eax
    L_00462c8d:
        je short L_00462ca5
    L_00462c8f:
        push dword ptr [edi+4]
    L_00462c92:
        push eax
    L_00462c93:
        call asm_FUN_0045bd80_0045bd80
    L_00462c98:
        pop ecx
    L_00462c99:
        pop ecx
    L_00462c9a:
        jmp short L_00462ca5
    L_00462c9c:
        and dword ptr [esi+4],0
    L_00462ca0:
        jmp short L_00462ca5
    L_00462ca2:
        mov dword ptr [esi+4],eax
    L_00462ca5:
        pop edi
    L_00462ca6:
        mov eax,esi
    L_00462ca8:
        pop esi
    L_00462ca9:
        ret 4
    }
}

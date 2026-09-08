#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C7B0..0x0040C7F6: FUN_0040c7b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c7b0_0040c7b0() {
    __asm {
    L_0040c7b0:
        push ebx
    L_0040c7b1:
        mov ebx,ecx
    L_0040c7b3:
        push esi
    L_0040c7b4:
        mov esi,dword ptr [ebx+1034h]
    L_0040c7ba:
        test esi,esi
    L_0040c7bc:
        mov dword ptr [ebx],46D0D8h
    L_0040c7c2:
        je short L_0040c7e0
    L_0040c7c4:
        push edi
    L_0040c7c5:
        mov eax,dword ptr [esi]
    L_0040c7c7:
        mov edi,dword ptr [esi+4]
    L_0040c7ca:
        push eax
    L_0040c7cb:
        call asm_free_004524a1
    L_0040c7d0:
        push esi
    L_0040c7d1:
        call asm_free_004524a1
    L_0040c7d6:
        add esp,8
    L_0040c7d9:
        test edi,edi
    L_0040c7db:
        mov esi,edi
    L_0040c7dd:
        jne short L_0040c7c5
    L_0040c7df:
        pop edi
    L_0040c7e0:
        test byte ptr [esp+0Ch],1
    L_0040c7e5:
        je short L_0040c7f0
    L_0040c7e7:
        push ebx
    L_0040c7e8:
        call asm_free_004524a1
    L_0040c7ed:
        add esp,4
    L_0040c7f0:
        pop esi
    L_0040c7f1:
        mov eax,ebx
    L_0040c7f3:
        pop ebx
    L_0040c7f4:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462F7C..0x00462FAF: ___DestructExceptionObject
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DestructExceptionObject_00462f7c() {
    __asm {
    L_00462f7c:
        push 8
    L_00462f7e:
        push 46CAC0h
    L_00462f83:
        call asm_SEH_prolog_00454bbc
    L_00462f88:
        mov eax,dword ptr [ebp+8]
    L_00462f8b:
        test eax,eax
    L_00462f8d:
        je short L_00462faa
    L_00462f8f:
        mov ecx,dword ptr [eax+1Ch]
    L_00462f92:
        mov ecx,dword ptr [ecx+4]
    L_00462f95:
        test ecx,ecx
    L_00462f97:
        je short L_00462faa
    L_00462f99:
        and dword ptr [ebp-4],0
    L_00462f9d:
        push ecx
    L_00462f9e:
        push dword ptr [eax+18h]
    L_00462fa1:
        call asm_CallMemberFunction0_00462706
    L_00462fa6:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00462faa:
        call asm_SEH_epilog_00454bf7
    L_00462faf:
        ret
    }
}

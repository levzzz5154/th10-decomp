#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044D790..0x0044D7C2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044d790() {
    __asm {
    L_0044d790:
        cmp dword ptr [ecx+1Ch],2
    L_0044d794:
        jne short L_0044d7c0
    L_0044d796:
        mov eax,dword ptr [ecx+14h]
    L_0044d799:
        dec eax
    L_0044d79a:
        test eax,eax
    L_0044d79c:
        mov dword ptr [ecx+14h],eax
    L_0044d79f:
        jg short L_0044d7ae
    L_0044d7a1:
        mov dword ptr [ecx+1Ch],0
    L_0044d7a8:
        mov eax,1
    L_0044d7ad:
        ret
    L_0044d7ae:
        imul eax,0FFFFEC78h
    L_0044d7b4:
        cdq
    L_0044d7b5:
        idiv dword ptr [ecx+18h]
    L_0044d7b8:
        push eax
    L_0044d7b9:
        mov eax,ecx
    L_0044d7bb:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_0044d7c0:
        xor eax,eax
    L_0044d7c2:
        ret
    }
}

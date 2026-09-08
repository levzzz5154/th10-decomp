#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044D810..0x0044D847: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044d810() {
    __asm {
    L_0044d810:
        cmp dword ptr [ecx+1Ch],4
    L_0044d814:
        jne short L_0044d845
    L_0044d816:
        mov eax,dword ptr [ecx+14h]
    L_0044d819:
        dec eax
    L_0044d81a:
        test eax,eax
    L_0044d81c:
        mov dword ptr [ecx+14h],eax
    L_0044d81f:
        jg short L_0044d82e
    L_0044d821:
        mov dword ptr [ecx+1Ch],0
    L_0044d828:
        mov eax,1
    L_0044d82d:
        ret
    L_0044d82e:
        imul eax,3E8h
    L_0044d834:
        cdq
    L_0044d835:
        idiv dword ptr [ecx+18h]
    L_0044d838:
        sub eax,3E8h
    L_0044d83d:
        push eax
    L_0044d83e:
        mov eax,ecx
    L_0044d840:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_0044d845:
        xor eax,eax
    L_0044d847:
        ret
    }
}

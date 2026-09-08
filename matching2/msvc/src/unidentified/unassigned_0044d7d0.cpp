#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044D7D0..0x0044D802: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044d7d0() {
    __asm {
    L_0044d7d0:
        cmp dword ptr [ecx+1Ch],3
    L_0044d7d4:
        jne short L_0044d800
    L_0044d7d6:
        mov eax,dword ptr [ecx+14h]
    L_0044d7d9:
        dec eax
    L_0044d7da:
        test eax,eax
    L_0044d7dc:
        mov dword ptr [ecx+14h],eax
    L_0044d7df:
        jg short L_0044d7ee
    L_0044d7e1:
        mov dword ptr [ecx+1Ch],0
    L_0044d7e8:
        mov eax,1
    L_0044d7ed:
        ret
    L_0044d7ee:
        imul eax,0FFFFFC18h
    L_0044d7f4:
        cdq
    L_0044d7f5:
        idiv dword ptr [ecx+18h]
    L_0044d7f8:
        push eax
    L_0044d7f9:
        mov eax,ecx
    L_0044d7fb:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_0044d800:
        xor eax,eax
    L_0044d802:
        ret
    }
}

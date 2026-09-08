#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044D740..0x0044D782: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044d740() {
    __asm {
    L_0044d740:
        cmp dword ptr [ecx+1Ch],1
    L_0044d744:
        jne short L_0044d780
    L_0044d746:
        mov eax,dword ptr [ecx+14h]
    L_0044d749:
        dec eax
    L_0044d74a:
        test eax,eax
    L_0044d74c:
        mov dword ptr [ecx+14h],eax
    L_0044d74f:
        jg short L_0044d769
    L_0044d751:
        mov eax,dword ptr [ecx+4]
    L_0044d754:
        mov dword ptr [ecx+1Ch],0
    L_0044d75b:
        mov eax,dword ptr [eax]
    L_0044d75d:
        mov ecx,dword ptr [eax]
    L_0044d75f:
        push eax
    L_0044d760:
        call dword ptr [ecx+48h]
    L_0044d763:
        mov eax,1
    L_0044d768:
        ret
    L_0044d769:
        imul eax,1388h
    L_0044d76f:
        cdq
    L_0044d770:
        idiv dword ptr [ecx+18h]
    L_0044d773:
        sub eax,1388h
    L_0044d778:
        push eax
    L_0044d779:
        mov eax,ecx
    L_0044d77b:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_0044d780:
        xor eax,eax
    L_0044d782:
        ret
    }
}

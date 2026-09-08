#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045986B..0x0045988E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045986b() {
    __asm {
    L_0045986b:
        mov eax,dword ptr [ebp-14h]
    L_0045986e:
        mov eax,dword ptr [eax]
    L_00459870:
        mov eax,dword ptr [eax]
    L_00459872:
        mov dword ptr [ebp-1Ch],eax
    L_00459875:
        xor eax,eax
    L_00459877:
        inc eax
    L_00459878:
        ret
    L_00459879:
        mov esp,dword ptr [ebp-18h]
    L_0045987c:
        cmp dword ptr [ebp-1Ch],0C0000017h
    L_00459883:
        jne short L_0045988d
    L_00459885:
        push 8
    L_00459887:
        call dword ptr [data_0046616c]
    L_0045988d:
        xor eax,eax
    }
}

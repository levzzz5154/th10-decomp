#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C770..0x0044C782: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c770() {
    __asm {
    L_0044c770:
        mov eax,dword ptr [esi]
    L_0044c772:
        test eax,eax
    L_0044c774:
        je short L_0044c782
    L_0044c776:
        mov ecx,dword ptr [eax]
    L_0044c778:
        push eax
    L_0044c779:
        call dword ptr [ecx+8]
    L_0044c77c:
        mov dword ptr [esi],0
    L_0044c782:
        ret
    }
}

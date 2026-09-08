#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436870..0x0043688E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436870() {
    __asm {
    L_00436870:
        mov ecx,dword ptr [edx+10Ch]
    L_00436876:
        push edi
    L_00436877:
        mov edi,dword ptr [edx+120h]
    L_0043687d:
        mov edx,ecx
    L_0043687f:
        shr ecx,2
    L_00436882:
        xor eax,eax
    L_00436884:
        rep stosd
    L_00436886:
        mov ecx,edx
    L_00436888:
        and ecx,3
    L_0043688b:
        rep stosb
    L_0043688d:
        pop edi
    L_0043688e:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CD85..0x0045CDAD: setSBCS
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_setSBCS_0045cd85() {
    __asm {
    L_0045cd85:
        push edi
    L_0045cd86:
        push 40h
    L_0045cd88:
        xor eax,eax
    L_0045cd8a:
        pop ecx
    L_0045cd8b:
        mov edi,497FA0h
    L_0045cd90:
        rep stosd
    L_0045cd92:
        stosb
    L_0045cd93:
        xor eax,eax
    L_0045cd95:
        mov dword ptr [data_004980a4],eax
    L_0045cd9a:
        mov dword ptr [data_00497f98],eax
    L_0045cd9f:
        mov dword ptr [data_00497f90],eax
    L_0045cda4:
        mov edi,4980B0h
    L_0045cda9:
        stosd
    L_0045cdaa:
        stosd
    L_0045cdab:
        stosd
    L_0045cdac:
        pop edi
    L_0045cdad:
        ret
    }
}

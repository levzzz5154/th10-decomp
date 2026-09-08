#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045371B..0x0045373C: _rand
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_rand_0045371b() {
    __asm {
    L_0045371b:
        call asm_getptd_00456357
    L_00453720:
        mov ecx,dword ptr [eax+14h]
    L_00453723:
        imul ecx,343FDh
    L_00453729:
        add ecx,269EC3h
    L_0045372f:
        mov dword ptr [eax+14h],ecx
    L_00453732:
        mov eax,ecx
    L_00453734:
        shr eax,10h
    L_00453737:
        and eax,7FFFh
    L_0045373c:
        ret
    }
}

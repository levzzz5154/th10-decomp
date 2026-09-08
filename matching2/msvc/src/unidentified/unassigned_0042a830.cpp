#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A830..0x0042A84B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042a830() {
    __asm {
    L_0042a830:
        mov ecx,dword ptr [eax+5460h]
    L_0042a836:
        sub ecx,eax
    L_0042a838:
        mov eax,2AAAAAABh
    L_0042a83d:
        imul ecx
    L_0042a83f:
        mov eax,edx
    L_0042a841:
        shr eax,1Fh
    L_0042a844:
        add eax,edx
    L_0042a846:
        lea eax,[eax+eax*2]
    L_0042a849:
        shl eax,1
    L_0042a84b:
        ret
    }
}

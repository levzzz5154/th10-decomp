#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BC20..0x0043BC36: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043bc20() {
    __asm {
    L_0043bc20:
        and dword ptr [edx+40h],0FFFFFFFEh
    L_0043bc24:
        push edi
    L_0043bc25:
        xor eax,eax
    L_0043bc27:
        mov ecx,11h
    L_0043bc2c:
        mov edi,edx
    L_0043bc2e:
        rep stosd
    L_0043bc30:
        or dword ptr [edx],2
    L_0043bc33:
        mov eax,edx
    L_0043bc35:
        pop edi
    L_0043bc36:
        ret
    }
}

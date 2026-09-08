#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CF30..0x0040CF3F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040cf30() {
    __asm {
    L_0040cf30:
        push edi
    L_0040cf31:
        xor eax,eax
    L_0040cf33:
        mov ecx,77h
    L_0040cf38:
        mov edi,edx
    L_0040cf3a:
        rep stosd
    L_0040cf3c:
        mov eax,edx
    L_0040cf3e:
        pop edi
    L_0040cf3f:
        ret
    }
}

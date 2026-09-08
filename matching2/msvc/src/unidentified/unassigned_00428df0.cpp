#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428DF0..0x00428E00: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428df0() {
    __asm {
    L_00428df0:
        mov ecx,dword ptr [eax+4]
    L_00428df3:
        push esi
    L_00428df4:
        mov esi,dword ptr [eax]
    L_00428df6:
        xor edx,edx
    L_00428df8:
        cmp ecx,esi
    L_00428dfa:
        setne dl
    L_00428dfd:
        pop esi
    L_00428dfe:
        mov eax,edx
    L_00428e00:
        ret
    }
}

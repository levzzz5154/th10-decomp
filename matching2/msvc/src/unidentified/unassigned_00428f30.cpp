#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428F30..0x00428F59: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428f30() {
    __asm {
    L_00428f30:
        push edi
    L_00428f31:
        push 42AC60h
    L_00428f36:
        push 42AC20h
    L_00428f3b:
        push 8
    L_00428f3d:
        push 24h
    L_00428f3f:
        lea eax,[esi+0A0h]
    L_00428f45:
        push eax
    L_00428f46:
        call asm_eh_vector_constructor_iterator_0045252d
    L_00428f4b:
        xor eax,eax
    L_00428f4d:
        mov ecx,0B5h
    L_00428f52:
        mov edi,esi
    L_00428f54:
        rep stosd
    L_00428f56:
        mov eax,esi
    L_00428f58:
        pop edi
    L_00428f59:
        ret
    }
}

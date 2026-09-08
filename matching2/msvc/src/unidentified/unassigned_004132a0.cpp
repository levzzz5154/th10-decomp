#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004132A0..0x004132B8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004132a0() {
    __asm {
    L_004132a0:
        push edi
    L_004132a1:
        xor eax,eax
    L_004132a3:
        mov ecx,23h
    L_004132a8:
        mov edi,edx
    L_004132aa:
        rep stosd
    L_004132ac:
        or dword ptr [edx],2
    L_004132af:
        mov dword ptr [data_00477708],edx
    L_004132b5:
        mov eax,edx
    L_004132b7:
        pop edi
    L_004132b8:
        ret
    }
}

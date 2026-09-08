#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004574F5..0x004574FC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004574f5() {
    __asm {
    L_004574f5:
        xor ebx,ebx
    L_004574f7:
        mov esi,dword ptr [ebp+0Ch]
    L_004574fa:
        mov edi,dword ptr [ebp+8]
    }
}

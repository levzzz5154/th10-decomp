#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040BA70..0x0040BA79: FUN_0040ba70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ba70_0040ba70() {
    __asm {
    L_0040ba70:
        push edi
    L_0040ba71:
        mov edi,ecx
    L_0040ba73:
        call asm_Recovery_UpdateEmitterDecision_0040b9f0
    L_0040ba78:
        pop edi
    L_0040ba79:
        ret
    }
}

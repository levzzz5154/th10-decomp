#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A340..0x0040A34F: FUN_0040a340
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040a340_0040a340() {
    __asm {
    L_0040a340:
        push esi
    L_0040a341:
        mov esi,dword ptr [data_004776f8]
    L_0040a347:
        call asm_FUN_0040a350_0040a350
    L_0040a34c:
        xor eax,eax
    L_0040a34e:
        pop esi
    L_0040a34f:
        ret
    }
}

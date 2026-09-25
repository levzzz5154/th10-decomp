#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405840..0x00405849: FUN_00405840
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405840_00405840() {
    __asm {
    L_00405840:
        push edi
    L_00405841:
        mov edi,ecx
    L_00405843:
        call asm_UpdatePlayer_00405750
    L_00405848:
        pop edi
    L_00405849:
        ret
    }
}

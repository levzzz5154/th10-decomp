#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459CAE..0x00459CB5: FUN_00459cae
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00459cae_00459cae() {
    __asm {
    L_00459cae:
        push ebx
    L_00459caf:
        call asm_FUN_0045f7b5_0045f7b5
    L_00459cb4:
        pop ecx
    L_00459cb5:
        ret
    }
}

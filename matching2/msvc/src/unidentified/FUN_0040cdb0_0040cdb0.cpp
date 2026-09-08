#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CDB0..0x0040CDB6: FUN_0040cdb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cdb0_0040cdb0() {
    __asm {
    L_0040cdb0:
        mov eax,dword ptr [eax+3504h]
    L_0040cdb6:
        ret
    }
}

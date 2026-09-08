#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404CE0..0x00404CE6: FUN_00404ce0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404ce0_00404ce0() {
    __asm {
    L_00404ce0:
        mov eax,dword ptr [eax+84h]
    L_00404ce6:
        ret
    }
}

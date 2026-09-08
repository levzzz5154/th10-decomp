#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405BB0..0x00405BB3: FUN_00405bb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405bb0_00405bb0() {
    __asm {
    L_00405bb0:
        mov eax,dword ptr [eax+28h]
    L_00405bb3:
        ret
    }
}

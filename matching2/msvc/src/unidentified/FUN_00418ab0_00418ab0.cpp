#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418AB0..0x00418AB3: FUN_00418ab0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418ab0_00418ab0() {
    __asm {
    L_00418ab0:
        mov eax,dword ptr [eax+40h]
    L_00418ab3:
        ret
    }
}

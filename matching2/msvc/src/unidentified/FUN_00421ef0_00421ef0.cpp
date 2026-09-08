#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421EF0..0x00421EF3: FUN_00421ef0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421ef0_00421ef0() {
    __asm {
    L_00421ef0:
        mov eax,dword ptr [eax+10h]
    L_00421ef3:
        ret
    }
}

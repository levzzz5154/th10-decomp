#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004367F0..0x004367F2: FUN_004367f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004367f0_004367f0() {
    __asm {
    L_004367f0:
        mov eax,dword ptr [eax]
    L_004367f2:
        ret
    }
}

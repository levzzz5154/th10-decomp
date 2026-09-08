#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004557F0..0x004557F5: FUN_004557f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004557f0_004557f0() {
    __asm {
    L_004557f0:
        mov eax,dword ptr [data_00499318]
    L_004557f5:
        ret
    }
}

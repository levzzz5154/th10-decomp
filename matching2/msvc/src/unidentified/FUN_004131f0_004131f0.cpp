#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004131F0..0x004131F3: FUN_004131f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004131f0_004131f0() {
    __asm {
    L_004131f0:
        mov eax,dword ptr [eax+8]
    L_004131f3:
        ret
    }
}

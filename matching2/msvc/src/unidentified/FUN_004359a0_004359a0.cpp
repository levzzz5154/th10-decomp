#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004359A0..0x004359A3: FUN_004359a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004359a0_004359a0() {
    __asm {
    L_004359a0:
        mov eax,dword ptr [eax+8]
    L_004359a3:
        ret
    }
}

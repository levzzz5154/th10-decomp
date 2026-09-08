#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004175A0..0x004175A3: FUN_004175a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004175a0_004175a0() {
    __asm {
    L_004175a0:
        mov eax,dword ptr [eax+54h]
    L_004175a3:
        ret
    }
}

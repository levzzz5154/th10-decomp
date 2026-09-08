#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004176A0..0x004176A3: FUN_004176a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004176a0_004176a0() {
    __asm {
    L_004176a0:
        mov eax,dword ptr [eax+30h]
    L_004176a3:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004088B0..0x004088B6: FUN_004088b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004088b0_004088b0() {
    __asm {
    L_004088b0:
        mov eax,dword ptr [eax+9EC8h]
    L_004088b6:
        ret
    }
}

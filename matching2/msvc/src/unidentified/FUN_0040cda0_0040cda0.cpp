#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CDA0..0x0040CDA6: FUN_0040cda0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cda0_0040cda0() {
    __asm {
    L_0040cda0:
        mov eax,dword ptr [eax+458h]
    L_0040cda6:
        ret
    }
}

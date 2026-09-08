#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C140..0x0044C147: FUN_0044c140
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044c140_0044c140() {
    __asm {
    L_0044c140:
        mov dword ptr [eax+0Ch],1
    L_0044c147:
        ret
    }
}

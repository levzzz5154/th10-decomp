#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C460..0x0040C462: FUN_0040c460
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c460_0040c460() {
    __asm {
    L_0040c460:
        mov dword ptr [eax],ecx
    L_0040c462:
        ret
    }
}

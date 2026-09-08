#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DD30..0x0044DD33: FUN_0044dd30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044dd30_0044dd30() {
    __asm {
    L_0044dd30:
        mov eax,dword ptr [eax+2Ch]
    L_0044dd33:
        ret
    }
}

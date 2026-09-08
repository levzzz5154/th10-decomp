#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C910..0x0040C912: FUN_0040c910
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c910_0040c910() {
    __asm {
    L_0040c910:
        mov dword ptr [ecx],eax
    L_0040c912:
        ret
    }
}

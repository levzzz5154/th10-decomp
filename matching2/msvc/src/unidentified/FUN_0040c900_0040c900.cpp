#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C900..0x0040C903: FUN_0040c900
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c900_0040c900() {
    __asm {
    L_0040c900:
        mov dword ptr [eax+8],ecx
    L_0040c903:
        ret
    }
}

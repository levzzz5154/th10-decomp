#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C980..0x0040C982: FUN_0040c980
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c980_0040c980() {
    __asm {
    L_0040c980:
        mov dword ptr [eax],ecx
    L_0040c982:
        ret
    }
}

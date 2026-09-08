#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043E560..0x0043E562: FUN_0043e560
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043e560_0043e560() {
    __asm {
    L_0043e560:
        mov eax,dword ptr [eax]
    L_0043e562:
        ret
    }
}

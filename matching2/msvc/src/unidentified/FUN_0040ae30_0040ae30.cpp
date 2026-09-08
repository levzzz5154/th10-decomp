#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE30..0x0040AE32: FUN_0040ae30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ae30_0040ae30() {
    __asm {
    L_0040ae30:
        mov eax,dword ptr [eax]
    L_0040ae32:
        ret
    }
}

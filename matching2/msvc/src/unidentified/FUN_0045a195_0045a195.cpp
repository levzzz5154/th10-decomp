#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A195..0x0045A19A: FUN_0045a195
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045a195_0045a195() {
    __asm {
    L_0045a195:
        mov eax,dword ptr [data_004739dc]
    L_0045a19a:
        ret
    }
}

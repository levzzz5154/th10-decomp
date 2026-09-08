#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C830..0x0042C836: FUN_0042c830
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042c830_0042c830() {
    __asm {
    L_0042c830:
        mov eax,dword ptr [eax+3ECh]
    L_0042c836:
        ret
    }
}

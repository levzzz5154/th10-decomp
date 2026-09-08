#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436820..0x00436826: FUN_00436820
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436820_00436820() {
    __asm {
    L_00436820:
        mov eax,dword ptr [eax+114h]
    L_00436826:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424600..0x00424606: FUN_00424600
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00424600_00424600() {
    __asm {
    L_00424600:
        mov eax,dword ptr [eax+8998h]
    L_00424606:
        ret
    }
}

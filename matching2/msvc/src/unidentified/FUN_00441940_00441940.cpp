#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441940..0x00441943: FUN_00441940
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441940_00441940() {
    __asm {
    L_00441940:
        mov eax,dword ptr [eax+44h]
    L_00441943:
        ret
    }
}

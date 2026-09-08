#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409DF0..0x00409DF6: FUN_00409df0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409df0_00409df0() {
    __asm {
    L_00409df0:
        mov eax,dword ptr [eax+8994h]
    L_00409df6:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418B70..0x00418B73: FUN_00418b70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418b70_00418b70() {
    __asm {
    L_00418b70:
        mov dword ptr [eax+30h],ecx
    L_00418b73:
        ret
    }
}

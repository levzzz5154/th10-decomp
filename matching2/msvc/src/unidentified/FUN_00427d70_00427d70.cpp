#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427D70..0x00427D75: FUN_00427d70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427d70_00427d70() {
    __asm {
    L_00427d70:
        mov dword ptr [eax],ecx
    L_00427d72:
        mov dword ptr [eax+4],edx
    L_00427d75:
        ret
    }
}

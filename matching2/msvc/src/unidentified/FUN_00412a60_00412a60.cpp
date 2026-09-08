#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412A60..0x00412A6D: FUN_00412a60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412a60_00412a60() {
    __asm {
    L_00412a60:
        mov eax,dword ptr [eax+14D8h]
    L_00412a66:
        mov eax,dword ptr [eax+4]
    L_00412a69:
        jmp asm_ECL_ResolveFloatOperand_0044fe40
    }
}

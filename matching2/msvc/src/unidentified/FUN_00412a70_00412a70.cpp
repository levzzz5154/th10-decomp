#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412A70..0x00412A7D: FUN_00412a70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412a70_00412a70() {
    __asm {
    L_00412a70:
        mov eax,dword ptr [eax+14D8h]
    L_00412a76:
        mov eax,dword ptr [eax+4]
    L_00412a79:
        jmp asm_ECL_ResolveFloatDestination_00450070
    }
}

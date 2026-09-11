#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040E770..0x00411D2E: FUN_0040e770
// Naked body preserves the retail register/stack ABI.

// 0x00412A00..0x00412A0F: ?ECL_ResolveIntFromEntity@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveIntFromEntity_00412a00() {
    __asm {
    L_00412a00:
        mov eax,dword ptr [eax+14D8h]
    L_00412a06:
        mov edx,dword ptr [eax+4]
    L_00412a09:
        push ecx
    L_00412a0a:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_00412a0f:
        ret
    }
}

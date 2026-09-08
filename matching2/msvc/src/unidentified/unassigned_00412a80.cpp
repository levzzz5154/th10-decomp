#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412A80..0x00412A90: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412a80() {
    __asm {
    L_00412a80:
        mov eax,dword ptr [eax+14D8h]
    L_00412a86:
        push ecx
    L_00412a87:
        push edx
    L_00412a88:
        mov edx,dword ptr [eax+4]
    L_00412a8b:
        call asm_ECL_ResolveIntValue_0044ff00
    L_00412a90:
        ret
    }
}

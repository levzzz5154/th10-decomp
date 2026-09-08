#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413760..0x0041376C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413760() {
    __asm {
    L_00413760:
        mov eax,dword ptr [eax+9EB4h]
    L_00413766:
        shr eax,4
    L_00413769:
        and eax,1
    L_0041376c:
        ret
    }
}

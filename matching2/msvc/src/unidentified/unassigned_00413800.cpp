#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413800..0x0041380B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413800() {
    __asm {
    L_00413800:
        mov eax,dword ptr [eax+2480h]
    L_00413806:
        not eax
    L_00413808:
        and eax,1
    L_0041380b:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FF40..0x0041FF4C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041ff40() {
    __asm {
    L_0041ff40:
        mov eax,dword ptr [eax+150h]
    L_0041ff46:
        shr eax,4
    L_0041ff49:
        and eax,1
    L_0041ff4c:
        ret
    }
}

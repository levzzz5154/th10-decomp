#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B510..0x0040B518: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b510() {
    __asm {
    L_0040b510:
        mov eax,dword ptr [eax+20h]
    L_0040b513:
        shr eax,1
    L_0040b515:
        and eax,1
    L_0040b518:
        ret
    }
}

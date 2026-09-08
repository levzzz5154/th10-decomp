#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B500..0x0040B506: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b500() {
    __asm {
    L_0040b500:
        mov eax,dword ptr [eax+20h]
    L_0040b503:
        and eax,1
    L_0040b506:
        ret
    }
}

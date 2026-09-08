#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B460..0x0040B468: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b460() {
    __asm {
    L_0040b460:
        mov eax,dword ptr [eax+74h]
    L_0040b463:
        shr eax,1
    L_0040b465:
        and eax,1
    L_0040b468:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B470..0x0040B479: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b470() {
    __asm {
    L_0040b470:
        mov eax,dword ptr [eax+74h]
    L_0040b473:
        shr eax,2
    L_0040b476:
        and eax,1
    L_0040b479:
        ret
    }
}

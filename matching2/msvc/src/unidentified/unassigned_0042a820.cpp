#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A820..0x0042A82D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042a820() {
    __asm {
    L_0042a820:
        mov eax,dword ptr [ecx+6274h]
    L_0042a826:
        sub eax,ecx
    L_0042a828:
        sub eax,5464h
    L_0042a82d:
        ret
    }
}

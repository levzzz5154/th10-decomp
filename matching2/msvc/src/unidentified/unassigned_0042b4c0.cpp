#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B4C0..0x0042B4C6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042b4c0() {
    __asm {
    L_0042b4c0:
        mov eax,ecx
    L_0042b4c2:
        and dword ptr [eax+2Ch],0FFFFFFFEh
    L_0042b4c6:
        ret
    }
}

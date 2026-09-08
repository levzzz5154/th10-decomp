#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C640..0x0044C650: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c640() {
    __asm {
    L_0044c640:
        mov dword ptr [eax+2000h],eax
    L_0044c646:
        mov byte ptr [eax],0
    L_0044c649:
        mov byte ptr [eax+2004h],0
    L_0044c650:
        ret
    }
}

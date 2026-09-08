#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C760..0x0044C766: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c760() {
    __asm {
    L_0044c760:
        mov dword ptr [eax],0
    L_0044c766:
        ret
    }
}

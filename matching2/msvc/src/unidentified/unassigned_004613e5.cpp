#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004613E5..0x004613E7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004613e5() {
    __asm {
    L_004613e5:
        mov ebx,dword ptr [ebp+8]
    }
}

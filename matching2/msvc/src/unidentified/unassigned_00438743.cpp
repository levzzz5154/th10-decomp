#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438743..0x0043874B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438743() {
    __asm {
    L_00438743:
        mov ebx,dword ptr [ebp-18h]
    L_00438746:
        mov esi,dword ptr [ebp-14h]
    L_00438749:
        mov edx,dword ptr [ebp+8]
    }
}

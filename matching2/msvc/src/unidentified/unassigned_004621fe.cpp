#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004621FE..0x00462200: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004621fe() {
    __asm {
    L_004621fe:
        mov ebx,dword ptr [ebp+8]
    }
}

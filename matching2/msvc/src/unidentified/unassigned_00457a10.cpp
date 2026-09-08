#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457A10..0x00457A12: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00457a10() {
    __asm {
    L_00457a10:
        mov esi,dword ptr [ebp+0Ch]
    }
}

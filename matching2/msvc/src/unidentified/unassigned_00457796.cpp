#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457796..0x00457798: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00457796() {
    __asm {
    L_00457796:
        mov esi,dword ptr [ebp-1Ch]
    }
}

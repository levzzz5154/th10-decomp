#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004556B8..0x004556BE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004556b8() {
    __asm {
    L_004556b8:
        xor eax,eax
    L_004556ba:
        inc eax
    L_004556bb:
        ret
    L_004556bc:
        mov esp,dword ptr [ebp-18h]
    }
}

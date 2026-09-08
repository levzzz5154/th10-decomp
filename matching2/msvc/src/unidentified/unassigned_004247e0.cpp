#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004247E0..0x004247E6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004247e0() {
    __asm {
    L_004247e0:
        mov eax,ecx
    L_004247e2:
        and dword ptr [eax+54h],0FFFFFFFEh
    L_004247e6:
        ret
    }
}

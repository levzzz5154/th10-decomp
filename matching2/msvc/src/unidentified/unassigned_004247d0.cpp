#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004247D0..0x004247D9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004247d0() {
    __asm {
    L_004247d0:
        mov eax,ecx
    L_004247d2:
        and dword ptr [eax+80h],0FFFFFFFEh
    L_004247d9:
        ret
    }
}

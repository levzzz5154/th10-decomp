#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004247C0..0x004247C6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004247c0() {
    __asm {
    L_004247c0:
        mov eax,ecx
    L_004247c2:
        and dword ptr [eax+10h],0FFFFFFFEh
    L_004247c6:
        ret
    }
}

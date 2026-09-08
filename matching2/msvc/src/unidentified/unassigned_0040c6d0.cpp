#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C6D0..0x0040C6DD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c6d0() {
    __asm {
    L_0040c6d0:
        mov eax,dword ptr [eax+4]
    L_0040c6d3:
        fld dword ptr [eax]
    L_0040c6d5:
        fsub dword ptr [esp+4]
    L_0040c6d9:
        fstp dword ptr [eax]
    L_0040c6db:
        ret 4
    }
}

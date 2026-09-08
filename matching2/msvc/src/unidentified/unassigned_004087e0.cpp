#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004087E0..0x004087F8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004087e0() {
    __asm {
    L_004087e0:
        fld dword ptr [ecx]
    L_004087e2:
        fadd dword ptr [eax]
    L_004087e4:
        fstp dword ptr [eax]
    L_004087e6:
        fld dword ptr [ecx+4]
    L_004087e9:
        fadd dword ptr [eax+4]
    L_004087ec:
        fstp dword ptr [eax+4]
    L_004087ef:
        fld dword ptr [ecx+8]
    L_004087f2:
        fadd dword ptr [eax+8]
    L_004087f5:
        fstp dword ptr [eax+8]
    L_004087f8:
        ret
    }
}

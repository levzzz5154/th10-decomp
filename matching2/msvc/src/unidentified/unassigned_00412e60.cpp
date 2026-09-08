#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412E60..0x00412E6F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412e60() {
    __asm {
    L_00412e60:
        fld dword ptr [ecx+4]
    L_00412e63:
        fadd dword ptr [edx+4]
    L_00412e66:
        fld dword ptr [ecx]
    L_00412e68:
        fadd dword ptr [edx]
    L_00412e6a:
        fstp dword ptr [eax]
    L_00412e6c:
        fstp dword ptr [eax+4]
    L_00412e6f:
        ret
    }
}

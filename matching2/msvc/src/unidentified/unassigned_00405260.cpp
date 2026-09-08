#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405260..0x00405278: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405260() {
    __asm {
    L_00405260:
        fld dword ptr [ecx+8]
    L_00405263:
        fadd dword ptr [edx+8]
    L_00405266:
        fld dword ptr [ecx+4]
    L_00405269:
        fadd dword ptr [edx+4]
    L_0040526c:
        fld dword ptr [ecx]
    L_0040526e:
        fadd dword ptr [edx]
    L_00405270:
        fstp dword ptr [eax]
    L_00405272:
        fstp dword ptr [eax+4]
    L_00405275:
        fstp dword ptr [eax+8]
    L_00405278:
        ret
    }
}

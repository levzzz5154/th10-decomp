#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405B40..0x00405B58: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405b40() {
    __asm {
    L_00405b40:
        fld dword ptr [ecx+4]
    L_00405b43:
        fsub dword ptr [eax+4]
    L_00405b46:
        fld dword ptr [ecx]
    L_00405b48:
        fsub dword ptr [eax]
    L_00405b4a:
        fld st(0)
    L_00405b4c:
        fmul st,st(1)
    L_00405b4e:
        fld st(2)
    L_00405b50:
        fmul st,st(3)
    L_00405b52:
        faddp st(1),st
    L_00405b54:
        fstp st(2)
    L_00405b56:
        fstp st(0)
    L_00405b58:
        ret
    }
}

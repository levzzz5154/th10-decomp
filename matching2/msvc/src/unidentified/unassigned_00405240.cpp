#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405240..0x00405258: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405240() {
    __asm {
    L_00405240:
        fld dword ptr [edx+8]
    L_00405243:
        fsub dword ptr [ecx+8]
    L_00405246:
        fld dword ptr [edx+4]
    L_00405249:
        fsub dword ptr [ecx+4]
    L_0040524c:
        fld dword ptr [edx]
    L_0040524e:
        fsub dword ptr [ecx]
    L_00405250:
        fstp dword ptr [eax]
    L_00405252:
        fstp dword ptr [eax+4]
    L_00405255:
        fstp dword ptr [eax+8]
    L_00405258:
        ret
    }
}

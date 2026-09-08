#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042ABD0..0x0042AC06: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042abd0() {
    __asm {
    L_0042abd0:
        mov ecx,dword ptr [eax+627Ch]
    L_0042abd6:
        xor edx,edx
    L_0042abd8:
        cmp ecx,edx
    L_0042abda:
        push esi
    L_0042abdb:
        je short L_0042abe6
    L_0042abdd:
        mov esi,dword ptr [eax+6280h]
    L_0042abe3:
        mov dword ptr [ecx+8],esi
    L_0042abe6:
        mov ecx,dword ptr [eax+6280h]
    L_0042abec:
        cmp ecx,edx
    L_0042abee:
        je short L_0042abf9
    L_0042abf0:
        mov esi,dword ptr [eax+627Ch]
    L_0042abf6:
        mov dword ptr [ecx+4],esi
    L_0042abf9:
        mov dword ptr [eax+627Ch],edx
    L_0042abff:
        mov dword ptr [eax+6280h],edx
    L_0042ac05:
        pop esi
    L_0042ac06:
        ret
    }
}

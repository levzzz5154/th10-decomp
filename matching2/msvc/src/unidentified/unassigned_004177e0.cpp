#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004177E0..0x004177F8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004177e0() {
    __asm {
    L_004177e0:
        mov eax,dword ptr [ecx+8]
    L_004177e3:
        push esi
    L_004177e4:
        mov esi,dword ptr [eax+4]
    L_004177e7:
        mov edx,2
    L_004177ec:
        or esi,edx
    L_004177ee:
        mov dword ptr [eax+4],esi
    L_004177f1:
        mov eax,dword ptr [ecx+0Ch]
    L_004177f4:
        or dword ptr [eax+4],edx
    L_004177f7:
        pop esi
    L_004177f8:
        ret
    }
}

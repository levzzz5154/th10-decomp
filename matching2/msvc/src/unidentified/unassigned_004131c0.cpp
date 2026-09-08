#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004131C0..0x004131E4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004131c0() {
    __asm {
    L_004131c0:
        mov ecx,dword ptr [eax+4]
    L_004131c3:
        xor edx,edx
    L_004131c5:
        cmp ecx,edx
    L_004131c7:
        push esi
    L_004131c8:
        je short L_004131d0
    L_004131ca:
        mov esi,dword ptr [eax+8]
    L_004131cd:
        mov dword ptr [ecx+8],esi
    L_004131d0:
        mov ecx,dword ptr [eax+8]
    L_004131d3:
        cmp ecx,edx
    L_004131d5:
        je short L_004131dd
    L_004131d7:
        mov esi,dword ptr [eax+4]
    L_004131da:
        mov dword ptr [ecx+4],esi
    L_004131dd:
        mov dword ptr [eax+4],edx
    L_004131e0:
        mov dword ptr [eax+8],edx
    L_004131e3:
        pop esi
    L_004131e4:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FF00..0x0041FF21: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041ff00() {
    __asm {
    L_0041ff00:
        mov ecx,dword ptr [eax+0Ch]
    L_0041ff03:
        push esi
    L_0041ff04:
        mov esi,dword ptr [ecx+4]
    L_0041ff07:
        mov edx,2
    L_0041ff0c:
        or esi,edx
    L_0041ff0e:
        mov dword ptr [ecx+4],esi
    L_0041ff11:
        mov ecx,dword ptr [eax+10h]
    L_0041ff14:
        or dword ptr [ecx+4],edx
    L_0041ff17:
        mov eax,dword ptr [eax+89A8h]
    L_0041ff1d:
        or dword ptr [eax+4],edx
    L_0041ff20:
        pop esi
    L_0041ff21:
        ret
    }
}

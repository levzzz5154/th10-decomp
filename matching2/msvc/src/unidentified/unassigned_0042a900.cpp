#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A900..0x0042A925: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042a900() {
    __asm {
    L_0042a900:
        mov ecx,dword ptr [eax+6274h]
    L_0042a906:
        mov byte ptr [ecx],dl
    L_0042a908:
        mov ecx,dword ptr [eax+6274h]
    L_0042a90e:
        inc ecx
    L_0042a90f:
        mov dword ptr [eax+6274h],ecx
    L_0042a915:
        sub ecx,eax
    L_0042a917:
        sub ecx,5464h
    L_0042a91d:
        xor eax,eax
    L_0042a91f:
        cmp ecx,78h
    L_0042a922:
        setge al
    L_0042a925:
        ret
    }
}

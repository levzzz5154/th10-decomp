#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041F820..0x0041F832: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041f820() {
    __asm {
    L_0041f820:
        mov ecx,dword ptr [eax+35Ch]
    L_0041f826:
        and ecx,0FFFFFFDFh
    L_0041f829:
        or ecx,10h
    L_0041f82c:
        mov dword ptr [eax+35Ch],ecx
    L_0041f832:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C590..0x0040C5A0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c590() {
    __asm {
    L_0040c590:
        mov edx,dword ptr [ecx]
    L_0040c592:
        mov ecx,dword ptr [esp+4]
    L_0040c596:
        xor eax,eax
    L_0040c598:
        cmp edx,ecx
    L_0040c59a:
        sete al
    L_0040c59d:
        ret 4
    L_0040c5a0:
        ret
    }
}

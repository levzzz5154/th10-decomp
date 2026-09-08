#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441590..0x004415BB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441590() {
    __asm {
    L_00441590:
        test eax,eax
    L_00441592:
        push esi
    L_00441593:
        mov esi,ecx
    L_00441595:
        je short L_004415ba
    L_00441597:
        push edi
    L_00441598:
        mov edi,eax
    L_0044159a:
        lea ebx,[ebx+force_disp32_zero]
    L_004415a0:
        cmp word ptr [esi+38Ah],0
    L_004415a8:
        jl short L_004415b0
    L_004415aa:
        push esi
    L_004415ab:
        call asm_FUN_0043ee30_0043ee30
    L_004415b0:
        add esi,3ACh
    L_004415b6:
        dec edi
    L_004415b7:
        jne short L_004415a0
    L_004415b9:
        pop edi
    L_004415ba:
        pop esi
    L_004415bb:
        ret
    }
}

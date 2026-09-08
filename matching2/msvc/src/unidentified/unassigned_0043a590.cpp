#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A590..0x0043A5BE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a590() {
    __asm {
    L_0043a590:
        push ecx
    L_0043a591:
        mov eax,dword ptr [eax]
    L_0043a593:
        test eax,eax
    L_0043a595:
        jne short L_0043a59b
    L_0043a597:
        pop ecx
    L_0043a598:
        ret 4
    L_0043a59b:
        mov byte ptr [esp],cl
    L_0043a59e:
        mov cl,byte ptr [esp+8]
    L_0043a5a2:
        mov byte ptr [esp+1],dl
    L_0043a5a6:
        mov byte ptr [esp+2],cl
    L_0043a5aa:
        mov edx,dword ptr [esp]
    L_0043a5ad:
        push edx
    L_0043a5ae:
        push eax
    L_0043a5af:
        call dword ptr [data_00466298]
    L_0043a5b5:
        neg eax
    L_0043a5b7:
        sbb eax,eax
    L_0043a5b9:
        neg eax
    L_0043a5bb:
        pop ecx
    L_0043a5bc:
        ret 4
    }
}

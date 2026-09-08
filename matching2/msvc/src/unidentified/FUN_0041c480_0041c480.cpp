#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C480..0x0041C4DA: FUN_0041c480
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c480_0041c480() {
    __asm {
    L_0041c480:
        push ecx
    L_0041c481:
        mov edx,dword ptr [data_00477810]
    L_0041c487:
        mov eax,dword ptr [edx+58h]
    L_0041c48a:
        push edi
    L_0041c48b:
        mov edi,ecx
    L_0041c48d:
        mov ecx,eax
    L_0041c48f:
        shr ecx,2
    L_0041c492:
        or ecx,eax
    L_0041c494:
        test cl,1
    L_0041c497:
        jne short L_0041c4a0
    L_0041c499:
        mov edx,eax
    L_0041c49b:
        test dh,4
    L_0041c49e:
        je short L_0041c4a8
    L_0041c4a0:
        mov eax,1
    L_0041c4a5:
        pop edi
    L_0041c4a6:
        pop ecx
    L_0041c4a7:
        ret
    L_0041c4a8:
        test dl,2
    L_0041c4ab:
        je short L_0041c4d3
    L_0041c4ad:
        mov edx,dword ptr [data_00476f78]
    L_0041c4b3:
        mov dword ptr [esp+4],edx
    L_0041c4b7:
        mov dword ptr [data_00476f78],0
    L_0041c4c1:
        call asm_FUN_0041c330_0041c330
    L_0041c4c6:
        mov ecx,dword ptr [esp+4]
    L_0041c4ca:
        mov dword ptr [data_00476f78],ecx
    L_0041c4d0:
        pop edi
    L_0041c4d1:
        pop ecx
    L_0041c4d2:
        ret
    L_0041c4d3:
        call asm_FUN_0041c330_0041c330
    L_0041c4d8:
        pop edi
    L_0041c4d9:
        pop ecx
    L_0041c4da:
        ret
    }
}

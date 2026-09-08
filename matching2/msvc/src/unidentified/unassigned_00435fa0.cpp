#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435FA0..0x00435FC3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00435fa0() {
    __asm {
    L_00435fa0:
        mov dword ptr [data_0048f860],eax
    L_00435fa5:
        lea eax,[eax+eax*2]
    L_00435fa8:
        shl eax,2
    L_00435fab:
        xor ecx,ecx
    L_00435fad:
        mov dword ptr [eax+477858h],2000h
    L_00435fb7:
        mov dword ptr [eax+477860h],ecx
    L_00435fbd:
        mov dword ptr [eax+47785Ch],ecx
    L_00435fc3:
        ret
    }
}

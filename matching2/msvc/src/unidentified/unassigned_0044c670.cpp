#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C670..0x0044C6A3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c670() {
    __asm {
    L_0044c670:
        mov eax,ecx
    L_0044c672:
        or ecx,0FFFFFFFFh
    L_0044c675:
        mov word ptr [eax+58h],0
    L_0044c67b:
        mov word ptr [eax+5Ah],1
    L_0044c681:
        mov word ptr [eax+5Ch],2
    L_0044c687:
        mov word ptr [eax+5Eh],3
    L_0044c68d:
        mov word ptr [eax+60h],cx
    L_0044c691:
        mov word ptr [eax+62h],cx
    L_0044c695:
        mov word ptr [eax+64h],cx
    L_0044c699:
        mov word ptr [eax+66h],cx
    L_0044c69d:
        mov word ptr [eax+68h],4
    L_0044c6a3:
        ret
    }
}

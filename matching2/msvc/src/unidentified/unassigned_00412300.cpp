#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412300..0x0041233F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412300() {
    __asm {
    L_00412300:
        mov eax,dword ptr [esp+4]
    L_00412304:
        add eax,2701h
    L_00412309:
        cmp eax,3
    L_0041230c:
        ja short L_00412339
    L_0041230e:
        jmp dword ptr [eax*4+412340h]
    L_00412315:
        lea eax,[ecx+1138h]
    L_0041231b:
        ret 4
    L_0041231e:
        lea eax,[ecx+113Ch]
    L_00412324:
        ret 4
    L_00412327:
        lea eax,[ecx+1140h]
    L_0041232d:
        ret 4
    L_00412330:
        lea eax,[ecx+1144h]
    L_00412336:
        ret 4
    L_00412339:
        xor eax,eax
    L_0041233b:
        ret 4
    L_0041233e:
        mov edi,edi
    }
}

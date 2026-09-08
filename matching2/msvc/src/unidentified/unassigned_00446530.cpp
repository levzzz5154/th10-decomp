#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446530..0x00446566: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00446530() {
    __asm {
    L_00446530:
        xor ecx,ecx
    L_00446532:
        mov cx,word ptr [edx]
    L_00446535:
        test ch,ch
    L_00446537:
        jns short L_00446566
    L_00446539:
        shr ecx,0Ah
    L_0044653c:
        and ecx,1Fh
    L_0044653f:
        push edi
    L_00446540:
        add dword ptr [eax],ecx
    L_00446542:
        mov edi,dword ptr [eax+4]
    L_00446545:
        xor ecx,ecx
    L_00446547:
        mov cx,word ptr [edx]
    L_0044654a:
        shr ecx,5
    L_0044654d:
        and ecx,1Fh
    L_00446550:
        add edi,ecx
    L_00446552:
        mov ecx,dword ptr [eax+8]
    L_00446555:
        mov dword ptr [eax+4],edi
    L_00446558:
        movzx edx,byte ptr [edx]
    L_0044655b:
        and edx,1Fh
    L_0044655e:
        add ecx,edx
    L_00446560:
        mov dword ptr [eax+8],ecx
    L_00446563:
        inc dword ptr [esi]
    L_00446565:
        pop edi
    L_00446566:
        ret
    }
}

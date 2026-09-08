#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446570..0x004465A6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00446570() {
    __asm {
    L_00446570:
        xor ecx,ecx
    L_00446572:
        mov cx,word ptr [edx]
    L_00446575:
        test ch,0F0h
    L_00446578:
        je short L_004465a6
    L_0044657a:
        shr ecx,8
    L_0044657d:
        and ecx,0Fh
    L_00446580:
        push edi
    L_00446581:
        add dword ptr [eax],ecx
    L_00446583:
        mov edi,dword ptr [eax+4]
    L_00446586:
        xor ecx,ecx
    L_00446588:
        mov cl,byte ptr [edx]
    L_0044658a:
        shr ecx,4
    L_0044658d:
        and ecx,0Fh
    L_00446590:
        add edi,ecx
    L_00446592:
        mov ecx,dword ptr [eax+8]
    L_00446595:
        mov dword ptr [eax+4],edi
    L_00446598:
        movzx edx,byte ptr [edx]
    L_0044659b:
        and edx,0Fh
    L_0044659e:
        add ecx,edx
    L_004465a0:
        mov dword ptr [eax+8],ecx
    L_004465a3:
        inc dword ptr [esi]
    L_004465a5:
        pop edi
    L_004465a6:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004126D0..0x0041270F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004126d0() {
    __asm {
    L_004126d0:
        mov eax,dword ptr [esp+4]
    L_004126d4:
        add eax,26FDh
    L_004126d9:
        cmp eax,3
    L_004126dc:
        ja short L_00412709
    L_004126de:
        jmp dword ptr [eax*4+412710h]
    L_004126e5:
        lea eax,[ecx+1148h]
    L_004126eb:
        ret 4
    L_004126ee:
        lea eax,[ecx+114Ch]
    L_004126f4:
        ret 4
    L_004126f7:
        lea eax,[ecx+1150h]
    L_004126fd:
        ret 4
    L_00412700:
        lea eax,[ecx+1154h]
    L_00412706:
        ret 4
    L_00412709:
        xor eax,eax
    L_0041270b:
        ret 4
    L_0041270e:
        mov edi,edi
    }
}

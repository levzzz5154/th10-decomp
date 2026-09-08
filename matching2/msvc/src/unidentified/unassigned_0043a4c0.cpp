#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A4C0..0x0043A503: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a4c0() {
    __asm {
    L_0043a4c0:
        mov eax,dword ptr [esi]
    L_0043a4c2:
        test eax,eax
    L_0043a4c4:
        je short L_0043a4e1
    L_0043a4c6:
        cmp dword ptr [esi+4],edi
    L_0043a4c9:
        je short L_0043a501
    L_0043a4cb:
        push eax
    L_0043a4cc:
        call dword ptr [data_004662a8]
    L_0043a4d2:
        mov eax,dword ptr [esi]
    L_0043a4d4:
        push eax
    L_0043a4d5:
        call dword ptr [data_004662a4]
    L_0043a4db:
        mov dword ptr [esi],0
    L_0043a4e1:
        push 10000h
    L_0043a4e6:
        push 0
    L_0043a4e8:
        mov dword ptr [esi+4],edi
    L_0043a4eb:
        mov ecx,dword ptr [data_00491c70]
    L_0043a4f1:
        push ecx
    L_0043a4f2:
        push edi
    L_0043a4f3:
        push esi
    L_0043a4f4:
        call dword ptr [data_004662ac]
    L_0043a4fa:
        neg eax
    L_0043a4fc:
        sbb eax,eax
    L_0043a4fe:
        neg eax
    L_0043a500:
        ret
    L_0043a501:
        xor eax,eax
    L_0043a503:
        ret
    }
}

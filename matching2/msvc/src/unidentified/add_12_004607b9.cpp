#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004607B9..0x00460816: ___add_12
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_add_12_004607b9() {
    __asm {
    L_004607b9:
        push esi
    L_004607ba:
        mov esi,dword ptr [esp+8]
    L_004607be:
        push edi
    L_004607bf:
        mov edi,dword ptr [esp+10h]
    L_004607c3:
        push esi
    L_004607c4:
        push dword ptr [edi]
    L_004607c6:
        push dword ptr [esi]
    L_004607c8:
        call asm_addl_00460798
    L_004607cd:
        add esp,0Ch
    L_004607d0:
        test eax,eax
    L_004607d2:
        je short L_004607eb
    L_004607d4:
        lea eax,[esi+4]
    L_004607d7:
        push eax
    L_004607d8:
        push 1
    L_004607da:
        push dword ptr [eax]
    L_004607dc:
        call asm_addl_00460798
    L_004607e1:
        add esp,0Ch
    L_004607e4:
        test eax,eax
    L_004607e6:
        je short L_004607eb
    L_004607e8:
        inc dword ptr [esi+8]
    L_004607eb:
        lea eax,[esi+4]
    L_004607ee:
        push eax
    L_004607ef:
        push dword ptr [edi+4]
    L_004607f2:
        push dword ptr [eax]
    L_004607f4:
        call asm_addl_00460798
    L_004607f9:
        add esp,0Ch
    L_004607fc:
        test eax,eax
    L_004607fe:
        je short L_00460803
    L_00460800:
        inc dword ptr [esi+8]
    L_00460803:
        lea eax,[esi+8]
    L_00460806:
        push eax
    L_00460807:
        push dword ptr [edi+8]
    L_0046080a:
        push dword ptr [eax]
    L_0046080c:
        call asm_addl_00460798
    L_00460811:
        add esp,0Ch
    L_00460814:
        pop edi
    L_00460815:
        pop esi
    L_00460816:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A620..0x0043A6AC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a620() {
    __asm {
    L_0043a620:
        mov eax,dword ptr [esi+4]
    L_0043a623:
        test eax,eax
    L_0043a625:
        mov dword ptr [esi],46F810h
    L_0043a62b:
        je short L_0043a634
    L_0043a62d:
        push eax
    L_0043a62e:
        call dword ptr [data_00466288]
    L_0043a634:
        mov eax,dword ptr [esi+8]
    L_0043a637:
        push edi
    L_0043a638:
        mov edi,dword ptr [data_00466274]
    L_0043a63e:
        push eax
    L_0043a63f:
        call edi
    L_0043a641:
        mov ecx,dword ptr [esi+8]
    L_0043a644:
        push ecx
    L_0043a645:
        mov dword ptr [esi+4],0
    L_0043a64c:
        call edi
    L_0043a64e:
        pop edi
    L_0043a64f:
        ret
    L_0043a650:
        mov eax,dword ptr [esi+4]
    L_0043a653:
        test eax,eax
    L_0043a655:
        je short L_0043a65e
    L_0043a657:
        push eax
    L_0043a658:
        call dword ptr [data_00466288]
    L_0043a65e:
        mov eax,dword ptr [esi+8]
    L_0043a661:
        push eax
    L_0043a662:
        call dword ptr [data_00466274]
    L_0043a668:
        mov ecx,dword ptr [esi+8]
    L_0043a66b:
        push ecx
    L_0043a66c:
        mov dword ptr [esi+4],0
    L_0043a673:
        call dword ptr [data_00466278]
    L_0043a679:
        test edi,edi
    L_0043a67b:
        push 1
    L_0043a67d:
        je short L_0043a696
    L_0043a67f:
        mov edx,dword ptr [esp+8]
    L_0043a683:
        mov eax,dword ptr [esi+8]
    L_0043a686:
        push edx
    L_0043a687:
        push edi
    L_0043a688:
        push eax
    L_0043a689:
        push ebx
    L_0043a68a:
        call dword ptr [data_0046628c]
    L_0043a690:
        mov dword ptr [esi+4],eax
    L_0043a693:
        ret 4
    L_0043a696:
        mov ecx,dword ptr [esi+8]
    L_0043a699:
        push esi
    L_0043a69a:
        push 43A6E0h
    L_0043a69f:
        push ecx
    L_0043a6a0:
        push ebx
    L_0043a6a1:
        call dword ptr [data_0046628c]
    L_0043a6a7:
        mov dword ptr [esi+4],eax
    L_0043a6aa:
        ret 4
    }
}

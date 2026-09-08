#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043B840..0x0043B880: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043b840() {
    __asm {
    L_0043b840:
        mov eax,dword ptr [esi+4]
    L_0043b843:
        test eax,eax
    L_0043b845:
        je short L_0043b84e
    L_0043b847:
        push eax
    L_0043b848:
        call dword ptr [data_00466288]
    L_0043b84e:
        mov eax,dword ptr [esi+8]
    L_0043b851:
        push eax
    L_0043b852:
        call dword ptr [data_00466274]
    L_0043b858:
        mov ecx,dword ptr [esi+8]
    L_0043b85b:
        push ecx
    L_0043b85c:
        mov dword ptr [esi+4],0
    L_0043b863:
        call dword ptr [data_00466278]
    L_0043b869:
        mov edx,dword ptr [esi+8]
    L_0043b86c:
        push 1
    L_0043b86e:
        push esi
    L_0043b86f:
        push 43A6E0h
    L_0043b874:
        push edx
    L_0043b875:
        push 10h
    L_0043b877:
        call dword ptr [data_0046628c]
    L_0043b87d:
        mov dword ptr [esi+4],eax
    L_0043b880:
        ret
    }
}

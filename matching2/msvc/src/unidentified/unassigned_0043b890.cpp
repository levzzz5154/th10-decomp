#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043B890..0x0043B8B0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043b890() {
    __asm {
    L_0043b890:
        mov eax,dword ptr [esi+4]
    L_0043b893:
        test eax,eax
    L_0043b895:
        je short L_0043b89e
    L_0043b897:
        push eax
    L_0043b898:
        call dword ptr [data_00466288]
    L_0043b89e:
        mov eax,dword ptr [esi+8]
    L_0043b8a1:
        push eax
    L_0043b8a2:
        call dword ptr [data_00466274]
    L_0043b8a8:
        mov dword ptr [esi+4],0
    L_0043b8af:
        ret
    L_0043b8b0:
        ret
    }
}

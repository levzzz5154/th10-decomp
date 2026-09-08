#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00447910..0x00447939: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00447910() {
    __asm {
    L_00447910:
        mov eax,dword ptr [esi]
    L_00447912:
        test eax,eax
    L_00447914:
        je short L_00447922
    L_00447916:
        mov ecx,dword ptr [eax]
    L_00447918:
        push eax
    L_00447919:
        call dword ptr [ecx+8]
    L_0044791c:
        mov dword ptr [esi],0
    L_00447922:
        mov eax,dword ptr [esi+4]
    L_00447925:
        test eax,eax
    L_00447927:
        je short L_00447939
    L_00447929:
        push eax
    L_0044792a:
        call asm_free_00452422
    L_0044792f:
        add esp,4
    L_00447932:
        mov dword ptr [esi+4],0
    L_00447939:
        ret
    }
}

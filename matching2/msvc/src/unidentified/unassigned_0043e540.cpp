#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043E540..0x0043E55F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043e540() {
    __asm {
    L_0043e540:
        mov eax,dword ptr [edi+esi*4+1EC0h]
    L_0043e547:
        test eax,eax
    L_0043e549:
        je short L_0043e55f
    L_0043e54b:
        push eax
    L_0043e54c:
        call asm_free_00452422
    L_0043e551:
        add esp,4
    L_0043e554:
        mov dword ptr [edi+esi*4+1EC0h],0
    L_0043e55f:
        ret
    }
}

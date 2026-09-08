#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C860..0x0040C883: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c860() {
    __asm {
    L_0040c860:
        mov eax,dword ptr [esi+8Ch]
    L_0040c866:
        test eax,eax
    L_0040c868:
        mov dword ptr [esi],46D0F0h
    L_0040c86e:
        je short L_0040c883
    L_0040c870:
        push eax
    L_0040c871:
        call asm_free_00452422
    L_0040c876:
        add esp,4
    L_0040c879:
        mov dword ptr [esi+8Ch],0
    L_0040c883:
        ret
    }
}

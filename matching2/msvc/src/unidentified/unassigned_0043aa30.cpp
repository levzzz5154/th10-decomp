#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043AA30..0x0043AA5A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043aa30() {
    __asm {
    L_0043aa30:
        mov eax,dword ptr [edi+esi*4+98h]
    L_0043aa37:
        test eax,eax
    L_0043aa39:
        je short L_0043aa4f
    L_0043aa3b:
        push eax
    L_0043aa3c:
        call asm_free_00452422
    L_0043aa41:
        add esp,4
    L_0043aa44:
        mov dword ptr [edi+esi*4+98h],0
    L_0043aa4f:
        mov dword ptr [edi+esi*4+98h],0
    L_0043aa5a:
        ret
    }
}

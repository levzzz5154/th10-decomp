#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AEF0..0x0042AF1C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042aef0() {
    __asm {
    L_0042aef0:
        mov eax,dword ptr [esi]
    L_0042aef2:
        test eax,eax
    L_0042aef4:
        je short L_0042af05
    L_0042aef6:
        push eax
    L_0042aef7:
        call asm_free_00452422
    L_0042aefc:
        add esp,4
    L_0042aeff:
        mov dword ptr [esi],0
    L_0042af05:
        mov eax,dword ptr [esi+4]
    L_0042af08:
        test eax,eax
    L_0042af0a:
        je short L_0042af1c
    L_0042af0c:
        push eax
    L_0042af0d:
        call asm_free_00452422
    L_0042af12:
        add esp,4
    L_0042af15:
        mov dword ptr [esi+4],0
    L_0042af1c:
        ret
    }
}

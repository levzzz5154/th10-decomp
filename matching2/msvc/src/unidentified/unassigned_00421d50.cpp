#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421D50..0x00421D6A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421d50() {
    __asm {
    L_00421d50:
        mov eax,dword ptr [esi+3ADA74h]
    L_00421d56:
        test eax,eax
    L_00421d58:
        je short L_00421d6a
    L_00421d5a:
        mov ecx,dword ptr [eax]
    L_00421d5c:
        push eax
    L_00421d5d:
        call dword ptr [ecx+8]
    L_00421d60:
        mov dword ptr [esi+3ADA74h],0
    L_00421d6a:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438A10..0x00438A24: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438a10() {
    __asm {
    L_00438a10:
        mov eax,dword ptr [esi+8]
    L_00438a13:
        test eax,eax
    L_00438a15:
        je short L_00438a24
    L_00438a17:
        mov ecx,dword ptr [eax]
    L_00438a19:
        push eax
    L_00438a1a:
        call dword ptr [ecx+8]
    L_00438a1d:
        mov dword ptr [esi+8],0
    L_00438a24:
        ret
    }
}

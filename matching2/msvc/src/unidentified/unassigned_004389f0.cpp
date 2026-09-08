#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004389F0..0x00438A04: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004389f0() {
    __asm {
    L_004389f0:
        mov eax,dword ptr [esi+4]
    L_004389f3:
        test eax,eax
    L_004389f5:
        je short L_00438a04
    L_004389f7:
        mov ecx,dword ptr [eax]
    L_004389f9:
        push eax
    L_004389fa:
        call dword ptr [ecx+8]
    L_004389fd:
        mov dword ptr [esi+4],0
    L_00438a04:
        ret
    }
}

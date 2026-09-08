#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A600..0x0043A61B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a600() {
    __asm {
    L_0043a600:
        push 8
    L_0043a602:
        lea eax,[esi+8]
    L_0043a605:
        push eax
    L_0043a606:
        mov dword ptr [esi],46F810h
    L_0043a60c:
        call dword ptr [data_00466290]
    L_0043a612:
        mov dword ptr [esi+4],0
    L_0043a619:
        mov eax,esi
    L_0043a61b:
        ret
    }
}

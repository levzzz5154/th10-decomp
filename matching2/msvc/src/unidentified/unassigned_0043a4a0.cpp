#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A4A0..0x0043A4BC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a4a0() {
    __asm {
    L_0043a4a0:
        mov eax,dword ptr [esi]
    L_0043a4a2:
        test eax,eax
    L_0043a4a4:
        je short L_0043a4bc
    L_0043a4a6:
        push eax
    L_0043a4a7:
        call dword ptr [data_004662a8]
    L_0043a4ad:
        mov eax,dword ptr [esi]
    L_0043a4af:
        push eax
    L_0043a4b0:
        call dword ptr [data_004662a4]
    L_0043a4b6:
        mov dword ptr [esi],0
    L_0043a4bc:
        ret
    }
}

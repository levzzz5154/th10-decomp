#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A570..0x0043A585: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a570() {
    __asm {
    L_0043a570:
        mov eax,dword ptr [eax]
    L_0043a572:
        test eax,eax
    L_0043a574:
        jne short L_0043a577
    L_0043a576:
        ret
    L_0043a577:
        push ecx
    L_0043a578:
        push eax
    L_0043a579:
        call dword ptr [data_00466298]
    L_0043a57f:
        neg eax
    L_0043a581:
        sbb eax,eax
    L_0043a583:
        neg eax
    L_0043a585:
        ret
    }
}

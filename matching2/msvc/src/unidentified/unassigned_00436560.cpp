#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436560..0x00436568: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436560() {
    __asm {
    L_00436560:
        mov eax,dword ptr [eax]
    L_00436562:
        test eax,eax
    L_00436564:
        jge short L_00436568
    L_00436566:
        neg eax
    L_00436568:
        ret
    }
}

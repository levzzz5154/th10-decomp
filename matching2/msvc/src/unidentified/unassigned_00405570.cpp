#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405570..0x0040557E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405570() {
    __asm {
    L_00405570:
        mov edx,dword ptr [ecx+3738h]
    L_00405576:
        xor eax,eax
    L_00405578:
        cmp edx,3Ch
    L_0040557b:
        setge al
    L_0040557e:
        ret
    }
}

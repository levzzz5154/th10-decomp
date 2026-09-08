#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004369C0..0x004369D3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004369c0() {
    __asm {
    L_004369c0:
        mov eax,dword ptr [esi]
    L_004369c2:
        test eax,eax
    L_004369c4:
        je short L_004369d3
    L_004369c6:
        push eax
    L_004369c7:
        call dword ptr [data_00466030]
    L_004369cd:
        mov dword ptr [esi],0
    L_004369d3:
        ret
    }
}

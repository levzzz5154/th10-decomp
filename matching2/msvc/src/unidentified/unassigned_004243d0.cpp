#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004243D0..0x004243DE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004243d0() {
    __asm {
    L_004243d0:
        neg eax
    L_004243d2:
        push eax
    L_004243d3:
        mov eax,dword ptr [esp+8]
    L_004243d7:
        call asm_MenuCursor_Advance_0044bea0
    L_004243dc:
        ret 4
    }
}

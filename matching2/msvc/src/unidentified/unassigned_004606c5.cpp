#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004606C5..0x004606DE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004606c5() {
    __asm {
    L_004606c5:
        mov ecx,dword ptr [esp+8]
    L_004606c9:
        mov eax,dword ptr [esp+4]
    L_004606cd:
        push 0
    L_004606cf:
        push dword ptr [esp+10h]
    L_004606d3:
        call asm_xtoa_00460636
    L_004606d8:
        mov eax,dword ptr [esp+10h]
    L_004606dc:
        pop ecx
    L_004606dd:
        pop ecx
    L_004606de:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404D10..0x00404D29: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404d10() {
    __asm {
    L_00404d10:
        fild dword ptr [eax+84h]
    L_00404d16:
        push ecx
    L_00404d17:
        mov ecx,dword ptr [eax+78h]
    L_00404d1a:
        mov eax,dword ptr [eax+88h]
    L_00404d20:
        fstp dword ptr [esp]
    L_00404d23:
        push ecx
    L_00404d24:
        call asm_FUN_0044c350_0044c350
    L_00404d29:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045370E..0x0045371A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045370e() {
    __asm {
    L_0045370e:
        call asm_getptd_00456357
    L_00453713:
        mov ecx,dword ptr [esp+4]
    L_00453717:
        mov dword ptr [eax+14h],ecx
    L_0045371a:
        ret
    }
}

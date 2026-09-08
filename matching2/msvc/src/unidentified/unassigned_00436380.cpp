#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436380..0x00436391: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436380() {
    __asm {
    L_00436380:
        xor ecx,ecx
    L_00436382:
        mov dword ptr [eax],46F308h
    L_00436388:
        mov dword ptr [eax+4],ecx
    L_0043638b:
        mov dword ptr [eax+8],ecx
    L_0043638e:
        mov dword ptr [eax+0Ch],ecx
    L_00436391:
        ret
    }
}

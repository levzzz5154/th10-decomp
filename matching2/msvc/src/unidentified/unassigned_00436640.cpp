#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436640..0x00436651: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436640() {
    __asm {
    L_00436640:
        xor ecx,ecx
    L_00436642:
        mov dword ptr [eax+4],ecx
    L_00436645:
        mov dword ptr [eax+8],ecx
    L_00436648:
        mov dword ptr [eax+0Ch],ecx
    L_0043664b:
        mov dword ptr [eax],46F328h
    L_00436651:
        ret
    }
}

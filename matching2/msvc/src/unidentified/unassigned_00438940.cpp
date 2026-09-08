#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438940..0x00438949: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438940() {
    __asm {
    L_00438940:
        mov dword ptr [eax+2000h],eax
    L_00438946:
        mov byte ptr [eax],0
    L_00438949:
        ret
    }
}

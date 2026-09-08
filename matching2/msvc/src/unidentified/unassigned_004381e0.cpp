#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004381E0..0x004381EF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004381e0() {
    __asm {
    L_004381e0:
        xor ecx,ecx
    L_004381e2:
        mov dword ptr [eax+18h],0Fh
    L_004381e9:
        mov dword ptr [eax+14h],ecx
    L_004381ec:
        mov byte ptr [eax+4],cl
    L_004381ef:
        ret
    }
}

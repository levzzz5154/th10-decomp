#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C710..0x0040C724: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c710() {
    __asm {
    L_0040c710:
        xor ecx,ecx
    L_0040c712:
        mov dword ptr [eax],46D0D8h
    L_0040c718:
        mov dword ptr [eax+1010h],ecx
    L_0040c71e:
        mov dword ptr [eax+1014h],ecx
    L_0040c724:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A990..0x0042A9A2: FUN_0042a990
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a990_0042a990() {
    __asm {
    L_0042a990:
        mov ecx,dword ptr [eax]
    L_0042a992:
        mov edx,dword ptr [eax+8]
    L_0042a995:
        mov dword ptr [eax+4],ecx
    L_0042a998:
        mov dword ptr [eax+0Ch],edx
    L_0042a99b:
        mov dword ptr [eax+14h],0
    L_0042a9a2:
        ret
    }
}

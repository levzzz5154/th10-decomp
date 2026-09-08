#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456344..0x00456356: __initptd
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_initptd_00456344() {
    __asm {
    L_00456344:
        mov eax,dword ptr [esp+4]
    L_00456348:
        mov dword ptr [eax+54h],4735D0h
    L_0045634f:
        mov dword ptr [eax+14h],1
    L_00456356:
        ret
    }
}

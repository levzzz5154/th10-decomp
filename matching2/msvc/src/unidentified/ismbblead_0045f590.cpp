#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F590..0x0045F5A0: __ismbblead
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ismbblead_0045f590() {
    __asm {
    L_0045f590:
        push 4
    L_0045f592:
        push 0
    L_0045f594:
        push dword ptr [esp+0Ch]
    L_0045f598:
        call asm_x_ismbbtype_0045f4c9
    L_0045f59d:
        add esp,0Ch
    L_0045f5a0:
        ret
    }
}

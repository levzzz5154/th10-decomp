#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D5CE..0x0045D5E3: FID_conflict:__ld12tod
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict___ld12tod_0045d5ce() {
    __asm {
    L_0045d5ce:
        push 473BF8h
    L_0045d5d3:
        push dword ptr [esp+0Ch]
    L_0045d5d7:
        push dword ptr [esp+0Ch]
    L_0045d5db:
        call asm_ld12cvt_0045d476
    L_0045d5e0:
        add esp,0Ch
    L_0045d5e3:
        ret
    }
}

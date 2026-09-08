#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D5E4..0x0045D5F9: FID_conflict:__ld12tod
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict___ld12tod_0045d5e4() {
    __asm {
    L_0045d5e4:
        push 473C10h
    L_0045d5e9:
        push dword ptr [esp+0Ch]
    L_0045d5ed:
        push dword ptr [esp+0Ch]
    L_0045d5f1:
        call asm_ld12cvt_0045d476
    L_0045d5f6:
        add esp,0Ch
    L_0045d5f9:
        ret
    }
}

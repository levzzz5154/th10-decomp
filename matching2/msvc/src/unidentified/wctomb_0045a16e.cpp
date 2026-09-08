#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A16E..0x0045A194: _wctomb
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_wctomb_0045a16e() {
    __asm {
    L_0045a16e:
        call asm_getptd_00456357
    L_0045a173:
        mov eax,dword ptr [eax+64h]
    L_0045a176:
        cmp eax,dword ptr [data_0047320c]
    L_0045a17c:
        je short L_0045a183
    L_0045a17e:
        call asm_updatetlocinfo_00455ade
    L_0045a183:
        push dword ptr [esp+8]
    L_0045a187:
        push dword ptr [esp+8]
    L_0045a18b:
        push eax
    L_0045a18c:
        call asm_wctomb_mt_0045a10e
    L_0045a191:
        add esp,0Ch
    L_0045a194:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E375..0x0045E39F: _mbtowc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_mbtowc_0045e375() {
    __asm {
    L_0045e375:
        call asm_getptd_00456357
    L_0045e37a:
        mov eax,dword ptr [eax+64h]
    L_0045e37d:
        cmp eax,dword ptr [data_0047320c]
    L_0045e383:
        je short L_0045e38a
    L_0045e385:
        call asm_updatetlocinfo_00455ade
    L_0045e38a:
        push dword ptr [esp+0Ch]
    L_0045e38e:
        push dword ptr [esp+0Ch]
    L_0045e392:
        push dword ptr [esp+0Ch]
    L_0045e396:
        push eax
    L_0045e397:
        call asm_mbtowc_mt_0045e2b5
    L_0045e39c:
        add esp,10h
    L_0045e39f:
        ret
    }
}

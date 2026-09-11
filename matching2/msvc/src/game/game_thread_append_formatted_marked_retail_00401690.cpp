#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401530..0x004015B3: ?GameThread_AppendRecord@@
// Naked body preserves the retail register/stack ABI.

// 0x00401690..0x004016F3: GameThread_AppendFormattedMarkedRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_AppendFormattedMarkedRetail_00401690() {
    __asm {
    L_00401690:
        sub esp,204h
    L_00401696:
        mov eax,dword ptr [data_00473660]
    L_0040169b:
        mov ecx,dword ptr [esp+208h]
    L_004016a2:
        xor eax,esp
    L_004016a4:
        mov dword ptr [esp+200h],eax
    L_004016ab:
        lea eax,[esp+20Ch]
    L_004016b2:
        push eax
    L_004016b3:
        push ecx
    L_004016b4:
        lea edx,[esp+8]
    L_004016b8:
        push edx
    L_004016b9:
        call asm_vsprintf_004524a6
    L_004016be:
        add esp,0Ch
    L_004016c1:
        lea eax,[esp]
    L_004016c4:
        mov ecx,esi
    L_004016c6:
        call asm_GameThread_AppendRecord_00401530
    L_004016cb:
        mov eax,dword ptr [esi+896Ch]
    L_004016d1:
        mov ecx,dword ptr [esp+200h]
    L_004016d8:
        imul eax,68h
    L_004016db:
        xor ecx,esp
    L_004016dd:
        mov dword ptr [eax+esi+764h],1
    L_004016e8:
        call asm_security_check_cookie_00458ea5
    L_004016ed:
        add esp,204h
    L_004016f3:
        ret
    }
}

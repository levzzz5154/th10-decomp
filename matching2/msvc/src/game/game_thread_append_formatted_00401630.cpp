// BLOCKED (D3305): closest_byte_count=85/85; first_diff=none
// (authoritative retail overlay probe exact; no readable candidate retained).
// residual_class=private EBX object receiver, variadic stack layout,
// _vsprintf argument evaluation, and security-cookie frame scheduling.
// variants_tested=live Ghidra decompilation plus callers/callees
// (0x004224C0, 0x00422660, 0x00431410, 0x00431BA0, 0x004329F0,
// 0x00433230, 0x00433B30; _vsprintf 0x004524A6, AppendRecord 0x00401530,
// cookie 0x00458EA5); standalone variadic C++ candidate emitted 88 bytes
// (requested extent 85), so it was not retained; native-LTCG is gated
// because this region is still kind=asm rather than semantic ownership.
// next_lever=schema2 native-LTCG over the real callers and this variadic
// member, preserving EBX as the first parameter and the exact cookie frame.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401530..0x004015B3: ?GameThread_AppendRecord@@
// Naked body preserves the retail register/stack ABI.

// 0x00401630..0x00401684: ?GameThread_AppendFormatted@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_AppendFormatted_00401630() {
    __asm {
    L_00401630:
        sub esp,204h
    L_00401636:
        mov eax,dword ptr [data_00473660]
    L_0040163b:
        mov ecx,dword ptr [esp+20Ch]
    L_00401642:
        xor eax,esp
    L_00401644:
        mov dword ptr [esp+200h],eax
    L_0040164b:
        lea eax,[esp+210h]
    L_00401652:
        push eax
    L_00401653:
        push ecx
    L_00401654:
        lea edx,[esp+8]
    L_00401658:
        push edx
    L_00401659:
        call asm_vsprintf_004524a6
    L_0040165e:
        mov ecx,dword ptr [esp+214h]
    L_00401665:
        add esp,0Ch
    L_00401668:
        lea eax,[esp]
    L_0040166b:
        call asm_GameThread_AppendRecord_00401530
    L_00401670:
        mov ecx,dword ptr [esp+200h]
    L_00401677:
        xor ecx,esp
    L_00401679:
        call asm_security_check_cookie_00458ea5
    L_0040167e:
        add esp,204h
    L_00401684:
        ret
    }
}

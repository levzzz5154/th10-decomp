#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401700..0x0040175D: FUN_00401700
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401700_00401700() {
    __asm {
    L_00401700:
        sub esp,204h
    L_00401706:
        mov eax,dword ptr [data_00473660]
    L_0040170b:
        mov ecx,dword ptr [esp+208h]
    L_00401712:
        xor eax,esp
    L_00401714:
        mov dword ptr [esp+200h],eax
    L_0040171b:
        lea eax,[esp+20Ch]
    L_00401722:
        push eax
    L_00401723:
        push ecx
    L_00401724:
        lea edx,[esp+8]
    L_00401728:
        push edx
    L_00401729:
        call asm_vsprintf_004524a6
    L_0040172e:
        add esp,0Ch
    L_00401731:
        lea ecx,[esp]
    L_00401734:
        call asm_FUN_004015c0_004015c0
    L_00401739:
        lea eax,[esp]
    L_0040173c:
        lea edx,[eax+1]
    L_0040173f:
        nop
    L_00401740:
        mov cl,byte ptr [eax]
    L_00401742:
        inc eax
    L_00401743:
        test cl,cl
    L_00401745:
        jne short L_00401740
    L_00401747:
        mov ecx,dword ptr [esp+200h]
    L_0040174e:
        xor ecx,esp
    L_00401750:
        sub eax,edx
    L_00401752:
        call asm_security_check_cookie_00458ea5
    L_00401757:
        add esp,204h
    L_0040175d:
        ret
    }
}

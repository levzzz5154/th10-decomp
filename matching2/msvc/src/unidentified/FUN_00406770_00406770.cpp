#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00406770..0x0040678D: FUN_00406770
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00406770_00406770() {
    __asm {
    L_00406770:
        mov eax,dword ptr [data_00477810]
    L_00406775:
        test eax,eax
    L_00406777:
        TH10_REL8(0x74, 0x00406777, VA_asm_Player_ForwardAxisWrap_0040678e)
    L_00406779:
        mov eax,dword ptr [eax+58h]
    L_0040677c:
        mov edx,eax
    L_0040677e:
        shr edx,2
    L_00406781:
        or edx,eax
    L_00406783:
        test dl,1
    L_00406786:
        TH10_REL8(0x74, 0x00406786, VA_asm_Player_ForwardAxisWrap_0040678e)
    L_00406788:
        mov eax,1
    L_0040678d:
        ret
    }
}

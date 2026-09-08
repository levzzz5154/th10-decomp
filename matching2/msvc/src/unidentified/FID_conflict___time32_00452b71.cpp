#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452B71..0x00452BA9: FID_conflict:__time32
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict___time32_00452b71() {
    __asm {
    L_00452b71:
        push ebp
    L_00452b72:
        mov ebp,esp
    L_00452b74:
        push ecx
    L_00452b75:
        push ecx
    L_00452b76:
        lea eax,[ebp-8]
    L_00452b79:
        push eax
    L_00452b7a:
        call dword ptr [data_004661b0]
    L_00452b80:
        mov eax,dword ptr [ebp-8]
    L_00452b83:
        mov ecx,dword ptr [ebp-4]
    L_00452b86:
        push 0
    L_00452b88:
        add eax,2AC18000h
    L_00452b8d:
        push 989680h
    L_00452b92:
        adc ecx,0FE624E21h
    L_00452b98:
        push ecx
    L_00452b99:
        push eax
    L_00452b9a:
        call asm_aulldiv_00456b80
    L_00452b9f:
        mov ecx,dword ptr [ebp+8]
    L_00452ba2:
        test ecx,ecx
    L_00452ba4:
        je short L_00452ba8
    L_00452ba6:
        mov dword ptr [ecx],eax
    L_00452ba8:
        leave
    L_00452ba9:
        ret
    }
}

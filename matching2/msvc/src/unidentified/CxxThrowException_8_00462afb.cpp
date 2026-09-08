#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462AFB..0x00462B34: __CxxThrowException@8
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CxxThrowException_8_00462afb() {
    __asm {
    L_00462afb:
        push ebp
    L_00462afc:
        mov ebp,esp
    L_00462afe:
        sub esp,20h
    L_00462b01:
        mov eax,dword ptr [ebp+8]
    L_00462b04:
        push esi
    L_00462b05:
        push edi
    L_00462b06:
        push 8
    L_00462b08:
        pop ecx
    L_00462b09:
        mov esi,46CA30h
    L_00462b0e:
        lea edi,[ebp-20h]
    L_00462b11:
        rep movsd
    L_00462b13:
        mov dword ptr [ebp-8],eax
    L_00462b16:
        mov eax,dword ptr [ebp+0Ch]
    L_00462b19:
        mov dword ptr [ebp-4],eax
    L_00462b1c:
        lea eax,[ebp-0Ch]
    L_00462b1f:
        push eax
    L_00462b20:
        push dword ptr [ebp-10h]
    L_00462b23:
        push dword ptr [ebp-1Ch]
    L_00462b26:
        push dword ptr [ebp-20h]
    L_00462b29:
        call dword ptr [data_00466044]
    L_00462b2f:
        pop edi
    L_00462b30:
        pop esi
    L_00462b31:
        leave
    L_00462b32:
        ret 8
    }
}

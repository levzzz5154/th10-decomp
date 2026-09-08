#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462A80..0x00462AD8: _CallCatchBlock2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CallCatchBlock2_00462a80() {
    __asm {
    L_00462a80:
        push ebp
    L_00462a81:
        mov ebp,esp
    L_00462a83:
        sub esp,18h
    L_00462a86:
        mov eax,dword ptr [data_00473660]
    L_00462a8b:
        and dword ptr [ebp-18h],0
    L_00462a8f:
        mov ecx,dword ptr [ebp+8]
    L_00462a92:
        mov dword ptr [ebp-10h],eax
    L_00462a95:
        mov eax,dword ptr [ebp+0Ch]
    L_00462a98:
        mov dword ptr [ebp-0Ch],eax
    L_00462a9b:
        mov eax,dword ptr [ebp+14h]
    L_00462a9e:
        inc eax
    L_00462a9f:
        mov dword ptr [ebp-14h],4627BDh
    L_00462aa6:
        mov dword ptr [ebp-8],ecx
    L_00462aa9:
        mov dword ptr [ebp-4],eax
    L_00462aac:
        mov eax,dword ptr fs:[0]
    L_00462ab2:
        mov dword ptr [ebp-18h],eax
    L_00462ab5:
        lea eax,[ebp-18h]
    L_00462ab8:
        mov dword ptr fs:[0],eax
    L_00462abe:
        push dword ptr [ebp+18h]
    L_00462ac1:
        push ecx
    L_00462ac2:
        push dword ptr [ebp+10h]
    L_00462ac5:
        call asm_CallSettingFrame_12_00463a10
    L_00462aca:
        mov ecx,eax
    L_00462acc:
        mov eax,dword ptr [ebp-18h]
    L_00462acf:
        mov dword ptr fs:[0],eax
    L_00462ad5:
        mov eax,ecx
    L_00462ad7:
        leave
    L_00462ad8:
        ret
    }
}

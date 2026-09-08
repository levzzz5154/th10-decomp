#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463A10..0x00463A5B: __CallSettingFrame@12
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CallSettingFrame_12_00463a10() {
    __asm {
    L_00463a10:
        push ebp
    L_00463a11:
        mov ebp,esp
    L_00463a13:
        sub esp,4
    L_00463a16:
        push ebx
    L_00463a17:
        push ecx
    L_00463a18:
        mov eax,dword ptr [ebp+0Ch]
    L_00463a1b:
        add eax,0Ch
    L_00463a1e:
        mov dword ptr [ebp-4],eax
    L_00463a21:
        mov eax,dword ptr [ebp+8]
    L_00463a24:
        push ebp
    L_00463a25:
        push dword ptr [ebp+10h]
    L_00463a28:
        mov ecx,dword ptr [ebp+10h]
    L_00463a2b:
        mov ebp,dword ptr [ebp-4]
    L_00463a2e:
        call asm_NLG_Notify1_00459969
    L_00463a33:
        push esi
    L_00463a34:
        push edi
    L_00463a35:
        call eax
    L_00463a37:
        pop edi
    L_00463a38:
        pop esi
    L_00463a39:
        mov ebx,ebp
    L_00463a3b:
        pop ebp
    L_00463a3c:
        mov ecx,dword ptr [ebp+10h]
    L_00463a3f:
        push ebp
    L_00463a40:
        mov ebp,ebx
    L_00463a42:
        cmp ecx,100h
    L_00463a48:
        jne short L_00463a4f
    L_00463a4a:
        mov ecx,2
    L_00463a4f:
        push ecx
    L_00463a50:
        call asm_NLG_Notify1_00459969
    L_00463a55:
        pop ebp
    L_00463a56:
        pop ecx
    L_00463a57:
        pop ebx
    L_00463a58:
        leave
    L_00463a59:
        ret 0Ch
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004349E0..0x00434A1A: ?StageText_SkipLine@@
// Naked body preserves the retail register/stack ABI.

// 0x00434A20..0x00434A7B: ?StageText_ExtractLine@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageText_ExtractLine_00434a20() {
    __asm {
    L_00434a20:
        cmp byte ptr [ecx],0Ah
    L_00434a23:
        mov eax,ecx
    L_00434a25:
        je short L_00434a3b
    L_00434a27:
        cmp byte ptr [eax],0Dh
    L_00434a2a:
        je short L_00434a3b
    L_00434a2c:
        mov edx,dword ptr [edi]
    L_00434a2e:
        test edx,edx
    L_00434a30:
        je short L_00434a79
    L_00434a32:
        inc eax
    L_00434a33:
        dec edx
    L_00434a34:
        mov dword ptr [edi],edx
    L_00434a36:
        cmp byte ptr [eax],0Ah
    L_00434a39:
        jne short L_00434a27
    L_00434a3b:
        cmp dword ptr [edi],0
    L_00434a3e:
        je short L_00434a79
    L_00434a40:
        push esi
    L_00434a41:
        mov esi,dword ptr [esp+8]
    L_00434a45:
        mov byte ptr [eax],0
    L_00434a48:
        sub esi,ecx
    L_00434a4a:
        lea ebx,[ebx+force_disp32_zero]
    L_00434a50:
        mov dl,byte ptr [ecx]
    L_00434a52:
        mov byte ptr [esi+ecx],dl
    L_00434a55:
        inc ecx
    L_00434a56:
        test dl,dl
    L_00434a58:
        jne short L_00434a50
    L_00434a5a:
        mov ecx,dword ptr [edi]
    L_00434a5c:
        inc eax
    L_00434a5d:
        dec ecx
    L_00434a5e:
        mov dword ptr [edi],ecx
    L_00434a60:
        mov edx,ecx
    L_00434a62:
        pop esi
    L_00434a63:
        mov cl,byte ptr [eax]
    L_00434a65:
        cmp cl,0Ah
    L_00434a68:
        je short L_00434a6f
    L_00434a6a:
        cmp cl,0Dh
    L_00434a6d:
        jne short L_00434a79
    L_00434a6f:
        test edx,edx
    L_00434a71:
        je short L_00434a79
    L_00434a73:
        inc eax
    L_00434a74:
        dec edx
    L_00434a75:
        mov dword ptr [edi],edx
    L_00434a77:
        jmp short L_00434a63
    L_00434a79:
        ret 4
    }
}

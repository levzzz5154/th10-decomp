#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452AE8..0x00452B3F: _sprintf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sprintf_00452ae8() {
    __asm {
    L_00452ae8:
        push ebp
    L_00452ae9:
        mov ebp,esp
    L_00452aeb:
        sub esp,20h
    L_00452aee:
        push esi
    L_00452aef:
        mov esi,dword ptr [ebp+8]
    L_00452af2:
        push edi
    L_00452af3:
        lea eax,[ebp+10h]
    L_00452af6:
        push eax
    L_00452af7:
        push dword ptr [ebp+0Ch]
    L_00452afa:
        lea eax,[ebp-20h]
    L_00452afd:
        push eax
    L_00452afe:
        mov dword ptr [ebp-1Ch],7FFFFFFFh
    L_00452b05:
        mov dword ptr [ebp-14h],42h
    L_00452b0c:
        mov dword ptr [ebp-18h],esi
    L_00452b0f:
        mov dword ptr [ebp-20h],esi
    L_00452b12:
        call asm_FUN_00454ed7_00454ed7
    L_00452b17:
        add esp,0Ch
    L_00452b1a:
        test esi,esi
    L_00452b1c:
        mov edi,eax
    L_00452b1e:
        je short L_00452b3a
    L_00452b20:
        dec dword ptr [ebp-1Ch]
    L_00452b23:
        js short L_00452b2d
    L_00452b25:
        mov eax,dword ptr [ebp-20h]
    L_00452b28:
        mov byte ptr [eax],0
    L_00452b2b:
        jmp short L_00452b3a
    L_00452b2d:
        lea eax,[ebp-20h]
    L_00452b30:
        push eax
    L_00452b31:
        push 0
    L_00452b33:
        call asm_flsbuf_00454d11
    L_00452b38:
        pop ecx
    L_00452b39:
        pop ecx
    L_00452b3a:
        mov eax,edi
    L_00452b3c:
        pop edi
    L_00452b3d:
        pop esi
    L_00452b3e:
        leave
    L_00452b3f:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463F40..0x00463FA6: __trandisp1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_trandisp1_00463f40() {
    __asm {
    L_00463f40:
        cmp byte ptr [edx+0Eh],5
    L_00463f44:
        jne short L_00463f57
    L_00463f46:
        mov bx,word ptr [ebp-0A4h]
    L_00463f4d:
        or bh,2
    L_00463f50:
        and bh,0FEh
    L_00463f53:
        mov bl,3Fh
    L_00463f55:
        jmp short L_00463f5b
    L_00463f57:
        mov bx,133Fh
    L_00463f5b:
        mov word ptr [ebp-0A2h],bx
    L_00463f62:
        fldcw word ptr [ebp-0A2h]
    L_00463f68:
        mov ebx,47708Ch
    L_00463f6d:
        fxam
    L_00463f6f:
        mov dword ptr [ebp-94h],edx
    L_00463f75:
        wait
        fnstsw word ptr [ebp-0A0h]
    L_00463f7c:
        mov byte ptr [ebp-90h],0
    L_00463f83:
        wait
    L_00463f84:
        mov cl,byte ptr [ebp-9Fh]
    L_00463f8a:
        shl cl,1
    L_00463f8c:
        sar cl,1
    L_00463f8e:
        rol cl,1
    L_00463f90:
        mov al,cl
    L_00463f92:
        and al,0Fh
    L_00463f94:
        xlatb
    L_00463f95:
        movsx eax,al
    L_00463f98:
        and ecx,404h
    L_00463f9e:
        mov ebx,edx
    L_00463fa0:
        add ebx,eax
    L_00463fa2:
        add ebx,10h
    L_00463fa5:
        jmp dword ptr [ebx]
    }
}

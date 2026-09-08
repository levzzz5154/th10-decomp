#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463FA7..0x00464032: __trandisp2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_trandisp2_00463fa7() {
    __asm {
    L_00463fa7:
        cmp byte ptr [edx+0Eh],5
    L_00463fab:
        jne short L_00463fbe
    L_00463fad:
        mov bx,word ptr [ebp-0A4h]
    L_00463fb4:
        or bh,2
    L_00463fb7:
        and bh,0FEh
    L_00463fba:
        mov bl,3Fh
    L_00463fbc:
        jmp short L_00463fc2
    L_00463fbe:
        mov bx,133Fh
    L_00463fc2:
        mov word ptr [ebp-0A2h],bx
    L_00463fc9:
        fldcw word ptr [ebp-0A2h]
    L_00463fcf:
        mov ebx,47708Ch
    L_00463fd4:
        fxam
    L_00463fd6:
        mov dword ptr [ebp-94h],edx
    L_00463fdc:
        wait
        fnstsw word ptr [ebp-0A0h]
    L_00463fe3:
        mov byte ptr [ebp-90h],0
    L_00463fea:
        fxch
    L_00463fec:
        mov cl,byte ptr [ebp-9Fh]
    L_00463ff2:
        fxam
    L_00463ff4:
        wait
        fnstsw word ptr [ebp-0A0h]
    L_00463ffb:
        fxch
    L_00463ffd:
        mov ch,byte ptr [ebp-9Fh]
    L_00464003:
        shl ch,1
    L_00464005:
        sar ch,1
    L_00464007:
        rol ch,1
    L_00464009:
        mov al,ch
    L_0046400b:
        and al,0Fh
    L_0046400d:
        xlatb
    L_0046400e:
        mov ah,al
    L_00464010:
        shl cl,1
    L_00464012:
        sar cl,1
    L_00464014:
        rol cl,1
    L_00464016:
        mov al,cl
    L_00464018:
        and al,0Fh
    L_0046401a:
        xlatb
    L_0046401b:
        shl ah,1
    L_0046401d:
        shl ah,1
    L_0046401f:
        or al,ah
    L_00464021:
        movsx eax,al
    L_00464024:
        and ecx,404h
    L_0046402a:
        mov ebx,edx
    L_0046402c:
        add ebx,eax
    L_0046402e:
        add ebx,10h
    L_00464031:
        jmp dword ptr [ebx]
    }
}

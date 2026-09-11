#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441600..0x00441933: FUN_00441600
// Naked body preserves the retail register/stack ABI.

// 0x00441950..0x00441AC1: FUN_00441950
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441950_00441950() {
    __asm {
    L_00441950:
        sub esp,8
    L_00441953:
        mov eax,dword ptr [esi+24h]
    L_00441956:
        test eax,eax
    L_00441958:
        mov dword ptr [esp],eax
    L_0044195b:
        jle asm_target_00441a04
    L_00441961:
        mov edx,dword ptr [esi+14h]
    L_00441964:
        mov ecx,dword ptr [esi+1Ch]
    L_00441967:
        mov dword ptr [esi+10h],edx
    L_0044196a:
        fld dword ptr [ecx]
    L_0044196c:
        fcomp dword ptr [data_00470b68]
    L_00441972:
        fnstsw ax
    L_00441974:
        test ah,41h
    L_00441977:
        jne short L_0044199a
    L_00441979:
        fld dword ptr [ecx]
    L_0044197b:
        fcomp dword ptr [data_00470b64]
    L_00441981:
        fnstsw ax
    L_00441983:
        test ah,5
    L_00441986:
        jp short L_0044199a
    L_00441988:
        fld dword ptr [esi+18h]
    L_0044198b:
        inc edx
    L_0044198c:
        fadd dword ptr [data_00470afc]
    L_00441992:
        mov dword ptr [esi+14h],edx
    L_00441995:
        fstp dword ptr [esi+18h]
    L_00441998:
        jmp short L_004419aa
    L_0044199a:
        fld dword ptr [ecx]
    L_0044199c:
        fadd dword ptr [esi+18h]
    L_0044199f:
        fst dword ptr [esi+18h]
    L_004419a2:
        call asm_FUN_00463b2c_00463b2c
    L_004419a7:
        mov dword ptr [esi+14h],eax
    L_004419aa:
        mov ecx,dword ptr [esi+24h]
    L_004419ad:
        cmp dword ptr [esi+14h],ecx
    L_004419b0:
        mov dword ptr [esp],ecx
    L_004419b3:
        jl short L_00441a04
    L_004419b5:
        mov eax,dword ptr [esi+20h]
    L_004419b8:
        test al,1
    L_004419ba:
        mov dword ptr [esp],ecx
    L_004419bd:
        jne short L_004419e1
    L_004419bf:
        or eax,1
    L_004419c2:
        mov dword ptr [esi+14h],0
    L_004419c9:
        mov dword ptr [esi+10h],0FFF0BDC1h
    L_004419d0:
        mov dword ptr [esi+18h],0
    L_004419d7:
        mov dword ptr [esi+1Ch],476F78h
    L_004419de:
        mov dword ptr [esi+20h],eax
    L_004419e1:
        fild dword ptr [esp]
    L_004419e4:
        mov dword ptr [esi+14h],ecx
    L_004419e7:
        dec ecx
    L_004419e8:
        mov dword ptr [esi+10h],ecx
    L_004419eb:
        fstp dword ptr [esi+18h]
    L_004419ee:
        mov eax,dword ptr [esi+28h]
    L_004419f1:
        cmp eax,7
    L_004419f4:
        mov dword ptr [esi+24h],0
    L_004419fb:
        je short L_00441a15
    L_004419fd:
        mov eax,dword ptr [esi+4]
    L_00441a00:
        add esp,8
    L_00441a03:
        ret
    L_00441a04:
        mov eax,dword ptr [esi+28h]
    L_00441a07:
        cmp eax,7
    L_00441a0a:
        jne short L_00441a1b
    L_00441a0c:
        mov ecx,dword ptr [esi]
    L_00441a0e:
        mov eax,dword ptr [esi+4]
    L_00441a11:
        add ecx,eax
    L_00441a13:
        mov dword ptr [esi],ecx
    L_00441a15:
        mov eax,dword ptr [esi]
    L_00441a17:
        add esp,8
    L_00441a1a:
        ret
    L_00441a1b:
        cmp eax,11h
    L_00441a1e:
        jne short L_00441a33
    L_00441a20:
        mov eax,dword ptr [esi+0Ch]
    L_00441a23:
        add dword ptr [esi],eax
    L_00441a25:
        mov ecx,dword ptr [esi+4]
    L_00441a28:
        add ecx,eax
    L_00441a2a:
        mov eax,dword ptr [esi]
    L_00441a2c:
        mov dword ptr [esi+0Ch],ecx
    L_00441a2f:
        add esp,8
    L_00441a32:
        ret
    L_00441a33:
        cmp eax,8
    L_00441a36:
        fild dword ptr [esp]
    L_00441a39:
        jne short L_00441a98
    L_00441a3b:
        fdivr dword ptr [esi+18h]
    L_00441a3e:
        fld st(0)
    L_00441a40:
        fadd st,st(1)
    L_00441a42:
        fld st(1)
    L_00441a44:
        fsub dword ptr [data_00470afc]
    L_00441a4a:
        fld dword ptr [data_00470afc]
    L_00441a50:
        fsub st,st(3)
    L_00441a52:
        fld dword ptr [data_00470bd4]
    L_00441a58:
        fsub st,st(3)
    L_00441a5a:
        fmul st,st(4)
    L_00441a5c:
        fmul st,st(4)
    L_00441a5e:
        fimul dword ptr [esi+4]
    L_00441a61:
        fld st(2)
    L_00441a63:
        fmul st,st(5)
    L_00441a65:
        fmul st,st(5)
    L_00441a67:
        fimul dword ptr [esi+0Ch]
    L_00441a6a:
        faddp st(1),st
    L_00441a6c:
        fld st(1)
    L_00441a6e:
        fmul st,st(2)
    L_00441a70:
        fmul st,st(5)
    L_00441a72:
        fimul dword ptr [esi+8]
    L_00441a75:
        faddp st(1),st
    L_00441a77:
        fxch st(3)
    L_00441a79:
        fadd dword ptr [data_00470afc]
    L_00441a7f:
        fmul st,st(2)
    L_00441a81:
        fmul st,st(2)
    L_00441a83:
        fimul dword ptr [esi]
    L_00441a85:
        faddp st(3),st
    L_00441a87:
        fxch st(2)
    L_00441a89:
        call asm_FUN_00463b2c_00463b2c
    L_00441a8e:
        fstp st(1)
    L_00441a90:
        fstp st(0)
    L_00441a92:
        fstp st(0)
    L_00441a94:
        add esp,8
    L_00441a97:
        ret
    L_00441a98:
        mov ecx,dword ptr [esi]
    L_00441a9a:
        mov edx,dword ptr [esi+18h]
    L_00441a9d:
        push ecx
    L_00441a9e:
        fstp dword ptr [esp]
    L_00441aa1:
        push edx
    L_00441aa2:
        mov dword ptr [esp+0Ch],ecx
    L_00441aa6:
        call asm_FUN_0044c350_0044c350
    L_00441aab:
        mov eax,dword ptr [esi+4]
    L_00441aae:
        sub eax,ecx
    L_00441ab0:
        mov dword ptr [esp],eax
    L_00441ab3:
        fimul dword ptr [esp]
    L_00441ab6:
        fiadd dword ptr [esp+4]
    L_00441aba:
        add esp,8
    L_00441abd:
        jmp asm_FUN_00463b2c_00463b2c
    }
}

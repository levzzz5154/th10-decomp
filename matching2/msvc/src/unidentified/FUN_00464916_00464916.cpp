#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464916..0x00464B1B: FUN_00464916
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00464916_00464916() {
    __asm {
    L_00464916:
        push eax
    L_00464917:
        push ebx
    L_00464918:
        push ecx
    L_00464919:
        mov eax,dword ptr [esp+16h]
    L_0046491d:
        xor eax,700h
    L_00464922:
        test eax,700h
    L_00464927:
        jne asm_target_00464ab0
    L_0046492d:
        shr eax,0Bh
    L_00464930:
        and eax,0Fh
    L_00464933:
        cmp byte ptr [eax+4770BCh],0
    L_0046493a:
        je asm_target_00464ab0
    L_00464940:
        mov eax,dword ptr [esp+16h]
    L_00464944:
        and eax,7FFF0000h
    L_00464949:
        cmp eax,7FFF0000h
    L_0046494e:
        je asm_target_00464ab0
    L_00464954:
        mov eax,dword ptr [esp+2Eh]
    L_00464958:
        and eax,7FFF0000h
    L_0046495d:
        je asm_target_00464ab0
    L_00464963:
        cmp eax,7FFF0000h
    L_00464968:
        je asm_target_00464ab0
    L_0046496e:
        mov eax,dword ptr [esp+2Ch]
    L_00464972:
        add eax,eax
    L_00464974:
        jne asm_target_00464ab0
    L_0046497a:
        mov eax,dword ptr [esp+14h]
    L_0046497e:
        add eax,eax
    L_00464980:
        jne asm_target_00464ab0
    L_00464986:
        mov eax,dword ptr [esp+18h]
    L_0046498a:
        and eax,7FFFh
    L_0046498f:
        add eax,3Fh
    L_00464992:
        mov ebx,dword ptr [esp+30h]
    L_00464996:
        and ebx,7FFFh
    L_0046499c:
        sub ebx,eax
    L_0046499e:
        ja short L_004649fe
    L_004649a0:
        mov eax,dword ptr [esp+18h]
    L_004649a4:
        and eax,7FFFh
    L_004649a9:
        add eax,0Ah
    L_004649ac:
        mov ebx,dword ptr [esp+30h]
    L_004649b0:
        and ebx,7FFFh
    L_004649b6:
        sub ebx,eax
    L_004649b8:
        js asm_target_00464ab0
    L_004649be:
        fld tbyte ptr [esp+28h]
    L_004649c2:
        mov eax,dword ptr [esp+18h]
    L_004649c6:
        mov ebx,dword ptr [esp+30h]
    L_004649ca:
        and ebx,7FFFh
    L_004649d0:
        mov ecx,ebx
    L_004649d2:
        sub ebx,eax
    L_004649d4:
        and ebx,7
    L_004649d7:
        or ebx,4
    L_004649da:
        sub ecx,ebx
    L_004649dc:
        mov ebx,eax
    L_004649de:
        and ebx,8000h
    L_004649e4:
        or ecx,ebx
    L_004649e6:
        mov dword ptr [esp+18h],ecx
    L_004649ea:
        fld tbyte ptr [esp+10h]
    L_004649ee:
        mov dword ptr [esp+18h],eax
    L_004649f2:
        fxch
    L_004649f4:
        fprem
    L_004649f6:
        fstp tbyte ptr [esp+28h]
    L_004649fa:
        fstp st(0)
    L_004649fc:
        jmp short L_004649a0
    L_004649fe:
        test edx,2
    L_00464a04:
        jne short L_00464a0e
    L_00464a06:
        fld tbyte ptr [esp+10h]
    L_00464a0a:
        fstp tbyte ptr [esp+1Ch]
    L_00464a0e:
        fnstcw word ptr [esp+34h]
    L_00464a12:
        mov eax,dword ptr [esp+34h]
    L_00464a16:
        or eax,33Fh
    L_00464a1b:
        mov dword ptr [esp+38h],eax
    L_00464a1f:
        fldcw word ptr [esp+38h]
    L_00464a23:
        mov eax,dword ptr [esp+18h]
    L_00464a27:
        and eax,7FFFh
    L_00464a2c:
        mov ebx,dword ptr [esp+30h]
    L_00464a30:
        and ebx,7FFFh
    L_00464a36:
        sub ebx,eax
    L_00464a38:
        and ebx,3Fh
    L_00464a3b:
        or ebx,20h
    L_00464a3e:
        add ebx,1
    L_00464a41:
        mov ecx,ebx
    L_00464a43:
        mov eax,dword ptr [esp+18h]
    L_00464a47:
        mov ebx,dword ptr [esp+30h]
    L_00464a4b:
        and ebx,7FFFh
    L_00464a51:
        and eax,8000h
    L_00464a56:
        or ebx,eax
    L_00464a58:
        mov dword ptr [esp+18h],ebx
    L_00464a5c:
        fld tbyte ptr [esp+10h]
    L_00464a60:
        fabs
    L_00464a62:
        fld tbyte ptr [esp+28h]
    L_00464a66:
        fabs
    L_00464a68:
        fcom
    L_00464a6a:
        fnstsw ax
    L_00464a6c:
        and eax,100h
    L_00464a71:
        jne short L_00464a75
    L_00464a73:
        fsub st,st(1)
    L_00464a75:
        fxch
    L_00464a77:
        fmul qword ptr [data_004770ec]
    L_00464a7d:
        fxch
    L_00464a7f:
        sub ecx,1
    L_00464a82:
        jne short L_00464a68
    L_00464a84:
        mov ebx,dword ptr [esp+30h]
    L_00464a88:
        fstp tbyte ptr [esp+28h]
    L_00464a8c:
        fstp st(0)
    L_00464a8e:
        fld tbyte ptr [esp+1Ch]
    L_00464a92:
        fld tbyte ptr [data_004770f4]
    L_00464a98:
        fprem
    L_00464a9a:
        fstp st(0)
    L_00464a9c:
        fld tbyte ptr [esp+28h]
    L_00464aa0:
        fldcw word ptr [esp+34h]
    L_00464aa4:
        and ebx,8000h
    L_00464aaa:
        je short L_00464aba
    L_00464aac:
        fchs
    L_00464aae:
        jmp short L_00464aba
    L_00464ab0:
        fld tbyte ptr [esp+10h]
    L_00464ab4:
        fld tbyte ptr [esp+28h]
    L_00464ab8:
        fprem
    L_00464aba:
        test edx,3
    L_00464ac0:
        je short L_00464b18
    L_00464ac2:
        fnstsw word ptr [esp+3Ch]
    L_00464ac6:
        test edx,1
    L_00464acc:
        je short L_00464aed
    L_00464ace:
        fnstcw word ptr [esp+34h]
    L_00464ad2:
        mov eax,dword ptr [esp+34h]
    L_00464ad6:
        or eax,300h
    L_00464adb:
        mov dword ptr [esp+38h],eax
    L_00464adf:
        fldcw word ptr [esp+38h]
    L_00464ae3:
        fmul qword ptr [data_004770dc]
    L_00464ae9:
        fldcw word ptr [esp+34h]
    L_00464aed:
        mov eax,dword ptr [esp+3Ch]
    L_00464af1:
        fxch
    L_00464af3:
        fstp st(0)
    L_00464af5:
        fld tbyte ptr [esp+1Ch]
    L_00464af9:
        fxch
    L_00464afb:
        and eax,4300h
    L_00464b00:
        sub esp,1Ch
    L_00464b03:
        fnstenv [esp]
    L_00464b06:
        and dword ptr [esp+4],0BCFFh
    L_00464b0e:
        or dword ptr [esp+4],eax
    L_00464b12:
        fldenv [esp]
    L_00464b15:
        add esp,1Ch
    L_00464b18:
        pop ecx
    L_00464b19:
        pop ebx
    L_00464b1a:
        pop eax
    L_00464b1b:
        ret
    }
}

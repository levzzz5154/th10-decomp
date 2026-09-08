#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00439540..0x00439659: FUN_00439540
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439540_00439540() {
    __asm {
    L_00439540:
        sub esp,14h
    L_00439543:
        push 4922ECh
    L_00439548:
        call dword ptr [data_004660b0]
    L_0043954e:
        mov dl,byte ptr [data_00492321]
    L_00439554:
        mov eax,dword ptr [data_00492508]
    L_00439559:
        mov ecx,dword ptr [data_0049250c]
    L_0043955f:
        inc dl
    L_00439561:
        or eax,ecx
    L_00439563:
        mov byte ptr [data_00492321],dl
    L_00439569:
        je short L_004395df
    L_0043956b:
        lea ecx,[esp+8]
    L_0043956f:
        push ecx
    L_00439570:
        call dword ptr [data_004660fc]
    L_00439576:
        mov eax,dword ptr [data_00492510]
    L_0043957b:
        mov edx,dword ptr [esp+8]
    L_0043957f:
        mov ecx,dword ptr [data_00492514]
    L_00439585:
        sub edx,eax
    L_00439587:
        mov eax,dword ptr [esp+0Ch]
    L_0043958b:
        sbb eax,ecx
    L_0043958d:
        mov dword ptr [esp+4],eax
    L_00439591:
        mov dword ptr [esp],edx
    L_00439594:
        fild qword ptr [esp]
    L_00439597:
        fild qword ptr [data_00492508]
    L_0043959d:
        fdivp st(1),st
    L_0043959f:
        fst qword ptr [esp]
    L_004395a2:
        fld qword ptr [data_00492540]
    L_004395a8:
        fcomp
    L_004395aa:
        fnstsw ax
    L_004395ac:
        test ah,41h
    L_004395af:
        jne short L_004395b9
    L_004395b1:
        fstp qword ptr [data_00492540]
    L_004395b7:
        jmp short L_004395bb
    L_004395b9:
        fstp st(0)
    L_004395bb:
        push 4922ECh
    L_004395c0:
        call dword ptr [data_004660b4]
    L_004395c6:
        fld qword ptr [esp]
    L_004395c9:
        mov al,byte ptr [data_00492321]
    L_004395ce:
        fsub qword ptr [data_00492540]
    L_004395d4:
        dec al
    L_004395d6:
        mov byte ptr [data_00492321],al
    L_004395db:
        add esp,14h
    L_004395de:
        ret
    L_004395df:
        push 1
    L_004395e1:
        call dword ptr [data_00466278]
    L_004395e7:
        call dword ptr [data_00466270]
    L_004395ed:
        test eax,eax
    L_004395ef:
        mov dword ptr [esp],eax
    L_004395f2:
        fild dword ptr [esp]
    L_004395f5:
        jge short L_004395fd
    L_004395f7:
        fadd qword ptr [data_00470b30]
    L_004395fd:
        push 1
    L_004395ff:
        fstp qword ptr [esp+4]
    L_00439603:
        call dword ptr [data_00466274]
    L_00439609:
        fld qword ptr [data_00492540]
    L_0043960f:
        fcomp qword ptr [esp]
    L_00439612:
        fnstsw ax
    L_00439614:
        test ah,41h
    L_00439617:
        jne short L_00439622
    L_00439619:
        fld qword ptr [esp]
    L_0043961c:
        fstp qword ptr [data_00492540]
    L_00439622:
        fld qword ptr [data_00492540]
    L_00439628:
        push 4922ECh
    L_0043962d:
        fmul qword ptr [data_00470b88]
    L_00439633:
        fsubr qword ptr [esp+4]
    L_00439637:
        fmul qword ptr [data_00470b28]
    L_0043963d:
        fstp qword ptr [esp+4]
    L_00439641:
        call dword ptr [data_004660b4]
    L_00439647:
        mov al,byte ptr [data_00492321]
    L_0043964c:
        fld qword ptr [esp]
    L_0043964f:
        dec al
    L_00439651:
        mov byte ptr [data_00492321],al
    L_00439656:
        add esp,14h
    L_00439659:
        ret
    }
}

// 0x00439D20..0x00439FE5: FUN_00439d20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439d20_00439d20() {
    __asm {
    L_00439d20:
        push ecx
    L_00439d21:
        mov eax,dword ptr [data_00491c30]
    L_00439d26:
        mov ecx,dword ptr [eax]
    L_00439d28:
        push 1
    L_00439d2a:
        push 7
    L_00439d2c:
        push eax
    L_00439d2d:
        call dword ptr [ecx+0E4h]
    L_00439d33:
        mov eax,dword ptr [data_00491c30]
    L_00439d38:
        mov edx,dword ptr [eax]
    L_00439d3a:
        push 0
    L_00439d3c:
        push 89h
    L_00439d41:
        push eax
    L_00439d42:
        call dword ptr [edx+0E4h]
    L_00439d48:
        mov eax,dword ptr [data_00491c30]
    L_00439d4d:
        mov ecx,dword ptr [eax]
    L_00439d4f:
        push 1
    L_00439d51:
        push 16h
    L_00439d53:
        push eax
    L_00439d54:
        call dword ptr [ecx+0E4h]
    L_00439d5a:
        mov eax,dword ptr [data_00491c30]
    L_00439d5f:
        mov edx,dword ptr [eax]
    L_00439d61:
        push 1
    L_00439d63:
        push 1Bh
    L_00439d65:
        push eax
    L_00439d66:
        call dword ptr [edx+0E4h]
    L_00439d6c:
        mov eax,dword ptr [data_00491c30]
    L_00439d71:
        mov ecx,dword ptr [eax]
    L_00439d73:
        push 2
    L_00439d75:
        push 9
    L_00439d77:
        push eax
    L_00439d78:
        call dword ptr [ecx+0E4h]
    L_00439d7e:
        mov eax,dword ptr [data_00491c30]
    L_00439d83:
        mov edx,dword ptr [eax]
    L_00439d85:
        push 5
    L_00439d87:
        push 13h
    L_00439d89:
        push eax
    L_00439d8a:
        call dword ptr [edx+0E4h]
    L_00439d90:
        mov eax,dword ptr [data_00491c30]
    L_00439d95:
        mov ecx,dword ptr [eax]
    L_00439d97:
        push 6
    L_00439d99:
        push 14h
    L_00439d9b:
        push eax
    L_00439d9c:
        call dword ptr [ecx+0E4h]
    L_00439da2:
        mov eax,dword ptr [data_00491c30]
    L_00439da7:
        mov edx,dword ptr [eax]
    L_00439da9:
        push 8
    L_00439dab:
        push 17h
    L_00439dad:
        push eax
    L_00439dae:
        call dword ptr [edx+0E4h]
    L_00439db4:
        mov eax,dword ptr [data_00491c30]
    L_00439db9:
        mov ecx,dword ptr [eax]
    L_00439dbb:
        push 1
    L_00439dbd:
        push 0Fh
    L_00439dbf:
        push eax
    L_00439dc0:
        call dword ptr [ecx+0E4h]
    L_00439dc6:
        mov eax,dword ptr [data_00491c30]
    L_00439dcb:
        mov edx,dword ptr [eax]
    L_00439dcd:
        push 1
    L_00439dcf:
        push 18h
    L_00439dd1:
        push eax
    L_00439dd2:
        call dword ptr [edx+0E4h]
    L_00439dd8:
        mov eax,dword ptr [data_00491c30]
    L_00439ddd:
        mov ecx,dword ptr [eax]
    L_00439ddf:
        push 7
    L_00439de1:
        push 19h
    L_00439de3:
        push eax
    L_00439de4:
        call dword ptr [ecx+0E4h]
    L_00439dea:
        mov eax,dword ptr [data_00491c30]
    L_00439def:
        mov edx,dword ptr [eax]
    L_00439df1:
        push 1
    L_00439df3:
        push 1Ch
    L_00439df5:
        push eax
    L_00439df6:
        call dword ptr [edx+0E4h]
    L_00439dfc:
        mov eax,dword ptr [data_00491c30]
    L_00439e01:
        mov ecx,dword ptr [eax]
    L_00439e03:
        mov dword ptr [esp],3F800000h
    L_00439e0a:
        mov edx,dword ptr [esp]
    L_00439e0d:
        push edx
    L_00439e0e:
        push 26h
    L_00439e10:
        push eax
    L_00439e11:
        call dword ptr [ecx+0E4h]
    L_00439e17:
        mov eax,dword ptr [data_00491c30]
    L_00439e1c:
        mov ecx,dword ptr [eax]
    L_00439e1e:
        push 0
    L_00439e20:
        push 23h
    L_00439e22:
        push eax
    L_00439e23:
        call dword ptr [ecx+0E4h]
    L_00439e29:
        mov eax,dword ptr [data_00491c30]
    L_00439e2e:
        mov edx,dword ptr [eax]
    L_00439e30:
        push 3
    L_00439e32:
        push 8Ch
    L_00439e37:
        push eax
    L_00439e38:
        call dword ptr [edx+0E4h]
    L_00439e3e:
        mov eax,dword ptr [data_00491c30]
    L_00439e43:
        mov ecx,dword ptr [eax]
    L_00439e45:
        push 0FFA0A0A0h
    L_00439e4a:
        push 22h
    L_00439e4c:
        push eax
    L_00439e4d:
        call dword ptr [ecx+0E4h]
    L_00439e53:
        mov eax,dword ptr [data_00491c30]
    L_00439e58:
        mov edx,dword ptr [eax]
    L_00439e5a:
        mov dword ptr [esp],447A0000h
    L_00439e61:
        mov ecx,dword ptr [esp]
    L_00439e64:
        push ecx
    L_00439e65:
        push 24h
    L_00439e67:
        push eax
    L_00439e68:
        call dword ptr [edx+0E4h]
    L_00439e6e:
        mov eax,dword ptr [data_00491c30]
    L_00439e73:
        mov edx,dword ptr [eax]
    L_00439e75:
        mov dword ptr [esp],459C4000h
    L_00439e7c:
        mov ecx,dword ptr [esp]
    L_00439e7f:
        push ecx
    L_00439e80:
        push 25h
    L_00439e82:
        push eax
    L_00439e83:
        call dword ptr [edx+0E4h]
    L_00439e89:
        mov eax,dword ptr [data_00491c30]
    L_00439e8e:
        mov edx,dword ptr [eax]
    L_00439e90:
        push 0
    L_00439e92:
        push 0A1h
    L_00439e97:
        push eax
    L_00439e98:
        call dword ptr [edx+0E4h]
    L_00439e9e:
        mov eax,dword ptr [data_00491c30]
    L_00439ea3:
        mov ecx,dword ptr [eax]
    L_00439ea5:
        push 4
    L_00439ea7:
        push 4
    L_00439ea9:
        push 0
    L_00439eab:
        push eax
    L_00439eac:
        call dword ptr [ecx+10Ch]
    L_00439eb2:
        mov eax,dword ptr [data_00491c30]
    L_00439eb7:
        mov edx,dword ptr [eax]
    L_00439eb9:
        push 2
    L_00439ebb:
        push 5
    L_00439ebd:
        push 0
    L_00439ebf:
        push eax
    L_00439ec0:
        call dword ptr [edx+10Ch]
    L_00439ec6:
        mov eax,dword ptr [data_00491c30]
    L_00439ecb:
        mov ecx,dword ptr [eax]
    L_00439ecd:
        push 3
    L_00439ecf:
        push 6
    L_00439ed1:
        push 0
    L_00439ed3:
        push eax
    L_00439ed4:
        call dword ptr [ecx+10Ch]
    L_00439eda:
        mov eax,dword ptr [data_00491c30]
    L_00439edf:
        mov edx,dword ptr [eax]
    L_00439ee1:
        push 4
    L_00439ee3:
        push 1
    L_00439ee5:
        push 0
    L_00439ee7:
        push eax
    L_00439ee8:
        call dword ptr [edx+10Ch]
    L_00439eee:
        mov eax,dword ptr [data_00491c30]
    L_00439ef3:
        mov ecx,dword ptr [eax]
    L_00439ef5:
        push 2
    L_00439ef7:
        push 2
    L_00439ef9:
        push 0
    L_00439efb:
        push eax
    L_00439efc:
        call dword ptr [ecx+10Ch]
    L_00439f02:
        mov eax,dword ptr [data_00491c30]
    L_00439f07:
        mov edx,dword ptr [eax]
    L_00439f09:
        push 3
    L_00439f0b:
        push 3
    L_00439f0d:
        push 0
    L_00439f0f:
        push eax
    L_00439f10:
        call dword ptr [edx+10Ch]
    L_00439f16:
        mov eax,dword ptr [data_00491c30]
    L_00439f1b:
        mov ecx,dword ptr [eax]
    L_00439f1d:
        push 2
    L_00439f1f:
        push 18h
    L_00439f21:
        push 0
    L_00439f23:
        push eax
    L_00439f24:
        call dword ptr [ecx+10Ch]
    L_00439f2a:
        mov eax,dword ptr [data_00491c30]
    L_00439f2f:
        mov edx,dword ptr [eax]
    L_00439f31:
        push 0
    L_00439f33:
        push 0Bh
    L_00439f35:
        push 0
    L_00439f37:
        push eax
    L_00439f38:
        call dword ptr [edx+10Ch]
    L_00439f3e:
        mov eax,dword ptr [data_00491c30]
    L_00439f43:
        mov ecx,dword ptr [eax]
    L_00439f45:
        push 0
    L_00439f47:
        push 7
    L_00439f49:
        push 0
    L_00439f4b:
        push eax
    L_00439f4c:
        call dword ptr [ecx+114h]
    L_00439f52:
        mov eax,dword ptr [data_00491c30]
    L_00439f57:
        mov edx,dword ptr [eax]
    L_00439f59:
        push 2
    L_00439f5b:
        push 5
    L_00439f5d:
        push 0
    L_00439f5f:
        push eax
    L_00439f60:
        call dword ptr [edx+114h]
    L_00439f66:
        mov eax,dword ptr [data_00491c30]
    L_00439f6b:
        mov ecx,dword ptr [eax]
    L_00439f6d:
        push 2
    L_00439f6f:
        push 6
    L_00439f71:
        push 0
    L_00439f73:
        push eax
    L_00439f74:
        call dword ptr [ecx+114h]
    L_00439f7a:
        mov eax,dword ptr [data_00491c30]
    L_00439f7f:
        mov edx,dword ptr [eax]
    L_00439f81:
        push 3
    L_00439f83:
        push 3
    L_00439f85:
        push 0
    L_00439f87:
        push eax
    L_00439f88:
        call dword ptr [edx+114h]
    L_00439f8e:
        mov eax,dword ptr [data_00491c30]
    L_00439f93:
        mov ecx,dword ptr [eax]
    L_00439f95:
        push 1
    L_00439f97:
        push 1
    L_00439f99:
        push 0
    L_00439f9b:
        push eax
    L_00439f9c:
        call dword ptr [ecx+114h]
    L_00439fa2:
        mov eax,dword ptr [data_00491c30]
    L_00439fa7:
        mov edx,dword ptr [eax]
    L_00439fa9:
        push 1
    L_00439fab:
        push 2
    L_00439fad:
        push 0
    L_00439faf:
        push eax
    L_00439fb0:
        call dword ptr [edx+114h]
    L_00439fb6:
        mov eax,dword ptr [data_00491c10]
    L_00439fbb:
        test eax,eax
    L_00439fbd:
        je short L_00439fe4
    L_00439fbf:
        mov cl,0FFh
    L_00439fc1:
        mov byte ptr [eax+3ADA68h],3
    L_00439fc8:
        mov byte ptr [eax+3ADA69h],cl
    L_00439fce:
        mov byte ptr [eax+3ADA6Ah],cl
    L_00439fd4:
        mov dword ptr [eax+3ADA64h],0
    L_00439fde:
        mov byte ptr [eax+3ADA6Ch],cl
    L_00439fe4:
        pop ecx
    L_00439fe5:
        ret
    }
}

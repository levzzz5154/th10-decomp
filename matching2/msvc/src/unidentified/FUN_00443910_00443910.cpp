#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00443910..0x00443B5E: FUN_00443910
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00443910_00443910() {
    __asm {
    L_00443910:
        fld dword ptr [data_00470b04]
    L_00443916:
        sub esp,2Ch
    L_00443919:
        fld dword ptr [edx+2Ch]
    L_0044391c:
        fucompp
    L_0044391e:
        fnstsw ax
    L_00443920:
        test ah,44h
    L_00443923:
        jp short L_00443931
    L_00443925:
        push ecx
    L_00443926:
        mov eax,edx
    L_00443928:
        call asm_FUN_00443290_00443290
    L_0044392d:
        add esp,2Ch
    L_00443930:
        ret
    L_00443931:
        mov eax,dword ptr [edx+2Ch]
    L_00443934:
        push esi
    L_00443935:
        mov dword ptr [esp+0Ch],eax
    L_00443939:
        fld dword ptr [esp+0Ch]
    L_0044393d:
        fsincos
    L_0044393f:
        fstp dword ptr [esp+4]
    L_00443943:
        fstp dword ptr [esp+8]
    L_00443947:
        fld dword ptr [edx+34Ch]
    L_0044394d:
        fadd dword ptr [edx+340h]
    L_00443953:
        mov esi,dword ptr [edx+35Ch]
    L_00443959:
        mov eax,esi
    L_0044395b:
        shr eax,12h
    L_0044395e:
        fadd dword ptr [edx+334h]
    L_00443964:
        and eax,3
    L_00443967:
        sub eax,0
    L_0044396a:
        fld dword ptr [edx+350h]
    L_00443970:
        fadd dword ptr [edx+344h]
    L_00443976:
        fadd dword ptr [edx+338h]
    L_0044397c:
        fld dword ptr [edx+4Ch]
    L_0044397f:
        fmul dword ptr [edx+3Ch]
    L_00443982:
        fld dword ptr [edx+50h]
    L_00443985:
        fmul dword ptr [edx+40h]
    L_00443988:
        fstp dword ptr [esp+0Ch]
    L_0044398c:
        je short L_004439c4
    L_0044398e:
        dec eax
    L_0044398f:
        je short L_004439ae
    L_00443991:
        dec eax
    L_00443992:
        jne short L_004439e0
    L_00443994:
        fchs
    L_00443996:
        mov dword ptr [esp+2Ch],0
    L_0044399e:
        fst dword ptr [esp+28h]
    L_004439a2:
        fstp dword ptr [esp+20h]
    L_004439a6:
        fld dword ptr [data_00470b04]
    L_004439ac:
        jmp short L_004439e6
    L_004439ae:
        fst dword ptr [esp+2Ch]
    L_004439b2:
        mov dword ptr [esp+28h],0
    L_004439ba:
        mov dword ptr [esp+20h],0
    L_004439c2:
        jmp short L_004439e6
    L_004439c4:
        fld dword ptr [data_00470b78]
    L_004439ca:
        fmul st,st(1)
    L_004439cc:
        fst dword ptr [esp+28h]
    L_004439d0:
        fstp dword ptr [esp+20h]
    L_004439d4:
        fmul dword ptr [data_00470b0c]
    L_004439da:
        fst dword ptr [esp+2Ch]
    L_004439de:
        jmp short L_004439e6
    L_004439e0:
        fstp st(0)
    L_004439e2:
        fld dword ptr [esp+24h]
    L_004439e6:
        shr esi,14h
    L_004439e9:
        and esi,3
    L_004439ec:
        sub esi,0
    L_004439ef:
        je short L_00443a33
    L_004439f1:
        dec esi
    L_004439f2:
        je short L_00443a15
    L_004439f4:
        dec esi
    L_004439f5:
        jne short L_00443a55
    L_004439f7:
        fld dword ptr [esp+0Ch]
    L_004439fb:
        mov dword ptr [esp+1Ch],0
    L_00443a03:
        fchs
    L_00443a05:
        fst dword ptr [esp+14h]
    L_00443a09:
        fstp dword ptr [esp+10h]
    L_00443a0d:
        fld dword ptr [data_00470b04]
    L_00443a13:
        jmp short L_00443a59
    L_00443a15:
        mov eax,dword ptr [esp+0Ch]
    L_00443a19:
        fld dword ptr [esp+0Ch]
    L_00443a1d:
        mov dword ptr [esp+14h],0
    L_00443a25:
        mov dword ptr [esp+10h],0
    L_00443a2d:
        mov dword ptr [esp+1Ch],eax
    L_00443a31:
        jmp short L_00443a59
    L_00443a33:
        fld dword ptr [esp+0Ch]
    L_00443a37:
        fmul dword ptr [data_00470b78]
    L_00443a3d:
        fst dword ptr [esp+14h]
    L_00443a41:
        fstp dword ptr [esp+10h]
    L_00443a45:
        fld dword ptr [esp+0Ch]
    L_00443a49:
        fmul dword ptr [data_00470b0c]
    L_00443a4f:
        fst dword ptr [esp+1Ch]
    L_00443a53:
        jmp short L_00443a59
    L_00443a55:
        fld dword ptr [esp+18h]
    L_00443a59:
        fld dword ptr [esp+20h]
    L_00443a5d:
        push 0
    L_00443a5f:
        fmul dword ptr [esp+8]
    L_00443a63:
        mov eax,edx
    L_00443a65:
        fld dword ptr [esp+14h]
    L_00443a69:
        fmul dword ptr [esp+0Ch]
    L_00443a6d:
        fsubp st(1),st
    L_00443a6f:
        fadd st,st(4)
    L_00443a71:
        fstp dword ptr [data_004978c0]
    L_00443a77:
        fld dword ptr [esp+14h]
    L_00443a7b:
        fmul dword ptr [esp+8]
    L_00443a7f:
        fld dword ptr [esp+24h]
    L_00443a83:
        fmul dword ptr [esp+0Ch]
    L_00443a87:
        faddp st(1),st
    L_00443a89:
        fadd st,st(3)
    L_00443a8b:
        fstp dword ptr [data_004978c4]
    L_00443a91:
        fld st(1)
    L_00443a93:
        fmul dword ptr [esp+8]
    L_00443a97:
        fld dword ptr [esp+18h]
    L_00443a9b:
        fmul dword ptr [esp+0Ch]
    L_00443a9f:
        fsubp st(1),st
    L_00443aa1:
        fadd st,st(4)
    L_00443aa3:
        fstp dword ptr [data_004978dc]
    L_00443aa9:
        fxch
    L_00443aab:
        fmul dword ptr [esp+0Ch]
    L_00443aaf:
        fld dword ptr [esp+18h]
    L_00443ab3:
        fmul dword ptr [esp+8]
    L_00443ab7:
        faddp st(1),st
    L_00443ab9:
        fadd st,st(2)
    L_00443abb:
        fstp dword ptr [data_004978e0]
    L_00443ac1:
        fld dword ptr [esp+2Ch]
    L_00443ac5:
        fmul dword ptr [esp+8]
    L_00443ac9:
        fld st(1)
    L_00443acb:
        fmul dword ptr [esp+0Ch]
    L_00443acf:
        fsubp st(1),st
    L_00443ad1:
        fadd st,st(3)
    L_00443ad3:
        fstp dword ptr [data_004978f8]
    L_00443ad9:
        fld dword ptr [esp+8]
    L_00443add:
        fmul st,st(1)
    L_00443adf:
        fld dword ptr [esp+2Ch]
    L_00443ae3:
        fmul dword ptr [esp+0Ch]
    L_00443ae7:
        faddp st(1),st
    L_00443ae9:
        fadd st,st(2)
    L_00443aeb:
        fstp dword ptr [data_004978fc]
    L_00443af1:
        fld dword ptr [esp+30h]
    L_00443af5:
        fmul dword ptr [esp+8]
    L_00443af9:
        fld dword ptr [esp+20h]
    L_00443afd:
        fmul dword ptr [esp+0Ch]
    L_00443b01:
        fsubp st(1),st
    L_00443b03:
        fadd st,st(3)
    L_00443b05:
        fstp dword ptr [data_00497914]
    L_00443b0b:
        fld dword ptr [esp+20h]
    L_00443b0f:
        fmul dword ptr [esp+8]
    L_00443b13:
        fld dword ptr [esp+30h]
    L_00443b17:
        fmul dword ptr [esp+0Ch]
    L_00443b1b:
        faddp st(1),st
    L_00443b1d:
        fadd st,st(2)
    L_00443b1f:
        fstp dword ptr [data_00497918]
    L_00443b25:
        fstp st(0)
    L_00443b27:
        fstp st(0)
    L_00443b29:
        fstp st(0)
    L_00443b2b:
        fld dword ptr [edx+354h]
    L_00443b31:
        fadd dword ptr [edx+348h]
    L_00443b37:
        fadd dword ptr [edx+33Ch]
    L_00443b3d:
        fst dword ptr [data_0049791c]
    L_00443b43:
        fst dword ptr [data_00497900]
    L_00443b49:
        fst dword ptr [data_004978e4]
    L_00443b4f:
        fstp dword ptr [data_004978c8]
    L_00443b55:
        call asm_FUN_00442670_00442670
    L_00443b5a:
        pop esi
    L_00443b5b:
        add esp,2Ch
    L_00443b5e:
        ret
    }
}

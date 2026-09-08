#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041F670..0x0041F751: FUN_0041f670
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041f670_0041f670() {
    __asm {
    L_0041f670:
        sub esp,18h
    L_0041f673:
        mov eax,dword ptr [esp+1Ch]
    L_0041f677:
        fld dword ptr [eax]
    L_0041f679:
        fsub dword ptr [ecx+24h]
    L_0041f67c:
        fstp dword ptr [esp+0Ch]
    L_0041f680:
        fld dword ptr [eax+4]
    L_0041f683:
        fsub dword ptr [ecx+28h]
    L_0041f686:
        fstp dword ptr [esp+10h]
    L_0041f68a:
        mov edx,dword ptr [esp+10h]
    L_0041f68e:
        fld dword ptr [eax+8]
    L_0041f691:
        mov eax,dword ptr [esp+0Ch]
    L_0041f695:
        fsub dword ptr [ecx+2Ch]
    L_0041f698:
        mov dword ptr [esp],eax
    L_0041f69b:
        mov dword ptr [esp+4],edx
    L_0041f69f:
        fstp dword ptr [esp+14h]
    L_0041f6a3:
        mov eax,dword ptr [esp+14h]
    L_0041f6a7:
        fld dword ptr [ecx+3Ch]
    L_0041f6aa:
        mov dword ptr [esp+8],eax
    L_0041f6ae:
        fchs
    L_0041f6b0:
        fld st(0)
    L_0041f6b2:
        fsin
    L_0041f6b4:
        fxch
    L_0041f6b6:
        fcos
    L_0041f6b8:
        fld dword ptr [esp]
    L_0041f6bb:
        fmul st,st(1)
    L_0041f6bd:
        fld st(2)
    L_0041f6bf:
        fmul dword ptr [esp+4]
    L_0041f6c3:
        fsubp st(1),st
    L_0041f6c5:
        fstp dword ptr [esp+0Ch]
    L_0041f6c9:
        fmul dword ptr [esp+4]
    L_0041f6cd:
        fxch
    L_0041f6cf:
        fmul dword ptr [esp]
    L_0041f6d2:
        faddp st(1),st
    L_0041f6d4:
        fld dword ptr [esp+0Ch]
    L_0041f6d8:
        fsub dword ptr [esp+20h]
    L_0041f6dc:
        fld st(1)
    L_0041f6de:
        fsub dword ptr [esp+20h]
    L_0041f6e2:
        fstp dword ptr [esp+4]
    L_0041f6e6:
        fld dword ptr [esp+0Ch]
    L_0041f6ea:
        fadd dword ptr [esp+20h]
    L_0041f6ee:
        fstp dword ptr [esp+0Ch]
    L_0041f6f2:
        fxch
    L_0041f6f4:
        fadd dword ptr [esp+20h]
    L_0041f6f8:
        fstp dword ptr [esp+10h]
    L_0041f6fc:
        fcomp dword ptr [ecx+40h]
    L_0041f6ff:
        fnstsw ax
    L_0041f701:
        test ah,41h
    L_0041f704:
        je short L_0041f74a
    L_0041f706:
        fld dword ptr [ecx+44h]
    L_0041f709:
        fmul dword ptr [data_00470b0c]
    L_0041f70f:
        fcomp dword ptr [esp+4]
    L_0041f713:
        fnstsw ax
    L_0041f715:
        test ah,5
    L_0041f718:
        jnp short L_0041f74a
    L_0041f71a:
        fld dword ptr [esp+0Ch]
    L_0041f71e:
        fcomp dword ptr [data_00470b04]
    L_0041f724:
        fnstsw ax
    L_0041f726:
        test ah,5
    L_0041f729:
        jnp short L_0041f74a
    L_0041f72b:
        fld dword ptr [ecx+44h]
    L_0041f72e:
        fmul dword ptr [data_00470b78]
    L_0041f734:
        fcomp dword ptr [esp+10h]
    L_0041f738:
        fnstsw ax
    L_0041f73a:
        test ah,41h
    L_0041f73d:
        je short L_0041f74a
    L_0041f73f:
        mov eax,2
    L_0041f744:
        add esp,18h
    L_0041f747:
        ret 8
    L_0041f74a:
        xor eax,eax
    L_0041f74c:
        add esp,18h
    L_0041f74f:
        ret 8
    }
}

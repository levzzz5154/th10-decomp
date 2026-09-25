#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041E4D0..0x0041E5B1: FUN_0041e4d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041e4d0_0041e4d0() {
    __asm {
    L_0041e4d0:
        sub esp,18h
    L_0041e4d3:
        mov eax,dword ptr [esp+1Ch]
    L_0041e4d7:
        fld dword ptr [eax]
    L_0041e4d9:
        fsub dword ptr [ecx+24h]
    L_0041e4dc:
        fstp dword ptr [esp+0Ch]
    L_0041e4e0:
        fld dword ptr [eax+4]
    L_0041e4e3:
        fsub dword ptr [ecx+28h]
    L_0041e4e6:
        fstp dword ptr [esp+10h]
    L_0041e4ea:
        mov edx,dword ptr [esp+10h]
    L_0041e4ee:
        fld dword ptr [eax+8]
    L_0041e4f1:
        mov eax,dword ptr [esp+0Ch]
    L_0041e4f5:
        fsub dword ptr [ecx+2Ch]
    L_0041e4f8:
        mov dword ptr [esp],eax
    L_0041e4fb:
        mov dword ptr [esp+4],edx
    L_0041e4ff:
        fstp dword ptr [esp+14h]
    L_0041e503:
        mov eax,dword ptr [esp+14h]
    L_0041e507:
        fld dword ptr [ecx+3Ch]
    L_0041e50a:
        mov dword ptr [esp+8],eax
    L_0041e50e:
        fchs
    L_0041e510:
        fld st(0)
    L_0041e512:
        fsin
    L_0041e514:
        fxch
    L_0041e516:
        fcos
    L_0041e518:
        fld dword ptr [esp]
    L_0041e51b:
        fmul st,st(1)
    L_0041e51d:
        fld st(2)
    L_0041e51f:
        fmul dword ptr [esp+4]
    L_0041e523:
        fsubp st(1),st
    L_0041e525:
        fstp dword ptr [esp+0Ch]
    L_0041e529:
        fmul dword ptr [esp+4]
    L_0041e52d:
        fxch
    L_0041e52f:
        fmul dword ptr [esp]
    L_0041e532:
        faddp st(1),st
    L_0041e534:
        fld dword ptr [esp+0Ch]
    L_0041e538:
        fsub dword ptr [esp+20h]
    L_0041e53c:
        fld st(1)
    L_0041e53e:
        fsub dword ptr [esp+20h]
    L_0041e542:
        fstp dword ptr [esp+4]
    L_0041e546:
        fld dword ptr [esp+0Ch]
    L_0041e54a:
        fadd dword ptr [esp+20h]
    L_0041e54e:
        fstp dword ptr [esp+0Ch]
    L_0041e552:
        fxch
    L_0041e554:
        fadd dword ptr [esp+20h]
    L_0041e558:
        fstp dword ptr [esp+10h]
    L_0041e55c:
        fcomp dword ptr [ecx+40h]
    L_0041e55f:
        fnstsw ax
    L_0041e561:
        test ah,41h
    L_0041e564:
        je short L_0041e5aa
    L_0041e566:
        fld dword ptr [ecx+44h]
    L_0041e569:
        fmul dword ptr [data_00470b0c]
    L_0041e56f:
        fcomp dword ptr [esp+4]
    L_0041e573:
        fnstsw ax
    L_0041e575:
        test ah,5
    L_0041e578:
        jnp short L_0041e5aa
    L_0041e57a:
        fld dword ptr [esp+0Ch]
    L_0041e57e:
        fcomp dword ptr [data_00470b04]
    L_0041e584:
        fnstsw ax
    L_0041e586:
        test ah,5
    L_0041e589:
        jnp short L_0041e5aa
    L_0041e58b:
        fld dword ptr [ecx+44h]
    L_0041e58e:
        fmul dword ptr [data_00470b78]
    L_0041e594:
        fcomp dword ptr [esp+10h]
    L_0041e598:
        fnstsw ax
    L_0041e59a:
        test ah,41h
    L_0041e59d:
        je short L_0041e5aa
    L_0041e59f:
        mov eax,2
    L_0041e5a4:
        add esp,18h
    L_0041e5a7:
        ret 8
    L_0041e5aa:
        xor eax,eax
    L_0041e5ac:
        add esp,18h
    L_0041e5af:
        ret 8
    }
}

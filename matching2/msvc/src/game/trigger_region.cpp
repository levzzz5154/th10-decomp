#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004267F0..0x004269C6: FUN_004267f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004267f0_004267f0() {
    __asm {
    L_004267f0:
        sub esp,24h
    L_004267f3:
        fld dword ptr [ecx+3C0h]
    L_004267f9:
        fsub dword ptr [eax]
    L_004267fb:
        fstp dword ptr [esp+0Ch]
    L_004267ff:
        fld dword ptr [ecx+3C4h]
    L_00426805:
        fsub dword ptr [eax+4]
    L_00426808:
        fstp dword ptr [esp+10h]
    L_0042680c:
        mov edx,dword ptr [esp+10h]
    L_00426810:
        fld dword ptr [ecx+3C8h]
    L_00426816:
        mov dword ptr [esp+4],edx
    L_0042681a:
        fsub dword ptr [eax+8]
    L_0042681d:
        mov eax,dword ptr [esp+0Ch]
    L_00426821:
        mov dword ptr [esp],eax
    L_00426824:
        fstp dword ptr [esp+14h]
    L_00426828:
        mov eax,dword ptr [esp+14h]
    L_0042682c:
        fld dword ptr [esp+28h]
    L_00426830:
        mov dword ptr [esp+8],eax
    L_00426834:
        fchs
    L_00426836:
        fld st(0)
    L_00426838:
        fsin
    L_0042683a:
        fxch
    L_0042683c:
        fcos
    L_0042683e:
        fld dword ptr [esp]
    L_00426841:
        fmul st,st(1)
    L_00426843:
        fld st(2)
    L_00426845:
        fmul dword ptr [esp+4]
    L_00426849:
        fsubp st(1),st
    L_0042684b:
        fstp dword ptr [esp+0Ch]
    L_0042684f:
        fmul dword ptr [esp+4]
    L_00426853:
        fxch
    L_00426855:
        fmul dword ptr [esp]
    L_00426858:
        faddp st(1),st
    L_0042685a:
        fld dword ptr [esp+0Ch]
    L_0042685e:
        fsub dword ptr [ecx+41Ch]
    L_00426864:
        fstp dword ptr [esp+18h]
    L_00426868:
        mov edx,dword ptr [esp+18h]
    L_0042686c:
        mov dword ptr [esp],edx
    L_0042686f:
        fld st(0)
    L_00426871:
        fsub dword ptr [ecx+420h]
    L_00426877:
        fstp dword ptr [esp+1Ch]
    L_0042687b:
        mov eax,dword ptr [esp+1Ch]
    L_0042687f:
        fld dword ptr [esp+14h]
    L_00426883:
        mov dword ptr [esp+4],eax
    L_00426887:
        fsub dword ptr [ecx+424h]
    L_0042688d:
        fstp dword ptr [esp+20h]
    L_00426891:
        mov edx,dword ptr [esp+20h]
    L_00426895:
        fld dword ptr [esp+0Ch]
    L_00426899:
        mov dword ptr [esp+8],edx
    L_0042689d:
        fadd dword ptr [ecx+41Ch]
    L_004268a3:
        fstp dword ptr [esp+18h]
    L_004268a7:
        mov eax,dword ptr [esp+18h]
    L_004268ab:
        mov dword ptr [esp+0Ch],eax
    L_004268af:
        fadd dword ptr [ecx+420h]
    L_004268b5:
        fstp dword ptr [esp+1Ch]
    L_004268b9:
        mov edx,dword ptr [esp+1Ch]
    L_004268bd:
        fld dword ptr [esp+14h]
    L_004268c1:
        mov dword ptr [esp+10h],edx
    L_004268c5:
        fadd dword ptr [ecx+424h]
    L_004268cb:
        fstp dword ptr [esp+20h]
    L_004268cf:
        mov eax,dword ptr [esp+20h]
    L_004268d3:
        fld dword ptr [esp]
    L_004268d6:
        mov dword ptr [esp+14h],eax
    L_004268da:
        fcomp dword ptr [esp+30h]
    L_004268de:
        fnstsw ax
    L_004268e0:
        test ah,41h
    L_004268e3:
        je asm_target_004269bf
    L_004268e9:
        fld dword ptr [esp+2Ch]
    L_004268ed:
        fmul dword ptr [data_00470b0c]
    L_004268f3:
        fcomp dword ptr [esp+4]
    L_004268f7:
        fnstsw ax
    L_004268f9:
        test ah,5
    L_004268fc:
        jnp short L_0042696b
    L_004268fe:
        fld dword ptr [esp+0Ch]
    L_00426902:
        fcomp dword ptr [data_00470b04]
    L_00426908:
        fnstsw ax
    L_0042690a:
        test ah,5
    L_0042690d:
        jnp short L_0042696b
    L_0042690f:
        fld dword ptr [esp+2Ch]
    L_00426913:
        fmul dword ptr [data_00470b78]
    L_00426919:
        fcomp dword ptr [esp+10h]
    L_0042691d:
        fnstsw ax
    L_0042691f:
        test ah,41h
    L_00426922:
        je short L_0042696b
    L_00426924:
        mov eax,dword ptr [data_0047770c]
    L_00426929:
        test eax,eax
    L_0042692b:
        je short L_0042693b
    L_0042692d:
        mov edx,dword ptr [eax+9EB8h]
    L_00426933:
        test edx,edx
    L_00426935:
        jne asm_target_004269bf
    L_0042693b:
        mov eax,dword ptr [ecx+458h]
    L_00426941:
        cmp eax,2
    L_00426944:
        je short L_004269bf
    L_00426946:
        cmp eax,4
    L_00426949:
        je short L_004269bf
    L_0042694b:
        cmp eax,3
    L_0042694e:
        je short L_004269bf
    L_00426950:
        mov eax,dword ptr [ecx+4310h]
    L_00426956:
        test eax,eax
    L_00426958:
        jg short L_004269bf
    L_0042695a:
        push ecx
    L_0042695b:
        call asm_FUN_00426cf0_00426cf0
    L_00426960:
        mov eax,1
    L_00426965:
        add esp,24h
    L_00426968:
        ret 0Ch
    L_0042696b:
        fld dword ptr [esp]
    L_0042696e:
        fcomp dword ptr [esp+30h]
    L_00426972:
        fnstsw ax
    L_00426974:
        test ah,41h
    L_00426977:
        je short L_004269bf
    L_00426979:
        fld dword ptr [esp+0Ch]
    L_0042697d:
        fcomp dword ptr [data_00470b04]
    L_00426983:
        fnstsw ax
    L_00426985:
        test ah,5
    L_00426988:
        jnp short L_004269bf
    L_0042698a:
        fld dword ptr [esp+2Ch]
    L_0042698e:
        fmul dword ptr [data_00470ca8]
    L_00426994:
        fcomp dword ptr [esp+4]
    L_00426998:
        fnstsw ax
    L_0042699a:
        test ah,5
    L_0042699d:
        jnp short L_004269bf
    L_0042699f:
        fld dword ptr [esp+2Ch]
    L_004269a3:
        fmul dword ptr [data_00470ca4]
    L_004269a9:
        fcomp dword ptr [esp+4]
    L_004269ad:
        fnstsw ax
    L_004269af:
        test ah,41h
    L_004269b2:
        je short L_004269bf
    L_004269b4:
        mov eax,2
    L_004269b9:
        add esp,24h
    L_004269bc:
        ret 0Ch
    L_004269bf:
        xor eax,eax
    L_004269c1:
        add esp,24h
    L_004269c4:
        ret 0Ch
    }
}

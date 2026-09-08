#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004436C0..0x0044390E: FUN_004436c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004436c0_004436c0() {
    __asm {
    L_004436c0:
        fld dword ptr [data_00470b04]
    L_004436c6:
        sub esp,2Ch
    L_004436c9:
        fld dword ptr [edx+2Ch]
    L_004436cc:
        fucompp
    L_004436ce:
        fnstsw ax
    L_004436d0:
        test ah,44h
    L_004436d3:
        jp short L_004436e1
    L_004436d5:
        push ecx
    L_004436d6:
        mov eax,edx
    L_004436d8:
        call asm_FUN_00443290_00443290
    L_004436dd:
        add esp,2Ch
    L_004436e0:
        ret
    L_004436e1:
        mov eax,dword ptr [edx+2Ch]
    L_004436e4:
        push esi
    L_004436e5:
        mov dword ptr [esp+0Ch],eax
    L_004436e9:
        fld dword ptr [esp+0Ch]
    L_004436ed:
        fsincos
    L_004436ef:
        fstp dword ptr [esp+4]
    L_004436f3:
        fstp dword ptr [esp+8]
    L_004436f7:
        fld dword ptr [edx+34Ch]
    L_004436fd:
        fadd dword ptr [edx+340h]
    L_00443703:
        mov esi,dword ptr [edx+35Ch]
    L_00443709:
        mov eax,esi
    L_0044370b:
        shr eax,12h
    L_0044370e:
        fadd dword ptr [edx+334h]
    L_00443714:
        and eax,3
    L_00443717:
        sub eax,0
    L_0044371a:
        fld dword ptr [edx+350h]
    L_00443720:
        fadd dword ptr [edx+344h]
    L_00443726:
        fadd dword ptr [edx+338h]
    L_0044372c:
        fld dword ptr [edx+4Ch]
    L_0044372f:
        fmul dword ptr [edx+3Ch]
    L_00443732:
        fld dword ptr [edx+50h]
    L_00443735:
        fmul dword ptr [edx+40h]
    L_00443738:
        fstp dword ptr [esp+0Ch]
    L_0044373c:
        je short L_00443774
    L_0044373e:
        dec eax
    L_0044373f:
        je short L_0044375e
    L_00443741:
        dec eax
    L_00443742:
        jne short L_00443790
    L_00443744:
        fchs
    L_00443746:
        mov dword ptr [esp+2Ch],0
    L_0044374e:
        fst dword ptr [esp+28h]
    L_00443752:
        fstp dword ptr [esp+20h]
    L_00443756:
        fld dword ptr [data_00470b04]
    L_0044375c:
        jmp short L_00443796
    L_0044375e:
        fst dword ptr [esp+2Ch]
    L_00443762:
        mov dword ptr [esp+28h],0
    L_0044376a:
        mov dword ptr [esp+20h],0
    L_00443772:
        jmp short L_00443796
    L_00443774:
        fld dword ptr [data_00470b78]
    L_0044377a:
        fmul st,st(1)
    L_0044377c:
        fst dword ptr [esp+28h]
    L_00443780:
        fstp dword ptr [esp+20h]
    L_00443784:
        fmul dword ptr [data_00470b0c]
    L_0044378a:
        fst dword ptr [esp+2Ch]
    L_0044378e:
        jmp short L_00443796
    L_00443790:
        fstp st(0)
    L_00443792:
        fld dword ptr [esp+24h]
    L_00443796:
        shr esi,14h
    L_00443799:
        and esi,3
    L_0044379c:
        sub esi,0
    L_0044379f:
        je short L_004437e3
    L_004437a1:
        dec esi
    L_004437a2:
        je short L_004437c5
    L_004437a4:
        dec esi
    L_004437a5:
        jne short L_00443805
    L_004437a7:
        fld dword ptr [esp+0Ch]
    L_004437ab:
        mov dword ptr [esp+1Ch],0
    L_004437b3:
        fchs
    L_004437b5:
        fst dword ptr [esp+14h]
    L_004437b9:
        fstp dword ptr [esp+10h]
    L_004437bd:
        fld dword ptr [data_00470b04]
    L_004437c3:
        jmp short L_00443809
    L_004437c5:
        mov eax,dword ptr [esp+0Ch]
    L_004437c9:
        fld dword ptr [esp+0Ch]
    L_004437cd:
        mov dword ptr [esp+14h],0
    L_004437d5:
        mov dword ptr [esp+10h],0
    L_004437dd:
        mov dword ptr [esp+1Ch],eax
    L_004437e1:
        jmp short L_00443809
    L_004437e3:
        fld dword ptr [esp+0Ch]
    L_004437e7:
        fmul dword ptr [data_00470b78]
    L_004437ed:
        fst dword ptr [esp+14h]
    L_004437f1:
        fstp dword ptr [esp+10h]
    L_004437f5:
        fld dword ptr [esp+0Ch]
    L_004437f9:
        fmul dword ptr [data_00470b0c]
    L_004437ff:
        fst dword ptr [esp+1Ch]
    L_00443803:
        jmp short L_00443809
    L_00443805:
        fld dword ptr [esp+18h]
    L_00443809:
        fld dword ptr [esp+20h]
    L_0044380d:
        push 0
    L_0044380f:
        fmul dword ptr [esp+8]
    L_00443813:
        mov eax,edx
    L_00443815:
        fld dword ptr [esp+14h]
    L_00443819:
        fmul dword ptr [esp+0Ch]
    L_0044381d:
        fsubp st(1),st
    L_0044381f:
        fadd st,st(4)
    L_00443821:
        fstp dword ptr [data_004978c0]
    L_00443827:
        fld dword ptr [esp+14h]
    L_0044382b:
        fmul dword ptr [esp+8]
    L_0044382f:
        fld dword ptr [esp+24h]
    L_00443833:
        fmul dword ptr [esp+0Ch]
    L_00443837:
        faddp st(1),st
    L_00443839:
        fadd st,st(3)
    L_0044383b:
        fstp dword ptr [data_004978c4]
    L_00443841:
        fld st(1)
    L_00443843:
        fmul dword ptr [esp+8]
    L_00443847:
        fld dword ptr [esp+18h]
    L_0044384b:
        fmul dword ptr [esp+0Ch]
    L_0044384f:
        fsubp st(1),st
    L_00443851:
        fadd st,st(4)
    L_00443853:
        fstp dword ptr [data_004978dc]
    L_00443859:
        fxch
    L_0044385b:
        fmul dword ptr [esp+0Ch]
    L_0044385f:
        fld dword ptr [esp+18h]
    L_00443863:
        fmul dword ptr [esp+8]
    L_00443867:
        faddp st(1),st
    L_00443869:
        fadd st,st(2)
    L_0044386b:
        fstp dword ptr [data_004978e0]
    L_00443871:
        fld dword ptr [esp+2Ch]
    L_00443875:
        fmul dword ptr [esp+8]
    L_00443879:
        fld st(1)
    L_0044387b:
        fmul dword ptr [esp+0Ch]
    L_0044387f:
        fsubp st(1),st
    L_00443881:
        fadd st,st(3)
    L_00443883:
        fstp dword ptr [data_004978f8]
    L_00443889:
        fld dword ptr [esp+8]
    L_0044388d:
        fmul st,st(1)
    L_0044388f:
        fld dword ptr [esp+2Ch]
    L_00443893:
        fmul dword ptr [esp+0Ch]
    L_00443897:
        faddp st(1),st
    L_00443899:
        fadd st,st(2)
    L_0044389b:
        fstp dword ptr [data_004978fc]
    L_004438a1:
        fld dword ptr [esp+30h]
    L_004438a5:
        fmul dword ptr [esp+8]
    L_004438a9:
        fld dword ptr [esp+20h]
    L_004438ad:
        fmul dword ptr [esp+0Ch]
    L_004438b1:
        fsubp st(1),st
    L_004438b3:
        fadd st,st(3)
    L_004438b5:
        fstp dword ptr [data_00497914]
    L_004438bb:
        fld dword ptr [esp+20h]
    L_004438bf:
        fmul dword ptr [esp+8]
    L_004438c3:
        fld dword ptr [esp+30h]
    L_004438c7:
        fmul dword ptr [esp+0Ch]
    L_004438cb:
        faddp st(1),st
    L_004438cd:
        fadd st,st(2)
    L_004438cf:
        fstp dword ptr [data_00497918]
    L_004438d5:
        fstp st(0)
    L_004438d7:
        fstp st(0)
    L_004438d9:
        fstp st(0)
    L_004438db:
        fld dword ptr [edx+354h]
    L_004438e1:
        fadd dword ptr [edx+348h]
    L_004438e7:
        fadd dword ptr [edx+33Ch]
    L_004438ed:
        fst dword ptr [data_0049791c]
    L_004438f3:
        fst dword ptr [data_00497900]
    L_004438f9:
        fst dword ptr [data_004978e4]
    L_004438ff:
        fstp dword ptr [data_004978c8]
    L_00443905:
        call asm_FUN_00442670_00442670
    L_0044390a:
        pop esi
    L_0044390b:
        add esp,2Ch
    L_0044390e:
        ret
    }
}

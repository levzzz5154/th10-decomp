// BLOCKED (H2501): closest_byte_count=554/598; first_diff=unmeasured;
// residual_class=private callee-preserved-register ABI: retail keeps this in
// EDX across Vector2_SetPolar at 0x004458B0. That callee now has an exact
// ordinary GCC C++ body, but MSVC's separate caller compilation cannot infer
// its private EDX-preservation contract and promotes this to EBP instead;
// variants_tested=nested-loop model, unrolled-loop model, full particle/ring
// layout reconstruction, and available plain source shapes;
// next_lever=express the caller's EDX preservation to its compiler without
// changing the binary ABI; retain this wrapper.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00445620..0x004456EC: FUN_00445620
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00445620_00445620() {
    __asm {
    L_00445620:
        sub esp,18h
    L_00445623:
        mov edx,ecx
    L_00445625:
        fld dword ptr [edx+340h]
    L_0044562b:
        push ebx
    L_0044562c:
        fadd dword ptr [edx+334h]
    L_00445632:
        push ebp
    L_00445633:
        mov ebp,dword ptr [edx+358h]
    L_00445639:
        mov eax,ebp
    L_0044563b:
        fstp dword ptr [esp+14h]
    L_0044563f:
        mov ecx,dword ptr [esp+14h]
    L_00445643:
        fld dword ptr [edx+344h]
    L_00445649:
        push esi
    L_0044564a:
        fadd dword ptr [edx+338h]
    L_00445650:
        push edi
    L_00445651:
        mov dword ptr [esp+10h],0C0490FDBh
    L_00445659:
        fstp dword ptr [esp+20h]
    L_0044565d:
        fld dword ptr [edx+348h]
    L_00445663:
        fadd dword ptr [edx+33Ch]
    L_00445669:
        mov dword ptr [eax],ecx
    L_0044566b:
        mov ecx,dword ptr [esp+20h]
    L_0044566f:
        mov dword ptr [eax+4],ecx
    L_00445672:
        fstp dword ptr [esp+24h]
    L_00445676:
        mov ecx,dword ptr [esp+24h]
    L_0044567a:
        fld dword ptr [ebp+4A4h]
    L_00445680:
        mov dword ptr [eax+8],ecx
    L_00445683:
        fadd dword ptr [ebp+14h]
    L_00445686:
        fst dword ptr [ebp+14h]
    L_00445689:
        fcomp dword ptr [data_00470b04]
    L_0044568f:
        fnstsw ax
    L_00445691:
        test ah,5
    L_00445694:
        jp short L_004456ca
    L_00445696:
        lea eax,[ebp+30h]
    L_00445699:
        mov ecx,0Bh
    L_0044569e:
        mov edi,edi
    L_004456a0:
        fld dword ptr [eax-1Ch]
    L_004456a3:
        add eax,54h
    L_004456a6:
        dec ecx
    L_004456a7:
        fadd dword ptr [data_00470afc]
    L_004456ad:
        fstp dword ptr [eax-70h]
    L_004456b0:
        fld dword ptr [eax-54h]
    L_004456b3:
        fadd dword ptr [data_00470afc]
    L_004456b9:
        fstp dword ptr [eax-54h]
    L_004456bc:
        fld dword ptr [eax-38h]
    L_004456bf:
        fadd dword ptr [data_00470afc]
    L_004456c5:
        fstp dword ptr [eax-38h]
    L_004456c8:
        jne short L_004456a0
    L_004456ca:
        fld dword ptr [ebp+4A4h]
    L_004456d0:
        fadd dword ptr [ebp+18h]
    L_004456d3:
        fst dword ptr [ebp+18h]
    L_004456d6:
        fcomp dword ptr [data_00470b04]
    L_004456dc:
        fnstsw ax
    L_004456de:
        test ah,5
    L_004456e1:
        TH10_REL8(0x7a, 0x004456e1, VA_asm_target_0044571a)
    L_004456e3:
        lea eax,[ebp+34h]
    L_004456e6:
        mov ecx,0Bh
    L_004456eb:
        TH10_REL8(0xeb, 0x004456eb, VA_asm_FUN_00445620_part_004456f0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004456f0:
        fld dword ptr [eax-1Ch]
    L_004456f3:
        add eax,54h
    L_004456f6:
        dec ecx
    L_004456f7:
        fadd dword ptr [data_00470afc]
    L_004456fd:
        fstp dword ptr [eax-70h]
    L_00445700:
        fld dword ptr [eax-54h]
    L_00445703:
        fadd dword ptr [data_00470afc]
    L_00445709:
        fstp dword ptr [eax-54h]
    L_0044570c:
        fld dword ptr [eax-38h]
    L_0044570f:
        fadd dword ptr [data_00470afc]
    L_00445715:
        fstp dword ptr [eax-38h]
    L_00445718:
        jne short L_004456f0
    L_0044571a:
        mov eax,dword ptr [edx+2FCh]
    L_00445720:
        lea edi,[ebp+1Ch]
    L_00445723:
        mov dword ptr [ebp+10h],eax
    L_00445726:
        mov dword ptr [esp+18h],edi
    L_0044572a:
        lea esi,[ebp+3A0h]
    L_00445730:
        mov ebx,1Fh
    L_00445735:
        TH10_REL8(0xeb, 0x00445735, VA_asm_FUN_00445620_part_00445740)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_00445740:
        fld dword ptr [ebp+4A4h]
    L_00445746:
        fadd dword ptr [edi+14h]
    L_00445749:
        fst dword ptr [edi+14h]
    L_0044574c:
        fcomp dword ptr [data_00470b04]
    L_00445752:
        fnstsw ax
    L_00445754:
        test ah,5
    L_00445757:
        jp short L_0044578b
    L_00445759:
        lea eax,[ebp+30h]
    L_0044575c:
        mov ecx,0Bh
    L_00445761:
        fld dword ptr [eax-1Ch]
    L_00445764:
        add eax,54h
    L_00445767:
        dec ecx
    L_00445768:
        fadd dword ptr [data_00470afc]
    L_0044576e:
        fstp dword ptr [eax-70h]
    L_00445771:
        fld dword ptr [eax-54h]
    L_00445774:
        fadd dword ptr [data_00470afc]
    L_0044577a:
        fstp dword ptr [eax-54h]
    L_0044577d:
        fld dword ptr [eax-38h]
    L_00445780:
        fadd dword ptr [data_00470afc]
    L_00445786:
        fstp dword ptr [eax-38h]
    L_00445789:
        jne short L_00445761
    L_0044578b:
        fld dword ptr [edi+18h]
    L_0044578e:
        fadd dword ptr [ebp+4A4h]
    L_00445794:
        fst dword ptr [edi+18h]
    L_00445797:
        fcomp dword ptr [data_00470b04]
    L_0044579d:
        fnstsw ax
    L_0044579f:
        test ah,5
    L_004457a2:
        jp short L_004457da
    L_004457a4:
        lea eax,[ebp+34h]
    L_004457a7:
        mov ecx,0Bh
    L_004457ac:
        TH10_NOP_LEA_ESP_DISP8()
    L_004457b0:
        fld dword ptr [eax-1Ch]
    L_004457b3:
        add eax,54h
    L_004457b6:
        dec ecx
    L_004457b7:
        fadd dword ptr [data_00470afc]
    L_004457bd:
        fstp dword ptr [eax-70h]
    L_004457c0:
        fld dword ptr [eax-54h]
    L_004457c3:
        fadd dword ptr [data_00470afc]
    L_004457c9:
        fstp dword ptr [eax-54h]
    L_004457cc:
        fld dword ptr [eax-38h]
    L_004457cf:
        fadd dword ptr [data_00470afc]
    L_004457d5:
        fstp dword ptr [eax-38h]
    L_004457d8:
        jne short L_004457b0
    L_004457da:
        mov ecx,dword ptr [edx+2FCh]
    L_004457e0:
        mov dword ptr [edi+10h],ecx
    L_004457e3:
        mov ecx,dword ptr [esp+10h]
    L_004457e7:
        mov byte ptr [edi+13h],0
    L_004457eb:
        fld dword ptr [esi+84h]
    L_004457f1:
        fadd dword ptr [esi]
    L_004457f3:
        fst dword ptr [esp+14h]
    L_004457f7:
        mov eax,dword ptr [esp+14h]
    L_004457fb:
        fstp dword ptr [esi]
    L_004457fd:
        push eax
    L_004457fe:
        push ecx
    L_004457ff:
        mov ecx,edi
    L_00445801:
        call asm_Vector2_SetPolar_004458b0
    L_00445806:
        fld dword ptr [edx+340h]
    L_0044580c:
        fadd dword ptr [edx+334h]
    L_00445812:
        add edi,1Ch
    L_00445815:
        fld dword ptr [edx+338h]
    L_0044581b:
        add esi,4
    L_0044581e:
        dec ebx
    L_0044581f:
        fadd dword ptr [edx+344h]
    L_00445825:
        fld dword ptr [edx+348h]
    L_0044582b:
        fadd dword ptr [edx+33Ch]
    L_00445831:
        fstp dword ptr [esp+24h]
    L_00445835:
        fxch
    L_00445837:
        fadd dword ptr [edi-1Ch]
    L_0044583a:
        fstp dword ptr [edi-1Ch]
    L_0044583d:
        fadd dword ptr [edi-18h]
    L_00445840:
        fstp dword ptr [edi-18h]
    L_00445843:
        fld dword ptr [esp+24h]
    L_00445847:
        fadd dword ptr [edi-14h]
    L_0044584a:
        fstp dword ptr [edi-14h]
    L_0044584d:
        fld dword ptr [esp+10h]
    L_00445851:
        fadd dword ptr [data_00470b6c]
    L_00445857:
        fstp dword ptr [esp+10h]
    L_0044585b:
        jne asm_FUN_00445620_part_00445740
    L_00445861:
        mov esi,dword ptr [esp+18h]
    L_00445865:
        mov ecx,7
    L_0044586a:
        rep movsd
    L_0044586c:
        pop edi
    L_0044586d:
        pop esi
    L_0044586e:
        pop ebp
    L_0044586f:
        xor eax,eax
    L_00445871:
        pop ebx
    L_00445872:
        add esp,18h
    L_00445875:
        ret
    }
}

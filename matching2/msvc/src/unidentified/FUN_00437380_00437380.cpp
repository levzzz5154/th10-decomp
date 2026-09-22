// BLOCKED (D3702): closest_byte_count=0/525; first_diff=extent (candidate
// extent 527 vs retail 525).
// residual_class=abi+structural: readable Win32 text candidate emitted a
// 527-byte body (two bytes over retail) while retail uses EAX/EDI/EBX private
// live-ins, stack-local RECT placement, and indirect GDI import slots.
// variants_tested=archived Ghidra pseudocode, caller 0x004372A0, and MSVC
// 13.10 readable candidate probe (527-byte extent vs 525-byte retail).
// next_lever=restore the missing live Ghidra function boundary, then compile
// the caller with the exact GDI import declarations and native register ABI.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00437380..0x0043758C: FUN_00437380
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00437380_00437380() {
    __asm {
    L_00437380:
        sub esp,88h
    L_00437386:
        test edi,edi
    L_00437388:
        push ebp
    L_00437389:
        mov ebp,dword ptr [esp+94h]
    L_00437390:
        jne short L_0043739e
    L_00437392:
        xor al,al
    L_00437394:
        pop ebp
    L_00437395:
        add esp,88h
    L_0043739b:
        ret 14h
    L_0043739e:
        mov ecx,dword ptr [eax+104h]
    L_004373a4:
        mov edx,dword ptr [eax+108h]
    L_004373aa:
        push ebx
    L_004373ab:
        push esi
    L_004373ac:
        mov esi,dword ptr [eax+114h]
    L_004373b2:
        mov eax,dword ptr [esp+0A0h]
    L_004373b9:
        push eax
    L_004373ba:
        push esi
    L_004373bb:
        mov dword ptr [esp+18h],ecx
    L_004373bf:
        mov dword ptr [esp+1Ch],edx
    L_004373c3:
        call dword ptr [data_0046602c]
    L_004373c9:
        push 1
    L_004373cb:
        push esi
    L_004373cc:
        mov dword ptr [esp+24h],eax
    L_004373d0:
        call dword ptr [data_0046601c]
    L_004373d6:
        mov eax,dword ptr [esp+0A8h]
    L_004373dd:
        cmp eax,0FFFFFFFFh
    L_004373e0:
        mov ebx,dword ptr [data_00466268]
    L_004373e6:
        je asm_target_0043752a
    L_004373ec:
        push eax
    L_004373ed:
        push esi
    L_004373ee:
        call dword ptr [data_00466018]
    L_004373f4:
        mov eax,dword ptr [esp+98h]
    L_004373fb:
        mov ecx,dword ptr [esp+10h]
    L_004373ff:
        mov edx,dword ptr [esp+14h]
    L_00437403:
        mov dword ptr [esp+24h],eax
    L_00437407:
        add eax,ecx
    L_00437409:
        mov dword ptr [esp+0Ch],eax
    L_0043740d:
        add eax,0FFFFFFFEh
    L_00437410:
        mov dword ptr [esp+2Ch],eax
    L_00437414:
        lea eax,[edx+ebp]
    L_00437417:
        add eax,0FFFFFFFEh
    L_0043741a:
        push 0
    L_0043741c:
        mov dword ptr [esp+34h],eax
    L_00437420:
        lea eax,[esp+28h]
    L_00437424:
        push eax
    L_00437425:
        push 0FFFFFFFFh
    L_00437427:
        push edi
    L_00437428:
        push esi
    L_00437429:
        mov dword ptr [esp+3Ch],ebp
    L_0043742d:
        call ebx
    L_0043742f:
        mov edx,dword ptr [esp+14h]
    L_00437433:
        mov eax,dword ptr [esp+98h]
    L_0043743a:
        mov ecx,dword ptr [esp+0Ch]
    L_0043743e:
        add edx,ebp
    L_00437440:
        mov dword ptr [esp+18h],edx
    L_00437444:
        mov dword ptr [esp+50h],edx
    L_00437448:
        mov edx,dword ptr [esp+98h]
    L_0043744f:
        add eax,2
    L_00437452:
        add ecx,2
    L_00437455:
        inc edx
    L_00437456:
        mov dword ptr [esp+54h],edx
    L_0043745a:
        lea edx,[ebp+2]
    L_0043745d:
        mov dword ptr [esp+58h],edx
    L_00437461:
        mov edx,dword ptr [esp+0Ch]
    L_00437465:
        inc edx
    L_00437466:
        mov dword ptr [esp+5Ch],edx
    L_0043746a:
        mov edx,dword ptr [esp+18h]
    L_0043746e:
        add edx,2
    L_00437471:
        mov dword ptr [esp+20h],edx
    L_00437475:
        mov dword ptr [esp+60h],edx
    L_00437479:
        mov edx,dword ptr [esp+18h]
    L_0043747d:
        mov dword ptr [esp+70h],edx
    L_00437481:
        mov edx,dword ptr [esp+98h]
    L_00437488:
        mov dword ptr [esp+44h],eax
    L_0043748c:
        mov dword ptr [esp+64h],eax
    L_00437490:
        mov dword ptr [esp+84h],eax
    L_00437497:
        lea eax,[ebp+2]
    L_0043749a:
        push 0
    L_0043749c:
        mov dword ptr [esp+78h],edx
    L_004374a0:
        mov dword ptr [esp+8Ch],eax
    L_004374a7:
        lea eax,[esp+48h]
    L_004374ab:
        push eax
    L_004374ac:
        lea edx,[ebp+2]
    L_004374af:
        mov dword ptr [esp+80h],edx
    L_004374b6:
        mov edx,dword ptr [esp+14h]
    L_004374ba:
        push 0FFFFFFFFh
    L_004374bc:
        mov dword ptr [esp+88h],edx
    L_004374c3:
        mov edx,dword ptr [esp+2Ch]
    L_004374c7:
        push edi
    L_004374c8:
        push esi
    L_004374c9:
        mov dword ptr [esp+5Ch],ebp
    L_004374cd:
        mov dword ptr [esp+60h],ecx
    L_004374d1:
        mov dword ptr [esp+7Ch],ebp
    L_004374d5:
        mov dword ptr [esp+80h],ecx
    L_004374dc:
        mov dword ptr [esp+94h],edx
    L_004374e3:
        mov dword ptr [esp+0A0h],ecx
    L_004374ea:
        mov dword ptr [esp+0A4h],edx
    L_004374f1:
        call ebx
    L_004374f3:
        push 0
    L_004374f5:
        lea ecx,[esp+58h]
    L_004374f9:
        push ecx
    L_004374fa:
        push 0FFFFFFFFh
    L_004374fc:
        push edi
    L_004374fd:
        push esi
    L_004374fe:
        call ebx
    L_00437500:
        push 0
    L_00437502:
        lea edx,[esp+68h]
    L_00437506:
        push edx
    L_00437507:
        push 0FFFFFFFFh
    L_00437509:
        push edi
    L_0043750a:
        push esi
    L_0043750b:
        call ebx
    L_0043750d:
        push 0
    L_0043750f:
        lea eax,[esp+78h]
    L_00437513:
        push eax
    L_00437514:
        push 0FFFFFFFFh
    L_00437516:
        push edi
    L_00437517:
        push esi
    L_00437518:
        call ebx
    L_0043751a:
        push 0
    L_0043751c:
        lea ecx,[esp+88h]
    L_00437523:
        push ecx
    L_00437524:
        push 0FFFFFFFFh
    L_00437526:
        push edi
    L_00437527:
        push esi
    L_00437528:
        call ebx
    L_0043752a:
        mov edx,dword ptr [esp+0A4h]
    L_00437531:
        push edx
    L_00437532:
        push esi
    L_00437533:
        call dword ptr [data_00466018]
    L_00437539:
        mov eax,dword ptr [esp+98h]
    L_00437540:
        lea ecx,[eax+1]
    L_00437543:
        mov dword ptr [esp+34h],ecx
    L_00437547:
        mov ecx,dword ptr [esp+10h]
    L_0043754b:
        lea edx,[ebp+1]
    L_0043754e:
        mov dword ptr [esp+38h],edx
    L_00437552:
        lea edx,[ecx+eax+1]
    L_00437556:
        mov eax,dword ptr [esp+14h]
    L_0043755a:
        push 0
    L_0043755c:
        mov dword ptr [esp+40h],edx
    L_00437560:
        lea edx,[esp+38h]
    L_00437564:
        push edx
    L_00437565:
        push 0FFFFFFFFh
    L_00437567:
        push edi
    L_00437568:
        lea ecx,[eax+ebp+1]
    L_0043756c:
        push esi
    L_0043756d:
        mov dword ptr [esp+54h],ecx
    L_00437571:
        call ebx
    L_00437573:
        mov eax,dword ptr [esp+1Ch]
    L_00437577:
        push eax
    L_00437578:
        push esi
    L_00437579:
        call dword ptr [data_0046602c]
    L_0043757f:
        pop esi
    L_00437580:
        pop ebx
    L_00437581:
        mov al,1
    L_00437583:
        pop ebp
    L_00437584:
        add esp,88h
    L_0043758a:
        ret 14h
    }
}

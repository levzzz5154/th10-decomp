// BLOCKED (H2601): closest_byte_count=679; first_diff=unmeasured;
// residual_class=structural: absolute jump-table layout plus schema-2 dispatch
// ABI: the 0x004125F8 table is a separately anchored continuation, while
// leaves return mixed integer/x87 values through the private ECX/global-state
// convention;
// variants_tested=exact retail naked wrapper, switch/jump-table semantic model,
// and the paired 0x00411FC0 accessor family from the same disassembly;
// next_lever=co-compile this fragment with an address-pinned jump-table anchor
// and both dispatch families; do not replace the exact wrapper with a C++ switch.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412350..0x004125F6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412350() {
    __asm {
    L_00412350:
        mov eax,dword ptr [esp+4]
    L_00412354:
        add eax,2710h
    L_00412359:
        cmp eax,32h
    L_0041235c:
        ja asm_target_004125ee
    L_00412362:
        jmp dword ptr [eax*4+4125F8h]
    L_00412369:
        mov ecx,4918B0h
    L_0041236e:
        call asm_Rng_NextU32_0044b9e0
    L_00412373:
        test eax,eax
    L_00412375:
        mov dword ptr [esp+4],eax
    L_00412379:
        fild dword ptr [esp+4]
    L_0041237d:
        jge asm_target_004125f4
    L_00412383:
        fadd dword ptr [data_00470b98]
    L_00412389:
        ret 4
    L_0041238c:
        mov ecx,4918B0h
    L_00412391:
        call asm_Rng_NextFloat_0044bb20
    L_00412396:
        ret 4
    L_00412399:
        mov ecx,4918B0h
    L_0041239e:
        call asm_Rng_NextFloatSigned_0044bb90
    L_004123a3:
        ret 4
    L_004123a6:
        mov ecx,4918B0h
    L_004123ab:
        call asm_Rng_NextFloatSigned_0044bb90
    L_004123b0:
        fmul dword ptr [data_00470b18]
    L_004123b6:
        ret 4
    L_004123b9:
        lea eax,[ecx+1068h]
    L_004123bf:
        mov ecx,dword ptr [data_00477834]
    L_004123c5:
        call asm_Entity_AngleFromPoint_00426660
    L_004123ca:
        ret 4
    L_004123cd:
        fld dword ptr [ecx+1160h]
    L_004123d3:
        ret 4
    L_004123d6:
        xor edx,edx
    L_004123d8:
        mov dl,byte ptr [ecx+2482h]
    L_004123de:
        and edx,1
    L_004123e1:
        mov dword ptr [esp+4],edx
    L_004123e5:
        fild dword ptr [esp+4]
    L_004123e9:
        ret 4
    L_004123ec:
        fild dword ptr [ecx+1138h]
    L_004123f2:
        ret 4
    L_004123f5:
        fild dword ptr [ecx+113Ch]
    L_004123fb:
        ret 4
    L_004123fe:
        fild dword ptr [ecx+1140h]
    L_00412404:
        ret 4
    L_00412407:
        fild dword ptr [ecx+1144h]
    L_0041240d:
        ret 4
    L_00412410:
        fld dword ptr [ecx+1148h]
    L_00412416:
        ret 4
    L_00412419:
        fld dword ptr [ecx+114Ch]
    L_0041241f:
        ret 4
    L_00412422:
        fld dword ptr [ecx+1150h]
    L_00412428:
        ret 4
    L_0041242b:
        fld dword ptr [ecx+1154h]
    L_00412431:
        ret 4
    L_00412434:
        fld dword ptr [ecx+1068h]
    L_0041243a:
        ret 4
    L_0041243d:
        fld dword ptr [ecx+106Ch]
    L_00412443:
        ret 4
    L_00412446:
        fld dword ptr [ecx+1094h]
    L_0041244c:
        ret 4
    L_0041244f:
        fld dword ptr [ecx+1098h]
    L_00412455:
        ret 4
    L_00412458:
        fld dword ptr [ecx+10C0h]
    L_0041245e:
        ret 4
    L_00412461:
        fld dword ptr [ecx+10C4h]
    L_00412467:
        ret 4
    L_0041246a:
        fld dword ptr [ecx+10B0h]
    L_00412470:
        ret 4
    L_00412473:
        fld dword ptr [ecx+10DCh]
    L_00412479:
        ret 4
    L_0041247c:
        fld dword ptr [ecx+1078h]
    L_00412482:
        fld dword ptr [ecx+1074h]
    L_00412488:
        fpatan
    L_0041248a:
        ret 4
    L_0041248d:
        fld dword ptr [ecx+10ACh]
    L_00412493:
        ret 4
    L_00412496:
        fld dword ptr [ecx+10D8h]
    L_0041249c:
        ret 4
    L_0041249f:
        fld dword ptr [ecx+10B4h]
    L_004124a5:
        ret 4
    L_004124a8:
        fld dword ptr [ecx+10E0h]
    L_004124ae:
        ret 4
    L_004124b1:
        mov eax,dword ptr [data_00477834]
    L_004124b6:
        fld dword ptr [eax+3C0h]
    L_004124bc:
        ret 4
    L_004124bf:
        mov ecx,dword ptr [data_00477834]
    L_004124c5:
        fld dword ptr [ecx+3C4h]
    L_004124cb:
        ret 4
    L_004124ce:
        mov edx,dword ptr [data_00477704]
    L_004124d4:
        mov eax,dword ptr [edx+10h]
    L_004124d7:
        fld dword ptr [eax+1068h]
    L_004124dd:
        ret 4
    L_004124e0:
        mov ecx,dword ptr [data_00477704]
    L_004124e6:
        mov edx,dword ptr [ecx+10h]
    L_004124e9:
        fld dword ptr [edx+106Ch]
    L_004124ef:
        ret 4
    L_004124f2:
        fild dword ptr [data_00474c98]
    L_004124f8:
        ret 4
    L_004124fb:
        fild dword ptr [data_00474c74]
    L_00412501:
        ret 4
    L_00412504:
        fld dword ptr [data_00470afc]
    L_0041250a:
        ret 4
    L_0041250d:
        lea eax,[ecx+1094h]
    L_00412513:
        mov ecx,dword ptr [data_00477834]
    L_00412519:
        call asm_Entity_AngleFromPoint_00426660
    L_0041251e:
        ret 4
    L_00412521:
        lea eax,[ecx+10C0h]
    L_00412527:
        mov ecx,dword ptr [data_00477834]
    L_0041252d:
        call asm_Entity_AngleFromPoint_00426660
    L_00412532:
        ret 4
    L_00412535:
        fild dword ptr [ecx+23FCh]
    L_0041253b:
        ret 4
    L_0041253e:
        fild dword ptr [data_00474c74]
    L_00412544:
        mov dword ptr [esp+4],1
    L_0041254c:
        fld dword ptr [data_00470b04]
    L_00412552:
        fucompp
    L_00412554:
        fnstsw ax
    L_00412556:
        test ah,44h
    L_00412559:
        jnp short L_00412563
    L_0041255b:
        mov dword ptr [esp+4],0
    L_00412563:
        fild dword ptr [esp+4]
    L_00412567:
        ret 4
    L_0041256a:
        fild dword ptr [data_00474c74]
    L_00412570:
        mov dword ptr [esp+4],1
    L_00412578:
        fld dword ptr [data_00470afc]
    L_0041257e:
        fucompp
    L_00412580:
        fnstsw ax
    L_00412582:
        test ah,44h
    L_00412585:
        jnp short L_0041258f
    L_00412587:
        mov dword ptr [esp+4],0
    L_0041258f:
        fild dword ptr [esp+4]
    L_00412593:
        ret 4
    L_00412596:
        fild dword ptr [data_00474c74]
    L_0041259c:
        mov dword ptr [esp+4],1
    L_004125a4:
        fld dword ptr [data_00470b08]
    L_004125aa:
        fucompp
    L_004125ac:
        fnstsw ax
    L_004125ae:
        test ah,44h
    L_004125b1:
        jnp short L_004125bb
    L_004125b3:
        mov dword ptr [esp+4],0
    L_004125bb:
        fild dword ptr [esp+4]
    L_004125bf:
        ret 4
    L_004125c2:
        fild dword ptr [data_00474c74]
    L_004125c8:
        mov dword ptr [esp+4],1
    L_004125d0:
        fld dword ptr [data_00470bd4]
    L_004125d6:
        fucompp
    L_004125d8:
        fnstsw ax
    L_004125da:
        test ah,44h
    L_004125dd:
        jnp short L_004125e7
    L_004125df:
        mov dword ptr [esp+4],0
    L_004125e7:
        fild dword ptr [esp+4]
    L_004125eb:
        ret 4
    L_004125ee:
        fld dword ptr [data_00470b04]
    L_004125f4:
        ret 4
    }
}

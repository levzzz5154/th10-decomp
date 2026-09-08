#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464110..0x00464915: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00464110() {
    __asm {
    L_00464110:
        fld tbyte ptr [esp+10h]
    L_00464114:
        fld tbyte ptr [esp+4]
    L_00464118:
        mov eax,dword ptr [esp+8]
    L_0046411c:
        add eax,eax
    L_0046411e:
        jae asm_target_004641aa
    L_00464124:
        xor eax,0E000000h
    L_00464129:
        test eax,0E000000h
    L_0046412e:
        je short L_00464133
    L_00464130:
        fdivp st(1),st
    L_00464132:
        ret
    L_00464133:
        shr eax,1Ch
    L_00464136:
        cmp byte ptr [eax+4770A0h],0
    L_0046413d:
        jne short L_00464142
    L_0046413f:
        fdivp st(1),st
    L_00464141:
        ret
    L_00464142:
        mov eax,dword ptr [esp+0Ch]
    L_00464146:
        and eax,7FFFh
    L_0046414b:
        je short L_004641b4
    L_0046414d:
        cmp eax,7FFFh
    L_00464152:
        je short L_004641b4
    L_00464154:
        fnstcw word ptr [esp+1Ch]
    L_00464158:
        mov eax,dword ptr [esp+1Ch]
    L_0046415c:
        or eax,33Fh
    L_00464161:
        and eax,0F3FFh
    L_00464166:
        mov dword ptr [esp+20h],eax
    L_0046416a:
        fldcw word ptr [esp+20h]
    L_0046416e:
        mov eax,dword ptr [esp+18h]
    L_00464172:
        and eax,7FFFh
    L_00464177:
        cmp eax,1
    L_0046417a:
        je short L_00464193
    L_0046417c:
        fmul dword ptr [data_004770b0]
    L_00464182:
        fxch
    L_00464184:
        fmul dword ptr [data_004770b0]
    L_0046418a:
        fxch
    L_0046418c:
        fldcw word ptr [esp+1Ch]
    L_00464190:
        fdivp st(1),st
    L_00464192:
        ret
    L_00464193:
        fmul dword ptr [data_004770b4]
    L_00464199:
        fxch
    L_0046419b:
        fmul dword ptr [data_004770b4]
    L_004641a1:
        fxch
    L_004641a3:
        fldcw word ptr [esp+1Ch]
    L_004641a7:
        fdivp st(1),st
    L_004641a9:
        ret
    L_004641aa:
        mov eax,dword ptr [esp+4]
    L_004641ae:
        or eax,dword ptr [esp+8]
    L_004641b2:
        jne short L_004641b7
    L_004641b4:
        fdivp st(1),st
    L_004641b6:
        ret
    L_004641b7:
        mov eax,dword ptr [esp+0Ch]
    L_004641bb:
        and eax,7FFFh
    L_004641c0:
        jne short L_004641b4
    L_004641c2:
        fnstcw word ptr [esp+1Ch]
    L_004641c6:
        mov eax,dword ptr [esp+1Ch]
    L_004641ca:
        or eax,33Fh
    L_004641cf:
        and eax,0F3FFh
    L_004641d4:
        mov dword ptr [esp+20h],eax
    L_004641d8:
        fldcw word ptr [esp+20h]
    L_004641dc:
        mov eax,dword ptr [esp+18h]
    L_004641e0:
        and eax,7FFFh
    L_004641e5:
        je short L_004641f8
    L_004641e7:
        cmp eax,7FFFh
    L_004641ec:
        je short L_00464220
    L_004641ee:
        mov eax,dword ptr [esp+14h]
    L_004641f2:
        add eax,eax
    L_004641f4:
        jae short L_00464220
    L_004641f6:
        jmp short L_00464200
    L_004641f8:
        mov eax,dword ptr [esp+14h]
    L_004641fc:
        add eax,eax
    L_004641fe:
        jb short L_00464220
    L_00464200:
        fxch
    L_00464202:
        fstp st(0)
    L_00464204:
        fld st(0)
    L_00464206:
        fmul dword ptr [data_004770b8]
    L_0046420c:
        fstp tbyte ptr [esp+4]
    L_00464210:
        fld tbyte ptr [esp+10h]
    L_00464214:
        fxch
    L_00464216:
        wait
    L_00464217:
        fldcw word ptr [esp+1Ch]
    L_0046421b:
        jmp asm_target_00464118
    L_00464220:
        fldcw word ptr [esp+1Ch]
    L_00464224:
        fdivp st(1),st
    L_00464226:
        ret
    L_00464227:
        sub esp,2Ch
    L_0046422a:
        and eax,3Fh
    L_0046422d:
        jmp dword ptr [eax*4+4770FEh]
    L_00464234:
        TH10_FDIV_ST_ST0()
    L_00464236:
        add esp,2Ch
    L_00464239:
        ret
    L_0046423a:
        add esp,2Ch
    L_0046423d:
        int 6
    L_0046423f:
        TH10_FDIVR_ST_ST0()
    L_00464241:
        add esp,2Ch
    L_00464244:
        ret
    L_00464245:
        add esp,2Ch
    L_00464248:
        int 6
    L_0046424a:
        TH10_FDIV_ST_ST0()
    L_0046424c:
        add esp,2Ch
    L_0046424f:
        ret
    L_00464250:
        fdivp st(0),st
    L_00464252:
        add esp,2Ch
    L_00464255:
        ret
    L_00464256:
        TH10_FDIVR_ST_ST0()
    L_00464258:
        add esp,2Ch
    L_0046425b:
        ret
    L_0046425c:
        fdivrp st(0),st
    L_0046425e:
        add esp,2Ch
    L_00464261:
        ret
    L_00464262:
        fstp tbyte ptr [esp+0Ch]
    L_00464266:
        fld st(0)
    L_00464268:
        fstp tbyte ptr [esp]
    L_0046426b:
        fstp tbyte ptr [esp+20h]
    L_0046426f:
        call asm_unassigned_00464110
    L_00464274:
        fld tbyte ptr [esp+20h]
    L_00464278:
        fxch
    L_0046427a:
        add esp,2Ch
    L_0046427d:
        ret
    L_0046427e:
        add esp,2Ch
    L_00464281:
        int 6
    L_00464283:
        fstp tbyte ptr [esp]
    L_00464286:
        fstp tbyte ptr [esp+0Ch]
    L_0046428a:
        call asm_unassigned_00464110
    L_0046428f:
        fld tbyte ptr [esp+0Ch]
    L_00464293:
        fxch
    L_00464295:
        add esp,2Ch
    L_00464298:
        ret
    L_00464299:
        add esp,2Ch
    L_0046429c:
        int 6
    L_0046429e:
        fxch
    L_004642a0:
        fstp tbyte ptr [esp+0Ch]
    L_004642a4:
        fld st(0)
    L_004642a6:
        fstp tbyte ptr [esp]
    L_004642a9:
        fstp tbyte ptr [esp+20h]
    L_004642ad:
        call asm_unassigned_00464110
    L_004642b2:
        fld tbyte ptr [esp+20h]
    L_004642b6:
        add esp,2Ch
    L_004642b9:
        ret
    L_004642ba:
        fstp tbyte ptr [esp]
    L_004642bd:
        fstp tbyte ptr [esp+0Ch]
    L_004642c1:
        call asm_unassigned_00464110
    L_004642c6:
        add esp,2Ch
    L_004642c9:
        ret
    L_004642ca:
        fstp tbyte ptr [esp+0Ch]
    L_004642ce:
        fstp tbyte ptr [esp]
    L_004642d1:
        call asm_unassigned_00464110
    L_004642d6:
        fld tbyte ptr [esp+0Ch]
    L_004642da:
        add esp,2Ch
    L_004642dd:
        ret
    L_004642de:
        fstp tbyte ptr [esp+0Ch]
    L_004642e2:
        fstp tbyte ptr [esp]
    L_004642e5:
        call asm_unassigned_00464110
    L_004642ea:
        add esp,2Ch
    L_004642ed:
        ret
    L_004642ee:
        fstp tbyte ptr [esp+0Ch]
    L_004642f2:
        fxch
    L_004642f4:
        fld st(0)
    L_004642f6:
        fstp tbyte ptr [esp]
    L_004642f9:
        fstp tbyte ptr [esp+20h]
    L_004642fd:
        call asm_unassigned_00464110
    L_00464302:
        fxch
    L_00464304:
        fld tbyte ptr [esp+20h]
    L_00464308:
        fxch st(2)
    L_0046430a:
        add esp,2Ch
    L_0046430d:
        ret
    L_0046430e:
        add esp,2Ch
    L_00464311:
        int 6
    L_00464313:
        fstp tbyte ptr [esp]
    L_00464316:
        fxch
    L_00464318:
        fstp tbyte ptr [esp+0Ch]
    L_0046431c:
        call asm_unassigned_00464110
    L_00464321:
        fxch
    L_00464323:
        fld tbyte ptr [esp+0Ch]
    L_00464327:
        fxch st(2)
    L_00464329:
        add esp,2Ch
    L_0046432c:
        ret
    L_0046432d:
        add esp,2Ch
    L_00464330:
        int 6
    L_00464332:
        fxch st(2)
    L_00464334:
        fstp tbyte ptr [esp+0Ch]
    L_00464338:
        fxch
    L_0046433a:
        fld st(0)
    L_0046433c:
        fstp tbyte ptr [esp]
    L_0046433f:
        fstp tbyte ptr [esp+20h]
    L_00464343:
        call asm_unassigned_00464110
    L_00464348:
        fxch
    L_0046434a:
        fld tbyte ptr [esp+20h]
    L_0046434e:
        add esp,2Ch
    L_00464351:
        ret
    L_00464352:
        fstp tbyte ptr [esp]
    L_00464355:
        fxch
    L_00464357:
        fstp tbyte ptr [esp+0Ch]
    L_0046435b:
        call asm_unassigned_00464110
    L_00464360:
        fxch
    L_00464362:
        add esp,2Ch
    L_00464365:
        ret
    L_00464366:
        fstp tbyte ptr [esp+0Ch]
    L_0046436a:
        fxch
    L_0046436c:
        fstp tbyte ptr [esp]
    L_0046436f:
        call asm_unassigned_00464110
    L_00464374:
        fxch
    L_00464376:
        fld tbyte ptr [esp+0Ch]
    L_0046437a:
        add esp,2Ch
    L_0046437d:
        ret
    L_0046437e:
        fstp tbyte ptr [esp+0Ch]
    L_00464382:
        fxch
    L_00464384:
        fstp tbyte ptr [esp]
    L_00464387:
        call asm_unassigned_00464110
    L_0046438c:
        fxch
    L_0046438e:
        add esp,2Ch
    L_00464391:
        ret
    L_00464392:
        fstp tbyte ptr [esp+0Ch]
    L_00464396:
        fxch st(2)
    L_00464398:
        fld st(0)
    L_0046439a:
        fstp tbyte ptr [esp]
    L_0046439d:
        fstp tbyte ptr [esp+20h]
    L_004643a1:
        call asm_unassigned_00464110
    L_004643a6:
        fxch st(2)
    L_004643a8:
        fld tbyte ptr [esp+20h]
    L_004643ac:
        fxch st(3)
    L_004643ae:
        add esp,2Ch
    L_004643b1:
        ret
    L_004643b2:
        add esp,2Ch
    L_004643b5:
        int 6
    L_004643b7:
        fstp tbyte ptr [esp]
    L_004643ba:
        fxch st(2)
    L_004643bc:
        fstp tbyte ptr [esp+0Ch]
    L_004643c0:
        call asm_unassigned_00464110
    L_004643c5:
        fxch st(2)
    L_004643c7:
        fld tbyte ptr [esp+0Ch]
    L_004643cb:
        fxch st(3)
    L_004643cd:
        add esp,2Ch
    L_004643d0:
        ret
    L_004643d1:
        add esp,2Ch
    L_004643d4:
        int 6
    L_004643d6:
        fxch st(3)
    L_004643d8:
        fstp tbyte ptr [esp+0Ch]
    L_004643dc:
        fxch st(2)
    L_004643de:
        fld st(0)
    L_004643e0:
        fstp tbyte ptr [esp]
    L_004643e3:
        fstp tbyte ptr [esp+20h]
    L_004643e7:
        call asm_unassigned_00464110
    L_004643ec:
        fxch st(2)
    L_004643ee:
        fld tbyte ptr [esp+20h]
    L_004643f2:
        add esp,2Ch
    L_004643f5:
        ret
    L_004643f6:
        fstp tbyte ptr [esp]
    L_004643f9:
        fxch st(2)
    L_004643fb:
        fstp tbyte ptr [esp+0Ch]
    L_004643ff:
        call asm_unassigned_00464110
    L_00464404:
        fxch st(2)
    L_00464406:
        add esp,2Ch
    L_00464409:
        ret
    L_0046440a:
        fstp tbyte ptr [esp+0Ch]
    L_0046440e:
        fxch st(2)
    L_00464410:
        fstp tbyte ptr [esp]
    L_00464413:
        call asm_unassigned_00464110
    L_00464418:
        fxch st(2)
    L_0046441a:
        fld tbyte ptr [esp+0Ch]
    L_0046441e:
        add esp,2Ch
    L_00464421:
        ret
    L_00464422:
        fstp tbyte ptr [esp+0Ch]
    L_00464426:
        fxch st(2)
    L_00464428:
        fstp tbyte ptr [esp]
    L_0046442b:
        call asm_unassigned_00464110
    L_00464430:
        fxch st(2)
    L_00464432:
        add esp,2Ch
    L_00464435:
        ret
    L_00464436:
        fstp tbyte ptr [esp+0Ch]
    L_0046443a:
        fxch st(3)
    L_0046443c:
        fld st(0)
    L_0046443e:
        fstp tbyte ptr [esp]
    L_00464441:
        fstp tbyte ptr [esp+20h]
    L_00464445:
        call asm_unassigned_00464110
    L_0046444a:
        fxch st(3)
    L_0046444c:
        fld tbyte ptr [esp+20h]
    L_00464450:
        fxch st(4)
    L_00464452:
        add esp,2Ch
    L_00464455:
        ret
    L_00464456:
        add esp,2Ch
    L_00464459:
        int 6
    L_0046445b:
        fstp tbyte ptr [esp]
    L_0046445e:
        fxch st(3)
    L_00464460:
        fstp tbyte ptr [esp+0Ch]
    L_00464464:
        call asm_unassigned_00464110
    L_00464469:
        fxch st(3)
    L_0046446b:
        fld tbyte ptr [esp+0Ch]
    L_0046446f:
        fxch st(4)
    L_00464471:
        add esp,2Ch
    L_00464474:
        ret
    L_00464475:
        add esp,2Ch
    L_00464478:
        int 6
    L_0046447a:
        fxch st(4)
    L_0046447c:
        fstp tbyte ptr [esp+0Ch]
    L_00464480:
        fxch st(3)
    L_00464482:
        fld st(0)
    L_00464484:
        fstp tbyte ptr [esp]
    L_00464487:
        fstp tbyte ptr [esp+20h]
    L_0046448b:
        call asm_unassigned_00464110
    L_00464490:
        fxch st(3)
    L_00464492:
        fld tbyte ptr [esp+20h]
    L_00464496:
        add esp,2Ch
    L_00464499:
        ret
    L_0046449a:
        fstp tbyte ptr [esp]
    L_0046449d:
        fxch st(3)
    L_0046449f:
        fstp tbyte ptr [esp+0Ch]
    L_004644a3:
        call asm_unassigned_00464110
    L_004644a8:
        fxch st(3)
    L_004644aa:
        add esp,2Ch
    L_004644ad:
        ret
    L_004644ae:
        fstp tbyte ptr [esp+0Ch]
    L_004644b2:
        fxch st(3)
    L_004644b4:
        fstp tbyte ptr [esp]
    L_004644b7:
        call asm_unassigned_00464110
    L_004644bc:
        fxch st(3)
    L_004644be:
        fld tbyte ptr [esp+0Ch]
    L_004644c2:
        add esp,2Ch
    L_004644c5:
        ret
    L_004644c6:
        fstp tbyte ptr [esp+0Ch]
    L_004644ca:
        fxch st(3)
    L_004644cc:
        fstp tbyte ptr [esp]
    L_004644cf:
        call asm_unassigned_00464110
    L_004644d4:
        fxch st(3)
    L_004644d6:
        add esp,2Ch
    L_004644d9:
        ret
    L_004644da:
        fstp tbyte ptr [esp+0Ch]
    L_004644de:
        fxch st(4)
    L_004644e0:
        fld st(0)
    L_004644e2:
        fstp tbyte ptr [esp]
    L_004644e5:
        fstp tbyte ptr [esp+20h]
    L_004644e9:
        call asm_unassigned_00464110
    L_004644ee:
        fxch st(4)
    L_004644f0:
        fld tbyte ptr [esp+20h]
    L_004644f4:
        fxch st(5)
    L_004644f6:
        add esp,2Ch
    L_004644f9:
        ret
    L_004644fa:
        add esp,2Ch
    L_004644fd:
        int 6
    L_004644ff:
        fstp tbyte ptr [esp]
    L_00464502:
        fxch st(4)
    L_00464504:
        fstp tbyte ptr [esp+0Ch]
    L_00464508:
        call asm_unassigned_00464110
    L_0046450d:
        fxch st(4)
    L_0046450f:
        fld tbyte ptr [esp+0Ch]
    L_00464513:
        fxch st(5)
    L_00464515:
        add esp,2Ch
    L_00464518:
        ret
    L_00464519:
        add esp,2Ch
    L_0046451c:
        int 6
    L_0046451e:
        fxch st(5)
    L_00464520:
        fstp tbyte ptr [esp+0Ch]
    L_00464524:
        fxch st(4)
    L_00464526:
        fld st(0)
    L_00464528:
        fstp tbyte ptr [esp]
    L_0046452b:
        fstp tbyte ptr [esp+20h]
    L_0046452f:
        call asm_unassigned_00464110
    L_00464534:
        fxch st(4)
    L_00464536:
        fld tbyte ptr [esp+20h]
    L_0046453a:
        add esp,2Ch
    L_0046453d:
        ret
    L_0046453e:
        fstp tbyte ptr [esp]
    L_00464541:
        fxch st(4)
    L_00464543:
        fstp tbyte ptr [esp+0Ch]
    L_00464547:
        call asm_unassigned_00464110
    L_0046454c:
        fxch st(4)
    L_0046454e:
        add esp,2Ch
    L_00464551:
        ret
    L_00464552:
        fstp tbyte ptr [esp+0Ch]
    L_00464556:
        fxch st(4)
    L_00464558:
        fstp tbyte ptr [esp]
    L_0046455b:
        call asm_unassigned_00464110
    L_00464560:
        fxch st(4)
    L_00464562:
        fld tbyte ptr [esp+0Ch]
    L_00464566:
        add esp,2Ch
    L_00464569:
        ret
    L_0046456a:
        fstp tbyte ptr [esp+0Ch]
    L_0046456e:
        fxch st(4)
    L_00464570:
        fstp tbyte ptr [esp]
    L_00464573:
        call asm_unassigned_00464110
    L_00464578:
        fxch st(4)
    L_0046457a:
        add esp,2Ch
    L_0046457d:
        ret
    L_0046457e:
        fstp tbyte ptr [esp+0Ch]
    L_00464582:
        fxch st(5)
    L_00464584:
        fld st(0)
    L_00464586:
        fstp tbyte ptr [esp]
    L_00464589:
        fstp tbyte ptr [esp+20h]
    L_0046458d:
        call asm_unassigned_00464110
    L_00464592:
        fxch st(5)
    L_00464594:
        fld tbyte ptr [esp+20h]
    L_00464598:
        fxch st(6)
    L_0046459a:
        add esp,2Ch
    L_0046459d:
        ret
    L_0046459e:
        add esp,2Ch
    L_004645a1:
        int 6
    L_004645a3:
        fstp tbyte ptr [esp]
    L_004645a6:
        fxch st(5)
    L_004645a8:
        fstp tbyte ptr [esp+0Ch]
    L_004645ac:
        call asm_unassigned_00464110
    L_004645b1:
        fxch st(5)
    L_004645b3:
        fld tbyte ptr [esp+0Ch]
    L_004645b7:
        fxch st(6)
    L_004645b9:
        add esp,2Ch
    L_004645bc:
        ret
    L_004645bd:
        add esp,2Ch
    L_004645c0:
        int 6
    L_004645c2:
        fxch st(6)
    L_004645c4:
        fstp tbyte ptr [esp+0Ch]
    L_004645c8:
        fxch st(5)
    L_004645ca:
        fld st(0)
    L_004645cc:
        fstp tbyte ptr [esp]
    L_004645cf:
        fstp tbyte ptr [esp+20h]
    L_004645d3:
        call asm_unassigned_00464110
    L_004645d8:
        fxch st(5)
    L_004645da:
        fld tbyte ptr [esp+20h]
    L_004645de:
        add esp,2Ch
    L_004645e1:
        ret
    L_004645e2:
        fstp tbyte ptr [esp]
    L_004645e5:
        fxch st(5)
    L_004645e7:
        fstp tbyte ptr [esp+0Ch]
    L_004645eb:
        call asm_unassigned_00464110
    L_004645f0:
        fxch st(5)
    L_004645f2:
        add esp,2Ch
    L_004645f5:
        ret
    L_004645f6:
        fstp tbyte ptr [esp+0Ch]
    L_004645fa:
        fxch st(5)
    L_004645fc:
        fstp tbyte ptr [esp]
    L_004645ff:
        call asm_unassigned_00464110
    L_00464604:
        fxch st(5)
    L_00464606:
        fld tbyte ptr [esp+0Ch]
    L_0046460a:
        add esp,2Ch
    L_0046460d:
        ret
    L_0046460e:
        fstp tbyte ptr [esp+0Ch]
    L_00464612:
        fxch st(5)
    L_00464614:
        fstp tbyte ptr [esp]
    L_00464617:
        call asm_unassigned_00464110
    L_0046461c:
        fxch st(5)
    L_0046461e:
        add esp,2Ch
    L_00464621:
        ret
    L_00464622:
        fstp tbyte ptr [esp+0Ch]
    L_00464626:
        fxch st(6)
    L_00464628:
        fld st(0)
    L_0046462a:
        fstp tbyte ptr [esp]
    L_0046462d:
        fstp tbyte ptr [esp+20h]
    L_00464631:
        call asm_unassigned_00464110
    L_00464636:
        fxch st(6)
    L_00464638:
        fld tbyte ptr [esp+20h]
    L_0046463c:
        fxch st(7)
    L_0046463e:
        add esp,2Ch
    L_00464641:
        ret
    L_00464642:
        add esp,2Ch
    L_00464645:
        int 6
    L_00464647:
        fstp tbyte ptr [esp]
    L_0046464a:
        fxch st(6)
    L_0046464c:
        fstp tbyte ptr [esp+0Ch]
    L_00464650:
        call asm_unassigned_00464110
    L_00464655:
        fxch st(6)
    L_00464657:
        fld tbyte ptr [esp+0Ch]
    L_0046465b:
        fxch st(7)
    L_0046465d:
        add esp,2Ch
    L_00464660:
        ret
    L_00464661:
        add esp,2Ch
    L_00464664:
        int 6
    L_00464666:
        fxch st(7)
    L_00464668:
        fstp tbyte ptr [esp+0Ch]
    L_0046466c:
        fxch st(6)
    L_0046466e:
        fld st(0)
    L_00464670:
        fstp tbyte ptr [esp]
    L_00464673:
        fstp tbyte ptr [esp+20h]
    L_00464677:
        call asm_unassigned_00464110
    L_0046467c:
        fxch st(6)
    L_0046467e:
        fld tbyte ptr [esp+20h]
    L_00464682:
        add esp,2Ch
    L_00464685:
        ret
    L_00464686:
        fstp tbyte ptr [esp]
    L_00464689:
        fxch st(6)
    L_0046468b:
        fstp tbyte ptr [esp+0Ch]
    L_0046468f:
        call asm_unassigned_00464110
    L_00464694:
        fxch st(6)
    L_00464696:
        add esp,2Ch
    L_00464699:
        ret
    L_0046469a:
        fstp tbyte ptr [esp+0Ch]
    L_0046469e:
        fxch st(6)
    L_004646a0:
        fstp tbyte ptr [esp]
    L_004646a3:
        call asm_unassigned_00464110
    L_004646a8:
        fxch st(6)
    L_004646aa:
        fld tbyte ptr [esp+0Ch]
    L_004646ae:
        add esp,2Ch
    L_004646b1:
        ret
    L_004646b2:
        fstp tbyte ptr [esp+0Ch]
    L_004646b6:
        fxch st(6)
    L_004646b8:
        fstp tbyte ptr [esp]
    L_004646bb:
        call asm_unassigned_00464110
    L_004646c0:
        fxch st(6)
    L_004646c2:
        add esp,2Ch
    L_004646c5:
        ret
    L_004646c6:
        sub esp,2Ch
    L_004646c9:
        fstp tbyte ptr [esp]
    L_004646cc:
        fstp tbyte ptr [esp+0Ch]
    L_004646d0:
        call asm_unassigned_00464110
    L_004646d5:
        add esp,2Ch
    L_004646d8:
        ret
    L_004646d9:
        sub esp,2Ch
    L_004646dc:
        fstp tbyte ptr [esp+0Ch]
    L_004646e0:
        fstp tbyte ptr [esp]
    L_004646e3:
        call asm_unassigned_00464110
    L_004646e8:
        add esp,2Ch
    L_004646eb:
        ret
    L_004646ec:
        push eax
    L_004646ed:
        mov eax,dword ptr [esp+8]
    L_004646f1:
        and eax,7F800000h
    L_004646f6:
        cmp eax,7F800000h
    L_004646fb:
        je short L_00464730
    L_004646fd:
        fnstsw ax
    L_004646ff:
        and eax,3800h
    L_00464704:
        je short L_00464713
    L_00464706:
        fld dword ptr [esp+8]
    L_0046470a:
        call asm_target_004646c6
    L_0046470f:
        pop eax
    L_00464710:
        ret 4
    L_00464713:
        fxch
    L_00464715:
        sub esp,0Ch
    L_00464718:
        fstp tbyte ptr [esp]
    L_0046471b:
        fld dword ptr [esp+14h]
    L_0046471f:
        call asm_target_004646c6
    L_00464724:
        fld tbyte ptr [esp]
    L_00464727:
        fxch
    L_00464729:
        add esp,0Ch
    L_0046472c:
        pop eax
    L_0046472d:
        ret 4
    L_00464730:
        fdiv dword ptr [esp+8]
    L_00464734:
        pop eax
    L_00464735:
        ret 4
    L_00464738:
        push eax
    L_00464739:
        mov eax,dword ptr [esp+0Ch]
    L_0046473d:
        and eax,7FF00000h
    L_00464742:
        cmp eax,7FF00000h
    L_00464747:
        je short L_0046477c
    L_00464749:
        fnstsw ax
    L_0046474b:
        and eax,3800h
    L_00464750:
        je short L_0046475f
    L_00464752:
        fld qword ptr [esp+8]
    L_00464756:
        call asm_target_004646c6
    L_0046475b:
        pop eax
    L_0046475c:
        ret 8
    L_0046475f:
        fxch
    L_00464761:
        sub esp,0Ch
    L_00464764:
        fstp tbyte ptr [esp]
    L_00464767:
        fld qword ptr [esp+14h]
    L_0046476b:
        call asm_target_004646c6
    L_00464770:
        fld tbyte ptr [esp]
    L_00464773:
        fxch
    L_00464775:
        add esp,0Ch
    L_00464778:
        pop eax
    L_00464779:
        ret 8
    L_0046477c:
        fdiv qword ptr [esp+8]
    L_00464780:
        pop eax
    L_00464781:
        ret 8
    L_00464784:
        push eax
    L_00464785:
        fnstsw ax
    L_00464787:
        and eax,3800h
    L_0046478c:
        je short L_0046479b
    L_0046478e:
        fild word ptr [esp+8]
    L_00464792:
        call asm_target_004646c6
    L_00464797:
        pop eax
    L_00464798:
        ret 4
    L_0046479b:
        fxch
    L_0046479d:
        sub esp,0Ch
    L_004647a0:
        fstp tbyte ptr [esp]
    L_004647a3:
        fild word ptr [esp+14h]
    L_004647a7:
        call asm_target_004646c6
    L_004647ac:
        fld tbyte ptr [esp]
    L_004647af:
        fxch
    L_004647b1:
        add esp,0Ch
    L_004647b4:
        pop eax
    L_004647b5:
        ret 4
    L_004647b8:
        push eax
    L_004647b9:
        fnstsw ax
    L_004647bb:
        and eax,3800h
    L_004647c0:
        je short L_004647cf
    L_004647c2:
        fild dword ptr [esp+8]
    L_004647c6:
        call asm_target_004646c6
    L_004647cb:
        pop eax
    L_004647cc:
        ret 4
    L_004647cf:
        fxch
    L_004647d1:
        sub esp,0Ch
    L_004647d4:
        fstp tbyte ptr [esp]
    L_004647d7:
        fild dword ptr [esp+14h]
    L_004647db:
        call asm_target_004646c6
    L_004647e0:
        fld tbyte ptr [esp]
    L_004647e3:
        fxch
    L_004647e5:
        add esp,0Ch
    L_004647e8:
        pop eax
    L_004647e9:
        ret 4
    L_004647ec:
        push eax
    L_004647ed:
        mov eax,dword ptr [esp+8]
    L_004647f1:
        and eax,7F800000h
    L_004647f6:
        cmp eax,7F800000h
    L_004647fb:
        je short L_00464830
    L_004647fd:
        fnstsw ax
    L_004647ff:
        and eax,3800h
    L_00464804:
        je short L_00464813
    L_00464806:
        fld dword ptr [esp+8]
    L_0046480a:
        call asm_target_004646d9
    L_0046480f:
        pop eax
    L_00464810:
        ret 4
    L_00464813:
        fxch
    L_00464815:
        sub esp,0Ch
    L_00464818:
        fstp tbyte ptr [esp]
    L_0046481b:
        fld dword ptr [esp+14h]
    L_0046481f:
        call asm_target_004646d9
    L_00464824:
        fld tbyte ptr [esp]
    L_00464827:
        fxch
    L_00464829:
        add esp,0Ch
    L_0046482c:
        pop eax
    L_0046482d:
        ret 4
    L_00464830:
        fdivr dword ptr [esp+8]
    L_00464834:
        pop eax
    L_00464835:
        ret 4
    L_00464838:
        push eax
    L_00464839:
        mov eax,dword ptr [esp+0Ch]
    L_0046483d:
        and eax,7FF00000h
    L_00464842:
        cmp eax,7FF00000h
    L_00464847:
        je short L_0046487c
    L_00464849:
        fnstsw ax
    L_0046484b:
        and eax,3800h
    L_00464850:
        je short L_0046485f
    L_00464852:
        fld qword ptr [esp+8]
    L_00464856:
        call asm_target_004646d9
    L_0046485b:
        pop eax
    L_0046485c:
        ret 8
    L_0046485f:
        fxch
    L_00464861:
        sub esp,0Ch
    L_00464864:
        fstp tbyte ptr [esp]
    L_00464867:
        fld qword ptr [esp+14h]
    L_0046486b:
        call asm_target_004646d9
    L_00464870:
        fld tbyte ptr [esp]
    L_00464873:
        fxch
    L_00464875:
        add esp,0Ch
    L_00464878:
        pop eax
    L_00464879:
        ret 8
    L_0046487c:
        fdivr qword ptr [esp+8]
    L_00464880:
        pop eax
    L_00464881:
        ret 8
    L_00464884:
        push eax
    L_00464885:
        fnstsw ax
    L_00464887:
        and eax,3800h
    L_0046488c:
        je short L_0046489b
    L_0046488e:
        fild word ptr [esp+8]
    L_00464892:
        call asm_target_004646d9
    L_00464897:
        pop eax
    L_00464898:
        ret 4
    L_0046489b:
        fxch
    L_0046489d:
        sub esp,0Ch
    L_004648a0:
        fstp tbyte ptr [esp]
    L_004648a3:
        fild word ptr [esp+14h]
    L_004648a7:
        call asm_target_004646d9
    L_004648ac:
        fld tbyte ptr [esp]
    L_004648af:
        fxch
    L_004648b1:
        add esp,0Ch
    L_004648b4:
        pop eax
    L_004648b5:
        ret 4
    L_004648b8:
        push eax
    L_004648b9:
        fnstsw ax
    L_004648bb:
        and eax,3800h
    L_004648c0:
        je short L_004648cf
    L_004648c2:
        fild dword ptr [esp+8]
    L_004648c6:
        call asm_target_004646d9
    L_004648cb:
        pop eax
    L_004648cc:
        ret 4
    L_004648cf:
        fxch
    L_004648d1:
        sub esp,0Ch
    L_004648d4:
        fstp tbyte ptr [esp]
    L_004648d7:
        fild dword ptr [esp+14h]
    L_004648db:
        call asm_target_004646d9
    L_004648e0:
        fld tbyte ptr [esp]
    L_004648e3:
        fxch
    L_004648e5:
        add esp,0Ch
    L_004648e8:
        pop eax
    L_004648e9:
        ret 4
    L_004648ec:
        push eax
    L_004648ed:
        sub esp,2Ch
    L_004648f0:
        fstp tbyte ptr [esp]
    L_004648f3:
        fstp tbyte ptr [esp+0Ch]
    L_004648f7:
        call asm_unassigned_00464110
    L_004648fc:
        add esp,2Ch
    L_004648ff:
        pop eax
    L_00464900:
        ret
    L_00464901:
        push eax
    L_00464902:
        sub esp,2Ch
    L_00464905:
        fstp tbyte ptr [esp+0Ch]
    L_00464909:
        fstp tbyte ptr [esp]
    L_0046490c:
        call asm_unassigned_00464110
    L_00464911:
        add esp,2Ch
    L_00464914:
        pop eax
    L_00464915:
        ret
    }
}

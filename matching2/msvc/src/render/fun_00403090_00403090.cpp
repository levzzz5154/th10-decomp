#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403090..0x0040384F: FUN_00403090
// Naked body preserves the retail register/stack ABI.

// 0x00403090..0x0040384F: FUN_00403090
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403090_00403090() {
    __asm {
    L_00403090:
        sub esp,128h
    L_00403096:
        fld dword ptr [ecx+4]
    L_00403099:
        push esi
    L_0040309a:
        fadd dword ptr [edx]
    L_0040309c:
        mov esi,eax
    L_0040309e:
        fstp dword ptr [esp+10h]
    L_004030a2:
        mov eax,dword ptr [esp+10h]
    L_004030a6:
        fld dword ptr [ecx+8]
    L_004030a9:
        mov dword ptr [esp+8Ch],eax
    L_004030b0:
        fadd dword ptr [edx+4]
    L_004030b3:
        fstp dword ptr [esp+14h]
    L_004030b7:
        mov eax,dword ptr [esp+14h]
    L_004030bb:
        fld dword ptr [ecx+0Ch]
    L_004030be:
        mov dword ptr [esp+90h],eax
    L_004030c5:
        fadd dword ptr [edx+8]
    L_004030c8:
        fstp dword ptr [esp+18h]
    L_004030cc:
        mov eax,dword ptr [esp+18h]
    L_004030d0:
        fld dword ptr [esi+3Ch]
    L_004030d3:
        mov dword ptr [esp+94h],eax
    L_004030da:
        fadd dword ptr [esi]
    L_004030dc:
        fld dword ptr [esi+40h]
    L_004030df:
        fadd dword ptr [esi+4]
    L_004030e2:
        fld dword ptr [esi+44h]
    L_004030e5:
        fadd dword ptr [esi+8]
    L_004030e8:
        fstp dword ptr [esp+84h]
    L_004030ef:
        fld dword ptr [esp+8Ch]
    L_004030f6:
        fsub st,st(2)
    L_004030f8:
        fstp dword ptr [esp+10h]
    L_004030fc:
        mov eax,dword ptr [esp+10h]
    L_00403100:
        fld dword ptr [esp+90h]
    L_00403107:
        mov dword ptr [esp+8Ch],eax
    L_0040310e:
        fsub st,st(1)
    L_00403110:
        fstp dword ptr [esp+14h]
    L_00403114:
        mov eax,dword ptr [esp+14h]
    L_00403118:
        mov dword ptr [esp+90h],eax
    L_0040311f:
        fstp st(0)
    L_00403121:
        fstp st(0)
    L_00403123:
        fld dword ptr [esp+94h]
    L_0040312a:
        fsub dword ptr [esp+84h]
    L_00403131:
        fstp dword ptr [esp+18h]
    L_00403135:
        mov eax,dword ptr [esp+18h]
    L_00403139:
        mov dword ptr [esp+94h],eax
    L_00403140:
        fld dword ptr [esp+94h]
    L_00403147:
        fmul dword ptr [esp+94h]
    L_0040314e:
        fld dword ptr [esp+90h]
    L_00403155:
        fmul dword ptr [esp+90h]
    L_0040315c:
        faddp st(1),st
    L_0040315e:
        fld dword ptr [esp+8Ch]
    L_00403165:
        fmul dword ptr [esp+8Ch]
    L_0040316c:
        faddp st(1),st
    L_0040316e:
        fcomp dword ptr [esp+130h]
    L_00403175:
        fnstsw ax
    L_00403177:
        test ah,41h
    L_0040317a:
        je asm_target_00403841
    L_00403180:
        fld dword ptr [ecx+10h]
    L_00403183:
        mov dword ptr [esp+124h],0
    L_0040318e:
        fmul dword ptr [data_00470b0c]
    L_00403194:
        mov dword ptr [esp+120h],0
    L_0040319f:
        mov dword ptr [esp+11Ch],0
    L_004031aa:
        mov dword ptr [esp+118h],0
    L_004031b5:
        fstp dword ptr [esp+7Ch]
    L_004031b9:
        mov eax,dword ptr [esp+7Ch]
    L_004031bd:
        fld dword ptr [ecx+14h]
    L_004031c0:
        mov dword ptr [esp+10h],eax
    L_004031c4:
        fmul dword ptr [data_00470b0c]
    L_004031ca:
        mov dword ptr [esp+110h],0
    L_004031d5:
        mov dword ptr [esp+10Ch],0
    L_004031e0:
        mov dword ptr [esp+108h],0
    L_004031eb:
        fstp dword ptr [esp+80h]
    L_004031f2:
        mov eax,dword ptr [esp+80h]
    L_004031f9:
        fld dword ptr [ecx+18h]
    L_004031fc:
        mov dword ptr [esp+14h],eax
    L_00403200:
        fmul dword ptr [data_00470b0c]
    L_00403206:
        mov dword ptr [esp+104h],0
    L_00403211:
        mov dword ptr [esp+0FCh],0
    L_0040321c:
        fstp dword ptr [esp+84h]
    L_00403223:
        mov eax,dword ptr [esp+84h]
    L_0040322a:
        fld dword ptr [esp+10h]
    L_0040322e:
        mov dword ptr [esp+18h],eax
    L_00403232:
        fadd dword ptr [ecx+4]
    L_00403235:
        fst dword ptr [esp+8Ch]
    L_0040323c:
        fld dword ptr [esp+14h]
    L_00403240:
        fadd dword ptr [ecx+8]
    L_00403243:
        fst dword ptr [esp+90h]
    L_0040324a:
        fld dword ptr [esp+18h]
    L_0040324e:
        fadd dword ptr [ecx+0Ch]
    L_00403251:
        fst dword ptr [esp+88h]
    L_00403258:
        fst dword ptr [esp+94h]
    L_0040325f:
        fld st(2)
    L_00403261:
        fstp dword ptr [esp+98h]
    L_00403268:
        fld st(1)
    L_0040326a:
        fstp dword ptr [esp+9Ch]
    L_00403271:
        fld dword ptr [ecx+0Ch]
    L_00403274:
        fsub dword ptr [esp+18h]
    L_00403278:
        fst dword ptr [esp+8]
    L_0040327c:
        fst dword ptr [esp+0A0h]
    L_00403283:
        fld st(3)
    L_00403285:
        fstp dword ptr [esp+0A4h]
    L_0040328c:
        fld dword ptr [ecx+8]
    L_0040328f:
        fsub dword ptr [esp+14h]
    L_00403293:
        fst dword ptr [esp+4]
    L_00403297:
        fst dword ptr [esp+0A8h]
    L_0040329e:
        fld st(2)
    L_004032a0:
        fstp dword ptr [esp+0ACh]
    L_004032a7:
        fxch st(4)
    L_004032a9:
        fstp dword ptr [esp+0B0h]
    L_004032b0:
        fxch st(3)
    L_004032b2:
        fstp dword ptr [esp+0B4h]
    L_004032b9:
        fxch st(2)
    L_004032bb:
        fstp dword ptr [esp+0B8h]
    L_004032c2:
        fld dword ptr [ecx+4]
    L_004032c5:
        mov ecx,dword ptr [esp+8]
    L_004032c9:
        fsub dword ptr [esp+10h]
    L_004032cd:
        mov dword ptr [esp+0D0h],ecx
    L_004032d4:
        mov ecx,dword ptr [esp+4]
    L_004032d8:
        mov dword ptr [esp+0D8h],ecx
    L_004032df:
        fst dword ptr [esp+0Ch]
    L_004032e3:
        mov eax,dword ptr [esp+0Ch]
    L_004032e7:
        fst dword ptr [esp+0BCh]
    L_004032ee:
        mov ecx,dword ptr [esp+0Ch]
    L_004032f2:
        fld st(1)
    L_004032f4:
        fstp dword ptr [esp+0C0h]
    L_004032fb:
        mov dword ptr [esp+0D4h],eax
    L_00403302:
        mov eax,dword ptr [esp+88h]
    L_00403309:
        fxch st(2)
    L_0040330b:
        fstp dword ptr [esp+0C4h]
    L_00403312:
        mov dword ptr [esp+0DCh],eax
    L_00403319:
        mov eax,dword ptr [esp+4]
    L_0040331d:
        fxch
    L_0040331f:
        fstp dword ptr [esp+0C8h]
    L_00403326:
        mov dword ptr [esp+0E0h],ecx
    L_0040332d:
        mov ecx,dword ptr [esp+8]
    L_00403331:
        fstp dword ptr [esp+0CCh]
    L_00403338:
        mov dword ptr [esp+0E4h],eax
    L_0040333f:
        mov dword ptr [esp+0E8h],ecx
    L_00403346:
        mov eax,dword ptr [edx+8]
    L_00403349:
        mov ecx,dword ptr [edx+4]
    L_0040334c:
        mov edx,dword ptr [edx]
    L_0040334e:
        push eax
    L_0040334f:
        push ecx
    L_00403350:
        push edx
    L_00403351:
        lea eax,[esp+0F8h]
    L_00403358:
        push eax
    L_00403359:
        mov dword ptr [esp+108h],0
    L_00403364:
        mov dword ptr [esp+104h],0
    L_0040336f:
        mov dword ptr [esp+100h],0
    L_0040337a:
        mov dword ptr [esp+138h],3F800000h
    L_00403385:
        mov dword ptr [esp+124h],3F800000h
    L_00403390:
        mov dword ptr [esp+110h],3F800000h
    L_0040339b:
        mov dword ptr [esp+0FCh],3F800000h
    L_004033a6:
        call asm_D3DXMatrixTranslation_00452182
    L_004033ab:
        push 8
    L_004033ad:
        lea ecx,[esp+0F0h]
    L_004033b4:
        push ecx
    L_004033b5:
        lea edx,[esi+4Ch]
    L_004033b8:
        push edx
    L_004033b9:
        lea eax,[esi+8Ch]
    L_004033bf:
        push eax
    L_004033c0:
        add esi,0CCh
    L_004033c6:
        push esi
    L_004033c7:
        push 0Ch
    L_004033c9:
        lea ecx,[esp+0A4h]
    L_004033d0:
        push ecx
    L_004033d1:
        push 0Ch
    L_004033d3:
        lea edx,[esp+3Ch]
    L_004033d7:
        push edx
    L_004033d8:
        call asm_D3DXVec3ProjectArray_00452188
    L_004033dd:
        fld dword ptr [data_00470be8]
    L_004033e3:
        fld dword ptr [esp+24h]
    L_004033e7:
        mov dword ptr [esp+8],43D40000h
    L_004033ef:
        fcomp dword ptr [data_00470b04]
    L_004033f5:
        mov dword ptr [esp+0Ch],43EC0000h
    L_004033fd:
        mov dword ptr [esp+4],41000000h
    L_00403405:
        fnstsw ax
    L_00403407:
        test ah,1
    L_0040340a:
        jne short L_00403483
    L_0040340c:
        fld dword ptr [esp+24h]
    L_00403410:
        fcomp dword ptr [data_00470afc]
    L_00403416:
        fnstsw ax
    L_00403418:
        test ah,41h
    L_0040341b:
        jp short L_00403483
    L_0040341d:
        fld dword ptr [esp+1Ch]
    L_00403421:
        fcomp dword ptr [data_00470be4]
    L_00403427:
        fnstsw ax
    L_00403429:
        test ah,5
    L_0040342c:
        jp short L_00403438
    L_0040342e:
        mov eax,dword ptr [esp+1Ch]
    L_00403432:
        mov dword ptr [esp+8],eax
    L_00403436:
        jmp short L_0040344f
    L_00403438:
        fld dword ptr [esp+1Ch]
    L_0040343c:
        fcomp dword ptr [data_00470be8]
    L_00403442:
        fnstsw ax
    L_00403444:
        test ah,41h
    L_00403447:
        jne short L_0040344f
    L_00403449:
        fstp st(0)
    L_0040344b:
        fld dword ptr [esp+1Ch]
    L_0040344f:
        fld dword ptr [esp+20h]
    L_00403453:
        fcomp dword ptr [data_00470be0]
    L_00403459:
        fnstsw ax
    L_0040345b:
        test ah,5
    L_0040345e:
        jp short L_0040346a
    L_00403460:
        mov ecx,dword ptr [esp+20h]
    L_00403464:
        mov dword ptr [esp+0Ch],ecx
    L_00403468:
        jmp short L_00403483
    L_0040346a:
        fld dword ptr [esp+20h]
    L_0040346e:
        fcomp dword ptr [data_00470bd0]
    L_00403474:
        fnstsw ax
    L_00403476:
        test ah,41h
    L_00403479:
        jne short L_00403483
    L_0040347b:
        mov edx,dword ptr [esp+20h]
    L_0040347f:
        mov dword ptr [esp+4],edx
    L_00403483:
        fld dword ptr [esp+30h]
    L_00403487:
        fcomp dword ptr [data_00470b04]
    L_0040348d:
        fnstsw ax
    L_0040348f:
        test ah,1
    L_00403492:
        jne short L_00403501
    L_00403494:
        fld dword ptr [esp+30h]
    L_00403498:
        fcomp dword ptr [data_00470afc]
    L_0040349e:
        fnstsw ax
    L_004034a0:
        test ah,41h
    L_004034a3:
        jp short L_00403501
    L_004034a5:
        fld dword ptr [esp+28h]
    L_004034a9:
        fcomp dword ptr [esp+8]
    L_004034ad:
        fnstsw ax
    L_004034af:
        test ah,5
    L_004034b2:
        jp short L_004034be
    L_004034b4:
        mov eax,dword ptr [esp+28h]
    L_004034b8:
        mov dword ptr [esp+8],eax
    L_004034bc:
        jmp short L_004034d1
    L_004034be:
        fld dword ptr [esp+28h]
    L_004034c2:
        fcomp
    L_004034c4:
        fnstsw ax
    L_004034c6:
        test ah,41h
    L_004034c9:
        jne short L_004034d1
    L_004034cb:
        fstp st(0)
    L_004034cd:
        fld dword ptr [esp+28h]
    L_004034d1:
        fld dword ptr [esp+2Ch]
    L_004034d5:
        fcomp dword ptr [esp+0Ch]
    L_004034d9:
        fnstsw ax
    L_004034db:
        test ah,5
    L_004034de:
        jp short L_004034ea
    L_004034e0:
        mov ecx,dword ptr [esp+2Ch]
    L_004034e4:
        mov dword ptr [esp+0Ch],ecx
    L_004034e8:
        jmp short L_00403501
    L_004034ea:
        fld dword ptr [esp+2Ch]
    L_004034ee:
        fcomp dword ptr [esp+4]
    L_004034f2:
        fnstsw ax
    L_004034f4:
        test ah,41h
    L_004034f7:
        jne short L_00403501
    L_004034f9:
        mov edx,dword ptr [esp+2Ch]
    L_004034fd:
        mov dword ptr [esp+4],edx
    L_00403501:
        fld dword ptr [esp+3Ch]
    L_00403505:
        fcomp dword ptr [data_00470b04]
    L_0040350b:
        fnstsw ax
    L_0040350d:
        test ah,1
    L_00403510:
        jne short L_0040357f
    L_00403512:
        fld dword ptr [esp+3Ch]
    L_00403516:
        fcomp dword ptr [data_00470afc]
    L_0040351c:
        fnstsw ax
    L_0040351e:
        test ah,41h
    L_00403521:
        jp short L_0040357f
    L_00403523:
        fld dword ptr [esp+34h]
    L_00403527:
        fcomp dword ptr [esp+8]
    L_0040352b:
        fnstsw ax
    L_0040352d:
        test ah,5
    L_00403530:
        jp short L_0040353c
    L_00403532:
        mov eax,dword ptr [esp+34h]
    L_00403536:
        mov dword ptr [esp+8],eax
    L_0040353a:
        jmp short L_0040354f
    L_0040353c:
        fld dword ptr [esp+34h]
    L_00403540:
        fcomp
    L_00403542:
        fnstsw ax
    L_00403544:
        test ah,41h
    L_00403547:
        jne short L_0040354f
    L_00403549:
        fstp st(0)
    L_0040354b:
        fld dword ptr [esp+34h]
    L_0040354f:
        fld dword ptr [esp+38h]
    L_00403553:
        fcomp dword ptr [esp+0Ch]
    L_00403557:
        fnstsw ax
    L_00403559:
        test ah,5
    L_0040355c:
        jp short L_00403568
    L_0040355e:
        mov ecx,dword ptr [esp+38h]
    L_00403562:
        mov dword ptr [esp+0Ch],ecx
    L_00403566:
        jmp short L_0040357f
    L_00403568:
        fld dword ptr [esp+38h]
    L_0040356c:
        fcomp dword ptr [esp+4]
    L_00403570:
        fnstsw ax
    L_00403572:
        test ah,41h
    L_00403575:
        jne short L_0040357f
    L_00403577:
        mov edx,dword ptr [esp+38h]
    L_0040357b:
        mov dword ptr [esp+4],edx
    L_0040357f:
        fld dword ptr [esp+48h]
    L_00403583:
        fcomp dword ptr [data_00470b04]
    L_00403589:
        fnstsw ax
    L_0040358b:
        test ah,1
    L_0040358e:
        jne short L_004035fd
    L_00403590:
        fld dword ptr [esp+48h]
    L_00403594:
        fcomp dword ptr [data_00470afc]
    L_0040359a:
        fnstsw ax
    L_0040359c:
        test ah,41h
    L_0040359f:
        jp short L_004035fd
    L_004035a1:
        fld dword ptr [esp+40h]
    L_004035a5:
        fcomp dword ptr [esp+8]
    L_004035a9:
        fnstsw ax
    L_004035ab:
        test ah,5
    L_004035ae:
        jp short L_004035ba
    L_004035b0:
        mov eax,dword ptr [esp+40h]
    L_004035b4:
        mov dword ptr [esp+8],eax
    L_004035b8:
        jmp short L_004035cd
    L_004035ba:
        fld dword ptr [esp+40h]
    L_004035be:
        fcomp
    L_004035c0:
        fnstsw ax
    L_004035c2:
        test ah,41h
    L_004035c5:
        jne short L_004035cd
    L_004035c7:
        fstp st(0)
    L_004035c9:
        fld dword ptr [esp+40h]
    L_004035cd:
        fld dword ptr [esp+44h]
    L_004035d1:
        fcomp dword ptr [esp+0Ch]
    L_004035d5:
        fnstsw ax
    L_004035d7:
        test ah,5
    L_004035da:
        jp short L_004035e6
    L_004035dc:
        mov ecx,dword ptr [esp+44h]
    L_004035e0:
        mov dword ptr [esp+0Ch],ecx
    L_004035e4:
        jmp short L_004035fd
    L_004035e6:
        fld dword ptr [esp+44h]
    L_004035ea:
        fcomp dword ptr [esp+4]
    L_004035ee:
        fnstsw ax
    L_004035f0:
        test ah,41h
    L_004035f3:
        jne short L_004035fd
    L_004035f5:
        mov edx,dword ptr [esp+44h]
    L_004035f9:
        mov dword ptr [esp+4],edx
    L_004035fd:
        fld dword ptr [esp+54h]
    L_00403601:
        fcomp dword ptr [data_00470b04]
    L_00403607:
        fnstsw ax
    L_00403609:
        test ah,1
    L_0040360c:
        jne short L_0040367b
    L_0040360e:
        fld dword ptr [esp+54h]
    L_00403612:
        fcomp dword ptr [data_00470afc]
    L_00403618:
        fnstsw ax
    L_0040361a:
        test ah,41h
    L_0040361d:
        jp short L_0040367b
    L_0040361f:
        fld dword ptr [esp+4Ch]
    L_00403623:
        fcomp dword ptr [esp+8]
    L_00403627:
        fnstsw ax
    L_00403629:
        test ah,5
    L_0040362c:
        jp short L_00403638
    L_0040362e:
        mov eax,dword ptr [esp+4Ch]
    L_00403632:
        mov dword ptr [esp+8],eax
    L_00403636:
        jmp short L_0040364b
    L_00403638:
        fld dword ptr [esp+4Ch]
    L_0040363c:
        fcomp
    L_0040363e:
        fnstsw ax
    L_00403640:
        test ah,41h
    L_00403643:
        jne short L_0040364b
    L_00403645:
        fstp st(0)
    L_00403647:
        fld dword ptr [esp+4Ch]
    L_0040364b:
        fld dword ptr [esp+50h]
    L_0040364f:
        fcomp dword ptr [esp+0Ch]
    L_00403653:
        fnstsw ax
    L_00403655:
        test ah,5
    L_00403658:
        jp short L_00403664
    L_0040365a:
        mov ecx,dword ptr [esp+50h]
    L_0040365e:
        mov dword ptr [esp+0Ch],ecx
    L_00403662:
        jmp short L_0040367b
    L_00403664:
        fld dword ptr [esp+50h]
    L_00403668:
        fcomp dword ptr [esp+4]
    L_0040366c:
        fnstsw ax
    L_0040366e:
        test ah,41h
    L_00403671:
        jne short L_0040367b
    L_00403673:
        mov edx,dword ptr [esp+50h]
    L_00403677:
        mov dword ptr [esp+4],edx
    L_0040367b:
        fld dword ptr [esp+60h]
    L_0040367f:
        fcomp dword ptr [data_00470b04]
    L_00403685:
        fnstsw ax
    L_00403687:
        test ah,1
    L_0040368a:
        jne short L_004036f9
    L_0040368c:
        fld dword ptr [esp+60h]
    L_00403690:
        fcomp dword ptr [data_00470afc]
    L_00403696:
        fnstsw ax
    L_00403698:
        test ah,41h
    L_0040369b:
        jp short L_004036f9
    L_0040369d:
        fld dword ptr [esp+58h]
    L_004036a1:
        fcomp dword ptr [esp+8]
    L_004036a5:
        fnstsw ax
    L_004036a7:
        test ah,5
    L_004036aa:
        jp short L_004036b6
    L_004036ac:
        mov eax,dword ptr [esp+58h]
    L_004036b0:
        mov dword ptr [esp+8],eax
    L_004036b4:
        jmp short L_004036c9
    L_004036b6:
        fld dword ptr [esp+58h]
    L_004036ba:
        fcomp
    L_004036bc:
        fnstsw ax
    L_004036be:
        test ah,41h
    L_004036c1:
        jne short L_004036c9
    L_004036c3:
        fstp st(0)
    L_004036c5:
        fld dword ptr [esp+58h]
    L_004036c9:
        fld dword ptr [esp+5Ch]
    L_004036cd:
        fcomp dword ptr [esp+0Ch]
    L_004036d1:
        fnstsw ax
    L_004036d3:
        test ah,5
    L_004036d6:
        jp short L_004036e2
    L_004036d8:
        mov ecx,dword ptr [esp+5Ch]
    L_004036dc:
        mov dword ptr [esp+0Ch],ecx
    L_004036e0:
        jmp short L_004036f9
    L_004036e2:
        fld dword ptr [esp+5Ch]
    L_004036e6:
        fcomp dword ptr [esp+4]
    L_004036ea:
        fnstsw ax
    L_004036ec:
        test ah,41h
    L_004036ef:
        jne short L_004036f9
    L_004036f1:
        mov edx,dword ptr [esp+5Ch]
    L_004036f5:
        mov dword ptr [esp+4],edx
    L_004036f9:
        fld dword ptr [esp+6Ch]
    L_004036fd:
        fcomp dword ptr [data_00470b04]
    L_00403703:
        fnstsw ax
    L_00403705:
        test ah,1
    L_00403708:
        jne short L_00403777
    L_0040370a:
        fld dword ptr [esp+6Ch]
    L_0040370e:
        fcomp dword ptr [data_00470afc]
    L_00403714:
        fnstsw ax
    L_00403716:
        test ah,41h
    L_00403719:
        jp short L_00403777
    L_0040371b:
        fld dword ptr [esp+64h]
    L_0040371f:
        fcomp dword ptr [esp+8]
    L_00403723:
        fnstsw ax
    L_00403725:
        test ah,5
    L_00403728:
        jp short L_00403734
    L_0040372a:
        mov eax,dword ptr [esp+64h]
    L_0040372e:
        mov dword ptr [esp+8],eax
    L_00403732:
        jmp short L_00403747
    L_00403734:
        fld dword ptr [esp+64h]
    L_00403738:
        fcomp
    L_0040373a:
        fnstsw ax
    L_0040373c:
        test ah,41h
    L_0040373f:
        jne short L_00403747
    L_00403741:
        fstp st(0)
    L_00403743:
        fld dword ptr [esp+64h]
    L_00403747:
        fld dword ptr [esp+68h]
    L_0040374b:
        fcomp dword ptr [esp+0Ch]
    L_0040374f:
        fnstsw ax
    L_00403751:
        test ah,5
    L_00403754:
        jp short L_00403760
    L_00403756:
        mov ecx,dword ptr [esp+68h]
    L_0040375a:
        mov dword ptr [esp+0Ch],ecx
    L_0040375e:
        jmp short L_00403777
    L_00403760:
        fld dword ptr [esp+68h]
    L_00403764:
        fcomp dword ptr [esp+4]
    L_00403768:
        fnstsw ax
    L_0040376a:
        test ah,41h
    L_0040376d:
        jne short L_00403777
    L_0040376f:
        mov edx,dword ptr [esp+68h]
    L_00403773:
        mov dword ptr [esp+4],edx
    L_00403777:
        fld dword ptr [esp+78h]
    L_0040377b:
        fcomp dword ptr [data_00470b04]
    L_00403781:
        fnstsw ax
    L_00403783:
        test ah,1
    L_00403786:
        jne short L_004037f5
    L_00403788:
        fld dword ptr [esp+78h]
    L_0040378c:
        fcomp dword ptr [data_00470afc]
    L_00403792:
        fnstsw ax
    L_00403794:
        test ah,41h
    L_00403797:
        jp short L_004037f5
    L_00403799:
        fld dword ptr [esp+70h]
    L_0040379d:
        fcomp dword ptr [esp+8]
    L_004037a1:
        fnstsw ax
    L_004037a3:
        test ah,5
    L_004037a6:
        jp short L_004037b2
    L_004037a8:
        mov eax,dword ptr [esp+70h]
    L_004037ac:
        mov dword ptr [esp+8],eax
    L_004037b0:
        jmp short L_004037c5
    L_004037b2:
        fld dword ptr [esp+70h]
    L_004037b6:
        fcomp
    L_004037b8:
        fnstsw ax
    L_004037ba:
        test ah,41h
    L_004037bd:
        jne short L_004037c5
    L_004037bf:
        fstp st(0)
    L_004037c1:
        fld dword ptr [esp+70h]
    L_004037c5:
        fld dword ptr [esp+74h]
    L_004037c9:
        fcomp dword ptr [esp+0Ch]
    L_004037cd:
        fnstsw ax
    L_004037cf:
        test ah,5
    L_004037d2:
        jp short L_004037de
    L_004037d4:
        mov ecx,dword ptr [esp+74h]
    L_004037d8:
        mov dword ptr [esp+0Ch],ecx
    L_004037dc:
        jmp short L_004037f5
    L_004037de:
        fld dword ptr [esp+74h]
    L_004037e2:
        fcomp dword ptr [esp+4]
    L_004037e6:
        fnstsw ax
    L_004037e8:
        test ah,41h
    L_004037eb:
        jne short L_004037f5
    L_004037ed:
        mov edx,dword ptr [esp+74h]
    L_004037f1:
        mov dword ptr [esp+4],edx
    L_004037f5:
        fcomp dword ptr [data_00470bcc]
    L_004037fb:
        fnstsw ax
    L_004037fd:
        test ah,1
    L_00403800:
        jne short L_00403841
    L_00403802:
        fld dword ptr [esp+8]
    L_00403806:
        fcomp dword ptr [data_00470bdc]
    L_0040380c:
        fnstsw ax
    L_0040380e:
        test ah,41h
    L_00403811:
        jp short L_00403841
    L_00403813:
        fld dword ptr [esp+4]
    L_00403817:
        fcomp dword ptr [data_00470b48]
    L_0040381d:
        fnstsw ax
    L_0040381f:
        test ah,1
    L_00403822:
        jne short L_00403841
    L_00403824:
        fld dword ptr [esp+0Ch]
    L_00403828:
        fcomp dword ptr [data_00470bd8]
    L_0040382e:
        fnstsw ax
    L_00403830:
        test ah,41h
    L_00403833:
        jp short L_00403841
    L_00403835:
        xor eax,eax
    L_00403837:
        pop esi
    L_00403838:
        add esp,128h
    L_0040383e:
        ret 4
    L_00403841:
        mov eax,1
    L_00403846:
        pop esi
    L_00403847:
        add esp,128h
    L_0040384d:
        ret 4
    }
}

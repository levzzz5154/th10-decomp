#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404610..0x00404986: FUN_00404610
// Naked body preserves the retail register/stack ABI.

// 0x0044C350..0x0044C54C: FUN_0044c350
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044c350_0044c350() {
    __asm {
    L_0044c350:
        fld dword ptr [esp+4]
    L_0044c354:
        dec eax
    L_0044c355:
        cmp eax,0Fh
    L_0044c358:
        fdiv dword ptr [esp+8]
    L_0044c35c:
        ja asm_target_0044c54a
    L_0044c362:
        jmp dword ptr [eax*4+44C550h]
    L_0044c369:
        fld st(0)
    L_0044c36b:
        fmulp st(1),st
    L_0044c36d:
        ret 8
    L_0044c370:
        fsubr dword ptr [data_00470afc]
    L_0044c376:
        fld st(0)
    L_0044c378:
        fmulp st(1),st
    L_0044c37a:
        fsubr dword ptr [data_00470afc]
    L_0044c380:
        ret 8
    L_0044c383:
        fld st(0)
    L_0044c385:
        fmul st,st(1)
    L_0044c387:
        fmulp st(1),st
    L_0044c389:
        ret 8
    L_0044c38c:
        fsubr dword ptr [data_00470afc]
    L_0044c392:
        fld st(0)
    L_0044c394:
        fld st(0)
    L_0044c396:
        fmul st,st(1)
    L_0044c398:
        fmulp st(2),st
    L_0044c39a:
        fxch
    L_0044c39c:
        fsubr dword ptr [data_00470afc]
    L_0044c3a2:
        fstp st(1)
    L_0044c3a4:
        ret 8
    L_0044c3a7:
        fld st(0)
    L_0044c3a9:
        fmul st,st(1)
    L_0044c3ab:
        fmul st,st(1)
    L_0044c3ad:
        fmulp st(1),st
    L_0044c3af:
        ret 8
    L_0044c3b2:
        fsubr dword ptr [data_00470afc]
    L_0044c3b8:
        fld st(0)
    L_0044c3ba:
        fld st(0)
    L_0044c3bc:
        fmul st,st(1)
    L_0044c3be:
        fmul st,st(2)
    L_0044c3c0:
        fmulp st(2),st
    L_0044c3c2:
        fxch
    L_0044c3c4:
        fsubr dword ptr [data_00470afc]
    L_0044c3ca:
        fstp st(1)
    L_0044c3cc:
        ret 8
    L_0044c3cf:
        fadd st(0),st
    L_0044c3d1:
        fcom dword ptr [data_00470afc]
    L_0044c3d7:
        fnstsw ax
    L_0044c3d9:
        test ah,5
    L_0044c3dc:
        jp short L_0044c3eb
    L_0044c3de:
        fld st(0)
    L_0044c3e0:
        fmulp st(1),st
    L_0044c3e2:
        fmul dword ptr [data_00470b0c]
    L_0044c3e8:
        ret 8
    L_0044c3eb:
        fsubr dword ptr [data_00470b08]
    L_0044c3f1:
        fld st(0)
    L_0044c3f3:
        fmulp st(1),st
    L_0044c3f5:
        fsubr dword ptr [data_00470b08]
    L_0044c3fb:
        fmul dword ptr [data_00470b0c]
    L_0044c401:
        ret 8
    L_0044c404:
        fadd st(0),st
    L_0044c406:
        fcom dword ptr [data_00470afc]
    L_0044c40c:
        fnstsw ax
    L_0044c40e:
        test ah,5
    L_0044c411:
        jp short L_0044c42c
    L_0044c413:
        fsubr dword ptr [data_00470afc]
    L_0044c419:
        fld st(0)
    L_0044c41b:
        fmulp st(1),st
    L_0044c41d:
        fmul dword ptr [data_00470b0c]
    L_0044c423:
        fsubr dword ptr [data_00470b0c]
    L_0044c429:
        ret 8
    L_0044c42c:
        fsub dword ptr [data_00470afc]
    L_0044c432:
        fld st(0)
    L_0044c434:
        fmulp st(1),st
    L_0044c436:
        fmul dword ptr [data_00470b0c]
    L_0044c43c:
        fadd dword ptr [data_00470b0c]
    L_0044c442:
        ret 8
    L_0044c445:
        fadd st(0),st
    L_0044c447:
        fcom dword ptr [data_00470afc]
    L_0044c44d:
        fnstsw ax
    L_0044c44f:
        test ah,5
    L_0044c452:
        jp short L_0044c463
    L_0044c454:
        fld st(0)
    L_0044c456:
        fmul st,st(1)
    L_0044c458:
        fmulp st(1),st
    L_0044c45a:
        fmul dword ptr [data_00470b0c]
    L_0044c460:
        ret 8
    L_0044c463:
        fsubr dword ptr [data_00470b08]
    L_0044c469:
        fld st(0)
    L_0044c46b:
        fld st(0)
    L_0044c46d:
        fmul st,st(1)
    L_0044c46f:
        jmp short L_0044c4cd
    L_0044c471:
        fadd st(0),st
    L_0044c473:
        fcom dword ptr [data_00470afc]
    L_0044c479:
        fnstsw ax
    L_0044c47b:
        test ah,5
    L_0044c47e:
        jp short L_0044c48e
    L_0044c480:
        fsubr dword ptr [data_00470afc]
    L_0044c486:
        fld st(0)
    L_0044c488:
        fld st(0)
    L_0044c48a:
        fmul st,st(1)
    L_0044c48c:
        jmp short L_0044c4ff
    L_0044c48e:
        fsub dword ptr [data_00470afc]
    L_0044c494:
        fld st(0)
    L_0044c496:
        fld st(0)
    L_0044c498:
        fmul st,st(1)
    L_0044c49a:
        jmp asm_target_0044c522
    L_0044c49f:
        fadd st(0),st
    L_0044c4a1:
        fcom dword ptr [data_00470afc]
    L_0044c4a7:
        fnstsw ax
    L_0044c4a9:
        test ah,5
    L_0044c4ac:
        jp short L_0044c4bf
    L_0044c4ae:
        fld st(0)
    L_0044c4b0:
        fmul st,st(1)
    L_0044c4b2:
        fmul st,st(1)
    L_0044c4b4:
        fmulp st(1),st
    L_0044c4b6:
        fmul dword ptr [data_00470b0c]
    L_0044c4bc:
        ret 8
    L_0044c4bf:
        fsubr dword ptr [data_00470b08]
    L_0044c4c5:
        fld st(0)
    L_0044c4c7:
        fld st(0)
    L_0044c4c9:
        fmul st,st(1)
    L_0044c4cb:
        fmul st,st(2)
    L_0044c4cd:
        fmulp st(2),st
    L_0044c4cf:
        fxch
    L_0044c4d1:
        fsubr dword ptr [data_00470b08]
    L_0044c4d7:
        fmul dword ptr [data_00470b0c]
    L_0044c4dd:
        fstp st(1)
    L_0044c4df:
        ret 8
    L_0044c4e2:
        fadd st(0),st
    L_0044c4e4:
        fcom dword ptr [data_00470afc]
    L_0044c4ea:
        fnstsw ax
    L_0044c4ec:
        test ah,5
    L_0044c4ef:
        jp short L_0044c514
    L_0044c4f1:
        fsubr dword ptr [data_00470afc]
    L_0044c4f7:
        fld st(0)
    L_0044c4f9:
        fld st(0)
    L_0044c4fb:
        fmul st,st(1)
    L_0044c4fd:
        fmul st,st(2)
    L_0044c4ff:
        fmulp st(2),st
    L_0044c501:
        fxch
    L_0044c503:
        fmul dword ptr [data_00470b0c]
    L_0044c509:
        fsubr dword ptr [data_00470b0c]
    L_0044c50f:
        fstp st(1)
    L_0044c511:
        ret 8
    L_0044c514:
        fsub dword ptr [data_00470afc]
    L_0044c51a:
        fld st(0)
    L_0044c51c:
        fld st(0)
    L_0044c51e:
        fmul st,st(1)
    L_0044c520:
        fmul st,st(2)
    L_0044c522:
        fmulp st(2),st
    L_0044c524:
        fxch
    L_0044c526:
        fmul dword ptr [data_00470b0c]
    L_0044c52c:
        fadd dword ptr [data_00470b0c]
    L_0044c532:
        fstp st(1)
    L_0044c534:
        ret 8
    L_0044c537:
        fstp st(0)
    L_0044c539:
        fld dword ptr [data_00470b04]
    L_0044c53f:
        ret 8
    L_0044c542:
        fstp st(0)
    L_0044c544:
        fld dword ptr [data_00470afc]
    L_0044c54a:
        ret 8
    }
}

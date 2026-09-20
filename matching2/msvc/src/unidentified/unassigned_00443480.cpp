// BLOCKED (H2601): closest_byte_count=505; first_diff=unmeasured;
// residual_class=scheduler: private EAX receiver plus x87 scheduler and
// stack-temporary ABI: two packed mode fields select long floating-point
// branches, pooled constants feed the x87 state, and the tail calls
// 0x00442AD0 with EAX live;
// variants_tested=exact retail naked wrapper, x87 branch-by-branch source
// reading, and the adjacent 0x00443080/0x00443290 angle-helper shapes;
// next_lever=co-compile a schema-2 render cluster with an IL-visible
// 0x00442AD0 signature and a source form that pins EAX/ESP across both x87
// mode selectors; do not land a cosmetic floating-point rewrite.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00443480..0x00443678: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00443480() {
    __asm {
    L_00443480:
        push ecx
    L_00443481:
        mov ecx,dword ptr [eax+35Ch]
    L_00443487:
        test cl,1
    L_0044348a:
        je short L_0044349b
    L_0044348c:
        test cl,2
    L_0044348f:
        je short L_0044349b
    L_00443491:
        mov dl,byte ptr [eax+2FFh]
    L_00443497:
        test dl,dl
    L_00443499:
        jne short L_004434a2
    L_0044349b:
        or eax,0FFFFFFFFh
    L_0044349e:
        pop ecx
    L_0044349f:
        ret 4
    L_004434a2:
        fld dword ptr [eax+4Ch]
    L_004434a5:
        shr ecx,12h
    L_004434a8:
        fmul dword ptr [eax+3Ch]
    L_004434ab:
        and ecx,3
    L_004434ae:
        sub ecx,0
    L_004434b1:
        fmul dword ptr [data_00470b0c]
    L_004434b7:
        fld dword ptr [eax+50h]
    L_004434ba:
        fmul dword ptr [eax+40h]
    L_004434bd:
        fmul dword ptr [data_00470b0c]
    L_004434c3:
        fstp dword ptr [esp]
    L_004434c6:
        je short L_0044353c
    L_004434c8:
        dec ecx
    L_004434c9:
        je short L_00443514
    L_004434cb:
        dec ecx
    L_004434cc:
        jne asm_target_0044357e
    L_004434d2:
        fld dword ptr [eax+340h]
    L_004434d8:
        fadd dword ptr [eax+34Ch]
    L_004434de:
        fadd dword ptr [eax+334h]
    L_004434e4:
        fsub st,st(1)
    L_004434e6:
        fsubrp st(1),st
    L_004434e8:
        fst dword ptr [data_004978f8]
    L_004434ee:
        fstp dword ptr [data_004978c0]
    L_004434f4:
        fld dword ptr [eax+340h]
    L_004434fa:
        fadd dword ptr [eax+34Ch]
    L_00443500:
        fadd dword ptr [eax+334h]
    L_00443506:
        fst dword ptr [data_00497914]
    L_0044350c:
        fstp dword ptr [data_004978dc]
    L_00443512:
        jmp short L_00443580
    L_00443514:
        fld dword ptr [eax+340h]
    L_0044351a:
        fadd dword ptr [eax+34Ch]
    L_00443520:
        fadd dword ptr [eax+334h]
    L_00443526:
        fst dword ptr [data_004978f8]
    L_0044352c:
        fstp dword ptr [data_004978c0]
    L_00443532:
        fadd st(0),st
    L_00443534:
        fadd dword ptr [eax+340h]
    L_0044353a:
        jmp short L_004434fa
    L_0044353c:
        fld dword ptr [eax+340h]
    L_00443542:
        fadd dword ptr [eax+34Ch]
    L_00443548:
        fadd dword ptr [eax+334h]
    L_0044354e:
        fsub st,st(1)
    L_00443550:
        fst dword ptr [data_004978f8]
    L_00443556:
        fstp dword ptr [data_004978c0]
    L_0044355c:
        fld dword ptr [eax+340h]
    L_00443562:
        fadd dword ptr [eax+34Ch]
    L_00443568:
        fadd dword ptr [eax+334h]
    L_0044356e:
        faddp st(1),st
    L_00443570:
        fst dword ptr [data_00497914]
    L_00443576:
        fstp dword ptr [data_004978dc]
    L_0044357c:
        jmp short L_00443580
    L_0044357e:
        fstp st(0)
    L_00443580:
        mov ecx,dword ptr [eax+35Ch]
    L_00443586:
        shr ecx,14h
    L_00443589:
        and ecx,3
    L_0044358c:
        sub ecx,0
    L_0044358f:
        je short L_004435fe
    L_00443591:
        dec ecx
    L_00443592:
        je short L_004435cd
    L_00443594:
        dec ecx
    L_00443595:
        jne asm_target_00443640
    L_0044359b:
        fld dword ptr [eax+344h]
    L_004435a1:
        fadd dword ptr [eax+350h]
    L_004435a7:
        fadd dword ptr [eax+338h]
    L_004435ad:
        fsub dword ptr [esp]
    L_004435b0:
        fsub dword ptr [esp]
    L_004435b3:
        fst dword ptr [data_004978e0]
    L_004435b9:
        fstp dword ptr [data_004978c4]
    L_004435bf:
        fld dword ptr [eax+344h]
    L_004435c5:
        fadd dword ptr [eax+350h]
    L_004435cb:
        jmp short L_0044362e
    L_004435cd:
        fld dword ptr [eax+344h]
    L_004435d3:
        fadd dword ptr [eax+350h]
    L_004435d9:
        fadd dword ptr [eax+338h]
    L_004435df:
        fst dword ptr [data_004978e0]
    L_004435e5:
        fstp dword ptr [data_004978c4]
    L_004435eb:
        fld dword ptr [esp]
    L_004435ee:
        fadd st(0),st
    L_004435f0:
        fadd dword ptr [eax+344h]
    L_004435f6:
        fadd dword ptr [eax+350h]
    L_004435fc:
        jmp short L_0044362e
    L_004435fe:
        fld dword ptr [eax+344h]
    L_00443604:
        fadd dword ptr [eax+350h]
    L_0044360a:
        fadd dword ptr [eax+338h]
    L_00443610:
        fsub dword ptr [esp]
    L_00443613:
        fst dword ptr [data_004978e0]
    L_00443619:
        fstp dword ptr [data_004978c4]
    L_0044361f:
        fld dword ptr [eax+344h]
    L_00443625:
        fadd dword ptr [eax+350h]
    L_0044362b:
        fadd dword ptr [esp]
    L_0044362e:
        fadd dword ptr [eax+338h]
    L_00443634:
        fst dword ptr [data_00497918]
    L_0044363a:
        fstp dword ptr [data_004978fc]
    L_00443640:
        fld dword ptr [eax+354h]
    L_00443646:
        mov ecx,dword ptr [esp+8]
    L_0044364a:
        fadd dword ptr [eax+348h]
    L_00443650:
        push 1
    L_00443652:
        fadd dword ptr [eax+33Ch]
    L_00443658:
        fst dword ptr [data_0049791c]
    L_0044365e:
        fst dword ptr [data_00497900]
    L_00443664:
        fst dword ptr [data_004978e4]
    L_0044366a:
        fstp dword ptr [data_004978c8]
    L_00443670:
        call asm_FUN_00442ad0_00442ad0
    L_00443675:
        pop ecx
    L_00443676:
        ret 4
    }
}

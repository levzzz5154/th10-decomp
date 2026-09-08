#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00443290..0x00443475: FUN_00443290
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00443290_00443290() {
    __asm {
    L_00443290:
        sub esp,8
    L_00443293:
        fld dword ptr [eax+4Ch]
    L_00443296:
        mov ecx,dword ptr [eax+35Ch]
    L_0044329c:
        fmul dword ptr [eax+3Ch]
    L_0044329f:
        shr ecx,12h
    L_004432a2:
        fld dword ptr [eax+50h]
    L_004432a5:
        and ecx,3
    L_004432a8:
        sub ecx,0
    L_004432ab:
        fmul dword ptr [eax+40h]
    L_004432ae:
        fst dword ptr [esp]
    L_004432b1:
        fmul dword ptr [data_00470b0c]
    L_004432b7:
        fstp dword ptr [esp+4]
    L_004432bb:
        je short L_00443335
    L_004432bd:
        dec ecx
    L_004432be:
        je short L_00443307
    L_004432c0:
        dec ecx
    L_004432c1:
        jne asm_target_00443377
    L_004432c7:
        fld dword ptr [eax+334h]
    L_004432cd:
        fadd dword ptr [eax+340h]
    L_004432d3:
        fadd dword ptr [eax+34Ch]
    L_004432d9:
        fsubrp st(1),st
    L_004432db:
        fst dword ptr [data_004978f8]
    L_004432e1:
        fstp dword ptr [data_004978c0]
    L_004432e7:
        fld dword ptr [eax+334h]
    L_004432ed:
        fadd dword ptr [eax+340h]
    L_004432f3:
        fadd dword ptr [eax+34Ch]
    L_004432f9:
        fst dword ptr [data_00497914]
    L_004432ff:
        fstp dword ptr [data_004978dc]
    L_00443305:
        jmp short L_00443379
    L_00443307:
        fld dword ptr [eax+334h]
    L_0044330d:
        fadd dword ptr [eax+340h]
    L_00443313:
        fadd dword ptr [eax+34Ch]
    L_00443319:
        fst dword ptr [data_004978f8]
    L_0044331f:
        fstp dword ptr [data_004978c0]
    L_00443325:
        fld dword ptr [eax+334h]
    L_0044332b:
        fadd dword ptr [eax+340h]
    L_00443331:
        faddp st(1),st
    L_00443333:
        jmp short L_004432f3
    L_00443335:
        fld dword ptr [eax+34Ch]
    L_0044333b:
        fadd dword ptr [eax+340h]
    L_00443341:
        fadd dword ptr [eax+334h]
    L_00443347:
        fld st(1)
    L_00443349:
        fmul dword ptr [data_00470b0c]
    L_0044334f:
        fsubp st(1),st
    L_00443351:
        fstp dword ptr [data_004978f8]
    L_00443357:
        mov ecx,dword ptr [data_004978f8]
    L_0044335d:
        mov dword ptr [data_004978c0],ecx
    L_00443363:
        fadd dword ptr [data_004978f8]
    L_00443369:
        fst dword ptr [data_00497914]
    L_0044336f:
        fstp dword ptr [data_004978dc]
    L_00443375:
        jmp short L_00443379
    L_00443377:
        fstp st(0)
    L_00443379:
        mov ecx,dword ptr [eax+35Ch]
    L_0044337f:
        shr ecx,14h
    L_00443382:
        and ecx,3
    L_00443385:
        sub ecx,0
    L_00443388:
        je short L_004433fe
    L_0044338a:
        dec ecx
    L_0044338b:
        je short L_004433c9
    L_0044338d:
        dec ecx
    L_0044338e:
        jne asm_target_0044343b
    L_00443394:
        fld dword ptr [eax+350h]
    L_0044339a:
        fadd dword ptr [eax+338h]
    L_004433a0:
        fadd dword ptr [eax+344h]
    L_004433a6:
        fsub dword ptr [esp]
    L_004433a9:
        fst dword ptr [data_004978e0]
    L_004433af:
        fstp dword ptr [data_004978c4]
    L_004433b5:
        fld dword ptr [eax+350h]
    L_004433bb:
        fadd dword ptr [eax+338h]
    L_004433c1:
        fadd dword ptr [eax+344h]
    L_004433c7:
        jmp short L_0044342f
    L_004433c9:
        fld dword ptr [eax+350h]
    L_004433cf:
        fadd dword ptr [eax+338h]
    L_004433d5:
        fadd dword ptr [eax+344h]
    L_004433db:
        fst dword ptr [data_004978e0]
    L_004433e1:
        fstp dword ptr [data_004978c4]
    L_004433e7:
        fld dword ptr [eax+350h]
    L_004433ed:
        fadd dword ptr [eax+338h]
    L_004433f3:
        fadd dword ptr [esp]
    L_004433f6:
        fadd dword ptr [eax+344h]
    L_004433fc:
        jmp short L_0044342f
    L_004433fe:
        fld dword ptr [eax+350h]
    L_00443404:
        fadd dword ptr [eax+344h]
    L_0044340a:
        fadd dword ptr [eax+338h]
    L_00443410:
        fsub dword ptr [esp+4]
    L_00443414:
        fstp dword ptr [data_004978e0]
    L_0044341a:
        mov edx,dword ptr [data_004978e0]
    L_00443420:
        fld dword ptr [data_004978e0]
    L_00443426:
        mov dword ptr [data_004978c4],edx
    L_0044342c:
        fadd dword ptr [esp]
    L_0044342f:
        fst dword ptr [data_00497918]
    L_00443435:
        fstp dword ptr [data_004978fc]
    L_0044343b:
        fld dword ptr [eax+350h]
    L_00443441:
        mov ecx,dword ptr [esp+0Ch]
    L_00443445:
        fadd dword ptr [eax+348h]
    L_0044344b:
        push 0
    L_0044344d:
        fadd dword ptr [eax+33Ch]
    L_00443453:
        fst dword ptr [data_0049791c]
    L_00443459:
        fst dword ptr [data_00497900]
    L_0044345f:
        fst dword ptr [data_004978e4]
    L_00443465:
        fstp dword ptr [data_004978c8]
    L_0044346b:
        call asm_FUN_00442670_00442670
    L_00443470:
        add esp,8
    L_00443473:
        ret 4
    }
}

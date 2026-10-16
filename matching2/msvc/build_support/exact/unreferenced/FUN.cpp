// BLOCKED (H2601): closest_byte_count=370; first_diff=unmeasured;
// residual_class=abi: private register ABI and x87 source shape: retail
// receives object state in ECX, point data in EDI, and the scalar on the
// stack, while the 1000-iteration loop depends on those homes and the x87
// compare chain;
// variants_tested=exact retail naked wrapper, IDA __userpurge
// (EAX-return/ECX-object/EDI-point) signature, and the adjacent score-vector
// helper family; no caller-visible source model was byte-measured;
// next_lever=build the real score/entity caller cluster with an IL-visible
// callee carrying ECX/EDI and preserve the x87 compare ordering.

#include "../../include/asm_encoding.hpp"
#include "../../include/asm_symbols.hpp"

// 0x004084A0..0x00408611: FUN_004084a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004084a0_004084a0() {
    __asm {
    L_004084a0:
        fld dword ptr [esp+4]
    L_004084a4:
        sub esp,30h
    L_004084a7:
        fmul dword ptr [esp+34h]
    L_004084ab:
        push ebx
    L_004084ac:
        push esi
    L_004084ad:
        xor esi,esi
    L_004084af:
        add ecx,450h
    L_004084b5:
        mov ebx,7D0h
    L_004084ba:
        lea ebx,[ebx+force_disp32_zero]
    L_004084c0:
        mov ax,word ptr [ecx+56h]
    L_004084c4:
        test ax,ax
    L_004084c7:
        je asm_target_004085f9
    L_004084cd:
        cmp ax,3
    L_004084d1:
        je asm_target_004085f9
    L_004084d7:
        fld dword ptr [ecx]
    L_004084d9:
        fmul dword ptr [flt_0_5]
    L_004084df:
        fld dword ptr [ecx-3Ch]
    L_004084e2:
        fsub st,st(1)
    L_004084e4:
        fld dword ptr [ecx+4]
    L_004084e7:
        fmul dword ptr [flt_0_5]
    L_004084ed:
        fld dword ptr [ecx-38h]
    L_004084f0:
        fsub st,st(1)
    L_004084f2:
        fst dword ptr [esp+18h]
    L_004084f6:
        fxch st(3)
    L_004084f8:
        fadd dword ptr [ecx-3Ch]
    L_004084fb:
        fstp dword ptr [esp+8]
    L_004084ff:
        fadd dword ptr [ecx-38h]
    L_00408502:
        fst dword ptr [esp+0Ch]
    L_00408506:
        fstp dword ptr [esp+30h]
    L_0040850a:
        fxch
    L_0040850c:
        fadd dword ptr [ecx+4]
    L_0040850f:
        fstp dword ptr [esp+24h]
    L_00408513:
        fld dword ptr [esp+0Ch]
    L_00408517:
        fsub dword ptr [ecx+4]
    L_0040851a:
        fstp dword ptr [esp+0Ch]
    L_0040851e:
        fld dword ptr [edi+4]
    L_00408521:
        fsub dword ptr [esp+18h]
    L_00408525:
        fstp dword ptr [esp+3Ch]
    L_00408529:
        fsubr dword ptr [edi]
    L_0040852b:
        fld st(0)
    L_0040852d:
        fmulp st(1),st
    L_0040852f:
        fld dword ptr [esp+3Ch]
    L_00408533:
        fmul dword ptr [esp+3Ch]
    L_00408537:
        fadd st,st(1)
    L_00408539:
        fcomp st(2)
    L_0040853b:
        fnstsw ax
    L_0040853d:
        test ah,41h
    L_00408540:
        jne short L_004085a2
    L_00408542:
        fld dword ptr [edi+4]
    L_00408545:
        fsub dword ptr [esp+24h]
    L_00408549:
        fld st(0)
    L_0040854b:
        fmul st,st(1)
    L_0040854d:
        fadd st,st(2)
    L_0040854f:
        fcomp st(3)
    L_00408551:
        fnstsw ax
    L_00408553:
        fstp st(0)
    L_00408555:
        test ah,41h
    L_00408558:
        fstp st(0)
    L_0040855a:
        jne short L_004085a4
    L_0040855c:
        fld dword ptr [edi+4]
    L_0040855f:
        fsub dword ptr [esp+30h]
    L_00408563:
        fld dword ptr [edi]
    L_00408565:
        fsub dword ptr [esp+8]
    L_00408569:
        fld st(0)
    L_0040856b:
        fmul st,st(1)
    L_0040856d:
        fstp dword ptr [esp+3Ch]
    L_00408571:
        fstp st(0)
    L_00408573:
        fld st(0)
    L_00408575:
        fmul st,st(1)
    L_00408577:
        fadd dword ptr [esp+3Ch]
    L_0040857b:
        fcomp st(2)
    L_0040857d:
        fnstsw ax
    L_0040857f:
        fstp st(0)
    L_00408581:
        test ah,41h
    L_00408584:
        jne short L_004085a4
    L_00408586:
        fld dword ptr [edi+4]
    L_00408589:
        fsub dword ptr [esp+0Ch]
    L_0040858d:
        fld st(0)
    L_0040858f:
        fmul st,st(1)
    L_00408591:
        fadd dword ptr [esp+3Ch]
    L_00408595:
        fcomp st(2)
    L_00408597:
        fnstsw ax
    L_00408599:
        fstp st(0)
    L_0040859b:
        test ah,41h
    L_0040859e:
        je short L_004085f9
    L_004085a0:
        jmp short L_004085a4
    L_004085a2:
        fstp st(0)
    L_004085a4:
        mov edx,dword ptr [ecx-54h]
    L_004085a7:
        test edx,edx
    L_004085a9:
        je short L_004085f9
    L_004085ab:
        fld dword ptr [edx+34h]
    L_004085ae:
        fcomp dword ptr [data_00470bd0]
    L_004085b4:
        fnstsw ax
    L_004085b6:
        test ah,41h
    L_004085b9:
        jp short L_004085be
    L_004085bb:
        inc esi
    L_004085bc:
        jmp short L_004085f9
    L_004085be:
        fld dword ptr [edx+34h]
    L_004085c1:
        fcomp dword ptr [flt_16]
    L_004085c7:
        fnstsw ax
    L_004085c9:
        test ah,41h
    L_004085cc:
        jp short L_004085d1
    L_004085ce:
        inc esi
    L_004085cf:
        jmp short L_004085f9
    L_004085d1:
        fld dword ptr [edx+34h]
    L_004085d4:
        fcomp dword ptr [flt_32]
    L_004085da:
        fnstsw ax
    L_004085dc:
        test ah,41h
    L_004085df:
        jp short L_004085e6
    L_004085e1:
        add esi,4
    L_004085e4:
        jmp short L_004085f9
    L_004085e6:
        fld dword ptr [edx+34h]
    L_004085e9:
        fcomp dword ptr [flt_64]
    L_004085ef:
        fnstsw ax
    L_004085f1:
        test ah,41h
    L_004085f4:
        jp short L_004085f9
    L_004085f6:
        add esi,0Ah
    L_004085f9:
        add ecx,7F0h
    L_004085ff:
        dec ebx
    L_00408600:
        jne asm_target_004084c0
    L_00408606:
        mov eax,esi
    L_00408608:
        fstp st(0)
    L_0040860a:
        pop esi
    L_0040860b:
        pop ebx
    L_0040860c:
        add esp,30h
    L_0040860f:
        ret 4
    }
}

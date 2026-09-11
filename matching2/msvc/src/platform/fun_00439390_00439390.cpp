#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438AD0..0x0043900C: GameMain
// Naked body preserves the retail register/stack ABI.

// 0x00439390..0x004393C8: FUN_00439390
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439390_00439390() {
    __asm {
    L_00439390:
        push ebp
    L_00439391:
        mov ebp,dword ptr [esp+8]
    L_00439395:
        push esi
    L_00439396:
        push edi
    L_00439397:
        call asm_FUN_00439540_00439540
    L_0043939c:
        fcom qword ptr [ebp+40h]
    L_0043939f:
        fst qword ptr [ebp+38h]
    L_004393a2:
        fnstsw ax
    L_004393a4:
        test ah,5
    L_004393a7:
        jp short L_004393ac
    L_004393a9:
        fst qword ptr [ebp+48h]
    L_004393ac:
        fcom qword ptr [ebp+48h]
    L_004393af:
        fst qword ptr [ebp+40h]
    L_004393b2:
        fnstsw ax
    L_004393b4:
        test ah,41h
    L_004393b7:
        jne asm_target_00439527
    L_004393bd:
        fcomp qword ptr [ebp+48h]
    L_004393c0:
        fnstsw ax
    L_004393c2:
        test ah,41h
    L_004393c5:
        TH10_REL8(0x75, 0x004393c5, VA_asm_target_004393e9)
    L_004393c7:
        TH10_REL8(0xeb, 0x004393c7, VA_asm_FUN_00439390_part_004393d0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_004393d0:
        fld qword ptr [ebp+48h]
    L_004393d3:
        fadd qword ptr [data_00470c90]
    L_004393d9:
        fstp qword ptr [ebp+48h]
    L_004393dc:
        fld qword ptr [ebp+48h]
    L_004393df:
        fcomp qword ptr [ebp+38h]
    L_004393e2:
        fnstsw ax
    L_004393e4:
        test ah,5
    L_004393e7:
        jnp short L_004393d0
    L_004393e9:
        mov esi,dword ptr [data_00491c10]
    L_004393ef:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004393f4:
        mov edi,491E94h
    L_004393f9:
        mov dword ptr [data_00491fac],edi
    L_004393ff:
        call asm_Camera_ApplyRetail_00421480
    L_00439404:
        mov edx,dword ptr [data_00491fac]
    L_0043940a:
        mov eax,dword ptr [data_00491c30]
    L_0043940f:
        mov ecx,dword ptr [eax]
    L_00439411:
        add edx,0CCh
    L_00439417:
        push edx
    L_00439418:
        push eax
    L_00439419:
        call dword ptr [ecx+0BCh]
    L_0043941f:
        mov eax,dword ptr [data_00491be4]
    L_00439424:
        push eax
    L_00439425:
        mov dword ptr [data_00491fb0],1
    L_0043942f:
        call asm_FUN_00449c00_00449c00
    L_00439434:
        push 492590h
    L_00439439:
        mov esi,eax
    L_0043943b:
        call asm_FUN_0043ddf0_0043ddf0
    L_00439440:
        test esi,esi
    L_00439442:
        jne short L_00439459
    L_00439444:
        mov esi,492254h
    L_00439449:
        call asm_Platform_StopWorker_0044c150
    L_0043944e:
        pop edi
    L_0043944f:
        pop esi
    L_00439450:
        mov eax,1
    L_00439455:
        pop ebp
    L_00439456:
        ret 4
    L_00439459:
        cmp esi,0FFFFFFFFh
    L_0043945c:
        jne short L_00439473
    L_0043945e:
        mov esi,492254h
    L_00439463:
        call asm_Platform_StopWorker_0044c150
    L_00439468:
        pop edi
    L_00439469:
        pop esi
    L_0043946a:
        mov eax,2
    L_0043946f:
        pop ebp
    L_00439470:
        ret 4
    L_00439473:
        mov al,byte ptr [ebp+14h]
    L_00439476:
        inc al
    L_00439478:
        mov byte ptr [ebp+14h],al
    L_0043947b:
        movzx ecx,byte ptr [data_00491d66]
    L_00439482:
        movsx edx,al
    L_00439485:
        inc ecx
    L_00439486:
        cmp ecx,edx
    L_00439488:
        jg asm_target_00439511
    L_0043948e:
        mov eax,dword ptr [data_00491c30]
    L_00439493:
        mov ecx,dword ptr [eax]
    L_00439495:
        push eax
    L_00439496:
        call dword ptr [ecx+0A4h]
    L_0043949c:
        mov eax,dword ptr [data_00491c10]
    L_004394a1:
        lea ecx,[eax+3ADACCh]
    L_004394a7:
        mov dword ptr [eax+3ADAC8h],0
    L_004394b1:
        mov dword ptr [eax+72DACCh],ecx
    L_004394b7:
        mov dword ptr [eax+72DAD0h],ecx
    L_004394bd:
        mov edi,491C28h
    L_004394c2:
        mov dword ptr [data_00492378],0FFh
    L_004394cc:
        call asm_FUN_00420cd0_00420cd0
    L_004394d1:
        mov edx,dword ptr [data_00491be4]
    L_004394d7:
        push edx
    L_004394d8:
        call asm_FUN_00449d40_00449d40
    L_004394dd:
        mov esi,dword ptr [data_00491c10]
    L_004394e3:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004394e8:
        mov eax,dword ptr [data_00491c30]
    L_004394ed:
        mov ecx,dword ptr [eax]
    L_004394ef:
        push 0
    L_004394f1:
        push 0
    L_004394f3:
        push eax
    L_004394f4:
        call dword ptr [ecx+104h]
    L_004394fa:
        mov eax,dword ptr [data_00491c30]
    L_004394ff:
        mov edx,dword ptr [eax]
    L_00439501:
        push eax
    L_00439502:
        call dword ptr [edx+0A8h]
    L_00439508:
        mov byte ptr [ebp+14h],0
    L_0043950c:
        call asm_FUN_004391f0_004391f0
    L_00439511:
        call asm_FUN_00439540_00439540
    L_00439516:
        fsub qword ptr [ebp+38h]
    L_00439519:
        pop edi
    L_0043951a:
        pop esi
    L_0043951b:
        fstp qword ptr [data_004923a0]
    L_00439521:
        xor eax,eax
    L_00439523:
        pop ebp
    L_00439524:
        ret 4
    L_00439527:
        push 0
    L_00439529:
        fstp st(0)
    L_0043952b:
        call dword ptr [data_004660ac]
    L_00439531:
        pop edi
    L_00439532:
        pop esi
    L_00439533:
        xor eax,eax
    L_00439535:
        pop ebp
    L_00439536:
        ret 4
    }
}

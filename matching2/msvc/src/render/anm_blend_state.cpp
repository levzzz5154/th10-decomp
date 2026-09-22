// BLOCKED (H2701): closest_byte_count=440; first_diff=unmeasured;
// residual_class=abi/source_shape: live Ghidra identifies the real caller as
// FUN_00444760 (xref 0x00444994) and the flush callee as FUN_00442F50;
// retail carries entity in EAX and the animation manager in EBX, then stores
// packed blend/filter bytes through stack homes before issuing D3D state calls.
// variants_tested=exact retail naked wrapper, readable SyncRenderState
// counterpart, direct packed-state/D3D-vtable model, and a scratch LTCG
// caller cluster using 0x00444760; MSVC 13.10 baseline probe is exact
// (440/440), but the readable cluster did not survive existing dispatch
// contribution validation.
// next_lever=replace the existing 0x00444760 render-batch ABI anchor with a
// real caller/callee cluster that preserves EAX/EBX and packed byte homes;
// retain this wrapper until the complete 440-byte extent is emitted.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004423E0..0x00442597: FUN_004423e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004423e0_004423e0() {
    __asm {
    L_004423e0:
        push ecx
    L_004423e1:
        push esi
    L_004423e2:
        mov esi,eax
    L_004423e4:
        mov eax,dword ptr [ebx+35Ch]
    L_004423ea:
        mov cl,byte ptr [esi+3ADA68h]
    L_004423f0:
        shr eax,4
    L_004423f3:
        and eax,3
    L_004423f6:
        cmp cl,al
    L_004423f8:
        je short L_00442448
    L_004423fa:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004423ff:
        mov eax,dword ptr [ebx+35Ch]
    L_00442405:
        shr eax,4
    L_00442408:
        and al,3
    L_0044240a:
        mov byte ptr [esi+3ADA68h],al
    L_00442410:
        movzx eax,al
    L_00442413:
        sub eax,0
    L_00442416:
        je short L_00442436
    L_00442418:
        dec eax
    L_00442419:
        je short L_00442422
    L_0044241b:
        dec eax
    L_0044241c:
        jne short L_00442448
    L_0044241e:
        push 2
    L_00442420:
        jmp short L_00442438
    L_00442422:
        mov eax,dword ptr [data_00491c30]
    L_00442427:
        mov edx,dword ptr [eax]
    L_00442429:
        push 2
    L_0044242b:
        push 14h
    L_0044242d:
        push eax
    L_0044242e:
        call dword ptr [edx+0E4h]
    L_00442434:
        jmp short L_00442448
    L_00442436:
        push 6
    L_00442438:
        mov eax,dword ptr [data_00491c30]
    L_0044243d:
        mov ecx,dword ptr [eax]
    L_0044243f:
        push 14h
    L_00442441:
        push eax
    L_00442442:
        call dword ptr [ecx+0E4h]
    L_00442448:
        mov eax,dword ptr [ebx+35Ch]
    L_0044244e:
        test ah,ah
    L_00442450:
        push edi
    L_00442451:
        jns short L_0044245b
    L_00442453:
        mov edi,dword ptr [ebx+300h]
    L_00442459:
        jmp short L_00442461
    L_0044245b:
        mov edi,dword ptr [ebx+2FCh]
    L_00442461:
        mov eax,dword ptr [esi+73245Ch]
    L_00442467:
        test eax,eax
    L_00442469:
        mov dword ptr [esp+8],edi
    L_0044246d:
        je asm_target_00442509
    L_00442473:
        movzx eax,byte ptr [esi+73245Ah]
    L_0044247a:
        mov edx,edi
    L_0044247c:
        shr edx,10h
    L_0044247f:
        movzx edx,dl
    L_00442482:
        imul eax,edx
    L_00442485:
        shr eax,7
    L_00442488:
        cmp eax,100h
    L_0044248d:
        jb short L_00442494
    L_0044248f:
        mov eax,0FFh
    L_00442494:
        mov byte ptr [esp+0Ah],al
    L_00442498:
        mov ecx,dword ptr [esp+8]
    L_0044249c:
        movzx eax,byte ptr [esi+732459h]
    L_004424a3:
        shr ecx,8
    L_004424a6:
        movzx ecx,cl
    L_004424a9:
        imul eax,ecx
    L_004424ac:
        shr eax,7
    L_004424af:
        cmp eax,100h
    L_004424b4:
        jb short L_004424bb
    L_004424b6:
        mov eax,0FFh
    L_004424bb:
        movzx edx,byte ptr [esp+8]
    L_004424c0:
        mov byte ptr [esp+9],al
    L_004424c4:
        movzx eax,byte ptr [esi+732458h]
    L_004424cb:
        imul eax,edx
    L_004424ce:
        shr eax,7
    L_004424d1:
        cmp eax,100h
    L_004424d6:
        jb short L_004424dd
    L_004424d8:
        mov eax,0FFh
    L_004424dd:
        mov byte ptr [esp+8],al
    L_004424e1:
        movzx eax,byte ptr [esi+73245Bh]
    L_004424e8:
        mov ecx,dword ptr [esp+8]
    L_004424ec:
        shr ecx,18h
    L_004424ef:
        imul eax,ecx
    L_004424f2:
        shr eax,7
    L_004424f5:
        cmp eax,100h
    L_004424fa:
        jb short L_00442501
    L_004424fc:
        mov eax,0FFh
    L_00442501:
        mov byte ptr [esp+0Bh],al
    L_00442505:
        mov edi,dword ptr [esp+8]
    L_00442509:
        cmp dword ptr [esi+3ADA60h],edi
    L_0044250f:
        je short L_0044252d
    L_00442511:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00442516:
        push edi
    L_00442517:
        mov dword ptr [esi+3ADA60h],edi
    L_0044251d:
        mov eax,dword ptr [data_00491c30]
    L_00442522:
        mov edx,dword ptr [eax]
    L_00442524:
        push 3Ch
    L_00442526:
        push eax
    L_00442527:
        call dword ptr [edx+0E4h]
    L_0044252d:
        mov eax,dword ptr [ebx+35Ch]
    L_00442533:
        mov cl,byte ptr [esi+3ADA6Eh]
    L_00442539:
        shr eax,1Fh
    L_0044253c:
        cmp cl,al
    L_0044253e:
        pop edi
    L_0044253f:
        je short L_00442592
    L_00442541:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00442546:
        mov eax,dword ptr [ebx+35Ch]
    L_0044254c:
        shr eax,1Fh
    L_0044254f:
        and al,1
    L_00442551:
        mov byte ptr [esi+3ADA6Eh],al
    L_00442557:
        mov eax,dword ptr [data_00491c30]
    L_0044255c:
        mov ecx,dword ptr [eax]
    L_0044255e:
        jne short L_00442571
    L_00442560:
        push 2
    L_00442562:
        push 5
    L_00442564:
        push 0
    L_00442566:
        push eax
    L_00442567:
        call dword ptr [ecx+114h]
    L_0044256d:
        push 2
    L_0044256f:
        jmp short L_00442580
    L_00442571:
        push 1
    L_00442573:
        push 5
    L_00442575:
        push 0
    L_00442577:
        push eax
    L_00442578:
        call dword ptr [ecx+114h]
    L_0044257e:
        push 1
    L_00442580:
        mov eax,dword ptr [data_00491c30]
    L_00442585:
        mov edx,dword ptr [eax]
    L_00442587:
        push 6
    L_00442589:
        push 0
    L_0044258b:
        push eax
    L_0044258c:
        call dword ptr [edx+114h]
    L_00442592:
        inc dword ptr [esi+54h]
    L_00442595:
        pop esi
    L_00442596:
        pop ecx
    L_00442597:
        ret
    }
}

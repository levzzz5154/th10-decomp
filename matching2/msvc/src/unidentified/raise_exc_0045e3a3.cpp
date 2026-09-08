#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E3A3..0x0045E647: __raise_exc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_raise_exc_0045e3a3() {
    __asm {
    L_0045e3a3:
        push ebp
    L_0045e3a4:
        mov ebp,esp
    L_0045e3a6:
        mov ecx,dword ptr [ebp+8]
    L_0045e3a9:
        xor eax,eax
    L_0045e3ab:
        mov dword ptr [ecx+4],eax
    L_0045e3ae:
        mov ecx,dword ptr [ebp+8]
    L_0045e3b1:
        mov dword ptr [ecx+8],eax
    L_0045e3b4:
        mov ecx,dword ptr [ebp+8]
    L_0045e3b7:
        push ebx
    L_0045e3b8:
        xor ebx,ebx
    L_0045e3ba:
        mov dword ptr [ecx+0Ch],eax
    L_0045e3bd:
        mov cl,byte ptr [ebp+10h]
    L_0045e3c0:
        push esi
    L_0045e3c1:
        inc ebx
    L_0045e3c2:
        test cl,10h
    L_0045e3c5:
        push edi
    L_0045e3c6:
        je short L_0045e3d5
    L_0045e3c8:
        mov eax,dword ptr [ebp+8]
    L_0045e3cb:
        or dword ptr [eax+4],ebx
    L_0045e3ce:
        mov dword ptr [ebp+10h],0C000008Fh
    L_0045e3d5:
        test cl,2
    L_0045e3d8:
        je short L_0045e3e8
    L_0045e3da:
        mov eax,dword ptr [ebp+8]
    L_0045e3dd:
        or dword ptr [eax+4],2
    L_0045e3e1:
        mov dword ptr [ebp+10h],0C0000093h
    L_0045e3e8:
        test cl,bl
    L_0045e3ea:
        je short L_0045e3fa
    L_0045e3ec:
        mov eax,dword ptr [ebp+8]
    L_0045e3ef:
        or dword ptr [eax+4],4
    L_0045e3f3:
        mov dword ptr [ebp+10h],0C0000091h
    L_0045e3fa:
        test cl,4
    L_0045e3fd:
        je short L_0045e40d
    L_0045e3ff:
        mov eax,dword ptr [ebp+8]
    L_0045e402:
        or dword ptr [eax+4],8
    L_0045e406:
        mov dword ptr [ebp+10h],0C000008Eh
    L_0045e40d:
        test cl,8
    L_0045e410:
        je short L_0045e420
    L_0045e412:
        mov eax,dword ptr [ebp+8]
    L_0045e415:
        or dword ptr [eax+4],10h
    L_0045e419:
        mov dword ptr [ebp+10h],0C0000090h
    L_0045e420:
        mov esi,dword ptr [ebp+0Ch]
    L_0045e423:
        mov ecx,dword ptr [esi]
    L_0045e425:
        mov eax,dword ptr [ebp+8]
    L_0045e428:
        shl ecx,4
    L_0045e42b:
        not ecx
    L_0045e42d:
        xor ecx,dword ptr [eax+8]
    L_0045e430:
        push 2
    L_0045e432:
        and ecx,10h
    L_0045e435:
        xor dword ptr [eax+8],ecx
    L_0045e438:
        mov ecx,dword ptr [esi]
    L_0045e43a:
        mov eax,dword ptr [ebp+8]
    L_0045e43d:
        shl ecx,1
    L_0045e43f:
        not ecx
    L_0045e441:
        xor ecx,dword ptr [eax+8]
    L_0045e444:
        pop edi
    L_0045e445:
        and ecx,8
    L_0045e448:
        xor dword ptr [eax+8],ecx
    L_0045e44b:
        mov ecx,dword ptr [esi]
    L_0045e44d:
        mov eax,dword ptr [ebp+8]
    L_0045e450:
        shr ecx,1
    L_0045e452:
        not ecx
    L_0045e454:
        xor ecx,dword ptr [eax+8]
    L_0045e457:
        and ecx,4
    L_0045e45a:
        xor dword ptr [eax+8],ecx
    L_0045e45d:
        mov ecx,dword ptr [esi]
    L_0045e45f:
        mov eax,dword ptr [ebp+8]
    L_0045e462:
        shr ecx,3
    L_0045e465:
        not ecx
    L_0045e467:
        xor ecx,dword ptr [eax+8]
    L_0045e46a:
        and ecx,edi
    L_0045e46c:
        xor dword ptr [eax+8],ecx
    L_0045e46f:
        mov ecx,dword ptr [esi]
    L_0045e471:
        mov eax,dword ptr [ebp+8]
    L_0045e474:
        shr ecx,5
    L_0045e477:
        not ecx
    L_0045e479:
        xor ecx,dword ptr [eax+8]
    L_0045e47c:
        and ecx,ebx
    L_0045e47e:
        xor dword ptr [eax+8],ecx
    L_0045e481:
        call asm_statfp_0045ed70
    L_0045e486:
        test al,bl
    L_0045e488:
        je short L_0045e491
    L_0045e48a:
        mov ecx,dword ptr [ebp+8]
    L_0045e48d:
        or dword ptr [ecx+0Ch],10h
    L_0045e491:
        test al,4
    L_0045e493:
        je short L_0045e49c
    L_0045e495:
        mov ecx,dword ptr [ebp+8]
    L_0045e498:
        or dword ptr [ecx+0Ch],8
    L_0045e49c:
        test al,8
    L_0045e49e:
        je short L_0045e4a7
    L_0045e4a0:
        mov ecx,dword ptr [ebp+8]
    L_0045e4a3:
        or dword ptr [ecx+0Ch],4
    L_0045e4a7:
        test al,10h
    L_0045e4a9:
        je short L_0045e4b1
    L_0045e4ab:
        mov ecx,dword ptr [ebp+8]
    L_0045e4ae:
        or dword ptr [ecx+0Ch],edi
    L_0045e4b1:
        test al,20h
    L_0045e4b3:
        je short L_0045e4bb
    L_0045e4b5:
        mov eax,dword ptr [ebp+8]
    L_0045e4b8:
        or dword ptr [eax+0Ch],ebx
    L_0045e4bb:
        mov eax,dword ptr [esi]
    L_0045e4bd:
        mov ecx,0C00h
    L_0045e4c2:
        and eax,ecx
    L_0045e4c4:
        je short L_0045e4fa
    L_0045e4c6:
        cmp eax,400h
    L_0045e4cb:
        je short L_0045e4ec
    L_0045e4cd:
        cmp eax,800h
    L_0045e4d2:
        je short L_0045e4e0
    L_0045e4d4:
        cmp eax,ecx
    L_0045e4d6:
        jne short L_0045e500
    L_0045e4d8:
        mov eax,dword ptr [ebp+8]
    L_0045e4db:
        or dword ptr [eax],3
    L_0045e4de:
        jmp short L_0045e500
    L_0045e4e0:
        mov eax,dword ptr [ebp+8]
    L_0045e4e3:
        mov ecx,dword ptr [eax]
    L_0045e4e5:
        and ecx,0FFFFFFFEh
    L_0045e4e8:
        or ecx,edi
    L_0045e4ea:
        jmp short L_0045e4f6
    L_0045e4ec:
        mov eax,dword ptr [ebp+8]
    L_0045e4ef:
        mov ecx,dword ptr [eax]
    L_0045e4f1:
        and ecx,0FFFFFFFDh
    L_0045e4f4:
        or ecx,ebx
    L_0045e4f6:
        mov dword ptr [eax],ecx
    L_0045e4f8:
        jmp short L_0045e500
    L_0045e4fa:
        mov eax,dword ptr [ebp+8]
    L_0045e4fd:
        and dword ptr [eax],0FFFFFFFCh
    L_0045e500:
        mov eax,dword ptr [esi]
    L_0045e502:
        mov ecx,300h
    L_0045e507:
        and eax,ecx
    L_0045e509:
        je short L_0045e52b
    L_0045e50b:
        cmp eax,200h
    L_0045e510:
        je short L_0045e51e
    L_0045e512:
        cmp eax,ecx
    L_0045e514:
        jne short L_0045e538
    L_0045e516:
        mov eax,dword ptr [ebp+8]
    L_0045e519:
        and dword ptr [eax],0FFFFFFE3h
    L_0045e51c:
        jmp short L_0045e538
    L_0045e51e:
        mov eax,dword ptr [ebp+8]
    L_0045e521:
        mov ecx,dword ptr [eax]
    L_0045e523:
        and ecx,0FFFFFFE7h
    L_0045e526:
        or ecx,4
    L_0045e529:
        jmp short L_0045e536
    L_0045e52b:
        mov eax,dword ptr [ebp+8]
    L_0045e52e:
        mov ecx,dword ptr [eax]
    L_0045e530:
        and ecx,0FFFFFFEBh
    L_0045e533:
        or ecx,8
    L_0045e536:
        mov dword ptr [eax],ecx
    L_0045e538:
        mov eax,dword ptr [ebp+8]
    L_0045e53b:
        mov ecx,dword ptr [ebp+14h]
    L_0045e53e:
        shl ecx,5
    L_0045e541:
        xor ecx,dword ptr [eax]
    L_0045e543:
        and ecx,1FFE0h
    L_0045e549:
        xor dword ptr [eax],ecx
    L_0045e54b:
        mov eax,dword ptr [ebp+8]
    L_0045e54e:
        or dword ptr [eax+20h],ebx
    L_0045e551:
        mov eax,dword ptr [ebp+8]
    L_0045e554:
        mov ecx,dword ptr [eax+20h]
    L_0045e557:
        and ecx,0FFFFFFE3h
    L_0045e55a:
        or ecx,edi
    L_0045e55c:
        mov dword ptr [eax+20h],ecx
    L_0045e55f:
        mov eax,dword ptr [ebp+18h]
    L_0045e562:
        fld qword ptr [eax]
    L_0045e564:
        mov eax,dword ptr [ebp+8]
    L_0045e567:
        fstp qword ptr [eax+10h]
    L_0045e56a:
        mov eax,dword ptr [ebp+8]
    L_0045e56d:
        or dword ptr [eax+60h],ebx
    L_0045e570:
        mov eax,dword ptr [ebp+8]
    L_0045e573:
        mov ecx,dword ptr [eax+60h]
    L_0045e576:
        and ecx,0FFFFFFE3h
    L_0045e579:
        or ecx,edi
    L_0045e57b:
        mov edi,dword ptr [ebp+1Ch]
    L_0045e57e:
        mov dword ptr [eax+60h],ecx
    L_0045e581:
        fld qword ptr [edi]
    L_0045e583:
        mov eax,dword ptr [ebp+8]
    L_0045e586:
        fstp qword ptr [eax+50h]
    L_0045e589:
        call asm_clrfp_0045ed7b
    L_0045e58e:
        lea eax,[ebp+8]
    L_0045e591:
        push eax
    L_0045e592:
        push ebx
    L_0045e593:
        push 0
    L_0045e595:
        push dword ptr [ebp+10h]
    L_0045e598:
        call dword ptr [data_00466044]
    L_0045e59e:
        mov eax,dword ptr [ebp+8]
    L_0045e5a1:
        test byte ptr [eax+8],10h
    L_0045e5a5:
        je short L_0045e5aa
    L_0045e5a7:
        and dword ptr [esi],0FFFFFFFEh
    L_0045e5aa:
        test byte ptr [eax+8],8
    L_0045e5ae:
        je short L_0045e5b3
    L_0045e5b0:
        and dword ptr [esi],0FFFFFFFBh
    L_0045e5b3:
        test byte ptr [eax+8],4
    L_0045e5b7:
        je short L_0045e5bc
    L_0045e5b9:
        and dword ptr [esi],0FFFFFFF7h
    L_0045e5bc:
        test byte ptr [eax+8],2
    L_0045e5c0:
        je short L_0045e5c5
    L_0045e5c2:
        and dword ptr [esi],0FFFFFFEFh
    L_0045e5c5:
        test byte ptr [eax+8],bl
    L_0045e5c8:
        je short L_0045e5cd
    L_0045e5ca:
        and dword ptr [esi],0FFFFFFDFh
    L_0045e5cd:
        mov ecx,dword ptr [eax]
    L_0045e5cf:
        and ecx,3
    L_0045e5d2:
        sub ecx,0
    L_0045e5d5:
        mov edx,0FFFFF3FFh
    L_0045e5da:
        je short L_0045e60d
    L_0045e5dc:
        dec ecx
    L_0045e5dd:
        je short L_0045e5fb
    L_0045e5df:
        dec ecx
    L_0045e5e0:
        je short L_0045e5eb
    L_0045e5e2:
        dec ecx
    L_0045e5e3:
        jne short L_0045e60f
    L_0045e5e5:
        or byte ptr [esi+1],0Ch
    L_0045e5e9:
        jmp short L_0045e60f
    L_0045e5eb:
        mov ecx,dword ptr [esi]
    L_0045e5ed:
        and ecx,0FFFFFBFFh
    L_0045e5f3:
        or ecx,800h
    L_0045e5f9:
        jmp short L_0045e609
    L_0045e5fb:
        mov ecx,dword ptr [esi]
    L_0045e5fd:
        and ecx,0FFFFF7FFh
    L_0045e603:
        or ecx,400h
    L_0045e609:
        mov dword ptr [esi],ecx
    L_0045e60b:
        jmp short L_0045e60f
    L_0045e60d:
        and dword ptr [esi],edx
    L_0045e60f:
        mov ecx,dword ptr [eax]
    L_0045e611:
        shr ecx,2
    L_0045e614:
        and ecx,7
    L_0045e617:
        sub ecx,0
    L_0045e61a:
        je short L_0045e632
    L_0045e61c:
        dec ecx
    L_0045e61d:
        je short L_0045e626
    L_0045e61f:
        dec ecx
    L_0045e620:
        jne short L_0045e63e
    L_0045e622:
        and dword ptr [esi],edx
    L_0045e624:
        jmp short L_0045e63e
    L_0045e626:
        mov ecx,dword ptr [esi]
    L_0045e628:
        and ecx,edx
    L_0045e62a:
        or ecx,200h
    L_0045e630:
        jmp short L_0045e63c
    L_0045e632:
        mov ecx,dword ptr [esi]
    L_0045e634:
        and ecx,edx
    L_0045e636:
        or ecx,300h
    L_0045e63c:
        mov dword ptr [esi],ecx
    L_0045e63e:
        fld qword ptr [eax+50h]
    L_0045e641:
        fstp qword ptr [edi]
    L_0045e643:
        pop edi
    L_0045e644:
        pop esi
    L_0045e645:
        pop ebx
    L_0045e646:
        pop ebp
    L_0045e647:
        ret
    }
}

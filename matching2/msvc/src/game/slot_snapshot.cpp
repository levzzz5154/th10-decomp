// BLOCKED (D3806): closest_byte_count=0/582; first_diff=0x0042a450;
// residual_class=private EBX state input, pool/slot record layouts, and
// FUN_0042AB20/FUN_0042AA50/FUN_00428E10/FUN_00426F70/FUN_00424D90
// dependencies whose register conventions are still assembly-only.
// variants_tested=retail assembly baseline (582/582 exact), live-Ghidra
// decompilation, and a disposable schema-2 ownership probe; load_cluster
// rejected the proposed semantic classification because this exclusive
// region is still kind asm, before native-LTCG compilation.
// next_lever=caller-inclusive schema-2/native-LTCG cluster over the slot
// caller, this body, the pool allocator/copy helpers, and the complete
// record layouts; retain the full 582-byte contribution before promotion.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A450..0x0042A60C: FUN_0042a450
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a450_0042a450() {
    __asm {
    L_0042a450:
        mov eax,dword ptr [ebx+8]
    L_0042a453:
        test eax,eax
    L_0042a455:
        mov ecx,2
    L_0042a45a:
        je short L_0042a45f
    L_0042a45c:
        or dword ptr [eax+4],ecx
    L_0042a45f:
        mov eax,dword ptr [ebx+1CCh]
    L_0042a465:
        test eax,eax
    L_0042a467:
        je short L_0042a46c
    L_0042a469:
        or dword ptr [eax+4],ecx
    L_0042a46c:
        mov eax,dword ptr [ebx+0Ch]
    L_0042a46f:
        test eax,eax
    L_0042a471:
        je short L_0042a476
    L_0042a473:
        or dword ptr [eax+4],ecx
    L_0042a476:
        mov eax,dword ptr [ebx+10h]
    L_0042a479:
        test eax,eax
    L_0042a47b:
        push ebp
    L_0042a47c:
        push esi
    L_0042a47d:
        push edi
    L_0042a47e:
        jne asm_target_0042a5a3
    L_0042a484:
        mov eax,dword ptr [data_00474c7c]
    L_0042a489:
        mov ebp,dword ptr [ebx+eax*4+1Ch]
    L_0042a48d:
        mov ecx,ebx
    L_0042a48f:
        call asm_FUN_0042ab20_0042ab20
    L_0042a494:
        mov esi,dword ptr [data_00474c7c]
    L_0042a49a:
        push ebx
    L_0042a49b:
        call asm_LinkedPool_AllocateAndAppendRetail_0042aa50
    L_0042a4a0:
        mov dword ptr [ebx+9Ch],eax
    L_0042a4a6:
        mov eax,dword ptr [data_00491fc4]
    L_0042a4ab:
        test eax,eax
    L_0042a4ad:
        jne short L_0042a4f0
    L_0042a4af:
        mov eax,dword ptr [data_00474c44]
    L_0042a4b4:
        mov dword ptr [ebp+0Ch],eax
    L_0042a4b7:
        mov cx,word ptr [data_00474c48]
    L_0042a4be:
        mov word ptr [ebp+10h],cx
    L_0042a4c2:
        mov edx,dword ptr [data_00474c4c]
    L_0042a4c8:
        mov dword ptr [ebp+14h],edx
    L_0042a4cb:
        mov eax,dword ptr [data_00474c58]
    L_0042a4d0:
        mov dword ptr [ebp+18h],eax
    L_0042a4d3:
        mov ecx,dword ptr [data_00474c70]
    L_0042a4d9:
        mov dword ptr [ebp+1Ch],ecx
    L_0042a4dc:
        mov edx,dword ptr [data_00474c98]
    L_0042a4e2:
        mov dword ptr [ebp+20h],edx
    L_0042a4e5:
        mov eax,dword ptr [data_00474c90]
    L_0042a4ea:
        mov dword ptr [ebp+1B4h],eax
    L_0042a4f0:
        mov edx,dword ptr [data_00477834]
    L_0042a4f6:
        mov ecx,dword ptr [edx+3CCh]
    L_0042a4fc:
        mov dword ptr [ebp+24h],ecx
    L_0042a4ff:
        mov eax,dword ptr [edx+3D0h]
    L_0042a505:
        mov dword ptr [ebp+28h],eax
    L_0042a508:
        mov ecx,dword ptr [data_00474c7c]
    L_0042a50e:
        mov edi,dword ptr [ebx+ecx*4+1Ch]
    L_0042a512:
        lea esi,[edx+436Ch]
    L_0042a518:
        add edi,2Ch
    L_0042a51b:
        mov ecx,42h
    L_0042a520:
        rep movsd
    L_0042a522:
        lea ecx,[ebp+158h]
    L_0042a528:
        lea eax,[edx+32E0h]
    L_0042a52e:
        mov esi,4
    L_0042a533:
        mov edi,dword ptr [eax-0Ch]
    L_0042a536:
        mov dword ptr [ecx-24h],edi
    L_0042a539:
        mov edi,dword ptr [eax-8]
    L_0042a53c:
        mov dword ptr [ecx-20h],edi
    L_0042a53f:
        mov edi,dword ptr [eax-4]
    L_0042a542:
        mov dword ptr [ecx-4],edi
    L_0042a545:
        mov edi,dword ptr [eax]
    L_0042a547:
        mov dword ptr [ecx],edi
    L_0042a549:
        mov edi,dword ptr [eax+4]
    L_0042a54c:
        mov dword ptr [ecx+1Ch],edi
    L_0042a54f:
        mov edi,dword ptr [eax+8]
    L_0042a552:
        mov dword ptr [ecx+20h],edi
    L_0042a555:
        mov edi,dword ptr [eax+0Ch]
    L_0042a558:
        mov dword ptr [ecx+3Ch],edi
    L_0042a55b:
        mov edi,dword ptr [eax+10h]
    L_0042a55e:
        mov dword ptr [ecx+40h],edi
    L_0042a561:
        add eax,98h
    L_0042a566:
        add ecx,8
    L_0042a569:
        dec esi
    L_0042a56a:
        jne short L_0042a533
    L_0042a56c:
        mov eax,dword ptr [data_00474c9c]
    L_0042a571:
        mov dword ptr [ebp+1B8h],eax
    L_0042a577:
        mov ecx,dword ptr [data_00474c7c]
    L_0042a57d:
        mov dword ptr [ebx+1D0h],ecx
    L_0042a583:
        mov edx,dword ptr [edx+4474h]
    L_0042a589:
        mov eax,ecx
    L_0042a58b:
        mov ecx,dword ptr [ebx+eax*4+1Ch]
    L_0042a58f:
        mov dword ptr [ecx+1BCh],edx
    L_0042a595:
        pop edi
    L_0042a596:
        pop esi
    L_0042a597:
        mov dword ptr [ebx+1C8h],0
    L_0042a5a1:
        pop ebp
    L_0042a5a2:
        ret
    L_0042a5a3:
        cmp eax,1
    L_0042a5a6:
        jne short L_0042a595
    L_0042a5a8:
        mov eax,dword ptr [data_00474c7c]
    L_0042a5ad:
        mov edi,dword ptr [data_00477834]
    L_0042a5b3:
        lea ecx,[eax+eax*8]
    L_0042a5b6:
        mov ebp,dword ptr [ebx+ecx*4+0B0h]
    L_0042a5bd:
        mov dword ptr [ebx+1D0h],eax
    L_0042a5c3:
        lea ecx,[ebp+24h]
    L_0042a5c6:
        mov eax,edi
    L_0042a5c8:
        call asm_FUN_00428e10_00428e10
    L_0042a5cd:
        mov eax,dword ptr [data_00477834]
    L_0042a5d2:
        add edi,436Ch
    L_0042a5d8:
        lea esi,[ebp+2Ch]
    L_0042a5db:
        mov ecx,42h
    L_0042a5e0:
        rep movsd
    L_0042a5e2:
        mov edx,dword ptr [ebp+1BCh]
    L_0042a5e8:
        push eax
    L_0042a5e9:
        mov dword ptr [eax+4474h],edx
    L_0042a5ef:
        call asm_FUN_00426f70_00426f70
    L_0042a5f4:
        mov esi,dword ptr [data_00477834]
    L_0042a5fa:
        lea eax,[ebp+178h]
    L_0042a600:
        lea ecx,[esi+32E0h]
    L_0042a606:
        mov edi,4
    L_0042a60b:
        TH10_REL8(0xeb, 0x0042a60b, VA_asm_FUN_0042a450_part_0042a610)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042a610:
        mov edx,dword ptr [eax-44h]
    L_0042a613:
        mov dword ptr [ecx-0Ch],edx
    L_0042a616:
        mov edx,dword ptr [eax-40h]
    L_0042a619:
        mov dword ptr [ecx-8],edx
    L_0042a61c:
        mov edx,dword ptr [eax-24h]
    L_0042a61f:
        mov dword ptr [ecx-4],edx
    L_0042a622:
        mov edx,dword ptr [eax-20h]
    L_0042a625:
        mov dword ptr [ecx],edx
    L_0042a627:
        mov edx,dword ptr [eax-4]
    L_0042a62a:
        mov dword ptr [ecx+4],edx
    L_0042a62d:
        mov edx,dword ptr [eax]
    L_0042a62f:
        mov dword ptr [ecx+8],edx
    L_0042a632:
        mov edx,dword ptr [eax+1Ch]
    L_0042a635:
        mov dword ptr [ecx+0Ch],edx
    L_0042a638:
        mov edx,dword ptr [eax+20h]
    L_0042a63b:
        mov dword ptr [ecx+10h],edx
    L_0042a63e:
        mov edx,dword ptr [data_00474c68]
    L_0042a644:
        mov ebp,dword ptr [data_00474c6c]
    L_0042a64a:
        lea ebp,[ebp+edx*2]
    L_0042a64e:
        add ebp,edx
    L_0042a650:
        cmp ebp,5
    L_0042a653:
        jne short L_0042a661
    L_0042a655:
        mov edx,dword ptr [eax-44h]
    L_0042a658:
        mov dword ptr [ecx+0Ch],edx
    L_0042a65b:
        mov edx,dword ptr [eax-40h]
    L_0042a65e:
        mov dword ptr [ecx+10h],edx
    L_0042a661:
        add eax,8
    L_0042a664:
        add ecx,98h
    L_0042a66a:
        dec edi
    L_0042a66b:
        jne short L_0042a610
    L_0042a66d:
        xor edi,edi
    L_0042a66f:
        mov dword ptr [esi+332Ch],edi
    L_0042a675:
        mov dword ptr [esi+33C4h],edi
    L_0042a67b:
        mov dword ptr [esi+345Ch],edi
    L_0042a681:
        mov dword ptr [esi+34F4h],edi
    L_0042a687:
        call asm_FUN_00424d90_00424d90
    L_0042a68c:
        mov dword ptr [ebx+1C8h],edi
    L_0042a692:
        pop edi
    L_0042a693:
        pop esi
    L_0042a694:
        pop ebp
    L_0042a695:
        ret
    }
}

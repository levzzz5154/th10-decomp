#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
 
// BLOCKED (D3405): closest_byte_count=90/574; first_diff=0x004145F0;
// residual_class=SEH registration/prolog shape, thiscall receiver and
// Scheduler/AnimationManager private helper ABIs, plus vector-destructor
// cleanup-state ordering;
// variants_tested=live Ghidra decompile/callers/callees (0x0040A1A0,
// 0x00414830, 0x00417C80 and 0x00414370/00449F60/004492A0/004493E0)
// and MSVC 13.10 readable raw-layout fastcall candidate (536-byte extent,
// 90 matching bytes); next_lever=derive the original exception-state source
// and exact array-destructor cleanup declarations under schema2 without
// changing the production ABI.

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// 0x004145F0..0x004146BC: FUN_004145f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004145f0_004145f0() {
    __asm {
    L_004145f0:
        push 0FFFFFFFFh
    L_004145f2:
        push 46574Eh
    L_004145f7:
        mov eax,dword ptr fs:[0]
    L_004145fd:
        push eax
    L_004145fe:
        mov dword ptr fs:[0],esp
    L_00414605:
        push ecx
    L_00414606:
        push ebx
    L_00414607:
        push ebp
    L_00414608:
        push esi
    L_00414609:
        mov esi,dword ptr [esp+20h]
    L_0041460d:
        push edi
    L_0041460e:
        push esi
    L_0041460f:
        mov dword ptr [esp+20h],6
    L_00414617:
        call asm_FUN_00414370_00414370
    L_0041461c:
        mov edi,dword ptr [esi+8]
    L_0041461f:
        test edi,edi
    L_00414621:
        mov ebp,dword ptr [data_00491be4]
    L_00414627:
        mov ebx,dword ptr [data_004660b0]
    L_0041462d:
        je short L_00414656
    L_0041462f:
        push 492274h
    L_00414634:
        call ebx
    L_00414636:
        inc byte ptr [data_0049231c]
    L_0041463c:
        mov ecx,edi
    L_0041463e:
        mov edx,ebp
    L_00414640:
        call asm_Scheduler_Remove_00449f60
    L_00414645:
        push 492274h
    L_0041464a:
        call dword ptr [data_004660b4]
    L_00414650:
        dec byte ptr [data_0049231c]
    L_00414656:
        mov edi,dword ptr [esi+0Ch]
    L_00414659:
        test edi,edi
    L_0041465b:
        mov ebp,dword ptr [data_00491be4]
    L_00414661:
        je short L_0041468a
    L_00414663:
        push 492274h
    L_00414668:
        call ebx
    L_0041466a:
        inc byte ptr [data_0049231c]
    L_00414670:
        mov ecx,edi
    L_00414672:
        mov edx,ebp
    L_00414674:
        call asm_Scheduler_Remove_00449f60
    L_00414679:
        push 492274h
    L_0041467e:
        call dword ptr [data_004660b4]
    L_00414684:
        dec byte ptr [data_0049231c]
    L_0041468a:
        mov ebp,dword ptr [data_00491c10]
    L_00414690:
        mov dword ptr [esi+8],0
    L_00414697:
        mov eax,dword ptr [esi+9E50h]
    L_0041469d:
        push eax
    L_0041469e:
        mov edx,ebp
    L_004146a0:
        call asm_AnimationManager_SetFlag_004492a0
    L_004146a5:
        xor edi,edi
    L_004146a7:
        mov dword ptr [esi+9E50h],edi
    L_004146ad:
        lea ebx,[esi+9DF4h]
    L_004146b3:
        mov dword ptr [esp+10h],8
    L_004146bb:
        TH10_REL8(0xeb, 0x004146bb, VA_asm_FUN_004145f0_part_004146c0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004146c0:
        mov edx,dword ptr [ebx]
    L_004146c2:
        cmp edx,edi
    L_004146c4:
        TH10_REL8(0x74, 0x004146c4, VA_asm_target_0041472f)
    L_004146c6:
        mov eax,dword ptr [ebp+72DAD4h]
    L_004146cc:
        cmp eax,edi
    L_004146ce:
        je short L_004146dd
    L_004146d0:
        mov ecx,dword ptr [eax]
    L_004146d2:
        cmp dword ptr [ecx],edx
    L_004146d4:
        je short L_004146f6
    L_004146d6:
        mov eax,dword ptr [eax+4]
    L_004146d9:
        cmp eax,edi
    L_004146db:
        jne short L_004146d0
    L_004146dd:
        mov eax,dword ptr [ebp+72DADCh]
    L_004146e3:
        cmp eax,edi
    L_004146e5:
        TH10_REL8(0x74, 0x004146e5, VA_asm_target_0041472f)
    L_004146e7:
        mov ecx,dword ptr [eax]
    L_004146e9:
        cmp dword ptr [ecx],edx
    L_004146eb:
        je short L_004146f6
    L_004146ed:
        mov eax,dword ptr [eax+4]
    L_004146f0:
        cmp eax,edi
    L_004146f2:
        jne short L_004146e7
    L_004146f4:
        TH10_REL8(0xeb, 0x004146f4, VA_asm_target_0041472f)
    L_004146f6:
        mov eax,dword ptr [eax]
    L_004146f8:
        cmp eax,edi
    L_004146fa:
        TH10_REL8(0x74, 0x004146fa, VA_asm_target_0041472f)
    L_004146fc:
        mov ecx,dword ptr [eax+35Ch]
    L_00414702:
        mov edx,4000000h
    L_00414707:
        or ecx,edx
    L_00414709:
        mov dword ptr [eax+35Ch],ecx
    L_0041470f:
        cmp dword ptr [eax+18h],edi
    L_00414712:
        TH10_REL8(0x75, 0x00414712, VA_asm_target_0041472f)
    L_00414714:
        mov eax,dword ptr [eax+14h]
    L_00414717:
        cmp eax,edi
    L_00414719:
        TH10_REL8(0x74, 0x00414719, VA_asm_target_0041472f)
    L_0041471b:
        TH10_REL8(0xeb, 0x0041471b, VA_asm_FUN_004145f0_part_00414720)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00414720:
        mov ecx,dword ptr [eax]
    L_00414722:
        or dword ptr [ecx+35Ch],edx
    L_00414728:
        mov eax,dword ptr [eax+4]
    L_0041472b:
        cmp eax,edi
    L_0041472d:
        jne short L_00414720
    L_0041472f:
        mov eax,dword ptr [esp+10h]
    L_00414733:
        mov dword ptr [ebx],edi
    L_00414735:
        add ebx,4
    L_00414738:
        dec eax
    L_00414739:
        mov dword ptr [esp+10h],eax
    L_0041473d:
        TH10_REL8(0x75, 0x0041473d, VA_asm_FUN_004145f0_part_004146c0)
    L_0041473f:
        mov edx,dword ptr [esi+9EC8h]
    L_00414745:
        mov eax,ebp
    L_00414747:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_0041474c:
        mov eax,dword ptr [esi+9DA0h]
    L_00414752:
        cmp eax,edi
    L_00414754:
        mov dword ptr [data_0047770c],edi
    L_0041475a:
        je short L_00414765
    L_0041475c:
        push eax
    L_0041475d:
        call asm_free_00452422
    L_00414762:
        add esp,4
    L_00414765:
        push 401FF0h
    L_0041476a:
        push 7
    L_0041476c:
        push 3ACh
    L_00414771:
        lea ecx,[esi+8094h]
    L_00414777:
        push ecx
    L_00414778:
        mov dword ptr [esi+9DA0h],edi
    L_0041477e:
        mov byte ptr [esp+2Ch],4
    L_00414783:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00414788:
        push 401FF0h
    L_0041478d:
        push 2
    L_0041478f:
        push 3ACh
    L_00414794:
        lea edx,[esi+793Ch]
    L_0041479a:
        push edx
    L_0041479b:
        mov byte ptr [esp+2Ch],3
    L_004147a0:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004147a5:
        push 401FF0h
    L_004147aa:
        push 4
    L_004147ac:
        push 3ACh
    L_004147b1:
        lea eax,[esi+6A8Ch]
    L_004147b7:
        push eax
    L_004147b8:
        mov byte ptr [esp+2Ch],2
    L_004147bd:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004147c2:
        push 401FF0h
    L_004147c7:
        push 9
    L_004147c9:
        push 3ACh
    L_004147ce:
        lea ecx,[esi+4980h]
    L_004147d4:
        push ecx
    L_004147d5:
        mov byte ptr [esp+2Ch],1
    L_004147da:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004147df:
        push 401FF0h
    L_004147e4:
        push 0Ah
    L_004147e6:
        push 3ACh
    L_004147eb:
        lea edx,[esi+24C8h]
    L_004147f1:
        push edx
    L_004147f2:
        mov byte ptr [esp+2Ch],0
    L_004147f7:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004147fc:
        push 401FF0h
    L_00414801:
        push 0Ah
    L_00414803:
        push 3ACh
    L_00414808:
        add esi,10h
    L_0041480b:
        push esi
    L_0041480c:
        mov dword ptr [esp+2Ch],0FFFFFFFFh
    L_00414814:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00414819:
        mov ecx,dword ptr [esp+14h]
    L_0041481d:
        pop edi
    L_0041481e:
        pop esi
    L_0041481f:
        pop ebp
    L_00414820:
        pop ebx
    L_00414821:
        mov dword ptr fs:[0],ecx
    L_00414828:
        add esp,10h
    L_0041482b:
        ret 4
    }
}

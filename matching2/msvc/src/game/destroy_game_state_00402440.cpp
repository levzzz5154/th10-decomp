// BLOCKED (D3406): closest_byte_count=0/499; first_diff=unmeasured;
// residual_class=SEH registration/handler frame, three scheduler-removal
// calls with the private scheduler receiver, and two EH vector-destructor
// helper ABIs plus the state layout spanning offsets 0x180..0x2A44.
// variants_tested=live Ghidra complete decompilation with callers/callees,
// disassembly and variable audit; no compiler-readable candidate was
// byte-measured, so the exact naked overlay remains intact.
// next_lever=native-LTCG schema2 cluster over this body, its real
// 0x00417C80/0x00418190 callers, Scheduler_Remove, AnimationResource::Release,
// and both vector-destructor helpers, preserving the stdcall RET 4 and SEH
// cookie/handler layout.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402160..0x0040221B: ConstructGameState
// Naked body preserves the retail register/stack ABI.

// 0x00402440..0x00402632: DestroyGameState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DestroyGameState_00402440() {
    __asm {
    L_00402440:
        push 0FFFFFFFFh
    L_00402442:
        push 4652D6h
    L_00402447:
        mov eax,dword ptr fs:[0]
    L_0040244d:
        push eax
    L_0040244e:
        mov dword ptr fs:[0],esp
    L_00402455:
        push ecx
    L_00402456:
        push ebx
    L_00402457:
        push ebp
    L_00402458:
        push esi
    L_00402459:
        mov esi,dword ptr [esp+20h]
    L_0040245d:
        push edi
    L_0040245e:
        mov dword ptr [esp+1Ch],1
    L_00402466:
        mov edi,dword ptr [esi+8]
    L_00402469:
        test edi,edi
    L_0040246b:
        mov eax,dword ptr [data_00491be4]
    L_00402470:
        mov ebp,dword ptr [data_004660b0]
    L_00402476:
        mov ebx,dword ptr [data_004660b4]
    L_0040247c:
        mov dword ptr [esp+10h],eax
    L_00402480:
        je short L_004024a7
    L_00402482:
        push 492274h
    L_00402487:
        call ebp
    L_00402489:
        inc byte ptr [data_0049231c]
    L_0040248f:
        mov edx,dword ptr [esp+10h]
    L_00402493:
        mov ecx,edi
    L_00402495:
        call asm_Scheduler_Remove_00449f60
    L_0040249a:
        push 492274h
    L_0040249f:
        call ebx
    L_004024a1:
        dec byte ptr [data_0049231c]
    L_004024a7:
        mov edi,dword ptr [esi+0Ch]
    L_004024aa:
        test edi,edi
    L_004024ac:
        mov ecx,dword ptr [data_00491be4]
    L_004024b2:
        mov dword ptr [esp+10h],ecx
    L_004024b6:
        je short L_004024dd
    L_004024b8:
        push 492274h
    L_004024bd:
        call ebp
    L_004024bf:
        inc byte ptr [data_0049231c]
    L_004024c5:
        mov edx,dword ptr [esp+10h]
    L_004024c9:
        mov ecx,edi
    L_004024cb:
        call asm_Scheduler_Remove_00449f60
    L_004024d0:
        push 492274h
    L_004024d5:
        call ebx
    L_004024d7:
        dec byte ptr [data_0049231c]
    L_004024dd:
        mov edi,dword ptr [esi+2A40h]
    L_004024e3:
        test edi,edi
    L_004024e5:
        mov edx,dword ptr [data_00491be4]
    L_004024eb:
        mov dword ptr [esp+10h],edx
    L_004024ef:
        je short L_00402516
    L_004024f1:
        push 492274h
    L_004024f6:
        call ebp
    L_004024f8:
        inc byte ptr [data_0049231c]
    L_004024fe:
        mov edx,dword ptr [esp+10h]
    L_00402502:
        mov ecx,edi
    L_00402504:
        call asm_Scheduler_Remove_00449f60
    L_00402509:
        push 492274h
    L_0040250e:
        call ebx
    L_00402510:
        dec byte ptr [data_0049231c]
    L_00402516:
        mov eax,dword ptr [esi+10h]
    L_00402519:
        test eax,eax
    L_0040251b:
        je short L_0040252d
    L_0040251d:
        push eax
    L_0040251e:
        call asm_free_00452422
    L_00402523:
        add esp,4
    L_00402526:
        mov dword ptr [esi+10h],0
    L_0040252d:
        mov eax,dword ptr [esi+2A44h]
    L_00402533:
        test eax,eax
    L_00402535:
        je short L_0040254a
    L_00402537:
        push eax
    L_00402538:
        call asm_free_00452422
    L_0040253d:
        add esp,4
    L_00402540:
        mov dword ptr [esi+2A44h],0
    L_0040254a:
        mov eax,dword ptr [esi+17Ch]
    L_00402550:
        test eax,eax
    L_00402552:
        mov dword ptr [esi+2A44h],0
    L_0040255c:
        je short L_00402571
    L_0040255e:
        push eax
    L_0040255f:
        call asm_free_00452422
    L_00402564:
        add esp,4
    L_00402567:
        mov dword ptr [esi+17Ch],0
    L_00402571:
        test byte ptr [data_00474ca0],1
    L_00402578:
        jne short L_004025bd
    L_0040257a:
        mov eax,dword ptr [esi+2A30h]
    L_00402580:
        and eax,1
    L_00402583:
        add eax,4
    L_00402586:
        js short L_004025bd
    L_00402588:
        cmp eax,21h
    L_0040258b:
        jae short L_004025bd
    L_0040258d:
        mov ecx,dword ptr [data_00491c10]
    L_00402593:
        mov edi,dword ptr [ecx+eax*4+3AD06Ch]
    L_0040259a:
        test edi,edi
    L_0040259c:
        lea ebp,[ecx+eax*4+3AD06Ch]
    L_004025a3:
        je short L_004025bd
    L_004025a5:
        call asm_FUN_00447810_00447810
    L_004025aa:
        mov eax,dword ptr [ebp]
    L_004025ad:
        push eax
    L_004025ae:
        call asm_free_004524a1
    L_004025b3:
        add esp,4
    L_004025b6:
        mov dword ptr [ebp],0
    L_004025bd:
        cmp dword ptr [data_004776e8],esi
    L_004025c3:
        jne short L_004025cf
    L_004025c5:
        mov dword ptr [data_004776e8],0
    L_004025cf:
        cmp dword ptr [data_004776e4],esi
    L_004025d5:
        jne short L_004025e1
    L_004025d7:
        mov dword ptr [data_004776e4],0
    L_004025e1:
        push 401FF0h
    L_004025e6:
        push 3
    L_004025e8:
        push 3ACh
    L_004025ed:
        lea edx,[esi+1F08h]
    L_004025f3:
        push edx
    L_004025f4:
        mov byte ptr [esp+2Ch],0
    L_004025f9:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004025fe:
        push 401FF0h
    L_00402603:
        push 8
    L_00402605:
        push 3ACh
    L_0040260a:
        add esi,180h
    L_00402610:
        push esi
    L_00402611:
        mov dword ptr [esp+2Ch],0FFFFFFFFh
    L_00402619:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0040261e:
        mov ecx,dword ptr [esp+14h]
    L_00402622:
        pop edi
    L_00402623:
        pop esi
    L_00402624:
        pop ebp
    L_00402625:
        pop ebx
    L_00402626:
        mov dword ptr fs:[0],ecx
    L_0040262d:
        add esp,10h
    L_00402630:
        ret 4
    }
}

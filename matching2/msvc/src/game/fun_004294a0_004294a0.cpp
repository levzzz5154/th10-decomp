#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D3306): closest_byte_count=0/367; first_diff=0x004294A0
// residual_class=SEH registration/unwind shape plus private EAX/ECX helper
// calls and indirect critical-section callbacks in the destructor cluster.
// variants_tested=readable raw-layout teardown candidate (313-byte standalone
// extent; omitted retail SEH frame) with free/scheduler/vector-dtor calls, then
// restored to the exact naked baseline.
// next_lever=caller cluster 0x00429610/0x004296F0/0x00417C80 with callees
// 0x0042AB20, 0x00449F60, and 0x004525FF in native-LTCG schema2 context,
// retaining the compiler-generated SEH contribution.

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// 0x004294A0..0x0042960E: FUN_004294a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004294a0_004294a0() {
    __asm {
    L_004294a0:
        push 0FFFFFFFFh
    L_004294a2:
        push 465268h
    L_004294a7:
        mov eax,dword ptr fs:[0]
    L_004294ad:
        push eax
    L_004294ae:
        mov dword ptr fs:[0],esp
    L_004294b5:
        push ecx
    L_004294b6:
        push ebx
    L_004294b7:
        push ebp
    L_004294b8:
        push esi
    L_004294b9:
        push edi
    L_004294ba:
        mov edi,dword ptr [esp+24h]
    L_004294be:
        xor ebp,ebp
    L_004294c0:
        mov dword ptr [esp+1Ch],ebp
    L_004294c4:
        mov eax,dword ptr [edi+14h]
    L_004294c7:
        push eax
    L_004294c8:
        call asm_free_004524a1
    L_004294cd:
        add esp,4
    L_004294d0:
        xor esi,esi
    L_004294d2:
        mov eax,esi
    L_004294d4:
        mov ecx,edi
    L_004294d6:
        call asm_FUN_0042ab20_0042ab20
    L_004294db:
        inc esi
    L_004294dc:
        cmp esi,8
    L_004294df:
        jl short L_004294d2
    L_004294e1:
        mov eax,dword ptr [edi+18h]
    L_004294e4:
        push eax
    L_004294e5:
        call asm_free_004524a1
    L_004294ea:
        add esp,4
    L_004294ed:
        mov dword ptr [edi+18h],ebp
    L_004294f0:
        lea esi,[edi+1Ch]
    L_004294f3:
        mov ebx,8
    L_004294f8:
        mov eax,dword ptr [esi]
    L_004294fa:
        push eax
    L_004294fb:
        call asm_free_004524a1
    L_00429500:
        mov dword ptr [esi],ebp
    L_00429502:
        add esp,4
    L_00429505:
        add esi,4
    L_00429508:
        dec ebx
    L_00429509:
        jne short L_004294f8
    L_0042950b:
        mov esi,dword ptr [edi+8]
    L_0042950e:
        mov ebx,dword ptr [data_004660b0]
    L_00429514:
        cmp esi,ebp
    L_00429516:
        mov ebp,dword ptr [data_004660b4]
    L_0042951c:
        je short L_0042954c
    L_0042951e:
        mov eax,dword ptr [data_00491be4]
    L_00429523:
        push 492274h
    L_00429528:
        mov dword ptr [esp+14h],eax
    L_0042952c:
        call ebx
    L_0042952e:
        inc byte ptr [data_0049231c]
    L_00429534:
        mov edx,dword ptr [esp+10h]
    L_00429538:
        mov ecx,esi
    L_0042953a:
        call asm_Scheduler_Remove_00449f60
    L_0042953f:
        push 492274h
    L_00429544:
        call ebp
    L_00429546:
        dec byte ptr [data_0049231c]
    L_0042954c:
        mov eax,dword ptr [edi+1CCh]
    L_00429552:
        test eax,eax
    L_00429554:
        mov dword ptr [esp+10h],eax
    L_00429558:
        je short L_0042958d
    L_0042955a:
        mov esi,dword ptr [data_00491be4]
    L_00429560:
        push 492274h
    L_00429565:
        call ebx
    L_00429567:
        mov dl,byte ptr [data_0049231c]
    L_0042956d:
        mov ecx,dword ptr [esp+10h]
    L_00429571:
        inc dl
    L_00429573:
        mov byte ptr [data_0049231c],dl
    L_00429579:
        mov edx,esi
    L_0042957b:
        call asm_Scheduler_Remove_00449f60
    L_00429580:
        push 492274h
    L_00429585:
        call ebp
    L_00429587:
        dec byte ptr [data_0049231c]
    L_0042958d:
        mov eax,dword ptr [edi+0Ch]
    L_00429590:
        test eax,eax
    L_00429592:
        mov dword ptr [esp+10h],eax
    L_00429596:
        je short L_004295cb
    L_00429598:
        mov esi,dword ptr [data_00491be4]
    L_0042959e:
        push 492274h
    L_004295a3:
        call ebx
    L_004295a5:
        mov dl,byte ptr [data_0049231c]
    L_004295ab:
        mov ecx,dword ptr [esp+10h]
    L_004295af:
        inc dl
    L_004295b1:
        mov byte ptr [data_0049231c],dl
    L_004295b7:
        mov edx,esi
    L_004295b9:
        call asm_Scheduler_Remove_00449f60
    L_004295be:
        push 492274h
    L_004295c3:
        call ebp
    L_004295c5:
        dec byte ptr [data_0049231c]
    L_004295cb:
        cmp edi,dword ptr [data_00477838]
    L_004295d1:
        jne short L_004295dd
    L_004295d3:
        mov dword ptr [data_00477838],0
    L_004295dd:
        push 42AC60h
    L_004295e2:
        push 8
    L_004295e4:
        push 24h
    L_004295e6:
        add edi,0A0h
    L_004295ec:
        push edi
    L_004295ed:
        mov dword ptr [esp+2Ch],0FFFFFFFFh
    L_004295f5:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004295fa:
        mov ecx,dword ptr [esp+14h]
    L_004295fe:
        pop edi
    L_004295ff:
        pop esi
    L_00429600:
        pop ebp
    L_00429601:
        pop ebx
    L_00429602:
        mov dword ptr fs:[0],ecx
    L_00429609:
        add esp,10h
    L_0042960c:
        ret 4
    }
}

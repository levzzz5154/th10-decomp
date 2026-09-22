// BLOCKED (D3406): closest_byte_count=81/232; first_diff=unmeasured because
// the readable standalone candidate emitted an 81-byte contribution rather
// than the authoritative 232-byte extent.
// residual_class=SEH frame/handler shape, two scheduler-removal private ABI
// calls, and the state/resource cleanup layout. variants_tested=live Ghidra
// complete decompilation plus an MSVC 13.10 readable candidate (81-byte
// extent); a schema2 native-LTCG target+scheduler cluster was also attempted
// but LINK could not retain the decorated target entry and was discarded.
// next_lever=co-compile this body with the real 0x0040A1A0/0x00417C80 callers,
// Scheduler_Remove and free_00452422 in a corrected schema2 manifest; retain
// this exact overlay until the complete 232-byte contribution is exact.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B570..0x0042B657: FUN_0042b570
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042b570_0042b570() {
    __asm {
    L_0042b570:
        mov eax,dword ptr fs:[0]
    L_0042b576:
        push 0FFFFFFFFh
    L_0042b578:
        push 46523Bh
    L_0042b57d:
        push eax
    L_0042b57e:
        mov dword ptr fs:[0],esp
    L_0042b585:
        push ebx
    L_0042b586:
        mov ebx,dword ptr [esp+14h]
    L_0042b58a:
        push ebp
    L_0042b58b:
        push esi
    L_0042b58c:
        push edi
    L_0042b58d:
        mov dword ptr [esp+18h],0
    L_0042b595:
        mov esi,dword ptr [ebx+8]
    L_0042b598:
        test esi,esi
    L_0042b59a:
        mov edi,dword ptr [data_00491be4]
    L_0042b5a0:
        mov ebp,dword ptr [data_004660b0]
    L_0042b5a6:
        je short L_0042b5cf
    L_0042b5a8:
        push 492274h
    L_0042b5ad:
        call ebp
    L_0042b5af:
        inc byte ptr [data_0049231c]
    L_0042b5b5:
        mov ecx,esi
    L_0042b5b7:
        mov edx,edi
    L_0042b5b9:
        call asm_Scheduler_Remove_00449f60
    L_0042b5be:
        push 492274h
    L_0042b5c3:
        call dword ptr [data_004660b4]
    L_0042b5c9:
        dec byte ptr [data_0049231c]
    L_0042b5cf:
        mov esi,dword ptr [ebx+0Ch]
    L_0042b5d2:
        test esi,esi
    L_0042b5d4:
        mov edi,dword ptr [data_00491be4]
    L_0042b5da:
        je short L_0042b603
    L_0042b5dc:
        push 492274h
    L_0042b5e1:
        call ebp
    L_0042b5e3:
        inc byte ptr [data_0049231c]
    L_0042b5e9:
        mov ecx,esi
    L_0042b5eb:
        mov edx,edi
    L_0042b5ed:
        call asm_Scheduler_Remove_00449f60
    L_0042b5f2:
        push 492274h
    L_0042b5f7:
        call dword ptr [data_004660b4]
    L_0042b5fd:
        dec byte ptr [data_0049231c]
    L_0042b603:
        mov eax,dword ptr [ebx+370h]
    L_0042b609:
        xor ecx,ecx
    L_0042b60b:
        cmp eax,ecx
    L_0042b60d:
        mov dword ptr [data_00477840],ecx
    L_0042b613:
        je short L_0042b63d
    L_0042b615:
        push eax
    L_0042b616:
        call asm_free_00452422
    L_0042b61b:
        add esp,4
    L_0042b61e:
        mov dword ptr [ebx+370h],0
    L_0042b628:
        mov ecx,dword ptr [esp+10h]
    L_0042b62c:
        mov dword ptr fs:[0],ecx
    L_0042b633:
        pop edi
    L_0042b634:
        pop esi
    L_0042b635:
        pop ebp
    L_0042b636:
        pop ebx
    L_0042b637:
        add esp,0Ch
    L_0042b63a:
        ret 4
    L_0042b63d:
        pop edi
    L_0042b63e:
        mov dword ptr [ebx+370h],ecx
    L_0042b644:
        mov ecx,dword ptr [esp+0Ch]
    L_0042b648:
        pop esi
    L_0042b649:
        pop ebp
    L_0042b64a:
        mov dword ptr fs:[0],ecx
    L_0042b651:
        pop ebx
    L_0042b652:
        add esp,0Ch
    L_0042b655:
        ret 4
    }
}

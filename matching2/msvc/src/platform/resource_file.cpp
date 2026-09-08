#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436680..0x004366B0: FUN_00436680
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436680_00436680() {
    __asm {
    L_00436680:
        push esi
    L_00436681:
        mov esi,ecx
    L_00436683:
        mov eax,dword ptr [esi+0Ch]
    L_00436686:
        push edi
    L_00436687:
        xor edi,edi
    L_00436689:
        cmp eax,edi
    L_0043668b:
        mov dword ptr [esi],46F308h
    L_00436691:
        je short L_0043669f
    L_00436693:
        push eax
    L_00436694:
        call asm_free_00452422
    L_00436699:
        add esp,4
    L_0043669c:
        mov dword ptr [esi+0Ch],edi
    L_0043669f:
        mov dword ptr [esi+0Ch],edi
    L_004366a2:
        mov dword ptr [esi+4],edi
    L_004366a5:
        mov dword ptr [esi+8],edi
    L_004366a8:
        pop edi
    L_004366a9:
        mov dword ptr [esi],46F210h
    L_004366af:
        pop esi
    L_004366b0:
        ret
    }
}

// 0x004366C0..0x00436767: FUN_004366c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004366c0_004366c0() {
    __asm {
    L_004366c0:
        push ebx
    L_004366c1:
        push ebp
    L_004366c2:
        push esi
    L_004366c3:
        mov ebx,ecx
    L_004366c5:
        mov eax,dword ptr [ebx]
    L_004366c7:
        push edi
    L_004366c8:
        call dword ptr [eax+4]
    L_004366cb:
        mov ecx,dword ptr [esp+14h]
    L_004366cf:
        push 0Ah
    L_004366d1:
        push ecx
    L_004366d2:
        push 0
    L_004366d4:
        call dword ptr [data_004660e8]
    L_004366da:
        mov edi,eax
    L_004366dc:
        test edi,edi
    L_004366de:
        je short L_0043672f
    L_004366e0:
        push edi
    L_004366e1:
        push 0
    L_004366e3:
        call dword ptr [data_004660ec]
    L_004366e9:
        mov ebp,eax
    L_004366eb:
        test ebp,ebp
    L_004366ed:
        je short L_0043672f
    L_004366ef:
        push ebp
    L_004366f0:
        call dword ptr [data_004661dc]
    L_004366f6:
        mov esi,eax
    L_004366f8:
        test esi,esi
    L_004366fa:
        jne short L_00436713
    L_004366fc:
        push eax
    L_004366fd:
        call dword ptr [data_004660f4]
    L_00436703:
        mov edx,dword ptr [ebx]
    L_00436705:
        mov ecx,ebx
    L_00436707:
        call dword ptr [edx+4]
    L_0043670a:
        pop edi
    L_0043670b:
        pop esi
    L_0043670c:
        pop ebp
    L_0043670d:
        mov al,1
    L_0043670f:
        pop ebx
    L_00436710:
        ret 8
    L_00436713:
        push edi
    L_00436714:
        push 0
    L_00436716:
        call dword ptr [data_004660f8]
    L_0043671c:
        push eax
    L_0043671d:
        mov dword ptr [ebx+4],eax
    L_00436720:
        call asm_malloc_00452706
    L_00436725:
        add esp,4
    L_00436728:
        test eax,eax
    L_0043672a:
        mov dword ptr [ebx+0Ch],eax
    L_0043672d:
        jne short L_0043673f
    L_0043672f:
        mov edx,dword ptr [ebx]
    L_00436731:
        mov ecx,ebx
    L_00436733:
        call dword ptr [edx+4]
    L_00436736:
        pop edi
    L_00436737:
        pop esi
    L_00436738:
        pop ebp
    L_00436739:
        mov al,1
    L_0043673b:
        pop ebx
    L_0043673c:
        ret 8
    L_0043673f:
        mov ecx,dword ptr [ebx+4]
    L_00436742:
        mov edi,eax
    L_00436744:
        mov eax,ecx
    L_00436746:
        shr ecx,2
    L_00436749:
        rep movsd
    L_0043674b:
        mov ecx,eax
    L_0043674d:
        and ecx,3
    L_00436750:
        rep movsb
    L_00436752:
        mov ecx,dword ptr [ebx+0Ch]
    L_00436755:
        push ebp
    L_00436756:
        mov dword ptr [ebx+8],ecx
    L_00436759:
        call dword ptr [data_004660f4]
    L_0043675f:
        pop edi
    L_00436760:
        pop esi
    L_00436761:
        pop ebp
    L_00436762:
        mov al,1
    L_00436764:
        pop ebx
    L_00436765:
        ret 8
    }
}

// 0x00436CA0..0x00436CE7: FUN_00436ca0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436ca0_00436ca0() {
    __asm {
    L_00436ca0:
        mov eax,ecx
    L_00436ca2:
        shr eax,14h
    L_00436ca5:
        mov edx,ecx
    L_00436ca7:
        and eax,0Fh
    L_00436caa:
        shr edx,0Ch
    L_00436cad:
        shl eax,4
    L_00436cb0:
        and edx,0Fh
    L_00436cb3:
        or eax,edx
    L_00436cb5:
        mov edx,dword ptr [esi+120h]
    L_00436cbb:
        shr ecx,4
    L_00436cbe:
        and ecx,0Fh
    L_00436cc1:
        shl eax,4
    L_00436cc4:
        push edi
    L_00436cc5:
        mov edi,dword ptr [esi+10Ch]
    L_00436ccb:
        or eax,ecx
    L_00436ccd:
        xor ecx,ecx
    L_00436ccf:
        test edi,edi
    L_00436cd1:
        jle short L_00436ce6
    L_00436cd3:
        mov word ptr [edx],ax
    L_00436cd6:
        mov edi,dword ptr [esi+10Ch]
    L_00436cdc:
        add ecx,2
    L_00436cdf:
        add edx,2
    L_00436ce2:
        cmp ecx,edi
    L_00436ce4:
        jl short L_00436cd3
    L_00436ce6:
        pop edi
    L_00436ce7:
        ret
    }
}

// Recovered semantic C++ definitions.
#include "th10/platform/memory_file.hpp"

__declspec(noinline) ResourceFile::~ResourceFile() {
    Close();
}


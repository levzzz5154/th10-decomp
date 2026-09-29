// BLOCKED (D3407): closest_byte_count=0/369; first_diff=extent (readable loader candidate emitted 351 bytes vs retail 369 before byte comparison);
// residual_class=private-ABI/source-shape; retail carries path in EAX, state in ESI, and slot on the stack,
// with pointer arithmetic and Win32 indirect calls scheduled around that register tuple.
// variants_tested=retail naked baseline (369/369 exact), bounded readable loader model (351 bytes),
// live Ghidra FUN_0043D7D0 decompile, and exact probe;
// next_lever=native-LTCG cluster with the real path-loading caller and production state layout.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043D7D0..0x0043D940: cache a music slot from the current container file.
// Tested C++: reference/semantic_candidates/sound_music_cache.cpp.
// See reference/recovery_notes/sound_music_cache_0043d7d0.md.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d7d0_0043d7d0() {
    __asm {
    L_0043d7d0:
        push ecx
    L_0043d7d1:
        push ebx
    L_0043d7d2:
        push ebp
    L_0043d7d3:
        mov ebp,dword ptr [esp+10h]
    L_0043d7d7:
        mov ebx,eax
    L_0043d7d9:
        mov eax,dword ptr [esi+ebp*4+1EC0h]
    L_0043d7e0:
        test eax,eax
    L_0043d7e2:
        push edi
    L_0043d7e3:
        je short L_0043d824
    L_0043d7e5:
        mov eax,ebp
    L_0043d7e7:
        shl eax,8
    L_0043d7ea:
        lea edi,[eax+esi+4108h]
    L_0043d7f1:
        mov eax,ebx
    L_0043d7f3:
        mov dl,byte ptr [eax]
    L_0043d7f5:
        mov cl,dl
    L_0043d7f7:
        cmp dl,byte ptr [edi]
    L_0043d7f9:
        jne short L_0043d817
    L_0043d7fb:
        test cl,cl
    L_0043d7fd:
        je short L_0043d813
    L_0043d7ff:
        mov dl,byte ptr [eax+1]
    L_0043d802:
        mov cl,dl
    L_0043d804:
        cmp dl,byte ptr [edi+1]
    L_0043d807:
        jne short L_0043d817
    L_0043d809:
        add eax,2
    L_0043d80c:
        add edi,2
    L_0043d80f:
        test cl,cl
    L_0043d811:
        jne short L_0043d7f3
    L_0043d813:
        xor eax,eax
    L_0043d815:
        jmp short L_0043d81c
    L_0043d817:
        sbb eax,eax
    L_0043d819:
        sbb eax,0FFFFFFFFh
    L_0043d81c:
        test eax,eax
    L_0043d81e:
        je asm_target_0043d938
    L_0043d824:
        mov ecx,ebp
    L_0043d826:
        shl ecx,8
    L_0043d829:
        lea edx,[ecx+496698h]
    L_0043d82f:
        mov eax,ebx
    L_0043d831:
        sub edx,ebx
    L_0043d833:
        mov cl,byte ptr [eax]
    L_0043d835:
        mov byte ptr [edx+eax],cl
    L_0043d838:
        inc eax
    L_0043d839:
        test cl,cl
    L_0043d83b:
        jne short L_0043d833
    L_0043d83d:
        test byte ptr [data_00491d78],10h
    L_0043d844:
        je asm_target_0043d938
    L_0043d84a:
        mov eax,dword ptr [esi+610h]
    L_0043d850:
        test eax,eax
    L_0043d852:
        je asm_target_0043d938
    L_0043d858:
        mov eax,dword ptr [esi+ebp*4+1EC0h]
    L_0043d85f:
        test eax,eax
    L_0043d861:
        je short L_0043d877
    L_0043d863:
        push eax
    L_0043d864:
        call asm_free_00452422
    L_0043d869:
        add esp,4
    L_0043d86c:
        mov dword ptr [esi+ebp*4+1EC0h],0
    L_0043d877:
        push 0
    L_0043d879:
        push 8000080h
    L_0043d87e:
        push 3
    L_0043d880:
        push 0
    L_0043d882:
        push 1
    L_0043d884:
        push 80000000h
    L_0043d889:
        lea edx,[esi+5108h]
    L_0043d88f:
        push edx
    L_0043d890:
        call dword ptr [data_004660c4]
    L_0043d896:
        mov ebp,eax
    L_0043d898:
        cmp ebp,0FFFFFFFFh
    L_0043d89b:
        je short L_0043d8e0
    L_0043d89d:
        push esi
    L_0043d89e:
        mov ecx,ebx
    L_0043d8a0:
        call asm_Path_FindBasenameSlot_0043d2a0
    L_0043d8a5:
        mov edi,eax
    L_0043d8a7:
        mov eax,dword ptr [esi+1F84h]
    L_0043d8ad:
        imul edi,34h
    L_0043d8b0:
        mov ecx,dword ptr [eax+edi+10h]
    L_0043d8b4:
        push 0
    L_0043d8b6:
        push 0
    L_0043d8b8:
        push ecx
    L_0043d8b9:
        push ebp
    L_0043d8ba:
        call dword ptr [data_004660c8]
    L_0043d8c0:
        mov edx,dword ptr [esi+1F84h]
    L_0043d8c6:
        mov eax,dword ptr [edx+edi+14h]
    L_0043d8ca:
        push eax
    L_0043d8cb:
        call asm_malloc_00452706
    L_0043d8d0:
        mov ebx,eax
    L_0043d8d2:
        add esp,4
    L_0043d8d5:
        test ebx,ebx
    L_0043d8d7:
        jne short L_0043d8ea
    L_0043d8d9:
        push ebp
    L_0043d8da:
        call dword ptr [data_004660cc]
    L_0043d8e0:
        pop edi
    L_0043d8e1:
        pop ebp
    L_0043d8e2:
        or eax,0FFFFFFFFh
    L_0043d8e5:
        pop ebx
    L_0043d8e6:
        pop ecx
    L_0043d8e7:
        ret 4
    L_0043d8ea:
        mov ecx,dword ptr [esi+1F84h]
    L_0043d8f0:
        mov edx,dword ptr [ecx+edi+14h]
    L_0043d8f4:
        push 0
    L_0043d8f6:
        lea eax,[esp+10h]
    L_0043d8fa:
        push eax
    L_0043d8fb:
        push edx
    L_0043d8fc:
        push ebx
    L_0043d8fd:
        push ebp
    L_0043d8fe:
        call dword ptr [data_004660d0]
    L_0043d904:
        push ebp
    L_0043d905:
        call dword ptr [data_004660cc]
    L_0043d90b:
        mov ecx,dword ptr [esi+1F84h]
    L_0043d911:
        mov eax,dword ptr [esp+14h]
    L_0043d915:
        add ecx,edi
    L_0043d917:
        mov edx,ecx
    L_0043d919:
        mov dword ptr [esi+eax*4+1E80h],ecx
    L_0043d920:
        mov dword ptr [esi+eax*4+1EC0h],ebx
    L_0043d927:
        mov dword ptr [esi+eax*4+1F00h],ebx
    L_0043d92e:
        mov ecx,dword ptr [edx+14h]
    L_0043d931:
        mov dword ptr [esi+eax*4+1F40h],ecx
    L_0043d938:
        pop edi
    L_0043d939:
        pop ebp
    L_0043d93a:
        xor eax,eax
    L_0043d93c:
        pop ebx
    L_0043d93d:
        pop ecx
    L_0043d93e:
        ret 4
    }
}

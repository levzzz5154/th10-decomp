// Complete candidate: reference/semantic_candidates/sound_stream_launch.cpp.
// See recovery_notes/sound_file_stream_open_create_launch.md: 256 launch
// comparisons pass, including 53 executing shutdown through initial PCM refill.
// Native private ABI and byte matching remain pending; historical record below.
// BLOCKED (D3905): closest_byte_count=241/241 (exact assembly retained);
// first_diff=0x0043D693 at the EAX receiver transfer into ESI.
// residual_class=private EAX entry ABI, COM-style indirect calls, unsigned
// divide scheduling, and stack-local device descriptor construction.
// variants_tested=MSVC 13.10.6030 /O2 /Gz /MT /Gy /G6 /GF /GS /Zl with typed
// cdecl/fastcall receiver models, widened/narrowed sample arithmetic, and
// reordered local descriptor stores; no readable candidate preserved the
// 241-byte extent and private call sequence.
// next_lever=schema2 native-LTCG cluster with the real sound-thread caller,
// forcing EAX/ESI and retaining the indirect device-call ABI.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043D690..0x0043D780: FUN_0043d690
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d690_0043d690() {
    __asm {
    L_0043d690:
        push ebx
    L_0043d691:
        push ebp
    L_0043d692:
        push esi
    L_0043d693:
        mov esi,eax
    L_0043d695:
        mov eax,dword ptr [esp+10h]
    L_0043d699:
        lea edx,[esi+5108h]
    L_0043d69f:
        push edi
    L_0043d6a0:
        sub edx,eax
    L_0043d6a2:
        mov cl,byte ptr [eax]
    L_0043d6a4:
        mov byte ptr [edx+eax],cl
    L_0043d6a7:
        inc eax
    L_0043d6a8:
        test cl,cl
    L_0043d6aa:
        jne short L_0043d6a2
    L_0043d6ac:
        mov eax,dword ptr [esi+610h]
    L_0043d6b2:
        test eax,eax
    L_0043d6b4:
        jne short L_0043d6c0
    L_0043d6b6:
        or eax,0FFFFFFFFh
    L_0043d6b9:
        pop edi
    L_0043d6ba:
        pop esi
    L_0043d6bb:
        pop ebp
    L_0043d6bc:
        pop ebx
    L_0043d6bd:
        ret 4
    L_0043d6c0:
        cmp dword ptr [esi],0
    L_0043d6c3:
        je short L_0043d6b6
    L_0043d6c5:
        call asm_MidiWorker_StopRetail_0043dab0
    L_0043d6ca:
        mov ebx,dword ptr [esi+1F84h]
    L_0043d6d0:
        movzx ebp,word ptr [ebx+2Ch]
    L_0043d6d4:
        mov edi,dword ptr [ebx+24h]
    L_0043d6d7:
        imul edi,ebp
    L_0043d6da:
        push 0
    L_0043d6dc:
        push 0
    L_0043d6de:
        push 0
    L_0043d6e0:
        shl edi,2
    L_0043d6e3:
        push 0
    L_0043d6e5:
        shr edi,4
    L_0043d6e8:
        call dword ptr [data_00466120]
    L_0043d6ee:
        mov dword ptr [esi+520Ch],eax
    L_0043d6f4:
        mov ecx,dword ptr [data_00491c70]
    L_0043d6fa:
        lea eax,[esi+614h]
    L_0043d700:
        push eax
    L_0043d701:
        push 0
    L_0043d703:
        push ecx
    L_0043d704:
        push 43E3A0h
    L_0043d709:
        push 0
    L_0043d70b:
        push 0
    L_0043d70d:
        call dword ptr [data_00466118]
    L_0043d713:
        mov edx,dword ptr [esi+520Ch]
    L_0043d719:
        push ebx
    L_0043d71a:
        push edx
    L_0043d71b:
        mov dword ptr [esi+618h],eax
    L_0043d721:
        xor edx,edx
    L_0043d723:
        mov eax,edi
    L_0043d725:
        div ebp
    L_0043d727:
        mov ecx,dword ptr [data_0046a67c]
    L_0043d72d:
        sub edi,edx
    L_0043d72f:
        mov edx,dword ptr [data_0046a680]
    L_0043d735:
        push edi
    L_0043d736:
        push 10h
    L_0043d738:
        sub esp,10h
    L_0043d73b:
        mov eax,esp
    L_0043d73d:
        mov dword ptr [eax],ecx
    L_0043d73f:
        mov ecx,dword ptr [data_0046a684]
    L_0043d745:
        mov dword ptr [eax+4],edx
    L_0043d748:
        mov edx,dword ptr [data_0046a688]
    L_0043d74e:
        mov dword ptr [eax+8],ecx
    L_0043d751:
        mov dword ptr [eax+0Ch],edx
    L_0043d754:
        mov eax,dword ptr [esp+34h]
    L_0043d758:
        mov edx,dword ptr [esi+610h]
    L_0043d75e:
        push eax
    L_0043d75f:
        push edx
    L_0043d760:
        lea ecx,[esi+5208h]
    L_0043d766:
        mov edx,10100h
    L_0043d76b:
        call asm_FUN_0044c8f0_0044c8f0
    L_0043d770:
        xor ecx,ecx
    L_0043d772:
        test eax,eax
    L_0043d774:
        setge cl
    L_0043d777:
        pop edi
    L_0043d778:
        pop esi
    L_0043d779:
        pop ebp
    L_0043d77a:
        pop ebx
    L_0043d77b:
        dec ecx
    L_0043d77c:
        mov eax,ecx
    L_0043d77e:
        ret 4
    }
}

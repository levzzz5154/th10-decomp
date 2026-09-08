#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403850..0x00403983: FUN_00403850
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403850_00403850() {
    __asm {
    L_00403850:
        mov eax,dword ptr [ebx+2A44h]
    L_00403856:
        test eax,eax
    L_00403858:
        push esi
    L_00403859:
        push edi
    L_0040385a:
        jne short L_004038b3
    L_0040385c:
        mov eax,dword ptr [esp+0Ch]
    L_00403860:
        mov byte ptr [data_00497c38],0
    L_00403867:
        mov esi,eax
    L_00403869:
        lea esp,[esp+force_disp32_zero]
    L_00403870:
        mov cl,byte ptr [eax]
    L_00403872:
        inc eax
    L_00403873:
        test cl,cl
    L_00403875:
        jne short L_00403870
    L_00403877:
        mov edi,497C38h
    L_0040387c:
        sub eax,esi
    L_0040387e:
        dec edi
    L_0040387f:
        nop
    L_00403880:
        mov cl,byte ptr [edi+1]
    L_00403883:
        inc edi
    L_00403884:
        test cl,cl
    L_00403886:
        jne short L_00403880
    L_00403888:
        mov ecx,eax
    L_0040388a:
        shr ecx,2
    L_0040388d:
        rep movsd
    L_0040388f:
        mov ecx,eax
    L_00403891:
        push 0
    L_00403893:
        lea eax,[ebx+2A48h]
    L_00403899:
        and ecx,3
    L_0040389c:
        push eax
    L_0040389d:
        mov eax,497C38h
    L_004038a2:
        rep movsb
    L_004038a4:
        call asm_FUN_0044b360_0044b360
    L_004038a9:
        test eax,eax
    L_004038ab:
        mov dword ptr [ebx+2A44h],eax
    L_004038b1:
        je short L_0040391b
    L_004038b3:
        mov eax,dword ptr [ebx+2A48h]
    L_004038b9:
        push eax
    L_004038ba:
        call asm_malloc_00452706
    L_004038bf:
        mov ecx,dword ptr [ebx+2A48h]
    L_004038c5:
        mov esi,dword ptr [ebx+2A44h]
    L_004038cb:
        mov edx,ecx
    L_004038cd:
        shr ecx,2
    L_004038d0:
        mov dword ptr [ebx+10h],eax
    L_004038d3:
        mov edi,eax
    L_004038d5:
        rep movsd
    L_004038d7:
        mov ecx,edx
    L_004038d9:
        mov edx,dword ptr [data_00491c10]
    L_004038df:
        and ecx,3
    L_004038e2:
        rep movsb
    L_004038e4:
        mov eax,dword ptr [ebx+10h]
    L_004038e7:
        mov ecx,dword ptr [ebx+2A30h]
    L_004038ed:
        add esp,4
    L_004038f0:
        add eax,10h
    L_004038f3:
        and ecx,1
    L_004038f6:
        push eax
    L_004038f7:
        add ecx,4
    L_004038fa:
        call asm_Recovery_LoadCachedResource_00447280
    L_004038ff:
        test eax,eax
    L_00403901:
        mov dword ptr [ebx+178h],eax
    L_00403907:
        jne short L_00403923
    L_00403909:
        push 46CBC0h
    L_0040390e:
        mov ecx,474F70h
    L_00403913:
        call asm_TextLog_Append_0044b810
    L_00403918:
        add esp,4
    L_0040391b:
        pop edi
    L_0040391c:
        or eax,0FFFFFFFFh
    L_0040391f:
        pop esi
    L_00403920:
        ret 4
    L_00403923:
        mov eax,dword ptr [ebx+10h]
    L_00403926:
        lea ecx,[eax+90h]
    L_0040392c:
        mov dword ptr [ebx+14h],ecx
    L_0040392f:
        mov edx,dword ptr [eax+4]
    L_00403932:
        add edx,eax
    L_00403934:
        mov dword ptr [ebx+18h],edx
    L_00403937:
        mov ecx,dword ptr [eax+8]
    L_0040393a:
        add ecx,eax
    L_0040393c:
        mov dword ptr [ebx+1Ch],ecx
    L_0040393f:
        xor ecx,ecx
    L_00403941:
        cmp word ptr [eax],cx
    L_00403944:
        jle short L_00403961
    L_00403946:
        mov edx,dword ptr [ebx+14h]
    L_00403949:
        mov esi,dword ptr [edx+ecx*4]
    L_0040394c:
        lea eax,[edx+ecx*4]
    L_0040394f:
        mov edx,dword ptr [ebx+10h]
    L_00403952:
        add esi,edx
    L_00403954:
        mov dword ptr [eax],esi
    L_00403956:
        mov eax,dword ptr [ebx+10h]
    L_00403959:
        movsx edx,word ptr [eax]
    L_0040395c:
        inc ecx
    L_0040395d:
        cmp ecx,edx
    L_0040395f:
        jl short L_00403946
    L_00403961:
        mov eax,dword ptr [ebx+10h]
    L_00403964:
        movsx eax,word ptr [eax+2]
    L_00403968:
        imul eax,3ACh
    L_0040396e:
        push eax
    L_0040396f:
        call asm_malloc_00452706
    L_00403974:
        add esp,4
    L_00403977:
        pop edi
    L_00403978:
        mov dword ptr [ebx+17Ch],eax
    L_0040397e:
        xor eax,eax
    L_00403980:
        pop esi
    L_00403981:
        ret 4
    }
}

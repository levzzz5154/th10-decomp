#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004356F0..0x0043572C: FUN_004356f0
// Naked body preserves the retail register/stack ABI.

// 0x004358E0..0x0043599D: Resource_GetFileSizeRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Resource_GetFileSizeRetail_004358e0() {
    __asm {
    L_004358e0:
        push 0FFFFFFFFh
    L_004358e2:
        mov eax,dword ptr fs:[0]
    L_004358e8:
        push 465388h
    L_004358ed:
        push eax
    L_004358ee:
        mov dword ptr fs:[0],esp
    L_004358f5:
        sub esp,0Ch
    L_004358f8:
        push ebx
    L_004358f9:
        push ebp
    L_004358fa:
        push esi
    L_004358fb:
        push edi
    L_004358fc:
        mov esi,ecx
    L_004358fe:
        call asm_FUN_004356f0_004356f0
    L_00435903:
        mov ebp,eax
    L_00435905:
        xor edi,edi
    L_00435907:
        cmp ebp,edi
    L_00435909:
        je short L_00435939
    L_0043590b:
        push 2Fh
    L_0043590d:
        push esi
    L_0043590e:
        call asm_FUN_00452730_00452730
    L_00435913:
        add esp,8
    L_00435916:
        cmp eax,edi
    L_00435918:
        je short L_0043591d
    L_0043591a:
        lea esi,[eax+1]
    L_0043591d:
        mov ebx,esi
    L_0043591f:
        mov eax,ebp
    L_00435921:
        call asm_DatArchive_FindSize_00434ef0
    L_00435926:
        pop edi
    L_00435927:
        pop esi
    L_00435928:
        pop ebp
    L_00435929:
        pop ebx
    L_0043592a:
        mov ecx,dword ptr [esp+0Ch]
    L_0043592e:
        mov dword ptr fs:[0],ecx
    L_00435935:
        add esp,18h
    L_00435938:
        ret
    L_00435939:
        mov ebx,46F230h
    L_0043593e:
        mov dword ptr [esp+10h],ebx
    L_00435942:
        mov dword ptr [esp+14h],0FFFFFFFFh
    L_0043594a:
        mov dword ptr [esp+18h],edi
    L_0043594e:
        mov dword ptr [esp+24h],edi
    L_00435952:
        mov eax,dword ptr [data_00474908]
    L_00435957:
        push eax
    L_00435958:
        push esi
    L_00435959:
        lea ecx,[esp+18h]
    L_0043595d:
        call asm_FileHandle_OpenRetail_00435370
    L_00435962:
        mov eax,dword ptr [esp+14h]
    L_00435966:
        cmp eax,0FFFFFFFFh
    L_00435969:
        je short L_00435979
    L_0043596b:
        push edi
    L_0043596c:
        push eax
    L_0043596d:
        call dword ptr [data_004660d8]
    L_00435973:
        mov edi,eax
    L_00435975:
        mov eax,dword ptr [esp+14h]
    L_00435979:
        cmp eax,0FFFFFFFFh
    L_0043597c:
        mov dword ptr [esp+10h],ebx
    L_00435980:
        je short L_00435989
    L_00435982:
        push eax
    L_00435983:
        call dword ptr [data_004660cc]
    L_00435989:
        mov ecx,dword ptr [esp+1Ch]
    L_0043598d:
        mov eax,edi
    L_0043598f:
        pop edi
    L_00435990:
        pop esi
    L_00435991:
        pop ebp
    L_00435992:
        pop ebx
    L_00435993:
        mov dword ptr fs:[0],ecx
    L_0043599a:
        add esp,18h
    L_0043599d:
        ret
    }
}

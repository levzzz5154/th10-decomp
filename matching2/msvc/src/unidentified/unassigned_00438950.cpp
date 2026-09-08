#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438950..0x0043899E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438950() {
    __asm {
    L_00438950:
        cmp dword ptr [esi+2000h],esi
    L_00438956:
        je short L_0043899e
    L_00438958:
        push 46F7CCh
    L_0043895d:
        mov ecx,esi
    L_0043895f:
        call asm_TextLog_Append_0044b810
    L_00438964:
        mov al,byte ptr [esi+2004h]
    L_0043896a:
        add esp,4
    L_0043896d:
        test al,al
    L_0043896f:
        je short L_00438981
    L_00438971:
        push 10h
    L_00438973:
        push 46F7C8h
    L_00438978:
        push esi
    L_00438979:
        push 0
    L_0043897b:
        call dword ptr [data_00466234]
    L_00438981:
        mov eax,esi
    L_00438983:
        lea edx,[eax+1]
    L_00438986:
        mov cl,byte ptr [eax]
    L_00438988:
        inc eax
    L_00438989:
        test cl,cl
    L_0043898b:
        jne short L_00438986
    L_0043898d:
        push edi
    L_0043898e:
        sub eax,edx
    L_00438990:
        push esi
    L_00438991:
        push 46F7BCh
    L_00438996:
        mov edi,eax
    L_00438998:
        call asm_File_WriteWholeFile_0044b540
    L_0043899d:
        pop edi
    L_0043899e:
        ret
    }
}

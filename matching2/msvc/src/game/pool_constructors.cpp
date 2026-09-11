#include "asm_encoding.hpp"
#include "asm_symbols.hpp"


// 0x0042C920..0x0042C9EB: FUN_0042c920
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042c920_0042c920() {
    __asm {
    L_0042c920:
        mov dword ptr [edx],46ECF0h
    L_0042c926:
        xor eax,eax
    L_0042c928:
        mov dword ptr [edx+0B0h],eax
    L_0042c92e:
        mov dword ptr [edx+24h],eax
    L_0042c931:
        mov dword ptr [edx+0F8h],eax
    L_0042c937:
        push esi
    L_0042c938:
        mov esi,1
    L_0042c93d:
        mov dword ptr [edx+0F4h],esi
    L_0042c943:
        mov ecx,3E7h
    L_0042c948:
        mov dword ptr [edx+2Ch],ecx
    L_0042c94b:
        mov dword ptr [edx+188h],eax
    L_0042c951:
        mov dword ptr [edx+0FCh],eax
    L_0042c957:
        mov dword ptr [edx+1D0h],eax
    L_0042c95d:
        mov dword ptr [edx+1CCh],esi
    L_0042c963:
        mov dword ptr [edx+104h],ecx
    L_0042c969:
        mov dword ptr [edx+260h],eax
    L_0042c96f:
        mov dword ptr [edx+1D4h],eax
    L_0042c975:
        mov dword ptr [edx+2A8h],eax
    L_0042c97b:
        mov dword ptr [edx+2A4h],esi
    L_0042c981:
        mov dword ptr [edx+1DCh],ecx
    L_0042c987:
        push edi
    L_0042c988:
        and dword ptr [edx+2C0h],0FFFFFFFEh
    L_0042c98f:
        mov dword ptr [edx+5980h],eax
    L_0042c995:
        mov dword ptr [edx+58F4h],eax
    L_0042c99b:
        mov dword ptr [edx+59C8h],eax
    L_0042c9a1:
        mov dword ptr [edx+58FCh],ecx
    L_0042c9a7:
        mov dword ptr [edx+59C4h],esi
    L_0042c9ad:
        mov dword ptr [edx+5AB4h],eax
    L_0042c9b3:
        mov dword ptr [edx+5AB8h],eax
    L_0042c9b9:
        mov dword ptr [edx+5ABCh],eax
    L_0042c9bf:
        mov dword ptr [edx+5AC0h],eax
    L_0042c9c5:
        mov dword ptr [edx+5AB0h],4703E4h
    L_0042c9cf:
        mov ecx,16B3h
    L_0042c9d4:
        mov edi,edx
    L_0042c9d6:
        rep stosd
    L_0042c9d8:
        mov eax,dword ptr [edx+4]
    L_0042c9db:
        or eax,2
    L_0042c9de:
        pop edi
    L_0042c9df:
        mov dword ptr [edx+4],eax
    L_0042c9e2:
        mov dword ptr [data_0047784c],edx
    L_0042c9e8:
        mov eax,edx
    L_0042c9ea:
        pop esi
    L_0042c9eb:
        ret
    }
}


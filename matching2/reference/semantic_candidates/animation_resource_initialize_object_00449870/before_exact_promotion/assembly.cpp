#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449870..0x00449948: FUN_00449870
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449870_00449870() {
    __asm {
    L_00449870:
        sub esp,0Ch
    L_00449873:
        mov edx,dword ptr [esp+10h]
    L_00449877:
        push esi
    L_00449878:
        push edi
    L_00449879:
        mov dword ptr [esp+8],0
    L_00449881:
        mov edi,dword ptr [esp+8]
    L_00449885:
        lea esi,[edx+340h]
    L_0044988b:
        mov dword ptr [esi],edi
    L_0044988d:
        mov dword ptr [esp+0Ch],0
    L_00449895:
        mov edi,dword ptr [esp+0Ch]
    L_00449899:
        mov dword ptr [esi+4],edi
    L_0044989c:
        mov dword ptr [esp+10h],0
    L_004498a4:
        mov edi,dword ptr [esp+10h]
    L_004498a8:
        mov dword ptr [esi+8],edi
    L_004498ab:
        mov dword ptr [esp+8],0
    L_004498b3:
        mov edi,dword ptr [esp+8]
    L_004498b7:
        lea esi,[edx+334h]
    L_004498bd:
        mov dword ptr [esi],edi
    L_004498bf:
        mov dword ptr [esp+0Ch],0
    L_004498c7:
        mov edi,dword ptr [esp+0Ch]
    L_004498cb:
        mov dword ptr [esi+4],edi
    L_004498ce:
        mov dword ptr [esp+10h],0
    L_004498d6:
        mov edi,dword ptr [esp+10h]
    L_004498da:
        mov dword ptr [esi+8],edi
    L_004498dd:
        mov eax,ecx
    L_004498df:
        mov ecx,dword ptr [edx+35Ch]
    L_004498e5:
        lea esi,[edx+34Ch]
    L_004498eb:
        mov dword ptr [esp+8],0
    L_004498f3:
        mov edi,dword ptr [esp+8]
    L_004498f7:
        mov dword ptr [esi],edi
    L_004498f9:
        or ecx,40000000h
    L_004498ff:
        mov dword ptr [esp+0Ch],0
    L_00449907:
        mov edi,dword ptr [esp+0Ch]
    L_0044990b:
        mov dword ptr [esi+4],edi
    L_0044990e:
        mov dword ptr [edx+35Ch],ecx
    L_00449914:
        mov ecx,dword ptr [esp+1Ch]
    L_00449918:
        mov dword ptr [esp+10h],0
    L_00449920:
        mov edi,dword ptr [esp+10h]
    L_00449924:
        mov word ptr [edx+38Ah],cx
    L_0044992b:
        mov dword ptr [esi+8],edi
    L_0044992e:
        mov byte ptr [edx+3A1h],10h
    L_00449935:
        mov byte ptr [edx+3A0h],10h
    L_0044993c:
        call asm_AnimationObject_LoadScriptPreservingState_0043e7e0
    L_00449941:
        pop edi
    L_00449942:
        pop esi
    L_00449943:
        add esp,0Ch
    L_00449946:
        ret 8
    }
}

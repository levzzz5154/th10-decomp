#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C680..0x0041C75A: FUN_0041c680
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c680_0041c680() {
    __asm {
    L_0041c680:
        push esi
    L_0041c681:
        push edi
    L_0041c682:
        mov edx,ebx
    L_0041c684:
        call asm_ScoreObject_Initialize_0041c030
    L_0041c689:
        mov dword ptr [ebx],46DA10h
    L_0041c68f:
        xor eax,eax
    L_0041c691:
        mov esi,0FFFFFFFEh
    L_0041c696:
        lea edx,[ebx+424h]
    L_0041c69c:
        mov edi,edx
    L_0041c69e:
        mov ecx,7Eh
    L_0041c6a3:
        rep stosd
    L_0041c6a5:
        mov dword ptr [edx+2Ch],41000000h
    L_0041c6ac:
        mov edi,dword ptr [ebx+688h]
    L_0041c6b2:
        lea edx,[ebx+61Ch]
    L_0041c6b8:
        and edi,esi
    L_0041c6ba:
        mov dword ptr [edx+6Ch],edi
    L_0041c6bd:
        and dword ptr [edx+0B0h],esi
    L_0041c6c3:
        and dword ptr [edx+0FCh],esi
    L_0041c6c9:
        and dword ptr [edx+128h],esi
    L_0041c6cf:
        and dword ptr [edx+174h],esi
    L_0041c6d5:
        and dword ptr [edx+1B0h],esi
    L_0041c6db:
        and dword ptr [edx+1FCh],esi
    L_0041c6e1:
        and dword ptr [edx+228h],esi
    L_0041c6e7:
        and dword ptr [edx+378h],esi
    L_0041c6ed:
        xor eax,eax
    L_0041c6ef:
        mov edi,edx
    L_0041c6f1:
        mov ecx,0EBh
    L_0041c6f6:
        rep stosd
    L_0041c6f8:
        mov word ptr [edx+384h],0FFFFh
    L_0041c701:
        mov edi,dword ptr [ebx+0A34h]
    L_0041c707:
        lea edx,[ebx+9C8h]
    L_0041c70d:
        and edi,esi
    L_0041c70f:
        mov dword ptr [edx+6Ch],edi
    L_0041c712:
        and dword ptr [edx+0B0h],esi
    L_0041c718:
        and dword ptr [edx+0FCh],esi
    L_0041c71e:
        and dword ptr [edx+128h],esi
    L_0041c724:
        and dword ptr [edx+174h],esi
    L_0041c72a:
        and dword ptr [edx+1B0h],esi
    L_0041c730:
        and dword ptr [edx+1FCh],esi
    L_0041c736:
        and dword ptr [edx+228h],esi
    L_0041c73c:
        and dword ptr [edx+378h],esi
    L_0041c742:
        xor eax,eax
    L_0041c744:
        mov ecx,0EBh
    L_0041c749:
        mov edi,edx
    L_0041c74b:
        rep stosd
    L_0041c74d:
        pop edi
    L_0041c74e:
        mov word ptr [edx+384h],0FFFFh
    L_0041c757:
        mov eax,ebx
    L_0041c759:
        pop esi
    L_0041c75a:
        ret
    }
}

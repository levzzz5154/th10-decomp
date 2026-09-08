#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418C40..0x00418CBC: GameConfig_InitializeDefaults
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameConfig_InitializeDefaults_00418c40() {
    __asm {
    L_00418c40:
        push esi
    L_00418c41:
        push edi
    L_00418c42:
        xor eax,eax
    L_00418c44:
        mov ecx,0Dh
    L_00418c49:
        mov edi,edx
    L_00418c4b:
        rep stosd
    L_00418c4d:
        mov ecx,258h
    L_00418c52:
        mov word ptr [edx+16h],cx
    L_00418c56:
        mov word ptr [edx+18h],cx
    L_00418c5a:
        mov cl,1
    L_00418c5c:
        mov byte ptr [edx+1Bh],cl
    L_00418c5f:
        mov byte ptr [edx+1Ch],cl
    L_00418c62:
        or dword ptr [edx+30h],100h
    L_00418c69:
        xor al,al
    L_00418c6b:
        mov byte ptr [edx+1Ah],al
    L_00418c6e:
        mov dword ptr [edx],100003h
    L_00418c74:
        mov byte ptr [edx+1Dh],al
    L_00418c77:
        mov byte ptr [edx+1Eh],al
    L_00418c7a:
        mov esi,dword ptr [data_00474e88]
    L_00418c80:
        lea ecx,[edx+4]
    L_00418c83:
        mov dword ptr [ecx],esi
    L_00418c85:
        mov esi,dword ptr [data_00474e8c]
    L_00418c8b:
        mov dword ptr [ecx+4],esi
    L_00418c8e:
        mov esi,dword ptr [data_00474e90]
    L_00418c94:
        mov dword ptr [ecx+8],esi
    L_00418c97:
        mov esi,dword ptr [data_00474e94]
    L_00418c9d:
        mov dword ptr [ecx+0Ch],esi
    L_00418ca0:
        mov si,word ptr [data_00474e98]
    L_00418ca7:
        pop edi
    L_00418ca8:
        mov word ptr [ecx+10h],si
    L_00418cac:
        mov byte ptr [edx+1Fh],2
    L_00418cb0:
        mov byte ptr [edx+22h],al
    L_00418cb3:
        mov byte ptr [edx+20h],64h
    L_00418cb7:
        mov byte ptr [edx+21h],50h
    L_00418cbb:
        pop esi
    L_00418cbc:
        ret
    }
}

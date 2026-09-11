#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.

// 0x00404F30..0x00404FF9: FUN_00404f30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404f30_00404f30() {
    __asm {
    L_00404f30:
        sub esp,0Ch
    L_00404f33:
        push ebx
    L_00404f34:
        mov edx,esi
    L_00404f36:
        mov ebx,eax
    L_00404f38:
        call asm_InitializeEntity_00401de0
    L_00404f3d:
        mov dword ptr [esp+4],0
    L_00404f45:
        mov ecx,dword ptr [esp+4]
    L_00404f49:
        lea eax,[esi+340h]
    L_00404f4f:
        mov dword ptr [eax],ecx
    L_00404f51:
        mov dword ptr [esp+8],0
    L_00404f59:
        mov edx,dword ptr [esp+8]
    L_00404f5d:
        mov dword ptr [eax+4],edx
    L_00404f60:
        mov dword ptr [esp+0Ch],0
    L_00404f68:
        mov ecx,dword ptr [esp+0Ch]
    L_00404f6c:
        mov dword ptr [eax+8],ecx
    L_00404f6f:
        mov dword ptr [esp+4],0
    L_00404f77:
        mov eax,dword ptr [esp+4]
    L_00404f7b:
        lea edx,[esi+334h]
    L_00404f81:
        mov dword ptr [edx],eax
    L_00404f83:
        mov dword ptr [esp+8],0
    L_00404f8b:
        mov ecx,dword ptr [esp+8]
    L_00404f8f:
        mov dword ptr [edx+4],ecx
    L_00404f92:
        mov dword ptr [esp+0Ch],0
    L_00404f9a:
        mov eax,dword ptr [esp+0Ch]
    L_00404f9e:
        mov dword ptr [edx+8],eax
    L_00404fa1:
        mov dword ptr [esp+4],0
    L_00404fa9:
        mov edx,dword ptr [esp+4]
    L_00404fad:
        lea ecx,[esi+34Ch]
    L_00404fb3:
        mov dword ptr [ecx],edx
    L_00404fb5:
        mov dword ptr [esp+8],0
    L_00404fbd:
        mov eax,dword ptr [esp+8]
    L_00404fc1:
        mov dword ptr [ecx+4],eax
    L_00404fc4:
        mov al,10h
    L_00404fc6:
        mov dword ptr [esp+0Ch],0
    L_00404fce:
        mov edx,dword ptr [esp+0Ch]
    L_00404fd2:
        mov dword ptr [ecx+8],edx
    L_00404fd5:
        mov ecx,dword ptr [esp+14h]
    L_00404fd9:
        mov byte ptr [esi+3A1h],al
    L_00404fdf:
        mov byte ptr [esi+3A0h],al
    L_00404fe5:
        mov eax,esi
    L_00404fe7:
        mov word ptr [esi+38Ah],bx
    L_00404fee:
        call asm_AnimationObject_LoadScript_0043e710
    L_00404ff3:
        pop ebx
    L_00404ff4:
        add esp,0Ch
    L_00404ff7:
        ret 4
    }
}

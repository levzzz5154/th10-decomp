#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AB70..0x0041ABF7: FUN_0041ab70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ab70_0041ab70() {
    __asm {
    L_0041ab70:
        push esi
    L_0041ab71:
        mov esi,dword ptr [esp+8]
    L_0041ab75:
        mov dword ptr [eax+1B4h],esi
    L_0041ab7b:
        movzx esi,byte ptr [esp+0Ch]
    L_0041ab80:
        mov dword ptr [eax+1B8h],esi
    L_0041ab86:
        mov esi,dword ptr [edx]
    L_0041ab88:
        mov dword ptr [eax+180h],esi
    L_0041ab8e:
        mov edx,dword ptr [edx+4]
    L_0041ab91:
        mov dword ptr [eax+184h],edx
    L_0041ab97:
        mov edx,dword ptr [ecx]
    L_0041ab99:
        mov dword ptr [eax+188h],edx
    L_0041ab9f:
        mov ecx,dword ptr [ecx+4]
    L_0041aba2:
        mov dword ptr [eax+18Ch],ecx
    L_0041aba8:
        mov ecx,dword ptr [eax+1B0h]
    L_0041abae:
        xor edx,edx
    L_0041abb0:
        test cl,1
    L_0041abb3:
        pop esi
    L_0041abb4:
        jne short L_0041abdf
    L_0041abb6:
        or ecx,1
    L_0041abb9:
        mov dword ptr [eax+1A4h],edx
    L_0041abbf:
        mov dword ptr [eax+1A0h],0FFF0BDC1h
    L_0041abc9:
        mov dword ptr [eax+1A8h],edx
    L_0041abcf:
        mov dword ptr [eax+1ACh],476F78h
    L_0041abd9:
        mov dword ptr [eax+1B0h],ecx
    L_0041abdf:
        mov dword ptr [eax+1A4h],edx
    L_0041abe5:
        mov dword ptr [eax+1A8h],edx
    L_0041abeb:
        mov dword ptr [eax+1A0h],0FFFFFFFFh
    L_0041abf5:
        ret 8
    }
}

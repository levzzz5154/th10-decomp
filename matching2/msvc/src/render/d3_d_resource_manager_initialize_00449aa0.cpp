#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438880..0x004388E6: ?D3DResourceManager_Destroy@@
// Naked body preserves the retail register/stack ABI.

// 0x00449AA0..0x00449ADA: ?D3DResourceManager_Initialize@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DResourceManager_Initialize_00449aa0() {
    __asm {
    L_00449aa0:
        mov ecx,dword ptr [eax+4]
    L_00449aa3:
        xor edx,edx
    L_00449aa5:
        mov dword ptr [eax+8],edx
    L_00449aa8:
        mov dword ptr [eax+0Ch],edx
    L_00449aab:
        mov dword ptr [eax+10h],edx
    L_00449aae:
        mov dword ptr [eax],edx
    L_00449ab0:
        and ecx,0FFFFFFFEh
    L_00449ab3:
        mov dword ptr [eax+4],ecx
    L_00449ab6:
        lea ecx,[eax+24h]
    L_00449ab9:
        mov dword ptr [eax+14h],eax
    L_00449abc:
        mov dword ptr [eax+18h],edx
    L_00449abf:
        mov dword ptr [eax+1Ch],edx
    L_00449ac2:
        and dword ptr [ecx+4],0FFFFFFFEh
    L_00449ac6:
        mov dword ptr [ecx+8],edx
    L_00449ac9:
        mov dword ptr [ecx+0Ch],edx
    L_00449acc:
        mov dword ptr [ecx+10h],edx
    L_00449acf:
        mov dword ptr [ecx],edx
    L_00449ad1:
        mov dword ptr [ecx+14h],ecx
    L_00449ad4:
        mov dword ptr [ecx+18h],edx
    L_00449ad7:
        mov dword ptr [ecx+1Ch],edx
    L_00449ada:
        ret
    }
}

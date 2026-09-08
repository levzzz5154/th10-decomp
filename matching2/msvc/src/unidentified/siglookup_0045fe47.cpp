#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FE47..0x0045FE74: siglookup
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_siglookup_0045fe47() {
    __asm {
    L_0045fe47:
        mov ecx,dword ptr [data_00473654]
    L_0045fe4d:
        mov eax,edx
    L_0045fe4f:
        push edi
    L_0045fe50:
        cmp dword ptr [eax+4],esi
    L_0045fe53:
        je short L_0045fe62
    L_0045fe55:
        lea edi,[ecx+ecx*2]
    L_0045fe58:
        add eax,0Ch
    L_0045fe5b:
        lea edi,[edx+edi*4]
    L_0045fe5e:
        cmp eax,edi
    L_0045fe60:
        jb short L_0045fe50
    L_0045fe62:
        lea ecx,[ecx+ecx*2]
    L_0045fe65:
        lea ecx,[edx+ecx*4]
    L_0045fe68:
        cmp eax,ecx
    L_0045fe6a:
        pop edi
    L_0045fe6b:
        jae short L_0045fe72
    L_0045fe6d:
        cmp dword ptr [eax+4],esi
    L_0045fe70:
        je short L_0045fe74
    L_0045fe72:
        xor eax,eax
    L_0045fe74:
        ret
    }
}

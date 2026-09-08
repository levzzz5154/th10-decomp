#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C6E0..0x0044C751: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c6e0() {
    __asm {
    L_0044c6e0:
        mov ecx,dword ptr [esp+4]
    L_0044c6e4:
        mov edx,dword ptr [esp+8]
    L_0044c6e8:
        mov dword ptr [eax],ecx
    L_0044c6ea:
        mov ecx,dword ptr [esp+0Ch]
    L_0044c6ee:
        mov dword ptr [eax+4],edx
    L_0044c6f1:
        mov edx,dword ptr [esp+10h]
    L_0044c6f5:
        mov dword ptr [eax+8],ecx
    L_0044c6f8:
        mov ecx,dword ptr [esp+14h]
    L_0044c6fc:
        mov dword ptr [eax+0Ch],edx
    L_0044c6ff:
        mov edx,dword ptr [esp+18h]
    L_0044c703:
        mov dword ptr [eax+10h],ecx
    L_0044c706:
        mov ecx,dword ptr [esp+1Ch]
    L_0044c70a:
        mov dword ptr [eax+14h],edx
    L_0044c70d:
        mov edx,dword ptr [esp+20h]
    L_0044c711:
        mov dword ptr [eax+18h],ecx
    L_0044c714:
        mov ecx,dword ptr [esp+24h]
    L_0044c718:
        mov dword ptr [eax+1Ch],edx
    L_0044c71b:
        mov edx,dword ptr [esp+28h]
    L_0044c71f:
        mov dword ptr [eax+20h],ecx
    L_0044c722:
        mov ecx,dword ptr [esp+2Ch]
    L_0044c726:
        mov dword ptr [eax+24h],edx
    L_0044c729:
        mov edx,dword ptr [esp+30h]
    L_0044c72d:
        mov dword ptr [eax+28h],ecx
    L_0044c730:
        mov ecx,dword ptr [esp+34h]
    L_0044c734:
        mov dword ptr [eax+2Ch],edx
    L_0044c737:
        mov edx,dword ptr [esp+38h]
    L_0044c73b:
        mov dword ptr [eax+30h],ecx
    L_0044c73e:
        mov ecx,dword ptr [esp+3Ch]
    L_0044c742:
        mov dword ptr [eax+34h],edx
    L_0044c745:
        mov edx,dword ptr [esp+40h]
    L_0044c749:
        mov dword ptr [eax+38h],ecx
    L_0044c74c:
        mov dword ptr [eax+3Ch],edx
    L_0044c74f:
        ret 40h
    }
}

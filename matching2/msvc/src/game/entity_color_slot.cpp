#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442050..0x0044211F: FUN_00442050
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00442050_00442050() {
    __asm {
    L_00442050:
        sub esp,0Ch
    L_00442053:
        push ebx
    L_00442054:
        push ebp
    L_00442055:
        push esi
    L_00442056:
        mov esi,dword ptr [esp+1Ch]
    L_0044205a:
        mov dword ptr [eax+200h],esi
    L_00442060:
        xor esi,esi
    L_00442062:
        push edi
    L_00442063:
        xor edi,edi
    L_00442065:
        lea ebp,[eax+1D4h]
    L_0044206b:
        mov dword ptr [ebp],esi
    L_0044206e:
        mov dword ptr [ebp+4],edi
    L_00442071:
        xor ebx,ebx
    L_00442073:
        mov dword ptr [ebp+8],ebx
    L_00442076:
        lea ebp,[eax+1E0h]
    L_0044207c:
        mov dword ptr [ebp],esi
    L_0044207f:
        movzx esi,byte ptr [esp+24h]
    L_00442084:
        mov dword ptr [ebp+4],edi
    L_00442087:
        mov dword ptr [ebp+8],ebx
    L_0044208a:
        mov dword ptr [eax+204h],esi
    L_00442090:
        movzx ebx,byte ptr [ecx+2]
    L_00442094:
        movzx ebp,byte ptr [ecx+1]
    L_00442098:
        movzx ecx,byte ptr [ecx]
    L_0044209b:
        movzx esi,byte ptr [edx+2]
    L_0044209f:
        movzx edi,byte ptr [edx+1]
    L_004420a3:
        movzx edx,byte ptr [edx]
    L_004420a6:
        mov dword ptr [esp+10h],ecx
    L_004420aa:
        lea ecx,[eax+1BCh]
    L_004420b0:
        mov dword ptr [ecx],edx
    L_004420b2:
        mov dword ptr [ecx+4],edi
    L_004420b5:
        mov dword ptr [ecx+8],esi
    L_004420b8:
        mov ecx,dword ptr [esp+10h]
    L_004420bc:
        lea edx,[eax+1C8h]
    L_004420c2:
        mov dword ptr [edx],ecx
    L_004420c4:
        mov dword ptr [edx+4],ebp
    L_004420c7:
        pop edi
    L_004420c8:
        mov dword ptr [edx+8],ebx
    L_004420cb:
        mov ecx,dword ptr [eax+1FCh]
    L_004420d1:
        pop esi
    L_004420d2:
        pop ebp
    L_004420d3:
        xor edx,edx
    L_004420d5:
        test cl,1
    L_004420d8:
        pop ebx
    L_004420d9:
        jne short L_00442104
    L_004420db:
        or ecx,1
    L_004420de:
        mov dword ptr [eax+1F0h],edx
    L_004420e4:
        mov dword ptr [eax+1ECh],0FFF0BDC1h
    L_004420ee:
        mov dword ptr [eax+1F4h],edx
    L_004420f4:
        mov dword ptr [eax+1F8h],476F78h
    L_004420fe:
        mov dword ptr [eax+1FCh],ecx
    L_00442104:
        mov dword ptr [eax+1F0h],edx
    L_0044210a:
        mov dword ptr [eax+1F4h],edx
    L_00442110:
        mov dword ptr [eax+1ECh],0FFFFFFFFh
    L_0044211a:
        add esp,0Ch
    L_0044211d:
        ret 8
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004043D0..0x0040440A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004043d0() {
    __asm {
    L_004043d0:
        mov dword ptr [edx+1EECh],1
    L_004043da:
        push esi
    L_004043db:
        push edi
    L_004043dc:
        mov edi,dword ptr [ecx]
    L_004043de:
        lea esi,[edx+1EF0h]
    L_004043e4:
        mov dword ptr [esi],edi
    L_004043e6:
        mov edi,dword ptr [ecx+4]
    L_004043e9:
        mov dword ptr [esi+4],edi
    L_004043ec:
        mov ecx,dword ptr [ecx+8]
    L_004043ef:
        mov dword ptr [esi+8],ecx
    L_004043f2:
        mov ecx,dword ptr [eax]
    L_004043f4:
        add edx,1EFCh
    L_004043fa:
        mov dword ptr [edx],ecx
    L_004043fc:
        mov ecx,dword ptr [eax+4]
    L_004043ff:
        mov dword ptr [edx+4],ecx
    L_00404402:
        mov eax,dword ptr [eax+8]
    L_00404405:
        pop edi
    L_00404406:
        mov dword ptr [edx+8],eax
    L_00404409:
        pop esi
    L_0040440a:
        ret
    }
}

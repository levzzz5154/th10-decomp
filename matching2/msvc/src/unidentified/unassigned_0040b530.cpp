#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B530..0x0040B559: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b530() {
    __asm {
    L_0040b530:
        xor ecx,ecx
    L_0040b532:
        mov edx,eax
    L_0040b534:
        mov dword ptr [edx],ecx
    L_0040b536:
        mov dword ptr [edx+4],ecx
    L_0040b539:
        mov dword ptr [edx+8],ecx
    L_0040b53c:
        mov dword ptr [edx+0Ch],ecx
    L_0040b53f:
        mov dword ptr [edx+10h],ecx
    L_0040b542:
        mov dword ptr [edx+14h],ecx
    L_0040b545:
        mov dword ptr [edx+18h],ecx
    L_0040b548:
        mov dword ptr [edx+1Ch],ecx
    L_0040b54b:
        mov dword ptr [edx+20h],ecx
    L_0040b54e:
        mov dword ptr [edx+24h],ecx
    L_0040b551:
        or dword ptr [eax],2
    L_0040b554:
        mov dword ptr [data_00477700],eax
    L_0040b559:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AAE0..0x0042AB15: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042aae0() {
    __asm {
    L_0042aae0:
        push edi
    L_0042aae1:
        xor eax,eax
    L_0042aae3:
        mov ecx,18A1h
    L_0042aae8:
        mov edi,edx
    L_0042aaea:
        rep stosd
    L_0042aaec:
        lea eax,[edx+5464h]
    L_0042aaf2:
        mov dword ptr [edx+6274h],eax
    L_0042aaf8:
        xor eax,eax
    L_0042aafa:
        mov dword ptr [edx+5460h],edx
    L_0042ab00:
        mov dword ptr [edx+627Ch],eax
    L_0042ab06:
        mov dword ptr [edx+6280h],eax
    L_0042ab0c:
        mov dword ptr [edx+6278h],edx
    L_0042ab12:
        mov eax,edx
    L_0042ab14:
        pop edi
    L_0042ab15:
        ret
    }
}

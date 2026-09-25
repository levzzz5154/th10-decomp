#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460817..0x00460844: ___shl_12
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_shl_12_00460817() {
    __asm {
    L_00460817:
        mov eax,dword ptr [esp+4]
    L_0046081b:
        push esi
    L_0046081c:
        mov esi,dword ptr [eax]
    L_0046081e:
        mov ecx,esi
    L_00460820:
        add esi,esi
    L_00460822:
        push edi
    L_00460823:
        mov edi,dword ptr [eax+4]
    L_00460826:
        shr ecx,1Fh
    L_00460829:
        mov dword ptr [eax],esi
    L_0046082b:
        lea esi,[edi+edi]
    L_0046082e:
        or esi,ecx
    L_00460830:
        mov ecx,dword ptr [eax+8]
    L_00460833:
        mov edx,edi
    L_00460835:
        shr edx,1Fh
    L_00460838:
        shl ecx,1
    L_0046083a:
        or ecx,edx
    L_0046083c:
        pop edi
    L_0046083d:
        mov dword ptr [eax+4],esi
    L_00460840:
        mov dword ptr [eax+8],ecx
    L_00460843:
        pop esi
    L_00460844:
        ret
    }
}

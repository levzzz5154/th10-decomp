#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405C80..0x00405C9B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405c80() {
    __asm {
    L_00405c80:
        mov edx,ecx
    L_00405c82:
        push edi
    L_00405c83:
        xor eax,eax
    L_00405c85:
        mov ecx,84h
    L_00405c8a:
        mov edi,edx
    L_00405c8c:
        rep stosd
    L_00405c8e:
        mov dword ptr [edx+204h],0FFFFFFFFh
    L_00405c98:
        mov eax,edx
    L_00405c9a:
        pop edi
    L_00405c9b:
        ret
    }
}

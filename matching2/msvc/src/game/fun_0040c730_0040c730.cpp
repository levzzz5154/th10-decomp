#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.

// 0x0040C730..0x0040C776: FUN_0040c730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c730_0040c730() {
    __asm {
    L_0040c730:
        push esi
    L_0040c731:
        mov esi,dword ptr [eax+1028h]
    L_0040c737:
        xor edx,edx
    L_0040c739:
        lea ecx,[eax+8]
    L_0040c73c:
        and esi,0FFFFFFFEh
    L_0040c73f:
        mov dword ptr [eax+1028h],esi
    L_0040c745:
        mov dword ptr [ecx],edx
    L_0040c747:
        mov dword ptr [eax+0Ch],edx
    L_0040c74a:
        mov dword ptr [eax+101Ch],eax
    L_0040c750:
        mov dword ptr [eax+1018h],0FFFFFFFFh
    L_0040c75a:
        mov dword ptr [eax+1020h],edx
    L_0040c760:
        mov dword ptr [eax+4],ecx
    L_0040c763:
        mov dword ptr [eax+1030h],ecx
    L_0040c769:
        mov dword ptr [eax+1034h],edx
    L_0040c76f:
        mov dword ptr [eax+1038h],edx
    L_0040c775:
        pop esi
    L_0040c776:
        ret
    }
}

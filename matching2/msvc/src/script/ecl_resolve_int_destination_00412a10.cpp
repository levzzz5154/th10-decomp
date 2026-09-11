#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040E770..0x00411D2E: FUN_0040e770
// Naked body preserves the retail register/stack ABI.

// 0x00412A10..0x00412A5A: ?ECL_ResolveIntDestination@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveIntDestination_00412a10() {
    __asm {
    L_00412a10:
        mov edx,dword ptr [eax+14D8h]
    L_00412a16:
        mov eax,dword ptr [edx+4]
    L_00412a19:
        mov edx,dword ptr [eax+4]
    L_00412a1c:
        push esi
    L_00412a1d:
        movzx esi,word ptr [edx+8]
    L_00412a21:
        push edi
    L_00412a22:
        mov edi,1
    L_00412a27:
        shl edi,cl
    L_00412a29:
        test esi,edi
    L_00412a2b:
        je short L_00412a56
    L_00412a2d:
        mov edx,dword ptr [edx+ecx*4+10h]
    L_00412a31:
        test edx,edx
    L_00412a33:
        jl short L_00412a45
    L_00412a35:
        lea ecx,[eax+8]
    L_00412a38:
        mov eax,dword ptr [ecx+1004h]
    L_00412a3e:
        add eax,edx
    L_00412a40:
        pop edi
    L_00412a41:
        add eax,ecx
    L_00412a43:
        pop esi
    L_00412a44:
        ret
    L_00412a45:
        mov eax,dword ptr [eax+1014h]
    L_00412a4b:
        mov esi,dword ptr [eax]
    L_00412a4d:
        push edx
    L_00412a4e:
        mov ecx,eax
    L_00412a50:
        call dword ptr [esi+8]
    L_00412a53:
        pop edi
    L_00412a54:
        pop esi
    L_00412a55:
        ret
    L_00412a56:
        pop edi
    L_00412a57:
        xor eax,eax
    L_00412a59:
        pop esi
    L_00412a5a:
        ret
    }
}

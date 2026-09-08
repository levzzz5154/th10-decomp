#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441EC0..0x00441EED: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441ec0() {
    __asm {
    L_00441ec0:
        mov eax,dword ptr [eax+394h]
    L_00441ec6:
        test eax,eax
    L_00441ec8:
        je short L_00441edb
    L_00441eca:
        mov eax,dword ptr [eax]
    L_00441ecc:
        test eax,eax
    L_00441ece:
        jl short L_00441edb
    L_00441ed0:
        mov eax,dword ptr [ecx+eax*4+3AD06Ch]
    L_00441ed7:
        test eax,eax
    L_00441ed9:
        jne short L_00441ede
    L_00441edb:
        xor eax,eax
    L_00441edd:
        ret
    L_00441ede:
        mov ecx,dword ptr [eax+120h]
    L_00441ee4:
        xor edx,edx
    L_00441ee6:
        test ecx,ecx
    L_00441ee8:
        setne dl
    L_00441eeb:
        mov eax,edx
    L_00441eed:
        ret
    }
}

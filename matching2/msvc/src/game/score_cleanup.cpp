#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C850..0x0041C859: FUN_0041c850
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c850_0041c850() {
    __asm {
    L_0041c850:
        mov ecx,dword ptr [eax+18h]
    L_0041c853:
        test ecx,ecx
    L_0041c855:
        TH10_REL8(0x74, 0x0041c855, VA_asm_target_0041c876)
    L_0041c857:
        push esi
    L_0041c858:
        TH10_REL8(0xeb, 0x0041c858, VA_asm_FUN_0041c850_part_0041c860)
    }
}

// 0x0041C860..0x0041C87B: FUN_0041c850
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c850_part_0041c860() {
    __asm {
    L_0041c860:
        cmp dword ptr [ecx+0Ch],1
    L_0041c864:
        mov esi,dword ptr [ecx+8]
    L_0041c867:
        je short L_0041c86f
    L_0041c869:
        mov edx,dword ptr [ecx]
    L_0041c86b:
        push ebx
    L_0041c86c:
        call dword ptr [edx+14h]
    L_0041c86f:
        test esi,esi
    L_0041c871:
        mov ecx,esi
    L_0041c873:
        jne short L_0041c860
    L_0041c875:
        pop esi
    L_0041c876:
        mov eax,1
    L_0041c87b:
        ret
    }
}

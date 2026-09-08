#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046069E..0x004606C4: __ltoa
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ltoa_0046069e() {
    __asm {
    L_0046069e:
        push ebp
    L_0046069f:
        mov ebp,esp
    L_004606a1:
        xor eax,eax
    L_004606a3:
        cmp dword ptr [ebp+10h],0Ah
    L_004606a7:
        jne short L_004606af
    L_004606a9:
        cmp dword ptr [ebp+8],eax
    L_004606ac:
        jge short L_004606af
    L_004606ae:
        inc eax
    L_004606af:
        mov ecx,dword ptr [ebp+0Ch]
    L_004606b2:
        push eax
    L_004606b3:
        push dword ptr [ebp+10h]
    L_004606b6:
        mov eax,dword ptr [ebp+8]
    L_004606b9:
        call asm_xtoa_00460636
    L_004606be:
        mov eax,dword ptr [ebp+0Ch]
    L_004606c1:
        pop ecx
    L_004606c2:
        pop ecx
    L_004606c3:
        pop ebp
    L_004606c4:
        ret
    }
}

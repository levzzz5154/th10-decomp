#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460674..0x0046069D: __itoa
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_itoa_00460674() {
    __asm {
    L_00460674:
        push ebp
    L_00460675:
        mov ebp,esp
    L_00460677:
        cmp dword ptr [ebp+10h],0Ah
    L_0046067b:
        mov eax,dword ptr [ebp+8]
    L_0046067e:
        jne short L_0046068a
    L_00460680:
        test eax,eax
    L_00460682:
        jge short L_0046068a
    L_00460684:
        push 1
    L_00460686:
        push 0Ah
    L_00460688:
        jmp short L_0046068f
    L_0046068a:
        push 0
    L_0046068c:
        push dword ptr [ebp+10h]
    L_0046068f:
        mov ecx,dword ptr [ebp+0Ch]
    L_00460692:
        call asm_xtoa_00460636
    L_00460697:
        mov eax,dword ptr [ebp+0Ch]
    L_0046069a:
        pop ecx
    L_0046069b:
        pop ecx
    L_0046069c:
        pop ebp
    L_0046069d:
        ret
    }
}

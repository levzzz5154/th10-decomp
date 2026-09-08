#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046074C..0x0046077C: __i64toa
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_i64toa_0046074c() {
    __asm {
    L_0046074c:
        push ebp
    L_0046074d:
        mov ebp,esp
    L_0046074f:
        xor eax,eax
    L_00460751:
        cmp dword ptr [ebp+14h],0Ah
    L_00460755:
        jne short L_00460766
    L_00460757:
        cmp dword ptr [ebp+0Ch],eax
    L_0046075a:
        jg short L_00460766
    L_0046075c:
        jl short L_00460763
    L_0046075e:
        cmp dword ptr [ebp+8],eax
    L_00460761:
        jae short L_00460766
    L_00460763:
        xor eax,eax
    L_00460765:
        inc eax
    L_00460766:
        push eax
    L_00460767:
        push dword ptr [ebp+14h]
    L_0046076a:
        mov eax,dword ptr [ebp+10h]
    L_0046076d:
        push dword ptr [ebp+0Ch]
    L_00460770:
        push dword ptr [ebp+8]
    L_00460773:
        call asm_FID_conflict_x64toa_20_004606df
    L_00460778:
        mov eax,dword ptr [ebp+10h]
    L_0046077b:
        pop ebp
    L_0046077c:
        ret
    }
}

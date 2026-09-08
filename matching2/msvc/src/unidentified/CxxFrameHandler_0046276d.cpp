#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046276D..0x004627A2: ___CxxFrameHandler
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CxxFrameHandler_0046276d() {
    __asm {
    L_0046276d:
        push ebp
    L_0046276e:
        mov ebp,esp
    L_00462770:
        sub esp,4
    L_00462773:
        push ebx
    L_00462774:
        push esi
    L_00462775:
        push edi
    L_00462776:
        cld
    L_00462777:
        mov dword ptr [ebp-4],eax
    L_0046277a:
        xor eax,eax
    L_0046277c:
        push eax
    L_0046277d:
        push eax
    L_0046277e:
        push eax
    L_0046277f:
        push dword ptr [ebp-4]
    L_00462782:
        push dword ptr [ebp+14h]
    L_00462785:
        push dword ptr [ebp+10h]
    L_00462788:
        push dword ptr [ebp+0Ch]
    L_0046278b:
        push dword ptr [ebp+8]
    L_0046278e:
        call asm_InternalCxxFrameHandler_00463963
    L_00462793:
        add esp,20h
    L_00462796:
        mov dword ptr [ebp-4],eax
    L_00462799:
        pop edi
    L_0046279a:
        pop esi
    L_0046279b:
        pop ebx
    L_0046279c:
        mov eax,dword ptr [ebp-4]
    L_0046279f:
        mov esp,ebp
    L_004627a1:
        pop ebp
    L_004627a2:
        ret
    }
}

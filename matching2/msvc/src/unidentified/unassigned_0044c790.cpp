#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C790..0x0044C7D4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c790() {
    __asm {
    L_0044c790:
        mov eax,dword ptr [esi]
    L_0044c792:
        test eax,eax
    L_0044c794:
        je short L_0044c7a2
    L_0044c796:
        mov ecx,dword ptr [eax]
    L_0044c798:
        push eax
    L_0044c799:
        call dword ptr [ecx+8]
    L_0044c79c:
        mov dword ptr [esi],0
    L_0044c7a2:
        push 0
    L_0044c7a4:
        push esi
    L_0044c7a5:
        push 0
    L_0044c7a7:
        call asm_Ordinal_11_00452170
    L_0044c7ac:
        test eax,eax
    L_0044c7ae:
        jl short L_0044c7d2
    L_0044c7b0:
        mov ecx,dword ptr [esp+8]
    L_0044c7b4:
        mov eax,dword ptr [esi]
    L_0044c7b6:
        mov edx,dword ptr [eax]
    L_0044c7b8:
        push ecx
    L_0044c7b9:
        mov ecx,dword ptr [esp+8]
    L_0044c7bd:
        push ecx
    L_0044c7be:
        push eax
    L_0044c7bf:
        call dword ptr [edx+18h]
    L_0044c7c2:
        test eax,eax
    L_0044c7c4:
        jl short L_0044c7d2
    L_0044c7c6:
        mov ecx,dword ptr [esp+0Ch]
    L_0044c7ca:
        push esi
    L_0044c7cb:
        call asm_Input_SetJoystickPropertyRetail_0044c7e0
    L_0044c7d0:
        xor eax,eax
    L_0044c7d2:
        ret 0Ch
    }
}

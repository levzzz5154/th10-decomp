#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453977..0x004539A1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00453977() {
    __asm {
    L_00453977:
        mov eax,dword ptr [ebp-14h]
    L_0045397a:
        mov ecx,dword ptr [eax]
    L_0045397c:
        mov ecx,dword ptr [ecx]
    L_0045397e:
        mov dword ptr [ebp-24h],ecx
    L_00453981:
        push eax
    L_00453982:
        push ecx
    L_00453983:
        call asm_XcptFilter_004577ce
    L_00453988:
        pop ecx
    L_00453989:
        pop ecx
    L_0045398a:
        ret
    L_0045398b:
        mov esp,dword ptr [ebp-18h]
    L_0045398e:
        mov edi,dword ptr [ebp-24h]
    L_00453991:
        cmp dword ptr [ebp-1Ch],0
    L_00453995:
        jne short L_0045399d
    L_00453997:
        push edi
    L_00453998:
        call asm_exit_004576fd
    L_0045399d:
        call asm_unassigned_0045771d
    }
}

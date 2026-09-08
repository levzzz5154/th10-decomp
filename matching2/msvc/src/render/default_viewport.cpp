#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C1A0..0x0043C225: FUN_0043c1a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c1a0_0043c1a0() {
    __asm {
    L_0043c1a0:
        sub esp,10h
    L_0043c1a3:
        push ebx
    L_0043c1a4:
        push esi
    L_0043c1a5:
        mov esi,dword ptr [data_00491c10]
    L_0043c1ab:
        push edi
    L_0043c1ac:
        mov edi,ecx
    L_0043c1ae:
        mov dword ptr [esp+0Ch],0
    L_0043c1b6:
        mov dword ptr [esp+10h],0
    L_0043c1be:
        mov dword ptr [esp+14h],44200000h
    L_0043c1c6:
        mov dword ptr [esp+18h],43F00000h
    L_0043c1ce:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0043c1d3:
        xor eax,eax
    L_0043c1d5:
        mov dword ptr [data_00491cf4],eax
    L_0043c1da:
        mov dword ptr [data_00491cf8],eax
    L_0043c1df:
        mov eax,dword ptr [data_00491c30]
    L_0043c1e4:
        push 491CF4h
    L_0043c1e9:
        mov dword ptr [data_00491cfc],280h
    L_0043c1f3:
        mov dword ptr [data_00491d00],1E0h
    L_0043c1fd:
        mov ecx,dword ptr [eax]
    L_0043c1ff:
        push eax
    L_0043c200:
        call dword ptr [ecx+0BCh]
    L_0043c206:
        mov ebx,dword ptr [edi+18h]
    L_0043c209:
        mov eax,dword ptr [edi+20h]
    L_0043c20c:
        shl ebx,18h
    L_0043c20f:
        or ebx,eax
    L_0043c211:
        lea edi,[esp+0Ch]
    L_0043c215:
        call asm_FUN_0043bda0_0043bda0
    L_0043c21a:
        pop edi
    L_0043c21b:
        pop esi
    L_0043c21c:
        mov eax,1
    L_0043c221:
        pop ebx
    L_0043c222:
        add esp,10h
    L_0043c225:
        ret
    }
}

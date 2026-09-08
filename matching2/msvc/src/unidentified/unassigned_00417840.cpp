#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417840..0x00417860: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417840() {
    __asm {
    L_00417840:
        mov eax,dword ptr [esi+20h]
    L_00417843:
        and eax,0FFFFFFFEh
    L_00417846:
        push edi
    L_00417847:
        lea edx,[esi+24h]
    L_0041784a:
        mov dword ptr [esi+20h],eax
    L_0041784d:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00417852:
        xor eax,eax
    L_00417854:
        mov ecx,18h
    L_00417859:
        mov edi,esi
    L_0041785b:
        rep stosd
    L_0041785d:
        mov eax,esi
    L_0041785f:
        pop edi
    L_00417860:
        ret
    }
}

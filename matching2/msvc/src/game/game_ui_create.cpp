#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004180E0..0x0041814A: GameUi_CreateAndPublish
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameUi_CreateAndPublish_004180e0() {
    __asm {
    L_004180e0:
        push esi
    L_004180e1:
        push edi
    L_004180e2:
        push 60h
    L_004180e4:
        call asm_operator_new_00452493
    L_004180e9:
        mov esi,eax
    L_004180eb:
        add esp,4
    L_004180ee:
        test esi,esi
    L_004180f0:
        je short L_00418110
    L_004180f2:
        mov eax,dword ptr [esi+20h]
    L_004180f5:
        and eax,0FFFFFFFEh
    L_004180f8:
        lea edx,[esi+24h]
    L_004180fb:
        mov dword ptr [esi+20h],eax
    L_004180fe:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00418103:
        mov ecx,18h
    L_00418108:
        xor eax,eax
    L_0041810a:
        mov edi,esi
    L_0041810c:
        rep stosd
    L_0041810e:
        jmp short L_00418112
    L_00418110:
        xor esi,esi
    L_00418112:
        mov eax,dword ptr [data_00491c30]
    L_00418117:
        mov ecx,dword ptr [eax]
    L_00418119:
        push eax
    L_0041811a:
        call dword ptr [ecx+14h]
    L_0041811d:
        mov edx,dword ptr [esp+0Ch]
    L_00418121:
        mov dword ptr [esi+5Ch],edx
    L_00418124:
        mov edx,dword ptr [esi+58h]
    L_00418127:
        push 0
    L_00418129:
        or edx,4
    L_0041812c:
        push 417C70h
    L_00418131:
        mov edi,491C28h
    L_00418136:
        mov dword ptr [data_00477810],esi
    L_0041813c:
        mov dword ptr [esi+58h],edx
    L_0041813f:
        call asm_FUN_00420ea0_00420ea0
    L_00418144:
        pop edi
    L_00418145:
        mov eax,esi
    L_00418147:
        pop esi
    L_00418148:
        ret 4
    }
}

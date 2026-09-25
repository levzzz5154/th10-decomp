#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// 0x0043C8B0..0x0043C901: AsciiManager_CreateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AsciiManager_CreateRetail_0043c8b0() {
    __asm {
    L_0043c8b0:
        push esi
    L_0043c8b1:
        push 44h
    L_0043c8b3:
        call asm_operator_new_00452493
    L_0043c8b8:
        mov esi,eax
    L_0043c8ba:
        add esp,4
    L_0043c8bd:
        xor eax,eax
    L_0043c8bf:
        test esi,esi
    L_0043c8c1:
        je short L_0043c8fe
    L_0043c8c3:
        mov ecx,dword ptr [esi+40h]
    L_0043c8c6:
        mov edx,dword ptr [esp+10h]
    L_0043c8ca:
        push edi
    L_0043c8cb:
        and ecx,0FFFFFFFEh
    L_0043c8ce:
        mov dword ptr [esi+40h],ecx
    L_0043c8d1:
        mov ecx,11h
    L_0043c8d6:
        mov edi,esi
    L_0043c8d8:
        rep stosd
    L_0043c8da:
        mov eax,dword ptr [esi]
    L_0043c8dc:
        mov ecx,dword ptr [esp+18h]
    L_0043c8e0:
        or eax,2
    L_0043c8e3:
        pop edi
    L_0043c8e4:
        mov dword ptr [esi],eax
    L_0043c8e6:
        mov eax,dword ptr [esp+18h]
    L_0043c8ea:
        push eax
    L_0043c8eb:
        mov eax,dword ptr [esp+10h]
    L_0043c8ef:
        push ecx
    L_0043c8f0:
        mov ecx,dword ptr [esp+10h]
    L_0043c8f4:
        push edx
    L_0043c8f5:
        push eax
    L_0043c8f6:
        push ecx
    L_0043c8f7:
        call asm_FUN_0043c970_0043c970
    L_0043c8fc:
        mov eax,esi
    L_0043c8fe:
        pop esi
    L_0043c8ff:
        ret 14h
    }
}

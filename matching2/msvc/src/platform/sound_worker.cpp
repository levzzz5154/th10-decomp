#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043CC40..0x0043CCEE: Platform_StopSoundWorkersRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_StopSoundWorkersRetail_0043cc40() {
    __asm {
    L_0043cc40:
        mov eax,dword ptr [esi+5218h]
    L_0043cc46:
        test eax,eax
    L_0043cc48:
        je asm_target_0043ccec
    L_0043cc4e:
        mov ecx,dword ptr [esi+5224h]
    L_0043cc54:
        test ecx,ecx
    L_0043cc56:
        jne short L_0043cc62
    L_0043cc58:
        mov dword ptr [esi+5224h],1
    L_0043cc62:
        push ebx
    L_0043cc63:
        push edi
    L_0043cc64:
        mov edi,dword ptr [data_0046611c]
    L_0043cc6a:
        push 64h
    L_0043cc6c:
        push eax
    L_0043cc6d:
        call edi
    L_0043cc6f:
        cmp eax,102h
    L_0043cc74:
        mov ebx,dword ptr [data_004660ac]
    L_0043cc7a:
        jne short L_0043cc96
    L_0043cc7c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0043cc80:
        push 1
    L_0043cc82:
        call ebx
    L_0043cc84:
        mov eax,dword ptr [esi+5218h]
    L_0043cc8a:
        push 64h
    L_0043cc8c:
        push eax
    L_0043cc8d:
        call edi
    L_0043cc8f:
        cmp eax,102h
    L_0043cc94:
        je short L_0043cc80
    L_0043cc96:
        mov ecx,dword ptr [esi+521Ch]
    L_0043cc9c:
        push 64h
    L_0043cc9e:
        push ecx
    L_0043cc9f:
        call edi
    L_0043cca1:
        cmp eax,102h
    L_0043cca6:
        jne short L_0043ccbe
    L_0043cca8:
        push 1
    L_0043ccaa:
        call ebx
    L_0043ccac:
        mov edx,dword ptr [esi+521Ch]
    L_0043ccb2:
        push 64h
    L_0043ccb4:
        push edx
    L_0043ccb5:
        call edi
    L_0043ccb7:
        cmp eax,102h
    L_0043ccbc:
        je short L_0043cca8
    L_0043ccbe:
        mov eax,dword ptr [esi+5218h]
    L_0043ccc4:
        mov edi,dword ptr [data_004660cc]
    L_0043ccca:
        push eax
    L_0043cccb:
        call edi
    L_0043cccd:
        mov ecx,dword ptr [esi+521Ch]
    L_0043ccd3:
        push ecx
    L_0043ccd4:
        call edi
    L_0043ccd6:
        pop edi
    L_0043ccd7:
        mov dword ptr [esi+5218h],0
    L_0043cce1:
        mov dword ptr [esi+521Ch],0
    L_0043cceb:
        pop ebx
    L_0043ccec:
        xor eax,eax
    L_0043ccee:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// 0x0043C970..0x0043CAD4: FUN_0043c970
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c970_0043c970() {
    __asm {
    L_0043c970:
        push ebp
    L_0043c971:
        mov ebp,dword ptr [esp+8]
    L_0043c975:
        cmp ebp,8
    L_0043c978:
        ja asm_target_0043ca78
    L_0043c97e:
        push edi
    L_0043c97f:
        jmp dword ptr [ebp*4+43CAD8h]
    L_0043c986:
        mov eax,43BD40h
    L_0043c98b:
        push esi
    L_0043c98c:
        mov edi,0Eh
    L_0043c991:
        call asm_Scheduler_CreateAndRegister_0044a000
    L_0043c996:
        mov dword ptr [esi+8],eax
    L_0043c999:
        mov eax,43C1A0h
    L_0043c99e:
        push esi
    L_0043c99f:
        mov edi,ebx
    L_0043c9a1:
        call asm_Scheduler_CreateAndRegisterSecondary_0044a030
    L_0043c9a6:
        mov dword ptr [esi+0Ch],eax
    L_0043c9a9:
        jmp asm_target_0043ca77
    L_0043c9ae:
        mov eax,43C550h
    L_0043c9b3:
        jmp asm_target_0043ca69
    L_0043c9b8:
        mov eax,43C230h
    L_0043c9bd:
        push esi
    L_0043c9be:
        mov edi,0Eh
    L_0043c9c3:
        call asm_Scheduler_CreateAndRegister_0044a000
    L_0043c9c8:
        mov dword ptr [esi+8],eax
    L_0043c9cb:
        push esi
    L_0043c9cc:
        mov eax,43C2C0h
    L_0043c9d1:
        mov edi,ebx
    L_0043c9d3:
        call asm_Scheduler_CreateAndRegisterSecondary_0044a030
    L_0043c9d8:
        mov dword ptr [esi+0Ch],eax
    L_0043c9db:
        jmp asm_target_0043ca77
    L_0043c9e0:
        mov dword ptr [esi+18h],0FFh
    L_0043c9e7:
        mov eax,43BD40h
    L_0043c9ec:
        jmp short L_0043c9bd
    L_0043c9ee:
        mov eax,43C230h
    L_0043c9f3:
        jmp short L_0043c98b
    L_0043c9f5:
        push esi
    L_0043c9f6:
        mov eax,43C460h
    L_0043c9fb:
        mov edi,0Eh
    L_0043ca00:
        call asm_Scheduler_CreateAndRegister_0044a000
    L_0043ca05:
        mov dword ptr [esi+8],eax
    L_0043ca08:
        mov eax,43C500h
    L_0043ca0d:
        push esi
    L_0043ca0e:
        mov edi,ebx
    L_0043ca10:
        call asm_Scheduler_CreateAndRegisterSecondary_0044a030
    L_0043ca15:
        mov dword ptr [esi+0Ch],eax
    L_0043ca18:
        jmp short L_0043ca77
    L_0043ca1a:
        push esi
    L_0043ca1b:
        mov eax,43C310h
    L_0043ca20:
        mov edi,0Eh
    L_0043ca25:
        call asm_Scheduler_CreateAndRegister_0044a000
    L_0043ca2a:
        mov dword ptr [esi+8],eax
    L_0043ca2d:
        mov eax,43C3C0h
    L_0043ca32:
        push esi
    L_0043ca33:
        mov edi,ebx
    L_0043ca35:
        call asm_Scheduler_CreateAndRegisterSecondary_0044a030
    L_0043ca3a:
        mov dword ptr [esi+0Ch],eax
    L_0043ca3d:
        jmp short L_0043ca77
    L_0043ca3f:
        push esi
    L_0043ca40:
        mov eax,43C310h
    L_0043ca45:
        mov edi,0Eh
    L_0043ca4a:
        call asm_Scheduler_CreateAndRegister_0044a000
    L_0043ca4f:
        mov dword ptr [esi+8],eax
    L_0043ca52:
        mov eax,43C410h
    L_0043ca57:
        push esi
    L_0043ca58:
        mov edi,ebx
    L_0043ca5a:
        call asm_Scheduler_CreateAndRegisterSecondary_0044a030
    L_0043ca5f:
        mov dword ptr [esi+0Ch],eax
    L_0043ca62:
        jmp short L_0043ca77
    L_0043ca64:
        mov eax,43C710h
    L_0043ca69:
        mov edi,0Eh
    L_0043ca6e:
        push esi
    L_0043ca6f:
        call asm_Scheduler_CreateAndRegister_0044a000
    L_0043ca74:
        mov dword ptr [esi+8],eax
    L_0043ca77:
        pop edi
    L_0043ca78:
        mov eax,dword ptr [esi+8]
    L_0043ca7b:
        mov dword ptr [eax+10h],43C870h
    L_0043ca82:
        mov eax,dword ptr [esi+40h]
    L_0043ca85:
        xor ecx,ecx
    L_0043ca87:
        test al,1
    L_0043ca89:
        jne short L_0043caa5
    L_0043ca8b:
        or eax,1
    L_0043ca8e:
        mov dword ptr [esi+34h],ecx
    L_0043ca91:
        mov dword ptr [esi+30h],0FFF0BDC1h
    L_0043ca98:
        mov dword ptr [esi+38h],ecx
    L_0043ca9b:
        mov dword ptr [esi+3Ch],476F78h
    L_0043caa2:
        mov dword ptr [esi+40h],eax
    L_0043caa5:
        mov edx,dword ptr [esp+10h]
    L_0043caa9:
        mov eax,dword ptr [esp+14h]
    L_0043caad:
        mov dword ptr [esi+34h],ecx
    L_0043cab0:
        mov dword ptr [esi+38h],ecx
    L_0043cab3:
        mov ecx,dword ptr [esp+0Ch]
    L_0043cab7:
        mov dword ptr [esi+30h],0FFFFFFFFh
    L_0043cabe:
        mov dword ptr [esi+1Ch],ecx
    L_0043cac1:
        mov ecx,dword ptr [esp+18h]
    L_0043cac5:
        mov dword ptr [esi+10h],ebp
    L_0043cac8:
        mov dword ptr [esi+20h],edx
    L_0043cacb:
        mov dword ptr [esi+24h],eax
    L_0043cace:
        mov dword ptr [esi+28h],ecx
    L_0043cad1:
        pop ebp
    L_0043cad2:
        ret 14h
    }
}

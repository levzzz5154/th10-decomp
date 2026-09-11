#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404530..0x004045A6: FUN_00404530
// Naked body preserves the retail register/stack ABI.

// 0x00405750..0x0040582E: UpdatePlayer
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_UpdatePlayer_00405750() {
    __asm {
    L_00405750:
        mov eax,dword ptr [edi+28h]
    L_00405753:
        sub esp,0Ch
    L_00405756:
        push esi
    L_00405757:
        xor esi,esi
    L_00405759:
        cmp eax,esi
    L_0040575b:
        je asm_target_00405825
    L_00405761:
        dec eax
    L_00405762:
        push ebx
    L_00405763:
        push ebp
    L_00405764:
        jne asm_target_0040581b
    L_0040576a:
        mov eax,dword ptr [edi+2Ch]
    L_0040576d:
        mov ebp,dword ptr [data_00491c10]
    L_00405773:
        push eax
    L_00405774:
        mov edx,ebp
    L_00405776:
        call asm_AnimationManager_Find_004491c0
    L_0040577b:
        mov ebx,eax
    L_0040577d:
        cmp ebx,esi
    L_0040577f:
        jne short L_00405793
    L_00405781:
        pop ebp
    L_00405782:
        mov dword ptr [edi+2Ch],esi
    L_00405785:
        pop ebx
    L_00405786:
        mov dword ptr [edi+28h],esi
    L_00405789:
        mov eax,1
    L_0040578e:
        pop esi
    L_0040578f:
        add esp,0Ch
    L_00405792:
        ret
    L_00405793:
        mov eax,dword ptr [data_004776f4]
    L_00405798:
        test byte ptr [eax+378Ch],1
    L_0040579f:
        je short L_004057c1
    L_004057a1:
        mov eax,dword ptr [eax+3788h]
    L_004057a7:
        cmp eax,5Dh
    L_004057aa:
        jl short L_004057b1
    L_004057ac:
        cmp eax,60h
    L_004057af:
        jle short L_004057b6
    L_004057b1:
        cmp eax,6Dh
    L_004057b4:
        jne short L_004057c1
    L_004057b6:
        fld dword ptr [edi+34h]
    L_004057b9:
        fsub dword ptr [data_00470b0c]
    L_004057bf:
        jmp short L_004057db
    L_004057c1:
        mov eax,dword ptr [data_00474c68]
    L_004057c6:
        fld dword ptr [edi+34h]
    L_004057c9:
        cmp eax,esi
    L_004057cb:
        jne short L_004057d5
    L_004057cd:
        fsub dword ptr [data_00470afc]
    L_004057d3:
        jmp short L_004057db
    L_004057d5:
        fsub dword ptr [data_00470d34]
    L_004057db:
        mov edx,dword ptr [edi+2Ch]
    L_004057de:
        fstp dword ptr [edi+34h]
    L_004057e1:
        fld dword ptr [edi+30h]
    L_004057e4:
        mov ecx,dword ptr [edi+38h]
    L_004057e7:
        fadd dword ptr [data_00470b4c]
    L_004057ed:
        push edx
    L_004057ee:
        lea esi,[esp+10h]
    L_004057f2:
        mov edx,ebp
    L_004057f4:
        fstp dword ptr [esp+10h]
    L_004057f8:
        mov dword ptr [esp+18h],ecx
    L_004057fc:
        fld dword ptr [edi+34h]
    L_004057ff:
        fadd dword ptr [data_00470b48]
    L_00405805:
        fstp dword ptr [esp+14h]
    L_00405809:
        call asm_AnimationManager_SetPosition_004492f0
    L_0040580e:
        mov eax,dword ptr [ebx+40h]
    L_00405811:
        mov esi,edi
    L_00405813:
        mov dword ptr [edi+3Ch],eax
    L_00405816:
        call asm_Player_Draw_00405ac0
    L_0040581b:
        lea esi,[edi+14h]
    L_0040581e:
        call asm_FrameTimer_Tick_00404ed0
    L_00405823:
        pop ebp
    L_00405824:
        pop ebx
    L_00405825:
        mov eax,1
    L_0040582a:
        pop esi
    L_0040582b:
        add esp,0Ch
    L_0040582e:
        ret
    }
}

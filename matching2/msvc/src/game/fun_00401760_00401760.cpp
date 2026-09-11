#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401000..0x004010FA: GameThread_ConstructOverlay
// Naked body preserves the retail register/stack ABI.

// 0x00401760..0x00401A41: FUN_00401760
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401760_00401760() {
    __asm {
    L_00401760:
        sub esp,10h
    L_00401763:
        push ebx
    L_00401764:
        push ebp
    L_00401765:
        mov ebp,dword ptr [esp+1Ch]
    L_00401769:
        mov eax,dword ptr [ebp+370h]
    L_0040176f:
        and eax,0FFD7FFFFh
    L_00401774:
        or eax,140001h
    L_00401779:
        mov dword ptr [ebp+370h],eax
    L_0040177f:
        mov eax,dword ptr [ebp+896Ch]
    L_00401785:
        test eax,eax
    L_00401787:
        push esi
    L_00401788:
        push edi
    L_00401789:
        mov dword ptr [esp+10h],1
    L_00401791:
        lea ebx,[ebp+76Ch]
    L_00401797:
        mov dword ptr [esp+1Ch],0
    L_0040179f:
        jle asm_target_004019e9
    L_004017a5:
        lea eax,[ebx+40h]
    L_004017a8:
        mov ecx,eax
    L_004017aa:
        mov edx,dword ptr [ecx]
    L_004017ac:
        lea eax,[ebp+348h]
    L_004017b2:
        mov dword ptr [eax],edx
    L_004017b4:
        mov edx,dword ptr [ecx+4]
    L_004017b7:
        mov dword ptr [eax+4],edx
    L_004017ba:
        mov ecx,dword ptr [ecx+8]
    L_004017bd:
        mov dword ptr [eax+8],ecx
    L_004017c0:
        fld dword ptr [ebx+54h]
    L_004017c3:
        mov ecx,dword ptr [ebp+370h]
    L_004017c9:
        mov edx,dword ptr [ebx+50h]
    L_004017cc:
        fstp dword ptr [ebp+54h]
    L_004017cf:
        or ecx,8
    L_004017d2:
        mov dword ptr [ebp+50h],edx
    L_004017d5:
        mov dword ptr [ebp+370h],ecx
    L_004017db:
        cmp dword ptr [ebx+60h],1
    L_004017df:
        mov edi,ebx
    L_004017e1:
        mov dword ptr [esp+14h],edi
    L_004017e5:
        jne short L_004017f9
    L_004017e7:
        mov dword ptr [esp+24h],40E00000h
    L_004017ef:
        mov dword ptr [esp+18h],41100000h
    L_004017f7:
        jmp short L_0040180e
    L_004017f9:
        fild dword ptr [ebp+898Ch]
    L_004017ff:
        mov dword ptr [esp+18h],41600000h
    L_00401807:
        fmul dword ptr [ebx+50h]
    L_0040180a:
        fstp dword ptr [esp+24h]
    L_0040180e:
        mov eax,dword ptr [ebx+5Ch]
    L_00401811:
        cmp dword ptr [esp+10h],eax
    L_00401815:
        je asm_target_004018a0
    L_0040181b:
        mov esi,dword ptr [data_00491c10]
    L_00401821:
        mov edi,eax
    L_00401823:
        mov dword ptr [esp+10h],edi
    L_00401827:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0040182c:
        test edi,edi
    L_0040182e:
        je short L_00401867
    L_00401830:
        mov edi,491D7Ch
    L_00401835:
        mov dword ptr [data_00491fac],edi
    L_0040183b:
        call asm_FUN_004215a0_004215a0
    L_00401840:
        mov edx,dword ptr [data_00491fac]
    L_00401846:
        mov eax,dword ptr [data_00491c30]
    L_0040184b:
        mov ecx,dword ptr [eax]
    L_0040184d:
        add edx,0CCh
    L_00401853:
        push edx
    L_00401854:
        push eax
    L_00401855:
        call dword ptr [ecx+0BCh]
    L_0040185b:
        mov dword ptr [data_00491fb0],0
    L_00401865:
        jmp short L_0040189c
    L_00401867:
        mov edi,491E94h
    L_0040186c:
        mov dword ptr [data_00491fac],edi
    L_00401872:
        call asm_FUN_004215a0_004215a0
    L_00401877:
        mov edx,dword ptr [data_00491fac]
    L_0040187d:
        mov eax,dword ptr [data_00491c30]
    L_00401882:
        mov ecx,dword ptr [eax]
    L_00401884:
        add edx,0CCh
    L_0040188a:
        push edx
    L_0040188b:
        push eax
    L_0040188c:
        call dword ptr [ecx+0BCh]
    L_00401892:
        mov dword ptr [data_00491fb0],1
    L_0040189c:
        mov edi,dword ptr [esp+14h]
    L_004018a0:
        cmp byte ptr [ebx],0
    L_004018a3:
        je asm_target_004019c7
    L_004018a9:
        lea esp,[esp+force_disp32_zero]
    L_004018b0:
        mov al,byte ptr [edi]
    L_004018b2:
        cmp al,0Ah
    L_004018b4:
        jne short L_004018d7
    L_004018b6:
        fld dword ptr [esp+18h]
    L_004018ba:
        fmul dword ptr [ebx+54h]
    L_004018bd:
        fadd dword ptr [ebp+34Ch]
    L_004018c3:
        fstp dword ptr [ebp+34Ch]
    L_004018c9:
        mov eax,dword ptr [ebx+40h]
    L_004018cc:
        mov dword ptr [ebp+348h],eax
    L_004018d2:
        jmp asm_target_004019bb
    L_004018d7:
        cmp al,20h
    L_004018d9:
        je asm_target_004019ab
    L_004018df:
        mov ecx,dword ptr [ebx+60h]
    L_004018e2:
        imul ecx,62h
    L_004018e5:
        movzx edx,al
    L_004018e8:
        lea eax,[ecx+edx-20h]
    L_004018ec:
        mov ecx,dword ptr [ebp+8994h]
    L_004018f2:
        imul eax,44h
    L_004018f5:
        mov edx,dword ptr [ecx+118h]
    L_004018fb:
        add eax,edx
    L_004018fd:
        mov dword ptr [ebp+3A8h],eax
    L_00401903:
        mov ecx,dword ptr [ebp+370h]
    L_00401909:
        fld dword ptr [eax+30h]
    L_0040190c:
        mov eax,dword ptr [eax+34h]
    L_0040190f:
        lea esi,[ebp+14h]
    L_00401912:
        or ecx,8
    L_00401915:
        mov dword ptr [esi+4Ch],eax
    L_00401918:
        fstp dword ptr [esi+50h]
    L_0040191b:
        mov dword ptr [esi+35Ch],ecx
    L_00401921:
        mov eax,dword ptr [ebx+64h]
    L_00401924:
        test eax,eax
    L_00401926:
        je short L_00401996
    L_00401928:
        mov ecx,dword ptr [ebx+4Ch]
    L_0040192b:
        fld dword ptr [ebp+348h]
    L_00401931:
        fadd dword ptr [data_00470b08]
    L_00401937:
        mov eax,dword ptr [data_00491c10]
    L_0040193c:
        and ecx,0FF000000h
    L_00401942:
        mov dword ptr [ebp+310h],ecx
    L_00401948:
        mov edx,dword ptr [ebx+4Ch]
    L_0040194b:
        fstp dword ptr [ebp+348h]
    L_00401951:
        fld dword ptr [ebp+34Ch]
    L_00401957:
        shr edx,19h
    L_0040195a:
        fadd dword ptr [data_00470b08]
    L_00401960:
        push eax
    L_00401961:
        mov byte ptr [ebp+313h],dl
    L_00401967:
        fstp dword ptr [ebp+34Ch]
    L_0040196d:
        call asm_FUN_00443080_00443080
    L_00401972:
        fld dword ptr [ebp+348h]
    L_00401978:
        fsub dword ptr [data_00470b08]
    L_0040197e:
        fstp dword ptr [ebp+348h]
    L_00401984:
        fld dword ptr [ebp+34Ch]
    L_0040198a:
        fsub dword ptr [data_00470b08]
    L_00401990:
        fstp dword ptr [ebp+34Ch]
    L_00401996:
        mov edx,dword ptr [data_00491c10]
    L_0040199c:
        mov ecx,dword ptr [ebx+4Ch]
    L_0040199f:
        push edx
    L_004019a0:
        mov dword ptr [ebp+310h],ecx
    L_004019a6:
        call asm_FUN_00443080_00443080
    L_004019ab:
        fld dword ptr [esp+24h]
    L_004019af:
        fadd dword ptr [ebp+348h]
    L_004019b5:
        fstp dword ptr [ebp+348h]
    L_004019bb:
        mov al,byte ptr [edi+1]
    L_004019be:
        inc edi
    L_004019bf:
        test al,al
    L_004019c1:
        jne asm_target_004018b0
    L_004019c7:
        mov eax,dword ptr [esp+1Ch]
    L_004019cb:
        mov ecx,dword ptr [ebp+896Ch]
    L_004019d1:
        inc eax
    L_004019d2:
        add ebx,68h
    L_004019d5:
        cmp eax,ecx
    L_004019d7:
        mov dword ptr [esp+1Ch],eax
    L_004019db:
        jl asm_target_004017a5
    L_004019e1:
        mov eax,dword ptr [esp+10h]
    L_004019e5:
        test eax,eax
    L_004019e7:
        je short L_00401a33
    L_004019e9:
        mov esi,dword ptr [data_00491c10]
    L_004019ef:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004019f4:
        mov edi,491E94h
    L_004019f9:
        mov dword ptr [data_00491fac],edi
    L_004019ff:
        call asm_FUN_004215a0_004215a0
    L_00401a04:
        mov edx,dword ptr [data_00491fac]
    L_00401a0a:
        mov eax,dword ptr [data_00491c30]
    L_00401a0f:
        mov ecx,dword ptr [eax]
    L_00401a11:
        add edx,0CCh
    L_00401a17:
        push edx
    L_00401a18:
        push eax
    L_00401a19:
        call dword ptr [ecx+0BCh]
    L_00401a1f:
        pop edi
    L_00401a20:
        pop esi
    L_00401a21:
        mov eax,1
    L_00401a26:
        pop ebp
    L_00401a27:
        mov dword ptr [data_00491fb0],eax
    L_00401a2c:
        pop ebx
    L_00401a2d:
        add esp,10h
    L_00401a30:
        ret 4
    L_00401a33:
        pop edi
    L_00401a34:
        pop esi
    L_00401a35:
        pop ebp
    L_00401a36:
        mov eax,1
    L_00401a3b:
        pop ebx
    L_00401a3c:
        add esp,10h
    L_00401a3f:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417870..0x00417C60: FUN_00417870
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417870_00417870() {
    __asm {
    L_00417870:
        push ebx
    L_00417871:
        push ebp
    L_00417872:
        mov ebp,dword ptr [esp+0Ch]
    L_00417876:
        mov eax,dword ptr [ebp+58h]
    L_00417879:
        push esi
    L_0041787a:
        or eax,4
    L_0041787d:
        push edi
    L_0041787e:
        mov dword ptr [ebp+58h],eax
    L_00417881:
        mov bl,80h
    L_00417883:
        mov eax,dword ptr [data_00491c10]
    L_00417888:
        mov ecx,dword ptr [eax]
    L_0041788a:
        xor edi,edi
    L_0041788c:
        cmp ecx,edi
    L_0041788e:
        jge short L_00417895
    L_00417890:
        cmp dword ptr [eax+4],edi
    L_00417893:
        jl short L_004178ab
    L_00417895:
        test byte ptr [data_00491ff4],bl
    L_0041789b:
        jne asm_target_00417b3e
    L_004178a1:
        push 1
    L_004178a3:
        call dword ptr [data_004660ac]
    L_004178a9:
        jmp short L_00417883
    L_004178ab:
        cmp dword ptr [data_00491fc4],edi
    L_004178b1:
        mov dword ptr [data_00476f78],3F800000h
    L_004178bb:
        mov dword ptr [data_00474c88],edi
    L_004178c1:
        mov dword ptr [data_00474c8c],edi
    L_004178c7:
        je asm_target_004179e9
    L_004178cd:
        cmp dword ptr [data_00474c7c],7
    L_004178d4:
        jne short L_004178e2
    L_004178d6:
        mov eax,4
    L_004178db:
        mov dword ptr [data_00474c74],eax
    L_004178e0:
        jmp short L_004178e7
    L_004178e2:
        mov eax,dword ptr [data_00474c74]
    L_004178e7:
        mov ecx,dword ptr [data_00474c68]
    L_004178ed:
        imul eax,0F0h
    L_004178f3:
        mov edx,dword ptr [data_00474c6c]
    L_004178f9:
        mov esi,dword ptr [data_0047783c]
    L_004178ff:
        lea edx,[edx+ecx*2]
    L_00417902:
        add edx,ecx
    L_00417904:
        imul edx,437Ch
    L_0041790a:
        add edx,esi
    L_0041790c:
        mov ecx,dword ptr [eax+edx+18h]
    L_00417910:
        add eax,edx
    L_00417912:
        mov dword ptr [data_00474c40],ecx
    L_00417918:
        movsx edx,byte ptr [eax+1Dh]
    L_0041791c:
        test byte ptr [data_00474ca0],8
    L_00417923:
        mov dword ptr [data_00474c94],edx
    L_00417929:
        jne short L_00417931
    L_0041792b:
        mov dword ptr [data_00474c90],edi
    L_00417931:
        push 0C350h
    L_00417936:
        mov ecx,474C40h
    L_0041793b:
        mov dword ptr [data_00474c44],edi
    L_00417941:
        call asm_ScoreGauge_SetTargetTenthAndDisableTimer_00418b80
    L_00417946:
        test byte ptr [data_00474ca0],10h
    L_0041794d:
        jne short L_0041795b
    L_0041794f:
        mov dword ptr [data_00474c70],2
    L_00417959:
        jmp short L_00417976
    L_0041795b:
        mov eax,dword ptr [data_00474cac]
    L_00417960:
        cmp eax,edi
    L_00417962:
        jne short L_00417970
    L_00417964:
        mov dword ptr [data_00474c70],9
    L_0041796e:
        jmp short L_00417976
    L_00417970:
        dec eax
    L_00417971:
        mov dword ptr [data_00474c70],eax
    L_00417976:
        mov eax,dword ptr [data_00474c7c]
    L_0041797b:
        mov ecx,dword ptr [data_00474ca0]
    L_00417981:
        dec eax
    L_00417982:
        neg eax
    L_00417984:
        sbb eax,eax
    L_00417986:
        and eax,50h
    L_00417989:
        and ecx,0FFFFFFFBh
    L_0041798c:
        mov word ptr [data_00474c48],ax
    L_00417992:
        mov dword ptr [data_00474ca0],ecx
    L_00417998:
        cmp dword ptr [ebp+5Ch],edi
    L_0041799b:
        jne short L_004179cc
    L_0041799d:
        mov eax,dword ptr [data_00474c68]
    L_004179a2:
        mov ecx,dword ptr [data_00474c6c]
    L_004179a8:
        lea edx,[ecx+eax*2]
    L_004179ab:
        add edx,eax
    L_004179ad:
        imul edx,437Ch
    L_004179b3:
        mov ecx,dword ptr [edx+esi+4C8h]
    L_004179ba:
        cmp ecx,1869Fh
    L_004179c0:
        lea eax,[edx+esi+4C8h]
    L_004179c7:
        jge short L_004179cc
    L_004179c9:
        inc ecx
    L_004179ca:
        mov dword ptr [eax],ecx
    L_004179cc:
        mov al,byte ptr [data_00474ca0]
    L_004179d1:
        and al,8
    L_004179d3:
        neg al
    L_004179d5:
        mov dword ptr [data_00474c9c],edi
    L_004179db:
        sbb eax,eax
    L_004179dd:
        and eax,0FFFFFE00h
    L_004179e2:
        mov dword ptr [data_00474c98],eax
    L_004179e7:
        jmp short L_004179fb
    L_004179e9:
        mov eax,dword ptr [data_00474c44]
    L_004179ee:
        cmp eax,dword ptr [data_00474c40]
    L_004179f4:
        jle short L_004179fb
    L_004179f6:
        mov dword ptr [data_00474c40],eax
    L_004179fb:
        push 4187C0h
    L_00417a00:
        mov dword ptr [data_00474c50],9
    L_00417a0a:
        call asm_SchedulerCallback_Create_00449ed0
    L_00417a0f:
        mov ecx,dword ptr [data_00491be4]
    L_00417a15:
        mov esi,eax
    L_00417a17:
        mov eax,dword ptr [esi+4]
    L_00417a1a:
        mov ebx,0FFFFFFFDh
    L_00417a1f:
        and eax,ebx
    L_00417a21:
        push ecx
    L_00417a22:
        mov edi,0Ah
    L_00417a27:
        mov dword ptr [esi+20h],ebp
    L_00417a2a:
        mov dword ptr [esi+4],eax
    L_00417a2d:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_00417a32:
        push 4187D0h
    L_00417a37:
        mov dword ptr [ebp+8],esi
    L_00417a3a:
        call asm_SchedulerCallback_Create_00449ed0
    L_00417a3f:
        mov esi,eax
    L_00417a41:
        and dword ptr [esi+4],ebx
    L_00417a44:
        mov edx,dword ptr [data_00491be4]
    L_00417a4a:
        push edx
    L_00417a4b:
        mov edi,4
    L_00417a50:
        mov dword ptr [esi+20h],ebp
    L_00417a53:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00417a58:
        mov eax,dword ptr [data_00477848]
    L_00417a5d:
        mov dword ptr [ebp+0Ch],esi
    L_00417a60:
        lea edi,[ebp+24h]
    L_00417a63:
        mov ecx,0Dh
    L_00417a68:
        mov esi,491D48h
    L_00417a6d:
        rep movsd
    L_00417a6f:
        mov ecx,dword ptr [eax]
    L_00417a71:
        mov dword ptr [ebp+4],ecx
    L_00417a74:
        test byte ptr [data_00474ca0],2
    L_00417a7b:
        jne short L_00417af5
    L_00417a7d:
        mov edx,dword ptr [ebp+5Ch]
    L_00417a80:
        push 477710h
    L_00417a85:
        push edx
    L_00417a86:
        call asm_FUN_00429610_00429610
    L_00417a8b:
        test eax,eax
    L_00417a8d:
        je asm_target_00417b3c
    L_00417a93:
        mov eax,dword ptr [data_00477848]
    L_00417a98:
        mov ecx,dword ptr [eax+4]
    L_00417a9b:
        push 0
    L_00417a9d:
        push ecx
    L_00417a9e:
        call asm_CreateGameState_00402640
    L_00417aa3:
        test eax,eax
    L_00417aa5:
        je asm_target_00417b3c
    L_00417aab:
        call asm_ItemManager_CreateRetail_00414830
    L_00417ab0:
        test eax,eax
    L_00417ab2:
        je asm_target_00417b3c
    L_00417ab8:
        call asm_Recovery_CreateLargeResourceState_00425020
    L_00417abd:
        test eax,eax
    L_00417abf:
        je short L_00417b3c
    L_00417ac1:
        call asm_FUN_00406060_00406060
    L_00417ac6:
        test eax,eax
    L_00417ac8:
        je short L_00417b3c
    L_00417aca:
        call asm_FUN_0041aed0_0041aed0
    L_00417acf:
        test eax,eax
    L_00417ad1:
        je short L_00417b3c
    L_00417ad3:
        call asm_ScoreManager_CreateAndInitRetail_0041c290
    L_00417ad8:
        test eax,eax
    L_00417ada:
        je short L_00417b3c
    L_00417adc:
        call asm_Recovery_CreateTimerState_00422360
    L_00417ae1:
        test eax,eax
    L_00417ae3:
        je short L_00417b3c
    L_00417ae5:
        call asm_Recovery_CreateResourceState_00419090
    L_00417aea:
        test eax,eax
    L_00417aec:
        je short L_00417b3c
    L_00417aee:
        call asm_Recovery_CreateHugeResourceState_0042b660
    L_00417af3:
        jmp short L_00417b1c
    L_00417af5:
        mov ebx,dword ptr [data_00477838]
    L_00417afb:
        call asm_FUN_0042a6a0_0042a6a0
    L_00417b00:
        mov edx,dword ptr [data_0047770c]
    L_00417b06:
        push edx
    L_00417b07:
        call asm_FUN_00413a20_00413a20
    L_00417b0c:
        mov eax,dword ptr [data_00477848]
    L_00417b11:
        mov ecx,dword ptr [eax+4]
    L_00417b14:
        push 0
    L_00417b16:
        push ecx
    L_00417b17:
        call asm_CreateGameState_00402640
    L_00417b1c:
        test eax,eax
    L_00417b1e:
        je short L_00417b3c
    L_00417b20:
        test byte ptr [data_00474ca0],9
    L_00417b27:
        jne short L_00417b81
    L_00417b29:
        mov edx,dword ptr [data_00477848]
    L_00417b2f:
        mov eax,dword ptr [edx+0Ch]
    L_00417b32:
        push eax
    L_00417b33:
        call asm_EnemyManager_CreateRetail_0040d6b0
    L_00417b38:
        test eax,eax
    L_00417b3a:
        jne short L_00417b8b
    L_00417b3c:
        xor edi,edi
    L_00417b3e:
        mov esi,dword ptr [ebp+58h]
    L_00417b41:
        or esi,8
    L_00417b44:
        push 491C28h
    L_00417b49:
        mov dword ptr [ebp+58h],esi
    L_00417b4c:
        call asm_FUN_00421300_00421300
    L_00417b51:
        mov dword ptr [data_00492264],edi
    L_00417b57:
        mov dword ptr [data_00492260],1
    L_00417b61:
        mov eax,dword ptr [ebp+8]
    L_00417b64:
        cmp eax,edi
    L_00417b66:
        je short L_00417b6c
    L_00417b68:
        or dword ptr [eax+4],2
    L_00417b6c:
        mov ebp,dword ptr [ebp+0Ch]
    L_00417b6f:
        cmp ebp,edi
    L_00417b71:
        je short L_00417b77
    L_00417b73:
        or dword ptr [ebp+4],2
    L_00417b77:
        pop edi
    L_00417b78:
        pop esi
    L_00417b79:
        pop ebp
    L_00417b7a:
        or eax,0FFFFFFFFh
    L_00417b7d:
        pop ebx
    L_00417b7e:
        ret 4
    L_00417b81:
        mov eax,dword ptr [data_00477704]
    L_00417b86:
        call asm_PathState_Reset_00417800
    L_00417b8b:
        call asm_BulletManager_Create_0040af90
    L_00417b90:
        test eax,eax
    L_00417b92:
        je short L_00417b3c
    L_00417b94:
        call asm_Recovery_CreateFixedState_004056b0
    L_00417b99:
        test eax,eax
    L_00417b9b:
        je short L_00417b3c
    L_00417b9d:
        call asm_PlayerManager_CreateRetail_00408c90
    L_00417ba2:
        test eax,eax
    L_00417ba4:
        je short L_00417b3c
    L_00417ba6:
        test byte ptr [data_00474ca0],20h
    L_00417bad:
        jne short L_00417bd8
    L_00417baf:
        call asm_GameState_DispatchDummy_00420c00
    L_00417bb4:
        mov ecx,dword ptr [data_00477848]
    L_00417bba:
        mov edx,dword ptr [ecx+10h]
    L_00417bbd:
        push edx
    L_00417bbe:
        xor esi,esi
    L_00417bc0:
        push esi
    L_00417bc1:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_00417bc6:
        mov eax,dword ptr [data_00477848]
    L_00417bcb:
        mov ecx,dword ptr [eax+14h]
    L_00417bce:
        push ecx
    L_00417bcf:
        push 1
    L_00417bd1:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_00417bd6:
        jmp short L_00417bda
    L_00417bd8:
        xor esi,esi
    L_00417bda:
        mov eax,dword ptr [data_00477708]
    L_00417bdf:
        fld qword ptr [data_00470b70]
    L_00417be5:
        fstp qword ptr [eax+2Ch]
    L_00417be8:
        push esi
    L_00417be9:
        fld qword ptr [data_00470b70]
    L_00417bef:
        fstp qword ptr [eax+24h]
    L_00417bf2:
        lea eax,[ebp+10h]
    L_00417bf5:
        call asm_Player_SetSchedulerValue_00405410
    L_00417bfa:
        cmp dword ptr [data_00494518],esi
    L_00417c00:
        je short L_00417c12
    L_00417c02:
        push 10h
    L_00417c04:
        call dword ptr [data_004660ac]
    L_00417c0a:
        cmp dword ptr [data_00494518],esi
    L_00417c10:
        jne short L_00417c02
    L_00417c12:
        cmp dword ptr [data_00474c84],esi
    L_00417c18:
        je short L_00417c20
    L_00417c1a:
        mov dword ptr [data_00474c8c],esi
    L_00417c20:
        push 491C28h
    L_00417c25:
        mov dword ptr [data_00474c84],esi
    L_00417c2b:
        call asm_FUN_00421070_00421070
    L_00417c30:
        and dword ptr [ebp+58h],0FFFFFFFBh
    L_00417c34:
        and dword ptr [data_00474ca0],0FFFFFFF4h
    L_00417c3b:
        mov eax,ebp
    L_00417c3d:
        mov dword ptr [data_00492264],esi
    L_00417c43:
        mov dword ptr [data_00492260],1
    L_00417c4d:
        mov dword ptr [data_004918a4],esi
    L_00417c53:
        call asm_Retire_ScoreRuntimeCallbacks_00409e20
    L_00417c58:
        pop edi
    L_00417c59:
        pop esi
    L_00417c5a:
        pop ebp
    L_00417c5b:
        xor eax,eax
    L_00417c5d:
        pop ebx
    L_00417c5e:
        ret 4
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004218D0..0x00421B0B: FUN_004218d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004218d0_004218d0() {
    __asm {
    L_004218d0:
        push ebx
    L_004218d1:
        push ebp
    L_004218d2:
        push esi
    L_004218d3:
        push edi
    L_004218d4:
        mov edi,eax
    L_004218d6:
        mov eax,dword ptr [edi+38Ch]
    L_004218dc:
        cmp eax,dword ptr [edi+390h]
    L_004218e2:
        je asm_target_004219a4
    L_004218e8:
        lea ebp,[edi+6C4h]
    L_004218ee:
        push ebp
    L_004218ef:
        call dword ptr [data_004660b0]
    L_004218f5:
        mov bl,byte ptr [edi+6F9h]
    L_004218fb:
        mov ecx,dword ptr [edi+390h]
    L_00421901:
        mov eax,dword ptr [edi+38Ch]
    L_00421907:
        inc bl
    L_00421909:
        cmp ecx,0Fh
    L_0042190c:
        mov byte ptr [edi+6F9h],bl
    L_00421912:
        mov dword ptr [edi+394h],eax
    L_00421918:
        mov dword ptr [edi+780h],0FF000000h
    L_00421922:
        ja short L_0042198b
    L_00421924:
        jmp dword ptr [ecx*4+421B0Ch]
    L_0042192b:
        mov dword ptr [edi+390h],1
    L_00421935:
        call asm_EnemySlot_CreateAndInitRetail_0041fd00
    L_0042193a:
        test eax,eax
    L_0042193c:
        mov dword ptr [edi+768h],eax
    L_00421942:
        jne short L_0042198b
    L_00421944:
        mov dword ptr [edi+390h],3
    L_0042194e:
        call asm_Recovery_ReleaseGlobalStates_004203f0
    L_00421953:
        mov esi,5
    L_00421958:
        call asm_SlotLockTable_LeaveRetail_00421c50
    L_0042195d:
        pop edi
    L_0042195e:
        pop esi
    L_0042195f:
        pop ebp
    L_00421960:
        mov eax,4
    L_00421965:
        pop ebx
    L_00421966:
        ret
    L_00421967:
        dec eax
    L_00421968:
        cmp eax,0Dh
    L_0042196b:
        ja short L_0042198b
    L_0042196d:
        movzx ecx,byte ptr [eax+421B5Ch]
    L_00421974:
        jmp dword ptr [ecx*4+421B4Ch]
    L_0042197b:
        mov esi,dword ptr [data_00477810]
    L_00421981:
        call asm_Heap_DestroyOwned_00418150
    L_00421986:
        call asm_ProgressManager_CreateAndStartWorker_0042cd50
    L_0042198b:
        mov eax,dword ptr [edi+390h]
    L_00421991:
        push ebp
    L_00421992:
        mov dword ptr [edi+38Ch],eax
    L_00421998:
        call dword ptr [data_004660b4]
    L_0042199e:
        dec byte ptr [edi+6F9h]
    L_004219a4:
        pop edi
    L_004219a5:
        pop esi
    L_004219a6:
        pop ebp
    L_004219a7:
        mov eax,1
    L_004219ac:
        pop ebx
    L_004219ad:
        ret
    L_004219ae:
        mov esi,dword ptr [data_00477700]
    L_004219b4:
        call asm_ScoreOwnedObject_Destroy_0040b9d0
    L_004219b9:
        jmp short L_00421986
    L_004219bb:
        sub eax,2
    L_004219be:
        je short L_004219e2
    L_004219c0:
        sub eax,5
    L_004219c3:
        je short L_004219d7
    L_004219c5:
        sub eax,7
    L_004219c8:
        jne short L_0042198b
    L_004219ca:
        mov esi,dword ptr [data_00477700]
    L_004219d0:
        call asm_ScoreOwnedObject_Destroy_0040b9d0
    L_004219d5:
        jmp short L_004219e2
    L_004219d7:
        mov esi,dword ptr [data_00477810]
    L_004219dd:
        call asm_Heap_DestroyOwned_00418150
    L_004219e2:
        mov dword ptr [edi+390h],4
    L_004219ec:
        mov dword ptr [data_00491c00],3
    L_004219f6:
        jmp short L_00421986
    L_004219f8:
        cmp eax,4
    L_004219fb:
        jne short L_00421a08
    L_004219fd:
        mov esi,dword ptr [data_0047784c]
    L_00421a03:
        call asm_Heap_DestroyOwnedSecondary_0042cdb0
    L_00421a08:
        push 0
    L_00421a0a:
        mov dword ptr [edi+39Ch],1
    L_00421a14:
        call asm_GameUi_CreateAndPublish_004180e0
    L_00421a19:
        jmp asm_target_0042198b
    L_00421a1e:
        cmp eax,4
    L_00421a21:
        jne short L_00421a2e
    L_00421a23:
        mov esi,dword ptr [data_0047784c]
    L_00421a29:
        call asm_Heap_DestroyOwnedSecondary_0042cdb0
    L_00421a2e:
        push 1
    L_00421a30:
        mov dword ptr [edi+390h],7
    L_00421a3a:
        mov dword ptr [edi+39Ch],1
    L_00421a44:
        call asm_GameUi_CreateAndPublish_004180e0
    L_00421a49:
        jmp asm_target_0042198b
    L_00421a4e:
        cmp eax,7
    L_00421a51:
        mov esi,dword ptr [data_00477810]
    L_00421a57:
        mov ebx,dword ptr [esi+5Ch]
    L_00421a5a:
        mov dword ptr [edi+39Ch],0
    L_00421a64:
        jne short L_00421a6b
    L_00421a66:
        call asm_Heap_DestroyOwned_00418150
    L_00421a6b:
        push ebx
    L_00421a6c:
        mov dword ptr [edi+390h],7
    L_00421a76:
        call asm_GameUi_CreateAndPublish_004180e0
    L_00421a7b:
        jmp asm_target_0042198b
    L_00421a80:
        mov esi,dword ptr [data_00477810]
    L_00421a86:
        call asm_Heap_DestroyOwned_00418150
    L_00421a8b:
        mov dword ptr [edi+39Ch],1
    L_00421a95:
        mov dword ptr [edi+390h],7
    L_00421a9f:
        mov eax,dword ptr [data_00474c80]
    L_00421aa4:
        lea edx,[eax+eax*2]
    L_00421aa7:
        shl edx,4
    L_00421aaa:
        add edx,474788h
    L_00421ab0:
        push 0
    L_00421ab2:
        mov dword ptr [data_00474c7c],eax
    L_00421ab7:
        mov dword ptr [data_00477848],edx
    L_00421abd:
        call asm_GameUi_CreateAndPublish_004180e0
    L_00421ac2:
        jmp asm_target_0042198b
    L_00421ac7:
        mov esi,dword ptr [data_00477810]
    L_00421acd:
        call asm_Heap_DestroyOwned_00418150
    L_00421ad2:
        push 0
    L_00421ad4:
        mov dword ptr [edi+39Ch],1
    L_00421ade:
        mov dword ptr [edi+390h],7
    L_00421ae8:
        call asm_GameUi_CreateAndPublish_004180e0
    L_00421aed:
        jmp asm_target_0042198b
    L_00421af2:
        cmp eax,7
    L_00421af5:
        jne short L_00421b02
    L_00421af7:
        mov esi,dword ptr [data_00477810]
    L_00421afd:
        call asm_Heap_DestroyOwned_00418150
    L_00421b02:
        call asm_Recovery_CreateSmallState_0040b940
    L_00421b07:
        jmp asm_target_0042198b
    }
}

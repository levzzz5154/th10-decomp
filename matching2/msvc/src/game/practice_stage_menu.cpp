#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00430FF0..0x004313F6: FUN_00430ff0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00430ff0_00430ff0() {
    __asm {
    L_00430ff0:
        push ebp
    L_00430ff1:
        mov ebp,dword ptr [esp+8]
    L_00430ff5:
        mov eax,dword ptr [ebp+20h]
    L_00430ff8:
        cmp eax,4
    L_00430ffb:
        ja asm_target_004313ee
    L_00431001:
        push ebx
    L_00431002:
        push esi
    L_00431003:
        push edi
    L_00431004:
        jmp dword ptr [eax*4+4313F8h]
    L_0043100b:
        mov dword ptr [ebp+2Ch],6
    L_00431012:
        mov eax,dword ptr [ebp+2Ch]
    L_00431015:
        test eax,eax
    L_00431017:
        je short L_00431032
    L_00431019:
        mov ecx,dword ptr [data_00491c08]
    L_0043101f:
        cmp ecx,eax
    L_00431021:
        jl short L_00431026
    L_00431023:
        dec eax
    L_00431024:
        jmp short L_00431037
    L_00431026:
        xor eax,eax
    L_00431028:
        test ecx,ecx
    L_0043102a:
        setl al
    L_0043102d:
        dec eax
    L_0043102e:
        and eax,ecx
    L_00431030:
        jmp short L_00431037
    L_00431032:
        mov eax,dword ptr [data_00491c08]
    L_00431037:
        push ebp
    L_00431038:
        mov edi,6Ah
    L_0043103d:
        mov dword ptr [ebp+24h],eax
    L_00431040:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00431045:
        mov edi,dword ptr [data_00474c68]
    L_0043104b:
        add edi,6Bh
    L_0043104e:
        push ebp
    L_0043104f:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00431054:
        mov ecx,1
    L_00431059:
        mov eax,ebp
    L_0043105b:
        call asm_GameState_SetTimerTarget_0042c620
    L_00431060:
        cmp dword ptr [ebp+2B4h],0Ah
    L_00431067:
        jle asm_target_004313eb
    L_0043106d:
        mov ecx,2
    L_00431072:
        mov eax,ebp
    L_00431074:
        call asm_GameState_SetTimerTarget_0042c620
    L_00431079:
        pop edi
    L_0043107a:
        pop esi
    L_0043107b:
        pop ebx
    L_0043107c:
        mov eax,1
    L_00431081:
        pop ebp
    L_00431082:
        ret 4
    L_00431085:
        mov ecx,dword ptr [ebp+24h]
    L_00431088:
        lea esi,[ebp+24h]
    L_0043108b:
        mov dword ptr [esi+4],ecx
    L_0043108e:
        mov cl,byte ptr [data_00474e36]
    L_00431094:
        mov al,10h
    L_00431096:
        test cl,al
    L_00431098:
        jne short L_004310a2
    L_0043109a:
        test byte ptr [data_00474e34],al
    L_004310a0:
        je short L_004310ab
    L_004310a2:
        push 0FFFFFFFFh
    L_004310a4:
        mov eax,esi
    L_004310a6:
        call asm_MenuCursor_Advance_0044bea0
    L_004310ab:
        mov cl,byte ptr [data_00474e36]
    L_004310b1:
        mov al,20h
    L_004310b3:
        test cl,al
    L_004310b5:
        jne short L_004310bf
    L_004310b7:
        test byte ptr [data_00474e34],al
    L_004310bd:
        je short L_004310c8
    L_004310bf:
        push 1
    L_004310c1:
        mov eax,esi
    L_004310c3:
        call asm_MenuCursor_Advance_0044bea0
    L_004310c8:
        mov edx,dword ptr [esi+4]
    L_004310cb:
        cmp edx,dword ptr [esi]
    L_004310cd:
        je short L_004310e0
    L_004310cf:
        push 0
    L_004310d1:
        mov edi,0Ch
    L_004310d6:
        mov ecx,492590h
    L_004310db:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004310e0:
        mov eax,dword ptr [data_00474e36]
    L_004310e5:
        test al,0Ah
    L_004310e7:
        je short L_00431119
    L_004310e9:
        mov ecx,4
    L_004310ee:
        mov eax,ebp
    L_004310f0:
        call asm_GameState_SetTimerTarget_0042c620
    L_004310f5:
        push 0
    L_004310f7:
        mov edi,0Bh
    L_004310fc:
        mov ecx,492590h
    L_00431101:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00431106:
        mov eax,dword ptr [esi]
    L_00431108:
        pop edi
    L_00431109:
        pop esi
    L_0043110a:
        pop ebx
    L_0043110b:
        mov dword ptr [data_00491c08],eax
    L_00431110:
        mov eax,1
    L_00431115:
        pop ebp
    L_00431116:
        ret 4
    L_00431119:
        test eax,1001h
    L_0043111e:
        je asm_target_004313eb
    L_00431124:
        mov eax,dword ptr [data_00474c74]
    L_00431129:
        mov edx,dword ptr [esi]
    L_0043112b:
        mov edi,dword ptr [data_0047783c]
    L_00431131:
        lea ecx,[eax+eax*2]
    L_00431134:
        mov eax,dword ptr [data_00474c68]
    L_00431139:
        lea ecx,[edx+ecx*2]
    L_0043113c:
        mov edx,dword ptr [data_00474c6c]
    L_00431142:
        lea edx,[edx+eax*2]
    L_00431145:
        add edx,eax
    L_00431147:
        imul edx,437Ch
    L_0043114d:
        add edx,edi
    L_0043114f:
        mov al,byte ptr [edx+ecx*8+4E9h]
    L_00431156:
        test al,al
    L_00431158:
        mov ebx,3
    L_0043115d:
        jne short L_00431166
    L_0043115f:
        mov edi,25h
    L_00431164:
        jmp short L_00431174
    L_00431166:
        mov ecx,ebx
    L_00431168:
        mov eax,ebp
    L_0043116a:
        call asm_GameState_SetTimerTarget_0042c620
    L_0043116f:
        mov edi,0Ah
    L_00431174:
        mov ecx,492590h
    L_00431179:
        push 0
    L_0043117b:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00431180:
        mov eax,dword ptr [esi]
    L_00431182:
        mov edx,497AA8h
    L_00431187:
        mov dword ptr [data_00491c08],eax
    L_0043118c:
        mov dword ptr [data_00474cac],0
    L_00431196:
        call asm_Input_UpdateKeyboardState_0044b010
    L_0043119b:
        test eax,eax
    L_0043119d:
        mov al,80h
    L_0043119f:
        jne asm_target_004312b5
    L_004311a5:
        test byte ptr [data_00497ad9],al
    L_004311ab:
        je short L_004311c3
    L_004311ad:
        pop edi
    L_004311ae:
        pop esi
    L_004311af:
        pop ebx
    L_004311b0:
        mov dword ptr [data_00474cac],1
    L_004311ba:
        mov eax,1
    L_004311bf:
        pop ebp
    L_004311c0:
        ret 4
    L_004311c3:
        test byte ptr [data_00497ada],al
    L_004311c9:
        je short L_004311e1
    L_004311cb:
        pop edi
    L_004311cc:
        pop esi
    L_004311cd:
        pop ebx
    L_004311ce:
        mov dword ptr [data_00474cac],2
    L_004311d8:
        mov eax,1
    L_004311dd:
        pop ebp
    L_004311de:
        ret 4
    L_004311e1:
        test byte ptr [data_00497adb],al
    L_004311e7:
        je short L_004311fb
    L_004311e9:
        pop edi
    L_004311ea:
        pop esi
    L_004311eb:
        mov dword ptr [data_00474cac],ebx
    L_004311f1:
        pop ebx
    L_004311f2:
        mov eax,1
    L_004311f7:
        pop ebp
    L_004311f8:
        ret 4
    L_004311fb:
        test byte ptr [data_00497adc],al
    L_00431201:
        je short L_00431219
    L_00431203:
        pop edi
    L_00431204:
        pop esi
    L_00431205:
        pop ebx
    L_00431206:
        mov dword ptr [data_00474cac],4
    L_00431210:
        mov eax,1
    L_00431215:
        pop ebp
    L_00431216:
        ret 4
    L_00431219:
        test byte ptr [data_00497add],al
    L_0043121f:
        je short L_00431237
    L_00431221:
        pop edi
    L_00431222:
        pop esi
    L_00431223:
        pop ebx
    L_00431224:
        mov dword ptr [data_00474cac],5
    L_0043122e:
        mov eax,1
    L_00431233:
        pop ebp
    L_00431234:
        ret 4
    L_00431237:
        test byte ptr [data_00497ade],al
    L_0043123d:
        je short L_00431255
    L_0043123f:
        pop edi
    L_00431240:
        pop esi
    L_00431241:
        pop ebx
    L_00431242:
        mov dword ptr [data_00474cac],6
    L_0043124c:
        mov eax,1
    L_00431251:
        pop ebp
    L_00431252:
        ret 4
    L_00431255:
        test byte ptr [data_00497adf],al
    L_0043125b:
        je short L_00431273
    L_0043125d:
        pop edi
    L_0043125e:
        pop esi
    L_0043125f:
        pop ebx
    L_00431260:
        mov dword ptr [data_00474cac],7
    L_0043126a:
        mov eax,1
    L_0043126f:
        pop ebp
    L_00431270:
        ret 4
    L_00431273:
        test byte ptr [data_00497ae0],al
    L_00431279:
        je short L_00431291
    L_0043127b:
        pop edi
    L_0043127c:
        pop esi
    L_0043127d:
        pop ebx
    L_0043127e:
        mov dword ptr [data_00474cac],8
    L_00431288:
        mov eax,1
    L_0043128d:
        pop ebp
    L_0043128e:
        ret 4
    L_00431291:
        mov cl,byte ptr [data_00497ae1]
    L_00431297:
        test cl,al
    L_00431299:
        je asm_target_004313eb
    L_0043129f:
        pop edi
    L_004312a0:
        pop esi
    L_004312a1:
        pop ebx
    L_004312a2:
        mov dword ptr [data_00474cac],9
    L_004312ac:
        mov eax,1
    L_004312b1:
        pop ebp
    L_004312b2:
        ret 4
    L_004312b5:
        test byte ptr [data_00497aaa],al
    L_004312bb:
        jne asm_target_004311ad
    L_004312c1:
        test byte ptr [data_00497aab],al
    L_004312c7:
        jne asm_target_004311cb
    L_004312cd:
        test byte ptr [data_00497aac],al
    L_004312d3:
        jne asm_target_004311e9
    L_004312d9:
        test byte ptr [data_00497aad],al
    L_004312df:
        jne asm_target_00431203
    L_004312e5:
        test byte ptr [data_00497aae],al
    L_004312eb:
        jne asm_target_00431221
    L_004312f1:
        test byte ptr [data_00497aaf],al
    L_004312f7:
        jne asm_target_0043123f
    L_004312fd:
        test byte ptr [data_00497ab0],al
    L_00431303:
        jne asm_target_0043125d
    L_00431309:
        test byte ptr [data_00497ab1],al
    L_0043130f:
        jne asm_target_0043127b
    L_00431315:
        mov cl,byte ptr [data_00497ab2]
    L_0043131b:
        jmp asm_target_00431297
    L_00431320:
        cmp dword ptr [ebp+2B4h],0Ah
    L_00431327:
        jne short L_00431352
    L_00431329:
        mov esi,dword ptr [data_004776e0]
    L_0043132f:
        push 43C40000h
    L_00431334:
        push 43F00000h
    L_00431339:
        call asm_FUN_0040c540_0040c540
    L_0043133e:
        push 0
    L_00431340:
        push 0
    L_00431342:
        push 0
    L_00431344:
        push 20h
    L_00431346:
        push 5
    L_00431348:
        mov ebx,2Bh
    L_0043134d:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_00431352:
        cmp dword ptr [ebp+2B4h],28h
    L_00431359:
        jl asm_target_004313eb
    L_0043135f:
        lea esi,[ebp+24h]
    L_00431362:
        mov eax,esi
    L_00431364:
        call asm_Score_InputHistorySave_0044be20
    L_00431369:
        mov ecx,3
    L_0043136e:
        mov eax,ebp
    L_00431370:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00431375:
        mov eax,dword ptr [esi]
    L_00431377:
        inc eax
    L_00431378:
        lea ecx,[eax+eax*2]
    L_0043137b:
        shl ecx,4
    L_0043137e:
        add ecx,474788h
    L_00431384:
        push 40C00000h
    L_00431389:
        mov dword ptr [data_00477848],ecx
    L_0043138f:
        mov dword ptr [data_00474c7c],eax
    L_00431394:
        mov dword ptr [data_00474c80],eax
    L_00431399:
        call asm_Sound_PlayRandomVoiceRetail_00420c30
    L_0043139e:
        pop edi
    L_0043139f:
        pop esi
    L_004313a0:
        pop ebx
    L_004313a1:
        mov dword ptr [data_00491fb8],7
    L_004313ab:
        mov eax,1
    L_004313b0:
        pop ebp
    L_004313b1:
        ret 4
    L_004313b4:
        cmp dword ptr [ebp+2B4h],6
    L_004313bb:
        jl short L_004313eb
    L_004313bd:
        mov esi,6Ah
    L_004313c2:
        mov edi,ebp
    L_004313c4:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004313c9:
        mov esi,dword ptr [data_00474c68]
    L_004313cf:
        add esi,6Bh
    L_004313d2:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004313d7:
        mov ecx,8
    L_004313dc:
        mov eax,ebp
    L_004313de:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_004313e3:
        lea eax,[ebp+24h]
    L_004313e6:
        call asm_Score_InputHistoryStep_0044be70
    L_004313eb:
        pop edi
    L_004313ec:
        pop esi
    L_004313ed:
        pop ebx
    L_004313ee:
        mov eax,1
    L_004313f3:
        pop ebp
    L_004313f4:
        ret 4
    }
}

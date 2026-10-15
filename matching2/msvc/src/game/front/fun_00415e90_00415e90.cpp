// BLOCKED (D3503): closest_byte_count=4480/4480; first_diff=none
// (retail assembly baseline is exact; no readable candidate retained).
// residual_class=large state-machine/jump-table body with private caller
// context, opaque object layout, and many ABI-sensitive helper calls.
// variants_tested=live Ghidra decompilation at 0x00415E90; caller
// 0x00414900 inspection; retail assembly probe.
// next_lever=schema-2 native-LTCG cluster joining 0x00414900 and this
// member, then recover the state layout and helper prototypes incrementally.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"



// 0x00415E90..0x00416F61: FUN_00415e90
// Naked body preserves the retail register/stack ABI.

// 0x00415E90..0x00416F61: FUN_00415e90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00415e90_00415e90() {
    __asm {
    L_00415e90:
        sub esp,0D8h
    L_00415e96:
        push ebx
    L_00415e97:
        push ebp
    L_00415e98:
        mov ebp,dword ptr [esp+0E4h]
    L_00415e9f:
        mov eax,dword ptr [ebp+78h]
    L_00415ea2:
        xor edx,edx
    L_00415ea4:
        cmp eax,edx
    L_00415ea6:
        push esi
    L_00415ea7:
        push edi
    L_00415ea8:
        jle short L_00415eae
    L_00415eaa:
        dec eax
    L_00415eab:
        mov dword ptr [ebp+78h],eax
    L_00415eae:
        test byte ptr [ebp+7Ch],1
    L_00415eb2:
        je short L_00415ef7
    L_00415eb4:
        mov eax,dword ptr [g_input]
    L_00415eb9:
        test ah,1
    L_00415ebc:
        je short L_00415ef7
    L_00415ebe:
        mov eax,dword ptr [ebp+5Ch]
    L_00415ec1:
        movzx ecx,word ptr [eax]
    L_00415ec4:
        mov eax,dword ptr [ebp+28h]
    L_00415ec7:
        test al,1
    L_00415ec9:
        mov dword ptr [esp+10h],ecx
    L_00415ecd:
        jne short L_00415ee9
    L_00415ecf:
        or eax,1
    L_00415ed2:
        mov dword ptr [ebp+1Ch],edx
    L_00415ed5:
        mov dword ptr [ebp+18h],0FFF0BDC1h
    L_00415edc:
        mov dword ptr [ebp+20h],edx
    L_00415edf:
        mov dword ptr [ebp+24h],476F78h
    L_00415ee6:
        mov dword ptr [ebp+28h],eax
    L_00415ee9:
        fild dword ptr [esp+10h]
    L_00415eed:
        mov dword ptr [ebp+1Ch],ecx
    L_00415ef0:
        dec ecx
    L_00415ef1:
        mov dword ptr [ebp+18h],ecx
    L_00415ef4:
        fstp dword ptr [ebp+20h]
    L_00415ef7:
        mov ecx,dword ptr [ebp+5Ch]
    L_00415efa:
        movzx edx,word ptr [ecx]
    L_00415efd:
        cmp dword ptr [ebp+1Ch],edx
    L_00415f00:
        jl asm_target_00416f25
    L_00415f06:
        mov eax,dword ptr [ebp+5Ch]
    L_00415f09:
        movzx ecx,byte ptr [eax+2]
    L_00415f0d:
        cmp ecx,17h
    L_00415f10:
        ja asm_target_00416f09
    L_00415f16:
        jmp dword ptr [ecx*4+416F64h]
    L_00415f1d:
        lea edi,[ebp+4Ch]
    L_00415f20:
        jmp short L_00415f25
    L_00415f22:
        lea edi,[ebp+50h]
    L_00415f25:
        mov eax,dword ptr [edi]
    L_00415f27:
        mov ebx,dword ptr [g_sprt_ctrl]
    L_00415f2d:
        mov edx,ebx
    L_00415f2f:
        push eax
    L_00415f30:
        call asm_AnimationManager_Find_004491c0
    L_00415f35:
        mov esi,eax
    L_00415f37:
        test esi,esi
    L_00415f39:
        jne short L_00415f3d
    L_00415f3b:
        mov dword ptr [edi],eax
    L_00415f3d:
        mov eax,dword ptr [ebp+5Ch]
    L_00415f40:
        add eax,4
    L_00415f43:
        call asm_Path_DecodeXor_00417010
    L_00415f48:
        mov ecx,dword ptr [ebp+84h]
    L_00415f4e:
        mov edx,dword ptr [ebp+ecx*4+88h]
    L_00415f55:
        push eax
    L_00415f56:
        push edx
    L_00415f57:
        push ebx
    L_00415f58:
        call asm_Recovery_MarkLogState_00447a50
    L_00415f5d:
        add esp,0Ch
    L_00415f60:
        mov eax,edi
    L_00415f62:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_00415f67:
        jmp asm_target_00416f09
    L_00415f6c:
        mov eax,dword ptr [ebp+80h]
    L_00415f72:
        test eax,eax
    L_00415f74:
        jne asm_target_00416041
    L_00415f7a:
        mov eax,dword ptr [ebp+4Ch]
    L_00415f7d:
        mov esi,dword ptr [g_sprt_ctrl]
    L_00415f83:
        lea edi,[ebp+4Ch]
    L_00415f86:
        push eax
    L_00415f87:
        mov edx,esi
    L_00415f89:
        call asm_AnimationManager_Find_004491c0
    L_00415f8e:
        test eax,eax
    L_00415f90:
        jne short L_00415f94
    L_00415f92:
        mov dword ptr [edi],eax
    L_00415f94:
        mov ecx,dword ptr [ebp+84h]
    L_00415f9a:
        mov edx,dword ptr [ebp+ecx*4+88h]
    L_00415fa1:
        push 46CFD4h
    L_00415fa6:
        push edx
    L_00415fa7:
        push esi
    L_00415fa8:
        mov esi,eax
    L_00415faa:
        call asm_Recovery_MarkLogState_00447a50
    L_00415faf:
        mov eax,dword ptr [ebp+50h]
    L_00415fb2:
        mov esi,dword ptr [g_sprt_ctrl]
    L_00415fb8:
        lea ebx,[ebp+50h]
    L_00415fbb:
        add esp,0Ch
    L_00415fbe:
        push eax
    L_00415fbf:
        mov edx,esi
    L_00415fc1:
        call asm_AnimationManager_Find_004491c0
    L_00415fc6:
        test eax,eax
    L_00415fc8:
        jne short L_00415fcc
    L_00415fca:
        mov dword ptr [ebx],eax
    L_00415fcc:
        mov ecx,dword ptr [ebp+84h]
    L_00415fd2:
        mov edx,dword ptr [ebp+ecx*4+88h]
    L_00415fd9:
        push 46CFD4h
    L_00415fde:
        push edx
    L_00415fdf:
        push esi
    L_00415fe0:
        mov esi,eax
    L_00415fe2:
        call asm_Recovery_MarkLogState_00447a50
    L_00415fe7:
        mov eax,dword ptr [edi]
    L_00415fe9:
        mov edx,dword ptr [g_sprt_ctrl]
    L_00415fef:
        add esp,0Ch
    L_00415ff2:
        push eax
    L_00415ff3:
        call asm_AnimationManager_Find_004491c0
    L_00415ff8:
        mov esi,eax
    L_00415ffa:
        test esi,esi
    L_00415ffc:
        jne short L_00416000
    L_00415ffe:
        mov dword ptr [edi],eax
    L_00416000:
        mov eax,dword ptr [ebp+5Ch]
    L_00416003:
        add eax,4
    L_00416006:
        call asm_Path_DecodeXor_00417010
    L_0041600b:
        mov ecx,dword ptr [ebp+84h]
    L_00416011:
        mov edx,dword ptr [ebp+ecx*4+88h]
    L_00416018:
        push eax
    L_00416019:
        mov eax,dword ptr [g_sprt_ctrl]
    L_0041601e:
        push edx
    L_0041601f:
        push eax
    L_00416020:
        call asm_Recovery_MarkLogState_00447a50
    L_00416025:
        add esp,0Ch
    L_00416028:
        mov eax,edi
    L_0041602a:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_0041602f:
        mov eax,ebx
    L_00416031:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_00416036:
        inc dword ptr [ebp+80h]
    L_0041603c:
        jmp asm_target_00416f09
    L_00416041:
        mov ecx,dword ptr [ebp+50h]
    L_00416044:
        mov ebx,dword ptr [g_sprt_ctrl]
    L_0041604a:
        lea edi,[ebp+50h]
    L_0041604d:
        push ecx
    L_0041604e:
        mov edx,ebx
    L_00416050:
        call asm_AnimationManager_Find_004491c0
    L_00416055:
        mov esi,eax
    L_00416057:
        test esi,esi
    L_00416059:
        jne short L_0041605d
    L_0041605b:
        mov dword ptr [edi],eax
    L_0041605d:
        mov eax,dword ptr [ebp+5Ch]
    L_00416060:
        add eax,4
    L_00416063:
        call asm_Path_DecodeXor_00417010
    L_00416068:
        mov edx,dword ptr [ebp+84h]
    L_0041606e:
        push eax
    L_0041606f:
        mov eax,dword ptr [ebp+edx*4+88h]
    L_00416076:
        push eax
    L_00416077:
        push ebx
    L_00416078:
        call asm_Recovery_MarkLogState_00447a50
    L_0041607d:
        add esp,0Ch
    L_00416080:
        mov eax,edi
    L_00416082:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_00416087:
        mov dword ptr [ebp+80h],0
    L_00416091:
        jmp asm_target_00416f09
    L_00416096:
        lea eax,[ebp+4Ch]
    L_00416099:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_0041609e:
        lea eax,[ebp+50h]
    L_004160a1:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_004160a6:
        jmp asm_target_00416f09
    L_004160ab:
        mov ecx,dword ptr [g_front]
    L_004160b1:
        mov eax,dword ptr [ecx+9EC8h]
    L_004160b7:
        push 0Fh
    L_004160b9:
        push 5Ah
    L_004160bb:
        push eax
    L_004160bc:
        lea edi,[esp+1Ch]
    L_004160c0:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004160c5:
        mov edx,dword ptr [eax]
    L_004160c7:
        mov dword ptr [ebp+48h],edx
    L_004160ca:
        jmp asm_target_00416f09
    L_004160cf:
        mov eax,dword ptr [data_00474c68]
    L_004160d4:
        sub eax,0
    L_004160d7:
        je short L_00416103
    L_004160d9:
        dec eax
    L_004160da:
        jne asm_target_00416f09
    L_004160e0:
        mov eax,dword ptr [g_player]
    L_004160e5:
        mov eax,dword ptr [eax+10h]
    L_004160e8:
        push 0Fh
    L_004160ea:
        push 1Dh
    L_004160ec:
        push eax
    L_004160ed:
        lea edi,[esp+0BCh]
    L_004160f4:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004160f9:
        mov ecx,dword ptr [eax]
    L_004160fb:
        mov dword ptr [ebp+40h],ecx
    L_004160fe:
        jmp asm_target_00416f09
    L_00416103:
        mov edx,dword ptr [g_player]
    L_00416109:
        mov eax,dword ptr [edx+10h]
    L_0041610c:
        push 0Fh
    L_0041610e:
        push 1Dh
    L_00416110:
        push eax
    L_00416111:
        lea edi,[esp+8Ch]
    L_00416118:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0041611d:
        mov eax,dword ptr [eax]
    L_0041611f:
        mov dword ptr [ebp+40h],eax
    L_00416122:
        jmp asm_target_00416f09
    L_00416127:
        mov eax,dword ptr [data_00474c7c]
    L_0041612c:
        cmp eax,6
    L_0041612f:
        jne short L_00416186
    L_00416131:
        mov eax,dword ptr [data_00474c68]
    L_00416136:
        sub eax,0
    L_00416139:
        je short L_00416163
    L_0041613b:
        dec eax
    L_0041613c:
        jne asm_target_00416f09
    L_00416142:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_00416148:
        mov eax,dword ptr [ecx+38h]
    L_0041614b:
        push 0Fh
    L_0041614d:
        push 20h
    L_0041614f:
        push eax
    L_00416150:
        lea edi,[esp+2Ch]
    L_00416154:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416159:
        mov edx,dword ptr [eax]
    L_0041615b:
        mov dword ptr [ebp+44h],edx
    L_0041615e:
        jmp asm_target_00416f09
    L_00416163:
        mov eax,dword ptr [g_enemy_ctrl]
    L_00416168:
        mov eax,dword ptr [eax+38h]
    L_0041616b:
        push 0Fh
    L_0041616d:
        push 20h
    L_0041616f:
        push eax
    L_00416170:
        lea edi,[esp+0E4h]
    L_00416177:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0041617c:
        mov ecx,dword ptr [eax]
    L_0041617e:
        mov dword ptr [ebp+44h],ecx
    L_00416181:
        jmp asm_target_00416f09
    L_00416186:
        cmp eax,7
    L_00416189:
        jne short L_004161e7
    L_0041618b:
        cmp dword ptr [ebp],1
    L_0041618f:
        jge short L_004161e7
    L_00416191:
        mov eax,dword ptr [data_00474c68]
    L_00416196:
        sub eax,0
    L_00416199:
        je short L_004161c3
    L_0041619b:
        dec eax
    L_0041619c:
        jne asm_target_00416f09
    L_004161a2:
        mov edx,dword ptr [g_enemy_ctrl]
    L_004161a8:
        mov eax,dword ptr [edx+38h]
    L_004161ab:
        push 0Fh
    L_004161ad:
        push 25h
    L_004161af:
        push eax
    L_004161b0:
        lea edi,[esp+34h]
    L_004161b4:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004161b9:
        mov eax,dword ptr [eax]
    L_004161bb:
        mov dword ptr [ebp+44h],eax
    L_004161be:
        jmp asm_target_00416f09
    L_004161c3:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_004161c9:
        mov eax,dword ptr [ecx+38h]
    L_004161cc:
        push 0Fh
    L_004161ce:
        push 25h
    L_004161d0:
        push eax
    L_004161d1:
        lea edi,[esp+94h]
    L_004161d8:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004161dd:
        mov edx,dword ptr [eax]
    L_004161df:
        mov dword ptr [ebp+44h],edx
    L_004161e2:
        jmp asm_target_00416f09
    L_004161e7:
        mov eax,dword ptr [data_00474c68]
    L_004161ec:
        sub eax,0
    L_004161ef:
        je short L_00416218
    L_004161f1:
        dec eax
    L_004161f2:
        jne asm_target_00416f09
    L_004161f8:
        mov eax,dword ptr [g_player]
    L_004161fd:
        mov eax,dword ptr [eax+10h]
    L_00416200:
        push 0Fh
    L_00416202:
        push 1Eh
    L_00416204:
        push eax
    L_00416205:
        lea edi,[esp+3Ch]
    L_00416209:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0041620e:
        mov ecx,dword ptr [eax]
    L_00416210:
        mov dword ptr [ebp+44h],ecx
    L_00416213:
        jmp asm_target_00416f09
    L_00416218:
        mov edx,dword ptr [g_player]
    L_0041621e:
        mov eax,dword ptr [edx+10h]
    L_00416221:
        push 0Fh
    L_00416223:
        push 1Eh
    L_00416225:
        push eax
    L_00416226:
        lea edi,[esp+0C4h]
    L_0041622d:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416232:
        mov eax,dword ptr [eax]
    L_00416234:
        mov dword ptr [ebp+44h],eax
    L_00416237:
        jmp asm_target_00416f09
    L_0041623c:
        lea eax,[ebp+40h]
    L_0041623f:
        mov esi,7
    L_00416244:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00416249:
        jmp asm_target_00416f09
    L_0041624e:
        lea eax,[ebp+44h]
    L_00416251:
        mov esi,7
    L_00416256:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_0041625b:
        jmp asm_target_00416f09
    L_00416260:
        lea esi,[ebp+40h]
    L_00416263:
        mov eax,esi
    L_00416265:
        call asm_FUN_00409e50_00409e50
    L_0041626a:
        mov dword ptr [esi],0
    L_00416270:
        jmp asm_target_00416f09
    L_00416275:
        lea esi,[ebp+44h]
    L_00416278:
        mov eax,esi
    L_0041627a:
        call asm_FUN_00409e50_00409e50
    L_0041627f:
        lea eax,[ebp+54h]
    L_00416282:
        mov dword ptr [esi],0
    L_00416288:
        call asm_FUN_00409e50_00409e50
    L_0041628d:
        jmp asm_target_00416f09
    L_00416292:
        lea eax,[ebp+48h]
    L_00416295:
        call asm_FUN_00409e50_00409e50
    L_0041629a:
        lea eax,[ebp+4Ch]
    L_0041629d:
        call asm_FUN_00409e50_00409e50
    L_004162a2:
        lea eax,[ebp+50h]
    L_004162a5:
        call asm_FUN_00409e50_00409e50
    L_004162aa:
        jmp asm_target_00416f09
    L_004162af:
        lea eax,[ebp+44h]
    L_004162b2:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_004162b7:
        lea eax,[ebp+40h]
    L_004162ba:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_004162bf:
        mov ecx,dword ptr [ebp+4Ch]
    L_004162c2:
        mov edi,dword ptr [g_sprt_ctrl]
    L_004162c8:
        xor ebx,ebx
    L_004162ca:
        lea esi,[ebp+60h]
    L_004162cd:
        push ecx
    L_004162ce:
        mov edx,edi
    L_004162d0:
        mov dword ptr [ebp+84h],ebx
    L_004162d6:
        call asm_AnimationManager_SetPosition_004492f0
    L_004162db:
        mov eax,dword ptr [ebp+84h]
    L_004162e1:
        add eax,8
    L_004162e4:
        lea edx,[eax+eax*2]
    L_004162e7:
        mov eax,dword ptr [ebp+50h]
    L_004162ea:
        lea esi,[ebp+edx*4]
    L_004162ee:
        push eax
    L_004162ef:
        mov edx,edi
    L_004162f1:
        call asm_AnimationManager_SetPosition_004492f0
    L_004162f6:
        mov dword ptr [ebp+80h],ebx
    L_004162fc:
        jmp asm_target_00416f09
    L_00416301:
        lea eax,[ebp+40h]
    L_00416304:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_00416309:
        lea eax,[ebp+44h]
    L_0041630c:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_00416311:
        mov ecx,dword ptr [ebp+4Ch]
    L_00416314:
        mov edi,dword ptr [g_sprt_ctrl]
    L_0041631a:
        lea esi,[ebp+6Ch]
    L_0041631d:
        push ecx
    L_0041631e:
        mov edx,edi
    L_00416320:
        mov dword ptr [ebp+84h],1
    L_0041632a:
        call asm_AnimationManager_SetPosition_004492f0
    L_0041632f:
        mov eax,dword ptr [ebp+84h]
    L_00416335:
        add eax,8
    L_00416338:
        lea edx,[eax+eax*2]
    L_0041633b:
        mov eax,dword ptr [ebp+50h]
    L_0041633e:
        lea esi,[ebp+edx*4]
    L_00416342:
        push eax
    L_00416343:
        mov edx,edi
    L_00416345:
        call asm_AnimationManager_SetPosition_004492f0
    L_0041634a:
        mov dword ptr [ebp+80h],0
    L_00416354:
        jmp asm_target_00416f09
    L_00416359:
        mov esi,dword ptr [ebp+7Ch]
    L_0041635c:
        xor ecx,ecx
    L_0041635e:
        mov cl,byte ptr [eax+4]
    L_00416361:
        mov eax,esi
    L_00416363:
        xor ecx,esi
    L_00416365:
        and ecx,1
    L_00416368:
        xor eax,ecx
    L_0041636a:
        mov dword ptr [ebp+7Ch],eax
    L_0041636d:
        jmp asm_target_00416f09
    L_00416372:
        mov ecx,dword ptr [data_00474c68]
    L_00416378:
        sub ecx,0
    L_0041637b:
        je short L_004163c6
    L_0041637d:
        dec ecx
    L_0041637e:
        jne asm_target_00416f09
    L_00416384:
        mov edx,dword ptr [eax+4]
    L_00416387:
        add edx,2Dh
    L_0041638a:
        lea esi,[ebp+40h]
    L_0041638d:
        push edx
    L_0041638e:
        mov ebx,17h
    L_00416393:
        lea edi,[esp+3Ch]
    L_00416397:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041639c:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_004163a1:
        mov eax,dword ptr [ebp+5Ch]
    L_004163a4:
        mov ecx,dword ptr [eax+4]
    L_004163a7:
        add ecx,35h
    L_004163aa:
        push ecx
    L_004163ab:
        mov ebx,1Ah
    L_004163b0:
        lea edi,[esp+94h]
    L_004163b7:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004163bc:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_004163c1:
        jmp asm_target_00416f09
    L_004163c6:
        mov edx,dword ptr [eax+4]
    L_004163c9:
        add edx,34h
    L_004163cc:
        lea esi,[ebp+40h]
    L_004163cf:
        push edx
    L_004163d0:
        mov ebx,17h
    L_004163d5:
        lea edi,[esp+44h]
    L_004163d9:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004163de:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_004163e3:
        mov eax,dword ptr [ebp+5Ch]
    L_004163e6:
        mov ecx,dword ptr [eax+4]
    L_004163e9:
        add ecx,3Ch
    L_004163ec:
        push ecx
    L_004163ed:
        mov ebx,1Ah
    L_004163f2:
        lea edi,[esp+0D4h]
    L_004163f9:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004163fe:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_00416403:
        jmp asm_target_00416f09
    L_00416408:
        mov ecx,dword ptr [data_00474c7c]
    L_0041640e:
        dec ecx
    L_0041640f:
        cmp ecx,6
    L_00416412:
        ja asm_target_00416f09
    L_00416418:
        jmp dword ptr [ecx*4+416FC4h]
    L_0041641f:
        mov ecx,dword ptr [data_00474c68]
    L_00416425:
        sub ecx,0
    L_00416428:
        je short L_00416487
    L_0041642a:
        dec ecx
    L_0041642b:
        jne asm_target_00416f09
    L_00416431:
        mov eax,dword ptr [eax+4]
    L_00416434:
        mov edx,dword ptr [g_enemy_ctrl]
    L_0041643a:
        mov ecx,dword ptr [edx+38h]
    L_0041643d:
        add eax,0Fh
    L_00416440:
        push eax
    L_00416441:
        lea esi,[ebp+44h]
    L_00416444:
        push ecx
    L_00416445:
        mov ebx,18h
    L_0041644a:
        lea edi,[esp+50h]
    L_0041644e:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416453:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416458:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_0041645e:
        mov eax,dword ptr [ecx+38h]
    L_00416461:
        mov edx,dword ptr [ebp+5Ch]
    L_00416464:
        mov ecx,dword ptr [edx+4]
    L_00416467:
        add ecx,17h
    L_0041646a:
        push ecx
    L_0041646b:
        push eax
    L_0041646c:
        mov ebx,1Bh
    L_00416471:
        lea edi,[esp+0A0h]
    L_00416478:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041647d:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416482:
        jmp asm_target_00416f09
    L_00416487:
        mov eax,dword ptr [eax+4]
    L_0041648a:
        mov edx,dword ptr [g_enemy_ctrl]
    L_00416490:
        mov ecx,dword ptr [edx+38h]
    L_00416493:
        add eax,0Fh
    L_00416496:
        push eax
    L_00416497:
        lea esi,[ebp+44h]
    L_0041649a:
        push ecx
    L_0041649b:
        mov ebx,18h
    L_004164a0:
        lea edi,[esp+58h]
    L_004164a4:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004164a9:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004164ae:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_004164b4:
        mov eax,dword ptr [ecx+38h]
    L_004164b7:
        mov edx,dword ptr [ebp+5Ch]
    L_004164ba:
        mov ecx,dword ptr [edx+4]
    L_004164bd:
        add ecx,17h
    L_004164c0:
        push ecx
    L_004164c1:
        push eax
    L_004164c2:
        mov ebx,1Bh
    L_004164c7:
        lea edi,[esp+0C8h]
    L_004164ce:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004164d3:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004164d8:
        jmp asm_target_00416f09
    L_004164dd:
        mov ecx,dword ptr [data_00474c68]
    L_004164e3:
        sub ecx,0
    L_004164e6:
        je short L_00416545
    L_004164e8:
        dec ecx
    L_004164e9:
        jne asm_target_00416f09
    L_004164ef:
        mov eax,dword ptr [eax+4]
    L_004164f2:
        mov edx,dword ptr [g_enemy_ctrl]
    L_004164f8:
        mov ecx,dword ptr [edx+38h]
    L_004164fb:
        add eax,15h
    L_004164fe:
        push eax
    L_004164ff:
        lea esi,[ebp+44h]
    L_00416502:
        push ecx
    L_00416503:
        mov ebx,18h
    L_00416508:
        lea edi,[esp+60h]
    L_0041650c:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416511:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416516:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_0041651c:
        mov eax,dword ptr [ecx+38h]
    L_0041651f:
        mov edx,dword ptr [ebp+5Ch]
    L_00416522:
        mov ecx,dword ptr [edx+4]
    L_00416525:
        add ecx,1Eh
    L_00416528:
        push ecx
    L_00416529:
        push eax
    L_0041652a:
        mov ebx,1Bh
    L_0041652f:
        lea edi,[esp+0A8h]
    L_00416536:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041653b:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416540:
        jmp asm_target_00416f09
    L_00416545:
        mov eax,dword ptr [eax+4]
    L_00416548:
        mov edx,dword ptr [g_enemy_ctrl]
    L_0041654e:
        mov ecx,dword ptr [edx+38h]
    L_00416551:
        add eax,15h
    L_00416554:
        push eax
    L_00416555:
        lea esi,[ebp+44h]
    L_00416558:
        push ecx
    L_00416559:
        mov ebx,18h
    L_0041655e:
        lea edi,[esp+68h]
    L_00416562:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416567:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041656c:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_00416572:
        mov eax,dword ptr [ecx+38h]
    L_00416575:
        mov edx,dword ptr [ebp+5Ch]
    L_00416578:
        mov ecx,dword ptr [edx+4]
    L_0041657b:
        add ecx,1Eh
    L_0041657e:
        push ecx
    L_0041657f:
        push eax
    L_00416580:
        mov ebx,1Bh
    L_00416585:
        lea edi,[esp+0E8h]
    L_0041658c:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416591:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416596:
        jmp asm_target_00416f09
    L_0041659b:
        mov ecx,dword ptr [data_00474c68]
    L_004165a1:
        sub ecx,0
    L_004165a4:
        je short L_00416603
    L_004165a6:
        dec ecx
    L_004165a7:
        jne asm_target_00416f09
    L_004165ad:
        mov eax,dword ptr [eax+4]
    L_004165b0:
        mov edx,dword ptr [g_enemy_ctrl]
    L_004165b6:
        mov ecx,dword ptr [edx+38h]
    L_004165b9:
        add eax,22h
    L_004165bc:
        push eax
    L_004165bd:
        lea esi,[ebp+44h]
    L_004165c0:
        push ecx
    L_004165c1:
        mov ebx,18h
    L_004165c6:
        lea edi,[esp+70h]
    L_004165ca:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004165cf:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004165d4:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_004165da:
        mov eax,dword ptr [ecx+38h]
    L_004165dd:
        mov edx,dword ptr [ebp+5Ch]
    L_004165e0:
        mov ecx,dword ptr [edx+4]
    L_004165e3:
        add ecx,2Bh
    L_004165e6:
        push ecx
    L_004165e7:
        push eax
    L_004165e8:
        mov ebx,1Bh
    L_004165ed:
        lea edi,[esp+0B0h]
    L_004165f4:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004165f9:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004165fe:
        jmp asm_target_00416f09
    L_00416603:
        mov eax,dword ptr [eax+4]
    L_00416606:
        mov edx,dword ptr [g_enemy_ctrl]
    L_0041660c:
        mov ecx,dword ptr [edx+38h]
    L_0041660f:
        add eax,22h
    L_00416612:
        push eax
    L_00416613:
        lea esi,[ebp+44h]
    L_00416616:
        push ecx
    L_00416617:
        mov ebx,18h
    L_0041661c:
        lea edi,[esp+78h]
    L_00416620:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416625:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041662a:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_00416630:
        mov eax,dword ptr [ecx+38h]
    L_00416633:
        mov edx,dword ptr [ebp+5Ch]
    L_00416636:
        mov ecx,dword ptr [edx+4]
    L_00416639:
        add ecx,2Bh
    L_0041663c:
        push ecx
    L_0041663d:
        push eax
    L_0041663e:
        mov ebx,1Bh
    L_00416643:
        lea edi,[esp+0D0h]
    L_0041664a:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041664f:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416654:
        jmp asm_target_00416f09
    L_00416659:
        mov ecx,dword ptr [data_00474c68]
    L_0041665f:
        sub ecx,0
    L_00416662:
        je short L_004166c1
    L_00416664:
        dec ecx
    L_00416665:
        jne asm_target_00416f09
    L_0041666b:
        mov eax,dword ptr [eax+4]
    L_0041666e:
        mov edx,dword ptr [g_enemy_ctrl]
    L_00416674:
        mov ecx,dword ptr [edx+38h]
    L_00416677:
        add eax,25h
    L_0041667a:
        push eax
    L_0041667b:
        lea esi,[ebp+44h]
    L_0041667e:
        push ecx
    L_0041667f:
        mov ebx,18h
    L_00416684:
        lea edi,[esp+80h]
    L_0041668b:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416690:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416695:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_0041669b:
        mov eax,dword ptr [ecx+38h]
    L_0041669e:
        mov edx,dword ptr [ebp+5Ch]
    L_004166a1:
        mov ecx,dword ptr [edx+4]
    L_004166a4:
        add ecx,2Eh
    L_004166a7:
        push ecx
    L_004166a8:
        push eax
    L_004166a9:
        mov ebx,1Bh
    L_004166ae:
        lea edi,[esp+1Ch]
    L_004166b2:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004166b7:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004166bc:
        jmp asm_target_00416f09
    L_004166c1:
        mov eax,dword ptr [eax+4]
    L_004166c4:
        mov edx,dword ptr [g_enemy_ctrl]
    L_004166ca:
        mov ecx,dword ptr [edx+38h]
    L_004166cd:
        add eax,25h
    L_004166d0:
        push eax
    L_004166d1:
        lea esi,[ebp+44h]
    L_004166d4:
        push ecx
    L_004166d5:
        mov ebx,18h
    L_004166da:
        lea edi,[esp+20h]
    L_004166de:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004166e3:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004166e8:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_004166ee:
        mov eax,dword ptr [ecx+38h]
    L_004166f1:
        mov edx,dword ptr [ebp+5Ch]
    L_004166f4:
        mov ecx,dword ptr [edx+4]
    L_004166f7:
        add ecx,2Eh
    L_004166fa:
        push ecx
    L_004166fb:
        push eax
    L_004166fc:
        mov ebx,1Bh
    L_00416701:
        lea edi,[esp+24h]
    L_00416705:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041670a:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041670f:
        jmp asm_target_00416f09
    L_00416714:
        mov ecx,dword ptr [data_00474c68]
    L_0041671a:
        sub ecx,0
    L_0041671d:
        je short L_00416779
    L_0041671f:
        dec ecx
    L_00416720:
        jne asm_target_00416f09
    L_00416726:
        mov eax,dword ptr [eax+4]
    L_00416729:
        mov edx,dword ptr [g_enemy_ctrl]
    L_0041672f:
        mov ecx,dword ptr [edx+38h]
    L_00416732:
        add eax,16h
    L_00416735:
        push eax
    L_00416736:
        lea esi,[ebp+44h]
    L_00416739:
        push ecx
    L_0041673a:
        mov ebx,18h
    L_0041673f:
        lea edi,[esp+2Ch]
    L_00416743:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416748:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041674d:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_00416753:
        mov eax,dword ptr [ecx+38h]
    L_00416756:
        mov edx,dword ptr [ebp+5Ch]
    L_00416759:
        mov ecx,dword ptr [edx+4]
    L_0041675c:
        add ecx,1Fh
    L_0041675f:
        push ecx
    L_00416760:
        push eax
    L_00416761:
        mov ebx,1Bh
    L_00416766:
        lea edi,[esp+34h]
    L_0041676a:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041676f:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416774:
        jmp asm_target_00416f09
    L_00416779:
        mov eax,dword ptr [eax+4]
    L_0041677c:
        mov edx,dword ptr [g_enemy_ctrl]
    L_00416782:
        mov ecx,dword ptr [edx+38h]
    L_00416785:
        add eax,16h
    L_00416788:
        push eax
    L_00416789:
        lea esi,[ebp+44h]
    L_0041678c:
        push ecx
    L_0041678d:
        mov ebx,18h
    L_00416792:
        lea edi,[esp+3Ch]
    L_00416796:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041679b:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004167a0:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_004167a6:
        mov eax,dword ptr [ecx+38h]
    L_004167a9:
        mov edx,dword ptr [ebp+5Ch]
    L_004167ac:
        mov ecx,dword ptr [edx+4]
    L_004167af:
        add ecx,1Fh
    L_004167b2:
        push ecx
    L_004167b3:
        push eax
    L_004167b4:
        mov ebx,1Bh
    L_004167b9:
        lea edi,[esp+44h]
    L_004167bd:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004167c2:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004167c7:
        jmp asm_target_00416f09
    L_004167cc:
        mov ecx,dword ptr [data_00474c68]
    L_004167d2:
        sub ecx,0
    L_004167d5:
        je short L_00416831
    L_004167d7:
        dec ecx
    L_004167d8:
        jne asm_target_00416f09
    L_004167de:
        mov eax,dword ptr [eax+4]
    L_004167e1:
        mov edx,dword ptr [g_enemy_ctrl]
    L_004167e7:
        mov ecx,dword ptr [edx+38h]
    L_004167ea:
        add eax,30h
    L_004167ed:
        push eax
    L_004167ee:
        lea esi,[ebp+44h]
    L_004167f1:
        push ecx
    L_004167f2:
        mov ebx,1Ch
    L_004167f7:
        lea edi,[esp+4Ch]
    L_004167fb:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416800:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416805:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_0041680b:
        mov eax,dword ptr [ecx+38h]
    L_0041680e:
        mov edx,dword ptr [ebp+5Ch]
    L_00416811:
        mov ecx,dword ptr [edx+4]
    L_00416814:
        add ecx,39h
    L_00416817:
        push ecx
    L_00416818:
        push eax
    L_00416819:
        mov ebx,1Fh
    L_0041681e:
        lea edi,[esp+54h]
    L_00416822:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416827:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041682c:
        jmp asm_target_00416f09
    L_00416831:
        mov eax,dword ptr [eax+4]
    L_00416834:
        mov edx,dword ptr [g_enemy_ctrl]
    L_0041683a:
        mov ecx,dword ptr [edx+38h]
    L_0041683d:
        add eax,30h
    L_00416840:
        push eax
    L_00416841:
        lea esi,[ebp+44h]
    L_00416844:
        push ecx
    L_00416845:
        mov ebx,1Ch
    L_0041684a:
        lea edi,[esp+5Ch]
    L_0041684e:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416853:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416858:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_0041685e:
        mov eax,dword ptr [ecx+38h]
    L_00416861:
        mov edx,dword ptr [ebp+5Ch]
    L_00416864:
        mov ecx,dword ptr [edx+4]
    L_00416867:
        add ecx,39h
    L_0041686a:
        push ecx
    L_0041686b:
        push eax
    L_0041686c:
        mov ebx,1Fh
    L_00416871:
        lea edi,[esp+64h]
    L_00416875:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041687a:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041687f:
        jmp asm_target_00416f09
    L_00416884:
        cmp dword ptr [ebp],1
    L_00416888:
        mov ecx,dword ptr [data_00474c68]
    L_0041688e:
        jge asm_target_00416949
    L_00416894:
        sub ecx,0
    L_00416897:
        je short L_004168f3
    L_00416899:
        dec ecx
    L_0041689a:
        jne asm_target_00416f09
    L_004168a0:
        mov eax,dword ptr [eax+4]
    L_004168a3:
        mov edx,dword ptr [g_enemy_ctrl]
    L_004168a9:
        mov ecx,dword ptr [edx+38h]
    L_004168ac:
        add eax,44h
    L_004168af:
        push eax
    L_004168b0:
        lea esi,[ebp+44h]
    L_004168b3:
        push ecx
    L_004168b4:
        mov ebx,21h
    L_004168b9:
        lea edi,[esp+6Ch]
    L_004168bd:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004168c2:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004168c7:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_004168cd:
        mov eax,dword ptr [ecx+38h]
    L_004168d0:
        mov edx,dword ptr [ebp+5Ch]
    L_004168d3:
        mov ecx,dword ptr [edx+4]
    L_004168d6:
        add ecx,4Dh
    L_004168d9:
        push ecx
    L_004168da:
        push eax
    L_004168db:
        mov ebx,24h
    L_004168e0:
        lea edi,[esp+74h]
    L_004168e4:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004168e9:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004168ee:
        jmp asm_target_00416f09
    L_004168f3:
        mov eax,dword ptr [eax+4]
    L_004168f6:
        mov edx,dword ptr [g_enemy_ctrl]
    L_004168fc:
        mov ecx,dword ptr [edx+38h]
    L_004168ff:
        add eax,44h
    L_00416902:
        push eax
    L_00416903:
        lea esi,[ebp+44h]
    L_00416906:
        push ecx
    L_00416907:
        mov ebx,21h
    L_0041690c:
        lea edi,[esp+7Ch]
    L_00416910:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416915:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041691a:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_00416920:
        mov eax,dword ptr [ecx+38h]
    L_00416923:
        mov edx,dword ptr [ebp+5Ch]
    L_00416926:
        mov ecx,dword ptr [edx+4]
    L_00416929:
        add ecx,4Dh
    L_0041692c:
        push ecx
    L_0041692d:
        push eax
    L_0041692e:
        mov ebx,24h
    L_00416933:
        lea edi,[esp+84h]
    L_0041693a:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041693f:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416944:
        jmp asm_target_00416f09
    L_00416949:
        sub ecx,0
    L_0041694c:
        je short L_004169ae
    L_0041694e:
        dec ecx
    L_0041694f:
        jne asm_target_00416f09
    L_00416955:
        mov eax,dword ptr [eax+4]
    L_00416958:
        mov edx,dword ptr [g_enemy_ctrl]
    L_0041695e:
        mov ecx,dword ptr [edx+38h]
    L_00416961:
        add eax,2Eh
    L_00416964:
        push eax
    L_00416965:
        lea esi,[ebp+44h]
    L_00416968:
        push ecx
    L_00416969:
        mov ebx,18h
    L_0041696e:
        lea edi,[esp+8Ch]
    L_00416975:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041697a:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041697f:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_00416985:
        mov eax,dword ptr [ecx+38h]
    L_00416988:
        mov edx,dword ptr [ebp+5Ch]
    L_0041698b:
        mov ecx,dword ptr [edx+4]
    L_0041698e:
        add ecx,37h
    L_00416991:
        push ecx
    L_00416992:
        push eax
    L_00416993:
        mov ebx,1Bh
    L_00416998:
        lea edi,[esp+94h]
    L_0041699f:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004169a4:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004169a9:
        jmp asm_target_00416f09
    L_004169ae:
        mov eax,dword ptr [eax+4]
    L_004169b1:
        mov edx,dword ptr [g_enemy_ctrl]
    L_004169b7:
        mov ecx,dword ptr [edx+38h]
    L_004169ba:
        add eax,2Eh
    L_004169bd:
        push eax
    L_004169be:
        lea esi,[ebp+44h]
    L_004169c1:
        push ecx
    L_004169c2:
        mov ebx,18h
    L_004169c7:
        lea edi,[esp+9Ch]
    L_004169ce:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004169d3:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004169d8:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_004169de:
        mov eax,dword ptr [ecx+38h]
    L_004169e1:
        mov edx,dword ptr [ebp+5Ch]
    L_004169e4:
        mov ecx,dword ptr [edx+4]
    L_004169e7:
        add ecx,37h
    L_004169ea:
        push ecx
    L_004169eb:
        push eax
    L_004169ec:
        mov ebx,1Bh
    L_004169f1:
        lea edi,[esp+0A4h]
    L_004169f8:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004169fd:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416a02:
        jmp asm_target_00416f09
    L_00416a07:
        mov ecx,dword ptr [ebp+30h]
    L_00416a0a:
        xor ebx,ebx
    L_00416a0c:
        cmp ecx,ebx
    L_00416a0e:
        jg short L_00416a1c
    L_00416a10:
        mov edx,dword ptr [eax+4]
    L_00416a13:
        push edx
    L_00416a14:
        lea eax,[ebp+2Ch]
    L_00416a17:
        call asm_Player_SetSchedulerValue_00405410
    L_00416a1c:
        lea esi,[ebp+2Ch]
    L_00416a1f:
        push 0BF800000h
    L_00416a24:
        call asm_FrameTimer_Advance_0044bf40
    L_00416a29:
        test dword ptr [data_00474e62],1001h
    L_00416a33:
        jne short L_00416a65
    L_00416a35:
        cmp dword ptr [ebp+30h],ebx
    L_00416a38:
        jle short L_00416a65
    L_00416a3a:
        test byte ptr [ebp+7Ch],1
    L_00416a3e:
        je asm_target_00416f2d
    L_00416a44:
        mov eax,dword ptr [g_input]
    L_00416a49:
        test ah,1
    L_00416a4c:
        je asm_target_00416f2d
    L_00416a52:
        push ebx
    L_00416a53:
        mov eax,esi
    L_00416a55:
        call asm_Player_SetSchedulerValue_00405410
    L_00416a5a:
        mov dword ptr [ebp+80h],ebx
    L_00416a60:
        jmp asm_target_00416f09
    L_00416a65:
        push ebx
    L_00416a66:
        xor edi,edi
    L_00416a68:
        mov ecx,492590h
    L_00416a6d:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00416a72:
        push ebx
    L_00416a73:
        mov eax,esi
    L_00416a75:
        call asm_Player_SetSchedulerValue_00405410
    L_00416a7a:
        mov dword ptr [ebp+80h],ebx
    L_00416a80:
        jmp asm_target_00416f09
    L_00416a85:
        mov dword ptr [ebp+78h],1
    L_00416a8c:
        jmp asm_target_00416f09
    L_00416a91:
        mov eax,dword ptr [data_00477848]
    L_00416a96:
        mov ecx,dword ptr [eax+28h]
    L_00416a99:
        push ecx
    L_00416a9a:
        push 1
    L_00416a9c:
        call asm_Sound_PlayDummyRetail_00420b10
    L_00416aa1:
        mov edx,dword ptr [g_front]
    L_00416aa7:
        mov eax,dword ptr [edx+9E80h]
    L_00416aad:
        push 0Fh
    L_00416aaf:
        push 2
    L_00416ab1:
        push eax
    L_00416ab2:
        lea edi,[esp+0B0h]
    L_00416ab9:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416abe:
        jmp asm_target_00416f09
    L_00416ac3:
        mov eax,dword ptr [data_00474c7c]
    L_00416ac8:
        dec eax
    L_00416ac9:
        cmp eax,6
    L_00416acc:
        ja asm_target_00416f09
    L_00416ad2:
        jmp dword ptr [eax*4+416FE0h]
    L_00416ad9:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_00416adf:
        mov eax,dword ptr [ecx+38h]
    L_00416ae2:
        push 0Fh
    L_00416ae4:
        push 0Dh
    L_00416ae6:
        push eax
    L_00416ae7:
        lea edi,[esp+0B8h]
    L_00416aee:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416af3:
        mov edx,dword ptr [eax]
    L_00416af5:
        mov dword ptr [ebp+54h],edx
    L_00416af8:
        jmp asm_target_00416f09
    L_00416afd:
        mov eax,dword ptr [g_enemy_ctrl]
    L_00416b02:
        mov eax,dword ptr [eax+38h]
    L_00416b05:
        push 0Fh
    L_00416b07:
        push 10h
    L_00416b09:
        push eax
    L_00416b0a:
        lea edi,[esp+0C0h]
    L_00416b11:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416b16:
        mov ecx,dword ptr [eax]
    L_00416b18:
        mov dword ptr [ebp+54h],ecx
    L_00416b1b:
        jmp asm_target_00416f09
    L_00416b20:
        mov edx,dword ptr [g_enemy_ctrl]
    L_00416b26:
        mov eax,dword ptr [edx+38h]
    L_00416b29:
        push 0Fh
    L_00416b2b:
        push 14h
    L_00416b2d:
        push eax
    L_00416b2e:
        lea edi,[esp+0C8h]
    L_00416b35:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416b3a:
        mov eax,dword ptr [eax]
    L_00416b3c:
        mov dword ptr [ebp+54h],eax
    L_00416b3f:
        jmp asm_target_00416f09
    L_00416b44:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_00416b4a:
        mov eax,dword ptr [ecx+38h]
    L_00416b4d:
        push 0Fh
    L_00416b4f:
        push 15h
    L_00416b51:
        push eax
    L_00416b52:
        lea edi,[esp+0D0h]
    L_00416b59:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416b5e:
        mov edx,dword ptr [eax]
    L_00416b60:
        mov dword ptr [ebp+54h],edx
    L_00416b63:
        jmp asm_target_00416f09
    L_00416b68:
        mov eax,dword ptr [g_enemy_ctrl]
    L_00416b6d:
        mov eax,dword ptr [eax+38h]
    L_00416b70:
        push 0Fh
    L_00416b72:
        push 0Eh
    L_00416b74:
        push eax
    L_00416b75:
        lea edi,[esp+0D8h]
    L_00416b7c:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416b81:
        mov ecx,dword ptr [eax]
    L_00416b83:
        mov dword ptr [ebp+54h],ecx
    L_00416b86:
        jmp asm_target_00416f09
    L_00416b8b:
        mov edx,dword ptr [g_enemy_ctrl]
    L_00416b91:
        mov eax,dword ptr [edx+38h]
    L_00416b94:
        push 0Fh
    L_00416b96:
        push 23h
    L_00416b98:
        push eax
    L_00416b99:
        lea edi,[esp+0E0h]
    L_00416ba0:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416ba5:
        mov eax,dword ptr [eax]
    L_00416ba7:
        mov dword ptr [ebp+54h],eax
    L_00416baa:
        jmp asm_target_00416f09
    L_00416baf:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_00416bb5:
        mov eax,dword ptr [ecx+38h]
    L_00416bb8:
        push 0Fh
    L_00416bba:
        push 1Dh
    L_00416bbc:
        push eax
    L_00416bbd:
        lea edi,[esp+0E8h]
    L_00416bc4:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416bc9:
        mov edx,dword ptr [eax]
    L_00416bcb:
        mov dword ptr [ebp+54h],edx
    L_00416bce:
        jmp asm_target_00416f09
    L_00416bd3:
        mov ecx,dword ptr [data_00474c74]
    L_00416bd9:
        cmp ecx,4
    L_00416bdc:
        je short L_00416c3d
    L_00416bde:
        mov eax,dword ptr [data_00474c68]
    L_00416be3:
        mov edx,dword ptr [data_00474c6c]
    L_00416be9:
        lea edx,[edx+eax*2]
    L_00416bec:
        add edx,eax
    L_00416bee:
        imul edx,437Ch
    L_00416bf4:
        lea eax,[ecx+ecx*2]
    L_00416bf7:
        mov ecx,dword ptr [data_00474c7c]
    L_00416bfd:
        lea eax,[ecx+eax*2]
    L_00416c00:
        mov ecx,dword ptr [data_0047783c]
    L_00416c06:
        add edx,ecx
    L_00416c08:
        mov byte ptr [edx+eax*8+4E1h],1
    L_00416c10:
        mov eax,dword ptr [data_00474c74]
    L_00416c15:
        mov esi,dword ptr [data_00474c6c]
    L_00416c1b:
        lea edx,[eax+eax*2+4Eh]
    L_00416c1f:
        mov eax,dword ptr [data_00474c7c]
    L_00416c24:
        lea edx,[eax+edx*2]
    L_00416c27:
        mov eax,dword ptr [data_00474c68]
    L_00416c2c:
        lea esi,[esi+eax*2]
    L_00416c2f:
        add esi,eax
    L_00416c31:
        imul esi,437Ch
    L_00416c37:
        add esi,ecx
    L_00416c39:
        mov byte ptr [esi+edx*8],1
    L_00416c3d:
        test byte ptr [data_00474ca0],10h
    L_00416c44:
        je short L_00416c56
    L_00416c46:
        mov edi,dword ptr [g_pause]
    L_00416c4c:
        call asm_FUN_00423370_00423370
    L_00416c51:
        jmp asm_target_00416f09
    L_00416c56:
        mov eax,dword ptr [data_00474c7c]
    L_00416c5b:
        cmp eax,6
    L_00416c5e:
        jne asm_target_00416de8
    L_00416c64:
        mov eax,dword ptr [g_front]
    L_00416c69:
        or dword ptr [eax+9EB4h],20h
    L_00416c70:
        mov eax,dword ptr [data_00474c4c]
    L_00416c75:
        imul eax,3E8h
    L_00416c7b:
        push eax
    L_00416c7c:
        mov ecx,474C40h
    L_00416c81:
        call asm_AddScaled_GameScore_00409d90
    L_00416c86:
        mov eax,dword ptr [data_00474c74]
    L_00416c8b:
        cmp eax,4
    L_00416c8e:
        ja asm_target_00416d66
    L_00416c94:
        jmp dword ptr [eax*4+416FFCh]
    L_00416c9b:
        mov ecx,dword ptr [data_00474c70]
    L_00416ca1:
        imul ecx,1312D00h
    L_00416ca7:
        push ecx
    L_00416ca8:
        mov ecx,474C40h
    L_00416cad:
        call asm_AddScaled_GameScore_00409d90
    L_00416cb2:
        movsx edx,word ptr [data_00474c48]
    L_00416cb9:
        imul edx,186A0h
    L_00416cbf:
        push edx
    L_00416cc0:
        jmp asm_target_00416d5c
    L_00416cc5:
        mov eax,dword ptr [data_00474c70]
    L_00416cca:
        imul eax,17D7840h
    L_00416cd0:
        push eax
    L_00416cd1:
        mov ecx,474C40h
    L_00416cd6:
        call asm_AddScaled_GameScore_00409d90
    L_00416cdb:
        movsx ecx,word ptr [data_00474c48]
    L_00416ce2:
        imul ecx,186A0h
    L_00416ce8:
        jmp short L_00416d5b
    L_00416cea:
        mov edx,dword ptr [data_00474c70]
    L_00416cf0:
        imul edx,2160EC0h
    L_00416cf6:
        push edx
    L_00416cf7:
        mov ecx,474C40h
    L_00416cfc:
        call asm_AddScaled_GameScore_00409d90
    L_00416d01:
        movsx eax,word ptr [data_00474c48]
    L_00416d08:
        imul eax,30D40h
    L_00416d0e:
        push eax
    L_00416d0f:
        jmp short L_00416d5c
    L_00416d11:
        mov ecx,dword ptr [data_00474c70]
    L_00416d17:
        imul ecx,2625A00h
    L_00416d1d:
        push ecx
    L_00416d1e:
        mov ecx,474C40h
    L_00416d23:
        call asm_AddScaled_GameScore_00409d90
    L_00416d28:
        movsx edx,word ptr [data_00474c48]
    L_00416d2f:
        imul edx,493E0h
    L_00416d35:
        push edx
    L_00416d36:
        jmp short L_00416d5c
    L_00416d38:
        mov eax,dword ptr [data_00474c70]
    L_00416d3d:
        imul eax,2625A00h
    L_00416d43:
        push eax
    L_00416d44:
        mov ecx,474C40h
    L_00416d49:
        call asm_AddScaled_GameScore_00409d90
    L_00416d4e:
        movsx ecx,word ptr [data_00474c48]
    L_00416d55:
        imul ecx,61A80h
    L_00416d5b:
        push ecx
    L_00416d5c:
        mov ecx,474C40h
    L_00416d61:
        call asm_AddScaled_GameScore_00409d90
    L_00416d66:
        mov edx,dword ptr [data_00477838]
    L_00416d6c:
        cmp dword ptr [edx+10h],1
    L_00416d70:
        je asm_target_00416e8a
    L_00416d76:
        push 0
    L_00416d78:
        push 0
    L_00416d7a:
        push 0
    L_00416d7c:
        push 78h
    L_00416d7e:
        push 5
    L_00416d80:
        mov ebx,31h
    L_00416d85:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_00416d8a:
        mov eax,dword ptr [g_front]
    L_00416d8f:
        mov ebx,dword ptr [eax+9EB4h]
    L_00416d95:
        mov dword ptr [eax+9ECCh],0
    L_00416d9f:
        or ebx,10h
    L_00416da2:
        mov dword ptr [eax+9EB4h],ebx
    L_00416da8:
        mov eax,dword ptr [data_00474c68]
    L_00416dad:
        mov ecx,dword ptr [data_00474c6c]
    L_00416db3:
        mov esi,dword ptr [data_00474c74]
    L_00416db9:
        lea edx,[ecx+eax*2]
    L_00416dbc:
        add edx,eax
    L_00416dbe:
        mov eax,dword ptr [data_0047783c]
    L_00416dc3:
        imul edx,10DFh
    L_00416dc9:
        add edx,esi
    L_00416dcb:
        lea eax,[eax+edx*4+4D0h]
    L_00416dd2:
        mov ecx,dword ptr [eax]
    L_00416dd4:
        cmp ecx,1869Fh
    L_00416dda:
        jge asm_target_00416f09
    L_00416de0:
        inc ecx
    L_00416de1:
        mov dword ptr [eax],ecx
    L_00416de3:
        jmp asm_target_00416f09
    L_00416de8:
        cmp eax,7
    L_00416deb:
        jne asm_target_00416e98
    L_00416df1:
        mov eax,dword ptr [g_front]
    L_00416df6:
        or dword ptr [eax+9EB4h],20h
    L_00416dfd:
        mov ecx,dword ptr [data_00474c4c]
    L_00416e03:
        imul ecx,3E8h
    L_00416e09:
        push ecx
    L_00416e0a:
        mov ecx,474C40h
    L_00416e0f:
        call asm_AddScaled_GameScore_00409d90
    L_00416e14:
        mov edx,dword ptr [data_00474c70]
    L_00416e1a:
        imul edx,2625A00h
    L_00416e20:
        push edx
    L_00416e21:
        mov ecx,474C40h
    L_00416e26:
        call asm_AddScaled_GameScore_00409d90
    L_00416e2b:
        movsx eax,word ptr [data_00474c48]
    L_00416e32:
        imul eax,61A80h
    L_00416e38:
        push eax
    L_00416e39:
        mov ecx,474C40h
    L_00416e3e:
        call asm_AddScaled_GameScore_00409d90
    L_00416e43:
        mov ecx,dword ptr [data_00477838]
    L_00416e49:
        cmp dword ptr [ecx+10h],1
    L_00416e4d:
        je short L_00416e8a
    L_00416e4f:
        mov edi,dword ptr [g_pause]
    L_00416e55:
        call asm_FUN_00423370_00423370
    L_00416e5a:
        mov eax,dword ptr [data_00474c68]
    L_00416e5f:
        mov edx,dword ptr [data_00474c6c]
    L_00416e65:
        lea ecx,[edx+eax*2]
    L_00416e68:
        mov edx,dword ptr [data_00474c74]
    L_00416e6e:
        add ecx,eax
    L_00416e70:
        imul ecx,10DFh
    L_00416e76:
        add ecx,edx
    L_00416e78:
        mov edx,dword ptr [data_0047783c]
    L_00416e7e:
        lea eax,[edx+ecx*4+4D0h]
    L_00416e85:
        jmp asm_target_00416dd2
    L_00416e8a:
        push 4
    L_00416e8c:
        mov eax,491C28h
    L_00416e91:
        call asm_SetInputMode_0040ac90
    L_00416e96:
        jmp short L_00416f09
    L_00416e98:
        mov edi,dword ptr [g_front]
    L_00416e9e:
        mov eax,dword ptr [edi+9E14h]
    L_00416ea4:
        mov edx,dword ptr [g_sprt_ctrl]
    L_00416eaa:
        lea esi,[edi+9E14h]
    L_00416eb0:
        push eax
    L_00416eb1:
        call asm_AnimationManager_SetFlag_004492a0
    L_00416eb6:
        push 0Fh
    L_00416eb8:
        mov dword ptr [esi],0
    L_00416ebe:
        mov ecx,dword ptr [edi+9EC8h]
    L_00416ec4:
        push 4Ch
    L_00416ec6:
        push ecx
    L_00416ec7:
        lea edi,[esp+0F0h]
    L_00416ece:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416ed3:
        mov edx,dword ptr [eax]
    L_00416ed5:
        push 0Bh
    L_00416ed7:
        mov eax,491C28h
    L_00416edc:
        mov dword ptr [esi],edx
    L_00416ede:
        call asm_SetInputMode_0040ac90
    L_00416ee3:
        mov eax,474C40h
    L_00416ee8:
        call asm_FUN_004175e0_004175e0
    L_00416eed:
        jmp short L_00416f09
    L_00416eef:
        cmp dword ptr [data_00474c7c],6
    L_00416ef6:
        je short L_00416eff
    L_00416ef8:
        push 40000000h
    L_00416efd:
        jmp short L_00416f04
    L_00416eff:
        push 41000000h
    L_00416f04:
        call asm_Sound_PlayRandomVoiceRetail_00420c30
    L_00416f09:
        mov eax,dword ptr [ebp+5Ch]
    L_00416f0c:
        movzx ecx,byte ptr [eax+3]
    L_00416f10:
        lea edx,[ecx+eax+4]
    L_00416f14:
        mov eax,edx
    L_00416f16:
        mov dword ptr [ebp+5Ch],edx
    L_00416f19:
        movzx ecx,word ptr [eax]
    L_00416f1c:
        cmp dword ptr [ebp+1Ch],ecx
    L_00416f1f:
        jge asm_target_00415f06
    L_00416f25:
        lea esi,[ebp+18h]
    L_00416f28:
        call asm_FrameTimer_Tick_00404ed0
    L_00416f2d:
        pop edi
    L_00416f2e:
        pop esi
    L_00416f2f:
        pop ebp
    L_00416f30:
        xor eax,eax
    L_00416f32:
        pop ebx
    L_00416f33:
        add esp,0D8h
    L_00416f39:
        ret 4
    L_00416f3c:
        mov ecx,dword ptr [data_00474c84]
    L_00416f42:
        xor eax,eax
    L_00416f44:
        cmp ecx,eax
    L_00416f46:
        je short L_00416f4d
    L_00416f48:
        mov dword ptr [data_00474c8c],eax
    L_00416f4d:
        pop edi
    L_00416f4e:
        pop esi
    L_00416f4f:
        pop ebp
    L_00416f50:
        mov dword ptr [data_00474c84],eax
    L_00416f55:
        or eax,0FFFFFFFFh
    L_00416f58:
        pop ebx
    L_00416f59:
        add esp,0D8h
    L_00416f5f:
        ret 4
        _emit 0x8b
        _emit 0xff
        _emit 0x3c
        _emit 0x6f
        _emit 0x41
        _emit 0x00
        _emit 0xcf
        _emit 0x60
        _emit 0x41
        _emit 0x00
        _emit 0x27
        _emit 0x61
        _emit 0x41
        _emit 0x00
        _emit 0xab
        _emit 0x60
        _emit 0x41
        _emit 0x00
        _emit 0x60
        _emit 0x62
        _emit 0x41
        _emit 0x00
        _emit 0x75
        _emit 0x62
        _emit 0x41
        _emit 0x00
        _emit 0x92
        _emit 0x62
        _emit 0x41
        _emit 0x00
        _emit 0xaf
        _emit 0x62
        _emit 0x41
        _emit 0x00
        _emit 0x01
        _emit 0x63
        _emit 0x41
        _emit 0x00
        _emit 0x59
        _emit 0x63
        _emit 0x41
        _emit 0x00
        _emit 0x07
        _emit 0x6a
        _emit 0x41
        _emit 0x00
        _emit 0x85
        _emit 0x6a
        _emit 0x41
        _emit 0x00
        _emit 0x72
        _emit 0x63
        _emit 0x41
        _emit 0x00
        _emit 0x08
        _emit 0x64
        _emit 0x41
        _emit 0x00
        _emit 0x1d
        _emit 0x5f
        _emit 0x41
        _emit 0x00
        _emit 0x22
        _emit 0x5f
        _emit 0x41
        _emit 0x00
        _emit 0x6c
        _emit 0x5f
        _emit 0x41
        _emit 0x00
        _emit 0x96
        _emit 0x60
        _emit 0x41
        _emit 0x00
        _emit 0x91
        _emit 0x6a
        _emit 0x41
        _emit 0x00
        _emit 0xc3
        _emit 0x6a
        _emit 0x41
        _emit 0x00
        _emit 0xd3
        _emit 0x6b
        _emit 0x41
        _emit 0x00
        _emit 0xef
        _emit 0x6e
        _emit 0x41
        _emit 0x00
        _emit 0x3c
        _emit 0x62
        _emit 0x41
        _emit 0x00
        _emit 0x4e
        _emit 0x62
        _emit 0x41
        _emit 0x00
        _emit 0x1f
        _emit 0x64
        _emit 0x41
        _emit 0x00
        _emit 0xdd
        _emit 0x64
        _emit 0x41
        _emit 0x00
        _emit 0x9b
        _emit 0x65
        _emit 0x41
        _emit 0x00
        _emit 0x59
        _emit 0x66
        _emit 0x41
        _emit 0x00
        _emit 0x14
        _emit 0x67
        _emit 0x41
        _emit 0x00
        _emit 0xcc
        _emit 0x67
        _emit 0x41
        _emit 0x00
        _emit 0x84
        _emit 0x68
        _emit 0x41
        _emit 0x00
        _emit 0xd9
        _emit 0x6a
        _emit 0x41
        _emit 0x00
        _emit 0xfd
        _emit 0x6a
        _emit 0x41
        _emit 0x00
        _emit 0x20
        _emit 0x6b
        _emit 0x41
        _emit 0x00
        _emit 0x44
        _emit 0x6b
        _emit 0x41
        _emit 0x00
        _emit 0x68
        _emit 0x6b
        _emit 0x41
        _emit 0x00
        _emit 0x8b
        _emit 0x6b
        _emit 0x41
        _emit 0x00
        _emit 0xaf
        _emit 0x6b
        _emit 0x41
        _emit 0x00
        _emit 0x9b
        _emit 0x6c
        _emit 0x41
        _emit 0x00
        _emit 0xc5
        _emit 0x6c
        _emit 0x41
        _emit 0x00
        _emit 0xea
        _emit 0x6c
        _emit 0x41
        _emit 0x00
        _emit 0x11
        _emit 0x6d
        _emit 0x41
        _emit 0x00
        _emit 0x38
        _emit 0x6d
        _emit 0x41
        _emit 0x00
    }
}

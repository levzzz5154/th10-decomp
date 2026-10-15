#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"

// BLOCKED (D3901): closest_byte_count=0/1568; first_diff=unmeasured;
// residual_class=private stack-state receiver, jump-table command dispatch,
// animation/text helper ABIs, and the real caller's ESI handoff. variants_tested=
// exact retail assembly probe (1568/1568), caller topology at 0x0040BD20,
// legacy partial event-script model, and the existing synthetic schema-1
// FrameTimer context; no schema-2 readable candidate was retained.
// next_lever=schema-2/native-LTCG cluster with real caller 0x0040BD20 and
// helpers 0x00405410/0x0040C480/0x0040C4D0/0x00417010/0x0043C8B0/
// 0x00447A50/0x00449630 co-compiled.
// 0x0040BD80..0x0040BDD9: FUN_0040bd80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040bd80_0040bd80() {
    __asm {
    L_0040bd80:
        sub esp,0Ch
    L_0040bd83:
        push ebp
    L_0040bd84:
        mov ebp,dword ptr [esp+14h]
    L_0040bd88:
        mov eax,dword ptr [ebp+74h]
    L_0040bd8b:
        test al,4
    L_0040bd8d:
        je short L_0040bd98
    L_0040bd8f:
        xor eax,eax
    L_0040bd91:
        pop ebp
    L_0040bd92:
        add esp,0Ch
    L_0040bd95:
        ret 4
    L_0040bd98:
        mov ecx,dword ptr [g_ending]
    L_0040bd9e:
        test byte ptr [ecx+20h],1
    L_0040bda2:
        jne short L_0040bdc6
    L_0040bda4:
        test al,2
    L_0040bda6:
        jne short L_0040bdc6
    L_0040bda8:
        mov ecx,dword ptr [g_input_keys_raw]
    L_0040bdae:
        test ch,1
    L_0040bdb1:
        je short L_0040bdc6
    L_0040bdb3:
        test al,1
    L_0040bdb5:
        je short L_0040bdc6
    L_0040bdb7:
        mov edx,dword ptr [ebp+54h]
    L_0040bdba:
        movzx eax,word ptr [edx]
    L_0040bdbd:
        push eax
    L_0040bdbe:
        lea eax,[ebp+18h]
    L_0040bdc1:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bdc6:
        mov ecx,dword ptr [ebp+54h]
    L_0040bdc9:
        movzx edx,word ptr [ecx]
    L_0040bdcc:
        cmp dword ptr [ebp+1Ch],edx
    L_0040bdcf:
        push ebx
    L_0040bdd0:
        push esi
    L_0040bdd1:
        push edi
    L_0040bdd2:
        jl asm_target_0040c27c
    L_0040bdd8:
        TH10_REL8(0xeb, 0x0040bdd8, VA_asm_FUN_0040bd80_part_0040bde0)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0040bde0:
        mov eax,dword ptr [ebp+54h]
    L_0040bde3:
        movzx ecx,byte ptr [eax+2]
    L_0040bde7:
        cmp ecx,11h
    L_0040bdea:
        ja asm_target_0040c25f
    L_0040bdf0:
        jmp dword ptr [ecx*4+40C358h]
    L_0040bdf7:
        mov ecx,dword ptr [ebp+78h]
    L_0040bdfa:
        test ecx,ecx
    L_0040bdfc:
        jne asm_target_0040be8c
    L_0040be02:
        lea edi,[ebp+40h]
    L_0040be05:
        mov ebx,5
    L_0040be0a:
        lea ebx,[ebx+force_disp32_zero]
    L_0040be10:
        mov eax,dword ptr [edi]
    L_0040be12:
        mov esi,dword ptr [g_sprt_ctrl]
    L_0040be18:
        push eax
    L_0040be19:
        mov edx,esi
    L_0040be1b:
        call asm_AnimationManager_Find_004491c0
    L_0040be20:
        test eax,eax
    L_0040be22:
        jne short L_0040be26
    L_0040be24:
        mov dword ptr [edi],eax
    L_0040be26:
        push 46CFD4h
    L_0040be2b:
        push 0FFFFFFh
    L_0040be30:
        push esi
    L_0040be31:
        mov esi,eax
    L_0040be33:
        call asm_Recovery_MarkLogState_00447a50
    L_0040be38:
        add esp,0Ch
    L_0040be3b:
        mov eax,edi
    L_0040be3d:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_0040be42:
        add edi,4
    L_0040be45:
        dec ebx
    L_0040be46:
        jne short L_0040be10
    L_0040be48:
        mov ecx,dword ptr [ebp+40h]
    L_0040be4b:
        mov ebx,dword ptr [g_sprt_ctrl]
    L_0040be51:
        lea edi,[ebp+40h]
    L_0040be54:
        push ecx
    L_0040be55:
        mov edx,ebx
    L_0040be57:
        call asm_AnimationManager_Find_004491c0
    L_0040be5c:
        mov esi,eax
    L_0040be5e:
        test esi,esi
    L_0040be60:
        jne short L_0040be64
    L_0040be62:
        mov dword ptr [edi],eax
    L_0040be64:
        mov eax,dword ptr [ebp+54h]
    L_0040be67:
        add eax,4
    L_0040be6a:
        call asm_Path_DecodeXor_00417010
    L_0040be6f:
        mov edx,dword ptr [ebp+7Ch]
    L_0040be72:
        push eax
    L_0040be73:
        push edx
    L_0040be74:
        push ebx
    L_0040be75:
        call asm_Recovery_MarkLogState_00447a50
    L_0040be7a:
        add esp,0Ch
    L_0040be7d:
        mov eax,edi
    L_0040be7f:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_0040be84:
        inc dword ptr [ebp+78h]
    L_0040be87:
        jmp asm_target_0040c25f
    L_0040be8c:
        add eax,4
    L_0040be8f:
        call asm_Path_DecodeXor_00417010
    L_0040be94:
        mov ecx,dword ptr [ebp+78h]
    L_0040be97:
        push eax
    L_0040be98:
        mov eax,dword ptr [ebp+7Ch]
    L_0040be9b:
        push eax
    L_0040be9c:
        lea esi,[ebp+ecx*4+40h]
    L_0040bea0:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0040bea5:
        mov edx,dword ptr [g_sprt_ctrl]
    L_0040beab:
        push edx
    L_0040beac:
        mov esi,eax
    L_0040beae:
        call asm_Recovery_MarkLogState_00447a50
    L_0040beb3:
        mov eax,dword ptr [ebp+78h]
    L_0040beb6:
        add esp,0Ch
    L_0040beb9:
        lea eax,[ebp+eax*4+40h]
    L_0040bebd:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_0040bec2:
        mov ecx,dword ptr [ebp+78h]
    L_0040bec5:
        inc ecx
    L_0040bec6:
        mov eax,ecx
    L_0040bec8:
        cmp eax,5
    L_0040becb:
        mov dword ptr [ebp+78h],ecx
    L_0040bece:
        jl asm_target_0040c25f
    L_0040bed4:
        mov dword ptr [ebp+78h],0
    L_0040bedb:
        jmp asm_target_0040c25f
    L_0040bee0:
        lea esi,[ebp+40h]
    L_0040bee3:
        mov edi,5
    L_0040bee8:
        mov eax,esi
    L_0040beea:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_0040beef:
        add esi,4
    L_0040bef2:
        dec edi
    L_0040bef3:
        jne short L_0040bee8
    L_0040bef5:
        jmp asm_target_0040c25f
    L_0040befa:
        mov ecx,dword ptr [ebp+30h]
    L_0040befd:
        test ecx,ecx
    L_0040beff:
        jg short L_0040bf0d
    L_0040bf01:
        mov ecx,dword ptr [eax+4]
    L_0040bf04:
        push ecx
    L_0040bf05:
        lea eax,[ebp+2Ch]
    L_0040bf08:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bf0d:
        lea esi,[ebp+2Ch]
    L_0040bf10:
        push 0BF800000h
    L_0040bf15:
        call asm_FrameTimer_Advance_0044bf40
    L_0040bf1a:
        mov edx,dword ptr [ebp+54h]
    L_0040bf1d:
        mov eax,dword ptr [edx+4]
    L_0040bf20:
        test eax,eax
    L_0040bf22:
        jge short L_0040bf30
    L_0040bf24:
        push 3E7h
    L_0040bf29:
        mov eax,esi
    L_0040bf2b:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bf30:
        test dword ptr [g_input_keys_held],1001h
    L_0040bf3a:
        jne short L_0040bf7f
    L_0040bf3c:
        mov eax,dword ptr [ebp+30h]
    L_0040bf3f:
        test eax,eax
    L_0040bf41:
        jle short L_0040bf7f
    L_0040bf43:
        mov ecx,dword ptr [g_ending]
    L_0040bf49:
        test byte ptr [ecx+20h],1
    L_0040bf4d:
        jne asm_target_0040c34a
    L_0040bf53:
        mov ecx,dword ptr [g_input_keys_raw]
    L_0040bf59:
        test ch,1
    L_0040bf5c:
        je asm_target_0040c34a
    L_0040bf62:
        cdq
    L_0040bf63:
        mov ecx,6
    L_0040bf68:
        idiv ecx
    L_0040bf6a:
        test edx,edx
    L_0040bf6c:
        jne asm_target_0040c34a
    L_0040bf72:
        push edx
    L_0040bf73:
        mov eax,esi
    L_0040bf75:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bf7a:
        jmp asm_target_0040c25f
    L_0040bf7f:
        push 0
    L_0040bf81:
        xor edi,edi
    L_0040bf83:
        mov ecx,492590h
    L_0040bf88:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0040bf8d:
        push edi
    L_0040bf8e:
        mov eax,esi
    L_0040bf90:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bf95:
        jmp asm_target_0040c25f
    L_0040bf9a:
        mov ecx,dword ptr [ebp+30h]
    L_0040bf9d:
        xor ebx,ebx
    L_0040bf9f:
        cmp ecx,ebx
    L_0040bfa1:
        jg short L_0040bfaf
    L_0040bfa3:
        mov edx,dword ptr [eax+4]
    L_0040bfa6:
        push edx
    L_0040bfa7:
        lea eax,[ebp+2Ch]
    L_0040bfaa:
        call asm_Player_SetSchedulerValue_00405410
    L_0040bfaf:
        lea esi,[ebp+2Ch]
    L_0040bfb2:
        push 0BF800000h
    L_0040bfb7:
        call asm_FrameTimer_Advance_0044bf40
    L_0040bfbc:
        test dword ptr [g_input_keys_held],1001h
    L_0040bfc6:
        jne short L_0040c000
    L_0040bfc8:
        mov eax,dword ptr [ebp+30h]
    L_0040bfcb:
        cmp eax,ebx
    L_0040bfcd:
        jle short L_0040c000
    L_0040bfcf:
        mov ecx,dword ptr [g_ending]
    L_0040bfd5:
        test byte ptr [ecx+20h],1
    L_0040bfd9:
        jne asm_target_0040c34a
    L_0040bfdf:
        mov ecx,dword ptr [g_input_keys_raw]
    L_0040bfe5:
        test ch,1
    L_0040bfe8:
        je asm_target_0040c34a
    L_0040bfee:
        cdq
    L_0040bfef:
        mov ecx,6
    L_0040bff4:
        idiv ecx
    L_0040bff6:
        test edx,edx
    L_0040bff8:
        jne asm_target_0040c34a
    L_0040bffe:
        jmp short L_0040c00d
    L_0040c000:
        push ebx
    L_0040c001:
        xor edi,edi
    L_0040c003:
        mov ecx,492590h
    L_0040c008:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0040c00d:
        push ebx
    L_0040c00e:
        mov eax,esi
    L_0040c010:
        call asm_Player_SetSchedulerValue_00405410
    L_0040c015:
        mov dword ptr [ebp+78h],ebx
    L_0040c018:
        mov dword ptr [g_screen_effects_frozen],ebx
    L_0040c01e:
        jmp asm_target_0040c25f
    L_0040c023:
        mov edx,dword ptr [eax+4]
    L_0040c026:
        mov eax,dword ptr [ebp+edx*4+90h]
    L_0040c02d:
        lea esi,[ebp+edx*4+90h]
    L_0040c034:
        mov edx,dword ptr [g_sprt_ctrl]
    L_0040c03a:
        push eax
    L_0040c03b:
        call asm_AnimationManager_SetFlag_004492a0
    L_0040c040:
        mov dword ptr [esi],0
    L_0040c046:
        mov eax,dword ptr [ebp+54h]
    L_0040c049:
        mov ecx,dword ptr [eax+0Ch]
    L_0040c04c:
        mov edx,dword ptr [eax+8]
    L_0040c04f:
        mov eax,dword ptr [ebp+edx*4+80h]
    L_0040c056:
        push 0Fh
    L_0040c058:
        push ecx
    L_0040c059:
        push eax
    L_0040c05a:
        lea edi,[esp+2Ch]
    L_0040c05e:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0040c063:
        mov ecx,dword ptr [ebp+54h]
    L_0040c066:
        mov edx,dword ptr [ecx+4]
    L_0040c069:
        mov eax,dword ptr [eax]
    L_0040c06b:
        mov dword ptr [ebp+edx*4+90h],eax
    L_0040c072:
        jmp asm_target_0040c25f
    L_0040c077:
        cmp dword ptr [g_globals_difficulty],1
    L_0040c07e:
        jne asm_target_0040c25f
    L_0040c084:
        mov ecx,dword ptr [eax+4]
    L_0040c087:
        lea esi,[ebp+ecx*4+90h]
    L_0040c08e:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_0040c093:
        mov eax,dword ptr [ebp+54h]
    L_0040c096:
        mov edx,dword ptr [eax+0Ch]
    L_0040c099:
        mov eax,dword ptr [eax+8]
    L_0040c09c:
        mov ecx,dword ptr [ebp+eax*4+80h]
    L_0040c0a3:
        push 0Fh
    L_0040c0a5:
        push edx
    L_0040c0a6:
        push ecx
    L_0040c0a7:
        lea edi,[esp+1Ch]
    L_0040c0ab:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0040c0b0:
        mov edx,dword ptr [ebp+54h]
    L_0040c0b3:
        mov ecx,dword ptr [edx+4]
    L_0040c0b6:
        mov edx,dword ptr [eax]
    L_0040c0b8:
        mov dword ptr [ebp+ecx*4+90h],edx
    L_0040c0bf:
        jmp asm_target_0040c25f
    L_0040c0c4:
        cmp dword ptr [g_globals_difficulty],2
    L_0040c0cb:
        jne asm_target_0040c25f
    L_0040c0d1:
        mov eax,dword ptr [eax+4]
    L_0040c0d4:
        lea esi,[ebp+eax*4+90h]
    L_0040c0db:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_0040c0e0:
        mov eax,dword ptr [ebp+54h]
    L_0040c0e3:
        mov ecx,dword ptr [eax+0Ch]
    L_0040c0e6:
        mov edx,dword ptr [eax+8]
    L_0040c0e9:
        mov eax,dword ptr [ebp+edx*4+80h]
    L_0040c0f0:
        push 0Fh
    L_0040c0f2:
        push ecx
    L_0040c0f3:
        push eax
    L_0040c0f4:
        lea edi,[esp+20h]
    L_0040c0f8:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0040c0fd:
        mov ecx,dword ptr [ebp+54h]
    L_0040c100:
        mov edx,dword ptr [ecx+4]
    L_0040c103:
        mov eax,dword ptr [eax]
    L_0040c105:
        mov dword ptr [ebp+edx*4+90h],eax
    L_0040c10c:
        jmp asm_target_0040c25f
    L_0040c111:
        cmp dword ptr [g_globals_difficulty],3
    L_0040c118:
        jne asm_target_0040c25f
    L_0040c11e:
        mov ecx,dword ptr [eax+4]
    L_0040c121:
        lea esi,[ebp+ecx*4+90h]
    L_0040c128:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_0040c12d:
        mov eax,dword ptr [ebp+54h]
    L_0040c130:
        mov edx,dword ptr [eax+0Ch]
    L_0040c133:
        mov eax,dword ptr [eax+8]
    L_0040c136:
        mov ecx,dword ptr [ebp+eax*4+80h]
    L_0040c13d:
        push 0Fh
    L_0040c13f:
        push edx
    L_0040c140:
        push ecx
    L_0040c141:
        lea edi,[esp+24h]
    L_0040c145:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0040c14a:
        mov edx,dword ptr [ebp+54h]
    L_0040c14d:
        mov ecx,dword ptr [edx+4]
    L_0040c150:
        mov edx,dword ptr [eax]
    L_0040c152:
        mov dword ptr [ebp+ecx*4+90h],edx
    L_0040c159:
        jmp asm_target_0040c25f
    L_0040c15e:
        mov eax,dword ptr [eax+4]
    L_0040c161:
        mov dword ptr [ebp+7Ch],eax
    L_0040c164:
        jmp asm_target_0040c25f
    L_0040c169:
        add eax,4
    L_0040c16c:
        push eax
    L_0040c16d:
        push 0
    L_0040c16f:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_0040c174:
        mov esi,dword ptr [ebp+54h]
    L_0040c177:
        add esi,4
    L_0040c17a:
        mov edi,46CFC4h
    L_0040c17f:
        mov ecx,10h
    L_0040c184:
        xor edx,edx
    L_0040c186:
        repe cmpsb
    L_0040c188:
        jne short L_0040c197
    L_0040c18a:
        push 0Fh
    L_0040c18c:
        push edx
    L_0040c18d:
        call asm_Sound_PlayDummyRetail_00420b10
    L_0040c192:
        jmp asm_target_0040c25f
    L_0040c197:
        push 10h
    L_0040c199:
        push 0
    L_0040c19b:
        call asm_Sound_PlayDummyRetail_00420b10
    L_0040c1a0:
        jmp asm_target_0040c25f
    L_0040c1a5:
        push 40400000h
    L_0040c1aa:
        call asm_Sound_PlayRandomVoiceRetail_00420c30
    L_0040c1af:
        and dword ptr [ebp+74h],0FFFFFFFEh
    L_0040c1b3:
        jmp asm_target_0040c25f
    L_0040c1b8:
        mov ebx,dword ptr [g_sprt_ctrl]
    L_0040c1be:
        lea esi,[ebp+40h]
    L_0040c1c1:
        mov edi,5
    L_0040c1c6:
        mov eax,dword ptr [esi]
    L_0040c1c8:
        push eax
    L_0040c1c9:
        mov edx,ebx
    L_0040c1cb:
        call asm_AnimationManager_SetFlag_004492a0
    L_0040c1d0:
        mov dword ptr [esi],0
    L_0040c1d6:
        add esi,4
    L_0040c1d9:
        dec edi
    L_0040c1da:
        jne short L_0040c1c6
    L_0040c1dc:
        mov eax,dword ptr [ebp+54h]
    L_0040c1df:
        mov ecx,dword ptr [g_ending]
    L_0040c1e5:
        add eax,4
    L_0040c1e8:
        push ecx
    L_0040c1e9:
        call asm_FUN_0040b480_0040b480
    L_0040c1ee:
        mov edx,eax
    L_0040c1f0:
        test edx,edx
    L_0040c1f2:
        je asm_target_0040c2c7
    L_0040c1f8:
        xor eax,eax
    L_0040c1fa:
        mov ecx,3Bh
    L_0040c1ff:
        mov edi,ebp
    L_0040c201:
        rep stosd
    L_0040c203:
        mov eax,dword ptr [edx+4]
    L_0040c206:
        add eax,edx
    L_0040c208:
        mov dword ptr [ebp+54h],eax
    L_0040c20b:
        push 0
    L_0040c20d:
        lea eax,[ebp+4]
    L_0040c210:
        call asm_Player_SetSchedulerValue_00405410
    L_0040c215:
        push 0
    L_0040c217:
        lea eax,[ebp+18h]
    L_0040c21a:
        call asm_Player_SetSchedulerValue_00405410
    L_0040c21f:
        push 0
    L_0040c221:
        lea eax,[ebp+2Ch]
    L_0040c224:
        call asm_Player_SetSchedulerValue_00405410
    L_0040c229:
        mov eax,dword ptr [ebp+74h]
    L_0040c22c:
        or eax,2
    L_0040c22f:
        mov dword ptr [ebp+7Ch],0FFFFFFh
    L_0040c236:
        mov dword ptr [ebp+74h],eax
    L_0040c239:
        jmp short L_0040c26d
    L_0040c23b:
        mov ecx,dword ptr [eax+4]
    L_0040c23e:
        push 0
    L_0040c240:
        push 0
    L_0040c242:
        push 0
    L_0040c244:
        push ecx
    L_0040c245:
        push 0
    L_0040c247:
        jmp short L_0040c255
    L_0040c249:
        mov edx,dword ptr [eax+4]
    L_0040c24c:
        push 0
    L_0040c24e:
        push 0
    L_0040c250:
        push 0
    L_0040c252:
        push edx
    L_0040c253:
        push 5
    L_0040c255:
        mov ebx,31h
    L_0040c25a:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_0040c25f:
        mov eax,dword ptr [ebp+54h]
    L_0040c262:
        movzx ecx,byte ptr [eax+3]
    L_0040c266:
        lea edx,[ecx+eax+4]
    L_0040c26a:
        mov dword ptr [ebp+54h],edx
    L_0040c26d:
        mov eax,dword ptr [ebp+54h]
    L_0040c270:
        movzx ecx,word ptr [eax]
    L_0040c273:
        cmp dword ptr [ebp+1Ch],ecx
    L_0040c276:
        jge asm_FUN_0040bd80_part_0040bde0
    L_0040c27c:
        mov edx,dword ptr [ebp+1Ch]
    L_0040c27f:
        mov ecx,dword ptr [ebp+24h]
    L_0040c282:
        mov dword ptr [ebp+18h],edx
    L_0040c285:
        fld dword ptr [ecx]
    L_0040c287:
        fcomp dword ptr [flt_0_99]
    L_0040c28d:
        fnstsw ax
    L_0040c28f:
        test ah,41h
    L_0040c292:
        jne asm_target_0040c33a
    L_0040c298:
        fld dword ptr [ecx]
    L_0040c29a:
        fcomp dword ptr [flt_1_01]
    L_0040c2a0:
        fnstsw ax
    L_0040c2a2:
        test ah,5
    L_0040c2a5:
        jp asm_target_0040c33a
    L_0040c2ab:
        fld dword ptr [ebp+20h]
    L_0040c2ae:
        pop edi
    L_0040c2af:
        fadd dword ptr [flt_1]
    L_0040c2b5:
        pop esi
    L_0040c2b6:
        inc edx
    L_0040c2b7:
        pop ebx
    L_0040c2b8:
        fstp dword ptr [ebp+20h]
    L_0040c2bb:
        mov dword ptr [ebp+1Ch],edx
    L_0040c2be:
        xor eax,eax
    L_0040c2c0:
        pop ebp
    L_0040c2c1:
        add esp,0Ch
    L_0040c2c4:
        ret 4
    L_0040c2c7:
        pop edi
    L_0040c2c8:
        pop esi
    L_0040c2c9:
        pop ebx
    L_0040c2ca:
        or eax,0FFFFFFFFh
    L_0040c2cd:
        pop ebp
    L_0040c2ce:
        add esp,0Ch
    L_0040c2d1:
        ret 4
    L_0040c2d4:
        mov esi,dword ptr [g_ascii_manager]
    L_0040c2da:
        push 43C40000h
    L_0040c2df:
        push 43F00000h
    L_0040c2e4:
        call asm_FUN_0040c540_0040c540
    L_0040c2e9:
        mov edx,dword ptr [ebp+54h]
    L_0040c2ec:
        mov esi,dword ptr [edx+4]
    L_0040c2ef:
        mov ebx,dword ptr [g_sprt_ctrl]
    L_0040c2f5:
        add esi,1Dh
    L_0040c2f8:
        call asm_AnimationManager_ClearResourceSlot_004477d0
    L_0040c2fd:
        mov eax,dword ptr [ebp+54h]
    L_0040c300:
        mov edx,dword ptr [ebp+74h]
    L_0040c303:
        add eax,8
    L_0040c306:
        or edx,4
    L_0040c309:
        mov dword ptr [ebp+70h],eax
    L_0040c30c:
        push ebp
    L_0040c30d:
        lea eax,[ebp+0D0h]
    L_0040c313:
        mov edi,40C3A0h
    L_0040c318:
        mov dword ptr [ebp+74h],edx
    L_0040c31b:
        call asm_FUN_0044c1c0_0044c1c0
    L_0040c320:
        mov eax,dword ptr [ebp+54h]
    L_0040c323:
        movzx ecx,byte ptr [eax+3]
    L_0040c327:
        pop edi
    L_0040c328:
        pop esi
    L_0040c329:
        lea edx,[ecx+eax+4]
    L_0040c32d:
        pop ebx
    L_0040c32e:
        mov dword ptr [ebp+54h],edx
    L_0040c331:
        xor eax,eax
    L_0040c333:
        pop ebp
    L_0040c334:
        add esp,0Ch
    L_0040c337:
        ret 4
    L_0040c33a:
        fld dword ptr [ecx]
    L_0040c33c:
        fadd dword ptr [ebp+20h]
    L_0040c33f:
        fst dword ptr [ebp+20h]
    L_0040c342:
        call asm_FUN_00463b2c_00463b2c
    L_0040c347:
        mov dword ptr [ebp+1Ch],eax
    L_0040c34a:
        pop edi
    L_0040c34b:
        pop esi
    L_0040c34c:
        pop ebx
    L_0040c34d:
        xor eax,eax
    L_0040c34f:
        pop ebp
    L_0040c350:
        add esp,0Ch
    L_0040c353:
        ret 4
        _emit 0x8b
        _emit 0xff
        _emit 0xc7
        _emit 0xc2
        _emit 0x40
        _emit 0x00
        _emit 0x5f
        _emit 0xc2
        _emit 0x40
        _emit 0x00
        _emit 0x5f
        _emit 0xc2
        _emit 0x40
        _emit 0x00
        _emit 0xf7
        _emit 0xbd
        _emit 0x40
        _emit 0x00
        _emit 0xe0
        _emit 0xbe
        _emit 0x40
        _emit 0x00
        _emit 0xfa
        _emit 0xbe
        _emit 0x40
        _emit 0x00
        _emit 0x9a
        _emit 0xbf
        _emit 0x40
        _emit 0x00
        _emit 0xd4
        _emit 0xc2
        _emit 0x40
        _emit 0x00
        _emit 0x23
        _emit 0xc0
        _emit 0x40
        _emit 0x00
        _emit 0x5e
        _emit 0xc1
        _emit 0x40
        _emit 0x00
        _emit 0x69
        _emit 0xc1
        _emit 0x40
        _emit 0x00
        _emit 0xa5
        _emit 0xc1
        _emit 0x40
        _emit 0x00
        _emit 0xb8
        _emit 0xc1
        _emit 0x40
        _emit 0x00
        _emit 0x3b
        _emit 0xc2
        _emit 0x40
        _emit 0x00
        _emit 0x49
        _emit 0xc2
        _emit 0x40
        _emit 0x00
        _emit 0x77
        _emit 0xc0
        _emit 0x40
        _emit 0x00
        _emit 0xc4
        _emit 0xc0
        _emit 0x40
        _emit 0x00
        _emit 0x11
        _emit 0xc1
        _emit 0x40
        _emit 0x00
    }
}

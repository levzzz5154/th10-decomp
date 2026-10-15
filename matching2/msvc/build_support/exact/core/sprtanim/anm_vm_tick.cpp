// BLOCKED (D2401): retail region=9964 bytes; the live Ghidra body spans
// 0x0043EE30..0x004413A2, followed in the region by alignment and its
// 94-entry opcode table. The boundary is one stack object pointer/RET 4; the
// body itself is a 532-block interpreter with 203 direct
// calls and x87/EAX/ECX/EDX/EDI helper ABIs. The legacy semantic model uses a
// separate hook-driven state object and cannot be installed as this body.
// See anm_vm_tick_0043ee30_dependency_audit.md for the verified call graph,
// state flow, and smallest useful conversion cluster.
// next_lever=convert the complete dispatcher and its nonstandard helper call
// surfaces as one semantic cluster; individual opcode cases share PC, timing,
// interrupt, and frame-update paths and are not independent cut points.
#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"


// Ghidra body 0x0043EE30..0x004413A2; RET 4 at 0x004413A0.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043ee30_0043ee30() {
    __asm {
    L_0043ee30:
        sub esp,0FCh
    L_0043ee36:
        push ebp
    L_0043ee37:
        mov ebp,dword ptr [esp+104h]
    L_0043ee3e:
        mov eax,dword ptr [ebp+390h]
    L_0043ee44:
        test eax,eax
    L_0043ee46:
        jne short L_0043ee57
    L_0043ee48:
        mov eax,1
    L_0043ee4d:
        pop ebp
    L_0043ee4e:
        add esp,0FCh
    L_0043ee54:
        ret 4
    L_0043ee57:
        mov eax,dword ptr [ebp+35Ch]
    L_0043ee5d:
        test eax,20000h
    L_0043ee62:
        je short L_0043ee70
    L_0043ee64:
        xor eax,eax
    L_0043ee66:
        pop ebp
    L_0043ee67:
        add esp,0FCh
    L_0043ee6d:
        ret 4
    L_0043ee70:
        test eax,20000000h
    L_0043ee75:
        mov ecx,dword ptr [g_game_speed]
    L_0043ee7b:
        mov dword ptr [esp+98h],ecx
    L_0043ee82:
        je short L_0043ee8e
    L_0043ee84:
        mov dword ptr [g_game_speed],3F800000h
    L_0043ee8e:
        mov ax,word ptr [ebp+304h]
    L_0043ee95:
        push ebx
    L_0043ee96:
        push esi
    L_0043ee97:
        push edi
    L_0043ee98:
        or edi,0FFFFFFFFh
    L_0043ee9b:
        test ax,ax
    L_0043ee9e:
        jne asm_target_0043f62d
    L_0043eea4:
        mov ebx,dword ptr [ebp+390h]
    L_0043eeaa:
        movsx edx,word ptr [ebx+4]
    L_0043eeae:
        cmp edx,dword ptr [ebp+60h]
    L_0043eeb1:
        jg asm_target_00440e42
    L_0043eeb7:
        movsx eax,word ptr [ebx]
    L_0043eeba:
        inc eax
    L_0043eebb:
        cmp eax,5Dh
    L_0043eebe:
        ja asm_target_0043f532
    L_0043eec4:
        jmp dword ptr [eax*4+4413A4h]
    L_0043eecb:
        test byte ptr [ebx+6],1
    L_0043eecf:
        mov eax,dword ptr [ebx+8]
    L_0043eed2:
        je short L_0043eedb
    L_0043eed4:
        mov ecx,ebp
    L_0043eed6:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043eedb:
        mov esi,dword ptr [ebp+35Ch]
    L_0043eee1:
        shl eax,1Dh
    L_0043eee4:
        xor eax,esi
    L_0043eee6:
        and eax,20000000h
    L_0043eeeb:
        mov ecx,esi
    L_0043eeed:
        xor ecx,eax
    L_0043eeef:
        mov dword ptr [ebp+35Ch],ecx
    L_0043eef5:
        movzx edx,word ptr [ebx+2]
    L_0043eef9:
        add edx,ebx
    L_0043eefb:
        mov dword ptr [ebp+390h],edx
    L_0043ef01:
        or edi,0FFFFFFFFh
    L_0043ef04:
        jmp short L_0043eea4
    L_0043ef06:
        test byte ptr [ebx+6],1
    L_0043ef0a:
        mov eax,dword ptr [ebx+8]
    L_0043ef0d:
        je short L_0043ef16
    L_0043ef0f:
        mov ecx,ebp
    L_0043ef11:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043ef16:
        mov ecx,dword ptr [ebp+20h]
    L_0043ef19:
        mov edx,dword ptr [ebp+308h]
    L_0043ef1f:
        push ecx
    L_0043ef20:
        push eax
    L_0043ef21:
        push edx
    L_0043ef22:
        lea edi,[esp+0F0h]
    L_0043ef29:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0043ef2e:
        mov esi,edi
    L_0043ef30:
        jmp short L_0043ef88
    L_0043ef32:
        test byte ptr [ebx+6],1
    L_0043ef36:
        mov eax,dword ptr [ebx+8]
    L_0043ef39:
        je short L_0043ef42
    L_0043ef3b:
        mov ecx,ebp
    L_0043ef3d:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043ef42:
        mov edx,dword ptr [ebp+20h]
    L_0043ef45:
        push edx
    L_0043ef46:
        push eax
    L_0043ef47:
        mov eax,dword ptr [ebp+308h]
    L_0043ef4d:
        push eax
    L_0043ef4e:
        lea edi,[esp+100h]
    L_0043ef55:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0043ef5a:
        mov esi,edi
    L_0043ef5c:
        jmp asm_target_0043f00d
    L_0043ef61:
        test byte ptr [ebx+6],1
    L_0043ef65:
        mov eax,dword ptr [ebx+8]
    L_0043ef68:
        je short L_0043ef71
    L_0043ef6a:
        mov ecx,ebp
    L_0043ef6c:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043ef71:
        mov ecx,dword ptr [ebp+20h]
    L_0043ef74:
        mov edx,dword ptr [ebp+308h]
    L_0043ef7a:
        push ecx
    L_0043ef7b:
        push eax
    L_0043ef7c:
        push edx
    L_0043ef7d:
        lea edi,[esp+40h]
    L_0043ef81:
        call asm_AnimationManager_CreateSecondaryBack_00448f60
    L_0043ef86:
        mov esi,edi
    L_0043ef88:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0043ef8d:
        mov esi,eax
    L_0043ef8f:
        lea eax,[esi+10h]
    L_0043ef92:
        lea ecx,[ebp+10h]
    L_0043ef95:
        call asm_ScoreList_InsertAfter_00413200
    L_0043ef9a:
        lea ecx,[esi+34Ch]
    L_0043efa0:
        lea eax,[ebp+334h]
    L_0043efa6:
        mov edx,dword ptr [eax]
    L_0043efa8:
        mov dword ptr [ecx],edx
    L_0043efaa:
        mov edx,dword ptr [eax+4]
    L_0043efad:
        mov dword ptr [ecx+4],edx
    L_0043efb0:
        mov eax,dword ptr [eax+8]
    L_0043efb3:
        mov dword ptr [ecx+8],eax
    L_0043efb6:
        lea ecx,[ebp+340h]
    L_0043efbc:
        mov edx,dword ptr [ecx]
    L_0043efbe:
        add esi,340h
    L_0043efc4:
        mov dword ptr [esi],edx
    L_0043efc6:
        mov eax,dword ptr [ecx+4]
    L_0043efc9:
        mov dword ptr [esi+4],eax
    L_0043efcc:
        mov ecx,dword ptr [ecx+8]
    L_0043efcf:
        mov dword ptr [esi+8],ecx
    L_0043efd2:
        movzx edx,word ptr [ebx+2]
    L_0043efd6:
        add edx,ebx
    L_0043efd8:
        mov dword ptr [ebp+390h],edx
    L_0043efde:
        or edi,0FFFFFFFFh
    L_0043efe1:
        jmp asm_target_0043eea4
    L_0043efe6:
        test byte ptr [ebx+6],1
    L_0043efea:
        mov eax,dword ptr [ebx+8]
    L_0043efed:
        je short L_0043eff6
    L_0043efef:
        mov ecx,ebp
    L_0043eff1:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043eff6:
        mov edx,dword ptr [ebp+20h]
    L_0043eff9:
        push edx
    L_0043effa:
        push eax
    L_0043effb:
        mov eax,dword ptr [ebp+308h]
    L_0043f001:
        push eax
    L_0043f002:
        lea edi,[esp+34h]
    L_0043f006:
        call asm_AnimationManager_CreateSecondaryFront_00449090
    L_0043f00b:
        mov esi,edi
    L_0043f00d:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0043f012:
        mov esi,eax
    L_0043f014:
        lea eax,[esi+10h]
    L_0043f017:
        lea ecx,[ebp+10h]
    L_0043f01a:
        call asm_ScoreList_InsertAfter_00413200
    L_0043f01f:
        lea edx,[esi+34Ch]
    L_0043f025:
        lea ecx,[ebp+334h]
    L_0043f02b:
        mov eax,dword ptr [ecx]
    L_0043f02d:
        mov dword ptr [edx],eax
    L_0043f02f:
        mov eax,dword ptr [ecx+4]
    L_0043f032:
        mov dword ptr [edx+4],eax
    L_0043f035:
        mov ecx,dword ptr [ecx+8]
    L_0043f038:
        mov dword ptr [edx+8],ecx
    L_0043f03b:
        lea edx,[ebp+340h]
    L_0043f041:
        mov eax,dword ptr [edx]
    L_0043f043:
        add esi,340h
    L_0043f049:
        mov dword ptr [esi],eax
    L_0043f04b:
        mov ecx,dword ptr [edx+4]
    L_0043f04e:
        mov dword ptr [esi+4],ecx
    L_0043f051:
        mov edx,dword ptr [edx+8]
    L_0043f054:
        mov dword ptr [esi+8],edx
    L_0043f057:
        movzx edx,word ptr [ebx+2]
    L_0043f05b:
        add edx,ebx
    L_0043f05d:
        mov dword ptr [ebp+390h],edx
    L_0043f063:
        or edi,0FFFFFFFFh
    L_0043f066:
        jmp asm_target_0043eea4
    L_0043f06b:
        or dword ptr [ebp+35Ch],1
    L_0043f072:
        test byte ptr [ebx+6],1
    L_0043f076:
        mov eax,dword ptr [ebx+8]
    L_0043f079:
        je short L_0043f082
    L_0043f07b:
        mov ecx,ebp
    L_0043f07d:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f082:
        mov ecx,dword ptr [ebp+308h]
    L_0043f088:
        mov edx,eax
    L_0043f08a:
        mov eax,ebp
    L_0043f08c:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0043f091:
        mov eax,dword ptr [ebp+60h]
    L_0043f094:
        mov dword ptr [ebp+380h],eax
    L_0043f09a:
        movzx edx,word ptr [ebx+2]
    L_0043f09e:
        add edx,ebx
    L_0043f0a0:
        mov dword ptr [ebp+390h],edx
    L_0043f0a6:
        or edi,0FFFFFFFFh
    L_0043f0a9:
        jmp asm_target_0043eea4
    L_0043f0ae:
        test byte ptr [ebx+6],1
    L_0043f0b2:
        je short L_0043f0c1
    L_0043f0b4:
        mov ecx,dword ptr [ebx+8]
    L_0043f0b7:
        push ecx
    L_0043f0b8:
        mov esi,ebp
    L_0043f0ba:
        call asm_FUN_0043eac0_0043eac0
    L_0043f0bf:
        jmp short L_0043f0c4
    L_0043f0c1:
        fld dword ptr [ebx+8]
    L_0043f0c4:
        fstp dword ptr [ebp+3Ch]
    L_0043f0c7:
        mov al,byte ptr [ebx+6]
    L_0043f0ca:
        test al,2
    L_0043f0cc:
        je short L_0043f0db
    L_0043f0ce:
        mov edx,dword ptr [ebx+0Ch]
    L_0043f0d1:
        push edx
    L_0043f0d2:
        mov esi,ebp
    L_0043f0d4:
        call asm_FUN_0043eac0_0043eac0
    L_0043f0d9:
        jmp short L_0043f0de
    L_0043f0db:
        fld dword ptr [ebx+0Ch]
    L_0043f0de:
        mov eax,dword ptr [ebp+35Ch]
    L_0043f0e4:
        fstp dword ptr [ebp+40h]
    L_0043f0e7:
        or eax,8
    L_0043f0ea:
        mov dword ptr [ebp+35Ch],eax
    L_0043f0f0:
        movzx edx,word ptr [ebx+2]
    L_0043f0f4:
        add edx,ebx
    L_0043f0f6:
        mov dword ptr [ebp+390h],edx
    L_0043f0fc:
        or edi,0FFFFFFFFh
    L_0043f0ff:
        jmp asm_target_0043eea4
    L_0043f104:
        test byte ptr [ebx+6],1
    L_0043f108:
        mov eax,dword ptr [ebx+8]
    L_0043f10b:
        je short L_0043f114
    L_0043f10d:
        mov ecx,ebp
    L_0043f10f:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f114:
        mov byte ptr [ebp+2FFh],al
    L_0043f11a:
        movzx edx,word ptr [ebx+2]
    L_0043f11e:
        add edx,ebx
    L_0043f120:
        mov dword ptr [ebp+390h],edx
    L_0043f126:
        or edi,0FFFFFFFFh
    L_0043f129:
        jmp asm_target_0043eea4
    L_0043f12e:
        test byte ptr [ebx+6],1
    L_0043f132:
        mov eax,dword ptr [ebx+8]
    L_0043f135:
        je short L_0043f13e
    L_0043f137:
        mov ecx,ebp
    L_0043f139:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f13e:
        mov byte ptr [ebp+2FEh],al
    L_0043f144:
        test byte ptr [ebx+6],2
    L_0043f148:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f14b:
        je short L_0043f154
    L_0043f14d:
        mov ecx,ebp
    L_0043f14f:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f154:
        mov byte ptr [ebp+2FDh],al
    L_0043f15a:
        test byte ptr [ebx+6],4
    L_0043f15e:
        mov eax,dword ptr [ebx+10h]
    L_0043f161:
        je short L_0043f16a
    L_0043f163:
        mov ecx,ebp
    L_0043f165:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f16a:
        mov byte ptr [ebp+2FCh],al
    L_0043f170:
        movzx edx,word ptr [ebx+2]
    L_0043f174:
        add edx,ebx
    L_0043f176:
        mov dword ptr [ebp+390h],edx
    L_0043f17c:
        or edi,0FFFFFFFFh
    L_0043f17f:
        jmp asm_target_0043eea4
    L_0043f184:
        test byte ptr [ebx+6],1
    L_0043f188:
        mov eax,dword ptr [ebx+8]
    L_0043f18b:
        je short L_0043f194
    L_0043f18d:
        mov ecx,ebp
    L_0043f18f:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f194:
        mov byte ptr [ebp+303h],al
    L_0043f19a:
        movzx edx,word ptr [ebx+2]
    L_0043f19e:
        add edx,ebx
    L_0043f1a0:
        mov dword ptr [ebp+390h],edx
    L_0043f1a6:
        or edi,0FFFFFFFFh
    L_0043f1a9:
        jmp asm_target_0043eea4
    L_0043f1ae:
        test byte ptr [ebx+6],1
    L_0043f1b2:
        mov eax,dword ptr [ebx+8]
    L_0043f1b5:
        je short L_0043f1be
    L_0043f1b7:
        mov ecx,ebp
    L_0043f1b9:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f1be:
        mov byte ptr [ebp+302h],al
    L_0043f1c4:
        test byte ptr [ebx+6],2
    L_0043f1c8:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f1cb:
        je short L_0043f1d4
    L_0043f1cd:
        mov ecx,ebp
    L_0043f1cf:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f1d4:
        mov byte ptr [ebp+301h],al
    L_0043f1da:
        test byte ptr [ebx+6],4
    L_0043f1de:
        mov eax,dword ptr [ebx+10h]
    L_0043f1e1:
        je short L_0043f1ea
    L_0043f1e3:
        mov ecx,ebp
    L_0043f1e5:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f1ea:
        mov byte ptr [ebp+300h],al
    L_0043f1f0:
        movzx edx,word ptr [ebx+2]
    L_0043f1f4:
        add edx,ebx
    L_0043f1f6:
        mov dword ptr [ebp+390h],edx
    L_0043f1fc:
        or edi,0FFFFFFFFh
    L_0043f1ff:
        jmp asm_target_0043eea4
    L_0043f204:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f207:
        push eax
    L_0043f208:
        lea eax,[ebp+5Ch]
    L_0043f20b:
        call asm_Player_SetSchedulerValue_00405410
    L_0043f210:
        mov eax,dword ptr [ebx+8]
    L_0043f213:
        mov ecx,dword ptr [ebp+38Ch]
    L_0043f219:
        add ecx,eax
    L_0043f21b:
        mov dword ptr [ebp+390h],ecx
    L_0043f221:
        jmp asm_target_0043eea4
    L_0043f226:
        xor edx,edx
    L_0043f228:
        mov dx,word ptr [ebx+6]
    L_0043f22c:
        lea esi,[ebx+8]
    L_0043f22f:
        xor ecx,ecx
    L_0043f231:
        mov eax,esi
    L_0043f233:
        push edx
    L_0043f234:
        mov edx,ebp
    L_0043f236:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_0043f23b:
        dec dword ptr [eax]
    L_0043f23d:
        test byte ptr [ebx+6],1
    L_0043f241:
        mov eax,dword ptr [esi]
    L_0043f243:
        je short L_0043f24c
    L_0043f245:
        mov ecx,ebp
    L_0043f247:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f24c:
        test eax,eax
    L_0043f24e:
        jle asm_target_0043f532
    L_0043f254:
        mov eax,dword ptr [ebx+10h]
    L_0043f257:
        push eax
    L_0043f258:
        lea eax,[ebp+5Ch]
    L_0043f25b:
        call asm_Player_SetSchedulerValue_00405410
    L_0043f260:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f263:
        mov ecx,dword ptr [ebp+38Ch]
    L_0043f269:
        add ecx,eax
    L_0043f26b:
        mov dword ptr [ebp+390h],ecx
    L_0043f271:
        jmp asm_target_0043eea4
    L_0043f276:
        mov eax,dword ptr [ebp+35Ch]
    L_0043f27c:
        fld dword ptr [ebp+3Ch]
    L_0043f27f:
        fmul dword ptr [data_00470b60]
    L_0043f285:
        xor eax,200h
    L_0043f28a:
        or eax,8
    L_0043f28d:
        mov dword ptr [ebp+35Ch],eax
    L_0043f293:
        fstp dword ptr [ebp+3Ch]
    L_0043f296:
        movzx edx,word ptr [ebx+2]
    L_0043f29a:
        add edx,ebx
    L_0043f29c:
        mov dword ptr [ebp+390h],edx
    L_0043f2a2:
        or edi,0FFFFFFFFh
    L_0043f2a5:
        jmp asm_target_0043eea4
    L_0043f2aa:
        mov eax,dword ptr [ebp+35Ch]
    L_0043f2b0:
        fld dword ptr [ebp+40h]
    L_0043f2b3:
        fmul dword ptr [data_00470b60]
    L_0043f2b9:
        xor eax,400h
    L_0043f2be:
        or eax,8
    L_0043f2c1:
        mov dword ptr [ebp+35Ch],eax
    L_0043f2c7:
        fstp dword ptr [ebp+40h]
    L_0043f2ca:
        movzx edx,word ptr [ebx+2]
    L_0043f2ce:
        add edx,ebx
    L_0043f2d0:
        mov dword ptr [ebp+390h],edx
    L_0043f2d6:
        or edi,0FFFFFFFFh
    L_0043f2d9:
        jmp asm_target_0043eea4
    L_0043f2de:
        test byte ptr [ebx+6],1
    L_0043f2e2:
        je short L_0043f2f1
    L_0043f2e4:
        mov edx,dword ptr [ebx+8]
    L_0043f2e7:
        push edx
    L_0043f2e8:
        mov esi,ebp
    L_0043f2ea:
        call asm_FUN_0043eac0_0043eac0
    L_0043f2ef:
        jmp short L_0043f2f4
    L_0043f2f1:
        fld dword ptr [ebx+8]
    L_0043f2f4:
        fstp dword ptr [ebp+24h]
    L_0043f2f7:
        mov al,byte ptr [ebx+6]
    L_0043f2fa:
        test al,2
    L_0043f2fc:
        je short L_0043f30b
    L_0043f2fe:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f301:
        push eax
    L_0043f302:
        mov esi,ebp
    L_0043f304:
        call asm_FUN_0043eac0_0043eac0
    L_0043f309:
        jmp short L_0043f30e
    L_0043f30b:
        fld dword ptr [ebx+0Ch]
    L_0043f30e:
        fstp dword ptr [ebp+28h]
    L_0043f311:
        mov al,byte ptr [ebx+6]
    L_0043f314:
        test al,4
    L_0043f316:
        je short L_0043f325
    L_0043f318:
        mov ecx,dword ptr [ebx+10h]
    L_0043f31b:
        push ecx
    L_0043f31c:
        mov esi,ebp
    L_0043f31e:
        call asm_FUN_0043eac0_0043eac0
    L_0043f323:
        jmp short L_0043f328
    L_0043f325:
        fld dword ptr [ebx+10h]
    L_0043f328:
        mov eax,dword ptr [ebp+35Ch]
    L_0043f32e:
        fstp dword ptr [ebp+2Ch]
    L_0043f331:
        or eax,4
    L_0043f334:
        mov dword ptr [ebp+35Ch],eax
    L_0043f33a:
        movzx edx,word ptr [ebx+2]
    L_0043f33e:
        add edx,ebx
    L_0043f340:
        mov dword ptr [ebp+390h],edx
    L_0043f346:
        or edi,0FFFFFFFFh
    L_0043f349:
        jmp asm_target_0043eea4
    L_0043f34e:
        test byte ptr [ebx+6],1
    L_0043f352:
        je short L_0043f361
    L_0043f354:
        mov edx,dword ptr [ebx+8]
    L_0043f357:
        push edx
    L_0043f358:
        mov esi,ebp
    L_0043f35a:
        call asm_FUN_0043eac0_0043eac0
    L_0043f35f:
        jmp short L_0043f364
    L_0043f361:
        fld dword ptr [ebx+8]
    L_0043f364:
        fstp dword ptr [ebp+30h]
    L_0043f367:
        mov al,byte ptr [ebx+6]
    L_0043f36a:
        test al,2
    L_0043f36c:
        je short L_0043f37b
    L_0043f36e:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f371:
        push eax
    L_0043f372:
        mov esi,ebp
    L_0043f374:
        call asm_FUN_0043eac0_0043eac0
    L_0043f379:
        jmp short L_0043f37e
    L_0043f37b:
        fld dword ptr [ebx+0Ch]
    L_0043f37e:
        fstp dword ptr [ebp+34h]
    L_0043f381:
        mov al,byte ptr [ebx+6]
    L_0043f384:
        test al,4
    L_0043f386:
        je short L_0043f395
    L_0043f388:
        mov ecx,dword ptr [ebx+10h]
    L_0043f38b:
        push ecx
    L_0043f38c:
        mov esi,ebp
    L_0043f38e:
        call asm_FUN_0043eac0_0043eac0
    L_0043f393:
        jmp short L_0043f398
    L_0043f395:
        fld dword ptr [ebx+10h]
    L_0043f398:
        mov eax,dword ptr [ebp+35Ch]
    L_0043f39e:
        fstp dword ptr [ebp+38h]
    L_0043f3a1:
        or eax,4
    L_0043f3a4:
        mov dword ptr [ebp+35Ch],eax
    L_0043f3aa:
        movzx edx,word ptr [ebx+2]
    L_0043f3ae:
        add edx,ebx
    L_0043f3b0:
        mov dword ptr [ebp+390h],edx
    L_0043f3b6:
        or edi,0FFFFFFFFh
    L_0043f3b9:
        jmp asm_target_0043eea4
    L_0043f3be:
        test byte ptr [ebx+6],1
    L_0043f3c2:
        je short L_0043f3d1
    L_0043f3c4:
        mov edx,dword ptr [ebx+8]
    L_0043f3c7:
        push edx
    L_0043f3c8:
        mov esi,ebp
    L_0043f3ca:
        call asm_FUN_0043eac0_0043eac0
    L_0043f3cf:
        jmp short L_0043f3d4
    L_0043f3d1:
        fld dword ptr [ebx+8]
    L_0043f3d4:
        fstp dword ptr [ebp+44h]
    L_0043f3d7:
        mov al,byte ptr [ebx+6]
    L_0043f3da:
        test al,2
    L_0043f3dc:
        je short L_0043f400
    L_0043f3de:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f3e1:
        push eax
    L_0043f3e2:
        mov esi,ebp
    L_0043f3e4:
        call asm_FUN_0043eac0_0043eac0
    L_0043f3e9:
        fstp dword ptr [ebp+48h]
    L_0043f3ec:
        movzx edx,word ptr [ebx+2]
    L_0043f3f0:
        add edx,ebx
    L_0043f3f2:
        mov dword ptr [ebp+390h],edx
    L_0043f3f8:
        or edi,0FFFFFFFFh
    L_0043f3fb:
        jmp asm_target_0043eea4
    L_0043f400:
        fld dword ptr [ebx+0Ch]
    L_0043f403:
        fstp dword ptr [ebp+48h]
    L_0043f406:
        movzx edx,word ptr [ebx+2]
    L_0043f40a:
        add edx,ebx
    L_0043f40c:
        mov dword ptr [ebp+390h],edx
    L_0043f412:
        or edi,0FFFFFFFFh
    L_0043f415:
        jmp asm_target_0043eea4
    L_0043f41a:
        test byte ptr [ebx+6],2
    L_0043f41e:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f421:
        je short L_0043f42a
    L_0043f423:
        mov ecx,ebp
    L_0043f425:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f42a:
        xor ecx,ecx
    L_0043f42c:
        mov cl,byte ptr [ebx+8]
    L_0043f42f:
        xor edx,edx
    L_0043f431:
        mov dl,byte ptr [ebp+2FFh]
    L_0043f437:
        push ecx
    L_0043f438:
        mov ecx,eax
    L_0043f43a:
        push edx
    L_0043f43b:
        push 0
    L_0043f43d:
        mov eax,ebp
    L_0043f43f:
        call asm_RecoveryState_Configure42300_00442300
    L_0043f444:
        movzx edx,word ptr [ebx+2]
    L_0043f448:
        add edx,ebx
    L_0043f44a:
        mov dword ptr [ebp+390h],edx
    L_0043f450:
        or edi,0FFFFFFFFh
    L_0043f453:
        jmp asm_target_0043eea4
    L_0043f458:
        mov eax,dword ptr [ebx+8]
    L_0043f45b:
        mov esi,dword ptr [ebp+35Ch]
    L_0043f461:
        shl eax,4
    L_0043f464:
        xor eax,esi
    L_0043f466:
        and eax,30h
    L_0043f469:
        mov ecx,esi
    L_0043f46b:
        xor ecx,eax
    L_0043f46d:
        mov dword ptr [ebp+35Ch],ecx
    L_0043f473:
        movzx edx,word ptr [ebx+2]
    L_0043f477:
        add edx,ebx
    L_0043f479:
        mov dword ptr [ebp+390h],edx
    L_0043f47f:
        or edi,0FFFFFFFFh
    L_0043f482:
        jmp asm_target_0043eea4
    L_0043f487:
        mov eax,dword ptr [ebp+35Ch]
    L_0043f48d:
        test ah,1
    L_0043f490:
        mov al,byte ptr [ebx+6]
    L_0043f493:
        jne asm_target_0043f546
    L_0043f499:
        test al,4
    L_0043f49b:
        je short L_0043f4ae
    L_0043f49d:
        mov ecx,dword ptr [ebx+10h]
    L_0043f4a0:
        push ecx
    L_0043f4a1:
        mov esi,ebp
    L_0043f4a3:
        call asm_FUN_0043eac0_0043eac0
    L_0043f4a8:
        fstp dword ptr [esp+48h]
    L_0043f4ac:
        jmp short L_0043f4b5
    L_0043f4ae:
        mov edx,dword ptr [ebx+10h]
    L_0043f4b1:
        mov dword ptr [esp+48h],edx
    L_0043f4b5:
        test byte ptr [ebx+6],2
    L_0043f4b9:
        je short L_0043f4cf
    L_0043f4bb:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f4be:
        push eax
    L_0043f4bf:
        mov esi,ebp
    L_0043f4c1:
        call asm_FUN_0043eac0_0043eac0
    L_0043f4c6:
        fstp dword ptr [esp+0C4h]
    L_0043f4cd:
        jmp short L_0043f4d9
    L_0043f4cf:
        mov ecx,dword ptr [ebx+0Ch]
    L_0043f4d2:
        mov dword ptr [esp+0C4h],ecx
    L_0043f4d9:
        test byte ptr [ebx+6],1
    L_0043f4dd:
        je short L_0043f4ec
    L_0043f4df:
        mov edx,dword ptr [ebx+8]
    L_0043f4e2:
        push edx
    L_0043f4e3:
        mov esi,ebp
    L_0043f4e5:
        call asm_FUN_0043eac0_0043eac0
    L_0043f4ea:
        jmp short L_0043f4ef
    L_0043f4ec:
        fld dword ptr [ebx+8]
    L_0043f4ef:
        mov eax,dword ptr [esp+0C4h]
    L_0043f4f6:
        fstp dword ptr [esp+0F8h]
    L_0043f4fd:
        mov ecx,dword ptr [esp+48h]
    L_0043f501:
        mov dword ptr [esp+0FCh],eax
    L_0043f508:
        mov eax,dword ptr [esp+0F8h]
    L_0043f50f:
        lea edx,[ebp+334h]
    L_0043f515:
        mov dword ptr [esp+100h],ecx
    L_0043f51c:
        mov ecx,dword ptr [esp+0FCh]
    L_0043f523:
        mov dword ptr [edx],eax
    L_0043f525:
        mov eax,dword ptr [esp+100h]
    L_0043f52c:
        mov dword ptr [edx+4],ecx
    L_0043f52f:
        mov dword ptr [edx+8],eax
    L_0043f532:
        movzx edx,word ptr [ebx+2]
    L_0043f536:
        add edx,ebx
    L_0043f538:
        mov dword ptr [ebp+390h],edx
    L_0043f53e:
        or edi,0FFFFFFFFh
    L_0043f541:
        jmp asm_target_0043eea4
    L_0043f546:
        test al,4
    L_0043f548:
        je short L_0043f55e
    L_0043f54a:
        mov ecx,dword ptr [ebx+10h]
    L_0043f54d:
        push ecx
    L_0043f54e:
        mov esi,ebp
    L_0043f550:
        call asm_FUN_0043eac0_0043eac0
    L_0043f555:
        fstp dword ptr [esp+9Ch]
    L_0043f55c:
        jmp short L_0043f568
    L_0043f55e:
        mov edx,dword ptr [ebx+10h]
    L_0043f561:
        mov dword ptr [esp+9Ch],edx
    L_0043f568:
        test byte ptr [ebx+6],2
    L_0043f56c:
        je short L_0043f582
    L_0043f56e:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f571:
        push eax
    L_0043f572:
        mov esi,ebp
    L_0043f574:
        call asm_FUN_0043eac0_0043eac0
    L_0043f579:
        fstp dword ptr [esp+0D4h]
    L_0043f580:
        jmp short L_0043f58c
    L_0043f582:
        mov ecx,dword ptr [ebx+0Ch]
    L_0043f585:
        mov dword ptr [esp+0D4h],ecx
    L_0043f58c:
        test byte ptr [ebx+6],1
    L_0043f590:
        je short L_0043f59f
    L_0043f592:
        mov edx,dword ptr [ebx+8]
    L_0043f595:
        push edx
    L_0043f596:
        mov esi,ebp
    L_0043f598:
        call asm_FUN_0043eac0_0043eac0
    L_0043f59d:
        jmp short L_0043f5a2
    L_0043f59f:
        fld dword ptr [ebx+8]
    L_0043f5a2:
        mov eax,dword ptr [esp+0D4h]
    L_0043f5a9:
        fstp dword ptr [esp+0E8h]
    L_0043f5b0:
        mov ecx,dword ptr [esp+9Ch]
    L_0043f5b7:
        mov dword ptr [esp+0ECh],eax
    L_0043f5be:
        mov eax,dword ptr [esp+0E8h]
    L_0043f5c5:
        lea edx,[ebp+34Ch]
    L_0043f5cb:
        mov dword ptr [esp+0F0h],ecx
    L_0043f5d2:
        mov ecx,dword ptr [esp+0ECh]
    L_0043f5d9:
        mov dword ptr [edx],eax
    L_0043f5db:
        mov eax,dword ptr [esp+0F0h]
    L_0043f5e2:
        mov dword ptr [edx+4],ecx
    L_0043f5e5:
        jmp asm_target_0043f52f
    L_0043f5ea:
        test byte ptr [ebx+6],1
    L_0043f5ee:
        mov eax,dword ptr [ebx+8]
    L_0043f5f1:
        je short L_0043f5fa
    L_0043f5f3:
        mov ecx,ebp
    L_0043f5f5:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f5fa:
        lea esi,[ebp+5Ch]
    L_0043f5fd:
        call asm_FrameTimer_Decrement_00428dd0
    L_0043f602:
        movzx edx,word ptr [ebx+2]
    L_0043f606:
        add edx,ebx
    L_0043f608:
        mov dword ptr [ebp+390h],edx
    L_0043f60e:
        or edi,0FFFFFFFFh
    L_0043f611:
        jmp asm_target_0043eea4
    L_0043f616:
        and dword ptr [ebp+35Ch],0FFFFFFFEh
    L_0043f61d:
        mov ax,word ptr [ebp+304h]
    L_0043f624:
        test ax,ax
    L_0043f627:
        je asm_target_00440e2b
    L_0043f62d:
        mov esi,dword ptr [ebp+38Ch]
    L_0043f633:
        xor edx,edx
    L_0043f635:
        mov cx,word ptr [esi]
    L_0043f638:
        cmp cx,40h
    L_0043f63c:
        jne short L_0043f646
    L_0043f63e:
        movsx ebx,ax
    L_0043f641:
        cmp ebx,dword ptr [esi+8]
    L_0043f644:
        je short L_0043f660
    L_0043f646:
        cmp cx,di
    L_0043f649:
        je short L_0043f660
    L_0043f64b:
        cmp cx,40h
    L_0043f64f:
        jne short L_0043f658
    L_0043f651:
        cmp dword ptr [esi+8],edi
    L_0043f654:
        jne short L_0043f658
    L_0043f656:
        mov edx,esi
    L_0043f658:
        movzx ecx,word ptr [esi+2]
    L_0043f65c:
        add esi,ecx
    L_0043f65e:
        jmp short L_0043f635
    L_0043f660:
        mov ecx,dword ptr [ebp+35Ch]
    L_0043f666:
        and ecx,0FFFFEFFFh
    L_0043f66c:
        mov word ptr [ebp+304h],0
    L_0043f675:
        mov dword ptr [ebp+35Ch],ecx
    L_0043f67b:
        cmp word ptr [esi],40h
    L_0043f67f:
        je short L_0043f68b
    L_0043f681:
        test edx,edx
    L_0043f683:
        je asm_target_00440e35
    L_0043f689:
        mov esi,edx
    L_0043f68b:
        lea eax,[ebp+5Ch]
    L_0043f68e:
        mov ecx,eax
    L_0043f690:
        mov ebx,dword ptr [ecx]
    L_0043f692:
        lea edx,[ebp+368h]
    L_0043f698:
        mov dword ptr [edx],ebx
    L_0043f69a:
        mov ebx,dword ptr [ecx+4]
    L_0043f69d:
        mov dword ptr [edx+4],ebx
    L_0043f6a0:
        mov ebx,dword ptr [ecx+8]
    L_0043f6a3:
        mov dword ptr [edx+8],ebx
    L_0043f6a6:
        mov ebx,dword ptr [ecx+0Ch]
    L_0043f6a9:
        mov ecx,dword ptr [ecx+10h]
    L_0043f6ac:
        mov dword ptr [edx+0Ch],ebx
    L_0043f6af:
        mov dword ptr [edx+10h],ecx
    L_0043f6b2:
        mov edx,dword ptr [ebp+390h]
    L_0043f6b8:
        mov dword ptr [ebp+37Ch],edx
    L_0043f6be:
        movsx ecx,word ptr [esi+4]
    L_0043f6c2:
        push ecx
    L_0043f6c3:
        call asm_Player_SetSchedulerValue_00405410
    L_0043f6c8:
        movzx edx,word ptr [esi+2]
    L_0043f6cc:
        mov eax,dword ptr [ebp+35Ch]
    L_0043f6d2:
        add edx,esi
    L_0043f6d4:
        or eax,1
    L_0043f6d7:
        mov dword ptr [ebp+390h],edx
    L_0043f6dd:
        mov dword ptr [ebp+35Ch],eax
    L_0043f6e3:
        jmp asm_target_0043eea4
    L_0043f6e8:
        lea eax,[ebp+368h]
    L_0043f6ee:
        mov edx,dword ptr [eax]
    L_0043f6f0:
        lea ecx,[ebp+5Ch]
    L_0043f6f3:
        mov dword ptr [ecx],edx
    L_0043f6f5:
        mov edx,dword ptr [eax+4]
    L_0043f6f8:
        mov dword ptr [ecx+4],edx
    L_0043f6fb:
        mov edx,dword ptr [eax+8]
    L_0043f6fe:
        mov dword ptr [ecx+8],edx
    L_0043f701:
        mov edx,dword ptr [eax+0Ch]
    L_0043f704:
        mov eax,dword ptr [eax+10h]
    L_0043f707:
        mov dword ptr [ecx+0Ch],edx
    L_0043f70a:
        mov dword ptr [ecx+10h],eax
    L_0043f70d:
        mov ecx,dword ptr [ebp+37Ch]
    L_0043f713:
        mov dword ptr [ebp+390h],ecx
    L_0043f719:
        jmp asm_target_0043eea4
    L_0043f71e:
        mov edx,dword ptr [ebx+8]
    L_0043f721:
        mov esi,dword ptr [ebp+35Ch]
    L_0043f727:
        xor edx,esi
    L_0043f729:
        and edx,1
    L_0043f72c:
        mov eax,esi
    L_0043f72e:
        xor eax,edx
    L_0043f730:
        mov dword ptr [ebp+35Ch],eax
    L_0043f736:
        movzx edx,word ptr [ebx+2]
    L_0043f73a:
        add edx,ebx
    L_0043f73c:
        mov dword ptr [ebp+390h],edx
    L_0043f742:
        or edi,0FFFFFFFFh
    L_0043f745:
        jmp asm_target_0043eea4
    L_0043f74a:
        movzx eax,word ptr [ebx+8]
    L_0043f74e:
        mov ecx,dword ptr [ebp+35Ch]
    L_0043f754:
        shl eax,12h
    L_0043f757:
        xor eax,ecx
    L_0043f759:
        mov esi,ecx
    L_0043f75b:
        and eax,0C0000h
    L_0043f760:
        xor esi,eax
    L_0043f762:
        mov dword ptr [ebp+35Ch],esi
    L_0043f768:
        movzx ecx,word ptr [ebx+0Ah]
    L_0043f76c:
        shl ecx,14h
    L_0043f76f:
        mov eax,esi
    L_0043f771:
        xor ecx,eax
    L_0043f773:
        and ecx,300000h
    L_0043f779:
        xor ecx,eax
    L_0043f77b:
        mov dword ptr [ebp+35Ch],ecx
    L_0043f781:
        movzx edx,word ptr [ebx+2]
    L_0043f785:
        add edx,ebx
    L_0043f787:
        mov dword ptr [ebp+390h],edx
    L_0043f78d:
        or edi,0FFFFFFFFh
    L_0043f790:
        jmp asm_target_0043eea4
    L_0043f795:
        test byte ptr [ebx+6],1
    L_0043f799:
        je short L_0043f7c0
    L_0043f79b:
        mov edx,dword ptr [ebx+8]
    L_0043f79e:
        push edx
    L_0043f79f:
        mov esi,ebp
    L_0043f7a1:
        call asm_FUN_0043eac0_0043eac0
    L_0043f7a6:
        fstp dword ptr [ebp+234h]
    L_0043f7ac:
        movzx edx,word ptr [ebx+2]
    L_0043f7b0:
        add edx,ebx
    L_0043f7b2:
        mov dword ptr [ebp+390h],edx
    L_0043f7b8:
        or edi,0FFFFFFFFh
    L_0043f7bb:
        jmp asm_target_0043eea4
    L_0043f7c0:
        fld dword ptr [ebx+8]
    L_0043f7c3:
        fstp dword ptr [ebp+234h]
    L_0043f7c9:
        movzx edx,word ptr [ebx+2]
    L_0043f7cd:
        add edx,ebx
    L_0043f7cf:
        mov dword ptr [ebp+390h],edx
    L_0043f7d5:
        or edi,0FFFFFFFFh
    L_0043f7d8:
        jmp asm_target_0043eea4
    L_0043f7dd:
        test byte ptr [ebx+6],1
    L_0043f7e1:
        je short L_0043f808
    L_0043f7e3:
        mov eax,dword ptr [ebx+8]
    L_0043f7e6:
        push eax
    L_0043f7e7:
        mov esi,ebp
    L_0043f7e9:
        call asm_FUN_0043eac0_0043eac0
    L_0043f7ee:
        fstp dword ptr [ebp+238h]
    L_0043f7f4:
        movzx edx,word ptr [ebx+2]
    L_0043f7f8:
        add edx,ebx
    L_0043f7fa:
        mov dword ptr [ebp+390h],edx
    L_0043f800:
        or edi,0FFFFFFFFh
    L_0043f803:
        jmp asm_target_0043eea4
    L_0043f808:
        fld dword ptr [ebx+8]
    L_0043f80b:
        fstp dword ptr [ebp+238h]
    L_0043f811:
        movzx edx,word ptr [ebx+2]
    L_0043f815:
        add edx,ebx
    L_0043f817:
        mov dword ptr [ebp+390h],edx
    L_0043f81d:
        or edi,0FFFFFFFFh
    L_0043f820:
        jmp asm_target_0043eea4
    L_0043f825:
        mov ecx,dword ptr [ebx+8]
    L_0043f828:
        mov esi,dword ptr [ebp+35Ch]
    L_0043f82e:
        shl ecx,0Bh
    L_0043f831:
        xor ecx,esi
    L_0043f833:
        and ecx,800h
    L_0043f839:
        mov eax,esi
    L_0043f83b:
        xor eax,ecx
    L_0043f83d:
        mov dword ptr [ebp+35Ch],eax
    L_0043f843:
        movzx edx,word ptr [ebx+2]
    L_0043f847:
        add edx,ebx
    L_0043f849:
        mov dword ptr [ebp+390h],edx
    L_0043f84f:
        or edi,0FFFFFFFFh
    L_0043f852:
        jmp asm_target_0043eea4
    L_0043f857:
        mov edx,dword ptr [ebx+8]
    L_0043f85a:
        mov esi,dword ptr [ebp+35Ch]
    L_0043f860:
        shl edx,0Dh
    L_0043f863:
        xor edx,esi
    L_0043f865:
        and edx,2000h
    L_0043f86b:
        mov eax,esi
    L_0043f86d:
        xor eax,edx
    L_0043f86f:
        mov dword ptr [ebp+35Ch],eax
    L_0043f875:
        movzx edx,word ptr [ebx+2]
    L_0043f879:
        add edx,ebx
    L_0043f87b:
        mov dword ptr [ebp+390h],edx
    L_0043f881:
        or edi,0FFFFFFFFh
    L_0043f884:
        jmp asm_target_0043eea4
    L_0043f889:
        mov eax,dword ptr [ebx+8]
    L_0043f88c:
        mov ecx,dword ptr [ebp+35Ch]
    L_0043f892:
        shl eax,1Fh
    L_0043f895:
        and ecx,7FFFFFFFh
    L_0043f89b:
        or eax,ecx
    L_0043f89d:
        mov dword ptr [ebp+35Ch],eax
    L_0043f8a3:
        movzx edx,word ptr [ebx+2]
    L_0043f8a7:
        add edx,ebx
    L_0043f8a9:
        mov dword ptr [ebp+390h],edx
    L_0043f8af:
        or edi,0FFFFFFFFh
    L_0043f8b2:
        jmp asm_target_0043eea4
    L_0043f8b7:
        test byte ptr [ebx+6],1
    L_0043f8bb:
        mov eax,dword ptr [ebx+8]
    L_0043f8be:
        je short L_0043f8c7
    L_0043f8c0:
        mov ecx,ebp
    L_0043f8c2:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043f8c7:
        mov dword ptr [ebp+0B4h],eax
    L_0043f8cd:
        mov eax,dword ptr [data_00491c14]
    L_0043f8d2:
        lea edx,[ebp+88h]
    L_0043f8d8:
        mov dword ptr [edx],eax
    L_0043f8da:
        mov ecx,dword ptr [data_00491c18]
    L_0043f8e0:
        mov dword ptr [edx+4],ecx
    L_0043f8e3:
        mov eax,dword ptr [data_00491c1c]
    L_0043f8e8:
        mov dword ptr [edx+8],eax
    L_0043f8eb:
        mov edx,dword ptr [data_00491c14]
    L_0043f8f1:
        lea ecx,[ebp+94h]
    L_0043f8f7:
        mov dword ptr [ecx],edx
    L_0043f8f9:
        mov eax,dword ptr [data_00491c18]
    L_0043f8fe:
        mov dword ptr [ecx+4],eax
    L_0043f901:
        mov edx,dword ptr [data_00491c1c]
    L_0043f907:
        mov dword ptr [ecx+8],edx
    L_0043f90a:
        mov eax,dword ptr [ebx+0Ch]
    L_0043f90d:
        mov dword ptr [ebp+0B8h],eax
    L_0043f913:
        mov eax,dword ptr [ebp+35Ch]
    L_0043f919:
        test ah,1
    L_0043f91c:
        lea edi,[ebp+70h]
    L_0043f91f:
        jne short L_0043f93b
    L_0043f921:
        lea ecx,[ebp+334h]
    L_0043f927:
        mov eax,dword ptr [ecx]
    L_0043f929:
        mov edx,edi
    L_0043f92b:
        mov dword ptr [edx],eax
    L_0043f92d:
        mov eax,dword ptr [ecx+4]
    L_0043f930:
        mov ecx,dword ptr [ecx+8]
    L_0043f933:
        mov dword ptr [edx+4],eax
    L_0043f936:
        mov dword ptr [edx+8],ecx
    L_0043f939:
        jmp short L_0043f953
    L_0043f93b:
        lea edx,[ebp+34Ch]
    L_0043f941:
        mov ecx,dword ptr [edx]
    L_0043f943:
        mov eax,edi
    L_0043f945:
        mov dword ptr [eax],ecx
    L_0043f947:
        mov ecx,dword ptr [edx+4]
    L_0043f94a:
        mov edx,dword ptr [edx+8]
    L_0043f94d:
        mov dword ptr [eax+4],ecx
    L_0043f950:
        mov dword ptr [eax+8],edx
    L_0043f953:
        test byte ptr [ebx+6],10h
    L_0043f957:
        je short L_0043f96d
    L_0043f959:
        mov eax,dword ptr [ebx+18h]
    L_0043f95c:
        push eax
    L_0043f95d:
        mov esi,ebp
    L_0043f95f:
        call asm_FUN_0043eac0_0043eac0
    L_0043f964:
        fstp dword ptr [esp+0D0h]
    L_0043f96b:
        jmp short L_0043f977
    L_0043f96d:
        mov ecx,dword ptr [ebx+18h]
    L_0043f970:
        mov dword ptr [esp+0D0h],ecx
    L_0043f977:
        test byte ptr [ebx+6],8
    L_0043f97b:
        je short L_0043f991
    L_0043f97d:
        mov edx,dword ptr [ebx+14h]
    L_0043f980:
        push edx
    L_0043f981:
        mov esi,ebp
    L_0043f983:
        call asm_FUN_0043eac0_0043eac0
    L_0043f988:
        fstp dword ptr [esp+0C8h]
    L_0043f98f:
        jmp short L_0043f99b
    L_0043f991:
        mov eax,dword ptr [ebx+14h]
    L_0043f994:
        mov dword ptr [esp+0C8h],eax
    L_0043f99b:
        test byte ptr [ebx+6],4
    L_0043f99f:
        je short L_0043f9ae
    L_0043f9a1:
        mov ecx,dword ptr [ebx+10h]
    L_0043f9a4:
        push ecx
    L_0043f9a5:
        mov esi,ebp
    L_0043f9a7:
        call asm_FUN_0043eac0_0043eac0
    L_0043f9ac:
        jmp short L_0043f9b1
    L_0043f9ae:
        fld dword ptr [ebx+10h]
    L_0043f9b1:
        mov edx,dword ptr [esp+0C8h]
    L_0043f9b8:
        fstp dword ptr [esp+0D8h]
    L_0043f9bf:
        mov eax,dword ptr [esp+0D0h]
    L_0043f9c6:
        mov dword ptr [esp+0DCh],edx
    L_0043f9cd:
        mov edx,dword ptr [esp+0D8h]
    L_0043f9d4:
        mov dword ptr [esp+0E0h],eax
    L_0043f9db:
        mov eax,dword ptr [esp+0DCh]
    L_0043f9e2:
        lea ecx,[ebp+7Ch]
    L_0043f9e5:
        mov dword ptr [ecx],edx
    L_0043f9e7:
        mov edx,dword ptr [esp+0E0h]
    L_0043f9ee:
        mov dword ptr [ecx+4],eax
    L_0043f9f1:
        mov eax,edi
    L_0043f9f3:
        mov dword ptr [ecx+8],edx
    L_0043f9f6:
        call asm_EmbeddedTimer_Reset_004050d0
    L_0043f9fb:
        movzx edx,word ptr [ebx+2]
    L_0043f9ff:
        add edx,ebx
    L_0043fa01:
        mov dword ptr [ebp+390h],edx
    L_0043fa07:
        or edi,0FFFFFFFFh
    L_0043fa0a:
        jmp asm_target_0043eea4
    L_0043fa0f:
        mov al,byte ptr [ebp+2FCh]
    L_0043fa15:
        mov cl,byte ptr [ebp+2FDh]
    L_0043fa1b:
        mov dl,byte ptr [ebp+2FEh]
    L_0043fa21:
        mov byte ptr [esp+3Ch],al
    L_0043fa25:
        test byte ptr [ebx+6],10h
    L_0043fa29:
        mov eax,dword ptr [ebx+18h]
    L_0043fa2c:
        mov byte ptr [esp+3Dh],cl
    L_0043fa30:
        mov byte ptr [esp+3Eh],dl
    L_0043fa34:
        je short L_0043fa3d
    L_0043fa36:
        mov ecx,ebp
    L_0043fa38:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fa3d:
        mov dword ptr [esp+24h],eax
    L_0043fa41:
        test byte ptr [ebx+6],8
    L_0043fa45:
        je short L_0043fa57
    L_0043fa47:
        mov eax,dword ptr [ebx+14h]
    L_0043fa4a:
        mov ecx,ebp
    L_0043fa4c:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fa51:
        mov dword ptr [esp+14h],eax
    L_0043fa55:
        jmp short L_0043fa5e
    L_0043fa57:
        mov ecx,dword ptr [ebx+14h]
    L_0043fa5a:
        mov dword ptr [esp+14h],ecx
    L_0043fa5e:
        test byte ptr [ebx+6],4
    L_0043fa62:
        mov eax,dword ptr [ebx+10h]
    L_0043fa65:
        je short L_0043fa6e
    L_0043fa67:
        mov ecx,ebp
    L_0043fa69:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fa6e:
        mov dl,byte ptr [esp+24h]
    L_0043fa72:
        mov cl,byte ptr [esp+14h]
    L_0043fa76:
        mov byte ptr [esp+12h],al
    L_0043fa7a:
        test byte ptr [ebx+6],1
    L_0043fa7e:
        mov eax,dword ptr [ebx+8]
    L_0043fa81:
        mov byte ptr [esp+10h],dl
    L_0043fa85:
        mov byte ptr [esp+11h],cl
    L_0043fa89:
        je short L_0043fa92
    L_0043fa8b:
        mov ecx,ebp
    L_0043fa8d:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fa92:
        xor edx,edx
    L_0043fa94:
        mov dl,byte ptr [ebx+0Ch]
    L_0043fa97:
        lea ecx,[esp+10h]
    L_0043fa9b:
        push edx
    L_0043fa9c:
        push eax
    L_0043fa9d:
        lea edx,[esp+44h]
    L_0043faa1:
        mov eax,ebp
    L_0043faa3:
        call asm_ConfigureColorPlaybackState_00442220
    L_0043faa8:
        movzx edx,word ptr [ebx+2]
    L_0043faac:
        add edx,ebx
    L_0043faae:
        mov dword ptr [ebp+390h],edx
    L_0043fab4:
        or edi,0FFFFFFFFh
    L_0043fab7:
        jmp asm_target_0043eea4
    L_0043fabc:
        test byte ptr [ebx+6],4
    L_0043fac0:
        je short L_0043fad0
    L_0043fac2:
        mov eax,dword ptr [ebx+10h]
    L_0043fac5:
        mov ecx,ebp
    L_0043fac7:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043facc:
        mov esi,eax
    L_0043face:
        jmp short L_0043fad3
    L_0043fad0:
        mov esi,dword ptr [ebx+10h]
    L_0043fad3:
        test byte ptr [ebx+6],1
    L_0043fad7:
        mov eax,dword ptr [ebx+8]
    L_0043fada:
        je short L_0043fae3
    L_0043fadc:
        mov ecx,ebp
    L_0043fade:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fae3:
        xor ecx,ecx
    L_0043fae5:
        mov cl,byte ptr [ebp+2FFh]
    L_0043faeb:
        xor edx,edx
    L_0043faed:
        mov dl,byte ptr [ebx+0Ch]
    L_0043faf0:
        push esi
    L_0043faf1:
        push ecx
    L_0043faf2:
        mov ecx,eax
    L_0043faf4:
        push edx
    L_0043faf5:
        mov eax,ebp
    L_0043faf7:
        call asm_RecoveryState_Configure42300_00442300
    L_0043fafc:
        movzx edx,word ptr [ebx+2]
    L_0043fb00:
        add edx,ebx
    L_0043fb02:
        mov dword ptr [ebp+390h],edx
    L_0043fb08:
        or edi,0FFFFFFFFh
    L_0043fb0b:
        jmp asm_target_0043eea4
    L_0043fb10:
        mov al,byte ptr [ebp+300h]
    L_0043fb16:
        mov cl,byte ptr [ebp+301h]
    L_0043fb1c:
        mov dl,byte ptr [ebp+302h]
    L_0043fb22:
        mov byte ptr [esp+30h],al
    L_0043fb26:
        test byte ptr [ebx+6],10h
    L_0043fb2a:
        mov eax,dword ptr [ebx+18h]
    L_0043fb2d:
        mov byte ptr [esp+31h],cl
    L_0043fb31:
        mov byte ptr [esp+32h],dl
    L_0043fb35:
        je short L_0043fb3e
    L_0043fb37:
        mov ecx,ebp
    L_0043fb39:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fb3e:
        mov dword ptr [esp+14h],eax
    L_0043fb42:
        test byte ptr [ebx+6],8
    L_0043fb46:
        je short L_0043fb58
    L_0043fb48:
        mov eax,dword ptr [ebx+14h]
    L_0043fb4b:
        mov ecx,ebp
    L_0043fb4d:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fb52:
        mov dword ptr [esp+24h],eax
    L_0043fb56:
        jmp short L_0043fb5f
    L_0043fb58:
        mov ecx,dword ptr [ebx+14h]
    L_0043fb5b:
        mov dword ptr [esp+24h],ecx
    L_0043fb5f:
        test byte ptr [ebx+6],4
    L_0043fb63:
        mov eax,dword ptr [ebx+10h]
    L_0043fb66:
        je short L_0043fb6f
    L_0043fb68:
        mov ecx,ebp
    L_0043fb6a:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fb6f:
        mov dl,byte ptr [esp+14h]
    L_0043fb73:
        mov cl,byte ptr [esp+24h]
    L_0043fb77:
        mov byte ptr [esp+3Ah],al
    L_0043fb7b:
        test byte ptr [ebx+6],1
    L_0043fb7f:
        mov eax,dword ptr [ebx+8]
    L_0043fb82:
        mov byte ptr [esp+38h],dl
    L_0043fb86:
        mov byte ptr [esp+39h],cl
    L_0043fb8a:
        je short L_0043fb93
    L_0043fb8c:
        mov ecx,ebp
    L_0043fb8e:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fb93:
        xor edx,edx
    L_0043fb95:
        mov dl,byte ptr [ebx+0Ch]
    L_0043fb98:
        lea ecx,[esp+38h]
    L_0043fb9c:
        push edx
    L_0043fb9d:
        push eax
    L_0043fb9e:
        lea edx,[esp+38h]
    L_0043fba2:
        mov eax,ebp
    L_0043fba4:
        call asm_FUN_00442050_00442050
    L_0043fba9:
        movzx edx,word ptr [ebx+2]
    L_0043fbad:
        add edx,ebx
    L_0043fbaf:
        mov dword ptr [ebp+390h],edx
    L_0043fbb5:
        or edi,0FFFFFFFFh
    L_0043fbb8:
        jmp asm_target_0043eea4
    L_0043fbbd:
        test byte ptr [ebx+6],4
    L_0043fbc1:
        je short L_0043fbd1
    L_0043fbc3:
        mov eax,dword ptr [ebx+10h]
    L_0043fbc6:
        mov ecx,ebp
    L_0043fbc8:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fbcd:
        mov esi,eax
    L_0043fbcf:
        jmp short L_0043fbd4
    L_0043fbd1:
        mov esi,dword ptr [ebx+10h]
    L_0043fbd4:
        test byte ptr [ebx+6],1
    L_0043fbd8:
        mov eax,dword ptr [ebx+8]
    L_0043fbdb:
        je short L_0043fbe4
    L_0043fbdd:
        mov ecx,ebp
    L_0043fbdf:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fbe4:
        mov dl,byte ptr [ebx+0Ch]
    L_0043fbe7:
        xor ecx,ecx
    L_0043fbe9:
        mov cl,byte ptr [ebp+303h]
    L_0043fbef:
        push esi
    L_0043fbf0:
        push ecx
    L_0043fbf1:
        mov ecx,eax
    L_0043fbf3:
        mov eax,ebp
    L_0043fbf5:
        call asm_RecoveryState_Configure41F50_00441f50
    L_0043fbfa:
        movzx edx,word ptr [ebx+2]
    L_0043fbfe:
        add edx,ebx
    L_0043fc00:
        mov dword ptr [ebp+390h],edx
    L_0043fc06:
        or edi,0FFFFFFFFh
    L_0043fc09:
        jmp asm_target_0043eea4
    L_0043fc0e:
        test byte ptr [ebx+6],10h
    L_0043fc12:
        je short L_0043fc25
    L_0043fc14:
        mov edx,dword ptr [ebx+18h]
    L_0043fc17:
        push edx
    L_0043fc18:
        mov esi,ebp
    L_0043fc1a:
        call asm_FUN_0043eac0_0043eac0
    L_0043fc1f:
        fstp dword ptr [esp+50h]
    L_0043fc23:
        jmp short L_0043fc2c
    L_0043fc25:
        mov eax,dword ptr [ebx+18h]
    L_0043fc28:
        mov dword ptr [esp+50h],eax
    L_0043fc2c:
        test byte ptr [ebx+6],8
    L_0043fc30:
        je short L_0043fc46
    L_0043fc32:
        mov ecx,dword ptr [ebx+14h]
    L_0043fc35:
        push ecx
    L_0043fc36:
        mov esi,ebp
    L_0043fc38:
        call asm_FUN_0043eac0_0043eac0
    L_0043fc3d:
        fstp dword ptr [esp+0ACh]
    L_0043fc44:
        jmp short L_0043fc50
    L_0043fc46:
        mov edx,dword ptr [ebx+14h]
    L_0043fc49:
        mov dword ptr [esp+0ACh],edx
    L_0043fc50:
        test byte ptr [ebx+6],4
    L_0043fc54:
        je short L_0043fc63
    L_0043fc56:
        mov eax,dword ptr [ebx+10h]
    L_0043fc59:
        push eax
    L_0043fc5a:
        mov esi,ebp
    L_0043fc5c:
        call asm_FUN_0043eac0_0043eac0
    L_0043fc61:
        jmp short L_0043fc66
    L_0043fc63:
        fld dword ptr [ebx+10h]
    L_0043fc66:
        mov al,byte ptr [ebx+6]
    L_0043fc69:
        fstp dword ptr [esp+18h]
    L_0043fc6d:
        mov ecx,dword ptr [esp+0ACh]
    L_0043fc74:
        mov edx,dword ptr [esp+50h]
    L_0043fc78:
        test al,1
    L_0043fc7a:
        mov eax,dword ptr [ebx+8]
    L_0043fc7d:
        mov dword ptr [esp+1Ch],ecx
    L_0043fc81:
        mov dword ptr [esp+20h],edx
    L_0043fc85:
        je short L_0043fc8e
    L_0043fc87:
        mov ecx,ebp
    L_0043fc89:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fc8e:
        mov dword ptr [ebp+178h],eax
    L_0043fc94:
        mov ecx,dword ptr [data_00491c14]
    L_0043fc9a:
        lea eax,[ebp+14Ch]
    L_0043fca0:
        mov dword ptr [eax],ecx
    L_0043fca2:
        mov edx,dword ptr [data_00491c18]
    L_0043fca8:
        mov dword ptr [eax+4],edx
    L_0043fcab:
        mov ecx,dword ptr [data_00491c1c]
    L_0043fcb1:
        mov dword ptr [eax+8],ecx
    L_0043fcb4:
        mov eax,dword ptr [data_00491c14]
    L_0043fcb9:
        lea edx,[ebp+158h]
    L_0043fcbf:
        mov dword ptr [edx],eax
    L_0043fcc1:
        mov ecx,dword ptr [data_00491c18]
    L_0043fcc7:
        mov dword ptr [edx+4],ecx
    L_0043fcca:
        mov eax,dword ptr [data_00491c1c]
    L_0043fccf:
        mov dword ptr [edx+8],eax
    L_0043fcd2:
        mov ecx,dword ptr [ebx+0Ch]
    L_0043fcd5:
        mov dword ptr [ebp+17Ch],ecx
    L_0043fcdb:
        lea eax,[ebp+134h]
    L_0043fce1:
        lea edx,[ebp+24h]
    L_0043fce4:
        mov esi,dword ptr [edx]
    L_0043fce6:
        mov ecx,eax
    L_0043fce8:
        mov dword ptr [ecx],esi
    L_0043fcea:
        mov esi,dword ptr [edx+4]
    L_0043fced:
        mov edx,dword ptr [edx+8]
    L_0043fcf0:
        mov dword ptr [ecx+4],esi
    L_0043fcf3:
        mov dword ptr [ecx+8],edx
    L_0043fcf6:
        mov edx,dword ptr [esp+18h]
    L_0043fcfa:
        lea ecx,[ebp+140h]
    L_0043fd00:
        mov dword ptr [ecx],edx
    L_0043fd02:
        mov edx,dword ptr [esp+1Ch]
    L_0043fd06:
        mov dword ptr [ecx+4],edx
    L_0043fd09:
        mov edx,dword ptr [esp+20h]
    L_0043fd0d:
        mov dword ptr [ecx+8],edx
    L_0043fd10:
        call asm_EmbeddedTimer_Reset_004050d0
    L_0043fd15:
        or dword ptr [ebp+35Ch],4
    L_0043fd1c:
        movzx edx,word ptr [ebx+2]
    L_0043fd20:
        add edx,ebx
    L_0043fd22:
        mov dword ptr [ebp+390h],edx
    L_0043fd28:
        or edi,0FFFFFFFFh
    L_0043fd2b:
        jmp asm_target_0043eea4
    L_0043fd30:
        test byte ptr [ebx+6],8
    L_0043fd34:
        je short L_0043fd4a
    L_0043fd36:
        mov eax,dword ptr [ebx+14h]
    L_0043fd39:
        push eax
    L_0043fd3a:
        mov esi,ebp
    L_0043fd3c:
        call asm_FUN_0043eac0_0043eac0
    L_0043fd41:
        fstp dword ptr [esp+0A0h]
    L_0043fd48:
        jmp short L_0043fd54
    L_0043fd4a:
        mov ecx,dword ptr [ebx+14h]
    L_0043fd4d:
        mov dword ptr [esp+0A0h],ecx
    L_0043fd54:
        test byte ptr [ebx+6],4
    L_0043fd58:
        je short L_0043fd67
    L_0043fd5a:
        mov edx,dword ptr [ebx+10h]
    L_0043fd5d:
        push edx
    L_0043fd5e:
        mov esi,ebp
    L_0043fd60:
        call asm_FUN_0043eac0_0043eac0
    L_0043fd65:
        jmp short L_0043fd6a
    L_0043fd67:
        fld dword ptr [ebx+10h]
    L_0043fd6a:
        mov eax,dword ptr [esp+0A0h]
    L_0043fd71:
        fstp dword ptr [esp+104h]
    L_0043fd78:
        mov dword ptr [esp+108h],eax
    L_0043fd7f:
        test byte ptr [ebx+6],1
    L_0043fd83:
        je short L_0043fd93
    L_0043fd85:
        mov eax,dword ptr [ebx+8]
    L_0043fd88:
        mov ecx,ebp
    L_0043fd8a:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fd8f:
        mov esi,eax
    L_0043fd91:
        jmp short L_0043fd96
    L_0043fd93:
        mov esi,dword ptr [ebx+8]
    L_0043fd96:
        xor ecx,ecx
    L_0043fd98:
        mov cl,byte ptr [ebx+0Ch]
    L_0043fd9b:
        lea edx,[ebp+3Ch]
    L_0043fd9e:
        mov eax,ebp
    L_0043fda0:
        push ecx
    L_0043fda1:
        push esi
    L_0043fda2:
        lea ecx,[esp+10Ch]
    L_0043fda9:
        call asm_FUN_0041ab70_0041ab70
    L_0043fdae:
        or dword ptr [ebp+35Ch],8
    L_0043fdb5:
        movzx edx,word ptr [ebx+2]
    L_0043fdb9:
        add edx,ebx
    L_0043fdbb:
        mov dword ptr [ebp+390h],edx
    L_0043fdc1:
        or edi,0FFFFFFFFh
    L_0043fdc4:
        jmp asm_target_0043eea4
    L_0043fdc9:
        mov edx,dword ptr [ebx+8]
    L_0043fdcc:
        mov eax,dword ptr [ebp+35Ch]
    L_0043fdd2:
        shl edx,16h
    L_0043fdd5:
        xor edx,eax
    L_0043fdd7:
        mov esi,eax
    L_0043fdd9:
        and edx,3C00000h
    L_0043fddf:
        xor esi,edx
    L_0043fde1:
        mov eax,esi
    L_0043fde3:
        and eax,3C00000h
    L_0043fde8:
        cmp eax,2800000h
    L_0043fded:
        mov dword ptr [ebp+35Ch],esi
    L_0043fdf3:
        jne asm_target_0043f532
    L_0043fdf9:
        mov edi,ebp
    L_0043fdfb:
        call asm_FUN_004452f0_004452f0
    L_0043fe00:
        movzx edx,word ptr [ebx+2]
    L_0043fe04:
        add edx,ebx
    L_0043fe06:
        mov dword ptr [ebp+390h],edx
    L_0043fe0c:
        or edi,0FFFFFFFFh
    L_0043fe0f:
        jmp asm_target_0043eea4
    L_0043fe14:
        lea eax,[ebp+340h]
    L_0043fe1a:
        mov edx,eax
    L_0043fe1c:
        mov esi,dword ptr [edx]
    L_0043fe1e:
        lea ecx,[ebp+334h]
    L_0043fe24:
        mov dword ptr [ecx],esi
    L_0043fe26:
        mov esi,dword ptr [edx+4]
    L_0043fe29:
        mov edx,dword ptr [edx+8]
    L_0043fe2c:
        mov dword ptr [ecx+4],esi
    L_0043fe2f:
        mov dword ptr [ecx+8],edx
    L_0043fe32:
        xor ecx,ecx
    L_0043fe34:
        mov dword ptr [eax],ecx
    L_0043fe36:
        mov dword ptr [ebp+344h],ecx
    L_0043fe3c:
        mov dword ptr [ebp+348h],ecx
    L_0043fe42:
        movzx edx,word ptr [ebx+2]
    L_0043fe46:
        add edx,ebx
    L_0043fe48:
        mov dword ptr [ebp+390h],edx
    L_0043fe4e:
        or edi,0FFFFFFFFh
    L_0043fe51:
        jmp asm_target_0043eea4
    L_0043fe56:
        mov eax,dword ptr [ebp+35Ch]
    L_0043fe5c:
        and eax,0FE7FFFFFh
    L_0043fe61:
        or eax,2400000h
    L_0043fe66:
        mov dword ptr [ebp+35Ch],eax
    L_0043fe6c:
        test byte ptr [ebx+6],1
    L_0043fe70:
        mov eax,dword ptr [ebx+8]
    L_0043fe73:
        je short L_0043fe7c
    L_0043fe75:
        mov ecx,ebp
    L_0043fe77:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043fe7c:
        imul eax,38h
    L_0043fe7f:
        push eax
    L_0043fe80:
        call asm_malloc_00452706
    L_0043fe85:
        mov dword ptr [ebp+358h],eax
    L_0043fe8b:
        movzx edx,word ptr [ebx+2]
    L_0043fe8f:
        add edx,ebx
    L_0043fe91:
        add esp,4
    L_0043fe94:
        mov dword ptr [ebp+390h],edx
    L_0043fe9a:
        or edi,0FFFFFFFFh
    L_0043fe9d:
        jmp asm_target_0043eea4
    L_0043fea2:
        test byte ptr [ebx+6],2
    L_0043fea6:
        je short L_0043feb6
    L_0043fea8:
        mov eax,dword ptr [ebx+0Ch]
    L_0043feab:
        mov ecx,ebp
    L_0043fead:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043feb2:
        mov esi,eax
    L_0043feb4:
        jmp short L_0043feb9
    L_0043feb6:
        mov esi,dword ptr [ebx+0Ch]
    L_0043feb9:
        xor eax,eax
    L_0043febb:
        mov ax,word ptr [ebx+6]
    L_0043febf:
        xor ecx,ecx
    L_0043fec1:
        mov edx,ebp
    L_0043fec3:
        push eax
    L_0043fec4:
        lea eax,[ebx+8]
    L_0043fec7:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_0043fecc:
        mov dword ptr [eax],esi
    L_0043fece:
        movzx edx,word ptr [ebx+2]
    L_0043fed2:
        add edx,ebx
    L_0043fed4:
        mov dword ptr [ebp+390h],edx
    L_0043feda:
        or edi,0FFFFFFFFh
    L_0043fedd:
        jmp asm_target_0043eea4
    L_0043fee2:
        test byte ptr [ebx+6],2
    L_0043fee6:
        je short L_0043fef9
    L_0043fee8:
        mov ecx,dword ptr [ebx+0Ch]
    L_0043feeb:
        push ecx
    L_0043feec:
        mov esi,ebp
    L_0043feee:
        call asm_FUN_0043eac0_0043eac0
    L_0043fef3:
        fstp dword ptr [esp+58h]
    L_0043fef7:
        jmp short L_0043ff00
    L_0043fef9:
        mov edx,dword ptr [ebx+0Ch]
    L_0043fefc:
        mov dword ptr [esp+58h],edx
    L_0043ff00:
        xor eax,eax
    L_0043ff02:
        mov ax,word ptr [ebx+6]
    L_0043ff06:
        lea edi,[ebx+8]
    L_0043ff09:
        xor ecx,ecx
    L_0043ff0b:
        mov esi,ebp
    L_0043ff0d:
        push eax
    L_0043ff0e:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0043ff13:
        mov ecx,dword ptr [esp+58h]
    L_0043ff17:
        mov dword ptr [eax],ecx
    L_0043ff19:
        movzx edx,word ptr [ebx+2]
    L_0043ff1d:
        add edx,ebx
    L_0043ff1f:
        mov dword ptr [ebp+390h],edx
    L_0043ff25:
        or edi,0FFFFFFFFh
    L_0043ff28:
        jmp asm_target_0043eea4
    L_0043ff2d:
        test byte ptr [ebx+6],2
    L_0043ff31:
        je short L_0043ff41
    L_0043ff33:
        mov eax,dword ptr [ebx+0Ch]
    L_0043ff36:
        mov ecx,ebp
    L_0043ff38:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043ff3d:
        mov edi,eax
    L_0043ff3f:
        jmp short L_0043ff44
    L_0043ff41:
        mov edi,dword ptr [ebx+0Ch]
    L_0043ff44:
        test byte ptr [ebx+6],4
    L_0043ff48:
        je short L_0043ff58
    L_0043ff4a:
        mov eax,dword ptr [ebx+10h]
    L_0043ff4d:
        mov ecx,ebp
    L_0043ff4f:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0043ff54:
        mov esi,eax
    L_0043ff56:
        jmp short L_0043ff5b
    L_0043ff58:
        mov esi,dword ptr [ebx+10h]
    L_0043ff5b:
        xor eax,eax
    L_0043ff5d:
        mov ax,word ptr [ebx+6]
    L_0043ff61:
        xor ecx,ecx
    L_0043ff63:
        mov edx,ebp
    L_0043ff65:
        push eax
    L_0043ff66:
        lea eax,[ebx+8]
    L_0043ff69:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_0043ff6e:
        add esi,edi
    L_0043ff70:
        mov dword ptr [eax],esi
    L_0043ff72:
        movzx edx,word ptr [ebx+2]
    L_0043ff76:
        add edx,ebx
    L_0043ff78:
        mov dword ptr [ebp+390h],edx
    L_0043ff7e:
        or edi,0FFFFFFFFh
    L_0043ff81:
        jmp asm_target_0043eea4
    L_0043ff86:
        test byte ptr [ebx+6],2
    L_0043ff8a:
        je short L_0043ff9d
    L_0043ff8c:
        mov edx,dword ptr [ebx+0Ch]
    L_0043ff8f:
        push edx
    L_0043ff90:
        mov esi,ebp
    L_0043ff92:
        call asm_FUN_0043eac0_0043eac0
    L_0043ff97:
        fstp dword ptr [esp+60h]
    L_0043ff9b:
        jmp short L_0043ffa4
    L_0043ff9d:
        mov eax,dword ptr [ebx+0Ch]
    L_0043ffa0:
        mov dword ptr [esp+60h],eax
    L_0043ffa4:
        test byte ptr [ebx+6],4
    L_0043ffa8:
        je short L_0043ffbe
    L_0043ffaa:
        mov ecx,dword ptr [ebx+10h]
    L_0043ffad:
        push ecx
    L_0043ffae:
        mov esi,ebp
    L_0043ffb0:
        call asm_FUN_0043eac0_0043eac0
    L_0043ffb5:
        fstp dword ptr [esp+0B0h]
    L_0043ffbc:
        jmp short L_0043ffc8
    L_0043ffbe:
        mov edx,dword ptr [ebx+10h]
    L_0043ffc1:
        mov dword ptr [esp+0B0h],edx
    L_0043ffc8:
        xor eax,eax
    L_0043ffca:
        mov ax,word ptr [ebx+6]
    L_0043ffce:
        lea edi,[ebx+8]
    L_0043ffd1:
        xor ecx,ecx
    L_0043ffd3:
        mov esi,ebp
    L_0043ffd5:
        push eax
    L_0043ffd6:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0043ffdb:
        fld dword ptr [esp+0B0h]
    L_0043ffe2:
        fadd dword ptr [esp+60h]
    L_0043ffe6:
        fstp dword ptr [eax]
    L_0043ffe8:
        movzx edx,word ptr [ebx+2]
    L_0043ffec:
        add edx,ebx
    L_0043ffee:
        mov dword ptr [ebp+390h],edx
    L_0043fff4:
        or edi,0FFFFFFFFh
    L_0043fff7:
        jmp asm_target_0043eea4
    L_0043fffc:
        test byte ptr [ebx+6],2
    L_00440000:
        je short L_00440010
    L_00440002:
        mov eax,dword ptr [ebx+0Ch]
    L_00440005:
        mov ecx,ebp
    L_00440007:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0044000c:
        mov esi,eax
    L_0044000e:
        jmp short L_00440013
    L_00440010:
        mov esi,dword ptr [ebx+0Ch]
    L_00440013:
        test byte ptr [ebx+6],4
    L_00440017:
        je short L_00440027
    L_00440019:
        mov eax,dword ptr [ebx+10h]
    L_0044001c:
        mov ecx,ebp
    L_0044001e:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440023:
        mov edi,eax
    L_00440025:
        jmp short L_0044002a
    L_00440027:
        mov edi,dword ptr [ebx+10h]
    L_0044002a:
        xor eax,eax
    L_0044002c:
        mov ax,word ptr [ebx+6]
    L_00440030:
        xor ecx,ecx
    L_00440032:
        mov edx,ebp
    L_00440034:
        push eax
    L_00440035:
        lea eax,[ebx+8]
    L_00440038:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_0044003d:
        sub esi,edi
    L_0044003f:
        mov dword ptr [eax],esi
    L_00440041:
        movzx edx,word ptr [ebx+2]
    L_00440045:
        add edx,ebx
    L_00440047:
        mov dword ptr [ebp+390h],edx
    L_0044004d:
        or edi,0FFFFFFFFh
    L_00440050:
        jmp asm_target_0043eea4
    L_00440055:
        test byte ptr [ebx+6],2
    L_00440059:
        je short L_0044006f
    L_0044005b:
        mov ecx,dword ptr [ebx+0Ch]
    L_0044005e:
        push ecx
    L_0044005f:
        mov esi,ebp
    L_00440061:
        call asm_FUN_0043eac0_0043eac0
    L_00440066:
        fstp dword ptr [esp+0A8h]
    L_0044006d:
        jmp short L_00440079
    L_0044006f:
        mov edx,dword ptr [ebx+0Ch]
    L_00440072:
        mov dword ptr [esp+0A8h],edx
    L_00440079:
        test byte ptr [ebx+6],4
    L_0044007d:
        je short L_00440090
    L_0044007f:
        mov eax,dword ptr [ebx+10h]
    L_00440082:
        push eax
    L_00440083:
        mov esi,ebp
    L_00440085:
        call asm_FUN_0043eac0_0043eac0
    L_0044008a:
        fstp dword ptr [esp+68h]
    L_0044008e:
        jmp short L_00440097
    L_00440090:
        mov ecx,dword ptr [ebx+10h]
    L_00440093:
        mov dword ptr [esp+68h],ecx
    L_00440097:
        xor edx,edx
    L_00440099:
        mov dx,word ptr [ebx+6]
    L_0044009d:
        lea edi,[ebx+8]
    L_004400a0:
        xor ecx,ecx
    L_004400a2:
        mov esi,ebp
    L_004400a4:
        push edx
    L_004400a5:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_004400aa:
        fld dword ptr [esp+0A8h]
    L_004400b1:
        fsub dword ptr [esp+68h]
    L_004400b5:
        fstp dword ptr [eax]
    L_004400b7:
        movzx edx,word ptr [ebx+2]
    L_004400bb:
        add edx,ebx
    L_004400bd:
        mov dword ptr [ebp+390h],edx
    L_004400c3:
        or edi,0FFFFFFFFh
    L_004400c6:
        jmp asm_target_0043eea4
    L_004400cb:
        test byte ptr [ebx+6],2
    L_004400cf:
        je short L_004400df
    L_004400d1:
        mov eax,dword ptr [ebx+0Ch]
    L_004400d4:
        mov ecx,ebp
    L_004400d6:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_004400db:
        mov edi,eax
    L_004400dd:
        jmp short L_004400e2
    L_004400df:
        mov edi,dword ptr [ebx+0Ch]
    L_004400e2:
        test byte ptr [ebx+6],4
    L_004400e6:
        je short L_004400f6
    L_004400e8:
        mov eax,dword ptr [ebx+10h]
    L_004400eb:
        mov ecx,ebp
    L_004400ed:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_004400f2:
        mov esi,eax
    L_004400f4:
        jmp short L_004400f9
    L_004400f6:
        mov esi,dword ptr [ebx+10h]
    L_004400f9:
        xor eax,eax
    L_004400fb:
        mov ax,word ptr [ebx+6]
    L_004400ff:
        xor ecx,ecx
    L_00440101:
        mov edx,ebp
    L_00440103:
        push eax
    L_00440104:
        lea eax,[ebx+8]
    L_00440107:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_0044010c:
        imul esi,edi
    L_0044010f:
        mov dword ptr [eax],esi
    L_00440111:
        movzx edx,word ptr [ebx+2]
    L_00440115:
        add edx,ebx
    L_00440117:
        mov dword ptr [ebp+390h],edx
    L_0044011d:
        or edi,0FFFFFFFFh
    L_00440120:
        jmp asm_target_0043eea4
    L_00440125:
        test byte ptr [ebx+6],2
    L_00440129:
        je short L_0044013c
    L_0044012b:
        mov eax,dword ptr [ebx+0Ch]
    L_0044012e:
        push eax
    L_0044012f:
        mov esi,ebp
    L_00440131:
        call asm_FUN_0043eac0_0043eac0
    L_00440136:
        fstp dword ptr [esp+70h]
    L_0044013a:
        jmp short L_00440143
    L_0044013c:
        mov ecx,dword ptr [ebx+0Ch]
    L_0044013f:
        mov dword ptr [esp+70h],ecx
    L_00440143:
        test byte ptr [ebx+6],4
    L_00440147:
        je short L_0044015d
    L_00440149:
        mov edx,dword ptr [ebx+10h]
    L_0044014c:
        push edx
    L_0044014d:
        mov esi,ebp
    L_0044014f:
        call asm_FUN_0043eac0_0043eac0
    L_00440154:
        fstp dword ptr [esp+0B8h]
    L_0044015b:
        jmp short L_00440167
    L_0044015d:
        mov eax,dword ptr [ebx+10h]
    L_00440160:
        mov dword ptr [esp+0B8h],eax
    L_00440167:
        xor ecx,ecx
    L_00440169:
        mov cx,word ptr [ebx+6]
    L_0044016d:
        lea edi,[ebx+8]
    L_00440170:
        mov esi,ebp
    L_00440172:
        push ecx
    L_00440173:
        xor ecx,ecx
    L_00440175:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0044017a:
        fld dword ptr [esp+0B8h]
    L_00440181:
        fmul dword ptr [esp+70h]
    L_00440185:
        fstp dword ptr [eax]
    L_00440187:
        movzx edx,word ptr [ebx+2]
    L_0044018b:
        add edx,ebx
    L_0044018d:
        mov dword ptr [ebp+390h],edx
    L_00440193:
        or edi,0FFFFFFFFh
    L_00440196:
        jmp asm_target_0043eea4
    L_0044019b:
        test byte ptr [ebx+6],2
    L_0044019f:
        je short L_004401af
    L_004401a1:
        mov eax,dword ptr [ebx+0Ch]
    L_004401a4:
        mov ecx,ebp
    L_004401a6:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_004401ab:
        mov edi,eax
    L_004401ad:
        jmp short L_004401b2
    L_004401af:
        mov edi,dword ptr [ebx+0Ch]
    L_004401b2:
        test byte ptr [ebx+6],4
    L_004401b6:
        je short L_004401c6
    L_004401b8:
        mov eax,dword ptr [ebx+10h]
    L_004401bb:
        mov ecx,ebp
    L_004401bd:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_004401c2:
        mov esi,eax
    L_004401c4:
        jmp short L_004401c9
    L_004401c6:
        mov esi,dword ptr [ebx+10h]
    L_004401c9:
        xor eax,eax
    L_004401cb:
        mov ax,word ptr [ebx+6]
    L_004401cf:
        xor ecx,ecx
    L_004401d1:
        mov edx,ebp
    L_004401d3:
        push eax
    L_004401d4:
        lea eax,[ebx+8]
    L_004401d7:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_004401dc:
        mov ecx,eax
    L_004401de:
        mov eax,edi
    L_004401e0:
        cdq
    L_004401e1:
        idiv esi
    L_004401e3:
        mov dword ptr [ecx],eax
    L_004401e5:
        movzx edx,word ptr [ebx+2]
    L_004401e9:
        add edx,ebx
    L_004401eb:
        mov dword ptr [ebp+390h],edx
    L_004401f1:
        or edi,0FFFFFFFFh
    L_004401f4:
        jmp asm_target_0043eea4
    L_004401f9:
        test byte ptr [ebx+6],2
    L_004401fd:
        je short L_00440213
    L_004401ff:
        mov edx,dword ptr [ebx+0Ch]
    L_00440202:
        push edx
    L_00440203:
        mov esi,ebp
    L_00440205:
        call asm_FUN_0043eac0_0043eac0
    L_0044020a:
        fstp dword ptr [esp+0C0h]
    L_00440211:
        jmp short L_0044021d
    L_00440213:
        mov eax,dword ptr [ebx+0Ch]
    L_00440216:
        mov dword ptr [esp+0C0h],eax
    L_0044021d:
        test byte ptr [ebx+6],4
    L_00440221:
        je short L_00440234
    L_00440223:
        mov ecx,dword ptr [ebx+10h]
    L_00440226:
        push ecx
    L_00440227:
        mov esi,ebp
    L_00440229:
        call asm_FUN_0043eac0_0043eac0
    L_0044022e:
        fstp dword ptr [esp+78h]
    L_00440232:
        jmp short L_0044023b
    L_00440234:
        mov edx,dword ptr [ebx+10h]
    L_00440237:
        mov dword ptr [esp+78h],edx
    L_0044023b:
        xor eax,eax
    L_0044023d:
        mov ax,word ptr [ebx+6]
    L_00440241:
        lea edi,[ebx+8]
    L_00440244:
        xor ecx,ecx
    L_00440246:
        mov esi,ebp
    L_00440248:
        push eax
    L_00440249:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0044024e:
        fld dword ptr [esp+0C0h]
    L_00440255:
        fdiv dword ptr [esp+78h]
    L_00440259:
        fstp dword ptr [eax]
    L_0044025b:
        movzx edx,word ptr [ebx+2]
    L_0044025f:
        add edx,ebx
    L_00440261:
        mov dword ptr [ebp+390h],edx
    L_00440267:
        or edi,0FFFFFFFFh
    L_0044026a:
        jmp asm_target_0043eea4
    L_0044026f:
        test byte ptr [ebx+6],2
    L_00440273:
        je short L_00440283
    L_00440275:
        mov eax,dword ptr [ebx+0Ch]
    L_00440278:
        mov ecx,ebp
    L_0044027a:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_0044027f:
        mov edi,eax
    L_00440281:
        jmp short L_00440286
    L_00440283:
        mov edi,dword ptr [ebx+0Ch]
    L_00440286:
        test byte ptr [ebx+6],4
    L_0044028a:
        je short L_0044029a
    L_0044028c:
        mov eax,dword ptr [ebx+10h]
    L_0044028f:
        mov ecx,ebp
    L_00440291:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440296:
        mov esi,eax
    L_00440298:
        jmp short L_0044029d
    L_0044029a:
        mov esi,dword ptr [ebx+10h]
    L_0044029d:
        xor eax,eax
    L_0044029f:
        mov ax,word ptr [ebx+6]
    L_004402a3:
        xor ecx,ecx
    L_004402a5:
        mov edx,ebp
    L_004402a7:
        push eax
    L_004402a8:
        lea eax,[ebx+8]
    L_004402ab:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_004402b0:
        mov ecx,eax
    L_004402b2:
        mov eax,edi
    L_004402b4:
        cdq
    L_004402b5:
        idiv esi
    L_004402b7:
        mov dword ptr [ecx],edx
    L_004402b9:
        movzx edx,word ptr [ebx+2]
    L_004402bd:
        add edx,ebx
    L_004402bf:
        mov dword ptr [ebp+390h],edx
    L_004402c5:
        or edi,0FFFFFFFFh
    L_004402c8:
        jmp asm_target_0043eea4
    L_004402cd:
        test byte ptr [ebx+6],4
    L_004402d1:
        je short L_004402e7
    L_004402d3:
        mov ecx,dword ptr [ebx+10h]
    L_004402d6:
        push ecx
    L_004402d7:
        mov esi,ebp
    L_004402d9:
        call asm_FUN_0043eac0_0043eac0
    L_004402de:
        fstp dword ptr [esp+80h]
    L_004402e5:
        jmp short L_004402f1
    L_004402e7:
        mov edx,dword ptr [ebx+10h]
    L_004402ea:
        mov dword ptr [esp+80h],edx
    L_004402f1:
        test byte ptr [ebx+6],2
    L_004402f5:
        je short L_0044030b
    L_004402f7:
        mov eax,dword ptr [ebx+0Ch]
    L_004402fa:
        push eax
    L_004402fb:
        mov esi,ebp
    L_004402fd:
        call asm_FUN_0043eac0_0043eac0
    L_00440302:
        fstp dword ptr [esp+0B4h]
    L_00440309:
        jmp short L_00440315
    L_0044030b:
        mov ecx,dword ptr [ebx+0Ch]
    L_0044030e:
        mov dword ptr [esp+0B4h],ecx
    L_00440315:
        xor edx,edx
    L_00440317:
        mov dx,word ptr [ebx+6]
    L_0044031b:
        lea edi,[ebx+8]
    L_0044031e:
        xor ecx,ecx
    L_00440320:
        mov esi,ebp
    L_00440322:
        push edx
    L_00440323:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_00440328:
        fld dword ptr [esp+0B4h]
    L_0044032f:
        fld dword ptr [esp+80h]
    L_00440336:
        mov esi,eax
    L_00440338:
        call asm_FUN_00463bba_00463bba
    L_0044033d:
        fstp dword ptr [esi]
    L_0044033f:
        movzx edx,word ptr [ebx+2]
    L_00440343:
        add edx,ebx
    L_00440345:
        mov dword ptr [ebp+390h],edx
    L_0044034b:
        or edi,0FFFFFFFFh
    L_0044034e:
        jmp asm_target_0043eea4
    L_00440353:
        test byte ptr [ebx+6],2
    L_00440357:
        je short L_00440367
    L_00440359:
        mov eax,dword ptr [ebx+0Ch]
    L_0044035c:
        mov ecx,ebp
    L_0044035e:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440363:
        mov esi,eax
    L_00440365:
        jmp short L_0044036a
    L_00440367:
        mov esi,dword ptr [ebx+0Ch]
    L_0044036a:
        xor eax,eax
    L_0044036c:
        mov ax,word ptr [ebx+6]
    L_00440370:
        xor ecx,ecx
    L_00440372:
        mov edx,ebp
    L_00440374:
        push eax
    L_00440375:
        lea eax,[ebx+8]
    L_00440378:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_0044037d:
        add dword ptr [eax],esi
    L_0044037f:
        movzx edx,word ptr [ebx+2]
    L_00440383:
        add edx,ebx
    L_00440385:
        mov dword ptr [ebp+390h],edx
    L_0044038b:
        or edi,0FFFFFFFFh
    L_0044038e:
        jmp asm_target_0043eea4
    L_00440393:
        test byte ptr [ebx+6],2
    L_00440397:
        je short L_004403aa
    L_00440399:
        mov eax,dword ptr [ebx+0Ch]
    L_0044039c:
        push eax
    L_0044039d:
        mov esi,ebp
    L_0044039f:
        call asm_FUN_0043eac0_0043eac0
    L_004403a4:
        fstp dword ptr [esp+40h]
    L_004403a8:
        jmp short L_004403b1
    L_004403aa:
        mov ecx,dword ptr [ebx+0Ch]
    L_004403ad:
        mov dword ptr [esp+40h],ecx
    L_004403b1:
        xor edx,edx
    L_004403b3:
        mov dx,word ptr [ebx+6]
    L_004403b7:
        lea edi,[ebx+8]
    L_004403ba:
        xor ecx,ecx
    L_004403bc:
        mov esi,ebp
    L_004403be:
        push edx
    L_004403bf:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_004403c4:
        fld dword ptr [esp+40h]
    L_004403c8:
        fadd dword ptr [eax]
    L_004403ca:
        fstp dword ptr [eax]
    L_004403cc:
        movzx edx,word ptr [ebx+2]
    L_004403d0:
        add edx,ebx
    L_004403d2:
        mov dword ptr [ebp+390h],edx
    L_004403d8:
        or edi,0FFFFFFFFh
    L_004403db:
        jmp asm_target_0043eea4
    L_004403e0:
        test byte ptr [ebx+6],2
    L_004403e4:
        je short L_004403f4
    L_004403e6:
        mov eax,dword ptr [ebx+0Ch]
    L_004403e9:
        mov ecx,ebp
    L_004403eb:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_004403f0:
        mov esi,eax
    L_004403f2:
        jmp short L_004403f7
    L_004403f4:
        mov esi,dword ptr [ebx+0Ch]
    L_004403f7:
        xor eax,eax
    L_004403f9:
        mov ax,word ptr [ebx+6]
    L_004403fd:
        xor ecx,ecx
    L_004403ff:
        mov edx,ebp
    L_00440401:
        push eax
    L_00440402:
        lea eax,[ebx+8]
    L_00440405:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_0044040a:
        sub dword ptr [eax],esi
    L_0044040c:
        movzx edx,word ptr [ebx+2]
    L_00440410:
        add edx,ebx
    L_00440412:
        mov dword ptr [ebp+390h],edx
    L_00440418:
        or edi,0FFFFFFFFh
    L_0044041b:
        jmp asm_target_0043eea4
    L_00440420:
        test byte ptr [ebx+6],2
    L_00440424:
        je short L_0044043a
    L_00440426:
        mov eax,dword ptr [ebx+0Ch]
    L_00440429:
        push eax
    L_0044042a:
        mov esi,ebp
    L_0044042c:
        call asm_FUN_0043eac0_0043eac0
    L_00440431:
        fstp dword ptr [esp+88h]
    L_00440438:
        jmp short L_00440444
    L_0044043a:
        mov ecx,dword ptr [ebx+0Ch]
    L_0044043d:
        mov dword ptr [esp+88h],ecx
    L_00440444:
        xor edx,edx
    L_00440446:
        mov dx,word ptr [ebx+6]
    L_0044044a:
        lea edi,[ebx+8]
    L_0044044d:
        xor ecx,ecx
    L_0044044f:
        mov esi,ebp
    L_00440451:
        push edx
    L_00440452:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_00440457:
        fld dword ptr [eax]
    L_00440459:
        fsub dword ptr [esp+88h]
    L_00440460:
        fstp dword ptr [eax]
    L_00440462:
        movzx edx,word ptr [ebx+2]
    L_00440466:
        add edx,ebx
    L_00440468:
        mov dword ptr [ebp+390h],edx
    L_0044046e:
        or edi,0FFFFFFFFh
    L_00440471:
        jmp asm_target_0043eea4
    L_00440476:
        test byte ptr [ebx+6],2
    L_0044047a:
        je short L_0044048a
    L_0044047c:
        mov eax,dword ptr [ebx+0Ch]
    L_0044047f:
        mov ecx,ebp
    L_00440481:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440486:
        mov esi,eax
    L_00440488:
        jmp short L_0044048d
    L_0044048a:
        mov esi,dword ptr [ebx+0Ch]
    L_0044048d:
        xor eax,eax
    L_0044048f:
        mov ax,word ptr [ebx+6]
    L_00440493:
        xor ecx,ecx
    L_00440495:
        mov edx,ebp
    L_00440497:
        push eax
    L_00440498:
        lea eax,[ebx+8]
    L_0044049b:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_004404a0:
        mov ecx,dword ptr [eax]
    L_004404a2:
        imul ecx,esi
    L_004404a5:
        mov dword ptr [eax],ecx
    L_004404a7:
        movzx edx,word ptr [ebx+2]
    L_004404ab:
        add edx,ebx
    L_004404ad:
        mov dword ptr [ebp+390h],edx
    L_004404b3:
        or edi,0FFFFFFFFh
    L_004404b6:
        jmp asm_target_0043eea4
    L_004404bb:
        test byte ptr [ebx+6],2
    L_004404bf:
        je short L_004404d5
    L_004404c1:
        mov edx,dword ptr [ebx+0Ch]
    L_004404c4:
        push edx
    L_004404c5:
        mov esi,ebp
    L_004404c7:
        call asm_FUN_0043eac0_0043eac0
    L_004404cc:
        fstp dword ptr [esp+0BCh]
    L_004404d3:
        jmp short L_004404df
    L_004404d5:
        mov eax,dword ptr [ebx+0Ch]
    L_004404d8:
        mov dword ptr [esp+0BCh],eax
    L_004404df:
        xor ecx,ecx
    L_004404e1:
        mov cx,word ptr [ebx+6]
    L_004404e5:
        lea edi,[ebx+8]
    L_004404e8:
        mov esi,ebp
    L_004404ea:
        push ecx
    L_004404eb:
        xor ecx,ecx
    L_004404ed:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_004404f2:
        fld dword ptr [esp+0BCh]
    L_004404f9:
        fmul dword ptr [eax]
    L_004404fb:
        fstp dword ptr [eax]
    L_004404fd:
        movzx edx,word ptr [ebx+2]
    L_00440501:
        add edx,ebx
    L_00440503:
        mov dword ptr [ebp+390h],edx
    L_00440509:
        or edi,0FFFFFFFFh
    L_0044050c:
        jmp asm_target_0043eea4
    L_00440511:
        test byte ptr [ebx+6],2
    L_00440515:
        je short L_00440525
    L_00440517:
        mov eax,dword ptr [ebx+0Ch]
    L_0044051a:
        mov ecx,ebp
    L_0044051c:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440521:
        mov esi,eax
    L_00440523:
        jmp short L_00440528
    L_00440525:
        mov esi,dword ptr [ebx+0Ch]
    L_00440528:
        xor eax,eax
    L_0044052a:
        mov ax,word ptr [ebx+6]
    L_0044052e:
        xor ecx,ecx
    L_00440530:
        mov edx,ebp
    L_00440532:
        push eax
    L_00440533:
        lea eax,[ebx+8]
    L_00440536:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_0044053b:
        mov ecx,eax
    L_0044053d:
        mov eax,dword ptr [ecx]
    L_0044053f:
        cdq
    L_00440540:
        idiv esi
    L_00440542:
        mov dword ptr [ecx],eax
    L_00440544:
        movzx edx,word ptr [ebx+2]
    L_00440548:
        add edx,ebx
    L_0044054a:
        mov dword ptr [ebp+390h],edx
    L_00440550:
        or edi,0FFFFFFFFh
    L_00440553:
        jmp asm_target_0043eea4
    L_00440558:
        test byte ptr [ebx+6],2
    L_0044055c:
        je short L_00440572
    L_0044055e:
        mov edx,dword ptr [ebx+0Ch]
    L_00440561:
        push edx
    L_00440562:
        mov esi,ebp
    L_00440564:
        call asm_FUN_0043eac0_0043eac0
    L_00440569:
        fstp dword ptr [esp+90h]
    L_00440570:
        jmp short L_0044057c
    L_00440572:
        mov eax,dword ptr [ebx+0Ch]
    L_00440575:
        mov dword ptr [esp+90h],eax
    L_0044057c:
        xor ecx,ecx
    L_0044057e:
        mov cx,word ptr [ebx+6]
    L_00440582:
        lea edi,[ebx+8]
    L_00440585:
        mov esi,ebp
    L_00440587:
        push ecx
    L_00440588:
        xor ecx,ecx
    L_0044058a:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0044058f:
        fld dword ptr [eax]
    L_00440591:
        fdiv dword ptr [esp+90h]
    L_00440598:
        fstp dword ptr [eax]
    L_0044059a:
        movzx edx,word ptr [ebx+2]
    L_0044059e:
        add edx,ebx
    L_004405a0:
        mov dword ptr [ebp+390h],edx
    L_004405a6:
        or edi,0FFFFFFFFh
    L_004405a9:
        jmp asm_target_0043eea4
    L_004405ae:
        test byte ptr [ebx+6],2
    L_004405b2:
        je short L_004405c2
    L_004405b4:
        mov eax,dword ptr [ebx+0Ch]
    L_004405b7:
        mov ecx,ebp
    L_004405b9:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_004405be:
        mov esi,eax
    L_004405c0:
        jmp short L_004405c5
    L_004405c2:
        mov esi,dword ptr [ebx+0Ch]
    L_004405c5:
        xor eax,eax
    L_004405c7:
        mov ax,word ptr [ebx+6]
    L_004405cb:
        xor ecx,ecx
    L_004405cd:
        mov edx,ebp
    L_004405cf:
        push eax
    L_004405d0:
        lea eax,[ebx+8]
    L_004405d3:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_004405d8:
        mov ecx,eax
    L_004405da:
        mov eax,dword ptr [ecx]
    L_004405dc:
        cdq
    L_004405dd:
        idiv esi
    L_004405df:
        mov dword ptr [ecx],edx
    L_004405e1:
        movzx edx,word ptr [ebx+2]
    L_004405e5:
        add edx,ebx
    L_004405e7:
        mov dword ptr [ebp+390h],edx
    L_004405ed:
        or edi,0FFFFFFFFh
    L_004405f0:
        jmp asm_target_0043eea4
    L_004405f5:
        test byte ptr [ebx+6],2
    L_004405f9:
        je short L_0044060f
    L_004405fb:
        mov edx,dword ptr [ebx+0Ch]
    L_004405fe:
        push edx
    L_004405ff:
        mov esi,ebp
    L_00440601:
        call asm_FUN_0043eac0_0043eac0
    L_00440606:
        fstp dword ptr [esp+98h]
    L_0044060d:
        jmp short L_00440619
    L_0044060f:
        mov eax,dword ptr [ebx+0Ch]
    L_00440612:
        mov dword ptr [esp+98h],eax
    L_00440619:
        test byte ptr [ebx+6],1
    L_0044061d:
        lea edi,[ebx+8]
    L_00440620:
        je short L_00440635
    L_00440622:
        mov ecx,dword ptr [edi]
    L_00440624:
        push ecx
    L_00440625:
        mov esi,ebp
    L_00440627:
        call asm_FUN_0043eac0_0043eac0
    L_0044062c:
        fstp dword ptr [esp+0CCh]
    L_00440633:
        jmp short L_0044063e
    L_00440635:
        mov edx,dword ptr [edi]
    L_00440637:
        mov dword ptr [esp+0CCh],edx
    L_0044063e:
        xor eax,eax
    L_00440640:
        mov ax,word ptr [ebx+6]
    L_00440644:
        xor ecx,ecx
    L_00440646:
        mov esi,ebp
    L_00440648:
        push eax
    L_00440649:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0044064e:
        fld dword ptr [esp+0CCh]
    L_00440655:
        fld dword ptr [esp+98h]
    L_0044065c:
        mov esi,eax
    L_0044065e:
        call asm_FUN_00463bba_00463bba
    L_00440663:
        fstp dword ptr [esi]
    L_00440665:
        movzx edx,word ptr [ebx+2]
    L_00440669:
        add edx,ebx
    L_0044066b:
        mov dword ptr [ebp+390h],edx
    L_00440671:
        or edi,0FFFFFFFFh
    L_00440674:
        jmp asm_target_0043eea4
    L_00440679:
        test dword ptr [ebp+35Ch],40000000h
    L_00440683:
        mov al,byte ptr [ebx+6]
    L_00440686:
        je short L_0044069d
    L_00440688:
        test al,2
    L_0044068a:
        mov eax,dword ptr [ebx+0Ch]
    L_0044068d:
        je short L_00440696
    L_0044068f:
        mov ecx,ebp
    L_00440691:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440696:
        mov ecx,4918A8h
    L_0044069b:
        jmp short L_004406b0
    L_0044069d:
        test al,2
    L_0044069f:
        mov eax,dword ptr [ebx+0Ch]
    L_004406a2:
        je short L_004406ab
    L_004406a4:
        mov ecx,ebp
    L_004406a6:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_004406ab:
        mov ecx,4918B0h
    L_004406b0:
        mov edi,eax
    L_004406b2:
        call asm_EntityScript_NextRandomModulo_0043cb80
    L_004406b7:
        xor ecx,ecx
    L_004406b9:
        mov cx,word ptr [ebx+6]
    L_004406bd:
        mov esi,eax
    L_004406bf:
        lea eax,[ebx+8]
    L_004406c2:
        mov edx,ebp
    L_004406c4:
        push ecx
    L_004406c5:
        xor ecx,ecx
    L_004406c7:
        call asm_AnimationObject_ResolveIntegerVariable_0043eda0
    L_004406cc:
        mov dword ptr [eax],esi
    L_004406ce:
        movzx edx,word ptr [ebx+2]
    L_004406d2:
        add edx,ebx
    L_004406d4:
        mov dword ptr [ebp+390h],edx
    L_004406da:
        or edi,0FFFFFFFFh
    L_004406dd:
        jmp asm_target_0043eea4
    L_004406e2:
        test dword ptr [ebp+35Ch],40000000h
    L_004406ec:
        mov al,byte ptr [ebx+6]
    L_004406ef:
        je short L_00440711
    L_004406f1:
        test al,2
    L_004406f3:
        je short L_00440707
    L_004406f5:
        mov edx,dword ptr [ebx+0Ch]
    L_004406f8:
        push edx
    L_004406f9:
        mov esi,ebp
    L_004406fb:
        call asm_FUN_0043eac0_0043eac0
    L_00440700:
        mov ecx,4918A8h
    L_00440705:
        jmp short L_0044072a
    L_00440707:
        fld dword ptr [ebx+0Ch]
    L_0044070a:
        mov ecx,4918A8h
    L_0044070f:
        jmp short L_0044072a
    L_00440711:
        test al,2
    L_00440713:
        je short L_00440722
    L_00440715:
        mov eax,dword ptr [ebx+0Ch]
    L_00440718:
        push eax
    L_00440719:
        mov esi,ebp
    L_0044071b:
        call asm_FUN_0043eac0_0043eac0
    L_00440720:
        jmp short L_00440725
    L_00440722:
        fld dword ptr [ebx+0Ch]
    L_00440725:
        mov ecx,4918B0h
    L_0044072a:
        call asm_Rng_NextFloat_0044bb20
    L_0044072f:
        fmul st,st(1)
    L_00440731:
        xor ecx,ecx
    L_00440733:
        mov cx,word ptr [ebx+6]
    L_00440737:
        fstp dword ptr [esp+14h]
    L_0044073b:
        lea edi,[ebx+8]
    L_0044073e:
        mov esi,ebp
    L_00440740:
        fstp st(0)
    L_00440742:
        push ecx
    L_00440743:
        xor ecx,ecx
    L_00440745:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0044074a:
        mov edx,dword ptr [esp+14h]
    L_0044074e:
        mov dword ptr [eax],edx
    L_00440750:
        movzx edx,word ptr [ebx+2]
    L_00440754:
        add edx,ebx
    L_00440756:
        mov dword ptr [ebp+390h],edx
    L_0044075c:
        or edi,0FFFFFFFFh
    L_0044075f:
        jmp asm_target_0043eea4
    L_00440764:
        test byte ptr [ebx+6],2
    L_00440768:
        je short L_0044077b
    L_0044076a:
        mov eax,dword ptr [ebx+0Ch]
    L_0044076d:
        push eax
    L_0044076e:
        mov esi,ebp
    L_00440770:
        call asm_FUN_0043eac0_0043eac0
    L_00440775:
        fstp dword ptr [esp+44h]
    L_00440779:
        jmp short L_00440782
    L_0044077b:
        mov ecx,dword ptr [ebx+0Ch]
    L_0044077e:
        mov dword ptr [esp+44h],ecx
    L_00440782:
        xor edx,edx
    L_00440784:
        mov dx,word ptr [ebx+6]
    L_00440788:
        lea edi,[ebx+8]
    L_0044078b:
        xor ecx,ecx
    L_0044078d:
        mov esi,ebp
    L_0044078f:
        push edx
    L_00440790:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_00440795:
        fld dword ptr [esp+44h]
    L_00440799:
        fsin
    L_0044079b:
        fstp dword ptr [eax]
    L_0044079d:
        movzx edx,word ptr [ebx+2]
    L_004407a1:
        add edx,ebx
    L_004407a3:
        mov dword ptr [ebp+390h],edx
    L_004407a9:
        or edi,0FFFFFFFFh
    L_004407ac:
        jmp asm_target_0043eea4
    L_004407b1:
        test byte ptr [ebx+6],2
    L_004407b5:
        je short L_004407c8
    L_004407b7:
        mov eax,dword ptr [ebx+0Ch]
    L_004407ba:
        push eax
    L_004407bb:
        mov esi,ebp
    L_004407bd:
        call asm_FUN_0043eac0_0043eac0
    L_004407c2:
        fstp dword ptr [esp+4Ch]
    L_004407c6:
        jmp short L_004407cf
    L_004407c8:
        mov ecx,dword ptr [ebx+0Ch]
    L_004407cb:
        mov dword ptr [esp+4Ch],ecx
    L_004407cf:
        xor edx,edx
    L_004407d1:
        mov dx,word ptr [ebx+6]
    L_004407d5:
        lea edi,[ebx+8]
    L_004407d8:
        xor ecx,ecx
    L_004407da:
        mov esi,ebp
    L_004407dc:
        push edx
    L_004407dd:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_004407e2:
        fld dword ptr [esp+4Ch]
    L_004407e6:
        fcos
    L_004407e8:
        fstp dword ptr [eax]
    L_004407ea:
        movzx edx,word ptr [ebx+2]
    L_004407ee:
        add edx,ebx
    L_004407f0:
        mov dword ptr [ebp+390h],edx
    L_004407f6:
        or edi,0FFFFFFFFh
    L_004407f9:
        jmp asm_target_0043eea4
    L_004407fe:
        test byte ptr [ebx+6],2
    L_00440802:
        je short L_00440815
    L_00440804:
        mov eax,dword ptr [ebx+0Ch]
    L_00440807:
        push eax
    L_00440808:
        mov esi,ebp
    L_0044080a:
        call asm_FUN_0043eac0_0043eac0
    L_0044080f:
        fstp dword ptr [esp+54h]
    L_00440813:
        jmp short L_0044081c
    L_00440815:
        mov ecx,dword ptr [ebx+0Ch]
    L_00440818:
        mov dword ptr [esp+54h],ecx
    L_0044081c:
        xor edx,edx
    L_0044081e:
        mov dx,word ptr [ebx+6]
    L_00440822:
        lea edi,[ebx+8]
    L_00440825:
        xor ecx,ecx
    L_00440827:
        mov esi,ebp
    L_00440829:
        push edx
    L_0044082a:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0044082f:
        fld dword ptr [esp+54h]
    L_00440833:
        fptan
    L_00440835:
        fstp st(0)
    L_00440837:
        fstp dword ptr [eax]
    L_00440839:
        movzx edx,word ptr [ebx+2]
    L_0044083d:
        add edx,ebx
    L_0044083f:
        mov dword ptr [ebp+390h],edx
    L_00440845:
        or edi,0FFFFFFFFh
    L_00440848:
        jmp asm_target_0043eea4
    L_0044084d:
        test byte ptr [ebx+6],2
    L_00440851:
        je short L_00440864
    L_00440853:
        mov eax,dword ptr [ebx+0Ch]
    L_00440856:
        push eax
    L_00440857:
        mov esi,ebp
    L_00440859:
        call asm_FUN_0043eac0_0043eac0
    L_0044085e:
        fstp dword ptr [esp+5Ch]
    L_00440862:
        jmp short L_0044086b
    L_00440864:
        mov ecx,dword ptr [ebx+0Ch]
    L_00440867:
        mov dword ptr [esp+5Ch],ecx
    L_0044086b:
        xor edx,edx
    L_0044086d:
        mov dx,word ptr [ebx+6]
    L_00440871:
        lea edi,[ebx+8]
    L_00440874:
        xor ecx,ecx
    L_00440876:
        mov esi,ebp
    L_00440878:
        push edx
    L_00440879:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0044087e:
        fld dword ptr [esp+5Ch]
    L_00440882:
        mov esi,eax
    L_00440884:
        call asm_FUN_00463bf0_00463bf0
    L_00440889:
        fstp dword ptr [esi]
    L_0044088b:
        movzx edx,word ptr [ebx+2]
    L_0044088f:
        add edx,ebx
    L_00440891:
        mov dword ptr [ebp+390h],edx
    L_00440897:
        or edi,0FFFFFFFFh
    L_0044089a:
        jmp asm_target_0043eea4
    L_0044089f:
        test byte ptr [ebx+6],2
    L_004408a3:
        je short L_004408b6
    L_004408a5:
        mov eax,dword ptr [ebx+0Ch]
    L_004408a8:
        push eax
    L_004408a9:
        mov esi,ebp
    L_004408ab:
        call asm_FUN_0043eac0_0043eac0
    L_004408b0:
        fstp dword ptr [esp+64h]
    L_004408b4:
        jmp short L_004408bd
    L_004408b6:
        mov ecx,dword ptr [ebx+0Ch]
    L_004408b9:
        mov dword ptr [esp+64h],ecx
    L_004408bd:
        xor edx,edx
    L_004408bf:
        mov dx,word ptr [ebx+6]
    L_004408c3:
        lea edi,[ebx+8]
    L_004408c6:
        xor ecx,ecx
    L_004408c8:
        mov esi,ebp
    L_004408ca:
        push edx
    L_004408cb:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_004408d0:
        fld dword ptr [esp+64h]
    L_004408d4:
        fld1
    L_004408d6:
        fpatan
    L_004408d8:
        fstp dword ptr [eax]
    L_004408da:
        movzx edx,word ptr [ebx+2]
    L_004408de:
        add edx,ebx
    L_004408e0:
        mov dword ptr [ebp+390h],edx
    L_004408e6:
        or edi,0FFFFFFFFh
    L_004408e9:
        jmp asm_target_0043eea4
    L_004408ee:
        test byte ptr [ebx+6],1
    L_004408f2:
        lea edi,[ebx+8]
    L_004408f5:
        je short L_00440907
    L_004408f7:
        mov eax,dword ptr [edi]
    L_004408f9:
        push eax
    L_004408fa:
        mov esi,ebp
    L_004408fc:
        call asm_FUN_0043eac0_0043eac0
    L_00440901:
        fstp dword ptr [esp+6Ch]
    L_00440905:
        jmp short L_0044090d
    L_00440907:
        mov ecx,dword ptr [edi]
    L_00440909:
        mov dword ptr [esp+6Ch],ecx
    L_0044090d:
        xor edx,edx
    L_0044090f:
        mov dx,word ptr [ebx+6]
    L_00440913:
        xor ecx,ecx
    L_00440915:
        mov esi,ebp
    L_00440917:
        push edx
    L_00440918:
        call asm_AnimationObject_ResolveFloatVariable_0043ed00
    L_0044091d:
        mov esi,eax
    L_0044091f:
        mov eax,dword ptr [esp+6Ch]
    L_00440923:
        push 0
    L_00440925:
        push eax
    L_00440926:
        call asm_Angle_NormalizeSum_0044bc10
    L_0044092b:
        fstp dword ptr [esi]
    L_0044092d:
        movzx edx,word ptr [ebx+2]
    L_00440931:
        add edx,ebx
    L_00440933:
        mov dword ptr [ebp+390h],edx
    L_00440939:
        or edi,0FFFFFFFFh
    L_0044093c:
        jmp asm_target_0043eea4
    L_00440941:
        movzx ecx,byte ptr [ebx+8]
    L_00440945:
        mov esi,dword ptr [ebp+35Ch]
    L_0044094b:
        shl ecx,1Ch
    L_0044094e:
        xor ecx,esi
    L_00440950:
        and ecx,10000000h
    L_00440956:
        mov eax,esi
    L_00440958:
        xor eax,ecx
    L_0044095a:
        mov dword ptr [ebp+35Ch],eax
    L_00440960:
        movzx edx,word ptr [ebx+2]
    L_00440964:
        add edx,ebx
    L_00440966:
        mov dword ptr [ebp+390h],edx
    L_0044096c:
        or edi,0FFFFFFFFh
    L_0044096f:
        jmp asm_target_0043eea4
    L_00440974:
        movzx edx,byte ptr [ebx+8]
    L_00440978:
        mov dword ptr [ebp+20h],edx
    L_0044097b:
        movzx edx,word ptr [ebx+2]
    L_0044097f:
        add edx,ebx
    L_00440981:
        mov dword ptr [ebp+390h],edx
    L_00440987:
        or edi,0FFFFFFFFh
    L_0044098a:
        jmp asm_target_0043eea4
    L_0044098f:
        movzx eax,byte ptr [ebx+8]
    L_00440993:
        mov esi,dword ptr [ebp+35Ch]
    L_00440999:
        shl eax,0Fh
    L_0044099c:
        xor eax,esi
    L_0044099e:
        and eax,8000h
    L_004409a3:
        mov ecx,esi
    L_004409a5:
        xor ecx,eax
    L_004409a7:
        mov dword ptr [ebp+35Ch],ecx
    L_004409ad:
        movzx edx,word ptr [ebx+2]
    L_004409b1:
        add edx,ebx
    L_004409b3:
        mov dword ptr [ebp+390h],edx
    L_004409b9:
        or edi,0FFFFFFFFh
    L_004409bc:
        jmp asm_target_0043eea4
    L_004409c1:
        movzx ecx,byte ptr [ebx+8]
    L_004409c5:
        mov esi,dword ptr [ebp+35Ch]
    L_004409cb:
        shl ecx,1Bh
    L_004409ce:
        xor ecx,esi
    L_004409d0:
        and ecx,8000000h
    L_004409d6:
        mov eax,esi
    L_004409d8:
        xor eax,ecx
    L_004409da:
        mov dword ptr [ebp+35Ch],eax
    L_004409e0:
        movzx edx,word ptr [ebx+2]
    L_004409e4:
        add edx,ebx
    L_004409e6:
        mov dword ptr [ebp+390h],edx
    L_004409ec:
        or edi,0FFFFFFFFh
    L_004409ef:
        jmp asm_target_0043eea4
    L_004409f4:
        movzx edx,byte ptr [ebx+8]
    L_004409f8:
        mov esi,dword ptr [ebp+35Ch]
    L_004409fe:
        shl edx,1Eh
    L_00440a01:
        xor edx,esi
    L_00440a03:
        and edx,40000000h
    L_00440a09:
        mov eax,esi
    L_00440a0b:
        xor eax,edx
    L_00440a0d:
        mov dword ptr [ebp+35Ch],eax
    L_00440a13:
        movzx edx,word ptr [ebx+2]
    L_00440a17:
        add edx,ebx
    L_00440a19:
        mov dword ptr [ebp+390h],edx
    L_00440a1f:
        or edi,0FFFFFFFFh
    L_00440a22:
        jmp asm_target_0043eea4
    L_00440a27:
        test byte ptr [ebx+6],1
    L_00440a2b:
        je short L_00440a3b
    L_00440a2d:
        mov eax,dword ptr [ebx+8]
    L_00440a30:
        mov ecx,ebp
    L_00440a32:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440a37:
        mov esi,eax
    L_00440a39:
        jmp short L_00440a3e
    L_00440a3b:
        mov esi,dword ptr [ebx+8]
    L_00440a3e:
        test byte ptr [ebx+6],2
    L_00440a42:
        mov eax,dword ptr [ebx+0Ch]
    L_00440a45:
        je short L_00440a4e
    L_00440a47:
        mov ecx,ebp
    L_00440a49:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440a4e:
        cmp esi,eax
    L_00440a50:
        je asm_target_00440dda
    L_00440a56:
        movzx edx,word ptr [ebx+2]
    L_00440a5a:
        add edx,ebx
    L_00440a5c:
        mov dword ptr [ebp+390h],edx
    L_00440a62:
        or edi,0FFFFFFFFh
    L_00440a65:
        jmp asm_target_0043eea4
    L_00440a6a:
        test byte ptr [ebx+6],1
    L_00440a6e:
        je short L_00440a81
    L_00440a70:
        mov eax,dword ptr [ebx+8]
    L_00440a73:
        push eax
    L_00440a74:
        mov esi,ebp
    L_00440a76:
        call asm_FUN_0043eac0_0043eac0
    L_00440a7b:
        fstp dword ptr [esp+74h]
    L_00440a7f:
        jmp short L_00440a88
    L_00440a81:
        mov ecx,dword ptr [ebx+8]
    L_00440a84:
        mov dword ptr [esp+74h],ecx
    L_00440a88:
        test byte ptr [ebx+6],2
    L_00440a8c:
        je short L_00440a9b
    L_00440a8e:
        mov edx,dword ptr [ebx+0Ch]
    L_00440a91:
        push edx
    L_00440a92:
        mov esi,ebp
    L_00440a94:
        call asm_FUN_0043eac0_0043eac0
    L_00440a99:
        jmp short L_00440a9e
    L_00440a9b:
        fld dword ptr [ebx+0Ch]
    L_00440a9e:
        fld dword ptr [esp+74h]
    L_00440aa2:
        fucompp
    L_00440aa4:
        fnstsw ax
    L_00440aa6:
        test ah,44h
    L_00440aa9:
        jnp asm_target_00440dda
    L_00440aaf:
        movzx edx,word ptr [ebx+2]
    L_00440ab3:
        add edx,ebx
    L_00440ab5:
        mov dword ptr [ebp+390h],edx
    L_00440abb:
        or edi,0FFFFFFFFh
    L_00440abe:
        jmp asm_target_0043eea4
    L_00440ac3:
        test byte ptr [ebx+6],1
    L_00440ac7:
        je short L_00440ad7
    L_00440ac9:
        mov eax,dword ptr [ebx+8]
    L_00440acc:
        mov ecx,ebp
    L_00440ace:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440ad3:
        mov esi,eax
    L_00440ad5:
        jmp short L_00440ada
    L_00440ad7:
        mov esi,dword ptr [ebx+8]
    L_00440ada:
        test byte ptr [ebx+6],2
    L_00440ade:
        mov eax,dword ptr [ebx+0Ch]
    L_00440ae1:
        je short L_00440aea
    L_00440ae3:
        mov ecx,ebp
    L_00440ae5:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440aea:
        cmp esi,eax
    L_00440aec:
        jne asm_target_00440dda
    L_00440af2:
        movzx edx,word ptr [ebx+2]
    L_00440af6:
        add edx,ebx
    L_00440af8:
        mov dword ptr [ebp+390h],edx
    L_00440afe:
        or edi,0FFFFFFFFh
    L_00440b01:
        jmp asm_target_0043eea4
    L_00440b06:
        test byte ptr [ebx+6],1
    L_00440b0a:
        je short L_00440b1d
    L_00440b0c:
        mov eax,dword ptr [ebx+8]
    L_00440b0f:
        push eax
    L_00440b10:
        mov esi,ebp
    L_00440b12:
        call asm_FUN_0043eac0_0043eac0
    L_00440b17:
        fstp dword ptr [esp+7Ch]
    L_00440b1b:
        jmp short L_00440b24
    L_00440b1d:
        mov ecx,dword ptr [ebx+8]
    L_00440b20:
        mov dword ptr [esp+7Ch],ecx
    L_00440b24:
        test byte ptr [ebx+6],2
    L_00440b28:
        je short L_00440b37
    L_00440b2a:
        mov edx,dword ptr [ebx+0Ch]
    L_00440b2d:
        push edx
    L_00440b2e:
        mov esi,ebp
    L_00440b30:
        call asm_FUN_0043eac0_0043eac0
    L_00440b35:
        jmp short L_00440b3a
    L_00440b37:
        fld dword ptr [ebx+0Ch]
    L_00440b3a:
        fld dword ptr [esp+7Ch]
    L_00440b3e:
        fucompp
    L_00440b40:
        fnstsw ax
    L_00440b42:
        test ah,44h
    L_00440b45:
        jp asm_target_00440dda
    L_00440b4b:
        movzx edx,word ptr [ebx+2]
    L_00440b4f:
        add edx,ebx
    L_00440b51:
        mov dword ptr [ebp+390h],edx
    L_00440b57:
        or edi,0FFFFFFFFh
    L_00440b5a:
        jmp asm_target_0043eea4
    L_00440b5f:
        test byte ptr [ebx+6],1
    L_00440b63:
        je short L_00440b73
    L_00440b65:
        mov eax,dword ptr [ebx+8]
    L_00440b68:
        mov ecx,ebp
    L_00440b6a:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440b6f:
        mov esi,eax
    L_00440b71:
        jmp short L_00440b76
    L_00440b73:
        mov esi,dword ptr [ebx+8]
    L_00440b76:
        test byte ptr [ebx+6],2
    L_00440b7a:
        mov eax,dword ptr [ebx+0Ch]
    L_00440b7d:
        je short L_00440b86
    L_00440b7f:
        mov ecx,ebp
    L_00440b81:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440b86:
        cmp esi,eax
    L_00440b88:
        jl asm_target_00440dda
    L_00440b8e:
        movzx edx,word ptr [ebx+2]
    L_00440b92:
        add edx,ebx
    L_00440b94:
        mov dword ptr [ebp+390h],edx
    L_00440b9a:
        or edi,0FFFFFFFFh
    L_00440b9d:
        jmp asm_target_0043eea4
    L_00440ba2:
        test byte ptr [ebx+6],1
    L_00440ba6:
        je short L_00440bbc
    L_00440ba8:
        mov eax,dword ptr [ebx+8]
    L_00440bab:
        push eax
    L_00440bac:
        mov esi,ebp
    L_00440bae:
        call asm_FUN_0043eac0_0043eac0
    L_00440bb3:
        fstp dword ptr [esp+84h]
    L_00440bba:
        jmp short L_00440bc6
    L_00440bbc:
        mov ecx,dword ptr [ebx+8]
    L_00440bbf:
        mov dword ptr [esp+84h],ecx
    L_00440bc6:
        test byte ptr [ebx+6],2
    L_00440bca:
        je short L_00440bd9
    L_00440bcc:
        mov edx,dword ptr [ebx+0Ch]
    L_00440bcf:
        push edx
    L_00440bd0:
        mov esi,ebp
    L_00440bd2:
        call asm_FUN_0043eac0_0043eac0
    L_00440bd7:
        jmp short L_00440bdc
    L_00440bd9:
        fld dword ptr [ebx+0Ch]
    L_00440bdc:
        fld dword ptr [esp+84h]
    L_00440be3:
        fcomp
    L_00440be5:
        fnstsw ax
    L_00440be7:
        fstp st(0)
    L_00440be9:
        test ah,5
    L_00440bec:
        jnp asm_target_00440dda
    L_00440bf2:
        movzx edx,word ptr [ebx+2]
    L_00440bf6:
        add edx,ebx
    L_00440bf8:
        mov dword ptr [ebp+390h],edx
    L_00440bfe:
        or edi,0FFFFFFFFh
    L_00440c01:
        jmp asm_target_0043eea4
    L_00440c06:
        test byte ptr [ebx+6],1
    L_00440c0a:
        je short L_00440c1a
    L_00440c0c:
        mov eax,dword ptr [ebx+8]
    L_00440c0f:
        mov ecx,ebp
    L_00440c11:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440c16:
        mov esi,eax
    L_00440c18:
        jmp short L_00440c1d
    L_00440c1a:
        mov esi,dword ptr [ebx+8]
    L_00440c1d:
        test byte ptr [ebx+6],2
    L_00440c21:
        mov eax,dword ptr [ebx+0Ch]
    L_00440c24:
        je short L_00440c2d
    L_00440c26:
        mov ecx,ebp
    L_00440c28:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440c2d:
        cmp esi,eax
    L_00440c2f:
        jle asm_target_00440dda
    L_00440c35:
        movzx edx,word ptr [ebx+2]
    L_00440c39:
        add edx,ebx
    L_00440c3b:
        mov dword ptr [ebp+390h],edx
    L_00440c41:
        or edi,0FFFFFFFFh
    L_00440c44:
        jmp asm_target_0043eea4
    L_00440c49:
        test byte ptr [ebx+6],1
    L_00440c4d:
        je short L_00440c63
    L_00440c4f:
        mov eax,dword ptr [ebx+8]
    L_00440c52:
        push eax
    L_00440c53:
        mov esi,ebp
    L_00440c55:
        call asm_FUN_0043eac0_0043eac0
    L_00440c5a:
        fstp dword ptr [esp+8Ch]
    L_00440c61:
        jmp short L_00440c6d
    L_00440c63:
        mov ecx,dword ptr [ebx+8]
    L_00440c66:
        mov dword ptr [esp+8Ch],ecx
    L_00440c6d:
        test byte ptr [ebx+6],2
    L_00440c71:
        je short L_00440c80
    L_00440c73:
        mov edx,dword ptr [ebx+0Ch]
    L_00440c76:
        push edx
    L_00440c77:
        mov esi,ebp
    L_00440c79:
        call asm_FUN_0043eac0_0043eac0
    L_00440c7e:
        jmp short L_00440c83
    L_00440c80:
        fld dword ptr [ebx+0Ch]
    L_00440c83:
        fld dword ptr [esp+8Ch]
    L_00440c8a:
        fcomp
    L_00440c8c:
        fnstsw ax
    L_00440c8e:
        fstp st(0)
    L_00440c90:
        test ah,41h
    L_00440c93:
        jnp asm_target_00440dda
    L_00440c99:
        movzx edx,word ptr [ebx+2]
    L_00440c9d:
        add edx,ebx
    L_00440c9f:
        mov dword ptr [ebp+390h],edx
    L_00440ca5:
        or edi,0FFFFFFFFh
    L_00440ca8:
        jmp asm_target_0043eea4
    L_00440cad:
        test byte ptr [ebx+6],1
    L_00440cb1:
        je short L_00440cc1
    L_00440cb3:
        mov eax,dword ptr [ebx+8]
    L_00440cb6:
        mov ecx,ebp
    L_00440cb8:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440cbd:
        mov esi,eax
    L_00440cbf:
        jmp short L_00440cc4
    L_00440cc1:
        mov esi,dword ptr [ebx+8]
    L_00440cc4:
        test byte ptr [ebx+6],2
    L_00440cc8:
        mov eax,dword ptr [ebx+0Ch]
    L_00440ccb:
        je short L_00440cd4
    L_00440ccd:
        mov ecx,ebp
    L_00440ccf:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440cd4:
        cmp esi,eax
    L_00440cd6:
        jg asm_target_00440dda
    L_00440cdc:
        movzx edx,word ptr [ebx+2]
    L_00440ce0:
        add edx,ebx
    L_00440ce2:
        mov dword ptr [ebp+390h],edx
    L_00440ce8:
        or edi,0FFFFFFFFh
    L_00440ceb:
        jmp asm_target_0043eea4
    L_00440cf0:
        test byte ptr [ebx+6],1
    L_00440cf4:
        je short L_00440d0a
    L_00440cf6:
        mov eax,dword ptr [ebx+8]
    L_00440cf9:
        push eax
    L_00440cfa:
        mov esi,ebp
    L_00440cfc:
        call asm_FUN_0043eac0_0043eac0
    L_00440d01:
        fstp dword ptr [esp+94h]
    L_00440d08:
        jmp short L_00440d14
    L_00440d0a:
        mov ecx,dword ptr [ebx+8]
    L_00440d0d:
        mov dword ptr [esp+94h],ecx
    L_00440d14:
        test byte ptr [ebx+6],2
    L_00440d18:
        je short L_00440d27
    L_00440d1a:
        mov edx,dword ptr [ebx+0Ch]
    L_00440d1d:
        push edx
    L_00440d1e:
        mov esi,ebp
    L_00440d20:
        call asm_FUN_0043eac0_0043eac0
    L_00440d25:
        jmp short L_00440d2a
    L_00440d27:
        fld dword ptr [ebx+0Ch]
    L_00440d2a:
        fld dword ptr [esp+94h]
    L_00440d31:
        fcomp
    L_00440d33:
        fnstsw ax
    L_00440d35:
        fstp st(0)
    L_00440d37:
        test ah,41h
    L_00440d3a:
        je asm_target_00440dda
    L_00440d40:
        movzx edx,word ptr [ebx+2]
    L_00440d44:
        add edx,ebx
    L_00440d46:
        mov dword ptr [ebp+390h],edx
    L_00440d4c:
        or edi,0FFFFFFFFh
    L_00440d4f:
        jmp asm_target_0043eea4
    L_00440d54:
        test byte ptr [ebx+6],1
    L_00440d58:
        je short L_00440d68
    L_00440d5a:
        mov eax,dword ptr [ebx+8]
    L_00440d5d:
        mov ecx,ebp
    L_00440d5f:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440d64:
        mov esi,eax
    L_00440d66:
        jmp short L_00440d6b
    L_00440d68:
        mov esi,dword ptr [ebx+8]
    L_00440d6b:
        test byte ptr [ebx+6],2
    L_00440d6f:
        mov eax,dword ptr [ebx+0Ch]
    L_00440d72:
        je short L_00440d7b
    L_00440d74:
        mov ecx,ebp
    L_00440d76:
        call asm_AnimationObject_ReadIntegerVariable_0043ec70
    L_00440d7b:
        cmp esi,eax
    L_00440d7d:
        jge short L_00440dda
    L_00440d7f:
        movzx edx,word ptr [ebx+2]
    L_00440d83:
        add edx,ebx
    L_00440d85:
        mov dword ptr [ebp+390h],edx
    L_00440d8b:
        or edi,0FFFFFFFFh
    L_00440d8e:
        jmp asm_target_0043eea4
    L_00440d93:
        test byte ptr [ebx+6],1
    L_00440d97:
        je short L_00440daa
    L_00440d99:
        mov eax,dword ptr [ebx+8]
    L_00440d9c:
        push eax
    L_00440d9d:
        mov esi,ebp
    L_00440d9f:
        call asm_FUN_0043eac0_0043eac0
    L_00440da4:
        fstp dword ptr [esp+2Ch]
    L_00440da8:
        jmp short L_00440db1
    L_00440daa:
        mov ecx,dword ptr [ebx+8]
    L_00440dad:
        mov dword ptr [esp+2Ch],ecx
    L_00440db1:
        test byte ptr [ebx+6],2
    L_00440db5:
        je short L_00440dc4
    L_00440db7:
        mov edx,dword ptr [ebx+0Ch]
    L_00440dba:
        push edx
    L_00440dbb:
        mov esi,ebp
    L_00440dbd:
        call asm_FUN_0043eac0_0043eac0
    L_00440dc2:
        jmp short L_00440dc7
    L_00440dc4:
        fld dword ptr [ebx+0Ch]
    L_00440dc7:
        fld dword ptr [esp+2Ch]
    L_00440dcb:
        fcomp
    L_00440dcd:
        fnstsw ax
    L_00440dcf:
        fstp st(0)
    L_00440dd1:
        test ah,1
    L_00440dd4:
        jne asm_target_0043f532
    L_00440dda:
        mov eax,dword ptr [ebx+14h]
    L_00440ddd:
        push eax
    L_00440dde:
        lea eax,[ebp+5Ch]
    L_00440de1:
        call asm_Player_SetSchedulerValue_00405410
    L_00440de6:
        mov eax,dword ptr [ebx+10h]
    L_00440de9:
        mov ecx,dword ptr [ebp+38Ch]
    L_00440def:
        add ecx,eax
    L_00440df1:
        mov dword ptr [ebp+390h],ecx
    L_00440df7:
        jmp asm_target_0043eea4
    L_00440dfc:
        and dword ptr [ebp+35Ch],0FFFFFFFEh
    L_00440e03:
        mov eax,dword ptr [esp+0A4h]
    L_00440e0a:
        pop edi
    L_00440e0b:
        pop esi
    L_00440e0c:
        mov dword ptr [ebp+390h],0
    L_00440e16:
        pop ebx
    L_00440e17:
        mov dword ptr [g_game_speed],eax
    L_00440e1c:
        mov eax,1
    L_00440e21:
        pop ebp
    L_00440e22:
        add esp,0FCh
    L_00440e28:
        ret 4
    L_00440e2b:
        or dword ptr [ebp+35Ch],1000h
    L_00440e35:
        lea esi,[ebp+5Ch]
    L_00440e38:
        push 0BF800000h
    L_00440e3d:
        call asm_FrameTimer_Advance_0044bf40
    L_00440e42:
        fld dword ptr [data_00470b04]
    L_00440e48:
        fld dword ptr [ebp+30h]
    L_00440e4b:
        fucompp
    L_00440e4d:
        fnstsw ax
    L_00440e4f:
        test ah,44h
    L_00440e52:
        jnp short L_00440e82
    L_00440e54:
        fld dword ptr [g_game_speed]
    L_00440e5a:
        push ecx
    L_00440e5b:
        fmul dword ptr [ebp+30h]
    L_00440e5e:
        mov ecx,dword ptr [ebp+24h]
    L_00440e61:
        fstp dword ptr [esp]
    L_00440e64:
        push ecx
    L_00440e65:
        call asm_Angle_NormalizeSum_0044bc10
    L_00440e6a:
        fstp dword ptr [ebp+24h]
    L_00440e6d:
        mov eax,dword ptr [ebp+35Ch]
    L_00440e73:
        mov esi,4
    L_00440e78:
        or eax,esi
    L_00440e7a:
        mov dword ptr [ebp+35Ch],eax
    L_00440e80:
        jmp short L_00440e87
    L_00440e82:
        mov esi,4
    L_00440e87:
        fld dword ptr [data_00470b04]
    L_00440e8d:
        fld dword ptr [ebp+34h]
    L_00440e90:
        fucompp
    L_00440e92:
        fnstsw ax
    L_00440e94:
        test ah,44h
    L_00440e97:
        jnp short L_00440eb8
    L_00440e99:
        fld dword ptr [g_game_speed]
    L_00440e9f:
        mov edx,dword ptr [ebp+28h]
    L_00440ea2:
        fmul dword ptr [ebp+34h]
    L_00440ea5:
        push ecx
    L_00440ea6:
        fstp dword ptr [esp]
    L_00440ea9:
        push edx
    L_00440eaa:
        call asm_Angle_NormalizeSum_0044bc10
    L_00440eaf:
        fstp dword ptr [ebp+28h]
    L_00440eb2:
        or dword ptr [ebp+35Ch],esi
    L_00440eb8:
        fld dword ptr [data_00470b04]
    L_00440ebe:
        fld dword ptr [ebp+38h]
    L_00440ec1:
        fucompp
    L_00440ec3:
        fnstsw ax
    L_00440ec5:
        test ah,44h
    L_00440ec8:
        jnp short L_00440ee9
    L_00440eca:
        fld dword ptr [g_game_speed]
    L_00440ed0:
        mov eax,dword ptr [ebp+2Ch]
    L_00440ed3:
        fmul dword ptr [ebp+38h]
    L_00440ed6:
        push ecx
    L_00440ed7:
        fstp dword ptr [esp]
    L_00440eda:
        push eax
    L_00440edb:
        call asm_Angle_NormalizeSum_0044bc10
    L_00440ee0:
        fstp dword ptr [ebp+2Ch]
    L_00440ee3:
        or dword ptr [ebp+35Ch],esi
    L_00440ee9:
        fld dword ptr [data_00470b04]
    L_00440eef:
        fld dword ptr [ebp+48h]
    L_00440ef2:
        fucompp
    L_00440ef4:
        fnstsw ax
    L_00440ef6:
        test ah,44h
    L_00440ef9:
        jnp short L_00440f19
    L_00440efb:
        fld dword ptr [g_game_speed]
    L_00440f01:
        mov eax,dword ptr [ebp+35Ch]
    L_00440f07:
        fmul dword ptr [ebp+48h]
    L_00440f0a:
        or eax,8
    L_00440f0d:
        mov dword ptr [ebp+35Ch],eax
    L_00440f13:
        fadd dword ptr [ebp+40h]
    L_00440f16:
        fstp dword ptr [ebp+40h]
    L_00440f19:
        fld dword ptr [data_00470b04]
    L_00440f1f:
        fld dword ptr [ebp+44h]
    L_00440f22:
        fucompp
    L_00440f24:
        fnstsw ax
    L_00440f26:
        test ah,44h
    L_00440f29:
        jnp short L_00440f49
    L_00440f2b:
        fld dword ptr [g_game_speed]
    L_00440f31:
        mov eax,dword ptr [ebp+35Ch]
    L_00440f37:
        fmul dword ptr [ebp+44h]
    L_00440f3a:
        or eax,0Ch
    L_00440f3d:
        mov dword ptr [ebp+35Ch],eax
    L_00440f43:
        fadd dword ptr [ebp+3Ch]
    L_00440f46:
        fstp dword ptr [ebp+3Ch]
    L_00440f49:
        fld dword ptr [g_game_speed]
    L_00440f4f:
        fmul dword ptr [ebp+234h]
    L_00440f55:
        fadd dword ptr [ebp+54h]
    L_00440f58:
        fcom dword ptr [data_00470afc]
    L_00440f5e:
        fst dword ptr [ebp+54h]
    L_00440f61:
        fnstsw ax
    L_00440f63:
        test ah,1
    L_00440f66:
        jne short L_00440f73
    L_00440f68:
        fsub dword ptr [data_00470afc]
    L_00440f6e:
        fstp dword ptr [ebp+54h]
    L_00440f71:
        jmp short L_00440f8d
    L_00440f73:
        fcom dword ptr [data_00470b04]
    L_00440f79:
        fnstsw ax
    L_00440f7b:
        test ah,5
    L_00440f7e:
        jp short L_00440f8b
    L_00440f80:
        fadd dword ptr [data_00470afc]
    L_00440f86:
        fstp dword ptr [ebp+54h]
    L_00440f89:
        jmp short L_00440f8d
    L_00440f8b:
        fstp st(0)
    L_00440f8d:
        fld dword ptr [g_game_speed]
    L_00440f93:
        fmul dword ptr [ebp+238h]
    L_00440f99:
        fadd dword ptr [ebp+58h]
    L_00440f9c:
        fcom dword ptr [data_00470afc]
    L_00440fa2:
        fst dword ptr [ebp+58h]
    L_00440fa5:
        fnstsw ax
    L_00440fa7:
        test ah,1
    L_00440faa:
        jne short L_00440fb7
    L_00440fac:
        fsub dword ptr [data_00470afc]
    L_00440fb2:
        fstp dword ptr [ebp+58h]
    L_00440fb5:
        jmp short L_00440fd1
    L_00440fb7:
        fcom dword ptr [data_00470b04]
    L_00440fbd:
        fnstsw ax
    L_00440fbf:
        test ah,5
    L_00440fc2:
        jp short L_00440fcf
    L_00440fc4:
        fadd dword ptr [data_00470afc]
    L_00440fca:
        fstp dword ptr [ebp+58h]
    L_00440fcd:
        jmp short L_00440fd1
    L_00440fcf:
        fstp st(0)
    L_00440fd1:
        mov eax,dword ptr [ebp+35Ch]
    L_00440fd7:
        test ah,20h
    L_00440fda:
        je short L_00441012
    L_00440fdc:
        fld dword ptr [data_00491e6c]
    L_00440fe2:
        fadd dword ptr [ebp+340h]
    L_00440fe8:
        fstp dword ptr [ebp+340h]
    L_00440fee:
        fld dword ptr [data_00491e70]
    L_00440ff4:
        fadd dword ptr [ebp+344h]
    L_00440ffa:
        fstp dword ptr [ebp+344h]
    L_00441000:
        fld dword ptr [data_00491e74]
    L_00441006:
        fadd dword ptr [ebp+348h]
    L_0044100c:
        fstp dword ptr [ebp+348h]
    L_00441012:
        mov eax,dword ptr [ebp+0B4h]
    L_00441018:
        test eax,eax
    L_0044101a:
        je short L_00441056
    L_0044101c:
        mov eax,dword ptr [ebp+35Ch]
    L_00441022:
        test ah,1
    L_00441025:
        lea edi,[esp+18h]
    L_00441029:
        lea eax,[ebp+70h]
    L_0044102c:
        jne short L_0044103b
    L_0044102e:
        call asm_FUN_00404610_00404610
    L_00441033:
        lea ecx,[ebp+334h]
    L_00441039:
        jmp short L_00441046
    L_0044103b:
        call asm_FUN_00404610_00404610
    L_00441040:
        lea ecx,[ebp+34Ch]
    L_00441046:
        mov edx,dword ptr [eax]
    L_00441048:
        mov dword ptr [ecx],edx
    L_0044104a:
        mov edx,dword ptr [eax+4]
    L_0044104d:
        mov dword ptr [ecx+4],edx
    L_00441050:
        mov eax,dword ptr [eax+8]
    L_00441053:
        mov dword ptr [ecx+8],eax
    L_00441056:
        mov eax,dword ptr [ebp+100h]
    L_0044105c:
        test eax,eax
    L_0044105e:
        je short L_0044108e
    L_00441060:
        lea ecx,[esp+18h]
    L_00441064:
        push ecx
    L_00441065:
        lea eax,[ebp+0BCh]
    L_0044106b:
        call asm_FUN_00441600_00441600
    L_00441070:
        mov dl,byte ptr [esp+20h]
    L_00441074:
        mov al,byte ptr [esp+1Ch]
    L_00441078:
        mov cl,byte ptr [esp+18h]
    L_0044107c:
        mov byte ptr [ebp+2FEh],dl
    L_00441082:
        mov byte ptr [ebp+2FDh],al
    L_00441088:
        mov byte ptr [ebp+2FCh],cl
    L_0044108e:
        mov eax,dword ptr [ebp+12Ch]
    L_00441094:
        test eax,eax
    L_00441096:
        je short L_004410a9
    L_00441098:
        lea esi,[ebp+108h]
    L_0044109e:
        call asm_FUN_00441950_00441950
    L_004410a3:
        mov byte ptr [ebp+2FFh],al
    L_004410a9:
        mov eax,dword ptr [ebp+1B4h]
    L_004410af:
        test eax,eax
    L_004410b1:
        je short L_004410d7
    L_004410b3:
        lea esi,[ebp+180h]
    L_004410b9:
        lea edi,[esp+104h]
    L_004410c0:
        call asm_FUN_00441ad0_00441ad0
    L_004410c5:
        mov edx,dword ptr [eax]
    L_004410c7:
        mov dword ptr [ebp+3Ch],edx
    L_004410ca:
        mov eax,dword ptr [eax+4]
    L_004410cd:
        mov dword ptr [ebp+40h],eax
    L_004410d0:
        or dword ptr [ebp+35Ch],8
    L_004410d7:
        mov eax,dword ptr [ebp+178h]
    L_004410dd:
        test eax,eax
    L_004410df:
        je short L_0044110a
    L_004410e1:
        lea eax,[ebp+134h]
    L_004410e7:
        lea edi,[esp+18h]
    L_004410eb:
        call asm_FUN_00404610_00404610
    L_004410f0:
        mov edx,dword ptr [eax]
    L_004410f2:
        lea ecx,[ebp+24h]
    L_004410f5:
        mov dword ptr [ecx],edx
    L_004410f7:
        mov edx,dword ptr [eax+4]
    L_004410fa:
        mov dword ptr [ecx+4],edx
    L_004410fd:
        mov eax,dword ptr [eax+8]
    L_00441100:
        mov dword ptr [ecx+8],eax
    L_00441103:
        or dword ptr [ebp+35Ch],4
    L_0044110a:
        mov eax,dword ptr [ebp+200h]
    L_00441110:
        test eax,eax
    L_00441112:
        je short L_00441142
    L_00441114:
        lea ecx,[esp+18h]
    L_00441118:
        push ecx
    L_00441119:
        lea eax,[ebp+1BCh]
    L_0044111f:
        call asm_FUN_00441600_00441600
    L_00441124:
        mov dl,byte ptr [esp+20h]
    L_00441128:
        mov al,byte ptr [esp+1Ch]
    L_0044112c:
        mov cl,byte ptr [esp+18h]
    L_00441130:
        mov byte ptr [ebp+302h],dl
    L_00441136:
        mov byte ptr [ebp+301h],al
    L_0044113c:
        mov byte ptr [ebp+300h],cl
    L_00441142:
        mov eax,dword ptr [ebp+22Ch]
    L_00441148:
        test eax,eax
    L_0044114a:
        je short L_0044115d
    L_0044114c:
        lea esi,[ebp+208h]
    L_00441152:
        call asm_FUN_00441950_00441950
    L_00441157:
        mov byte ptr [ebp+303h],al
    L_0044115d:
        mov edx,dword ptr [ebp+35Ch]
    L_00441163:
        and edx,3C00000h
    L_00441169:
        cmp edx,2400000h
    L_0044116f:
        jne asm_target_0044133e
    L_00441175:
        mov eax,dword ptr [ebp+30Ch]
    L_0044117b:
        lea esi,[eax-1]
    L_0044117e:
        test esi,esi
    L_00441180:
        mov dword ptr [esp+28h],esi
    L_00441184:
        fild dword ptr [esp+28h]
    L_00441188:
        fld dword ptr [data_00470b14]
    L_0044118e:
        mov ecx,dword ptr [ebp+2Ch]
    L_00441191:
        mov ebx,dword ptr [ebp+358h]
    L_00441197:
        fdiv st,st(1)
    L_00441199:
        mov dword ptr [esp+2Ch],ecx
    L_0044119d:
        mov dword ptr [esp+10h],0
    L_004411a5:
        fstp dword ptr [esp+28h]
    L_004411a9:
        fild dword ptr [ebp+310h]
    L_004411af:
        fdiv st,st(1)
    L_004411b1:
        fstp dword ptr [esp+34h]
    L_004411b5:
        fstp st(0)
    L_004411b7:
        jle asm_target_00441308
    L_004411bd:
        mov edi,dword ptr [esp+28h]
    L_004411c1:
        TH10_REL8(0xeb, 0x004411c1, VA_asm_FUN_0043ee30_part_004411d0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_004411d0:
        mov dword ptr [ebx+0Ch],3F800000h
    L_004411d7:
        mov edx,dword ptr [ebp+2FCh]
    L_004411dd:
        mov dword ptr [ebx+10h],edx
    L_004411e0:
        mov eax,dword ptr [ebp+394h]
    L_004411e6:
        fld dword ptr [eax+20h]
    L_004411e9:
        mov edx,dword ptr [esp+2Ch]
    L_004411ed:
        fadd dword ptr [ebp+54h]
    L_004411f0:
        push ecx
    L_004411f1:
        mov ecx,ebx
    L_004411f3:
        fstp dword ptr [ebx+14h]
    L_004411f6:
        fld dword ptr [esp+14h]
    L_004411fa:
        fadd dword ptr [ebp+58h]
    L_004411fd:
        fstp dword ptr [ebx+18h]
    L_00441200:
        fld dword ptr [ebp+3Ch]
    L_00441203:
        fmul dword ptr [data_00470b0c]
    L_00441209:
        fadd dword ptr [ebp+40h]
    L_0044120c:
        fstp dword ptr [esp]
    L_0044120f:
        push edx
    L_00441210:
        call asm_Vector2_SetAnimationPolar_00441ef0
    L_00441215:
        mov dword ptr [ebx+8],0
    L_0044121c:
        fld dword ptr [ebp+340h]
    L_00441222:
        fadd dword ptr [ebp+334h]
    L_00441228:
        add ebx,1Ch
    L_0044122b:
        fld dword ptr [ebp+344h]
    L_00441231:
        fadd dword ptr [ebp+338h]
    L_00441237:
        fstp dword ptr [esp+1Ch]
    L_0044123b:
        fld dword ptr [ebp+348h]
    L_00441241:
        fadd dword ptr [ebp+33Ch]
    L_00441247:
        fxch
    L_00441249:
        fadd dword ptr [ebx-1Ch]
    L_0044124c:
        fstp dword ptr [ebx-1Ch]
    L_0044124f:
        fld dword ptr [esp+1Ch]
    L_00441253:
        fadd dword ptr [ebx-18h]
    L_00441256:
        fstp dword ptr [ebx-18h]
    L_00441259:
        fstp dword ptr [ebx-14h]
    L_0044125c:
        mov dword ptr [ebx+0Ch],3F800000h
    L_00441263:
        mov ecx,dword ptr [ebp+2FCh]
    L_00441269:
        mov dword ptr [ebx+10h],ecx
    L_0044126c:
        mov eax,dword ptr [ebp+394h]
    L_00441272:
        fld dword ptr [eax+28h]
    L_00441275:
        push ecx
    L_00441276:
        fadd dword ptr [ebp+54h]
    L_00441279:
        mov ecx,ebx
    L_0044127b:
        fstp dword ptr [ebx+14h]
    L_0044127e:
        fld dword ptr [esp+14h]
    L_00441282:
        fadd dword ptr [ebp+58h]
    L_00441285:
        fstp dword ptr [ebx+18h]
    L_00441288:
        fld dword ptr [ebp+3Ch]
    L_0044128b:
        fmul dword ptr [data_00470b0c]
    L_00441291:
        fsubr dword ptr [ebp+40h]
    L_00441294:
        fstp dword ptr [esp]
    L_00441297:
        push edx
    L_00441298:
        call asm_Vector2_SetAnimationPolar_00441ef0
    L_0044129d:
        mov dword ptr [ebx+8],0
    L_004412a4:
        fld dword ptr [ebp+340h]
    L_004412aa:
        fadd dword ptr [ebp+334h]
    L_004412b0:
        push edi
    L_004412b1:
        fld dword ptr [ebp+344h]
    L_004412b7:
        push edx
    L_004412b8:
        fadd dword ptr [ebp+338h]
    L_004412be:
        add ebx,1Ch
    L_004412c1:
        fstp dword ptr [esp+0E4h]
    L_004412c8:
        fld dword ptr [ebp+33Ch]
    L_004412ce:
        fadd dword ptr [ebp+348h]
    L_004412d4:
        fxch
    L_004412d6:
        fadd dword ptr [ebx-1Ch]
    L_004412d9:
        fstp dword ptr [ebx-1Ch]
    L_004412dc:
        fld dword ptr [esp+0E4h]
    L_004412e3:
        fadd dword ptr [ebx-18h]
    L_004412e6:
        fstp dword ptr [ebx-18h]
    L_004412e9:
        fstp dword ptr [ebx-14h]
    L_004412ec:
        fld dword ptr [esp+3Ch]
    L_004412f0:
        fadd dword ptr [esp+18h]
    L_004412f4:
        fstp dword ptr [esp+18h]
    L_004412f8:
        call asm_Angle_NormalizeSum_0044bc10
    L_004412fd:
        dec esi
    L_004412fe:
        fstp dword ptr [esp+2Ch]
    L_00441302:
        jne asm_FUN_0043ee30_part_004411d0
    L_00441308:
        mov esi,dword ptr [ebp+358h]
    L_0044130e:
        fld dword ptr [esp+10h]
    L_00441312:
        mov ecx,7
    L_00441317:
        mov edi,ebx
    L_00441319:
        rep movsd
    L_0044131b:
        fadd dword ptr [ebp+58h]
    L_0044131e:
        fstp dword ptr [ebx+18h]
    L_00441321:
        fld dword ptr [esp+10h]
    L_00441325:
        mov esi,dword ptr [ebp+358h]
    L_0044132b:
        add esi,1Ch
    L_0044132e:
        lea edi,[ebx+1Ch]
    L_00441331:
        mov ecx,7
    L_00441336:
        rep movsd
    L_00441338:
        fadd dword ptr [ebp+58h]
    L_0044133b:
        fstp dword ptr [ebx+34h]
    L_0044133e:
        mov edx,dword ptr [ebp+60h]
    L_00441341:
        mov ecx,dword ptr [ebp+68h]
    L_00441344:
        mov dword ptr [ebp+5Ch],edx
    L_00441347:
        fld dword ptr [ecx]
    L_00441349:
        fcomp dword ptr [data_00470b68]
    L_0044134f:
        fnstsw ax
    L_00441351:
        test ah,41h
    L_00441354:
        jne short L_00441377
    L_00441356:
        fld dword ptr [ecx]
    L_00441358:
        fcomp dword ptr [data_00470b64]
    L_0044135e:
        fnstsw ax
    L_00441360:
        test ah,5
    L_00441363:
        jp short L_00441377
    L_00441365:
        fld dword ptr [ebp+64h]
    L_00441368:
        inc edx
    L_00441369:
        fadd dword ptr [data_00470afc]
    L_0044136f:
        mov dword ptr [ebp+60h],edx
    L_00441372:
        fstp dword ptr [ebp+64h]
    L_00441375:
        jmp short L_00441387
    L_00441377:
        fld dword ptr [ecx]
    L_00441379:
        fadd dword ptr [ebp+64h]
    L_0044137c:
        fst dword ptr [ebp+64h]
    L_0044137f:
        call asm_FUN_00463b2c_00463b2c
    L_00441384:
        mov dword ptr [ebp+60h],eax
    L_00441387:
        mov ecx,dword ptr [esp+0A4h]
    L_0044138e:
        pop edi
    L_0044138f:
        pop esi
    L_00441390:
        pop ebx
    L_00441391:
        mov dword ptr [g_game_speed],ecx
    L_00441397:
        xor eax,eax
    L_00441399:
        pop ebp
    L_0044139a:
        add esp,0FCh
    L_004413a0:
        ret 4
        _emit 0x90
        _emit 0xfc
        _emit 0x0d
        _emit 0x44
        _emit 0x00
        _emit 0x32
        _emit 0xf5
        _emit 0x43
        _emit 0x00
        _emit 0xfc
        _emit 0x0d
        _emit 0x44
        _emit 0x00
        _emit 0x03
        _emit 0x0e
        _emit 0x44
        _emit 0x00
        _emit 0x6b
        _emit 0xf0
        _emit 0x43
        _emit 0x00
        _emit 0x04
        _emit 0xf2
        _emit 0x43
        _emit 0x00
        _emit 0x26
        _emit 0xf2
        _emit 0x43
        _emit 0x00
        _emit 0xa2
        _emit 0xfe
        _emit 0x43
        _emit 0x00
        _emit 0xe2
        _emit 0xfe
        _emit 0x43
        _emit 0x00
        _emit 0x53
        _emit 0x03
        _emit 0x44
        _emit 0x00
        _emit 0x93
        _emit 0x03
        _emit 0x44
        _emit 0x00
        _emit 0xe0
        _emit 0x03
        _emit 0x44
        _emit 0x00
        _emit 0x20
        _emit 0x04
        _emit 0x44
        _emit 0x00
        _emit 0x76
        _emit 0x04
        _emit 0x44
        _emit 0x00
        _emit 0xbb
        _emit 0x04
        _emit 0x44
        _emit 0x00
        _emit 0x11
        _emit 0x05
        _emit 0x44
        _emit 0x00
        _emit 0x58
        _emit 0x05
        _emit 0x44
        _emit 0x00
        _emit 0xae
        _emit 0x05
        _emit 0x44
        _emit 0x00
        _emit 0xf5
        _emit 0x05
        _emit 0x44
        _emit 0x00
        _emit 0x2d
        _emit 0xff
        _emit 0x43
        _emit 0x00
        _emit 0x86
        _emit 0xff
        _emit 0x43
        _emit 0x00
        _emit 0xfc
        _emit 0xff
        _emit 0x43
        _emit 0x00
        _emit 0x55
        _emit 0x00
        _emit 0x44
        _emit 0x00
        _emit 0xcb
        _emit 0x00
        _emit 0x44
        _emit 0x00
        _emit 0x25
        _emit 0x01
        _emit 0x44
        _emit 0x00
        _emit 0x9b
        _emit 0x01
        _emit 0x44
        _emit 0x00
        _emit 0xf9
        _emit 0x01
        _emit 0x44
        _emit 0x00
        _emit 0x6f
        _emit 0x02
        _emit 0x44
        _emit 0x00
        _emit 0xcd
        _emit 0x02
        _emit 0x44
        _emit 0x00
        _emit 0x27
        _emit 0x0a
        _emit 0x44
        _emit 0x00
        _emit 0x6a
        _emit 0x0a
        _emit 0x44
        _emit 0x00
        _emit 0xc3
        _emit 0x0a
        _emit 0x44
        _emit 0x00
        _emit 0x06
        _emit 0x0b
        _emit 0x44
        _emit 0x00
        _emit 0x5f
        _emit 0x0b
        _emit 0x44
        _emit 0x00
        _emit 0xa2
        _emit 0x0b
        _emit 0x44
        _emit 0x00
        _emit 0x06
        _emit 0x0c
        _emit 0x44
        _emit 0x00
        _emit 0x49
        _emit 0x0c
        _emit 0x44
        _emit 0x00
        _emit 0xad
        _emit 0x0c
        _emit 0x44
        _emit 0x00
        _emit 0xf0
        _emit 0x0c
        _emit 0x44
        _emit 0x00
        _emit 0x54
        _emit 0x0d
        _emit 0x44
        _emit 0x00
        _emit 0x93
        _emit 0x0d
        _emit 0x44
        _emit 0x00
        _emit 0x79
        _emit 0x06
        _emit 0x44
        _emit 0x00
        _emit 0xe2
        _emit 0x06
        _emit 0x44
        _emit 0x00
        _emit 0x64
        _emit 0x07
        _emit 0x44
        _emit 0x00
        _emit 0xb1
        _emit 0x07
        _emit 0x44
        _emit 0x00
        _emit 0xfe
        _emit 0x07
        _emit 0x44
        _emit 0x00
        _emit 0x4d
        _emit 0x08
        _emit 0x44
        _emit 0x00
        _emit 0x9f
        _emit 0x08
        _emit 0x44
        _emit 0x00
        _emit 0xee
        _emit 0x08
        _emit 0x44
        _emit 0x00
        _emit 0x87
        _emit 0xf4
        _emit 0x43
        _emit 0x00
        _emit 0xde
        _emit 0xf2
        _emit 0x43
        _emit 0x00
        _emit 0xae
        _emit 0xf0
        _emit 0x43
        _emit 0x00
        _emit 0x04
        _emit 0xf1
        _emit 0x43
        _emit 0x00
        _emit 0x2e
        _emit 0xf1
        _emit 0x43
        _emit 0x00
        _emit 0x4e
        _emit 0xf3
        _emit 0x43
        _emit 0x00
        _emit 0xbe
        _emit 0xf3
        _emit 0x43
        _emit 0x00
        _emit 0x1a
        _emit 0xf4
        _emit 0x43
        _emit 0x00
        _emit 0xb7
        _emit 0xf8
        _emit 0x43
        _emit 0x00
        _emit 0x0f
        _emit 0xfa
        _emit 0x43
        _emit 0x00
        _emit 0xbc
        _emit 0xfa
        _emit 0x43
        _emit 0x00
        _emit 0x0e
        _emit 0xfc
        _emit 0x43
        _emit 0x00
        _emit 0x30
        _emit 0xfd
        _emit 0x43
        _emit 0x00
        _emit 0x76
        _emit 0xf2
        _emit 0x43
        _emit 0x00
        _emit 0xaa
        _emit 0xf2
        _emit 0x43
        _emit 0x00
        _emit 0x1d
        _emit 0xf6
        _emit 0x43
        _emit 0x00
        _emit 0x32
        _emit 0xf5
        _emit 0x43
        _emit 0x00
        _emit 0x4a
        _emit 0xf7
        _emit 0x43
        _emit 0x00
        _emit 0x58
        _emit 0xf4
        _emit 0x43
        _emit 0x00
        _emit 0xc9
        _emit 0xfd
        _emit 0x43
        _emit 0x00
        _emit 0x74
        _emit 0x09
        _emit 0x44
        _emit 0x00
        _emit 0x16
        _emit 0xf6
        _emit 0x43
        _emit 0x00
        _emit 0x95
        _emit 0xf7
        _emit 0x43
        _emit 0x00
        _emit 0xdd
        _emit 0xf7
        _emit 0x43
        _emit 0x00
        _emit 0x1e
        _emit 0xf7
        _emit 0x43
        _emit 0x00
        _emit 0x25
        _emit 0xf8
        _emit 0x43
        _emit 0x00
        _emit 0x57
        _emit 0xf8
        _emit 0x43
        _emit 0x00
        _emit 0xea
        _emit 0xf5
        _emit 0x43
        _emit 0x00
        _emit 0xae
        _emit 0xf1
        _emit 0x43
        _emit 0x00
        _emit 0x84
        _emit 0xf1
        _emit 0x43
        _emit 0x00
        _emit 0x10
        _emit 0xfb
        _emit 0x43
        _emit 0x00
        _emit 0xbd
        _emit 0xfb
        _emit 0x43
        _emit 0x00
        _emit 0x8f
        _emit 0x09
        _emit 0x44
        _emit 0x00
        _emit 0xe8
        _emit 0xf6
        _emit 0x43
        _emit 0x00
        _emit 0xc1
        _emit 0x09
        _emit 0x44
        _emit 0x00
        _emit 0x14
        _emit 0xfe
        _emit 0x43
        _emit 0x00
        _emit 0x56
        _emit 0xfe
        _emit 0x43
        _emit 0x00
        _emit 0x41
        _emit 0x09
        _emit 0x44
        _emit 0x00
        _emit 0xcb
        _emit 0xee
        _emit 0x43
        _emit 0x00
        _emit 0xf4
        _emit 0x09
        _emit 0x44
        _emit 0x00
        _emit 0x06
        _emit 0xef
        _emit 0x43
        _emit 0x00
        _emit 0x89
        _emit 0xf8
        _emit 0x43
        _emit 0x00
        _emit 0x61
        _emit 0xef
        _emit 0x43
        _emit 0x00
        _emit 0x32
        _emit 0xef
        _emit 0x43
        _emit 0x00
        _emit 0xe6
        _emit 0xef
        _emit 0x43
        _emit 0x00
    }
}

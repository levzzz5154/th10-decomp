#include "asm_encoding.hpp"
#include "asm_symbols.hpp"


// BLOCKED (D3401): closest_byte_count=2520/2520; first_diff=none
// (authoritative MSVC 13.10 probe exact for the retained retail body).
// residual_class=large schema2 body with private helper ABI/register scheduling
// (callee inputs include EAX/ECX/EDX and stack temporaries), 0x004489D0/
// 0x00448E30/0x00449470/0x00449950 layout dependencies, and x87 conversion
// order in the 0x00463B2C random-offset paths. variants_tested=live Ghidra
// decompile plus xrefs/callers/callees and dependency paths; Ghidra dataflow
// confirms the parameter and helper propagation, while no PCode is available
// for the private-ABI helper regions. next_lever=co-compile this body with
// the blocked animation-manager helper family in a native-LTCG schema2 context.
//
// 0x00426F70..0x00427019: FUN_00426f70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00426f70_00426f70() {
    __asm {
    L_00426f70:
        sub esp,38h
    L_00426f73:
        mov cx,word ptr [data_00474c48]
    L_00426f7a:
        movsx edx,cx
    L_00426f7d:
        mov eax,66666667h
    L_00426f82:
        imul edx
    L_00426f84:
        sar edx,3
    L_00426f87:
        push ebx
    L_00426f88:
        push ebp
    L_00426f89:
        mov ebp,dword ptr [esp+44h]
    L_00426f8d:
        mov eax,edx
    L_00426f8f:
        shr eax,1Fh
    L_00426f92:
        add eax,edx
    L_00426f94:
        cmp cx,64h
    L_00426f98:
        push esi
    L_00426f99:
        push edi
    L_00426f9a:
        mov dword ptr [esp+4Ch],eax
    L_00426f9e:
        mov ebx,4000000h
    L_00426fa3:
        jl asm_target_004270e6
    L_00426fa9:
        lea esi,[ebp+330Ch]
    L_00426faf:
        mov dword ptr [esp+10h],4
    L_00426fb7:
        mov ecx,dword ptr [esi]
    L_00426fb9:
        test ecx,ecx
    L_00426fbb:
        TH10_REL8(0x74, 0x00426fbb, VA_asm_target_0042702f)
    L_00426fbd:
        mov edx,dword ptr [data_00491c10]
    L_00426fc3:
        mov eax,dword ptr [edx+72DAD4h]
    L_00426fc9:
        test eax,eax
    L_00426fcb:
        je short L_00426fdd
    L_00426fcd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00426fd0:
        mov edi,dword ptr [eax]
    L_00426fd2:
        cmp dword ptr [edi],ecx
    L_00426fd4:
        je short L_00426ff6
    L_00426fd6:
        mov eax,dword ptr [eax+4]
    L_00426fd9:
        test eax,eax
    L_00426fdb:
        jne short L_00426fd0
    L_00426fdd:
        mov eax,dword ptr [edx+72DADCh]
    L_00426fe3:
        test eax,eax
    L_00426fe5:
        TH10_REL8(0x74, 0x00426fe5, VA_asm_target_0042702f)
    L_00426fe7:
        mov edx,dword ptr [eax]
    L_00426fe9:
        cmp dword ptr [edx],ecx
    L_00426feb:
        je short L_00426ff6
    L_00426fed:
        mov eax,dword ptr [eax+4]
    L_00426ff0:
        test eax,eax
    L_00426ff2:
        jne short L_00426fe7
    L_00426ff4:
        TH10_REL8(0xeb, 0x00426ff4, VA_asm_target_0042702f)
    L_00426ff6:
        mov eax,dword ptr [eax]
    L_00426ff8:
        test eax,eax
    L_00426ffa:
        TH10_REL8(0x74, 0x00426ffa, VA_asm_target_0042702f)
    L_00426ffc:
        mov edx,dword ptr [eax+35Ch]
    L_00427002:
        mov ecx,dword ptr [eax+18h]
    L_00427005:
        or edx,ebx
    L_00427007:
        test ecx,ecx
    L_00427009:
        mov dword ptr [eax+35Ch],edx
    L_0042700f:
        TH10_REL8(0x75, 0x0042700f, VA_asm_target_0042702f)
    L_00427011:
        mov eax,dword ptr [eax+14h]
    L_00427014:
        test eax,eax
    L_00427016:
        TH10_REL8(0x74, 0x00427016, VA_asm_target_0042702f)
    L_00427018:
        TH10_REL8(0xeb, 0x00427018, VA_asm_FUN_00426f70_part_00427020)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00427020:
        mov ecx,dword ptr [eax]
    L_00427022:
        or dword ptr [ecx+35Ch],ebx
    L_00427028:
        mov eax,dword ptr [eax+4]
    L_0042702b:
        test eax,eax
    L_0042702d:
        jne short L_00427020
    L_0042702f:
        mov dword ptr [esi],0
    L_00427035:
        mov eax,dword ptr [data_00474c68]
    L_0042703a:
        mov ecx,dword ptr [data_00474c6c]
    L_00427040:
        lea edx,[ecx+eax*2]
    L_00427043:
        add eax,edx
    L_00427045:
        cmp eax,5
    L_00427048:
        ja asm_target_004270cc
    L_0042704e:
        jmp dword ptr [eax*4+427930h]
    L_00427055:
        mov eax,dword ptr [ebp+10h]
    L_00427058:
        push 0Fh
    L_0042705a:
        push 14h
    L_0042705c:
        push eax
    L_0042705d:
        lea edi,[esp+3Ch]
    L_00427061:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_00427066:
        mov ecx,dword ptr [eax]
    L_00427068:
        mov dword ptr [esi],ecx
    L_0042706a:
        jmp short L_004270cc
    L_0042706c:
        mov edx,dword ptr [ebp+10h]
    L_0042706f:
        push 0Fh
    L_00427071:
        push 15h
    L_00427073:
        push edx
    L_00427074:
        lea edi,[esp+40h]
    L_00427078:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0042707d:
        mov eax,dword ptr [eax]
    L_0042707f:
        mov dword ptr [esi],eax
    L_00427081:
        jmp short L_004270cc
    L_00427083:
        lea edi,[esp+38h]
    L_00427087:
        jmp short L_004270bb
    L_00427089:
        mov eax,dword ptr [ebp+10h]
    L_0042708c:
        push 0Fh
    L_0042708e:
        push 14h
    L_00427090:
        push eax
    L_00427091:
        lea edi,[esp+48h]
    L_00427095:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0042709a:
        mov ecx,dword ptr [eax]
    L_0042709c:
        mov dword ptr [esi],ecx
    L_0042709e:
        jmp short L_004270cc
    L_004270a0:
        mov edx,dword ptr [ebp+10h]
    L_004270a3:
        push 0Fh
    L_004270a5:
        push 15h
    L_004270a7:
        push edx
    L_004270a8:
        lea edi,[esp+4Ch]
    L_004270ac:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_004270b1:
        mov eax,dword ptr [eax]
    L_004270b3:
        mov dword ptr [esi],eax
    L_004270b5:
        jmp short L_004270cc
    L_004270b7:
        lea edi,[esp+44h]
    L_004270bb:
        mov ecx,dword ptr [ebp+10h]
    L_004270be:
        push 0Fh
    L_004270c0:
        push 16h
    L_004270c2:
        push ecx
    L_004270c3:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_004270c8:
        mov edx,dword ptr [eax]
    L_004270ca:
        mov dword ptr [esi],edx
    L_004270cc:
        mov eax,dword ptr [esp+10h]
    L_004270d0:
        add esi,98h
    L_004270d6:
        dec eax
    L_004270d7:
        mov dword ptr [esp+10h],eax
    L_004270db:
        jne asm_target_00426fb7
    L_004270e1:
        jmp asm_target_00427169
    L_004270e6:
        mov ebx,dword ptr [data_00491c10]
    L_004270ec:
        lea edx,[ebp+330Ch]
    L_004270f2:
        mov esi,4
    L_004270f7:
        mov ecx,dword ptr [edx]
    L_004270f9:
        test ecx,ecx
    L_004270fb:
        je short L_00427160
    L_004270fd:
        mov eax,dword ptr [ebx+72DAD4h]
    L_00427103:
        test eax,eax
    L_00427105:
        je short L_00427114
    L_00427107:
        mov edi,dword ptr [eax]
    L_00427109:
        cmp dword ptr [edi],ecx
    L_0042710b:
        je short L_0042712f
    L_0042710d:
        mov eax,dword ptr [eax+4]
    L_00427110:
        test eax,eax
    L_00427112:
        jne short L_00427107
    L_00427114:
        mov eax,dword ptr [ebx+72DADCh]
    L_0042711a:
        test eax,eax
    L_0042711c:
        je short L_00427160
    L_0042711e:
        mov edi,edi
    L_00427120:
        mov edi,dword ptr [eax]
    L_00427122:
        cmp dword ptr [edi],ecx
    L_00427124:
        je short L_0042712f
    L_00427126:
        mov eax,dword ptr [eax+4]
    L_00427129:
        test eax,eax
    L_0042712b:
        jne short L_00427120
    L_0042712d:
        jmp short L_00427160
    L_0042712f:
        mov eax,dword ptr [eax]
    L_00427131:
        test eax,eax
    L_00427133:
        je short L_00427160
    L_00427135:
        mov edi,dword ptr [eax+18h]
    L_00427138:
        test edi,edi
    L_0042713a:
        mov ecx,1
    L_0042713f:
        mov word ptr [eax+304h],cx
    L_00427146:
        jne short L_00427160
    L_00427148:
        mov eax,dword ptr [eax+14h]
    L_0042714b:
        test eax,eax
    L_0042714d:
        je short L_00427160
    L_0042714f:
        nop
    L_00427150:
        mov edi,dword ptr [eax]
    L_00427152:
        mov word ptr [edi+304h],cx
    L_00427159:
        mov eax,dword ptr [eax+4]
    L_0042715c:
        test eax,eax
    L_0042715e:
        jne short L_00427150
    L_00427160:
        add edx,98h
    L_00427166:
        dec esi
    L_00427167:
        jne short L_004270f7
    L_00427169:
        mov eax,dword ptr [esp+4Ch]
    L_0042716d:
        cmp eax,5
    L_00427170:
        jl short L_0042717b
    L_00427172:
        mov eax,4
    L_00427177:
        mov dword ptr [esp+4Ch],eax
    L_0042717b:
        cmp dword ptr [ebp+3500h],eax
    L_00427181:
        je asm_target_00427924
    L_00427187:
        xor esi,esi
    L_00427189:
        test eax,eax
    L_0042718b:
        mov dword ptr [esp+10h],esi
    L_0042718f:
        jle asm_target_00427857
    L_00427195:
        TH10_REL8(0xeb, 0x00427195, VA_asm_FUN_00426f70_part_004271a0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_004271a0:
        mov ecx,dword ptr [ebp+3CCh]
    L_004271a6:
        mov eax,esi
    L_004271a8:
        imul eax,98h
    L_004271ae:
        lea edi,[eax+ebp]
    L_004271b1:
        mov dword ptr [edi+32DCh],ecx
    L_004271b7:
        mov edx,dword ptr [ebp+3D0h]
    L_004271bd:
        mov dword ptr [edi+32E0h],edx
    L_004271c3:
        mov ecx,dword ptr [edi+3308h]
    L_004271c9:
        test ecx,ecx
    L_004271cb:
        je short L_0042723f
    L_004271cd:
        mov edx,dword ptr [data_00491c10]
    L_004271d3:
        mov eax,dword ptr [edx+72DAD4h]
    L_004271d9:
        test eax,eax
    L_004271db:
        je short L_004271ed
    L_004271dd:
        TH10_NOP_LEA_ECX_DISP8()
    L_004271e0:
        mov ebx,dword ptr [eax]
    L_004271e2:
        cmp dword ptr [ebx],ecx
    L_004271e4:
        je short L_00427206
    L_004271e6:
        mov eax,dword ptr [eax+4]
    L_004271e9:
        test eax,eax
    L_004271eb:
        jne short L_004271e0
    L_004271ed:
        mov eax,dword ptr [edx+72DADCh]
    L_004271f3:
        test eax,eax
    L_004271f5:
        je short L_0042723f
    L_004271f7:
        mov edx,dword ptr [eax]
    L_004271f9:
        cmp dword ptr [edx],ecx
    L_004271fb:
        je short L_00427206
    L_004271fd:
        mov eax,dword ptr [eax+4]
    L_00427200:
        test eax,eax
    L_00427202:
        jne short L_004271f7
    L_00427204:
        jmp short L_0042723f
    L_00427206:
        mov eax,dword ptr [eax]
    L_00427208:
        test eax,eax
    L_0042720a:
        je short L_0042723f
    L_0042720c:
        mov ebx,dword ptr [eax+35Ch]
    L_00427212:
        mov ecx,dword ptr [eax+18h]
    L_00427215:
        mov edx,4000000h
    L_0042721a:
        or ebx,edx
    L_0042721c:
        test ecx,ecx
    L_0042721e:
        mov dword ptr [eax+35Ch],ebx
    L_00427224:
        jne short L_0042723f
    L_00427226:
        mov eax,dword ptr [eax+14h]
    L_00427229:
        test eax,eax
    L_0042722b:
        je short L_0042723f
    L_0042722d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00427230:
        mov ecx,dword ptr [eax]
    L_00427232:
        or dword ptr [ecx+35Ch],edx
    L_00427238:
        mov eax,dword ptr [eax+4]
    L_0042723b:
        test eax,eax
    L_0042723d:
        jne short L_00427230
    L_0042723f:
        mov dword ptr [edi+3308h],0
    L_00427249:
        mov dword ptr [edi+3328h],esi
    L_0042724f:
        mov eax,dword ptr [data_00474c68]
    L_00427254:
        sub eax,0
    L_00427257:
        je asm_target_0042764e
    L_0042725d:
        dec eax
    L_0042725e:
        jne asm_target_00427833
    L_00427264:
        mov eax,dword ptr [data_00474c6c]
    L_00427269:
        sub eax,0
    L_0042726c:
        je asm_target_0042749b
    L_00427272:
        dec eax
    L_00427273:
        je asm_target_00427381
    L_00427279:
        dec eax
    L_0042727a:
        jne asm_target_00427833
    L_00427280:
        mov eax,dword ptr [esp+4Ch]
    L_00427284:
        mov eax,dword ptr [eax*4+476F7Ch]
    L_0042728b:
        mov edx,dword ptr [ebp+45Ch]
    L_00427291:
        add eax,esi
    L_00427293:
        lea ecx,[eax+eax*2]
    L_00427296:
        fld dword ptr [edx+ecx*4+20h]
    L_0042729a:
        lea esi,[edx+ecx*4+20h]
    L_0042729e:
        fmul dword ptr [data_00470b44]
    L_004272a4:
        call asm_FUN_00463b2c_00463b2c
    L_004272a9:
        mov dword ptr [edi+32E4h],eax
    L_004272af:
        fld dword ptr [esi+4]
    L_004272b2:
        fmul dword ptr [data_00470b44]
    L_004272b8:
        call asm_FUN_00463b2c_00463b2c
    L_004272bd:
        mov dword ptr [edi+32E8h],eax
    L_004272c3:
        mov eax,dword ptr [ebp+4474h]
    L_004272c9:
        test eax,eax
    L_004272cb:
        je short L_004272d7
    L_004272cd:
        mov eax,dword ptr [edi+32A0h]
    L_004272d3:
        test eax,eax
    L_004272d5:
        jne short L_0042730b
    L_004272d7:
        mov eax,dword ptr [ebp+3CCh]
    L_004272dd:
        mov esi,dword ptr [edi+32E4h]
    L_004272e3:
        mov ecx,dword ptr [edi+32E8h]
    L_004272e9:
        mov edx,dword ptr [ebp+3D0h]
    L_004272ef:
        add eax,esi
    L_004272f1:
        add ecx,edx
    L_004272f3:
        mov dword ptr [edi+32D4h],eax
    L_004272f9:
        mov dword ptr [edi+32D8h],ecx
    L_004272ff:
        mov dword ptr [edi+32ECh],eax
    L_00427305:
        mov dword ptr [edi+32F0h],ecx
    L_0042730b:
        mov esi,dword ptr [data_00491c10]
    L_00427311:
        mov ebx,dword ptr [ebp+10h]
    L_00427314:
        call asm_FUN_00449950_00449950
    L_00427319:
        mov esi,eax
    L_0042731b:
        mov eax,dword ptr [esi+35Ch]
    L_00427321:
        push 13h
    L_00427323:
        or eax,40000000h
    L_00427328:
        push esi
    L_00427329:
        mov ecx,ebx
    L_0042732b:
        mov dword ptr [esi+20h],0Fh
    L_00427332:
        mov dword ptr [esi+35Ch],eax
    L_00427338:
        call asm_FUN_00449870_00449870
    L_0042733d:
        mov edx,dword ptr [data_00491c10]
    L_00427343:
        mov ebx,esi
    L_00427345:
        lea eax,[esp+14h]
    L_00427349:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0042734e:
        mov eax,dword ptr [esp+14h]
    L_00427352:
        mov dword ptr [edi+3308h],eax
    L_00427358:
        mov eax,dword ptr [ebp+4474h]
    L_0042735e:
        test eax,eax
    L_00427360:
        je short L_00427372
    L_00427362:
        mov esi,3
    L_00427367:
        lea eax,[edi+3308h]
    L_0042736d:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00427372:
        mov dword ptr [edi+3330h],427AD0h
    L_0042737c:
        jmp asm_target_0042782f
    L_00427381:
        mov ecx,dword ptr [esp+4Ch]
    L_00427385:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_0042738c:
        add eax,esi
    L_0042738e:
        lea edx,[eax+eax*2]
    L_00427391:
        mov eax,dword ptr [ebp+45Ch]
    L_00427397:
        fld dword ptr [eax+edx*4+20h]
    L_0042739b:
        lea eax,[eax+edx*4+20h]
    L_0042739f:
        fmul dword ptr [data_00470b44]
    L_004273a5:
        mov dword ptr [esp+18h],eax
    L_004273a9:
        lea ebx,[edi+32E4h]
    L_004273af:
        call asm_FUN_00463b2c_00463b2c
    L_004273b4:
        mov ecx,dword ptr [esp+18h]
    L_004273b8:
        mov dword ptr [ebx],eax
    L_004273ba:
        fld dword ptr [ecx+4]
    L_004273bd:
        fmul dword ptr [data_00470b44]
    L_004273c3:
        call asm_FUN_00463b2c_00463b2c
    L_004273c8:
        mov edx,dword ptr [esp+4Ch]
    L_004273cc:
        mov dword ptr [ebx+4],eax
    L_004273cf:
        mov eax,dword ptr [edx*4+476F7Ch]
    L_004273d6:
        mov ecx,dword ptr [ebp+45Ch]
    L_004273dc:
        add eax,esi
    L_004273de:
        lea eax,[eax+eax*2]
    L_004273e1:
        fld dword ptr [ecx+eax*4+98h]
    L_004273e8:
        lea eax,[ecx+eax*4+98h]
    L_004273ef:
        fmul dword ptr [data_00470b44]
    L_004273f5:
        mov dword ptr [esp+18h],eax
    L_004273f9:
        lea esi,[edi+32ECh]
    L_004273ff:
        call asm_FUN_00463b2c_00463b2c
    L_00427404:
        mov edx,dword ptr [esp+18h]
    L_00427408:
        mov dword ptr [esi],eax
    L_0042740a:
        fld dword ptr [edx+4]
    L_0042740d:
        fmul dword ptr [data_00470b44]
    L_00427413:
        call asm_FUN_00463b2c_00463b2c
    L_00427418:
        mov dword ptr [esi+4],eax
    L_0042741b:
        mov eax,dword ptr [ebp+4474h]
    L_00427421:
        test eax,eax
    L_00427423:
        jne short L_00427427
    L_00427425:
        mov esi,ebx
    L_00427427:
        mov eax,dword ptr [esi]
    L_00427429:
        mov ecx,dword ptr [ebp+3CCh]
    L_0042742f:
        mov ebx,dword ptr [esi+4]
    L_00427432:
        mov esi,dword ptr [data_00491c10]
    L_00427438:
        add eax,ecx
    L_0042743a:
        mov ecx,dword ptr [ebp+3D0h]
    L_00427440:
        add ecx,ebx
    L_00427442:
        mov dword ptr [edi+32D4h],eax
    L_00427448:
        mov dword ptr [edi+32D8h],ecx
    L_0042744e:
        mov ebx,dword ptr [ebp+10h]
    L_00427451:
        call asm_FUN_00449950_00449950
    L_00427456:
        mov esi,eax
    L_00427458:
        mov edx,dword ptr [esi+35Ch]
    L_0042745e:
        push 12h
    L_00427460:
        or edx,40000000h
    L_00427466:
        push esi
    L_00427467:
        mov ecx,ebx
    L_00427469:
        mov dword ptr [esi+20h],0Fh
    L_00427470:
        mov dword ptr [esi+35Ch],edx
    L_00427476:
        call asm_FUN_00449870_00449870
    L_0042747b:
        mov edx,dword ptr [data_00491c10]
    L_00427481:
        mov ebx,esi
    L_00427483:
        lea eax,[esp+1Ch]
    L_00427487:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0042748c:
        mov eax,dword ptr [esp+1Ch]
    L_00427490:
        mov dword ptr [edi+3308h],eax
    L_00427496:
        jmp asm_target_0042782f
    L_0042749b:
        mov eax,dword ptr [ebp+4474h]
    L_004274a1:
        test eax,eax
    L_004274a3:
        jne short L_004274e8
    L_004274a5:
        mov ecx,dword ptr [esp+4Ch]
    L_004274a9:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_004274b0:
        add eax,esi
    L_004274b2:
        lea edx,[eax+eax*2]
    L_004274b5:
        mov eax,dword ptr [ebp+45Ch]
    L_004274bb:
        fld dword ptr [eax+edx*4+20h]
    L_004274bf:
        lea ebx,[eax+edx*4+20h]
    L_004274c3:
        fmul dword ptr [data_00470b44]
    L_004274c9:
        call asm_FUN_00463b2c_00463b2c
    L_004274ce:
        mov dword ptr [edi+32E4h],eax
    L_004274d4:
        fld dword ptr [ebx+4]
    L_004274d7:
        fmul dword ptr [data_00470b44]
    L_004274dd:
        call asm_FUN_00463b2c_00463b2c
    L_004274e2:
        mov dword ptr [edi+32E8h],eax
    L_004274e8:
        mov ecx,dword ptr [esp+4Ch]
    L_004274ec:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_004274f3:
        add eax,esi
    L_004274f5:
        lea edx,[eax+eax*2]
    L_004274f8:
        mov eax,dword ptr [ebp+45Ch]
    L_004274fe:
        fld dword ptr [eax+edx*4+98h]
    L_00427505:
        lea ebx,[eax+edx*4+98h]
    L_0042750c:
        fmul dword ptr [data_00470b44]
    L_00427512:
        call asm_FUN_00463b2c_00463b2c
    L_00427517:
        mov dword ptr [edi+32ECh],eax
    L_0042751d:
        fld dword ptr [ebx+4]
    L_00427520:
        fmul dword ptr [data_00470b44]
    L_00427526:
        call asm_FUN_00463b2c_00463b2c
    L_0042752b:
        mov ecx,dword ptr [g_player]
    L_00427531:
        mov dword ptr [edi+32F0h],eax
    L_00427537:
        mov eax,esi
    L_00427539:
        shl eax,6
    L_0042753c:
        mov edx,dword ptr [eax+ecx+43ACh]
    L_00427543:
        mov dword ptr [esp+18h],eax
    L_00427547:
        mov dword ptr [edi+32D4h],edx
    L_0042754d:
        mov eax,dword ptr [eax+ecx+43B0h]
    L_00427554:
        mov dword ptr [edi+32D8h],eax
    L_0042755a:
        mov eax,dword ptr [ebp+4474h]
    L_00427560:
        test eax,eax
    L_00427562:
        je short L_004275d3
    L_00427564:
        mov eax,dword ptr [edi+32A0h]
    L_0042756a:
        test eax,eax
    L_0042756c:
        jne short L_004275d3
    L_0042756e:
        test esi,esi
    L_00427570:
        jne short L_004275bb
    L_00427572:
        mov ecx,dword ptr [esp+4Ch]
    L_00427576:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_0042757d:
        lea edx,[eax+eax*2]
    L_00427580:
        mov eax,dword ptr [ebp+45Ch]
    L_00427586:
        fld dword ptr [eax+edx*4+98h]
    L_0042758d:
        lea esi,[eax+edx*4+98h]
    L_00427594:
        fmul dword ptr [data_00470b44]
    L_0042759a:
        call asm_FUN_00463b2c_00463b2c
    L_0042759f:
        mov dword ptr [ebp+32E4h],eax
    L_004275a5:
        fld dword ptr [esi+4]
    L_004275a8:
        fmul dword ptr [data_00470b44]
    L_004275ae:
        call asm_FUN_00463b2c_00463b2c
    L_004275b3:
        mov dword ptr [ebp+32E8h],eax
    L_004275b9:
        jmp short L_004275d3
    L_004275bb:
        mov ecx,dword ptr [edi+324Ch]
    L_004275c1:
        mov dword ptr [edi+32E4h],ecx
    L_004275c7:
        mov edx,dword ptr [edi+3250h]
    L_004275cd:
        mov dword ptr [edi+32E8h],edx
    L_004275d3:
        mov esi,dword ptr [data_00491c10]
    L_004275d9:
        mov dword ptr [edi+3330h],427950h
    L_004275e3:
        mov ebx,dword ptr [ebp+10h]
    L_004275e6:
        call asm_FUN_00449950_00449950
    L_004275eb:
        mov esi,eax
    L_004275ed:
        mov edx,dword ptr [esi+35Ch]
    L_004275f3:
        push 11h
    L_004275f5:
        or edx,40000000h
    L_004275fb:
        push esi
    L_004275fc:
        mov ecx,ebx
    L_004275fe:
        mov dword ptr [esi+20h],0Fh
    L_00427605:
        mov dword ptr [esi+35Ch],edx
    L_0042760b:
        call asm_FUN_00449870_00449870
    L_00427610:
        mov edx,dword ptr [data_00491c10]
    L_00427616:
        mov ebx,esi
    L_00427618:
        lea eax,[esp+20h]
    L_0042761c:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00427621:
        mov eax,dword ptr [esp+20h]
    L_00427625:
        mov dword ptr [edi+3308h],eax
    L_0042762b:
        mov eax,dword ptr [esp+18h]
    L_0042762f:
        mov ecx,dword ptr [eax+ebp+436Ch]
    L_00427636:
        mov dword ptr [edi+32DCh],ecx
    L_0042763c:
        mov edx,dword ptr [eax+ebp+4370h]
    L_00427643:
        mov dword ptr [edi+32E0h],edx
    L_00427649:
        jmp asm_target_0042782f
    L_0042764e:
        mov eax,dword ptr [esp+4Ch]
    L_00427652:
        mov eax,dword ptr [eax*4+476F7Ch]
    L_00427659:
        mov edx,dword ptr [ebp+45Ch]
    L_0042765f:
        add eax,esi
    L_00427661:
        lea ecx,[eax+eax*2]
    L_00427664:
        fld dword ptr [edx+ecx*4+20h]
    L_00427668:
        lea eax,[edx+ecx*4+20h]
    L_0042766c:
        fmul dword ptr [data_00470b44]
    L_00427672:
        mov dword ptr [esp+18h],eax
    L_00427676:
        lea ebx,[edi+32E4h]
    L_0042767c:
        call asm_FUN_00463b2c_00463b2c
    L_00427681:
        mov dword ptr [ebx],eax
    L_00427683:
        mov eax,dword ptr [esp+18h]
    L_00427687:
        fld dword ptr [eax+4]
    L_0042768a:
        fmul dword ptr [data_00470b44]
    L_00427690:
        call asm_FUN_00463b2c_00463b2c
    L_00427695:
        mov ecx,dword ptr [esp+4Ch]
    L_00427699:
        mov dword ptr [ebx+4],eax
    L_0042769c:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_004276a3:
        add eax,esi
    L_004276a5:
        lea edx,[eax+eax*2]
    L_004276a8:
        mov eax,dword ptr [ebp+45Ch]
    L_004276ae:
        fld dword ptr [eax+edx*4+98h]
    L_004276b5:
        lea eax,[eax+edx*4+98h]
    L_004276bc:
        fmul dword ptr [data_00470b44]
    L_004276c2:
        mov dword ptr [esp+18h],eax
    L_004276c6:
        call asm_FUN_00463b2c_00463b2c
    L_004276cb:
        mov ecx,dword ptr [esp+18h]
    L_004276cf:
        mov dword ptr [edi+32ECh],eax
    L_004276d5:
        fld dword ptr [ecx+4]
    L_004276d8:
        fmul dword ptr [data_00470b44]
    L_004276de:
        call asm_FUN_00463b2c_00463b2c
    L_004276e3:
        mov dword ptr [edi+32F0h],eax
    L_004276e9:
        mov eax,dword ptr [ebp+4474h]
    L_004276ef:
        test eax,eax
    L_004276f1:
        je short L_004276f9
    L_004276f3:
        lea ebx,[edi+32ECh]
    L_004276f9:
        mov ecx,dword ptr [ebx]
    L_004276fb:
        mov eax,dword ptr [ebp+3CCh]
    L_00427701:
        mov edx,dword ptr [ebx+4]
    L_00427704:
        add eax,ecx
    L_00427706:
        mov ecx,dword ptr [ebp+3D0h]
    L_0042770c:
        add ecx,edx
    L_0042770e:
        mov dword ptr [edi+32D4h],eax
    L_00427714:
        mov dword ptr [edi+32D8h],ecx
    L_0042771a:
        mov dword ptr [edi+32DCh],eax
    L_00427720:
        mov dword ptr [edi+32E0h],ecx
    L_00427726:
        mov eax,dword ptr [data_00474c6c]
    L_0042772b:
        sub eax,0
    L_0042772e:
        je asm_target_004277e1
    L_00427734:
        dec eax
    L_00427735:
        je short L_00427791
    L_00427737:
        dec eax
    L_00427738:
        jne asm_target_00427833
    L_0042773e:
        mov esi,dword ptr [data_00491c10]
    L_00427744:
        mov ebx,dword ptr [ebp+10h]
    L_00427747:
        call asm_FUN_00449950_00449950
    L_0042774c:
        mov esi,eax
    L_0042774e:
        mov edx,dword ptr [esi+35Ch]
    L_00427754:
        push 13h
    L_00427756:
        or edx,40000000h
    L_0042775c:
        push esi
    L_0042775d:
        mov ecx,ebx
    L_0042775f:
        mov dword ptr [esi+20h],0Fh
    L_00427766:
        mov dword ptr [esi+35Ch],edx
    L_0042776c:
        call asm_FUN_00449870_00449870
    L_00427771:
        mov edx,dword ptr [data_00491c10]
    L_00427777:
        mov ebx,esi
    L_00427779:
        lea eax,[esp+24h]
    L_0042777d:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00427782:
        mov edx,dword ptr [esp+24h]
    L_00427786:
        mov dword ptr [edi+3308h],edx
    L_0042778c:
        jmp asm_target_0042782f
    L_00427791:
        mov esi,dword ptr [data_00491c10]
    L_00427797:
        mov ebx,dword ptr [ebp+10h]
    L_0042779a:
        call asm_FUN_00449950_00449950
    L_0042779f:
        mov esi,eax
    L_004277a1:
        mov edx,dword ptr [esi+35Ch]
    L_004277a7:
        push 12h
    L_004277a9:
        or edx,40000000h
    L_004277af:
        push esi
    L_004277b0:
        mov ecx,ebx
    L_004277b2:
        mov dword ptr [esi+20h],0Fh
    L_004277b9:
        mov dword ptr [esi+35Ch],edx
    L_004277bf:
        call asm_FUN_00449870_00449870
    L_004277c4:
        mov edx,dword ptr [data_00491c10]
    L_004277ca:
        mov ebx,esi
    L_004277cc:
        lea eax,[esp+28h]
    L_004277d0:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_004277d5:
        mov eax,dword ptr [esp+28h]
    L_004277d9:
        mov dword ptr [edi+3308h],eax
    L_004277df:
        jmp short L_0042782f
    L_004277e1:
        mov esi,dword ptr [data_00491c10]
    L_004277e7:
        mov ebx,dword ptr [ebp+10h]
    L_004277ea:
        call asm_FUN_00449950_00449950
    L_004277ef:
        mov esi,eax
    L_004277f1:
        mov edx,dword ptr [esi+35Ch]
    L_004277f7:
        push 11h
    L_004277f9:
        or edx,40000000h
    L_004277ff:
        push esi
    L_00427800:
        mov ecx,ebx
    L_00427802:
        mov dword ptr [esi+20h],0Fh
    L_00427809:
        mov dword ptr [esi+35Ch],edx
    L_0042780f:
        call asm_FUN_00449870_00449870
    L_00427814:
        mov edx,dword ptr [data_00491c10]
    L_0042781a:
        mov ebx,esi
    L_0042781c:
        lea eax,[esp+2Ch]
    L_00427820:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00427825:
        mov ecx,dword ptr [esp+2Ch]
    L_00427829:
        mov dword ptr [edi+3308h],ecx
    L_0042782f:
        mov esi,dword ptr [esp+10h]
    L_00427833:
        mov eax,dword ptr [esp+4Ch]
    L_00427837:
        inc esi
    L_00427838:
        cmp esi,eax
    L_0042783a:
        mov dword ptr [edi+32A0h],2
    L_00427844:
        mov dword ptr [esp+10h],esi
    L_00427848:
        jl asm_FUN_00426f70_part_004271a0
    L_0042784e:
        cmp esi,4
    L_00427851:
        jge asm_target_004278fd
    L_00427857:
        mov ebx,dword ptr [data_00491c10]
    L_0042785d:
        mov edx,esi
    L_0042785f:
        imul edx,98h
    L_00427865:
        mov edi,4
    L_0042786a:
        lea edx,[edx+ebp+3308h]
    L_00427871:
        sub edi,esi
    L_00427873:
        mov ecx,dword ptr [edx]
    L_00427875:
        test ecx,ecx
    L_00427877:
        mov dword ptr [edx-68h],0
    L_0042787e:
        TH10_REL8(0x74, 0x0042787e, VA_asm_target_004278f0)
    L_00427880:
        mov eax,dword ptr [ebx+72DAD4h]
    L_00427886:
        test eax,eax
    L_00427888:
        je short L_0042789d
    L_0042788a:
        lea ebx,[ebx+force_disp32_zero]
    L_00427890:
        mov esi,dword ptr [eax]
    L_00427892:
        cmp dword ptr [esi],ecx
    L_00427894:
        je short L_004278b6
    L_00427896:
        mov eax,dword ptr [eax+4]
    L_00427899:
        test eax,eax
    L_0042789b:
        jne short L_00427890
    L_0042789d:
        mov eax,dword ptr [ebx+72DADCh]
    L_004278a3:
        test eax,eax
    L_004278a5:
        TH10_REL8(0x74, 0x004278a5, VA_asm_target_004278f0)
    L_004278a7:
        mov esi,dword ptr [eax]
    L_004278a9:
        cmp dword ptr [esi],ecx
    L_004278ab:
        je short L_004278b6
    L_004278ad:
        mov eax,dword ptr [eax+4]
    L_004278b0:
        test eax,eax
    L_004278b2:
        jne short L_004278a7
    L_004278b4:
        TH10_REL8(0xeb, 0x004278b4, VA_asm_target_004278f0)
    L_004278b6:
        mov eax,dword ptr [eax]
    L_004278b8:
        test eax,eax
    L_004278ba:
        TH10_REL8(0x74, 0x004278ba, VA_asm_target_004278f0)
    L_004278bc:
        mov esi,dword ptr [eax+18h]
    L_004278bf:
        test esi,esi
    L_004278c1:
        mov ecx,1
    L_004278c6:
        mov word ptr [eax+304h],cx
    L_004278cd:
        TH10_REL8(0x75, 0x004278cd, VA_asm_target_004278f0)
    L_004278cf:
        mov eax,dword ptr [eax+14h]
    L_004278d2:
        test eax,eax
    L_004278d4:
        TH10_REL8(0x74, 0x004278d4, VA_asm_target_004278f0)
    L_004278d6:
        TH10_REL8(0xeb, 0x004278d6, VA_asm_FUN_00426f70_part_004278e0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_004278e0:
        mov esi,dword ptr [eax]
    L_004278e2:
        mov word ptr [esi+304h],cx
    L_004278e9:
        mov eax,dword ptr [eax+4]
    L_004278ec:
        test eax,eax
    L_004278ee:
        jne short L_004278e0
    L_004278f0:
        add edx,98h
    L_004278f6:
        dec edi
    L_004278f7:
        jne asm_target_00427873
    L_004278fd:
        mov ecx,dword ptr [esp+4Ch]
    L_00427901:
        mov eax,1
    L_00427906:
        mov dword ptr [ebp+3500h],ecx
    L_0042790c:
        mov dword ptr [ebp+332Ch],eax
    L_00427912:
        mov dword ptr [ebp+33C4h],eax
    L_00427918:
        mov dword ptr [ebp+345Ch],eax
    L_0042791e:
        mov dword ptr [ebp+34F4h],eax
    L_00427924:
        pop edi
    L_00427925:
        pop esi
    L_00427926:
        pop ebp
    L_00427927:
        pop ebx
    L_00427928:
        add esp,38h
    L_0042792b:
        ret 4
        _emit 0x8b
        _emit 0xff
        _emit 0x55
        _emit 0x70
        _emit 0x42
        _emit 0x00
        _emit 0x6c
        _emit 0x70
        _emit 0x42
        _emit 0x00
        _emit 0x83
        _emit 0x70
        _emit 0x42
        _emit 0x00
        _emit 0x89
        _emit 0x70
        _emit 0x42
        _emit 0x00
        _emit 0xa0
        _emit 0x70
        _emit 0x42
        _emit 0x00
        _emit 0xb7
        _emit 0x70
        _emit 0x42
        _emit 0x00
    }
}

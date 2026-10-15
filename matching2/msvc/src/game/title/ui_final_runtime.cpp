#include "asm_encoding.hpp"
#include "asm_symbols.hpp"






// 0x00433EF0..0x0043408C: FUN_00433ef0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00433ef0_00433ef0() {
    __asm {
    L_00433ef0:
        sub esp,1Ch
    L_00433ef3:
        push ebp
    L_00433ef4:
        mov ebp,dword ptr [esp+24h]
    L_00433ef8:
        mov eax,dword ptr [ebp+20h]
    L_00433efb:
        cmp eax,3
    L_00433efe:
        ja asm_target_004349c1
    L_00433f04:
        push ebx
    L_00433f05:
        push esi
    L_00433f06:
        push edi
    L_00433f07:
        jmp dword ptr [eax*4+4349CCh]
    L_00433f0e:
        cmp dword ptr [ebp+2B4h],1
    L_00433f15:
        jne asm_target_00434101
    L_00433f1b:
        mov dword ptr [ebp+2Ch],6
    L_00433f22:
        mov eax,dword ptr [ebp+2Ch]
    L_00433f25:
        test eax,eax
    L_00433f27:
        je short L_00433f38
    L_00433f29:
        jg short L_00433f31
    L_00433f2b:
        dec eax
    L_00433f2c:
        mov dword ptr [ebp+24h],eax
    L_00433f2f:
        jmp short L_00433f3f
    L_00433f31:
        xor eax,eax
    L_00433f33:
        mov dword ptr [ebp+24h],eax
    L_00433f36:
        jmp short L_00433f3f
    L_00433f38:
        mov dword ptr [ebp+24h],0
    L_00433f3f:
        mov eax,dword ptr [ebp+440h]
    L_00433f45:
        mov edx,dword ptr [g_sprt_ctrl]
    L_00433f4b:
        push eax
    L_00433f4c:
        call asm_AnimationManager_Find_004491c0
    L_00433f51:
        test eax,eax
    L_00433f53:
        jne short L_00433f82
    L_00433f55:
        push ebp
    L_00433f56:
        mov edi,5Fh
    L_00433f5b:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00433f60:
        mov ecx,dword ptr [g_ascii_manager]
    L_00433f66:
        mov eax,dword ptr [ecx+8994h]
    L_00433f6c:
        push 0Fh
    L_00433f6e:
        push 8
    L_00433f70:
        push eax
    L_00433f71:
        lea edi,[esp+28h]
    L_00433f75:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00433f7a:
        mov edx,dword ptr [eax]
    L_00433f7c:
        mov dword ptr [ebp+5D0h],edx
    L_00433f82:
        push ebp
    L_00433f83:
        mov edi,67h
    L_00433f88:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00433f8d:
        push 0
    L_00433f8f:
        lea eax,[esp+34h]
    L_00433f93:
        push eax
    L_00433f94:
        mov eax,46ED14h
    L_00433f99:
        mov dword ptr [esp+20h],0
    L_00433fa1:
        call asm_FUN_0044b360_0044b360
    L_00433fa6:
        test eax,eax
    L_00433fa8:
        mov dword ptr [ebp+5AACh],eax
    L_00433fae:
        je asm_target_00434803
    L_00433fb4:
        mov ecx,dword ptr [esp+30h]
    L_00433fb8:
        test ecx,ecx
    L_00433fba:
        jle asm_target_00434054
    L_00433fc0:
        lea ecx,[ebp+0E98h]
    L_00433fc6:
        lea edx,[ebp+698h]
    L_00433fcc:
        lea esi,[ebp+16D8h]
    L_00433fd2:
        mov dword ptr [esp+14h],ecx
    L_00433fd6:
        mov dword ptr [esp+10h],edx
    L_00433fda:
        lea ebx,[ebx+force_disp32_zero]
    L_00433fe0:
        mov cl,byte ptr [eax]
    L_00433fe2:
        cmp cl,23h
    L_00433fe5:
        je short L_00434043
    L_00433fe7:
        cmp cl,40h
    L_00433fea:
        jne short L_00434043
    L_00433fec:
        lea ecx,[eax+1]
    L_00433fef:
        mov eax,dword ptr [esp+10h]
    L_00433ff3:
        push eax
    L_00433ff4:
        lea edi,[esp+34h]
    L_00433ff8:
        call asm_StageText_ExtractLine_00434a20
    L_00433ffd:
        mov ecx,dword ptr [esp+14h]
    L_00434001:
        push ecx
    L_00434002:
        mov ecx,eax
    L_00434004:
        call asm_StageText_ExtractLine_00434a20
    L_00434009:
        mov ebx,8
    L_0043400e:
        mov edi,edi
    L_00434010:
        push esi
    L_00434011:
        lea edi,[esp+34h]
    L_00434015:
        mov ecx,eax
    L_00434017:
        call asm_StageText_ExtractLine_00434a20
    L_0043401c:
        add esi,42h
    L_0043401f:
        dec ebx
    L_00434020:
        jne short L_00434010
    L_00434022:
        mov edi,dword ptr [esp+18h]
    L_00434026:
        mov edx,dword ptr [esp+10h]
    L_0043402a:
        mov ecx,dword ptr [esp+14h]
    L_0043402e:
        inc edi
    L_0043402f:
        add edx,40h
    L_00434032:
        add ecx,42h
    L_00434035:
        mov dword ptr [esp+18h],edi
    L_00434039:
        mov dword ptr [esp+10h],edx
    L_0043403d:
        mov dword ptr [esp+14h],ecx
    L_00434041:
        jmp short L_0043404c
    L_00434043:
        lea edx,[esp+30h]
    L_00434047:
        call asm_StageText_SkipLine_004349e0
    L_0043404c:
        mov ecx,dword ptr [esp+30h]
    L_00434050:
        test ecx,ecx
    L_00434052:
        jg short L_00433fe0
    L_00434054:
        mov ecx,dword ptr [esp+18h]
    L_00434058:
        mov eax,ecx
    L_0043405a:
        xor edi,edi
    L_0043405c:
        cmp eax,edi
    L_0043405e:
        mov dword ptr [ebp+2Ch],ecx
    L_00434061:
        je short L_00434072
    L_00434063:
        jg short L_0043406b
    L_00434065:
        dec eax
    L_00434066:
        mov dword ptr [ebp+24h],eax
    L_00434069:
        jmp short L_00434075
    L_0043406b:
        xor eax,eax
    L_0043406d:
        mov dword ptr [ebp+24h],eax
    L_00434070:
        jmp short L_00434075
    L_00434072:
        mov dword ptr [ebp+24h],edi
    L_00434075:
        lea edx,[ebp+664h]
    L_0043407b:
        mov dword ptr [ebp+58D8h],edi
    L_00434081:
        mov dword ptr [ebp+688h],ecx
    L_00434087:
        mov dword ptr [esp+30h],edx
    L_0043408b:
        TH10_REL8(0xeb, 0x0043408b, VA_asm_FUN_00433ef0_part_00434090)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00434090:
        mov eax,dword ptr [data_00491fec]
    L_00434095:
        mov esi,dword ptr [g_sprt_ctrl]
    L_0043409b:
        mov dword ptr [esp+18h],eax
    L_0043409f:
        call asm_FUN_00449950_00449950
    L_004340a4:
        mov ebx,eax
    L_004340a6:
        or dword ptr [ebx+35Ch],40000000h
    L_004340b0:
        lea ecx,[edi+27h]
    L_004340b3:
        push ecx
    L_004340b4:
        mov ecx,dword ptr [esp+1Ch]
    L_004340b8:
        push ebx
    L_004340b9:
        mov dword ptr [ebx+20h],0Fh
    L_004340c0:
        call asm_FUN_00449870_00449870
    L_004340c5:
        mov edx,dword ptr [g_sprt_ctrl]
    L_004340cb:
        lea eax,[esp+14h]
    L_004340cf:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_004340d4:
        mov eax,dword ptr [esp+30h]
    L_004340d8:
        mov edx,dword ptr [esp+14h]
    L_004340dc:
        mov dword ptr [eax],edx
    L_004340de:
        inc edi
    L_004340df:
        add eax,4
    L_004340e2:
        cmp edi,8
    L_004340e5:
        mov dword ptr [esp+30h],eax
    L_004340e9:
        jl short L_00434090
    L_004340eb:
        xor ecx,ecx
    L_004340ed:
        mov dword ptr [ebp+68Ch],ecx
    L_004340f3:
        mov dword ptr [ebp+690h],ecx
    L_004340f9:
        mov dword ptr [ebp+694h],ecx
    L_004340ff:
        jmp short L_00434103
    L_00434101:
        xor ecx,ecx
    L_00434103:
        mov eax,dword ptr [ebp+2B4h]
    L_00434109:
        cmp eax,0Ah
    L_0043410c:
        jge asm_target_004342dd
    L_00434112:
        fild dword ptr [ebp+58D8h]
    L_00434118:
        lea edx,[eax+eax*4]
    L_0043411b:
        lea edx,[edx*8-28h]
    L_00434122:
        mov dword ptr [esp+30h],edx
    L_00434126:
        fmul dword ptr [data_00470ca0]
    L_0043412c:
        add eax,eax
    L_0043412e:
        lea edi,[eax-2]
    L_00434131:
        cmp edi,eax
    L_00434133:
        fsubr dword ptr [data_00470c80]
    L_00434139:
        mov dword ptr [esp+20h],42800000h
    L_00434141:
        mov dword ptr [esp+28h],0
    L_00434149:
        fiadd dword ptr [esp+30h]
    L_0043414d:
        fstp dword ptr [esp+24h]
    L_00434151:
        jge asm_target_004342dd
    L_00434157:
        mov eax,edi
    L_00434159:
        imul eax,42h
    L_0043415c:
        lea edx,[eax+ebp+0E98h]
    L_00434163:
        lea eax,[ebp+edi*4+614h]
    L_0043416a:
        mov dword ptr [esp+18h],edx
    L_0043416e:
        mov dword ptr [esp+30h],eax
    L_00434172:
        cmp edi,dword ptr [ebp+688h]
    L_00434178:
        jge asm_target_004342dd
    L_0043417e:
        mov ecx,dword ptr [ebp+14h]
    L_00434181:
        mov esi,dword ptr [g_sprt_ctrl]
    L_00434187:
        mov dword ptr [esp+14h],ecx
    L_0043418b:
        call asm_FUN_00449950_00449950
    L_00434190:
        mov ecx,dword ptr [esp+14h]
    L_00434194:
        mov ebx,eax
    L_00434196:
        mov eax,dword ptr [ebx+35Ch]
    L_0043419c:
        lea edx,[edi+0ADh]
    L_004341a2:
        push edx
    L_004341a3:
        or eax,40000000h
    L_004341a8:
        push ebx
    L_004341a9:
        mov dword ptr [ebx+20h],0Fh
    L_004341b0:
        mov dword ptr [ebx+35Ch],eax
    L_004341b6:
        call asm_FUN_00449870_00449870
    L_004341bb:
        mov esi,dword ptr [g_sprt_ctrl]
    L_004341c1:
        lea eax,[esp+10h]
    L_004341c5:
        mov edx,esi
    L_004341c7:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_004341cc:
        mov ecx,dword ptr [esp+10h]
    L_004341d0:
        mov eax,dword ptr [esp+30h]
    L_004341d4:
        mov edx,ecx
    L_004341d6:
        push edx
    L_004341d7:
        mov edx,esi
    L_004341d9:
        mov dword ptr [eax],ecx
    L_004341db:
        call asm_AnimationManager_Find_004491c0
    L_004341e0:
        mov ebx,eax
    L_004341e2:
        test ebx,ebx
    L_004341e4:
        jne short L_004341ec
    L_004341e6:
        mov eax,dword ptr [esp+30h]
    L_004341ea:
        mov dword ptr [eax],ebx
    L_004341ec:
        mov ecx,dword ptr [data_0047783c]
    L_004341f2:
        mov al,byte ptr [ecx+edi+1D892h]
    L_004341f9:
        test al,al
    L_004341fb:
        je short L_00434214
    L_004341fd:
        mov edx,dword ptr [esp+18h]
    L_00434201:
        push edx
    L_00434202:
        push 0FFFFFFh
    L_00434207:
        push esi
    L_00434208:
        mov esi,ebx
    L_0043420a:
        call asm_Recovery_MarkLogState_00447a50
    L_0043420f:
        add esp,0Ch
    L_00434212:
        jmp short L_0043422d
    L_00434214:
        lea eax,[edi+1]
    L_00434217:
        push eax
    L_00434218:
        push 46ECF4h
    L_0043421d:
        push 0FFFFFFh
    L_00434222:
        push esi
    L_00434223:
        mov esi,ebx
    L_00434225:
        call asm_Recovery_MarkLogState_00447a50
    L_0043422a:
        add esp,10h
    L_0043422d:
        mov eax,dword ptr [ebp+58D8h]
    L_00434233:
        cmp edi,eax
    L_00434235:
        jl short L_00434249
    L_00434237:
        add eax,0Ah
    L_0043423a:
        cmp edi,eax
    L_0043423c:
        jge short L_00434249
    L_0043423e:
        mov eax,dword ptr [ebx+35Ch]
    L_00434244:
        or eax,2
    L_00434247:
        jmp short L_00434252
    L_00434249:
        mov eax,dword ptr [ebx+35Ch]
    L_0043424f:
        and eax,0FFFFFFFDh
    L_00434252:
        mov dword ptr [ebx+35Ch],eax
    L_00434258:
        cmp edi,dword ptr [ebp+24h]
    L_0043425b:
        jne short L_0043426b
    L_0043425d:
        fld dword ptr [esp+20h]
    L_00434261:
        fsub qword ptr [data_00470c98]
    L_00434267:
        fstp dword ptr [esp+20h]
    L_0043426b:
        push 0
    L_0043426d:
        lea edx,[ebx+334h]
    L_00434273:
        push 4
    L_00434275:
        lea ecx,[esp+28h]
    L_00434279:
        mov eax,ebx
    L_0043427b:
        call asm_StageText_Initialize_00434a80
    L_00434280:
        mov eax,dword ptr [ebp+24h]
    L_00434283:
        cmp edi,eax
    L_00434285:
        jne short L_00434295
    L_00434287:
        fld dword ptr [esp+20h]
    L_0043428b:
        fadd qword ptr [data_00470c98]
    L_00434291:
        fstp dword ptr [esp+20h]
    L_00434295:
        mov edx,dword ptr [esp+18h]
    L_00434299:
        fld dword ptr [esp+24h]
    L_0043429d:
        mov esi,dword ptr [esp+30h]
    L_004342a1:
        fadd dword ptr [data_00470ca0]
    L_004342a7:
        xor ecx,ecx
    L_004342a9:
        cmp edi,eax
    L_004342ab:
        setne cl
    L_004342ae:
        fstp dword ptr [esp+24h]
    L_004342b2:
        add edx,42h
    L_004342b5:
        mov dword ptr [esp+18h],edx
    L_004342b9:
        add esi,4
    L_004342bc:
        mov dword ptr [esp+30h],esi
    L_004342c0:
        add ecx,2
    L_004342c3:
        mov word ptr [ebx+304h],cx
    L_004342ca:
        mov edx,dword ptr [ebp+2B4h]
    L_004342d0:
        inc edi
    L_004342d1:
        shl edx,1
    L_004342d3:
        xor ecx,ecx
    L_004342d5:
        cmp edi,edx
    L_004342d7:
        jl asm_target_00434172
    L_004342dd:
        cmp dword ptr [ebp+2B4h],0Ah
    L_004342e4:
        jl asm_target_004349be
    L_004342ea:
        mov dword ptr [ebp+20h],1
    L_004342f1:
        mov eax,dword ptr [ebp+2C0h]
    L_004342f7:
        test al,1
    L_004342f9:
        jne short L_00434324
    L_004342fb:
        or eax,1
    L_004342fe:
        mov dword ptr [ebp+2B4h],ecx
    L_00434304:
        mov dword ptr [ebp+2B0h],0FFF0BDC1h
    L_0043430e:
        mov dword ptr [ebp+2B8h],ecx
    L_00434314:
        mov dword ptr [ebp+2BCh],476F78h
    L_0043431e:
        mov dword ptr [ebp+2C0h],eax
    L_00434324:
        pop edi
    L_00434325:
        pop esi
    L_00434326:
        pop ebx
    L_00434327:
        mov dword ptr [ebp+2B4h],ecx
    L_0043432d:
        mov dword ptr [ebp+2B8h],ecx
    L_00434333:
        mov dword ptr [ebp+2B0h],0FFFFFFFFh
    L_0043433d:
        xor eax,eax
    L_0043433f:
        pop ebp
    L_00434340:
        add esp,1Ch
    L_00434343:
        ret 4
    L_00434346:
        mov eax,dword ptr [ebp+2B4h]
    L_0043434c:
        and eax,80000001h
    L_00434351:
        jns short L_00434358
    L_00434353:
        dec eax
    L_00434354:
        or eax,0FFFFFFFEh
    L_00434357:
        inc eax
    L_00434358:
        jne asm_target_004343f6
    L_0043435e:
        mov eax,dword ptr [ebp+68Ch]
    L_00434364:
        cmp eax,8
    L_00434367:
        jge asm_target_004343f6
    L_0043436d:
        lea esi,[ebp+eax*4+664h]
    L_00434374:
        call asm_AnimationManager_ValidateHandle_00449450
    L_00434379:
        mov ecx,dword ptr [data_0047783c]
    L_0043437f:
        mov esi,eax
    L_00434381:
        mov eax,dword ptr [ebp+690h]
    L_00434387:
        mov dl,byte ptr [eax+ecx+1D892h]
    L_0043438e:
        test dl,dl
    L_00434390:
        jne short L_004343b8
    L_00434392:
        mov ecx,dword ptr [ebp+694h]
    L_00434398:
        test ecx,ecx
    L_0043439a:
        je short L_004343b8
    L_0043439c:
        mov edx,dword ptr [ebp+68Ch]
    L_004343a2:
        mov eax,dword ptr [edx*4+476FD8h]
    L_004343a9:
        mov ecx,dword ptr [g_sprt_ctrl]
    L_004343af:
        push eax
    L_004343b0:
        push 8080FFh
    L_004343b5:
        push ecx
    L_004343b6:
        jmp short L_004343d8
    L_004343b8:
        mov edx,dword ptr [ebp+68Ch]
    L_004343be:
        lea eax,[edx+eax*8]
    L_004343c1:
        mov edx,dword ptr [g_sprt_ctrl]
    L_004343c7:
        imul eax,42h
    L_004343ca:
        lea ecx,[eax+ebp+16D8h]
    L_004343d1:
        push ecx
    L_004343d2:
        push 0FFFFFFh
    L_004343d7:
        push edx
    L_004343d8:
        call asm_Recovery_MarkLogState_00447a50
    L_004343dd:
        mov word ptr [esi+304h],2
    L_004343e6:
        mov eax,dword ptr [ebp+68Ch]
    L_004343ec:
        add esp,0Ch
    L_004343ef:
        inc eax
    L_004343f0:
        mov dword ptr [ebp+68Ch],eax
    L_004343f6:
        cmp dword ptr [ebp+2B4h],4
    L_004343fd:
        jle asm_target_004349be
    L_00434403:
        mov ecx,2
    L_00434408:
        mov eax,ebp
    L_0043440a:
        call asm_GameState_SetTimerTarget_0042c620
    L_0043440f:
        pop edi
    L_00434410:
        pop esi
    L_00434411:
        pop ebx
    L_00434412:
        xor eax,eax
    L_00434414:
        pop ebp
    L_00434415:
        add esp,1Ch
    L_00434418:
        ret 4
    L_0043441b:
        mov eax,dword ptr [ebp+2B4h]
    L_00434421:
        and eax,80000001h
    L_00434426:
        jns short L_0043442d
    L_00434428:
        dec eax
    L_00434429:
        or eax,0FFFFFFFEh
    L_0043442c:
        inc eax
    L_0043442d:
        jne asm_target_004344cd
    L_00434433:
        mov eax,dword ptr [ebp+68Ch]
    L_00434439:
        cmp eax,8
    L_0043443c:
        jge asm_target_004344cd
    L_00434442:
        lea esi,[ebp+eax*4+664h]
    L_00434449:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0043444e:
        mov ecx,dword ptr [data_0047783c]
    L_00434454:
        mov esi,eax
    L_00434456:
        mov eax,dword ptr [ebp+690h]
    L_0043445c:
        mov dl,byte ptr [eax+ecx+1D892h]
    L_00434463:
        xor ebx,ebx
    L_00434465:
        test dl,dl
    L_00434467:
        jne short L_0043448d
    L_00434469:
        cmp dword ptr [ebp+694h],ebx
    L_0043446f:
        je short L_0043448d
    L_00434471:
        mov edx,dword ptr [ebp+68Ch]
    L_00434477:
        mov eax,dword ptr [edx*4+476FD8h]
    L_0043447e:
        mov ecx,dword ptr [g_sprt_ctrl]
    L_00434484:
        push eax
    L_00434485:
        push 8080FFh
    L_0043448a:
        push ecx
    L_0043448b:
        jmp short L_004344ad
    L_0043448d:
        mov edx,dword ptr [ebp+68Ch]
    L_00434493:
        lea eax,[edx+eax*8]
    L_00434496:
        mov edx,dword ptr [g_sprt_ctrl]
    L_0043449c:
        imul eax,42h
    L_0043449f:
        lea ecx,[eax+ebp+16D8h]
    L_004344a6:
        push ecx
    L_004344a7:
        push 0FFFFFFh
    L_004344ac:
        push edx
    L_004344ad:
        call asm_Recovery_MarkLogState_00447a50
    L_004344b2:
        mov word ptr [esi+304h],2
    L_004344bb:
        mov eax,dword ptr [ebp+68Ch]
    L_004344c1:
        add esp,0Ch
    L_004344c4:
        inc eax
    L_004344c5:
        mov dword ptr [ebp+68Ch],eax
    L_004344cb:
        jmp short L_004344cf
    L_004344cd:
        xor ebx,ebx
    L_004344cf:
        mov eax,dword ptr [ebp+24h]
    L_004344d2:
        lea esi,[ebp+24h]
    L_004344d5:
        mov dword ptr [esi+4],eax
    L_004344d8:
        test byte ptr [data_00474e36],10h
    L_004344df:
        jne short L_004344ea
    L_004344e1:
        test byte ptr [data_00474e34],10h
    L_004344e8:
        je short L_004344f3
    L_004344ea:
        push 0FFFFFFFFh
    L_004344ec:
        mov eax,esi
    L_004344ee:
        call asm_MenuCursor_Advance_0044bea0
    L_004344f3:
        mov cl,byte ptr [data_00474e36]
    L_004344f9:
        mov al,20h
    L_004344fb:
        test cl,al
    L_004344fd:
        jne short L_00434507
    L_004344ff:
        test byte ptr [data_00474e34],al
    L_00434505:
        je short L_00434510
    L_00434507:
        push 1
    L_00434509:
        mov eax,esi
    L_0043450b:
        call asm_MenuCursor_Advance_0044bea0
    L_00434510:
        mov ecx,dword ptr [esi+4]
    L_00434513:
        cmp ecx,dword ptr [esi]
    L_00434515:
        je asm_target_00434673
    L_0043451b:
        push ebx
    L_0043451c:
        mov edi,0Ch
    L_00434521:
        mov ecx,492590h
    L_00434526:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043452b:
        mov ecx,dword ptr [ebp+58D8h]
    L_00434531:
        mov eax,dword ptr [esi]
    L_00434533:
        cmp eax,ecx
    L_00434535:
        jl short L_00434541
    L_00434537:
        add ecx,0Ah
    L_0043453a:
        cmp eax,ecx
    L_0043453c:
        jl short L_00434547
    L_0043453e:
        add eax,0FFFFFFF7h
    L_00434541:
        mov dword ptr [ebp+58D8h],eax
    L_00434547:
        fild dword ptr [ebp+58D8h]
    L_0043454d:
        mov eax,dword ptr [ebp+688h]
    L_00434553:
        xor edi,edi
    L_00434555:
        cmp eax,ebx
    L_00434557:
        fmul dword ptr [data_00470ca0]
    L_0043455d:
        mov dword ptr [esp+20h],42800000h
    L_00434565:
        mov dword ptr [esp+28h],0
    L_0043456d:
        fsubr dword ptr [data_00470c80]
    L_00434573:
        fstp dword ptr [esp+24h]
    L_00434577:
        jle asm_target_00434667
    L_0043457d:
        lea ebx,[ebp+614h]
    L_00434583:
        mov edx,dword ptr [ebx]
    L_00434585:
        push edx
    L_00434586:
        mov edx,dword ptr [g_sprt_ctrl]
    L_0043458c:
        call asm_AnimationManager_Find_004491c0
    L_00434591:
        mov esi,eax
    L_00434593:
        test esi,esi
    L_00434595:
        jne short L_00434599
    L_00434597:
        mov dword ptr [ebx],eax
    L_00434599:
        mov eax,dword ptr [ebp+58D8h]
    L_0043459f:
        cmp edi,eax
    L_004345a1:
        jl short L_004345b5
    L_004345a3:
        add eax,0Ah
    L_004345a6:
        cmp edi,eax
    L_004345a8:
        jge short L_004345b5
    L_004345aa:
        mov eax,dword ptr [esi+35Ch]
    L_004345b0:
        or eax,2
    L_004345b3:
        jmp short L_004345be
    L_004345b5:
        mov eax,dword ptr [esi+35Ch]
    L_004345bb:
        and eax,0FFFFFFFDh
    L_004345be:
        mov dword ptr [esi+35Ch],eax
    L_004345c4:
        cmp edi,dword ptr [ebp+24h]
    L_004345c7:
        jne short L_004345d7
    L_004345c9:
        fld dword ptr [esp+20h]
    L_004345cd:
        fsub qword ptr [data_00470c98]
    L_004345d3:
        fstp dword ptr [esp+20h]
    L_004345d7:
        fld dword ptr [esi+338h]
    L_004345dd:
        fsub dword ptr [esp+24h]
    L_004345e1:
        fabs
    L_004345e3:
        fcomp dword ptr [data_00470c64]
    L_004345e9:
        fnstsw ax
    L_004345eb:
        test ah,5
    L_004345ee:
        jp short L_00434607
    L_004345f0:
        push 0
    L_004345f2:
        lea edx,[esi+334h]
    L_004345f8:
        push 4
    L_004345fa:
        lea ecx,[esp+28h]
    L_004345fe:
        mov eax,esi
    L_00434600:
        call asm_StageText_Initialize_00434a80
    L_00434605:
        jmp short L_00434621
    L_00434607:
        mov ecx,dword ptr [esp+20h]
    L_0043460b:
        mov edx,dword ptr [esp+24h]
    L_0043460f:
        lea eax,[esi+334h]
    L_00434615:
        mov dword ptr [eax],ecx
    L_00434617:
        mov ecx,dword ptr [esp+28h]
    L_0043461b:
        mov dword ptr [eax+4],edx
    L_0043461e:
        mov dword ptr [eax+8],ecx
    L_00434621:
        mov eax,dword ptr [ebp+24h]
    L_00434624:
        cmp edi,eax
    L_00434626:
        jne short L_00434636
    L_00434628:
        fld dword ptr [esp+20h]
    L_0043462c:
        fadd qword ptr [data_00470c98]
    L_00434632:
        fstp dword ptr [esp+20h]
    L_00434636:
        fld dword ptr [esp+24h]
    L_0043463a:
        xor edx,edx
    L_0043463c:
        fadd dword ptr [data_00470ca0]
    L_00434642:
        cmp edi,eax
    L_00434644:
        setne dl
    L_00434647:
        add ebx,4
    L_0043464a:
        fstp dword ptr [esp+24h]
    L_0043464e:
        add edx,2
    L_00434651:
        mov word ptr [esi+304h],dx
    L_00434658:
        mov eax,dword ptr [ebp+688h]
    L_0043465e:
        inc edi
    L_0043465f:
        cmp edi,eax
    L_00434661:
        jl asm_target_00434583
    L_00434667:
        mov dword ptr [ebp+694h],0
    L_00434671:
        xor ebx,ebx
    L_00434673:
        mov eax,dword ptr [data_00474e36]
    L_00434678:
        test eax,1001h
    L_0043467d:
        je asm_target_004347fb
    L_00434683:
        lea esi,[ebp+664h]
    L_00434689:
        mov edi,8
    L_0043468e:
        mov edi,edi
    L_00434690:
        mov eax,dword ptr [esi]
    L_00434692:
        mov edx,dword ptr [g_sprt_ctrl]
    L_00434698:
        push eax
    L_00434699:
        call asm_AnimationManager_Find_004491c0
    L_0043469e:
        cmp eax,ebx
    L_004346a0:
        je short L_004346d0
    L_004346a2:
        cmp dword ptr [eax+18h],ebx
    L_004346a5:
        mov ecx,3
    L_004346aa:
        mov word ptr [eax+304h],cx
    L_004346b1:
        jne short L_004346d0
    L_004346b3:
        mov eax,dword ptr [eax+14h]
    L_004346b6:
        cmp eax,ebx
    L_004346b8:
        je short L_004346d0
    L_004346ba:
        lea ebx,[ebx+force_disp32_zero]
    L_004346c0:
        mov edx,dword ptr [eax]
    L_004346c2:
        mov word ptr [edx+304h],cx
    L_004346c9:
        mov eax,dword ptr [eax+4]
    L_004346cc:
        cmp eax,ebx
    L_004346ce:
        jne short L_004346c0
    L_004346d0:
        add esi,4
    L_004346d3:
        dec edi
    L_004346d4:
        jne short L_00434690
    L_004346d6:
        mov eax,dword ptr [ebp+24h]
    L_004346d9:
        mov dword ptr [ebp+690h],eax
    L_004346df:
        mov dword ptr [ebp+68Ch],ebx
    L_004346e5:
        mov eax,dword ptr [ebp+2C0h]
    L_004346eb:
        test al,1
    L_004346ed:
        jne short L_00434718
    L_004346ef:
        or eax,1
    L_004346f2:
        mov dword ptr [ebp+2B4h],ebx
    L_004346f8:
        mov dword ptr [ebp+2B0h],0FFF0BDC1h
    L_00434702:
        mov dword ptr [ebp+2B8h],ebx
    L_00434708:
        mov dword ptr [ebp+2BCh],476F78h
    L_00434712:
        mov dword ptr [ebp+2C0h],eax
    L_00434718:
        mov edx,dword ptr [data_0047783c]
    L_0043471e:
        mov dword ptr [ebp+2B4h],ebx
    L_00434724:
        mov dword ptr [ebp+2B8h],ebx
    L_0043472a:
        mov dword ptr [ebp+2B0h],0FFFFFFFFh
    L_00434734:
        mov ecx,dword ptr [ebp+690h]
    L_0043473a:
        mov al,byte ptr [ecx+edx+1D892h]
    L_00434741:
        test al,al
    L_00434743:
        jne short L_0043479b
    L_00434745:
        cmp dword ptr [ebp+694h],ebx
    L_0043474b:
        jne short L_0043479b
    L_0043474d:
        test byte ptr [data_00491d78],10h
    L_00434754:
        mov edx,46DF98h
    L_00434759:
        push ebx
    L_0043475a:
        mov eax,492590h
    L_0043475f:
        je short L_0043477e
    L_00434761:
        push 4
    L_00434763:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00434768:
        pop edi
    L_00434769:
        pop esi
    L_0043476a:
        pop ebx
    L_0043476b:
        mov dword ptr [ebp+694h],1
    L_00434775:
        xor eax,eax
    L_00434777:
        pop ebp
    L_00434778:
        add esp,1Ch
    L_0043477b:
        ret 4
    L_0043477e:
        push 3
    L_00434780:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00434785:
        pop edi
    L_00434786:
        pop esi
    L_00434787:
        pop ebx
    L_00434788:
        mov dword ptr [ebp+694h],1
    L_00434792:
        xor eax,eax
    L_00434794:
        pop ebp
    L_00434795:
        add esp,1Ch
    L_00434798:
        ret 4
    L_0043479b:
        mov eax,dword ptr [ebp+24h]
    L_0043479e:
        shl eax,6
    L_004347a1:
        lea ecx,[eax+ebp+698h]
    L_004347a8:
        push ecx
    L_004347a9:
        push ebx
    L_004347aa:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_004347af:
        test byte ptr [data_00491d78],10h
    L_004347b6:
        je short L_004347ca
    L_004347b8:
        push ebx
    L_004347b9:
        push 4
    L_004347bb:
        mov edx,46DF98h
    L_004347c0:
        mov eax,492590h
    L_004347c5:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004347ca:
        push ebx
    L_004347cb:
        push 2
    L_004347cd:
        mov edx,46DF98h
    L_004347d2:
        mov eax,492590h
    L_004347d7:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004347dc:
        mov edx,dword ptr [data_0047783c]
    L_004347e2:
        pop edi
    L_004347e3:
        pop esi
    L_004347e4:
        mov byte ptr [edx+1D892h],1
    L_004347eb:
        mov dword ptr [ebp+694h],ebx
    L_004347f1:
        pop ebx
    L_004347f2:
        xor eax,eax
    L_004347f4:
        pop ebp
    L_004347f5:
        add esp,1Ch
    L_004347f8:
        ret 4
    L_004347fb:
        test al,0Ah
    L_004347fd:
        je asm_target_004349be
    L_00434803:
        mov eax,dword ptr [ebp+5AACh]
    L_00434809:
        xor ebx,ebx
    L_0043480b:
        cmp eax,ebx
    L_0043480d:
        je short L_0043481e
    L_0043480f:
        push eax
    L_00434810:
        call asm_free_00452422
    L_00434815:
        add esp,4
    L_00434818:
        mov dword ptr [ebp+5AACh],ebx
    L_0043481e:
        lea eax,[ebp+24h]
    L_00434821:
        mov dword ptr [ebp+5AACh],ebx
    L_00434827:
        call asm_Score_InputHistoryStep_0044be70
    L_0043482c:
        mov eax,dword ptr [ebp+688h]
    L_00434832:
        xor esi,esi
    L_00434834:
        cmp eax,ebx
    L_00434836:
        jle short L_00434855
    L_00434838:
        lea edi,[ebp+614h]
    L_0043483e:
        mov edi,edi
    L_00434840:
        mov eax,edi
    L_00434842:
        call asm_FUN_00409e50_00409e50
    L_00434847:
        mov eax,dword ptr [ebp+688h]
    L_0043484d:
        inc esi
    L_0043484e:
        add edi,4
    L_00434851:
        cmp esi,eax
    L_00434853:
        jl short L_00434840
    L_00434855:
        mov esi,dword ptr [g_sprt_ctrl]
    L_0043485b:
        lea edx,[ebp+664h]
    L_00434861:
        mov dword ptr [esp+30h],8
    L_00434869:
        lea esp,[esp+force_disp32_zero]
    L_00434870:
        mov ecx,dword ptr [edx]
    L_00434872:
        cmp ecx,ebx
    L_00434874:
        je short L_004348d4
    L_00434876:
        mov eax,dword ptr [esi+72DAD4h]
    L_0043487c:
        cmp eax,ebx
    L_0043487e:
        je short L_0043488d
    L_00434880:
        mov edi,dword ptr [eax]
    L_00434882:
        cmp dword ptr [edi],ecx
    L_00434884:
        je short L_004348a6
    L_00434886:
        mov eax,dword ptr [eax+4]
    L_00434889:
        cmp eax,ebx
    L_0043488b:
        jne short L_00434880
    L_0043488d:
        mov eax,dword ptr [esi+72DADCh]
    L_00434893:
        cmp eax,ebx
    L_00434895:
        je short L_004348d4
    L_00434897:
        mov edi,dword ptr [eax]
    L_00434899:
        cmp dword ptr [edi],ecx
    L_0043489b:
        je short L_004348a6
    L_0043489d:
        mov eax,dword ptr [eax+4]
    L_004348a0:
        cmp eax,ebx
    L_004348a2:
        jne short L_00434897
    L_004348a4:
        jmp short L_004348d4
    L_004348a6:
        mov eax,dword ptr [eax]
    L_004348a8:
        cmp eax,ebx
    L_004348aa:
        je short L_004348d4
    L_004348ac:
        cmp dword ptr [eax+18h],ebx
    L_004348af:
        mov ecx,1
    L_004348b4:
        mov word ptr [eax+304h],cx
    L_004348bb:
        jne short L_004348d4
    L_004348bd:
        mov eax,dword ptr [eax+14h]
    L_004348c0:
        cmp eax,ebx
    L_004348c2:
        je short L_004348d4
    L_004348c4:
        mov edi,dword ptr [eax]
    L_004348c6:
        mov word ptr [edi+304h],cx
    L_004348cd:
        mov eax,dword ptr [eax+4]
    L_004348d0:
        cmp eax,ebx
    L_004348d2:
        jne short L_004348c4
    L_004348d4:
        mov eax,dword ptr [esp+30h]
    L_004348d8:
        add edx,4
    L_004348db:
        dec eax
    L_004348dc:
        mov dword ptr [esp+30h],eax
    L_004348e0:
        jne short L_00434870
    L_004348e2:
        push ebx
    L_004348e3:
        mov edi,0Bh
    L_004348e8:
        mov ecx,492590h
    L_004348ed:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004348f2:
        mov dword ptr [ebp+20h],3
    L_004348f9:
        mov eax,dword ptr [ebp+2C0h]
    L_004348ff:
        test al,1
    L_00434901:
        jne short L_0043492c
    L_00434903:
        or eax,1
    L_00434906:
        mov dword ptr [ebp+2B4h],ebx
    L_0043490c:
        mov dword ptr [ebp+2B0h],0FFF0BDC1h
    L_00434916:
        mov dword ptr [ebp+2B8h],ebx
    L_0043491c:
        mov dword ptr [ebp+2BCh],476F78h
    L_00434926:
        mov dword ptr [ebp+2C0h],eax
    L_0043492c:
        pop edi
    L_0043492d:
        pop esi
    L_0043492e:
        mov dword ptr [ebp+2B4h],ebx
    L_00434934:
        mov dword ptr [ebp+2B8h],ebx
    L_0043493a:
        pop ebx
    L_0043493b:
        mov dword ptr [ebp+2B0h],0FFFFFFFFh
    L_00434945:
        xor eax,eax
    L_00434947:
        pop ebp
    L_00434948:
        add esp,1Ch
    L_0043494b:
        ret 4
    L_0043494e:
        cmp dword ptr [ebp+2B4h],0Ah
    L_00434955:
        jl short L_004349be
    L_00434957:
        mov esi,67h
    L_0043495c:
        mov edi,ebp
    L_0043495e:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00434963:
        mov esi,8
    L_00434968:
        mov ecx,5Ah
    L_0043496d:
        mov eax,ebp
    L_0043496f:
        call asm_FUN_0042c770_0042c770
    L_00434974:
        mov ecx,5Bh
    L_00434979:
        mov eax,ebp
    L_0043497b:
        call asm_FUN_0042c770_0042c770
    L_00434980:
        mov esi,5Fh
    L_00434985:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043498a:
        lea eax,[ebp+5D0h]
    L_00434990:
        call asm_FUN_00409e50_00409e50
    L_00434995:
        mov ecx,2
    L_0043499a:
        mov eax,ebp
    L_0043499c:
        call asm_Title_DisableTimerWithOwner
    L_004349a1:
        push 46F018h
    L_004349a6:
        push 0
    L_004349a8:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_004349ad:
        push 0
    L_004349af:
        push 0
    L_004349b1:
        call asm_Sound_PlayDummyRetail_00420b10
    L_004349b6:
        lea eax,[ebp+24h]
    L_004349b9:
        call asm_Score_InputHistoryStep_0044be70
    L_004349be:
        pop edi
    L_004349bf:
        pop esi
    L_004349c0:
        pop ebx
    L_004349c1:
        xor eax,eax
    L_004349c3:
        pop ebp
    L_004349c4:
        add esp,1Ch
    L_004349c7:
        ret 4
        _emit 0x8b
        _emit 0xff
        _emit 0x0e
        _emit 0x3f
        _emit 0x43
        _emit 0x00
        _emit 0x46
        _emit 0x43
        _emit 0x43
        _emit 0x00
        _emit 0x1b
        _emit 0x44
        _emit 0x43
        _emit 0x00
        _emit 0x4e
        _emit 0x49
        _emit 0x43
        _emit 0x00
    }
}

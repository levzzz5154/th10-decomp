// BLOCKED (D3804): live Ghidra confirms this entry consumes mode in EAX, path
// in ECX, and its runtime receiver in EBX. The ordinary __fastcall(char*) view
// omits EAX and EBX, while the sole direct caller sets all three registers in
// assembly. This ABI cannot be expressed as a plain MSVC C++ function; the
// replay/config records and scheduler task nodes also lack production types.
// See matching2/reference/recovery_notes/replay_runtime_bootstrap_00428f60.md
// for branch behavior, helper evidence, and alias integration. Keep the
// retail body until a caller-inclusive native-LTCG bridge can supply these
// dependencies without changing the entry protocol.
#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"

// 0x00428F60..0x0042949F: FUN_00428f60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00428f60_00428f60() {
    __asm {
    L_00428f60:
        push ebp
    L_00428f61:
        xor ebp,ebp
    L_00428f63:
        cmp eax,ebp
    L_00428f65:
        push esi
    L_00428f66:
        push edi
    L_00428f67:
        mov dword ptr [ebx+10h],eax
    L_00428f6a:
        jne asm_target_00429245
    L_00428f70:
        mov eax,dword ptr [g_globals_stage]
    L_00428f75:
        mov ecx,ebx
    L_00428f77:
        mov dword ptr [g_replay],ebx
    L_00428f7d:
        call asm_FUN_0042ab20_0042ab20
    L_00428f82:
        mov esi,dword ptr [g_globals_stage]
    L_00428f88:
        push ebx
    L_00428f89:
        call asm_LinkedPool_AllocateAndAppendRetail_0042aa50
    L_00428f8e:
        push 24h
    L_00428f90:
        mov dword ptr [ebx+9Ch],eax
    L_00428f96:
        call asm_operator_new_00452493
    L_00428f9b:
        add esp,4
    L_00428f9e:
        cmp eax,ebp
    L_00428fa0:
        je short L_00428fd5
    L_00428fa2:
        xor ecx,ecx
    L_00428fa4:
        mov edx,eax
    L_00428fa6:
        mov dword ptr [edx],ecx
    L_00428fa8:
        mov dword ptr [edx+4],ecx
    L_00428fab:
        mov dword ptr [edx+8],ecx
    L_00428fae:
        mov dword ptr [edx+0Ch],ecx
    L_00428fb1:
        mov dword ptr [edx+10h],ecx
    L_00428fb4:
        mov dword ptr [edx+14h],ecx
    L_00428fb7:
        mov dword ptr [edx+18h],ecx
    L_00428fba:
        mov dword ptr [edx+1Ch],ecx
    L_00428fbd:
        mov dword ptr [edx+20h],ecx
    L_00428fc0:
        mov dword ptr [eax],72303174h
    L_00428fc6:
        mov word ptr [eax+4],5
    L_00428fcc:
        mov dword ptr [eax+10h],100h
    L_00428fd3:
        jmp short L_00428fd7
    L_00428fd5:
        xor eax,eax
    L_00428fd7:
        push 64h
    L_00428fd9:
        mov dword ptr [ebx+14h],eax
    L_00428fdc:
        call asm_operator_new_00452493
    L_00428fe1:
        mov esi,eax
    L_00428fe3:
        add esp,4
    L_00428fe6:
        cmp esi,ebp
    L_00428fe8:
        je short L_00428fff
    L_00428fea:
        lea edx,[esi+14h]
    L_00428fed:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00428ff2:
        mov ecx,19h
    L_00428ff7:
        xor eax,eax
    L_00428ff9:
        mov edi,esi
    L_00428ffb:
        rep stosd
    L_00428ffd:
        jmp short L_00429001
    L_00428fff:
        xor esi,esi
    L_00429001:
        push 1C4h
    L_00429006:
        mov dword ptr [ebx+18h],esi
    L_00429009:
        call asm_operator_new_00452493
    L_0042900e:
        mov edx,eax
    L_00429010:
        add esp,4
    L_00429013:
        cmp edx,ebp
    L_00429015:
        je short L_00429024
    L_00429017:
        mov ecx,71h
    L_0042901c:
        xor eax,eax
    L_0042901e:
        mov edi,edx
    L_00429020:
        rep stosd
    L_00429022:
        jmp short L_00429026
    L_00429024:
        xor edx,edx
    L_00429026:
        mov eax,dword ptr [g_globals_stage]
    L_0042902b:
        mov dword ptr [ebx+eax*4+1Ch],edx
    L_0042902f:
        mov ecx,dword ptr [g_globals_stage]
    L_00429035:
        mov eax,dword ptr [ebx+ecx*4+1Ch]
    L_00429039:
        mov edx,dword ptr [ebx+18h]
    L_0042903c:
        mov ecx,dword ptr [g_globals_character]
    L_00429042:
        mov dword ptr [edx+50h],ecx
    L_00429045:
        mov edx,dword ptr [ebx+18h]
    L_00429048:
        mov ecx,dword ptr [g_globals_shot_type]
    L_0042904e:
        mov dword ptr [edx+54h],ecx
    L_00429051:
        mov ecx,dword ptr [g_globals_difficulty]
    L_00429057:
        mov edx,dword ptr [ebx+18h]
    L_0042905a:
        mov dword ptr [edx+58h],ecx
    L_0042905d:
        mov ecx,dword ptr [g_game]
    L_00429063:
        cmp ecx,ebp
    L_00429065:
        je short L_00429077
    L_00429067:
        mov edi,dword ptr [ebx+18h]
    L_0042906a:
        lea esi,[ecx+24h]
    L_0042906d:
        add edi,14h
    L_00429070:
        mov ecx,0Dh
    L_00429075:
        rep movsd
    L_00429077:
        mov dx,word ptr [g_globals_stage]
    L_0042907e:
        mov word ptr [eax],dx
    L_00429081:
        mov cx,word ptr [g_rng]
    L_00429088:
        mov word ptr [eax+2],cx
    L_0042908c:
        mov ecx,dword ptr [g_stage_flags]
    L_00429092:
        mov dword ptr [g_rng_generation],ebp
    L_00429098:
        mov edx,dword ptr [eax+1C0h]
    L_0042909e:
        mov esi,dword ptr [eax+1C0h]
    L_004290a4:
        xor edx,ecx
    L_004290a6:
        and edx,1
    L_004290a9:
        xor esi,edx
    L_004290ab:
        mov dword ptr [eax+1C0h],esi
    L_004290b1:
        cmp dword ptr [g_stage_flags],ebp
    L_004290b7:
        je short L_004290bf
    L_004290b9:
        mov dword ptr [eax+24h],ebp
    L_004290bc:
        mov dword ptr [eax+28h],ebp
    L_004290bf:
        mov ecx,dword ptr [g_globals_score]
    L_004290c5:
        mov dword ptr [eax+0Ch],ecx
    L_004290c8:
        mov dx,word ptr [g_globals_power]
    L_004290cf:
        mov word ptr [eax+10h],dx
    L_004290d3:
        mov ecx,dword ptr [g_globals_gauge]
    L_004290d9:
        mov dword ptr [eax+14h],ecx
    L_004290dc:
        mov edx,dword ptr [g_player_power_display]
    L_004290e2:
        mov dword ptr [eax+18h],edx
    L_004290e5:
        mov ecx,dword ptr [g_globals_lives]
    L_004290eb:
        mov dword ptr [eax+1Ch],ecx
    L_004290ee:
        mov edx,dword ptr [g_rank]
    L_004290f4:
        mov dword ptr [eax+20h],edx
    L_004290f7:
        mov ecx,dword ptr [g_globals_continues]
    L_004290fd:
        mov dword ptr [eax+1B4h],ecx
    L_00429103:
        mov edx,dword ptr [ebx+18h]
    L_00429106:
        mov eax,dword ptr [g_globals_continues]
    L_0042910b:
        push 24h
    L_0042910d:
        mov dword ptr [edx+60h],eax
    L_00429110:
        call asm_operator_new_00452493
    L_00429115:
        add esp,4
    L_00429118:
        cmp eax,ebp
    L_0042911a:
        je short L_0042913d
    L_0042911c:
        mov ecx,dword ptr [eax+4]
    L_0042911f:
        mov dword ptr [eax+8],ebp
    L_00429122:
        mov dword ptr [eax+0Ch],ebp
    L_00429125:
        mov dword ptr [eax+10h],ebp
    L_00429128:
        mov dword ptr [eax],ebp
    L_0042912a:
        and ecx,0FFFFFFFEh
    L_0042912d:
        mov dword ptr [eax+4],ecx
    L_00429130:
        mov dword ptr [eax+14h],eax
    L_00429133:
        mov dword ptr [eax+18h],ebp
    L_00429136:
        mov dword ptr [eax+1Ch],ebp
    L_00429139:
        mov esi,eax
    L_0042913b:
        jmp short L_0042913f
    L_0042913d:
        xor esi,esi
    L_0042913f:
        mov ecx,dword ptr [esi+4]
    L_00429142:
        mov edx,dword ptr [g_func_ctrl]
    L_00429148:
        and ecx,0FFFFFFFDh
    L_0042914b:
        or ecx,1
    L_0042914e:
        push edx
    L_0042914f:
        mov edi,0Bh
    L_00429154:
        mov dword ptr [esi+8],42A3D0h
    L_0042915b:
        mov dword ptr [esi+0Ch],ebp
    L_0042915e:
        mov dword ptr [esi+10h],ebp
    L_00429161:
        mov dword ptr [esi+20h],ebx
    L_00429164:
        mov dword ptr [esi+4],ecx
    L_00429167:
        call asm_FuncCtrl_RegisterPrimary_00449ae0
    L_0042916c:
        push 24h
    L_0042916e:
        mov dword ptr [ebx+8],esi
    L_00429171:
        call asm_operator_new_00452493
    L_00429176:
        add esp,4
    L_00429179:
        cmp eax,ebp
    L_0042917b:
        je short L_0042919e
    L_0042917d:
        mov ecx,dword ptr [eax+4]
    L_00429180:
        mov dword ptr [eax+8],ebp
    L_00429183:
        mov dword ptr [eax+0Ch],ebp
    L_00429186:
        mov dword ptr [eax+10h],ebp
    L_00429189:
        mov dword ptr [eax],ebp
    L_0042918b:
        and ecx,0FFFFFFFEh
    L_0042918e:
        mov dword ptr [eax+4],ecx
    L_00429191:
        mov dword ptr [eax+14h],eax
    L_00429194:
        mov dword ptr [eax+18h],ebp
    L_00429197:
        mov dword ptr [eax+1Ch],ebp
    L_0042919a:
        mov esi,eax
    L_0042919c:
        jmp short L_004291a0
    L_0042919e:
        xor esi,esi
    L_004291a0:
        mov eax,dword ptr [esi+4]
    L_004291a3:
        mov ecx,dword ptr [g_func_ctrl]
    L_004291a9:
        and eax,0FFFFFFFDh
    L_004291ac:
        or eax,1
    L_004291af:
        push ecx
    L_004291b0:
        mov edi,1Bh
    L_004291b5:
        mov dword ptr [esi+8],42A3E0h
    L_004291bc:
        mov dword ptr [esi+0Ch],ebp
    L_004291bf:
        mov dword ptr [esi+10h],ebp
    L_004291c2:
        mov dword ptr [esi+20h],ebx
    L_004291c5:
        mov dword ptr [esi+4],eax
    L_004291c8:
        call asm_FuncCtrl_RegisterPrimary_00449ae0
    L_004291cd:
        push 24h
    L_004291cf:
        mov dword ptr [ebx+1CCh],esi
    L_004291d5:
        call asm_operator_new_00452493
    L_004291da:
        add esp,4
    L_004291dd:
        cmp eax,ebp
    L_004291df:
        je short L_00429202
    L_004291e1:
        mov ecx,dword ptr [eax+4]
    L_004291e4:
        mov dword ptr [eax+8],ebp
    L_004291e7:
        mov dword ptr [eax+0Ch],ebp
    L_004291ea:
        mov dword ptr [eax+10h],ebp
    L_004291ed:
        mov dword ptr [eax],ebp
    L_004291ef:
        and ecx,0FFFFFFFEh
    L_004291f2:
        mov dword ptr [eax+4],ecx
    L_004291f5:
        mov dword ptr [eax+14h],eax
    L_004291f8:
        mov dword ptr [eax+18h],ebp
    L_004291fb:
        mov dword ptr [eax+1Ch],ebp
    L_004291fe:
        mov esi,eax
    L_00429200:
        jmp short L_00429204
    L_00429202:
        xor esi,esi
    L_00429204:
        mov edx,dword ptr [esi+4]
    L_00429207:
        mov eax,dword ptr [g_func_ctrl]
    L_0042920c:
        and edx,0FFFFFFFDh
    L_0042920f:
        or edx,1
    L_00429212:
        push eax
    L_00429213:
        mov edi,5
    L_00429218:
        mov dword ptr [esi+8],42A430h
    L_0042921f:
        mov dword ptr [esi+0Ch],ebp
    L_00429222:
        mov dword ptr [esi+10h],ebp
    L_00429225:
        mov dword ptr [esi+20h],ebx
    L_00429228:
        mov dword ptr [esi+4],edx
    L_0042922b:
        call asm_FuncCtrl_RegisterSecondary_00449b70
    L_00429230:
        mov dword ptr [ebx+0Ch],esi
    L_00429233:
        mov ecx,dword ptr [g_globals_stage]
    L_00429239:
        mov dword ptr [ebx+1D0h],ecx
    L_0042923f:
        pop edi
    L_00429240:
        pop esi
    L_00429241:
        xor eax,eax
    L_00429243:
        pop ebp
    L_00429244:
        ret
    L_00429245:
        cmp eax,1
    L_00429248:
        jne asm_target_00429480
    L_0042924e:
        push ecx
    L_0042924f:
        mov esi,ebx
    L_00429251:
        mov dword ptr [g_replay],ebx
    L_00429257:
        call asm_FUN_0042a200_0042a200
    L_0042925c:
        test eax,eax
    L_0042925e:
        jne asm_target_00429499
    L_00429264:
        mov esi,dword ptr [ebx+18h]
    L_00429267:
        mov edi,dword ptr [g_game]
    L_0042926d:
        add esi,14h
    L_00429270:
        add edi,24h
    L_00429273:
        mov ecx,0Dh
    L_00429278:
        rep movsd
    L_0042927a:
        mov eax,dword ptr [g_globals_stage]
    L_0042927f:
        lea edx,[eax+eax*8]
    L_00429282:
        mov ecx,dword ptr [ebx+edx*4+0A0h]
    L_00429289:
        mov esi,dword ptr [ebx+edx*4+0B0h]
    L_00429290:
        mov dword ptr [ebx+edx*4+0A4h],ecx
    L_00429297:
        mov dword ptr [ebx+edx*4+0B4h],ebp
    L_0042929e:
        lea eax,[ebx+edx*4+0A0h]
    L_004292a5:
        mov edx,dword ptr [eax+8]
    L_004292a8:
        mov dword ptr [eax+0Ch],edx
    L_004292ab:
        mov eax,dword ptr [ebx+18h]
    L_004292ae:
        mov ecx,dword ptr [eax+50h]
    L_004292b1:
        mov dword ptr [g_globals_character],ecx
    L_004292b7:
        mov edx,dword ptr [ebx+18h]
    L_004292ba:
        mov eax,dword ptr [edx+54h]
    L_004292bd:
        mov dword ptr [g_globals_shot_type],eax
    L_004292c2:
        mov ecx,dword ptr [ebx+18h]
    L_004292c5:
        mov edx,dword ptr [ecx+58h]
    L_004292c8:
        mov dword ptr [g_globals_difficulty],edx
    L_004292ce:
        mov ax,word ptr [esi+2]
    L_004292d2:
        mov word ptr [g_rng],ax
    L_004292d8:
        mov dword ptr [g_rng_generation],ebp
    L_004292de:
        mov ecx,dword ptr [esi+0Ch]
    L_004292e1:
        mov dword ptr [g_globals_score],ecx
    L_004292e7:
        mov dx,word ptr [esi+10h]
    L_004292eb:
        mov word ptr [g_globals_power],dx
    L_004292f2:
        mov eax,dword ptr [esi+14h]
    L_004292f5:
        lea eax,[eax+eax*4]
    L_004292f8:
        shl eax,1
    L_004292fa:
        push eax
    L_004292fb:
        mov ecx,474C40h
    L_00429300:
        call asm_ScoreGauge_SetTargetTenthAndDisableTimer_00418b80
    L_00429305:
        mov ecx,dword ptr [esi+18h]
    L_00429308:
        push ecx
    L_00429309:
        mov eax,474C40h
    L_0042930e:
        call asm_EmbeddedTimer_SetCountdownRetail_0042a930
    L_00429313:
        mov edx,dword ptr [esi+1Ch]
    L_00429316:
        mov dword ptr [g_globals_lives],edx
    L_0042931c:
        mov eax,dword ptr [esi+20h]
    L_0042931f:
        mov dword ptr [g_rank],eax
    L_00429324:
        mov ecx,dword ptr [esi+1B4h]
    L_0042932a:
        mov eax,dword ptr [g_globals_stage]
    L_0042932f:
        mov dword ptr [g_globals_continues],ecx
    L_00429335:
        lea edx,[eax+eax*8]
    L_00429338:
        mov eax,dword ptr [ebx+edx*4+0B0h]
    L_0042933f:
        mov ecx,dword ptr [eax+1B8h]
    L_00429345:
        push 24h
    L_00429347:
        mov dword ptr [data_00474c9c],ecx
    L_0042934d:
        call asm_operator_new_00452493
    L_00429352:
        add esp,4
    L_00429355:
        cmp eax,ebp
    L_00429357:
        je short L_0042937a
    L_00429359:
        mov ecx,dword ptr [eax+4]
    L_0042935c:
        mov dword ptr [eax+8],ebp
    L_0042935f:
        mov dword ptr [eax+0Ch],ebp
    L_00429362:
        mov dword ptr [eax+10h],ebp
    L_00429365:
        mov dword ptr [eax],ebp
    L_00429367:
        and ecx,0FFFFFFFEh
    L_0042936a:
        mov dword ptr [eax+4],ecx
    L_0042936d:
        mov dword ptr [eax+14h],eax
    L_00429370:
        mov dword ptr [eax+18h],ebp
    L_00429373:
        mov dword ptr [eax+1Ch],ebp
    L_00429376:
        mov esi,eax
    L_00429378:
        jmp short L_0042937c
    L_0042937a:
        xor esi,esi
    L_0042937c:
        mov edx,dword ptr [esi+4]
    L_0042937f:
        mov eax,dword ptr [g_func_ctrl]
    L_00429384:
        and edx,0FFFFFFFDh
    L_00429387:
        or edx,1
    L_0042938a:
        push eax
    L_0042938b:
        mov edi,0Bh
    L_00429390:
        mov dword ptr [esi+8],42A3D0h
    L_00429397:
        mov dword ptr [esi+0Ch],ebp
    L_0042939a:
        mov dword ptr [esi+10h],ebp
    L_0042939d:
        mov dword ptr [esi+20h],ebx
    L_004293a0:
        mov dword ptr [esi+4],edx
    L_004293a3:
        call asm_FuncCtrl_RegisterPrimary_00449ae0
    L_004293a8:
        push 24h
    L_004293aa:
        mov dword ptr [ebx+8],esi
    L_004293ad:
        call asm_operator_new_00452493
    L_004293b2:
        add esp,4
    L_004293b5:
        cmp eax,ebp
    L_004293b7:
        je short L_004293da
    L_004293b9:
        mov ecx,dword ptr [eax+4]
    L_004293bc:
        mov dword ptr [eax+8],ebp
    L_004293bf:
        mov dword ptr [eax+0Ch],ebp
    L_004293c2:
        mov dword ptr [eax+10h],ebp
    L_004293c5:
        mov dword ptr [eax],ebp
    L_004293c7:
        and ecx,0FFFFFFFEh
    L_004293ca:
        mov dword ptr [eax+4],ecx
    L_004293cd:
        mov dword ptr [eax+14h],eax
    L_004293d0:
        mov dword ptr [eax+18h],ebp
    L_004293d3:
        mov dword ptr [eax+1Ch],ebp
    L_004293d6:
        mov esi,eax
    L_004293d8:
        jmp short L_004293dc
    L_004293da:
        xor esi,esi
    L_004293dc:
        mov ecx,dword ptr [esi+4]
    L_004293df:
        mov edx,dword ptr [g_func_ctrl]
    L_004293e5:
        and ecx,0FFFFFFFDh
    L_004293e8:
        or ecx,1
    L_004293eb:
        push edx
    L_004293ec:
        mov edi,1Bh
    L_004293f1:
        mov dword ptr [esi+8],42A3E0h
    L_004293f8:
        mov dword ptr [esi+0Ch],ebp
    L_004293fb:
        mov dword ptr [esi+10h],ebp
    L_004293fe:
        mov dword ptr [esi+20h],ebx
    L_00429401:
        mov dword ptr [esi+4],ecx
    L_00429404:
        call asm_FuncCtrl_RegisterPrimary_00449ae0
    L_00429409:
        push 24h
    L_0042940b:
        mov dword ptr [ebx+1CCh],esi
    L_00429411:
        call asm_operator_new_00452493
    L_00429416:
        add esp,4
    L_00429419:
        cmp eax,ebp
    L_0042941b:
        je short L_0042943e
    L_0042941d:
        mov ecx,dword ptr [eax+4]
    L_00429420:
        mov dword ptr [eax+8],ebp
    L_00429423:
        mov dword ptr [eax+0Ch],ebp
    L_00429426:
        mov dword ptr [eax+10h],ebp
    L_00429429:
        mov dword ptr [eax],ebp
    L_0042942b:
        and ecx,0FFFFFFFEh
    L_0042942e:
        mov dword ptr [eax+4],ecx
    L_00429431:
        mov dword ptr [eax+14h],eax
    L_00429434:
        mov dword ptr [eax+18h],ebp
    L_00429437:
        mov dword ptr [eax+1Ch],ebp
    L_0042943a:
        mov esi,eax
    L_0042943c:
        jmp short L_00429440
    L_0042943e:
        xor esi,esi
    L_00429440:
        mov eax,dword ptr [esi+4]
    L_00429443:
        mov ecx,dword ptr [g_func_ctrl]
    L_00429449:
        and eax,0FFFFFFFDh
    L_0042944c:
        or eax,1
    L_0042944f:
        push ecx
    L_00429450:
        mov edi,5
    L_00429455:
        mov dword ptr [esi+8],42A430h
    L_0042945c:
        mov dword ptr [esi+0Ch],ebp
    L_0042945f:
        mov dword ptr [esi+10h],ebp
    L_00429462:
        mov dword ptr [esi+20h],ebx
    L_00429465:
        mov dword ptr [esi+4],eax
    L_00429468:
        call asm_FuncCtrl_RegisterSecondary_00449b70
    L_0042946d:
        pop edi
    L_0042946e:
        mov dword ptr [ebx+0Ch],esi
    L_00429471:
        pop esi
    L_00429472:
        mov dword ptr [ebx+1D0h],0FFFFFFFFh
    L_0042947c:
        xor eax,eax
    L_0042947e:
        pop ebp
    L_0042947f:
        ret
    L_00429480:
        cmp eax,2
    L_00429483:
        jne asm_target_0042923f
    L_00429489:
        push ecx
    L_0042948a:
        mov esi,ebx
    L_0042948c:
        call asm_FUN_0042a200_0042a200
    L_00429491:
        test eax,eax
    L_00429493:
        je asm_target_0042923f
    L_00429499:
        pop edi
    L_0042949a:
        pop esi
    L_0042949b:
        or eax,0FFFFFFFFh
    L_0042949e:
        pop ebp
    L_0042949f:
        ret
    }
}

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EclVm_StartChildRetail_0044df70() {
    __asm {
    L_0044df70:
        sub esp,10h
    L_0044df73:
        mov edx,dword ptr [esp+18h]
    L_0044df77:
        push ebx
    L_0044df78:
        push ebp
    L_0044df79:
        push esi
    L_0044df7a:
        push edi
    L_0044df7b:
        mov edi,dword ptr [esp+24h]
    L_0044df7f:
        add edi,4
    L_0044df82:
        mov esi,eax
    L_0044df84:
        mov eax,dword ptr [edi]
    L_0044df86:
        mov ecx,dword ptr [eax+10h]
    L_0044df89:
        mov eax,dword ptr [esi+1008h]
    L_0044df8f:
        lea ebp,[ecx+edx*4+4]
    L_0044df93:
        xor edx,edx
    L_0044df95:
        test eax,eax
    L_0044df97:
        mov dword ptr [esp+14h],edx
    L_0044df9b:
        mov dword ptr [esp+1Ch],eax
    L_0044df9f:
        lea ecx,[eax+8]
    L_0044dfa2:
        jne short L_0044dfc1
    L_0044dfa4:
        mov ecx,eax
    L_0044dfa6:
        lea ebx,[ecx+4]
    L_0044dfa9:
        cmp ebx,1000h
    L_0044dfaf:
        jge short L_0044dfbc
    L_0044dfb1:
        mov dword ptr [ecx+esi+8],edx
    L_0044dfb5:
        add dword ptr [esi+1008h],4
    L_0044dfbc:
        mov ecx,0Ch
    L_0044dfc1:
        mov edx,dword ptr [edi]
    L_0044dfc3:
        mov ebx,dword ptr [esp+28h]
    L_0044dfc7:
        movzx edx,byte ptr [edx+0Bh]
    L_0044dfcb:
        inc ebx
    L_0044dfcc:
        cmp ebx,edx
    L_0044dfce:
        jge asm_target_0044e08e
    L_0044dfd4:
        lea eax,[ecx+esi+8]
    L_0044dfd8:
        mov dword ptr [esp+28h],eax
    L_0044dfdc:
        lea eax,[ebp+4]
    L_0044dfdf:
        mov dword ptr [esp+10h],eax
    L_0044dfe3:
        jmp short L_0044dff0
    L_0044dfe5:
        mov eax,dword ptr [esp+10h]
    L_0044dfe9:
        lea esp,[esp+force_disp32_zero]
    L_0044dff0:
        mov ecx,dword ptr [edi]
    L_0044dff2:
        mov dl,byte ptr [ecx+ebp+10h]
    L_0044dff6:
        cmp dl,66h
    L_0044dff9:
        je short L_0044e033
    L_0044dffb:
        cmp dl,67h
    L_0044dffe:
        je short L_0044e033
    L_0044e000:
        mov edx,dword ptr [esp+24h]
    L_0044e004:
        shr eax,2
    L_0044e007:
        mov ecx,dword ptr [ecx+eax*4+10h]
    L_0044e00b:
        push ecx
    L_0044e00c:
        push ebx
    L_0044e00d:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0044e012:
        mov edx,dword ptr [edi]
    L_0044e014:
        cmp byte ptr [edx+ebp+11h],66h
    L_0044e019:
        mov dword ptr [esp+18h],eax
    L_0044e01d:
        jne short L_0044e02b
    L_0044e01f:
        fild dword ptr [esp+18h]
    L_0044e023:
        mov eax,dword ptr [esp+28h]
    L_0044e027:
        fstp dword ptr [eax]
    L_0044e029:
        jmp short L_0044e062
    L_0044e02b:
        mov ecx,dword ptr [esp+28h]
    L_0044e02f:
        mov dword ptr [ecx],eax
    L_0044e031:
        jmp short L_0044e062
    L_0044e033:
        shr eax,2
    L_0044e036:
        mov edx,dword ptr [ecx+eax*4+10h]
    L_0044e03a:
        mov eax,dword ptr [esp+24h]
    L_0044e03e:
        push edx
    L_0044e03f:
        mov ecx,ebx
    L_0044e041:
        call asm_ECL_ResolveFloatValue_0044ff80
    L_0044e046:
        mov eax,dword ptr [edi]
    L_0044e048:
        cmp byte ptr [eax+ebp+11h],66h
    L_0044e04d:
        jne short L_0044e057
    L_0044e04f:
        mov ecx,dword ptr [esp+28h]
    L_0044e053:
        fstp dword ptr [ecx]
    L_0044e055:
        jmp short L_0044e062
    L_0044e057:
        call asm_FUN_00463b2c_00463b2c
    L_0044e05c:
        mov edx,dword ptr [esp+28h]
    L_0044e060:
        mov dword ptr [edx],eax
    L_0044e062:
        mov ecx,dword ptr [esp+28h]
    L_0044e066:
        mov eax,dword ptr [edi]
    L_0044e068:
        mov edx,dword ptr [esp+10h]
    L_0044e06c:
        add ecx,4
    L_0044e06f:
        mov dword ptr [esp+28h],ecx
    L_0044e073:
        movzx ecx,byte ptr [eax+0Bh]
    L_0044e077:
        inc ebx
    L_0044e078:
        add edx,8
    L_0044e07b:
        add ebp,8
    L_0044e07e:
        cmp ebx,ecx
    L_0044e080:
        mov dword ptr [esp+10h],edx
    L_0044e084:
        jl asm_target_0044dfe5
    L_0044e08a:
        mov eax,dword ptr [esp+1Ch]
    L_0044e08e:
        test eax,eax
    L_0044e090:
        mov edx,dword ptr [esp+24h]
    L_0044e094:
        mov ebx,4
    L_0044e099:
        je short L_0044e0f4
    L_0044e09b:
        mov ecx,dword ptr [esi+1008h]
    L_0044e0a1:
        add ecx,0FFFFFFFCh
    L_0044e0a4:
        js short L_0044e0b4
    L_0044e0a6:
        mov dword ptr [esi+1008h],ecx
    L_0044e0ac:
        mov ecx,dword ptr [ecx+esi+8]
    L_0044e0b0:
        mov dword ptr [esp+14h],ecx
    L_0044e0b4:
        mov ecx,dword ptr [esp+14h]
    L_0044e0b8:
        mov dword ptr [esi+1008h],eax
    L_0044e0be:
        mov dword ptr [eax+esi+4],ecx
    L_0044e0c2:
        mov eax,dword ptr [esi+1008h]
    L_0044e0c8:
        lea ecx,[eax+4]
    L_0044e0cb:
        cmp ecx,1000h
    L_0044e0d1:
        jge short L_0044e0df
    L_0044e0d3:
        mov ecx,dword ptr [edx]
    L_0044e0d5:
        mov dword ptr [eax+esi+8],ecx
    L_0044e0d9:
        add dword ptr [esi+1008h],ebx
    L_0044e0df:
        mov eax,dword ptr [esi+1008h]
    L_0044e0e5:
        lea ecx,[eax+4]
    L_0044e0e8:
        cmp ecx,1000h
    L_0044e0ee:
        jge short L_0044e12e
    L_0044e0f0:
        mov ecx,dword ptr [edi]
    L_0044e0f2:
        jmp short L_0044e124
    L_0044e0f4:
        mov eax,ebx
    L_0044e0f6:
        lea ebp,[eax+4]
    L_0044e0f9:
        xor ecx,ecx
    L_0044e0fb:
        cmp ebp,1000h
    L_0044e101:
        mov dword ptr [esi+1008h],ebx
    L_0044e107:
        jge short L_0044e113
    L_0044e109:
        mov dword ptr [eax+esi+8],ecx
    L_0044e10d:
        add dword ptr [esi+1008h],ebx
    L_0044e113:
        mov eax,dword ptr [esi+1008h]
    L_0044e119:
        lea ebp,[eax+4]
    L_0044e11c:
        cmp ebp,1000h
    L_0044e122:
        jge short L_0044e12e
    L_0044e124:
        mov dword ptr [eax+esi+8],ecx
    L_0044e128:
        add dword ptr [esi+1008h],ebx
    L_0044e12e:
        mov eax,dword ptr [edx+1014h]
    L_0044e134:
        mov ebx,dword ptr [eax+4]
    L_0044e137:
        mov dword ptr [eax+4],esi
    L_0044e13a:
        mov esi,dword ptr [edx+1014h]
    L_0044e140:
        mov edx,dword ptr [edi]
    L_0044e142:
        mov eax,dword ptr [esi+102Ch]
    L_0044e148:
        add edx,14h
    L_0044e14b:
        push edx
    L_0044e14c:
        call asm_FUN_00450470_00450470
    L_0044e151:
        mov ecx,dword ptr [esi+4]
    L_0044e154:
        mov dword ptr [ecx+4],eax
    L_0044e157:
        mov edx,dword ptr [esi+4]
    L_0044e15a:
        mov dword ptr [edx],0
    L_0044e160:
        mov eax,dword ptr [esi+4]
    L_0044e163:
        mov ecx,dword ptr [eax+4]
    L_0044e166:
        test ecx,ecx
    L_0044e168:
        jne short L_0044e17d
    L_0044e16a:
        mov dword ptr [edi],0
    L_0044e170:
        pop edi
    L_0044e171:
        pop esi
    L_0044e172:
        pop ebp
    L_0044e173:
        or eax,0FFFFFFFFh
    L_0044e176:
        pop ebx
    L_0044e177:
        add esp,10h
    L_0044e17a:
        ret 8
    L_0044e17d:
        mov ecx,dword ptr [esp+24h]
    L_0044e181:
        mov edx,dword ptr [ecx+1014h]
    L_0044e187:
        pop edi
    L_0044e188:
        pop esi
    L_0044e189:
        pop ebp
    L_0044e18a:
        mov dword ptr [edx+4],ebx
    L_0044e18d:
        xor eax,eax
    L_0044e18f:
        pop ebx
    L_0044e190:
        add esp,10h
    L_0044e193:
        ret 8
    }
}

// 0x0044E1A0..0x0044E1D7: FUN_0044e1a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044e1a0_0044e1a0() {
    __asm {
    L_0044e1a0:
        sub esp,108h
    L_0044e1a6:
        push ebx
    L_0044e1a7:
        push ebp
    L_0044e1a8:
        push esi
    L_0044e1a9:
        mov esi,eax
    L_0044e1ab:
        mov eax,dword ptr [esi+4]
    L_0044e1ae:
        lea ebx,[esi+4]
    L_0044e1b1:
        xor ebp,ebp
    L_0044e1b3:
        cmp eax,ebp
    L_0044e1b5:
        jne short L_0044e1c6
    L_0044e1b7:
        pop esi
    L_0044e1b8:
        pop ebp
    L_0044e1b9:
        or eax,0FFFFFFFFh
    L_0044e1bc:
        pop ebx
    L_0044e1bd:
        add esp,108h
    L_0044e1c3:
        ret 4
    L_0044e1c6:
        fild dword ptr [eax]
    L_0044e1c8:
        push edi
    L_0044e1c9:
        fcomp dword ptr [esi]
    L_0044e1cb:
        fnstsw ax
    L_0044e1cd:
        test ah,41h
    L_0044e1d0:
        jp asm_target_0044fb96
    L_0044e1d6:
        TH10_REL8(0xeb, 0x0044e1d6, VA_asm_FUN_0044e1a0_part_0044e1e0)
    }
}

// 0x0044E1E0..0x0044FBC1: FUN_0044e1a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044e1a0_part_0044e1e0() {
    __asm {
    L_0044e1e0:
        mov edi,dword ptr [ebx]
    L_0044e1e2:
        mov al,byte ptr [edi+0Ah]
    L_0044e1e5:
        test byte ptr [esi+101Ch],al
    L_0044e1eb:
        je asm_target_0044fb77
    L_0044e1f1:
        movsx eax,word ptr [edi+4]
    L_0044e1f5:
        cmp eax,57h
    L_0044e1f8:
        ja asm_target_0044fb68
    L_0044e1fe:
        movzx ecx,byte ptr [eax+44FCB4h]
    L_0044e205:
        jmp dword ptr [ecx*4+44FBC4h]
    L_0044e20c:
        lea edi,[esi+8]
    L_0044e20f:
        mov eax,edi
    L_0044e211:
        call asm_ECL_PopScratchValue_004506d0
    L_0044e216:
        cmp dword ptr [esi+1008h],ebp
    L_0044e21c:
        je asm_target_0044fbb0
    L_0044e222:
        mov eax,dword ptr [edi+1000h]
    L_0044e228:
        add eax,0FFFFFFFCh
    L_0044e22b:
        cmp eax,ebp
    L_0044e22d:
        jl short L_0044e23a
    L_0044e22f:
        mov dword ptr [edi+1000h],eax
    L_0044e235:
        mov edx,dword ptr [eax+edi]
    L_0044e238:
        mov dword ptr [ebx],edx
    L_0044e23a:
        mov eax,dword ptr [edi+1000h]
    L_0044e240:
        add eax,0FFFFFFFCh
    L_0044e243:
        cmp eax,ebp
    L_0044e245:
        jl short L_0044e252
    L_0044e247:
        mov dword ptr [edi+1000h],eax
    L_0044e24d:
        mov eax,dword ptr [edi+eax]
    L_0044e250:
        mov dword ptr [esi],eax
    L_0044e252:
        cmp dword ptr [ebx],ebp
    L_0044e254:
        je asm_target_0044fbb2
    L_0044e25a:
        jmp asm_target_0044fb77
    L_0044e25f:
        mov edi,dword ptr [esi+1014h]
    L_0044e265:
        push ebp
    L_0044e266:
        push 0FFFFFFFFh
    L_0044e268:
        call asm_EclVm_SpawnChild_004500d0
    L_0044e26d:
        jmp asm_target_0044fb77
    L_0044e272:
        mov eax,dword ptr [esi+1014h]
    L_0044e278:
        call asm_ECL_ResetVariableBindings_00450190
    L_0044e27d:
        jmp asm_target_0044fb77
    L_0044e282:
        mov ecx,dword ptr [edi+10h]
    L_0044e285:
        add ecx,4
    L_0044e288:
        shr ecx,2
    L_0044e28b:
        mov edx,dword ptr [edi+ecx*4+10h]
    L_0044e28f:
        push 1
    L_0044e291:
        push edx
    L_0044e292:
        push 1
    L_0044e294:
        mov edx,esi
    L_0044e296:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0044e29b:
        mov edi,dword ptr [esi+1014h]
    L_0044e2a1:
        push eax
    L_0044e2a2:
        call asm_EclVm_SpawnChild_004500d0
    L_0044e2a7:
        jmp asm_target_0044fb77
    L_0044e2ac:
        push ebp
    L_0044e2ad:
        mov edx,esi
    L_0044e2af:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0044e2b4:
        mov ecx,eax
    L_0044e2b6:
        mov eax,dword ptr [esi+1014h]
    L_0044e2bc:
        call asm_ECL_FindVariable_00450160
    L_0044e2c1:
        cmp eax,ebp
    L_0044e2c3:
        je asm_target_0044fb77
    L_0044e2c9:
        mov eax,dword ptr [eax]
    L_0044e2cb:
        mov dword ptr [eax+4],ebp
    L_0044e2ce:
        jmp asm_target_0044fb77
    L_0044e2d3:
        push ebp
    L_0044e2d4:
        mov edx,esi
    L_0044e2d6:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0044e2db:
        mov ecx,eax
    L_0044e2dd:
        mov eax,dword ptr [esi+1014h]
    L_0044e2e3:
        call asm_ECL_FindVariable_00450160
    L_0044e2e8:
        cmp eax,ebp
    L_0044e2ea:
        je asm_target_0044fb77
    L_0044e2f0:
        mov eax,dword ptr [eax]
    L_0044e2f2:
        or dword ptr [eax+1020h],1
    L_0044e2f9:
        jmp asm_target_0044fb77
    L_0044e2fe:
        push ebp
    L_0044e2ff:
        mov edx,esi
    L_0044e301:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0044e306:
        mov ecx,eax
    L_0044e308:
        mov eax,dword ptr [esi+1014h]
    L_0044e30e:
        call asm_ECL_FindVariable_00450160
    L_0044e313:
        cmp eax,ebp
    L_0044e315:
        je asm_target_0044fb77
    L_0044e31b:
        mov eax,dword ptr [eax]
    L_0044e31d:
        and dword ptr [eax+1020h],0FFFFFFFEh
    L_0044e324:
        jmp asm_target_0044fb77
    L_0044e329:
        push ebp
    L_0044e32a:
        mov edx,esi
    L_0044e32c:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0044e331:
        mov ecx,eax
    L_0044e333:
        mov eax,dword ptr [esi+1014h]
    L_0044e339:
        call asm_ECL_FindVariable_00450160
    L_0044e33e:
        cmp eax,ebp
    L_0044e340:
        je asm_target_0044fb77
    L_0044e346:
        mov edi,dword ptr [eax]
    L_0044e348:
        push 1
    L_0044e34a:
        mov edx,esi
    L_0044e34c:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0044e351:
        mov dword ptr [edi+1018h],eax
    L_0044e357:
        jmp asm_target_0044fb77
    L_0044e35c:
        push ebp
    L_0044e35d:
        push esi
    L_0044e35e:
        mov eax,esi
    L_0044e360:
        call asm_EclVm_StartChildRetail_0044df70
    L_0044e365:
        test eax,eax
    L_0044e367:
        jne asm_target_0044fbb2
    L_0044e36d:
        jmp asm_target_0044fb85
    L_0044e372:
        mov eax,dword ptr [esi+1008h]
    L_0044e378:
        add eax,0FFFFFFFCh
    L_0044e37b:
        cmp eax,ebp
    L_0044e37d:
        jl short L_0044e3b3
    L_0044e37f:
        mov dword ptr [esi+1008h],eax
    L_0044e385:
        mov ecx,dword ptr [esi+eax+8]
    L_0044e389:
        add eax,0FFFFFFFCh
    L_0044e38c:
        mov dword ptr [esp+90h],ecx
    L_0044e393:
        mov dword ptr [esi+1008h],eax
    L_0044e399:
        cmp byte ptr [esi+eax+8],66h
    L_0044e39e:
        jne short L_0044e3b3
    L_0044e3a0:
        fld dword ptr [esp+90h]
    L_0044e3a7:
        call asm_FUN_00463b2c_00463b2c
    L_0044e3ac:
        mov dword ptr [esp+90h],eax
    L_0044e3b3:
        cmp dword ptr [esp+90h],ebp
    L_0044e3ba:
        jne short L_0044e40f
    L_0044e3bc:
        jmp asm_target_0044fb77
    L_0044e3c1:
        mov eax,dword ptr [esi+1008h]
    L_0044e3c7:
        add eax,0FFFFFFFCh
    L_0044e3ca:
        cmp eax,ebp
    L_0044e3cc:
        jl short L_0044e402
    L_0044e3ce:
        mov dword ptr [esi+1008h],eax
    L_0044e3d4:
        mov edx,dword ptr [esi+eax+8]
    L_0044e3d8:
        add eax,0FFFFFFFCh
    L_0044e3db:
        mov dword ptr [esi+1008h],eax
    L_0044e3e1:
        cmp byte ptr [esi+eax+8],66h
    L_0044e3e6:
        mov dword ptr [esp+0FCh],edx
    L_0044e3ed:
        jne short L_0044e402
    L_0044e3ef:
        fld dword ptr [esp+0FCh]
    L_0044e3f6:
        call asm_FUN_00463b2c_00463b2c
    L_0044e3fb:
        mov dword ptr [esp+0FCh],eax
    L_0044e402:
        cmp dword ptr [esp+0FCh],ebp
    L_0044e409:
        jne asm_target_0044fb77
    L_0044e40f:
        mov eax,dword ptr [ebx]
    L_0044e411:
        fild dword ptr [eax+14h]
    L_0044e414:
        fstp dword ptr [esi]
    L_0044e416:
        mov ecx,dword ptr [eax+10h]
    L_0044e419:
        jmp asm_target_0044fb81
    L_0044e41e:
        push ebp
    L_0044e41f:
        mov edx,esi
    L_0044e421:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0044e426:
        mov dword ptr [esp+10h],eax
    L_0044e42a:
        fild dword ptr [esp+10h]
    L_0044e42e:
        fsubr dword ptr [esi]
    L_0044e430:
        fstp dword ptr [esi]
    L_0044e432:
        jmp asm_target_0044fb77
    L_0044e437:
        push ebp
    L_0044e438:
        mov edx,esi
    L_0044e43a:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0044e43f:
        lea edx,[esi+8]
    L_0044e442:
        mov ecx,eax
    L_0044e444:
        mov eax,edx
    L_0044e446:
        call asm_ECL_PushScratchValue_00450690
    L_0044e44b:
        jmp asm_target_0044fb77
    L_0044e450:
        lea eax,[esi+8]
    L_0044e453:
        call asm_ECL_PopScratchValue_004506d0
    L_0044e458:
        jmp asm_target_0044fb77
    L_0044e45d:
        push ebp
    L_0044e45e:
        mov edx,esi
    L_0044e460:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0044e465:
        mov dword ptr [esp+10h],eax
    L_0044e469:
        lea eax,[esp+10h]
    L_0044e46d:
        push eax
    L_0044e46e:
        lea eax,[esi+8]
    L_0044e471:
        mov dl,69h
    L_0044e473:
        push 4
    L_0044e475:
        call asm_FUN_004505b0_004505b0
    L_0044e47a:
        jmp asm_target_0044fb77
    L_0044e47f:
        xor ecx,ecx
    L_0044e481:
        call asm_ECL_ResolveVariableValue_00450030
    L_0044e486:
        mov edi,eax
    L_0044e488:
        mov eax,dword ptr [esi+1008h]
    L_0044e48e:
        add eax,0FFFFFFFCh
    L_0044e491:
        cmp eax,ebp
    L_0044e493:
        jl asm_target_0044fb77
    L_0044e499:
        mov dword ptr [esi+1008h],eax
    L_0044e49f:
        mov ecx,dword ptr [esi+eax+8]
    L_0044e4a3:
        mov dword ptr [edi],ecx
    L_0044e4a5:
        mov edx,dword ptr [esi+1008h]
    L_0044e4ab:
        add edx,0FFFFFFFCh
    L_0044e4ae:
        mov eax,edx
    L_0044e4b0:
        mov dword ptr [esi+1008h],edx
    L_0044e4b6:
        cmp byte ptr [esi+eax+8],66h
    L_0044e4bb:
        jne asm_target_0044fb77
    L_0044e4c1:
        fld dword ptr [edi]
    L_0044e4c3:
        call asm_FUN_00463b2c_00463b2c
    L_0044e4c8:
        mov dword ptr [edi],eax
    L_0044e4ca:
        jmp asm_target_0044fb77
    L_0044e4cf:
        xor ecx,ecx
    L_0044e4d1:
        mov eax,esi
    L_0044e4d3:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044e4d8:
        fstp dword ptr [esp+10h]
    L_0044e4dc:
        lea edx,[esp+10h]
    L_0044e4e0:
        push edx
    L_0044e4e1:
        lea eax,[esi+8]
    L_0044e4e4:
        mov dl,66h
    L_0044e4e6:
        push 4
    L_0044e4e8:
        call asm_FUN_004505b0_004505b0
    L_0044e4ed:
        jmp asm_target_0044fb77
    L_0044e4f2:
        xor ecx,ecx
    L_0044e4f4:
        mov eax,esi
    L_0044e4f6:
        call asm_ECL_ResolveFloatDestination_00450070
    L_0044e4fb:
        mov ecx,dword ptr [esi+1008h]
    L_0044e501:
        add ecx,0FFFFFFFCh
    L_0044e504:
        cmp ecx,ebp
    L_0044e506:
        jl asm_target_0044fb77
    L_0044e50c:
        mov dword ptr [esi+1008h],ecx
    L_0044e512:
        mov ecx,dword ptr [esi+ecx+8]
    L_0044e516:
        mov dword ptr [eax],ecx
    L_0044e518:
        mov edi,dword ptr [esi+1008h]
    L_0044e51e:
        add edi,0FFFFFFFCh
    L_0044e521:
        mov ecx,edi
    L_0044e523:
        mov dword ptr [esi+1008h],edi
    L_0044e529:
        mov cl,byte ptr [esi+ecx+8]
    L_0044e52d:
        cmp cl,66h
    L_0044e530:
        je asm_target_0044fb77
    L_0044e536:
        cmp cl,69h
    L_0044e539:
        jne asm_target_0044fb77
    L_0044e53f:
        fild dword ptr [eax]
    L_0044e541:
        fstp dword ptr [eax]
    L_0044e543:
        jmp asm_target_0044fb77
    L_0044e548:
        mov eax,dword ptr [esi+1008h]
    L_0044e54e:
        lea edi,[esi+8]
    L_0044e551:
        add eax,0FFFFFFFCh
    L_0044e554:
        cmp eax,ebp
    L_0044e556:
        jl short L_0044e58a
    L_0044e558:
        mov dword ptr [edi+1000h],eax
    L_0044e55e:
        mov edx,dword ptr [edi+eax]
    L_0044e561:
        add eax,0FFFFFFFCh
    L_0044e564:
        mov dword ptr [edi+1000h],eax
    L_0044e56a:
        cmp byte ptr [edi+eax],66h
    L_0044e56e:
        mov dword ptr [esp+104h],edx
    L_0044e575:
        jne short L_0044e58a
    L_0044e577:
        fld dword ptr [esp+104h]
    L_0044e57e:
        call asm_FUN_00463b2c_00463b2c
    L_0044e583:
        mov dword ptr [esp+104h],eax
    L_0044e58a:
        mov eax,dword ptr [edi+1000h]
    L_0044e590:
        add eax,0FFFFFFFCh
    L_0044e593:
        cmp eax,ebp
    L_0044e595:
        jl short L_0044e5c0
    L_0044e597:
        mov dword ptr [edi+1000h],eax
    L_0044e59d:
        mov ecx,dword ptr [edi+eax]
    L_0044e5a0:
        add eax,0FFFFFFFCh
    L_0044e5a3:
        mov dword ptr [esp+20h],ecx
    L_0044e5a7:
        mov dword ptr [edi+1000h],eax
    L_0044e5ad:
        cmp byte ptr [edi+eax],66h
    L_0044e5b1:
        jne short L_0044e5c0
    L_0044e5b3:
        fld dword ptr [esp+20h]
    L_0044e5b7:
        call asm_FUN_00463b2c_00463b2c
    L_0044e5bc:
        mov dword ptr [esp+20h],eax
    L_0044e5c0:
        mov edx,dword ptr [esp+104h]
    L_0044e5c7:
        mov ebx,dword ptr [esp+20h]
    L_0044e5cb:
        lea eax,[esp+20h]
    L_0044e5cf:
        push eax
    L_0044e5d0:
        add ebx,edx
    L_0044e5d2:
        mov dl,69h
    L_0044e5d4:
        mov eax,edi
    L_0044e5d6:
        push 4
    L_0044e5d8:
        mov dword ptr [esp+28h],ebx
    L_0044e5dc:
        call asm_FUN_004505b0_004505b0
    L_0044e5e1:
        jmp asm_target_0044fb77
    L_0044e5e6:
        mov eax,dword ptr [esi+1008h]
    L_0044e5ec:
        lea edi,[esi+8]
    L_0044e5ef:
        add eax,0FFFFFFFCh
    L_0044e5f2:
        cmp eax,ebp
    L_0044e5f4:
        jl short L_0044e61f
    L_0044e5f6:
        mov dword ptr [edi+1000h],eax
    L_0044e5fc:
        mov ecx,dword ptr [edi+eax]
    L_0044e5ff:
        add eax,0FFFFFFFCh
    L_0044e602:
        mov dword ptr [esp+50h],ecx
    L_0044e606:
        mov dword ptr [edi+1000h],eax
    L_0044e60c:
        cmp byte ptr [edi+eax],66h
    L_0044e610:
        jne short L_0044e61f
    L_0044e612:
        fld dword ptr [esp+50h]
    L_0044e616:
        call asm_FUN_00463b2c_00463b2c
    L_0044e61b:
        mov dword ptr [esp+50h],eax
    L_0044e61f:
        mov eax,dword ptr [edi+1000h]
    L_0044e625:
        add eax,0FFFFFFFCh
    L_0044e628:
        cmp eax,ebp
    L_0044e62a:
        jl short L_0044e655
    L_0044e62c:
        mov dword ptr [edi+1000h],eax
    L_0044e632:
        mov edx,dword ptr [edi+eax]
    L_0044e635:
        add eax,0FFFFFFFCh
    L_0044e638:
        mov dword ptr [edi+1000h],eax
    L_0044e63e:
        cmp byte ptr [edi+eax],66h
    L_0044e642:
        mov dword ptr [esp+24h],edx
    L_0044e646:
        jne short L_0044e655
    L_0044e648:
        fld dword ptr [esp+24h]
    L_0044e64c:
        call asm_FUN_00463b2c_00463b2c
    L_0044e651:
        mov dword ptr [esp+24h],eax
    L_0044e655:
        mov ebx,dword ptr [esp+24h]
    L_0044e659:
        mov eax,dword ptr [esp+50h]
    L_0044e65d:
        lea ecx,[esp+24h]
    L_0044e661:
        sub ebx,eax
    L_0044e663:
        push ecx
    L_0044e664:
        mov dl,69h
    L_0044e666:
        mov eax,edi
    L_0044e668:
        push 4
    L_0044e66a:
        mov dword ptr [esp+2Ch],ebx
    L_0044e66e:
        call asm_FUN_004505b0_004505b0
    L_0044e673:
        jmp asm_target_0044fb77
    L_0044e678:
        mov eax,dword ptr [esi+1008h]
    L_0044e67e:
        lea edi,[esi+8]
    L_0044e681:
        add eax,0FFFFFFFCh
    L_0044e684:
        cmp eax,ebp
    L_0044e686:
        jl short L_0044e6ba
    L_0044e688:
        mov dword ptr [edi+1000h],eax
    L_0044e68e:
        mov edx,dword ptr [edi+eax]
    L_0044e691:
        add eax,0FFFFFFFCh
    L_0044e694:
        mov dword ptr [edi+1000h],eax
    L_0044e69a:
        cmp byte ptr [edi+eax],66h
    L_0044e69e:
        mov dword ptr [esp+0B0h],edx
    L_0044e6a5:
        jne short L_0044e6ba
    L_0044e6a7:
        fld dword ptr [esp+0B0h]
    L_0044e6ae:
        call asm_FUN_00463b2c_00463b2c
    L_0044e6b3:
        mov dword ptr [esp+0B0h],eax
    L_0044e6ba:
        mov eax,dword ptr [edi+1000h]
    L_0044e6c0:
        lea ecx,[eax-4]
    L_0044e6c3:
        cmp ecx,ebp
    L_0044e6c5:
        jl short L_0044e70d
    L_0044e6c7:
        mov dword ptr [edi+1000h],ecx
    L_0044e6cd:
        mov eax,dword ptr [edi+ecx]
    L_0044e6d0:
        add ecx,0FFFFFFFCh
    L_0044e6d3:
        mov dword ptr [edi+1000h],ecx
    L_0044e6d9:
        cmp byte ptr [edi+ecx],66h
    L_0044e6dd:
        mov dword ptr [esp+44h],eax
    L_0044e6e1:
        jne short L_0044e711
    L_0044e6e3:
        fld dword ptr [esp+44h]
    L_0044e6e7:
        call asm_FUN_00463b2c_00463b2c
    L_0044e6ec:
        imul eax,dword ptr [esp+0B0h]
    L_0044e6f4:
        mov dword ptr [esp+44h],eax
    L_0044e6f8:
        lea eax,[esp+44h]
    L_0044e6fc:
        push eax
    L_0044e6fd:
        mov dl,69h
    L_0044e6ff:
        mov eax,edi
    L_0044e701:
        push 4
    L_0044e703:
        call asm_FUN_004505b0_004505b0
    L_0044e708:
        jmp asm_target_0044fb77
    L_0044e70d:
        mov eax,dword ptr [esp+44h]
    L_0044e711:
        imul eax,dword ptr [esp+0B0h]
    L_0044e719:
        mov dword ptr [esp+44h],eax
    L_0044e71d:
        lea eax,[esp+44h]
    L_0044e721:
        push eax
    L_0044e722:
        mov dl,69h
    L_0044e724:
        mov eax,edi
    L_0044e726:
        push 4
    L_0044e728:
        call asm_FUN_004505b0_004505b0
    L_0044e72d:
        jmp asm_target_0044fb77
    L_0044e732:
        mov eax,dword ptr [esi+1008h]
    L_0044e738:
        lea edi,[esi+8]
    L_0044e73b:
        add eax,0FFFFFFFCh
    L_0044e73e:
        cmp eax,ebp
    L_0044e740:
        jl short L_0044e76b
    L_0044e742:
        mov dword ptr [edi+1000h],eax
    L_0044e748:
        mov ecx,dword ptr [edi+eax]
    L_0044e74b:
        add eax,0FFFFFFFCh
    L_0044e74e:
        mov dword ptr [esp+58h],ecx
    L_0044e752:
        mov dword ptr [edi+1000h],eax
    L_0044e758:
        cmp byte ptr [edi+eax],66h
    L_0044e75c:
        jne short L_0044e76b
    L_0044e75e:
        fld dword ptr [esp+58h]
    L_0044e762:
        call asm_FUN_00463b2c_00463b2c
    L_0044e767:
        mov dword ptr [esp+58h],eax
    L_0044e76b:
        mov eax,dword ptr [edi+1000h]
    L_0044e771:
        lea ecx,[eax-4]
    L_0044e774:
        cmp ecx,ebp
    L_0044e776:
        jl short L_0044e7bb
    L_0044e778:
        mov dword ptr [edi+1000h],ecx
    L_0044e77e:
        mov eax,dword ptr [edi+ecx]
    L_0044e781:
        add ecx,0FFFFFFFCh
    L_0044e784:
        mov dword ptr [edi+1000h],ecx
    L_0044e78a:
        cmp byte ptr [edi+ecx],66h
    L_0044e78e:
        mov dword ptr [esp+3Ch],eax
    L_0044e792:
        jne short L_0044e7bf
    L_0044e794:
        fld dword ptr [esp+3Ch]
    L_0044e798:
        call asm_FUN_00463b2c_00463b2c
    L_0044e79d:
        cdq
    L_0044e79e:
        idiv dword ptr [esp+58h]
    L_0044e7a2:
        lea edx,[esp+3Ch]
    L_0044e7a6:
        push edx
    L_0044e7a7:
        mov dl,69h
    L_0044e7a9:
        push 4
    L_0044e7ab:
        mov dword ptr [esp+44h],eax
    L_0044e7af:
        mov eax,edi
    L_0044e7b1:
        call asm_FUN_004505b0_004505b0
    L_0044e7b6:
        jmp asm_target_0044fb77
    L_0044e7bb:
        mov eax,dword ptr [esp+3Ch]
    L_0044e7bf:
        cdq
    L_0044e7c0:
        idiv dword ptr [esp+58h]
    L_0044e7c4:
        lea edx,[esp+3Ch]
    L_0044e7c8:
        push edx
    L_0044e7c9:
        mov dl,69h
    L_0044e7cb:
        push 4
    L_0044e7cd:
        mov dword ptr [esp+44h],eax
    L_0044e7d1:
        mov eax,edi
    L_0044e7d3:
        call asm_FUN_004505b0_004505b0
    L_0044e7d8:
        jmp asm_target_0044fb77
    L_0044e7dd:
        mov eax,dword ptr [esi+1008h]
    L_0044e7e3:
        lea edi,[esi+8]
    L_0044e7e6:
        add eax,0FFFFFFFCh
    L_0044e7e9:
        cmp eax,ebp
    L_0044e7eb:
        jl short L_0044e81f
    L_0044e7ed:
        mov dword ptr [edi+1000h],eax
    L_0044e7f3:
        mov ecx,dword ptr [edi+eax]
    L_0044e7f6:
        add eax,0FFFFFFFCh
    L_0044e7f9:
        mov dword ptr [esp+0E0h],ecx
    L_0044e800:
        mov dword ptr [edi+1000h],eax
    L_0044e806:
        cmp byte ptr [edi+eax],66h
    L_0044e80a:
        jne short L_0044e81f
    L_0044e80c:
        fld dword ptr [esp+0E0h]
    L_0044e813:
        call asm_FUN_00463b2c_00463b2c
    L_0044e818:
        mov dword ptr [esp+0E0h],eax
    L_0044e81f:
        mov eax,dword ptr [edi+1000h]
    L_0044e825:
        lea ecx,[eax-4]
    L_0044e828:
        cmp ecx,ebp
    L_0044e82a:
        jl short L_0044e872
    L_0044e82c:
        mov dword ptr [edi+1000h],ecx
    L_0044e832:
        mov eax,dword ptr [edi+ecx]
    L_0044e835:
        add ecx,0FFFFFFFCh
    L_0044e838:
        mov dword ptr [edi+1000h],ecx
    L_0044e83e:
        cmp byte ptr [edi+ecx],66h
    L_0044e842:
        mov dword ptr [esp+28h],eax
    L_0044e846:
        jne short L_0044e876
    L_0044e848:
        fld dword ptr [esp+28h]
    L_0044e84c:
        call asm_FUN_00463b2c_00463b2c
    L_0044e851:
        cdq
    L_0044e852:
        idiv dword ptr [esp+0E0h]
    L_0044e859:
        mov eax,edi
    L_0044e85b:
        mov dword ptr [esp+28h],edx
    L_0044e85f:
        lea edx,[esp+28h]
    L_0044e863:
        push edx
    L_0044e864:
        mov dl,69h
    L_0044e866:
        push 4
    L_0044e868:
        call asm_FUN_004505b0_004505b0
    L_0044e86d:
        jmp asm_target_0044fb77
    L_0044e872:
        mov eax,dword ptr [esp+28h]
    L_0044e876:
        cdq
    L_0044e877:
        idiv dword ptr [esp+0E0h]
    L_0044e87e:
        mov eax,edi
    L_0044e880:
        mov dword ptr [esp+28h],edx
    L_0044e884:
        lea edx,[esp+28h]
    L_0044e888:
        push edx
    L_0044e889:
        mov dl,69h
    L_0044e88b:
        push 4
    L_0044e88d:
        call asm_FUN_004505b0_004505b0
    L_0044e892:
        jmp asm_target_0044fb77
    L_0044e897:
        mov ecx,dword ptr [esi+1008h]
    L_0044e89d:
        lea eax,[esi+8]
    L_0044e8a0:
        add ecx,0FFFFFFFCh
    L_0044e8a3:
        cmp ecx,ebp
    L_0044e8a5:
        jl short L_0044e8d2
    L_0044e8a7:
        mov dword ptr [eax+1000h],ecx
    L_0044e8ad:
        mov edx,dword ptr [eax+ecx]
    L_0044e8b0:
        add ecx,0FFFFFFFCh
    L_0044e8b3:
        mov dword ptr [eax+1000h],ecx
    L_0044e8b9:
        mov cl,byte ptr [eax+ecx]
    L_0044e8bc:
        cmp cl,66h
    L_0044e8bf:
        mov dword ptr [esp+60h],edx
    L_0044e8c3:
        je short L_0044e8d2
    L_0044e8c5:
        cmp cl,69h
    L_0044e8c8:
        jne short L_0044e8d2
    L_0044e8ca:
        fild dword ptr [esp+60h]
    L_0044e8ce:
        fstp dword ptr [esp+60h]
    L_0044e8d2:
        mov ecx,dword ptr [eax+1000h]
    L_0044e8d8:
        add ecx,0FFFFFFFCh
    L_0044e8db:
        cmp ecx,ebp
    L_0044e8dd:
        jl short L_0044e921
    L_0044e8df:
        mov dword ptr [eax+1000h],ecx
    L_0044e8e5:
        mov edx,dword ptr [eax+ecx]
    L_0044e8e8:
        add ecx,0FFFFFFFCh
    L_0044e8eb:
        mov dword ptr [eax+1000h],ecx
    L_0044e8f1:
        mov cl,byte ptr [eax+ecx]
    L_0044e8f4:
        cmp cl,66h
    L_0044e8f7:
        mov dword ptr [esp+30h],edx
    L_0044e8fb:
        je short L_0044e921
    L_0044e8fd:
        cmp cl,69h
    L_0044e900:
        jne short L_0044e921
    L_0044e902:
        fild dword ptr [esp+30h]
    L_0044e906:
        lea ecx,[esp+30h]
    L_0044e90a:
        push ecx
    L_0044e90b:
        mov dl,66h
    L_0044e90d:
        fadd dword ptr [esp+64h]
    L_0044e911:
        push 4
    L_0044e913:
        fstp dword ptr [esp+38h]
    L_0044e917:
        call asm_FUN_004505b0_004505b0
    L_0044e91c:
        jmp asm_target_0044fb77
    L_0044e921:
        fld dword ptr [esp+30h]
    L_0044e925:
        lea ecx,[esp+30h]
    L_0044e929:
        fadd dword ptr [esp+60h]
    L_0044e92d:
        push ecx
    L_0044e92e:
        mov dl,66h
    L_0044e930:
        push 4
    L_0044e932:
        fstp dword ptr [esp+38h]
    L_0044e936:
        call asm_FUN_004505b0_004505b0
    L_0044e93b:
        jmp asm_target_0044fb77
    L_0044e940:
        mov ecx,dword ptr [esi+1008h]
    L_0044e946:
        lea eax,[esi+8]
    L_0044e949:
        add ecx,0FFFFFFFCh
    L_0044e94c:
        cmp ecx,ebp
    L_0044e94e:
        jl short L_0044e984
    L_0044e950:
        mov dword ptr [eax+1000h],ecx
    L_0044e956:
        mov edx,dword ptr [eax+ecx]
    L_0044e959:
        add ecx,0FFFFFFFCh
    L_0044e95c:
        mov dword ptr [eax+1000h],ecx
    L_0044e962:
        mov cl,byte ptr [eax+ecx]
    L_0044e965:
        cmp cl,66h
    L_0044e968:
        mov dword ptr [esp+0B8h],edx
    L_0044e96f:
        je short L_0044e984
    L_0044e971:
        cmp cl,69h
    L_0044e974:
        jne short L_0044e984
    L_0044e976:
        fild dword ptr [esp+0B8h]
    L_0044e97d:
        fstp dword ptr [esp+0B8h]
    L_0044e984:
        mov ecx,dword ptr [eax+1000h]
    L_0044e98a:
        add ecx,0FFFFFFFCh
    L_0044e98d:
        cmp ecx,ebp
    L_0044e98f:
        jl short L_0044e9d6
    L_0044e991:
        mov dword ptr [eax+1000h],ecx
    L_0044e997:
        mov edx,dword ptr [eax+ecx]
    L_0044e99a:
        add ecx,0FFFFFFFCh
    L_0044e99d:
        mov dword ptr [eax+1000h],ecx
    L_0044e9a3:
        mov cl,byte ptr [eax+ecx]
    L_0044e9a6:
        cmp cl,66h
    L_0044e9a9:
        mov dword ptr [esp+40h],edx
    L_0044e9ad:
        je short L_0044e9d6
    L_0044e9af:
        cmp cl,69h
    L_0044e9b2:
        jne short L_0044e9d6
    L_0044e9b4:
        fild dword ptr [esp+40h]
    L_0044e9b8:
        lea ecx,[esp+40h]
    L_0044e9bc:
        push ecx
    L_0044e9bd:
        mov dl,66h
    L_0044e9bf:
        fsub dword ptr [esp+0BCh]
    L_0044e9c6:
        push 4
    L_0044e9c8:
        fstp dword ptr [esp+48h]
    L_0044e9cc:
        call asm_FUN_004505b0_004505b0
    L_0044e9d1:
        jmp asm_target_0044fb77
    L_0044e9d6:
        fld dword ptr [esp+40h]
    L_0044e9da:
        lea ecx,[esp+40h]
    L_0044e9de:
        fsub dword ptr [esp+0B8h]
    L_0044e9e5:
        push ecx
    L_0044e9e6:
        mov dl,66h
    L_0044e9e8:
        push 4
    L_0044e9ea:
        fstp dword ptr [esp+48h]
    L_0044e9ee:
        call asm_FUN_004505b0_004505b0
    L_0044e9f3:
        jmp asm_target_0044fb77
    L_0044e9f8:
        mov ecx,dword ptr [esi+1008h]
    L_0044e9fe:
        lea eax,[esi+8]
    L_0044ea01:
        add ecx,0FFFFFFFCh
    L_0044ea04:
        cmp ecx,ebp
    L_0044ea06:
        jl short L_0044ea33
    L_0044ea08:
        mov dword ptr [eax+1000h],ecx
    L_0044ea0e:
        mov edx,dword ptr [eax+ecx]
    L_0044ea11:
        add ecx,0FFFFFFFCh
    L_0044ea14:
        mov dword ptr [eax+1000h],ecx
    L_0044ea1a:
        mov cl,byte ptr [eax+ecx]
    L_0044ea1d:
        cmp cl,66h
    L_0044ea20:
        mov dword ptr [esp+68h],edx
    L_0044ea24:
        je short L_0044ea33
    L_0044ea26:
        cmp cl,69h
    L_0044ea29:
        jne short L_0044ea33
    L_0044ea2b:
        fild dword ptr [esp+68h]
    L_0044ea2f:
        fstp dword ptr [esp+68h]
    L_0044ea33:
        mov ecx,dword ptr [eax+1000h]
    L_0044ea39:
        add ecx,0FFFFFFFCh
    L_0044ea3c:
        cmp ecx,ebp
    L_0044ea3e:
        jl short L_0044ea82
    L_0044ea40:
        mov dword ptr [eax+1000h],ecx
    L_0044ea46:
        mov edx,dword ptr [eax+ecx]
    L_0044ea49:
        add ecx,0FFFFFFFCh
    L_0044ea4c:
        mov dword ptr [eax+1000h],ecx
    L_0044ea52:
        mov cl,byte ptr [eax+ecx]
    L_0044ea55:
        cmp cl,66h
    L_0044ea58:
        mov dword ptr [esp+38h],edx
    L_0044ea5c:
        je short L_0044ea82
    L_0044ea5e:
        cmp cl,69h
    L_0044ea61:
        jne short L_0044ea82
    L_0044ea63:
        fild dword ptr [esp+38h]
    L_0044ea67:
        lea ecx,[esp+38h]
    L_0044ea6b:
        push ecx
    L_0044ea6c:
        mov dl,66h
    L_0044ea6e:
        fmul dword ptr [esp+6Ch]
    L_0044ea72:
        push 4
    L_0044ea74:
        fstp dword ptr [esp+40h]
    L_0044ea78:
        call asm_FUN_004505b0_004505b0
    L_0044ea7d:
        jmp asm_target_0044fb77
    L_0044ea82:
        fld dword ptr [esp+38h]
    L_0044ea86:
        lea ecx,[esp+38h]
    L_0044ea8a:
        fmul dword ptr [esp+68h]
    L_0044ea8e:
        push ecx
    L_0044ea8f:
        mov dl,66h
    L_0044ea91:
        push 4
    L_0044ea93:
        fstp dword ptr [esp+40h]
    L_0044ea97:
        call asm_FUN_004505b0_004505b0
    L_0044ea9c:
        jmp asm_target_0044fb77
    L_0044eaa1:
        mov ecx,dword ptr [esi+1008h]
    L_0044eaa7:
        lea eax,[esi+8]
    L_0044eaaa:
        add ecx,0FFFFFFFCh
    L_0044eaad:
        cmp ecx,ebp
    L_0044eaaf:
        jl short L_0044eae5
    L_0044eab1:
        mov dword ptr [eax+1000h],ecx
    L_0044eab7:
        mov edx,dword ptr [eax+ecx]
    L_0044eaba:
        add ecx,0FFFFFFFCh
    L_0044eabd:
        mov dword ptr [eax+1000h],ecx
    L_0044eac3:
        mov cl,byte ptr [eax+ecx]
    L_0044eac6:
        cmp cl,66h
    L_0044eac9:
        mov dword ptr [esp+0F8h],edx
    L_0044ead0:
        je short L_0044eae5
    L_0044ead2:
        cmp cl,69h
    L_0044ead5:
        jne short L_0044eae5
    L_0044ead7:
        fild dword ptr [esp+0F8h]
    L_0044eade:
        fstp dword ptr [esp+0F8h]
    L_0044eae5:
        mov ecx,dword ptr [eax+1000h]
    L_0044eaeb:
        add ecx,0FFFFFFFCh
    L_0044eaee:
        cmp ecx,ebp
    L_0044eaf0:
        jl short L_0044eb37
    L_0044eaf2:
        mov dword ptr [eax+1000h],ecx
    L_0044eaf8:
        mov edx,dword ptr [eax+ecx]
    L_0044eafb:
        add ecx,0FFFFFFFCh
    L_0044eafe:
        mov dword ptr [eax+1000h],ecx
    L_0044eb04:
        mov cl,byte ptr [eax+ecx]
    L_0044eb07:
        cmp cl,66h
    L_0044eb0a:
        mov dword ptr [esp+2Ch],edx
    L_0044eb0e:
        je short L_0044eb37
    L_0044eb10:
        cmp cl,69h
    L_0044eb13:
        jne short L_0044eb37
    L_0044eb15:
        fild dword ptr [esp+2Ch]
    L_0044eb19:
        lea ecx,[esp+2Ch]
    L_0044eb1d:
        push ecx
    L_0044eb1e:
        mov dl,66h
    L_0044eb20:
        fdiv dword ptr [esp+0FCh]
    L_0044eb27:
        push 4
    L_0044eb29:
        fstp dword ptr [esp+34h]
    L_0044eb2d:
        call asm_FUN_004505b0_004505b0
    L_0044eb32:
        jmp asm_target_0044fb77
    L_0044eb37:
        fld dword ptr [esp+2Ch]
    L_0044eb3b:
        lea ecx,[esp+2Ch]
    L_0044eb3f:
        fdiv dword ptr [esp+0F8h]
    L_0044eb46:
        push ecx
    L_0044eb47:
        mov dl,66h
    L_0044eb49:
        push 4
    L_0044eb4b:
        fstp dword ptr [esp+34h]
    L_0044eb4f:
        call asm_FUN_004505b0_004505b0
    L_0044eb54:
        jmp asm_target_0044fb77
    L_0044eb59:
        mov eax,dword ptr [esi+1008h]
    L_0044eb5f:
        lea edi,[esi+8]
    L_0044eb62:
        add eax,0FFFFFFFCh
    L_0044eb65:
        cmp eax,ebp
    L_0044eb67:
        jl short L_0044eb92
    L_0044eb69:
        mov dword ptr [edi+1000h],eax
    L_0044eb6f:
        mov edx,dword ptr [edi+eax]
    L_0044eb72:
        add eax,0FFFFFFFCh
    L_0044eb75:
        mov dword ptr [edi+1000h],eax
    L_0044eb7b:
        cmp byte ptr [edi+eax],66h
    L_0044eb7f:
        mov dword ptr [esp+70h],edx
    L_0044eb83:
        jne short L_0044eb92
    L_0044eb85:
        fld dword ptr [esp+70h]
    L_0044eb89:
        call asm_FUN_00463b2c_00463b2c
    L_0044eb8e:
        mov dword ptr [esp+70h],eax
    L_0044eb92:
        mov eax,dword ptr [edi+1000h]
    L_0044eb98:
        add eax,0FFFFFFFCh
    L_0044eb9b:
        cmp eax,ebp
    L_0044eb9d:
        jl short L_0044ebd1
    L_0044eb9f:
        mov dword ptr [edi+1000h],eax
    L_0044eba5:
        mov ecx,dword ptr [edi+eax]
    L_0044eba8:
        add eax,0FFFFFFFCh
    L_0044ebab:
        mov dword ptr [esp+0C0h],ecx
    L_0044ebb2:
        mov dword ptr [edi+1000h],eax
    L_0044ebb8:
        cmp byte ptr [edi+eax],66h
    L_0044ebbc:
        jne short L_0044ebd1
    L_0044ebbe:
        fld dword ptr [esp+0C0h]
    L_0044ebc5:
        call asm_FUN_00463b2c_00463b2c
    L_0044ebca:
        mov dword ptr [esp+0C0h],eax
    L_0044ebd1:
        mov eax,dword ptr [esp+70h]
    L_0044ebd5:
        mov ebx,dword ptr [esp+0C0h]
    L_0044ebdc:
        xor edx,edx
    L_0044ebde:
        cmp ebx,eax
    L_0044ebe0:
        sete dl
    L_0044ebe3:
        lea ecx,[esp+10h]
    L_0044ebe7:
        push ecx
    L_0044ebe8:
        mov eax,edi
    L_0044ebea:
        push 4
    L_0044ebec:
        mov dword ptr [esp+18h],edx
    L_0044ebf0:
        mov dl,69h
    L_0044ebf2:
        call asm_FUN_004505b0_004505b0
    L_0044ebf7:
        jmp asm_target_0044fb77
    L_0044ebfc:
        mov eax,dword ptr [esi+1008h]
    L_0044ec02:
        lea edi,[esi+8]
    L_0044ec05:
        add eax,0FFFFFFFCh
    L_0044ec08:
        cmp eax,ebp
    L_0044ec0a:
        jl short L_0044ec35
    L_0044ec0c:
        mov dword ptr [edi+1000h],eax
    L_0044ec12:
        mov edx,dword ptr [edi+eax]
    L_0044ec15:
        add eax,0FFFFFFFCh
    L_0044ec18:
        mov dword ptr [edi+1000h],eax
    L_0044ec1e:
        cmp byte ptr [edi+eax],66h
    L_0044ec22:
        mov dword ptr [esp+78h],edx
    L_0044ec26:
        jne short L_0044ec35
    L_0044ec28:
        fld dword ptr [esp+78h]
    L_0044ec2c:
        call asm_FUN_00463b2c_00463b2c
    L_0044ec31:
        mov dword ptr [esp+78h],eax
    L_0044ec35:
        mov eax,dword ptr [edi+1000h]
    L_0044ec3b:
        add eax,0FFFFFFFCh
    L_0044ec3e:
        cmp eax,ebp
    L_0044ec40:
        jl short L_0044ec74
    L_0044ec42:
        mov dword ptr [edi+1000h],eax
    L_0044ec48:
        mov ecx,dword ptr [edi+eax]
    L_0044ec4b:
        add eax,0FFFFFFFCh
    L_0044ec4e:
        mov dword ptr [esp+0E8h],ecx
    L_0044ec55:
        mov dword ptr [edi+1000h],eax
    L_0044ec5b:
        cmp byte ptr [edi+eax],66h
    L_0044ec5f:
        jne short L_0044ec74
    L_0044ec61:
        fld dword ptr [esp+0E8h]
    L_0044ec68:
        call asm_FUN_00463b2c_00463b2c
    L_0044ec6d:
        mov dword ptr [esp+0E8h],eax
    L_0044ec74:
        mov eax,dword ptr [esp+78h]
    L_0044ec78:
        mov ebx,dword ptr [esp+0E8h]
    L_0044ec7f:
        xor edx,edx
    L_0044ec81:
        cmp ebx,eax
    L_0044ec83:
        setne dl
    L_0044ec86:
        lea ecx,[esp+10h]
    L_0044ec8a:
        push ecx
    L_0044ec8b:
        mov eax,edi
    L_0044ec8d:
        push 4
    L_0044ec8f:
        mov dword ptr [esp+18h],edx
    L_0044ec93:
        mov dl,69h
    L_0044ec95:
        call asm_FUN_004505b0_004505b0
    L_0044ec9a:
        jmp asm_target_0044fb77
    L_0044ec9f:
        mov eax,dword ptr [esi+1008h]
    L_0044eca5:
        lea edi,[esi+8]
    L_0044eca8:
        add eax,0FFFFFFFCh
    L_0044ecab:
        cmp eax,ebp
    L_0044ecad:
        jl short L_0044ece1
    L_0044ecaf:
        mov dword ptr [edi+1000h],eax
    L_0044ecb5:
        mov edx,dword ptr [edi+eax]
    L_0044ecb8:
        add eax,0FFFFFFFCh
    L_0044ecbb:
        mov dword ptr [edi+1000h],eax
    L_0044ecc1:
        cmp byte ptr [edi+eax],66h
    L_0044ecc5:
        mov dword ptr [esp+80h],edx
    L_0044eccc:
        jne short L_0044ece1
    L_0044ecce:
        fld dword ptr [esp+80h]
    L_0044ecd5:
        call asm_FUN_00463b2c_00463b2c
    L_0044ecda:
        mov dword ptr [esp+80h],eax
    L_0044ece1:
        mov eax,dword ptr [edi+1000h]
    L_0044ece7:
        add eax,0FFFFFFFCh
    L_0044ecea:
        cmp eax,ebp
    L_0044ecec:
        jl short L_0044ed20
    L_0044ecee:
        mov dword ptr [edi+1000h],eax
    L_0044ecf4:
        mov ecx,dword ptr [edi+eax]
    L_0044ecf7:
        add eax,0FFFFFFFCh
    L_0044ecfa:
        mov dword ptr [esp+0C8h],ecx
    L_0044ed01:
        mov dword ptr [edi+1000h],eax
    L_0044ed07:
        cmp byte ptr [edi+eax],66h
    L_0044ed0b:
        jne short L_0044ed20
    L_0044ed0d:
        fld dword ptr [esp+0C8h]
    L_0044ed14:
        call asm_FUN_00463b2c_00463b2c
    L_0044ed19:
        mov dword ptr [esp+0C8h],eax
    L_0044ed20:
        mov eax,dword ptr [esp+80h]
    L_0044ed27:
        mov ebx,dword ptr [esp+0C8h]
    L_0044ed2e:
        xor edx,edx
    L_0044ed30:
        cmp ebx,eax
    L_0044ed32:
        setl dl
    L_0044ed35:
        lea ecx,[esp+10h]
    L_0044ed39:
        push ecx
    L_0044ed3a:
        mov eax,edi
    L_0044ed3c:
        push 4
    L_0044ed3e:
        mov dword ptr [esp+18h],edx
    L_0044ed42:
        mov dl,69h
    L_0044ed44:
        call asm_FUN_004505b0_004505b0
    L_0044ed49:
        jmp asm_target_0044fb77
    L_0044ed4e:
        mov eax,dword ptr [esi+1008h]
    L_0044ed54:
        lea edi,[esi+8]
    L_0044ed57:
        add eax,0FFFFFFFCh
    L_0044ed5a:
        cmp eax,ebp
    L_0044ed5c:
        jl short L_0044ed90
    L_0044ed5e:
        mov dword ptr [edi+1000h],eax
    L_0044ed64:
        mov edx,dword ptr [edi+eax]
    L_0044ed67:
        add eax,0FFFFFFFCh
    L_0044ed6a:
        mov dword ptr [edi+1000h],eax
    L_0044ed70:
        cmp byte ptr [edi+eax],66h
    L_0044ed74:
        mov dword ptr [esp+88h],edx
    L_0044ed7b:
        jne short L_0044ed90
    L_0044ed7d:
        fld dword ptr [esp+88h]
    L_0044ed84:
        call asm_FUN_00463b2c_00463b2c
    L_0044ed89:
        mov dword ptr [esp+88h],eax
    L_0044ed90:
        mov eax,dword ptr [edi+1000h]
    L_0044ed96:
        add eax,0FFFFFFFCh
    L_0044ed99:
        cmp eax,ebp
    L_0044ed9b:
        jl short L_0044edcf
    L_0044ed9d:
        mov dword ptr [edi+1000h],eax
    L_0044eda3:
        mov ecx,dword ptr [edi+eax]
    L_0044eda6:
        add eax,0FFFFFFFCh
    L_0044eda9:
        mov dword ptr [esp+108h],ecx
    L_0044edb0:
        mov dword ptr [edi+1000h],eax
    L_0044edb6:
        cmp byte ptr [edi+eax],66h
    L_0044edba:
        jne short L_0044edcf
    L_0044edbc:
        fld dword ptr [esp+108h]
    L_0044edc3:
        call asm_FUN_00463b2c_00463b2c
    L_0044edc8:
        mov dword ptr [esp+108h],eax
    L_0044edcf:
        mov eax,dword ptr [esp+88h]
    L_0044edd6:
        mov ebx,dword ptr [esp+108h]
    L_0044eddd:
        xor edx,edx
    L_0044eddf:
        cmp ebx,eax
    L_0044ede1:
        setle dl
    L_0044ede4:
        lea ecx,[esp+10h]
    L_0044ede8:
        push ecx
    L_0044ede9:
        mov eax,edi
    L_0044edeb:
        push 4
    L_0044eded:
        mov dword ptr [esp+18h],edx
    L_0044edf1:
        mov dl,69h
    L_0044edf3:
        call asm_FUN_004505b0_004505b0
    L_0044edf8:
        jmp asm_target_0044fb77
    L_0044edfd:
        mov eax,dword ptr [esi+1008h]
    L_0044ee03:
        lea edi,[esi+8]
    L_0044ee06:
        add eax,0FFFFFFFCh
    L_0044ee09:
        cmp eax,ebp
    L_0044ee0b:
        jl short L_0044ee36
    L_0044ee0d:
        mov dword ptr [edi+1000h],eax
    L_0044ee13:
        mov edx,dword ptr [edi+eax]
    L_0044ee16:
        add eax,0FFFFFFFCh
    L_0044ee19:
        mov dword ptr [edi+1000h],eax
    L_0044ee1f:
        cmp byte ptr [edi+eax],66h
    L_0044ee23:
        mov dword ptr [esp+48h],edx
    L_0044ee27:
        jne short L_0044ee36
    L_0044ee29:
        fld dword ptr [esp+48h]
    L_0044ee2d:
        call asm_FUN_00463b2c_00463b2c
    L_0044ee32:
        mov dword ptr [esp+48h],eax
    L_0044ee36:
        mov eax,dword ptr [edi+1000h]
    L_0044ee3c:
        add eax,0FFFFFFFCh
    L_0044ee3f:
        cmp eax,ebp
    L_0044ee41:
        jl short L_0044ee75
    L_0044ee43:
        mov dword ptr [edi+1000h],eax
    L_0044ee49:
        mov ecx,dword ptr [edi+eax]
    L_0044ee4c:
        add eax,0FFFFFFFCh
    L_0044ee4f:
        mov dword ptr [esp+0D0h],ecx
    L_0044ee56:
        mov dword ptr [edi+1000h],eax
    L_0044ee5c:
        cmp byte ptr [edi+eax],66h
    L_0044ee60:
        jne short L_0044ee75
    L_0044ee62:
        fld dword ptr [esp+0D0h]
    L_0044ee69:
        call asm_FUN_00463b2c_00463b2c
    L_0044ee6e:
        mov dword ptr [esp+0D0h],eax
    L_0044ee75:
        mov eax,dword ptr [esp+48h]
    L_0044ee79:
        mov ebx,dword ptr [esp+0D0h]
    L_0044ee80:
        xor edx,edx
    L_0044ee82:
        cmp ebx,eax
    L_0044ee84:
        setg dl
    L_0044ee87:
        lea ecx,[esp+10h]
    L_0044ee8b:
        push ecx
    L_0044ee8c:
        mov eax,edi
    L_0044ee8e:
        push 4
    L_0044ee90:
        mov dword ptr [esp+18h],edx
    L_0044ee94:
        mov dl,69h
    L_0044ee96:
        call asm_FUN_004505b0_004505b0
    L_0044ee9b:
        jmp asm_target_0044fb77
    L_0044eea0:
        mov eax,dword ptr [esi+1008h]
    L_0044eea6:
        lea edi,[esi+8]
    L_0044eea9:
        add eax,0FFFFFFFCh
    L_0044eeac:
        cmp eax,ebp
    L_0044eeae:
        jl short L_0044eee2
    L_0044eeb0:
        mov dword ptr [edi+1000h],eax
    L_0044eeb6:
        mov edx,dword ptr [edi+eax]
    L_0044eeb9:
        add eax,0FFFFFFFCh
    L_0044eebc:
        mov dword ptr [edi+1000h],eax
    L_0044eec2:
        cmp byte ptr [edi+eax],66h
    L_0044eec6:
        mov dword ptr [esp+98h],edx
    L_0044eecd:
        jne short L_0044eee2
    L_0044eecf:
        fld dword ptr [esp+98h]
    L_0044eed6:
        call asm_FUN_00463b2c_00463b2c
    L_0044eedb:
        mov dword ptr [esp+98h],eax
    L_0044eee2:
        mov eax,dword ptr [edi+1000h]
    L_0044eee8:
        add eax,0FFFFFFFCh
    L_0044eeeb:
        cmp eax,ebp
    L_0044eeed:
        jl short L_0044ef21
    L_0044eeef:
        mov dword ptr [edi+1000h],eax
    L_0044eef5:
        mov ecx,dword ptr [edi+eax]
    L_0044eef8:
        add eax,0FFFFFFFCh
    L_0044eefb:
        mov dword ptr [esp+0F0h],ecx
    L_0044ef02:
        mov dword ptr [edi+1000h],eax
    L_0044ef08:
        cmp byte ptr [edi+eax],66h
    L_0044ef0c:
        jne short L_0044ef21
    L_0044ef0e:
        fld dword ptr [esp+0F0h]
    L_0044ef15:
        call asm_FUN_00463b2c_00463b2c
    L_0044ef1a:
        mov dword ptr [esp+0F0h],eax
    L_0044ef21:
        mov eax,dword ptr [esp+98h]
    L_0044ef28:
        mov ebx,dword ptr [esp+0F0h]
    L_0044ef2f:
        xor edx,edx
    L_0044ef31:
        cmp ebx,eax
    L_0044ef33:
        setge dl
    L_0044ef36:
        lea ecx,[esp+10h]
    L_0044ef3a:
        push ecx
    L_0044ef3b:
        mov eax,edi
    L_0044ef3d:
        push 4
    L_0044ef3f:
        mov dword ptr [esp+18h],edx
    L_0044ef43:
        mov dl,69h
    L_0044ef45:
        call asm_FUN_004505b0_004505b0
    L_0044ef4a:
        jmp asm_target_0044fb77
    L_0044ef4f:
        mov eax,dword ptr [esi+1008h]
    L_0044ef55:
        lea edi,[esi+8]
    L_0044ef58:
        add eax,0FFFFFFFCh
    L_0044ef5b:
        cmp eax,ebp
    L_0044ef5d:
        jl short L_0044ef91
    L_0044ef5f:
        mov dword ptr [edi+1000h],eax
    L_0044ef65:
        mov edx,dword ptr [edi+eax]
    L_0044ef68:
        add eax,0FFFFFFFCh
    L_0044ef6b:
        mov dword ptr [edi+1000h],eax
    L_0044ef71:
        cmp byte ptr [edi+eax],66h
    L_0044ef75:
        mov dword ptr [esp+0A0h],edx
    L_0044ef7c:
        jne short L_0044ef91
    L_0044ef7e:
        fld dword ptr [esp+0A0h]
    L_0044ef85:
        call asm_FUN_00463b2c_00463b2c
    L_0044ef8a:
        mov dword ptr [esp+0A0h],eax
    L_0044ef91:
        mov ebx,dword ptr [esp+0A0h]
    L_0044ef98:
        xor eax,eax
    L_0044ef9a:
        cmp ebx,ebp
    L_0044ef9c:
        sete al
    L_0044ef9f:
        lea ecx,[esp+10h]
    L_0044efa3:
        push ecx
    L_0044efa4:
        mov dl,69h
    L_0044efa6:
        push 4
    L_0044efa8:
        mov dword ptr [esp+18h],eax
    L_0044efac:
        mov eax,edi
    L_0044efae:
        call asm_FUN_004505b0_004505b0
    L_0044efb3:
        jmp asm_target_0044fb77
    L_0044efb8:
        mov eax,dword ptr [esi+1008h]
    L_0044efbe:
        lea ecx,[esi+8]
    L_0044efc1:
        add eax,0FFFFFFFCh
    L_0044efc4:
        cmp eax,ebp
    L_0044efc6:
        jl short L_0044effa
    L_0044efc8:
        mov dword ptr [ecx+1000h],eax
    L_0044efce:
        mov edx,dword ptr [ecx+eax]
    L_0044efd1:
        add eax,0FFFFFFFCh
    L_0044efd4:
        mov dword ptr [ecx+1000h],eax
    L_0044efda:
        mov al,byte ptr [ecx+eax]
    L_0044efdd:
        cmp al,66h
    L_0044efdf:
        mov dword ptr [esp+0D8h],edx
    L_0044efe6:
        je short L_0044effa
    L_0044efe8:
        cmp al,69h
    L_0044efea:
        jne short L_0044effa
    L_0044efec:
        fild dword ptr [esp+0D8h]
    L_0044eff3:
        fstp dword ptr [esp+0D8h]
    L_0044effa:
        mov eax,dword ptr [ecx+1000h]
    L_0044f000:
        add eax,0FFFFFFFCh
    L_0044f003:
        cmp eax,ebp
    L_0044f005:
        jl short L_0044f039
    L_0044f007:
        mov dword ptr [ecx+1000h],eax
    L_0044f00d:
        mov edx,dword ptr [ecx+eax]
    L_0044f010:
        add eax,0FFFFFFFCh
    L_0044f013:
        mov dword ptr [ecx+1000h],eax
    L_0044f019:
        mov al,byte ptr [ecx+eax]
    L_0044f01c:
        cmp al,66h
    L_0044f01e:
        mov dword ptr [esp+0A8h],edx
    L_0044f025:
        je short L_0044f039
    L_0044f027:
        cmp al,69h
    L_0044f029:
        jne short L_0044f039
    L_0044f02b:
        fild dword ptr [esp+0A8h]
    L_0044f032:
        fstp dword ptr [esp+0A8h]
    L_0044f039:
        fld dword ptr [esp+0D8h]
    L_0044f040:
        mov dword ptr [esp+14h],1
    L_0044f048:
        fld dword ptr [esp+0A8h]
    L_0044f04f:
        fucompp
    L_0044f051:
        fnstsw ax
    L_0044f053:
        test ah,44h
    L_0044f056:
        jnp short L_0044f05c
    L_0044f058:
        mov dword ptr [esp+14h],ebp
    L_0044f05c:
        lea eax,[esp+14h]
    L_0044f060:
        push eax
    L_0044f061:
        mov dl,69h
    L_0044f063:
        mov eax,ecx
    L_0044f065:
        push 4
    L_0044f067:
        call asm_FUN_004505b0_004505b0
    L_0044f06c:
        jmp asm_target_0044fb77
    L_0044f071:
        mov eax,dword ptr [esi+1008h]
    L_0044f077:
        lea ecx,[esi+8]
    L_0044f07a:
        add eax,0FFFFFFFCh
    L_0044f07d:
        cmp eax,ebp
    L_0044f07f:
        jl short L_0044f0b3
    L_0044f081:
        mov dword ptr [ecx+1000h],eax
    L_0044f087:
        mov edx,dword ptr [ecx+eax]
    L_0044f08a:
        add eax,0FFFFFFFCh
    L_0044f08d:
        mov dword ptr [ecx+1000h],eax
    L_0044f093:
        mov al,byte ptr [ecx+eax]
    L_0044f096:
        cmp al,66h
    L_0044f098:
        mov dword ptr [esp+100h],edx
    L_0044f09f:
        je short L_0044f0b3
    L_0044f0a1:
        cmp al,69h
    L_0044f0a3:
        jne short L_0044f0b3
    L_0044f0a5:
        fild dword ptr [esp+100h]
    L_0044f0ac:
        fstp dword ptr [esp+100h]
    L_0044f0b3:
        mov eax,dword ptr [ecx+1000h]
    L_0044f0b9:
        add eax,0FFFFFFFCh
    L_0044f0bc:
        cmp eax,ebp
    L_0044f0be:
        jl short L_0044f0e9
    L_0044f0c0:
        mov dword ptr [ecx+1000h],eax
    L_0044f0c6:
        mov edx,dword ptr [eax+ecx]
    L_0044f0c9:
        add eax,0FFFFFFFCh
    L_0044f0cc:
        mov dword ptr [ecx+1000h],eax
    L_0044f0d2:
        mov al,byte ptr [eax+ecx]
    L_0044f0d5:
        cmp al,66h
    L_0044f0d7:
        mov dword ptr [esp+4Ch],edx
    L_0044f0db:
        je short L_0044f0e9
    L_0044f0dd:
        cmp al,69h
    L_0044f0df:
        jne short L_0044f0e9
    L_0044f0e1:
        fild dword ptr [esp+4Ch]
    L_0044f0e5:
        fstp dword ptr [esp+4Ch]
    L_0044f0e9:
        fld dword ptr [esp+100h]
    L_0044f0f0:
        mov dword ptr [esp+14h],1
    L_0044f0f8:
        fld dword ptr [esp+4Ch]
    L_0044f0fc:
        fucompp
    L_0044f0fe:
        fnstsw ax
    L_0044f100:
        test ah,44h
    L_0044f103:
        jp asm_target_0044f05c
    L_0044f109:
        lea eax,[esp+14h]
    L_0044f10d:
        push eax
    L_0044f10e:
        mov dl,69h
    L_0044f110:
        mov eax,ecx
    L_0044f112:
        push 4
    L_0044f114:
        mov dword ptr [esp+1Ch],ebp
    L_0044f118:
        call asm_FUN_004505b0_004505b0
    L_0044f11d:
        jmp asm_target_0044fb77
    L_0044f122:
        mov eax,dword ptr [esi+1008h]
    L_0044f128:
        lea ecx,[esi+8]
    L_0044f12b:
        add eax,0FFFFFFFCh
    L_0044f12e:
        cmp eax,ebp
    L_0044f130:
        jl short L_0044f15b
    L_0044f132:
        mov dword ptr [ecx+1000h],eax
    L_0044f138:
        mov edx,dword ptr [eax+ecx]
    L_0044f13b:
        add eax,0FFFFFFFCh
    L_0044f13e:
        mov dword ptr [ecx+1000h],eax
    L_0044f144:
        mov al,byte ptr [eax+ecx]
    L_0044f147:
        cmp al,66h
    L_0044f149:
        mov dword ptr [esp+5Ch],edx
    L_0044f14d:
        je short L_0044f15b
    L_0044f14f:
        cmp al,69h
    L_0044f151:
        jne short L_0044f15b
    L_0044f153:
        fild dword ptr [esp+5Ch]
    L_0044f157:
        fstp dword ptr [esp+5Ch]
    L_0044f15b:
        mov eax,dword ptr [ecx+1000h]
    L_0044f161:
        add eax,0FFFFFFFCh
    L_0044f164:
        cmp eax,ebp
    L_0044f166:
        jl short L_0044f191
    L_0044f168:
        mov dword ptr [ecx+1000h],eax
    L_0044f16e:
        mov edx,dword ptr [eax+ecx]
    L_0044f171:
        add eax,0FFFFFFFCh
    L_0044f174:
        mov dword ptr [ecx+1000h],eax
    L_0044f17a:
        mov al,byte ptr [eax+ecx]
    L_0044f17d:
        cmp al,66h
    L_0044f17f:
        mov dword ptr [esp+54h],edx
    L_0044f183:
        je short L_0044f191
    L_0044f185:
        cmp al,69h
    L_0044f187:
        jne short L_0044f191
    L_0044f189:
        fild dword ptr [esp+54h]
    L_0044f18d:
        fstp dword ptr [esp+54h]
    L_0044f191:
        fld dword ptr [esp+54h]
    L_0044f195:
        mov dword ptr [esp+14h],1
    L_0044f19d:
        fcomp dword ptr [esp+5Ch]
    L_0044f1a1:
        fnstsw ax
    L_0044f1a3:
        test ah,5
    L_0044f1a6:
        jnp asm_target_0044f05c
    L_0044f1ac:
        lea eax,[esp+14h]
    L_0044f1b0:
        push eax
    L_0044f1b1:
        mov dl,69h
    L_0044f1b3:
        mov eax,ecx
    L_0044f1b5:
        push 4
    L_0044f1b7:
        mov dword ptr [esp+1Ch],ebp
    L_0044f1bb:
        call asm_FUN_004505b0_004505b0
    L_0044f1c0:
        jmp asm_target_0044fb77
    L_0044f1c5:
        mov eax,dword ptr [esi+1008h]
    L_0044f1cb:
        lea ecx,[esi+8]
    L_0044f1ce:
        add eax,0FFFFFFFCh
    L_0044f1d1:
        cmp eax,ebp
    L_0044f1d3:
        jl short L_0044f1fe
    L_0044f1d5:
        mov dword ptr [ecx+1000h],eax
    L_0044f1db:
        mov edx,dword ptr [eax+ecx]
    L_0044f1de:
        add eax,0FFFFFFFCh
    L_0044f1e1:
        mov dword ptr [ecx+1000h],eax
    L_0044f1e7:
        mov al,byte ptr [eax+ecx]
    L_0044f1ea:
        cmp al,66h
    L_0044f1ec:
        mov dword ptr [esp+6Ch],edx
    L_0044f1f0:
        je short L_0044f1fe
    L_0044f1f2:
        cmp al,69h
    L_0044f1f4:
        jne short L_0044f1fe
    L_0044f1f6:
        fild dword ptr [esp+6Ch]
    L_0044f1fa:
        fstp dword ptr [esp+6Ch]
    L_0044f1fe:
        mov eax,dword ptr [ecx+1000h]
    L_0044f204:
        add eax,0FFFFFFFCh
    L_0044f207:
        cmp eax,ebp
    L_0044f209:
        jl short L_0044f234
    L_0044f20b:
        mov dword ptr [ecx+1000h],eax
    L_0044f211:
        mov edx,dword ptr [eax+ecx]
    L_0044f214:
        add eax,0FFFFFFFCh
    L_0044f217:
        mov dword ptr [ecx+1000h],eax
    L_0044f21d:
        mov al,byte ptr [eax+ecx]
    L_0044f220:
        cmp al,66h
    L_0044f222:
        mov dword ptr [esp+64h],edx
    L_0044f226:
        je short L_0044f234
    L_0044f228:
        cmp al,69h
    L_0044f22a:
        jne short L_0044f234
    L_0044f22c:
        fild dword ptr [esp+64h]
    L_0044f230:
        fstp dword ptr [esp+64h]
    L_0044f234:
        fld dword ptr [esp+64h]
    L_0044f238:
        mov dword ptr [esp+14h],1
    L_0044f240:
        fcomp dword ptr [esp+6Ch]
    L_0044f244:
        fnstsw ax
    L_0044f246:
        test ah,41h
    L_0044f249:
        jnp asm_target_0044f05c
    L_0044f24f:
        lea eax,[esp+14h]
    L_0044f253:
        push eax
    L_0044f254:
        mov dl,69h
    L_0044f256:
        mov eax,ecx
    L_0044f258:
        push 4
    L_0044f25a:
        mov dword ptr [esp+1Ch],ebp
    L_0044f25e:
        call asm_FUN_004505b0_004505b0
    L_0044f263:
        jmp asm_target_0044fb77
    L_0044f268:
        mov eax,dword ptr [esi+1008h]
    L_0044f26e:
        lea ecx,[esi+8]
    L_0044f271:
        add eax,0FFFFFFFCh
    L_0044f274:
        cmp eax,ebp
    L_0044f276:
        jl short L_0044f2a1
    L_0044f278:
        mov dword ptr [ecx+1000h],eax
    L_0044f27e:
        mov edx,dword ptr [eax+ecx]
    L_0044f281:
        add eax,0FFFFFFFCh
    L_0044f284:
        mov dword ptr [ecx+1000h],eax
    L_0044f28a:
        mov al,byte ptr [eax+ecx]
    L_0044f28d:
        cmp al,66h
    L_0044f28f:
        mov dword ptr [esp+7Ch],edx
    L_0044f293:
        je short L_0044f2a1
    L_0044f295:
        cmp al,69h
    L_0044f297:
        jne short L_0044f2a1
    L_0044f299:
        fild dword ptr [esp+7Ch]
    L_0044f29d:
        fstp dword ptr [esp+7Ch]
    L_0044f2a1:
        mov eax,dword ptr [ecx+1000h]
    L_0044f2a7:
        add eax,0FFFFFFFCh
    L_0044f2aa:
        cmp eax,ebp
    L_0044f2ac:
        jl short L_0044f2d7
    L_0044f2ae:
        mov dword ptr [ecx+1000h],eax
    L_0044f2b4:
        mov edx,dword ptr [eax+ecx]
    L_0044f2b7:
        add eax,0FFFFFFFCh
    L_0044f2ba:
        mov dword ptr [ecx+1000h],eax
    L_0044f2c0:
        mov al,byte ptr [eax+ecx]
    L_0044f2c3:
        cmp al,66h
    L_0044f2c5:
        mov dword ptr [esp+74h],edx
    L_0044f2c9:
        je short L_0044f2d7
    L_0044f2cb:
        cmp al,69h
    L_0044f2cd:
        jne short L_0044f2d7
    L_0044f2cf:
        fild dword ptr [esp+74h]
    L_0044f2d3:
        fstp dword ptr [esp+74h]
    L_0044f2d7:
        fld dword ptr [esp+74h]
    L_0044f2db:
        mov dword ptr [esp+14h],1
    L_0044f2e3:
        fcomp dword ptr [esp+7Ch]
    L_0044f2e7:
        fnstsw ax
    L_0044f2e9:
        test ah,41h
    L_0044f2ec:
        je asm_target_0044f05c
    L_0044f2f2:
        lea eax,[esp+14h]
    L_0044f2f6:
        push eax
    L_0044f2f7:
        mov dl,69h
    L_0044f2f9:
        mov eax,ecx
    L_0044f2fb:
        push 4
    L_0044f2fd:
        mov dword ptr [esp+1Ch],ebp
    L_0044f301:
        call asm_FUN_004505b0_004505b0
    L_0044f306:
        jmp asm_target_0044fb77
    L_0044f30b:
        mov eax,dword ptr [esi+1008h]
    L_0044f311:
        lea ecx,[esi+8]
    L_0044f314:
        add eax,0FFFFFFFCh
    L_0044f317:
        cmp eax,ebp
    L_0044f319:
        jl short L_0044f34d
    L_0044f31b:
        mov dword ptr [ecx+1000h],eax
    L_0044f321:
        mov edx,dword ptr [eax+ecx]
    L_0044f324:
        add eax,0FFFFFFFCh
    L_0044f327:
        mov dword ptr [ecx+1000h],eax
    L_0044f32d:
        mov al,byte ptr [eax+ecx]
    L_0044f330:
        cmp al,66h
    L_0044f332:
        mov dword ptr [esp+8Ch],edx
    L_0044f339:
        je short L_0044f34d
    L_0044f33b:
        cmp al,69h
    L_0044f33d:
        jne short L_0044f34d
    L_0044f33f:
        fild dword ptr [esp+8Ch]
    L_0044f346:
        fstp dword ptr [esp+8Ch]
    L_0044f34d:
        mov eax,dword ptr [ecx+1000h]
    L_0044f353:
        add eax,0FFFFFFFCh
    L_0044f356:
        cmp eax,ebp
    L_0044f358:
        jl short L_0044f38c
    L_0044f35a:
        mov dword ptr [ecx+1000h],eax
    L_0044f360:
        mov edx,dword ptr [eax+ecx]
    L_0044f363:
        add eax,0FFFFFFFCh
    L_0044f366:
        mov dword ptr [ecx+1000h],eax
    L_0044f36c:
        mov al,byte ptr [eax+ecx]
    L_0044f36f:
        cmp al,66h
    L_0044f371:
        mov dword ptr [esp+84h],edx
    L_0044f378:
        je short L_0044f38c
    L_0044f37a:
        cmp al,69h
    L_0044f37c:
        jne short L_0044f38c
    L_0044f37e:
        fild dword ptr [esp+84h]
    L_0044f385:
        fstp dword ptr [esp+84h]
    L_0044f38c:
        fld dword ptr [esp+84h]
    L_0044f393:
        mov dword ptr [esp+14h],1
    L_0044f39b:
        fcomp dword ptr [esp+8Ch]
    L_0044f3a2:
        fnstsw ax
    L_0044f3a4:
        test ah,1
    L_0044f3a7:
        je asm_target_0044f05c
    L_0044f3ad:
        lea eax,[esp+14h]
    L_0044f3b1:
        push eax
    L_0044f3b2:
        mov dl,69h
    L_0044f3b4:
        mov eax,ecx
    L_0044f3b6:
        push 4
    L_0044f3b8:
        mov dword ptr [esp+1Ch],ebp
    L_0044f3bc:
        call asm_FUN_004505b0_004505b0
    L_0044f3c1:
        jmp asm_target_0044fb77
    L_0044f3c6:
        mov eax,dword ptr [esi+1008h]
    L_0044f3cc:
        lea ecx,[esi+8]
    L_0044f3cf:
        add eax,0FFFFFFFCh
    L_0044f3d2:
        cmp eax,ebp
    L_0044f3d4:
        jl short L_0044f408
    L_0044f3d6:
        mov dword ptr [ecx+1000h],eax
    L_0044f3dc:
        mov edx,dword ptr [eax+ecx]
    L_0044f3df:
        add eax,0FFFFFFFCh
    L_0044f3e2:
        mov dword ptr [ecx+1000h],eax
    L_0044f3e8:
        mov al,byte ptr [eax+ecx]
    L_0044f3eb:
        cmp al,66h
    L_0044f3ed:
        mov dword ptr [esp+94h],edx
    L_0044f3f4:
        je short L_0044f408
    L_0044f3f6:
        cmp al,69h
    L_0044f3f8:
        jne short L_0044f408
    L_0044f3fa:
        fild dword ptr [esp+94h]
    L_0044f401:
        fstp dword ptr [esp+94h]
    L_0044f408:
        fld dword ptr [data_00470b04]
    L_0044f40e:
        mov dword ptr [esp+14h],1
    L_0044f416:
        fld dword ptr [esp+94h]
    L_0044f41d:
        fucompp
    L_0044f41f:
        fnstsw ax
    L_0044f421:
        test ah,44h
    L_0044f424:
        jnp asm_target_0044f05c
    L_0044f42a:
        lea eax,[esp+14h]
    L_0044f42e:
        push eax
    L_0044f42f:
        mov dl,69h
    L_0044f431:
        mov eax,ecx
    L_0044f433:
        push 4
    L_0044f435:
        mov dword ptr [esp+1Ch],ebp
    L_0044f439:
        call asm_FUN_004505b0_004505b0
    L_0044f43e:
        jmp asm_target_0044fb77
    L_0044f443:
        mov eax,dword ptr [esi+1008h]
    L_0044f449:
        lea edi,[esi+8]
    L_0044f44c:
        add eax,0FFFFFFFCh
    L_0044f44f:
        cmp eax,ebp
    L_0044f451:
        jl short L_0044f485
    L_0044f453:
        mov dword ptr [edi+1000h],eax
    L_0044f459:
        mov ecx,dword ptr [eax+edi]
    L_0044f45c:
        add eax,0FFFFFFFCh
    L_0044f45f:
        mov dword ptr [esp+0A4h],ecx
    L_0044f466:
        mov dword ptr [edi+1000h],eax
    L_0044f46c:
        cmp byte ptr [eax+edi],66h
    L_0044f470:
        jne short L_0044f485
    L_0044f472:
        fld dword ptr [esp+0A4h]
    L_0044f479:
        call asm_FUN_00463b2c_00463b2c
    L_0044f47e:
        mov dword ptr [esp+0A4h],eax
    L_0044f485:
        mov eax,dword ptr [edi+1000h]
    L_0044f48b:
        add eax,0FFFFFFFCh
    L_0044f48e:
        cmp eax,ebp
    L_0044f490:
        jl short L_0044f4c4
    L_0044f492:
        mov dword ptr [edi+1000h],eax
    L_0044f498:
        mov edx,dword ptr [eax+edi]
    L_0044f49b:
        add eax,0FFFFFFFCh
    L_0044f49e:
        mov dword ptr [edi+1000h],eax
    L_0044f4a4:
        cmp byte ptr [eax+edi],66h
    L_0044f4a8:
        mov dword ptr [esp+9Ch],edx
    L_0044f4af:
        jne short L_0044f4c4
    L_0044f4b1:
        fld dword ptr [esp+9Ch]
    L_0044f4b8:
        call asm_FUN_00463b2c_00463b2c
    L_0044f4bd:
        mov dword ptr [esp+9Ch],eax
    L_0044f4c4:
        cmp dword ptr [esp+9Ch],ebp
    L_0044f4cb:
        jne short L_0044f4da
    L_0044f4cd:
        cmp dword ptr [esp+0A4h],ebp
    L_0044f4d4:
        mov dword ptr [esp+14h],ebp
    L_0044f4d8:
        je short L_0044f4e2
    L_0044f4da:
        mov dword ptr [esp+14h],1
    L_0044f4e2:
        lea eax,[esp+14h]
    L_0044f4e6:
        push eax
    L_0044f4e7:
        mov dl,69h
    L_0044f4e9:
        mov eax,edi
    L_0044f4eb:
        push 4
    L_0044f4ed:
        call asm_FUN_004505b0_004505b0
    L_0044f4f2:
        jmp asm_target_0044fb77
    L_0044f4f7:
        mov eax,dword ptr [esi+1008h]
    L_0044f4fd:
        lea edi,[esi+8]
    L_0044f500:
        add eax,0FFFFFFFCh
    L_0044f503:
        cmp eax,ebp
    L_0044f505:
        jl short L_0044f539
    L_0044f507:
        mov dword ptr [edi+1000h],eax
    L_0044f50d:
        mov ecx,dword ptr [eax+edi]
    L_0044f510:
        add eax,0FFFFFFFCh
    L_0044f513:
        mov dword ptr [esp+0B4h],ecx
    L_0044f51a:
        mov dword ptr [edi+1000h],eax
    L_0044f520:
        cmp byte ptr [eax+edi],66h
    L_0044f524:
        jne short L_0044f539
    L_0044f526:
        fld dword ptr [esp+0B4h]
    L_0044f52d:
        call asm_FUN_00463b2c_00463b2c
    L_0044f532:
        mov dword ptr [esp+0B4h],eax
    L_0044f539:
        mov eax,dword ptr [edi+1000h]
    L_0044f53f:
        add eax,0FFFFFFFCh
    L_0044f542:
        cmp eax,ebp
    L_0044f544:
        jl short L_0044f578
    L_0044f546:
        mov dword ptr [edi+1000h],eax
    L_0044f54c:
        mov edx,dword ptr [eax+edi]
    L_0044f54f:
        add eax,0FFFFFFFCh
    L_0044f552:
        mov dword ptr [edi+1000h],eax
    L_0044f558:
        cmp byte ptr [eax+edi],66h
    L_0044f55c:
        mov dword ptr [esp+0ACh],edx
    L_0044f563:
        jne short L_0044f578
    L_0044f565:
        fld dword ptr [esp+0ACh]
    L_0044f56c:
        call asm_FUN_00463b2c_00463b2c
    L_0044f571:
        mov dword ptr [esp+0ACh],eax
    L_0044f578:
        cmp dword ptr [esp+0ACh],ebp
    L_0044f57f:
        je short L_0044f592
    L_0044f581:
        cmp dword ptr [esp+0B4h],ebp
    L_0044f588:
        mov dword ptr [esp+14h],1
    L_0044f590:
        jne short L_0044f596
    L_0044f592:
        mov dword ptr [esp+14h],ebp
    L_0044f596:
        lea eax,[esp+14h]
    L_0044f59a:
        push eax
    L_0044f59b:
        mov dl,69h
    L_0044f59d:
        mov eax,edi
    L_0044f59f:
        push 4
    L_0044f5a1:
        call asm_FUN_004505b0_004505b0
    L_0044f5a6:
        jmp asm_target_0044fb77
    L_0044f5ab:
        mov eax,dword ptr [esi+1008h]
    L_0044f5b1:
        lea edi,[esi+8]
    L_0044f5b4:
        add eax,0FFFFFFFCh
    L_0044f5b7:
        cmp eax,ebp
    L_0044f5b9:
        jl short L_0044f5ed
    L_0044f5bb:
        mov dword ptr [edi+1000h],eax
    L_0044f5c1:
        mov ecx,dword ptr [eax+edi]
    L_0044f5c4:
        add eax,0FFFFFFFCh
    L_0044f5c7:
        mov dword ptr [esp+0C4h],ecx
    L_0044f5ce:
        mov dword ptr [edi+1000h],eax
    L_0044f5d4:
        cmp byte ptr [eax+edi],66h
    L_0044f5d8:
        jne short L_0044f5ed
    L_0044f5da:
        fld dword ptr [esp+0C4h]
    L_0044f5e1:
        call asm_FUN_00463b2c_00463b2c
    L_0044f5e6:
        mov dword ptr [esp+0C4h],eax
    L_0044f5ed:
        mov eax,dword ptr [edi+1000h]
    L_0044f5f3:
        add eax,0FFFFFFFCh
    L_0044f5f6:
        cmp eax,ebp
    L_0044f5f8:
        jl short L_0044f62c
    L_0044f5fa:
        mov dword ptr [edi+1000h],eax
    L_0044f600:
        mov edx,dword ptr [eax+edi]
    L_0044f603:
        add eax,0FFFFFFFCh
    L_0044f606:
        mov dword ptr [edi+1000h],eax
    L_0044f60c:
        cmp byte ptr [eax+edi],66h
    L_0044f610:
        mov dword ptr [esp+0BCh],edx
    L_0044f617:
        jne short L_0044f62c
    L_0044f619:
        fld dword ptr [esp+0BCh]
    L_0044f620:
        call asm_FUN_00463b2c_00463b2c
    L_0044f625:
        mov dword ptr [esp+0BCh],eax
    L_0044f62c:
        mov eax,dword ptr [esp+0BCh]
    L_0044f633:
        xor eax,dword ptr [esp+0C4h]
    L_0044f63a:
        lea ecx,[esp+10h]
    L_0044f63e:
        push ecx
    L_0044f63f:
        mov dword ptr [esp+14h],eax
    L_0044f643:
        mov dl,69h
    L_0044f645:
        mov eax,edi
    L_0044f647:
        push 4
    L_0044f649:
        call asm_FUN_004505b0_004505b0
    L_0044f64e:
        jmp asm_target_0044fb77
    L_0044f653:
        mov eax,dword ptr [esi+1008h]
    L_0044f659:
        lea edi,[esi+8]
    L_0044f65c:
        add eax,0FFFFFFFCh
    L_0044f65f:
        cmp eax,ebp
    L_0044f661:
        jl short L_0044f695
    L_0044f663:
        mov dword ptr [edi+1000h],eax
    L_0044f669:
        mov edx,dword ptr [eax+edi]
    L_0044f66c:
        add eax,0FFFFFFFCh
    L_0044f66f:
        mov dword ptr [edi+1000h],eax
    L_0044f675:
        cmp byte ptr [eax+edi],66h
    L_0044f679:
        mov dword ptr [esp+0D4h],edx
    L_0044f680:
        jne short L_0044f695
    L_0044f682:
        fld dword ptr [esp+0D4h]
    L_0044f689:
        call asm_FUN_00463b2c_00463b2c
    L_0044f68e:
        mov dword ptr [esp+0D4h],eax
    L_0044f695:
        mov eax,dword ptr [edi+1000h]
    L_0044f69b:
        add eax,0FFFFFFFCh
    L_0044f69e:
        cmp eax,ebp
    L_0044f6a0:
        jl short L_0044f6d4
    L_0044f6a2:
        mov dword ptr [edi+1000h],eax
    L_0044f6a8:
        mov ecx,dword ptr [eax+edi]
    L_0044f6ab:
        add eax,0FFFFFFFCh
    L_0044f6ae:
        mov dword ptr [esp+0CCh],ecx
    L_0044f6b5:
        mov dword ptr [edi+1000h],eax
    L_0044f6bb:
        cmp byte ptr [eax+edi],66h
    L_0044f6bf:
        jne short L_0044f6d4
    L_0044f6c1:
        fld dword ptr [esp+0CCh]
    L_0044f6c8:
        call asm_FUN_00463b2c_00463b2c
    L_0044f6cd:
        mov dword ptr [esp+0CCh],eax
    L_0044f6d4:
        mov edx,dword ptr [esp+0CCh]
    L_0044f6db:
        or edx,dword ptr [esp+0D4h]
    L_0044f6e2:
        lea eax,[esp+10h]
    L_0044f6e6:
        push eax
    L_0044f6e7:
        mov dword ptr [esp+14h],edx
    L_0044f6eb:
        mov dl,69h
    L_0044f6ed:
        mov eax,edi
    L_0044f6ef:
        push 4
    L_0044f6f1:
        call asm_FUN_004505b0_004505b0
    L_0044f6f6:
        jmp asm_target_0044fb77
    L_0044f6fb:
        mov eax,dword ptr [esi+1008h]
    L_0044f701:
        lea edi,[esi+8]
    L_0044f704:
        add eax,0FFFFFFFCh
    L_0044f707:
        cmp eax,ebp
    L_0044f709:
        jl short L_0044f73d
    L_0044f70b:
        mov dword ptr [edi+1000h],eax
    L_0044f711:
        mov ecx,dword ptr [eax+edi]
    L_0044f714:
        add eax,0FFFFFFFCh
    L_0044f717:
        mov dword ptr [esp+0E4h],ecx
    L_0044f71e:
        mov dword ptr [edi+1000h],eax
    L_0044f724:
        cmp byte ptr [edi+eax],66h
    L_0044f728:
        jne short L_0044f73d
    L_0044f72a:
        fld dword ptr [esp+0E4h]
    L_0044f731:
        call asm_FUN_00463b2c_00463b2c
    L_0044f736:
        mov dword ptr [esp+0E4h],eax
    L_0044f73d:
        mov eax,dword ptr [edi+1000h]
    L_0044f743:
        add eax,0FFFFFFFCh
    L_0044f746:
        cmp eax,ebp
    L_0044f748:
        jl short L_0044f77c
    L_0044f74a:
        mov dword ptr [edi+1000h],eax
    L_0044f750:
        mov edx,dword ptr [eax+edi]
    L_0044f753:
        add eax,0FFFFFFFCh
    L_0044f756:
        mov dword ptr [edi+1000h],eax
    L_0044f75c:
        cmp byte ptr [edi+eax],66h
    L_0044f760:
        mov dword ptr [esp+0DCh],edx
    L_0044f767:
        jne short L_0044f77c
    L_0044f769:
        fld dword ptr [esp+0DCh]
    L_0044f770:
        call asm_FUN_00463b2c_00463b2c
    L_0044f775:
        mov dword ptr [esp+0DCh],eax
    L_0044f77c:
        mov eax,dword ptr [esp+0DCh]
    L_0044f783:
        and eax,dword ptr [esp+0E4h]
    L_0044f78a:
        lea ecx,[esp+10h]
    L_0044f78e:
        push ecx
    L_0044f78f:
        mov dword ptr [esp+14h],eax
    L_0044f793:
        mov dl,69h
    L_0044f795:
        mov eax,edi
    L_0044f797:
        push 4
    L_0044f799:
        call asm_FUN_004505b0_004505b0
    L_0044f79e:
        jmp asm_target_0044fb77
    L_0044f7a3:
        mov eax,dword ptr [esi+1008h]
    L_0044f7a9:
        lea edi,[esi+8]
    L_0044f7ac:
        lea ecx,[eax-4]
    L_0044f7af:
        cmp ecx,ebp
    L_0044f7b1:
        jl short L_0044f7f3
    L_0044f7b3:
        mov dword ptr [edi+1000h],ecx
    L_0044f7b9:
        mov eax,dword ptr [ecx+edi]
    L_0044f7bc:
        add ecx,0FFFFFFFCh
    L_0044f7bf:
        mov dword ptr [edi+1000h],ecx
    L_0044f7c5:
        cmp byte ptr [edi+ecx],66h
    L_0044f7c9:
        mov dword ptr [esp+34h],eax
    L_0044f7cd:
        jne short L_0044f7f7
    L_0044f7cf:
        fld dword ptr [esp+34h]
    L_0044f7d3:
        call asm_FUN_00463b2c_00463b2c
    L_0044f7d8:
        lea edx,[esp+34h]
    L_0044f7dc:
        neg eax
    L_0044f7de:
        push edx
    L_0044f7df:
        mov dword ptr [esp+38h],eax
    L_0044f7e3:
        mov dl,69h
    L_0044f7e5:
        mov eax,edi
    L_0044f7e7:
        push 4
    L_0044f7e9:
        call asm_FUN_004505b0_004505b0
    L_0044f7ee:
        jmp asm_target_0044fb77
    L_0044f7f3:
        mov eax,dword ptr [esp+34h]
    L_0044f7f7:
        lea edx,[esp+34h]
    L_0044f7fb:
        neg eax
    L_0044f7fd:
        push edx
    L_0044f7fe:
        mov dword ptr [esp+38h],eax
    L_0044f802:
        mov dl,69h
    L_0044f804:
        mov eax,edi
    L_0044f806:
        push 4
    L_0044f808:
        call asm_FUN_004505b0_004505b0
    L_0044f80d:
        jmp asm_target_0044fb77
    L_0044f812:
        mov ecx,dword ptr [esi+1008h]
    L_0044f818:
        lea eax,[esi+8]
    L_0044f81b:
        add ecx,0FFFFFFFCh
    L_0044f81e:
        cmp ecx,ebp
    L_0044f820:
        jl short L_0044f84d
    L_0044f822:
        mov dword ptr [eax+1000h],ecx
    L_0044f828:
        mov edx,dword ptr [ecx+eax]
    L_0044f82b:
        add ecx,0FFFFFFFCh
    L_0044f82e:
        mov dword ptr [eax+1000h],ecx
    L_0044f834:
        mov cl,byte ptr [eax+ecx]
    L_0044f837:
        cmp cl,66h
    L_0044f83a:
        mov dword ptr [esp+1Ch],edx
    L_0044f83e:
        je short L_0044f851
    L_0044f840:
        cmp cl,69h
    L_0044f843:
        jne short L_0044f851
    L_0044f845:
        fild dword ptr [esp+1Ch]
    L_0044f849:
        fstp dword ptr [esp+1Ch]
    L_0044f84d:
        mov edx,dword ptr [esp+1Ch]
    L_0044f851:
        neg edx
    L_0044f853:
        lea ecx,[esp+1Ch]
    L_0044f857:
        push ecx
    L_0044f858:
        mov dword ptr [esp+20h],edx
    L_0044f85c:
        mov dl,66h
    L_0044f85e:
        push 4
    L_0044f860:
        call asm_FUN_004505b0_004505b0
    L_0044f865:
        jmp asm_target_0044fb77
    L_0044f86a:
        push ebp
    L_0044f86b:
        mov edx,esi
    L_0044f86d:
        call asm_ECL_ResolveIntOperand_0044fdb0
    L_0044f872:
        mov edi,eax
    L_0044f874:
        xor ecx,ecx
    L_0044f876:
        mov dword ptr [esp+10h],edi
    L_0044f87a:
        call asm_ECL_ResolveVariableValue_00450030
    L_0044f87f:
        lea edx,[esp+10h]
    L_0044f883:
        dec edi
    L_0044f884:
        push edx
    L_0044f885:
        mov dword ptr [eax],edi
    L_0044f887:
        lea eax,[esi+8]
    L_0044f88a:
        mov dl,69h
    L_0044f88c:
        push 4
    L_0044f88e:
        call asm_FUN_004505b0_004505b0
    L_0044f893:
        jmp asm_target_0044fb77
    L_0044f898:
        mov ecx,dword ptr [esi+1008h]
    L_0044f89e:
        lea eax,[esi+8]
    L_0044f8a1:
        add ecx,0FFFFFFFCh
    L_0044f8a4:
        cmp ecx,ebp
    L_0044f8a6:
        jl short L_0044f8dc
    L_0044f8a8:
        mov dword ptr [eax+1000h],ecx
    L_0044f8ae:
        mov edx,dword ptr [ecx+eax]
    L_0044f8b1:
        add ecx,0FFFFFFFCh
    L_0044f8b4:
        mov dword ptr [eax+1000h],ecx
    L_0044f8ba:
        mov cl,byte ptr [eax+ecx]
    L_0044f8bd:
        cmp cl,66h
    L_0044f8c0:
        mov dword ptr [esp+0ECh],edx
    L_0044f8c7:
        je short L_0044f8dc
    L_0044f8c9:
        cmp cl,69h
    L_0044f8cc:
        jne short L_0044f8dc
    L_0044f8ce:
        fild dword ptr [esp+0ECh]
    L_0044f8d5:
        fstp dword ptr [esp+0ECh]
    L_0044f8dc:
        fld dword ptr [esp+0ECh]
    L_0044f8e3:
        fsin
    L_0044f8e5:
        jmp short L_0044f934
    L_0044f8e7:
        mov ecx,dword ptr [esi+1008h]
    L_0044f8ed:
        lea eax,[esi+8]
    L_0044f8f0:
        add ecx,0FFFFFFFCh
    L_0044f8f3:
        cmp ecx,ebp
    L_0044f8f5:
        jl short L_0044f92b
    L_0044f8f7:
        mov dword ptr [eax+1000h],ecx
    L_0044f8fd:
        mov edx,dword ptr [eax+ecx]
    L_0044f900:
        add ecx,0FFFFFFFCh
    L_0044f903:
        mov dword ptr [eax+1000h],ecx
    L_0044f909:
        mov cl,byte ptr [eax+ecx]
    L_0044f90c:
        cmp cl,66h
    L_0044f90f:
        mov dword ptr [esp+0F4h],edx
    L_0044f916:
        je short L_0044f92b
    L_0044f918:
        cmp cl,69h
    L_0044f91b:
        jne short L_0044f92b
    L_0044f91d:
        fild dword ptr [esp+0F4h]
    L_0044f924:
        fstp dword ptr [esp+0F4h]
    L_0044f92b:
        fld dword ptr [esp+0F4h]
    L_0044f932:
        fcos
    L_0044f934:
        lea ecx,[esp+10h]
    L_0044f938:
        push ecx
    L_0044f939:
        fstp dword ptr [esp+14h]
    L_0044f93d:
        mov dl,66h
    L_0044f93f:
        push 4
    L_0044f941:
        call asm_FUN_004505b0_004505b0
    L_0044f946:
        jmp asm_target_0044fb77
    L_0044f94b:
        mov ecx,3
    L_0044f950:
        mov eax,esi
    L_0044f952:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044f957:
        push ecx
    L_0044f958:
        mov ecx,2
    L_0044f95d:
        fstp dword ptr [esp]
    L_0044f960:
        mov eax,esi
    L_0044f962:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044f967:
        push ecx
    L_0044f968:
        fstp dword ptr [esp]
    L_0044f96b:
        call asm_Angle_Normalize_0044bc70
    L_0044f970:
        push ecx
    L_0044f971:
        lea ecx,[esp+114h]
    L_0044f978:
        fstp dword ptr [esp]
    L_0044f97b:
        call asm_ECL_SetPolarVector_004501b0
    L_0044f980:
        xor ecx,ecx
    L_0044f982:
        mov eax,esi
    L_0044f984:
        call asm_ECL_ResolveFloatDestination_00450070
    L_0044f989:
        mov edx,dword ptr [esp+10Ch]
    L_0044f990:
        mov dword ptr [eax],edx
    L_0044f992:
        mov ecx,1
    L_0044f997:
        mov eax,esi
    L_0044f999:
        call asm_ECL_ResolveFloatDestination_00450070
    L_0044f99e:
        mov ecx,dword ptr [esp+110h]
    L_0044f9a5:
        mov dword ptr [eax],ecx
    L_0044f9a7:
        jmp asm_target_0044fb77
    L_0044f9ac:
        mov ecx,1
    L_0044f9b1:
        mov eax,esi
    L_0044f9b3:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044f9b8:
        fstp dword ptr [esp+18h]
    L_0044f9bc:
        mov ecx,2
    L_0044f9c1:
        mov eax,esi
    L_0044f9c3:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044f9c8:
        fstp dword ptr [esp+14h]
    L_0044f9cc:
        xor ecx,ecx
    L_0044f9ce:
        mov eax,esi
    L_0044f9d0:
        call asm_ECL_ResolveFloatDestination_00450070
    L_0044f9d5:
        fld dword ptr [esp+14h]
    L_0044f9d9:
        fmul dword ptr [esp+14h]
    L_0044f9dd:
        fld dword ptr [esp+18h]
    L_0044f9e1:
        fmul dword ptr [esp+18h]
    L_0044f9e5:
        faddp st(1),st
    L_0044f9e7:
        fstp dword ptr [eax]
    L_0044f9e9:
        jmp asm_target_0044fb77
    L_0044f9ee:
        xor ecx,ecx
    L_0044f9f0:
        mov eax,esi
    L_0044f9f2:
        call asm_ECL_ResolveFloatDestination_00450070
    L_0044f9f7:
        mov edi,eax
    L_0044f9f9:
        xor ecx,ecx
    L_0044f9fb:
        mov eax,esi
    L_0044f9fd:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044fa02:
        push ecx
    L_0044fa03:
        fstp dword ptr [esp]
    L_0044fa06:
        call asm_Angle_Normalize_0044bc70
    L_0044fa0b:
        fstp dword ptr [edi]
    L_0044fa0d:
        jmp asm_target_0044fb77
    L_0044fa12:
        mov ecx,2
    L_0044fa17:
        mov eax,esi
    L_0044fa19:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044fa1e:
        fstp dword ptr [esp+10h]
    L_0044fa22:
        xor ecx,ecx
    L_0044fa24:
        mov eax,esi
    L_0044fa26:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044fa2b:
        fsubr dword ptr [esp+10h]
    L_0044fa2f:
        mov ecx,3
    L_0044fa34:
        mov eax,esi
    L_0044fa36:
        fstp dword ptr [esp+14h]
    L_0044fa3a:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044fa3f:
        mov ecx,1
    L_0044fa44:
        fstp dword ptr [esp+10h]
    L_0044fa48:
        mov eax,esi
    L_0044fa4a:
        call asm_ECL_ResolveFloatOperand_0044fe40
    L_0044fa4f:
        fsubr dword ptr [esp+10h]
    L_0044fa53:
        fld dword ptr [esp+14h]
    L_0044fa57:
        xor ecx,ecx
    L_0044fa59:
        mov eax,esi
    L_0044fa5b:
        fpatan
    L_0044fa5d:
        fstp dword ptr [esp+10h]
    L_0044fa61:
        call asm_ECL_ResolveFloatDestination_00450070
    L_0044fa66:
        mov edx,dword ptr [esp+10h]
    L_0044fa6a:
        mov dword ptr [eax],edx
    L_0044fa6c:
        jmp asm_target_0044fb77
    L_0044fa71:
        push 400h
    L_0044fa76:
        add edi,14h
    L_0044fa79:
        call asm_malloc_00452706
    L_0044fa7e:
        add esp,4
    L_0044fa81:
        cmp edi,ebp
    L_0044fa83:
        mov dword ptr [esp+14h],eax
    L_0044fa87:
        mov byte ptr [eax],0
    L_0044fa8a:
        je asm_target_0044fb5d
    L_0044fa90:
        mov ebx,1
    L_0044fa95:
        mov dword ptr [esp+18h],0
    L_0044fa9d:
        mov ebp,6
    L_0044faa2:
        push 25h
    L_0044faa4:
        push edi
    L_0044faa5:
        call asm_FUN_00452730_00452730
    L_0044faaa:
        add esp,8
    L_0044faad:
        test eax,eax
    L_0044faaf:
        mov dword ptr [esp+10h],eax
    L_0044fab3:
        je asm_target_0044fb57
    L_0044fab9:
        mov edx,dword ptr [esp+14h]
    L_0044fabd:
        mov eax,edi
    L_0044fabf:
        sub edx,edi
    L_0044fac1:
        mov cl,byte ptr [eax]
    L_0044fac3:
        mov byte ptr [eax+edx],cl
    L_0044fac6:
        inc eax
    L_0044fac7:
        test cl,cl
    L_0044fac9:
        jne short L_0044fac1
    L_0044facb:
        mov eax,dword ptr [esp+10h]
    L_0044facf:
        mov edx,dword ptr [esp+14h]
    L_0044fad3:
        mov ecx,eax
    L_0044fad5:
        sub ecx,edi
    L_0044fad7:
        mov byte ptr [ecx+edx],0
    L_0044fadb:
        movsx eax,byte ptr [eax+1]
    L_0044fadf:
        sub eax,25h
    L_0044fae2:
        je short L_0044fb4a
    L_0044fae4:
        sub eax,3Fh
    L_0044fae7:
        je short L_0044faee
    L_0044fae9:
        sub eax,2
    L_0044faec:
        jne short L_0044fb4a
    L_0044faee:
        mov ecx,dword ptr [esi+4]
    L_0044faf1:
        mov eax,dword ptr [ecx+10h]
    L_0044faf4:
        mov edx,dword ptr [esp+18h]
    L_0044faf8:
        add edx,eax
    L_0044fafa:
        mov dl,byte ptr [edx+ecx+14h]
    L_0044fafe:
        cmp dl,66h
    L_0044fb01:
        je short L_0044fb21
    L_0044fb03:
        cmp dl,67h
    L_0044fb06:
        je short L_0044fb21
    L_0044fb08:
        cdq
    L_0044fb09:
        and edx,3
    L_0044fb0c:
        add eax,edx
    L_0044fb0e:
        sar eax,2
    L_0044fb11:
        add eax,ebp
    L_0044fb13:
        mov eax,dword ptr [ecx+eax*4]
    L_0044fb16:
        push eax
    L_0044fb17:
        push ebx
    L_0044fb18:
        mov edx,esi
    L_0044fb1a:
        call asm_ECL_ResolveIntValue_0044ff00
    L_0044fb1f:
        jmp short L_0044fb3b
    L_0044fb21:
        cdq
    L_0044fb22:
        and edx,3
    L_0044fb25:
        add eax,edx
    L_0044fb27:
        sar eax,2
    L_0044fb2a:
        add eax,ebp
    L_0044fb2c:
        mov ecx,dword ptr [ecx+eax*4]
    L_0044fb2f:
        push ecx
    L_0044fb30:
        mov eax,esi
    L_0044fb32:
        mov ecx,ebx
    L_0044fb34:
        call asm_ECL_ResolveFloatValue_0044ff80
    L_0044fb39:
        fstp st(0)
    L_0044fb3b:
        mov ecx,dword ptr [esp+18h]
    L_0044fb3f:
        add ecx,8
    L_0044fb42:
        add ebp,2
    L_0044fb45:
        mov dword ptr [esp+18h],ecx
    L_0044fb49:
        inc ebx
    L_0044fb4a:
        mov edi,dword ptr [esp+10h]
    L_0044fb4e:
        add edi,2
    L_0044fb51:
        jne asm_target_0044faa2
    L_0044fb57:
        mov eax,dword ptr [esp+14h]
    L_0044fb5b:
        xor ebp,ebp
    L_0044fb5d:
        push eax
    L_0044fb5e:
        call asm_free_00452422
    L_0044fb63:
        add esp,4
    L_0044fb66:
        jmp short L_0044fb77
    L_0044fb68:
        mov ecx,dword ptr [esi+1014h]
    L_0044fb6e:
        mov edx,dword ptr [ecx]
    L_0044fb70:
        call dword ptr [edx]
    L_0044fb72:
        cmp eax,0FFFFFFFFh
    L_0044fb75:
        je short L_0044fba1
    L_0044fb77:
        mov eax,dword ptr [esi+4]
    L_0044fb7a:
        movzx ecx,word ptr [eax+6]
    L_0044fb7e:
        lea ebx,[esi+4]
    L_0044fb81:
        add ecx,eax
    L_0044fb83:
        mov dword ptr [ebx],ecx
    L_0044fb85:
        mov edx,dword ptr [ebx]
    L_0044fb87:
        fild dword ptr [edx]
    L_0044fb89:
        fcomp dword ptr [esi]
    L_0044fb8b:
        fnstsw ax
    L_0044fb8d:
        test ah,41h
    L_0044fb90:
        jnp asm_FUN_0044e1a0_part_0044e1e0
    L_0044fb96:
        fld dword ptr [esp+11Ch]
    L_0044fb9d:
        fadd dword ptr [esi]
    L_0044fb9f:
        fstp dword ptr [esi]
    L_0044fba1:
        pop edi
    L_0044fba2:
        pop esi
    L_0044fba3:
        pop ebp
    L_0044fba4:
        xor eax,eax
    L_0044fba6:
        pop ebx
    L_0044fba7:
        add esp,108h
    L_0044fbad:
        ret 4
    L_0044fbb0:
        mov dword ptr [ebx],ebp
    L_0044fbb2:
        pop edi
    L_0044fbb3:
        pop esi
    L_0044fbb4:
        pop ebp
    L_0044fbb5:
        or eax,0FFFFFFFFh
    L_0044fbb8:
        pop ebx
    L_0044fbb9:
        add esp,108h
    L_0044fbbf:
        ret 4
    }
}

// The operand table the interpreter resolves a script operand through: +0x8 is
// the bitmap of slots holding an indirect reference, +0x10 the slot array.
struct EclOperandTable {
    unsigned char pad_00[8];
    unsigned short indirect_mask;      // +0x08
    unsigned char pad_0A[6];
    int slots[1];                      // +0x10
};

// Accessor object reached through +0x1014. Its second virtual entry resolves a
// slot that refers to a live script variable.
struct EclVariableContext {
    virtual void Reserved();           // +0x00
    virtual int ResolveSlot(int slot); // +0x04
};

// The interpreter's value stack and the cursor words that address slots inside
// it. The frame embeds it, so every access goes through this member.
struct EclStack {
    unsigned char data[0x1000];        // +0x0000
    int stack_pointer;                 // +0x1000
    int frame_base;                    // +0x1004
    void* variable_slots;              // +0x1008
    EclVariableContext* context;       // +0x100C
};

struct EclFrame {
    unsigned char pad_00[4];
    EclOperandTable* operand_table;    // +0x0004
    EclStack stack;                    // +0x0008
};

// 0x0044FDB0..0x0044FE3F: ?ECL_ResolveIntOperand@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveIntOperand_0044fdb0() {
    __asm {
    L_0044fdb0:
        mov eax,dword ptr [esp+4]
    L_0044fdb4:
        push ebx
    L_0044fdb5:
        push esi
    L_0044fdb6:
        mov esi,dword ptr [edx+4]
    L_0044fdb9:
        mov ebx,1
    L_0044fdbe:
        mov ecx,eax
    L_0044fdc0:
        push edi
    L_0044fdc1:
        movzx edi,word ptr [esi+8]
    L_0044fdc5:
        shl ebx,cl
    L_0044fdc7:
        test edi,ebx
    L_0044fdc9:
        je short L_0044fe36
    L_0044fdcb:
        mov esi,dword ptr [esi+eax*4+10h]
    L_0044fdcf:
        test esi,esi
    L_0044fdd1:
        jl short L_0044fde5
    L_0044fdd3:
        mov eax,dword ptr [edx+100Ch]
    L_0044fdd9:
        pop edi
    L_0044fdda:
        add eax,esi
    L_0044fddc:
        mov eax,dword ptr [eax+edx+8]
    L_0044fde0:
        pop esi
    L_0044fde1:
        pop ebx
    L_0044fde2:
        ret 4
    L_0044fde5:
        cmp esi,0FFFFFFFFh
    L_0044fde8:
        jne short L_0044fe24
    L_0044fdea:
        mov ecx,dword ptr [edx+1008h]
    L_0044fdf0:
        lea esi,[ecx-4]
    L_0044fdf3:
        test esi,esi
    L_0044fdf5:
        jl short L_0044fe3a
    L_0044fdf7:
        mov dword ptr [edx+1008h],esi
    L_0044fdfd:
        mov eax,dword ptr [esi+edx+8]
    L_0044fe01:
        add esi,0FFFFFFFCh
    L_0044fe04:
        mov dword ptr [edx+1008h],esi
    L_0044fe0a:
        cmp byte ptr [esi+edx+8],66h
    L_0044fe0f:
        mov dword ptr [esp+10h],eax
    L_0044fe13:
        jne short L_0044fe3a
    L_0044fe15:
        fld dword ptr [esp+10h]
    L_0044fe19:
        call asm_FUN_00463b2c_00463b2c
    L_0044fe1e:
        pop edi
    L_0044fe1f:
        pop esi
    L_0044fe20:
        pop ebx
    L_0044fe21:
        ret 4
    L_0044fe24:
        mov ecx,dword ptr [edx+1014h]
    L_0044fe2a:
        mov edx,dword ptr [ecx]
    L_0044fe2c:
        push esi
    L_0044fe2d:
        call dword ptr [edx+4]
    L_0044fe30:
        pop edi
    L_0044fe31:
        pop esi
    L_0044fe32:
        pop ebx
    L_0044fe33:
        ret 4
    L_0044fe36:
        mov eax,dword ptr [esi+eax*4+10h]
    L_0044fe3a:
        pop edi
    L_0044fe3b:
        pop esi
    L_0044fe3c:
        pop ebx
    L_0044fe3d:
        ret 4
    }
}

// 0x0044FE40..0x0044FEF6: ?ECL_ResolveFloatOperand@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveFloatOperand_0044fe40() {
    __asm {
    L_0044fe40:
        push ecx
    L_0044fe41:
        push esi
    L_0044fe42:
        push edi
    L_0044fe43:
        mov esi,eax
    L_0044fe45:
        mov edx,dword ptr [esi+4]
    L_0044fe48:
        movzx eax,word ptr [edx+8]
    L_0044fe4c:
        mov edi,1
    L_0044fe51:
        shl edi,cl
    L_0044fe53:
        test eax,edi
    L_0044fe55:
        je asm_target_0044feef
    L_0044fe5b:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fe5f:
        fcomp dword ptr [data_00470b04]
    L_0044fe65:
        fnstsw ax
    L_0044fe67:
        test ah,1
    L_0044fe6a:
        jne short L_0044fe83
    L_0044fe6c:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fe70:
        call asm_FUN_00463b2c_00463b2c
    L_0044fe75:
        add eax,dword ptr [esi+100Ch]
    L_0044fe7b:
        fld dword ptr [eax+esi+8]
    L_0044fe7f:
        pop edi
    L_0044fe80:
        pop esi
    L_0044fe81:
        pop ecx
    L_0044fe82:
        ret
    L_0044fe83:
        fld dword ptr [data_00470b60]
    L_0044fe89:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fe8d:
        fucompp
    L_0044fe8f:
        fnstsw ax
    L_0044fe91:
        test ah,44h
    L_0044fe94:
        jp short L_0044fed4
    L_0044fe96:
        mov eax,dword ptr [esi+1008h]
    L_0044fe9c:
        add eax,0FFFFFFFCh
    L_0044fe9f:
        js short L_0044fecc
    L_0044fea1:
        mov dword ptr [esi+1008h],eax
    L_0044fea7:
        mov ecx,dword ptr [eax+esi+8]
    L_0044feab:
        add eax,0FFFFFFFCh
    L_0044feae:
        mov dword ptr [esi+1008h],eax
    L_0044feb4:
        mov al,byte ptr [eax+esi+8]
    L_0044feb8:
        cmp al,66h
    L_0044feba:
        mov dword ptr [esp+8],ecx
    L_0044febe:
        je short L_0044fecc
    L_0044fec0:
        cmp al,69h
    L_0044fec2:
        jne short L_0044fecc
    L_0044fec4:
        fild dword ptr [esp+8]
    L_0044fec8:
        pop edi
    L_0044fec9:
        pop esi
    L_0044feca:
        pop ecx
    L_0044fecb:
        ret
    L_0044fecc:
        fld dword ptr [esp+8]
    L_0044fed0:
        pop edi
    L_0044fed1:
        pop esi
    L_0044fed2:
        pop ecx
    L_0044fed3:
        ret
    L_0044fed4:
        mov esi,dword ptr [esi+1014h]
    L_0044feda:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fede:
        mov edi,dword ptr [esi]
    L_0044fee0:
        call asm_FUN_00463b2c_00463b2c
    L_0044fee5:
        push eax
    L_0044fee6:
        mov ecx,esi
    L_0044fee8:
        call dword ptr [edi+0Ch]
    L_0044feeb:
        pop edi
    L_0044feec:
        pop esi
    L_0044feed:
        pop ecx
    L_0044feee:
        ret
    L_0044feef:
        fld dword ptr [edx+ecx*4+10h]
    L_0044fef3:
        pop edi
    L_0044fef4:
        pop esi
    L_0044fef5:
        pop ecx
    L_0044fef6:
        ret
    }
}

// 0x0044FF00..0x0044FF7B: ?ECL_ResolveIntValue@@
// Resolves the selector of one operand to the value it carries, following the
// indirect table and the tag byte the same way the operand resolver does.
int __fastcall ECL_ResolveIntValue_0044ff00(int unused, EclFrame* frame, int selector, int value) {
    EclOperandTable* table = frame->operand_table;
    unsigned short mask = table->indirect_mask;
    int result = value;
    if ((mask & (1 << selector)) != 0) {
        if (value >= 0) {
            EclStack* stack = &frame->stack;
            result = *(int*)&stack->data[stack->frame_base + value];
        } else if (value == -1) {
            if (frame->stack.stack_pointer - 4 >= 0) {
                frame->stack.stack_pointer -= 4;
                int raw = *(int*)&frame->stack.data[frame->stack.stack_pointer];
                frame->stack.stack_pointer -= 4;
                float typed = *(float*)&raw;
                if (frame->stack.data[frame->stack.stack_pointer] == 0x66)
                    result = (int)typed;
                else
                    result = raw;
            }
        } else {
            result = frame->stack.context->ResolveSlot(value);
        }
    }
    return result;
}

// 0x0044FF80..0x0045002A: ?ECL_ResolveFloatValue@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveFloatValue_0044ff80() {
    __asm {
    L_0044ff80:
        push esi
    L_0044ff81:
        mov esi,eax
    L_0044ff83:
        mov eax,dword ptr [esi+4]
    L_0044ff86:
        movzx edx,word ptr [eax+8]
    L_0044ff8a:
        mov eax,1
    L_0044ff8f:
        shl eax,cl
    L_0044ff91:
        test edx,eax
    L_0044ff93:
        je short L_00450006
    L_0044ff95:
        fld dword ptr [esp+8]
    L_0044ff99:
        fcomp dword ptr [data_00470b04]
    L_0044ff9f:
        fnstsw ax
    L_0044ffa1:
        test ah,1
    L_0044ffa4:
        jne short L_0044ffbd
    L_0044ffa6:
        fld dword ptr [esp+8]
    L_0044ffaa:
        call asm_FUN_00463b2c_00463b2c
    L_0044ffaf:
        add eax,dword ptr [esi+100Ch]
    L_0044ffb5:
        fld dword ptr [eax+esi+8]
    L_0044ffb9:
        pop esi
    L_0044ffba:
        ret 4
    L_0044ffbd:
        fld dword ptr [data_00470b60]
    L_0044ffc3:
        fld dword ptr [esp+8]
    L_0044ffc7:
        fucompp
    L_0044ffc9:
        fnstsw ax
    L_0044ffcb:
        test ah,44h
    L_0044ffce:
        jp short L_0045000e
    L_0044ffd0:
        mov eax,dword ptr [esi+1008h]
    L_0044ffd6:
        add eax,0FFFFFFFCh
    L_0044ffd9:
        js short L_00450006
    L_0044ffdb:
        mov dword ptr [esi+1008h],eax
    L_0044ffe1:
        mov ecx,dword ptr [eax+esi+8]
    L_0044ffe5:
        add eax,0FFFFFFFCh
    L_0044ffe8:
        mov dword ptr [esi+1008h],eax
    L_0044ffee:
        mov al,byte ptr [eax+esi+8]
    L_0044fff2:
        cmp al,66h
    L_0044fff4:
        mov dword ptr [esp+8],ecx
    L_0044fff8:
        je short L_00450006
    L_0044fffa:
        cmp al,69h
    L_0044fffc:
        jne short L_00450006
    L_0044fffe:
        fild dword ptr [esp+8]
    L_00450002:
        fstp dword ptr [esp+8]
    L_00450006:
        fld dword ptr [esp+8]
    L_0045000a:
        pop esi
    L_0045000b:
        ret 4
    L_0045000e:
        mov esi,dword ptr [esi+1014h]
    L_00450014:
        fld dword ptr [esp+8]
    L_00450018:
        push edi
    L_00450019:
        mov edi,dword ptr [esi]
    L_0045001b:
        call asm_FUN_00463b2c_00463b2c
    L_00450020:
        push eax
    L_00450021:
        mov ecx,esi
    L_00450023:
        call dword ptr [edi+0Ch]
    L_00450026:
        pop edi
    L_00450027:
        pop esi
    L_00450028:
        ret 4
    }
}

// 0x00450030..0x00450069: ?ECL_ResolveVariableValue@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveVariableValue_00450030() {
    __asm {
    L_00450030:
        mov eax,dword ptr [esi+4]
    L_00450033:
        movzx edx,word ptr [eax+8]
    L_00450037:
        push edi
    L_00450038:
        mov edi,1
    L_0045003d:
        shl edi,cl
    L_0045003f:
        test edx,edi
    L_00450041:
        pop edi
    L_00450042:
        je short L_00450067
    L_00450044:
        mov edx,dword ptr [eax+ecx*4+10h]
    L_00450048:
        test edx,edx
    L_0045004a:
        jl short L_0045005a
    L_0045004c:
        mov eax,dword ptr [esi+100Ch]
    L_00450052:
        lea ecx,[esi+8]
    L_00450055:
        add eax,edx
    L_00450057:
        add eax,ecx
    L_00450059:
        ret
    L_0045005a:
        mov ecx,dword ptr [esi+1014h]
    L_00450060:
        mov eax,dword ptr [ecx]
    L_00450062:
        push edx
    L_00450063:
        call dword ptr [eax+8]
    L_00450066:
        ret
    L_00450067:
        xor eax,eax
    L_00450069:
        ret
    }
}

// 0x00450070..0x004500CC: ?ECL_ResolveFloatDestination@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResolveFloatDestination_00450070() {
    __asm {
    L_00450070:
        push esi
    L_00450071:
        push edi
    L_00450072:
        mov esi,eax
    L_00450074:
        mov edx,dword ptr [esi+4]
    L_00450077:
        movzx eax,word ptr [edx+8]
    L_0045007b:
        mov edi,1
    L_00450080:
        shl edi,cl
    L_00450082:
        test eax,edi
    L_00450084:
        je short L_004500c8
    L_00450086:
        fld dword ptr [edx+ecx*4+10h]
    L_0045008a:
        fcomp dword ptr [data_00470b04]
    L_00450090:
        fld dword ptr [edx+ecx*4+10h]
    L_00450094:
        fnstsw ax
    L_00450096:
        test ah,1
    L_00450099:
        jne short L_004500b2
    L_0045009b:
        add esi,8
    L_0045009e:
        call asm_FUN_00463b2c_00463b2c
    L_004500a3:
        mov ecx,eax
    L_004500a5:
        mov eax,dword ptr [esi+1004h]
    L_004500ab:
        add eax,ecx
    L_004500ad:
        pop edi
    L_004500ae:
        add eax,esi
    L_004500b0:
        pop esi
    L_004500b1:
        ret
    L_004500b2:
        mov esi,dword ptr [esi+1014h]
    L_004500b8:
        mov edi,dword ptr [esi]
    L_004500ba:
        call asm_FUN_00463b2c_00463b2c
    L_004500bf:
        push eax
    L_004500c0:
        mov ecx,esi
    L_004500c2:
        call dword ptr [edi+10h]
    L_004500c5:
        pop edi
    L_004500c6:
        pop esi
    L_004500c7:
        ret
    L_004500c8:
        pop edi
    L_004500c9:
        xor eax,eax
    L_004500cb:
        pop esi
    L_004500cc:
        ret
    }
}

// 0x004500D0..0x0045015D: EclVm_SpawnChild
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EclVm_SpawnChild_004500d0() {
    __asm {
    L_004500d0:
        push ebx
    L_004500d1:
        push esi
    L_004500d2:
        push 1024h
    L_004500d7:
        call asm_operator_new_00452493
    L_004500dc:
        xor ebx,ebx
    L_004500de:
        add esp,4
    L_004500e1:
        cmp eax,ebx
    L_004500e3:
        je short L_004500f5
    L_004500e5:
        mov dword ptr [eax+1008h],ebx
    L_004500eb:
        mov dword ptr [eax+100Ch],ebx
    L_004500f1:
        mov esi,eax
    L_004500f3:
        jmp short L_004500f7
    L_004500f5:
        xor esi,esi
    L_004500f7:
        push 0Ch
    L_004500f9:
        call asm_operator_new_00452493
    L_004500fe:
        mov ecx,dword ptr [esp+10h]
    L_00450102:
        mov dword ptr [esi+1010h],ecx
    L_00450108:
        mov dword ptr [esi+1014h],edi
    L_0045010e:
        mov dword ptr [esi],ebx
    L_00450110:
        mov dword ptr [esi+4],ebx
    L_00450113:
        mov edx,dword ptr [edi+4]
    L_00450116:
        mov cl,byte ptr [edx+101Ch]
    L_0045011c:
        mov byte ptr [esi+101Ch],cl
    L_00450122:
        lea ecx,[edi+1030h]
    L_00450128:
        mov dword ptr [eax],esi
    L_0045012a:
        mov dword ptr [eax+4],ebx
    L_0045012d:
        mov dword ptr [eax+8],ebx
    L_00450130:
        mov edx,dword ptr [ecx+4]
    L_00450133:
        add esp,4
    L_00450136:
        cmp edx,ebx
    L_00450138:
        je short L_00450143
    L_0045013a:
        mov dword ptr [eax+4],edx
    L_0045013d:
        mov edx,dword ptr [ecx+4]
    L_00450140:
        mov dword ptr [edx+8],eax
    L_00450143:
        mov dword ptr [ecx+4],eax
    L_00450146:
        mov dword ptr [eax+8],ecx
    L_00450149:
        mov eax,dword ptr [esp+10h]
    L_0045014d:
        mov ecx,dword ptr [edi+4]
    L_00450150:
        push eax
    L_00450151:
        push ecx
    L_00450152:
        mov eax,esi
    L_00450154:
        call asm_EclVm_StartChildRetail_0044df70
    L_00450159:
        pop esi
    L_0045015a:
        pop ebx
    L_0045015b:
        ret 8
    }
}

// 0x00450160..0x00450168: ?ECL_FindVariable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_FindVariable_00450160() {
    __asm {
    L_00450160:
        add eax,1030h
    L_00450165:
        TH10_REL8(0x74, 0x00450165, VA_asm_target_00450181)
    L_00450167:
        TH10_REL8(0xeb, 0x00450167, VA_asm_ECL_FindVariable_part_00450170)
    }
}

// 0x00450170..0x00450183: ?ECL_FindVariable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_FindVariable_part_00450170() {
    __asm {
    L_00450170:
        mov edx,dword ptr [eax]
    L_00450172:
        cmp dword ptr [edx+1010h],ecx
    L_00450178:
        je short L_00450183
    L_0045017a:
        mov eax,dword ptr [eax+4]
    L_0045017d:
        test eax,eax
    L_0045017f:
        jne short L_00450170
    L_00450181:
        xor eax,eax
    L_00450183:
        ret
    }
}

// 0x00450190..0x004501AE: ?ECL_ResetVariableBindings@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_ResetVariableBindings_00450190() {
    __asm {
    L_00450190:
        mov eax,dword ptr [eax+1034h]
    L_00450196:
        xor edx,edx
    L_00450198:
        cmp eax,edx
    L_0045019a:
        je short L_004501ae
    L_0045019c:
        TH10_NOP_LEA_ESP_DISP8()
    L_004501a0:
        mov ecx,dword ptr [eax+4]
    L_004501a3:
        cmp ecx,edx
    L_004501a5:
        mov eax,dword ptr [eax]
    L_004501a7:
        mov dword ptr [eax+4],edx
    L_004501aa:
        mov eax,ecx
    L_004501ac:
        jne short L_004501a0
    L_004501ae:
        ret
    }
}

// 0x004501B0..0x004501CD: ?ECL_SetPolarVector@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_SetPolarVector_004501b0() {
    __asm {
    L_004501b0:
        push ecx
    L_004501b1:
        mov dword ptr [esp],ecx
    L_004501b4:
        mov eax,dword ptr [esp]
    L_004501b7:
        fld dword ptr [esp+8]
    L_004501bb:
        fsincos
    L_004501bd:
        fmul dword ptr [esp+0Ch]
    L_004501c1:
        fstp dword ptr [eax]
    L_004501c3:
        fmul dword ptr [esp+0Ch]
    L_004501c7:
        fstp dword ptr [eax+4]
    L_004501ca:
        pop ecx
    L_004501cb:
        ret 8
    }
}

// 0x004505B0..0x0045060F: FUN_004505b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004505b0_004505b0() {
    __asm {
    L_004505b0:
        mov ecx,dword ptr [eax+1000h]
    L_004505b6:
        push ebp
    L_004505b7:
        mov ebp,dword ptr [esp+8]
    L_004505bb:
        push esi
    L_004505bc:
        lea esi,[ecx+ebp]
    L_004505bf:
        cmp esi,1000h
    L_004505c5:
        jl short L_004505cf
    L_004505c7:
        pop esi
    L_004505c8:
        or eax,0FFFFFFFFh
    L_004505cb:
        pop ebp
    L_004505cc:
        ret 8
    L_004505cf:
        test dl,dl
    L_004505d1:
        je short L_004505dd
    L_004505d3:
        mov byte ptr [ecx+eax],dl
    L_004505d6:
        add dword ptr [eax+1000h],4
    L_004505dd:
        mov esi,dword ptr [esp+10h]
    L_004505e1:
        push edi
    L_004505e2:
        mov edi,dword ptr [eax+1000h]
    L_004505e8:
        mov ecx,ebp
    L_004505ea:
        mov edx,ecx
    L_004505ec:
        shr ecx,2
    L_004505ef:
        add edi,eax
    L_004505f1:
        rep movsd
    L_004505f3:
        mov ecx,edx
    L_004505f5:
        and ecx,3
    L_004505f8:
        rep movsb
    L_004505fa:
        mov ecx,dword ptr [eax+1000h]
    L_00450600:
        pop edi
    L_00450601:
        add ecx,ebp
    L_00450603:
        pop esi
    L_00450604:
        mov dword ptr [eax+1000h],ecx
    L_0045060a:
        xor eax,eax
    L_0045060c:
        pop ebp
    L_0045060d:
        ret 8
    }
}

// 0x00450690..0x004506CF: ?ECL_PushScratchValue@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_PushScratchValue_00450690() {
    __asm {
    L_00450690:
        mov edx,dword ptr [eax+1000h]
    L_00450696:
        add ecx,edx
    L_00450698:
        cmp ecx,1000h
    L_0045069e:
        jl short L_004506a4
    L_004506a0:
        or eax,0FFFFFFFFh
    L_004506a3:
        ret
    L_004506a4:
        push esi
    L_004506a5:
        lea esi,[ecx+4]
    L_004506a8:
        cmp esi,1000h
    L_004506ae:
        mov dword ptr [eax+1000h],ecx
    L_004506b4:
        jge short L_004506c6
    L_004506b6:
        mov esi,dword ptr [eax+1004h]
    L_004506bc:
        mov dword ptr [ecx+eax],esi
    L_004506bf:
        add dword ptr [eax+1000h],4
    L_004506c6:
        mov dword ptr [eax+1004h],edx
    L_004506cc:
        xor eax,eax
    L_004506ce:
        pop esi
    L_004506cf:
        ret
    }
}

// 0x004506D0..0x004506F8: ?ECL_PopScratchValue@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_PopScratchValue_004506d0() {
    __asm {
    L_004506d0:
        mov ecx,dword ptr [eax+1000h]
    L_004506d6:
        add ecx,0FFFFFFFCh
    L_004506d9:
        mov edx,dword ptr [eax+1004h]
    L_004506df:
        js short L_004506f0
    L_004506e1:
        mov dword ptr [eax+1000h],ecx
    L_004506e7:
        mov ecx,dword ptr [ecx+eax]
    L_004506ea:
        mov dword ptr [eax+1004h],ecx
    L_004506f0:
        mov dword ptr [eax+1000h],edx
    L_004506f6:
        xor eax,eax
    L_004506f8:
        ret
    }
}

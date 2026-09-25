#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D3606): closest_byte_count=0/1323; first_diff=0x0043B110.
// residual_class=full MIDI event parser layout plus private ESI/EBP state and
// helper handoffs to 0x0043A730 and 0x0043AEB0. variants_tested=live Ghidra
// decompilation, existing readable MIDI track/file models, and schema2/native
// LTCG dependency review; no nonexact body was retained. next_lever=co-compile
// the real caller 0x0043AF30, this parser, and both helpers in one native-LTCG
// cluster while preserving the MidiSequencer/MidiTrack offsets; production
// ownership remains kind=asm because regions.json is not edited in this lane.

// 0x0043B110..0x0043B63A: FUN_0043b110
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043b110_0043b110() {
    __asm {
    L_0043b110:
        sub esp,0Ch
    L_0043b113:
        push ebx
    L_0043b114:
        push ebp
    L_0043b115:
        mov ebp,dword ptr [esp+18h]
    L_0043b119:
        push esi
    L_0043b11a:
        mov esi,dword ptr [esp+20h]
    L_0043b11e:
        mov eax,dword ptr [esi+14h]
    L_0043b121:
        mov cl,byte ptr [eax]
    L_0043b123:
        push edi
    L_0043b124:
        lea edi,[esi+14h]
    L_0043b127:
        xor dl,dl
    L_0043b129:
        cmp cl,80h
    L_0043b12c:
        mov byte ptr [esp+11h],dl
    L_0043b130:
        mov byte ptr [esp+20h],dl
    L_0043b134:
        mov byte ptr [esp+12h],cl
    L_0043b138:
        jae short L_0043b143
    L_0043b13a:
        mov al,byte ptr [esi+0Ch]
    L_0043b13d:
        mov byte ptr [esp+12h],al
    L_0043b141:
        jmp short L_0043b146
    L_0043b143:
        inc eax
    L_0043b144:
        mov dword ptr [edi],eax
    L_0043b146:
        mov cl,byte ptr [esp+12h]
    L_0043b14a:
        mov al,cl
    L_0043b14c:
        and al,0F0h
    L_0043b14e:
        movzx eax,al
    L_0043b151:
        mov bl,cl
    L_0043b153:
        add eax,0FFFFFF80h
    L_0043b156:
        and bl,0Fh
    L_0043b159:
        cmp eax,70h
    L_0043b15c:
        mov byte ptr [esp+13h],bl
    L_0043b160:
        mov dword ptr [esp+18h],eax
    L_0043b164:
        ja asm_target_0043b287
    L_0043b16a:
        movzx eax,byte ptr [eax+43B64Ch]
    L_0043b171:
        jmp dword ptr [eax*4+43B63Ch]
    L_0043b178:
        cmp cl,0F0h
    L_0043b17b:
        jne asm_target_0043b2a2
    L_0043b181:
        mov ecx,dword ptr [ebp+94h]
    L_0043b187:
        mov esi,dword ptr [ebp+ecx*4+14h]
    L_0043b18b:
        test esi,esi
    L_0043b18d:
        je short L_0043b196
    L_0043b18f:
        mov edx,ebp
    L_0043b191:
        call asm_FUN_0043aeb0_0043aeb0
    L_0043b196:
        push 40h
    L_0043b198:
        call asm_malloc_00452706
    L_0043b19d:
        mov edx,dword ptr [ebp+94h]
    L_0043b1a3:
        mov dword ptr [ebp+edx*4+14h],eax
    L_0043b1a7:
        mov eax,dword ptr [ebp+94h]
    L_0043b1ad:
        mov ebx,dword ptr [ebp+eax*4+14h]
    L_0043b1b1:
        add esp,4
    L_0043b1b4:
        mov esi,edi
    L_0043b1b6:
        call asm_FUN_0043a730_0043a730
    L_0043b1bb:
        mov esi,eax
    L_0043b1bd:
        xor eax,eax
    L_0043b1bf:
        mov ecx,10h
    L_0043b1c4:
        mov edi,ebx
    L_0043b1c6:
        rep stosd
    L_0043b1c8:
        lea edi,[esi+1]
    L_0043b1cb:
        push edi
    L_0043b1cc:
        call asm_malloc_00452706
    L_0043b1d1:
        mov dword ptr [ebx],eax
    L_0043b1d3:
        mov byte ptr [eax],0F0h
    L_0043b1d6:
        xor eax,eax
    L_0043b1d8:
        add esp,4
    L_0043b1db:
        cmp esi,eax
    L_0043b1dd:
        mov dword ptr [ebx+10h],eax
    L_0043b1e0:
        mov dword ptr [ebx+4],edi
    L_0043b1e3:
        jle short L_0043b201
    L_0043b1e5:
        mov edi,dword ptr [esp+24h]
    L_0043b1e9:
        mov ecx,dword ptr [edi+14h]
    L_0043b1ec:
        mov cl,byte ptr [ecx]
    L_0043b1ee:
        mov edx,dword ptr [ebx]
    L_0043b1f0:
        add edi,14h
    L_0043b1f3:
        mov byte ptr [eax+edx+1],cl
    L_0043b1f7:
        mov ecx,dword ptr [edi]
    L_0043b1f9:
        inc ecx
    L_0043b1fa:
        inc eax
    L_0043b1fb:
        cmp eax,esi
    L_0043b1fd:
        mov dword ptr [edi],ecx
    L_0043b1ff:
        jl short L_0043b1e5
    L_0043b201:
        mov eax,dword ptr [ebp+13Ch]
    L_0043b207:
        test eax,eax
    L_0043b209:
        je short L_0043b261
    L_0043b20b:
        push 40h
    L_0043b20d:
        push ebx
    L_0043b20e:
        push eax
    L_0043b20f:
        call dword ptr [data_004662a0]
    L_0043b215:
        test eax,eax
    L_0043b217:
        jne short L_0043b235
    L_0043b219:
        mov edx,dword ptr [ebp+13Ch]
    L_0043b21f:
        push 40h
    L_0043b221:
        push ebx
    L_0043b222:
        push edx
    L_0043b223:
        call dword ptr [data_0046629c]
    L_0043b229:
        neg eax
    L_0043b22b:
        sbb eax,eax
    L_0043b22d:
        neg eax
    L_0043b22f:
        mov dword ptr [esp+14h],eax
    L_0043b233:
        je short L_0043b261
    L_0043b235:
        mov eax,dword ptr [ebx]
    L_0043b237:
        test eax,eax
    L_0043b239:
        je short L_0043b24a
    L_0043b23b:
        push eax
    L_0043b23c:
        call asm_free_00452422
    L_0043b241:
        add esp,4
    L_0043b244:
        mov dword ptr [ebx],0
    L_0043b24a:
        push ebx
    L_0043b24b:
        call asm_free_00452422
    L_0043b250:
        mov eax,dword ptr [ebp+94h]
    L_0043b256:
        add esp,4
    L_0043b259:
        mov dword ptr [ebp+eax*4+14h],0
    L_0043b261:
        mov ecx,dword ptr [ebp+94h]
    L_0043b267:
        inc ecx
    L_0043b268:
        and ecx,8000001Fh
    L_0043b26e:
        jns short L_0043b275
    L_0043b270:
        dec ecx
    L_0043b271:
        or ecx,0FFFFFFE0h
    L_0043b274:
        inc ecx
    L_0043b275:
        mov bl,byte ptr [esp+13h]
    L_0043b279:
        mov dword ptr [ebp+94h],ecx
    L_0043b27f:
        mov esi,dword ptr [esp+24h]
    L_0043b283:
        mov dl,byte ptr [esp+11h]
    L_0043b287:
        mov eax,dword ptr [esp+18h]
    L_0043b28b:
        cmp eax,40h
    L_0043b28e:
        ja asm_target_0043b5d8
    L_0043b294:
        movzx eax,byte ptr [eax+43B6D4h]
    L_0043b29b:
        jmp dword ptr [eax*4+43B6C0h]
    L_0043b2a2:
        cmp cl,0FFh
    L_0043b2a5:
        jne short L_0043b287
    L_0043b2a7:
        mov eax,dword ptr [edi]
    L_0043b2a9:
        mov dl,byte ptr [eax]
    L_0043b2ab:
        inc eax
    L_0043b2ac:
        mov esi,edi
    L_0043b2ae:
        mov byte ptr [esp+13h],dl
    L_0043b2b2:
        mov dword ptr [edi],eax
    L_0043b2b4:
        call asm_FUN_0043a730_0043a730
    L_0043b2b9:
        mov cl,byte ptr [esp+13h]
    L_0043b2bd:
        cmp cl,2Fh
    L_0043b2c0:
        mov dword ptr [esp+14h],eax
    L_0043b2c4:
        jne short L_0043b2da
    L_0043b2c6:
        mov eax,dword ptr [esp+24h]
    L_0043b2ca:
        pop edi
    L_0043b2cb:
        pop esi
    L_0043b2cc:
        pop ebp
    L_0043b2cd:
        mov dword ptr [eax],0
    L_0043b2d3:
        pop ebx
    L_0043b2d4:
        add esp,0Ch
    L_0043b2d7:
        ret 8
    L_0043b2da:
        cmp cl,51h
    L_0043b2dd:
        jne asm_target_0043b386
    L_0043b2e3:
        mov ecx,dword ptr [ebp+12Ch]
    L_0043b2e9:
        mov eax,dword ptr [ebp+120h]
    L_0043b2ef:
        push ecx
    L_0043b2f0:
        mov ecx,dword ptr [ebp+128h]
    L_0043b2f6:
        cdq
    L_0043b2f7:
        push ecx
    L_0043b2f8:
        push edx
    L_0043b2f9:
        push eax
    L_0043b2fa:
        call asm_allmul_00456640
    L_0043b2ff:
        push 0
    L_0043b301:
        push 3E8h
    L_0043b306:
        push edx
    L_0043b307:
        push eax
    L_0043b308:
        call asm_allmul_00456640
    L_0043b30d:
        mov ecx,eax
    L_0043b30f:
        mov eax,dword ptr [ebp+124h]
    L_0043b315:
        mov esi,edx
    L_0043b317:
        cdq
    L_0043b318:
        push edx
    L_0043b319:
        push eax
    L_0043b31a:
        push esi
    L_0043b31b:
        push ecx
    L_0043b31c:
        call asm_aulldiv_00456b80
    L_0043b321:
        mov ecx,dword ptr [ebp+130h]
    L_0043b327:
        mov esi,dword ptr [ebp+134h]
    L_0043b32d:
        add ecx,eax
    L_0043b32f:
        mov eax,dword ptr [esp+14h]
    L_0043b333:
        adc esi,edx
    L_0043b335:
        mov dword ptr [ebp+130h],ecx
    L_0043b33b:
        xor ecx,ecx
    L_0043b33d:
        cmp eax,ecx
    L_0043b33f:
        mov dword ptr [ebp+134h],esi
    L_0043b345:
        mov dword ptr [ebp+128h],ecx
    L_0043b34b:
        mov dword ptr [ebp+12Ch],ecx
    L_0043b351:
        mov dword ptr [ebp+124h],ecx
    L_0043b357:
        jle asm_target_0043b27f
    L_0043b35d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0043b360:
        mov edx,dword ptr [ebp+124h]
    L_0043b366:
        mov ecx,dword ptr [edi]
    L_0043b368:
        imul edx,101h
    L_0043b36e:
        movzx ecx,byte ptr [ecx]
    L_0043b371:
        add edx,ecx
    L_0043b373:
        mov dword ptr [ebp+124h],edx
    L_0043b379:
        mov edx,dword ptr [edi]
    L_0043b37b:
        inc edx
    L_0043b37c:
        dec eax
    L_0043b37d:
        mov dword ptr [edi],edx
    L_0043b37f:
        jne short L_0043b360
    L_0043b381:
        jmp asm_target_0043b27f
    L_0043b386:
        add dword ptr [edi],eax
    L_0043b388:
        jmp asm_target_0043b27f
    L_0043b38d:
        mov eax,dword ptr [edi]
    L_0043b38f:
        mov dl,byte ptr [eax]
    L_0043b391:
        inc eax
    L_0043b392:
        mov dword ptr [edi],eax
    L_0043b394:
        mov cl,byte ptr [eax]
    L_0043b396:
        inc eax
    L_0043b397:
        mov byte ptr [esp+11h],dl
    L_0043b39b:
        mov byte ptr [esp+20h],cl
    L_0043b39f:
        mov dword ptr [edi],eax
    L_0043b3a1:
        jmp asm_target_0043b283
    L_0043b3a6:
        mov eax,dword ptr [edi]
    L_0043b3a8:
        mov dl,byte ptr [eax]
    L_0043b3aa:
        inc eax
    L_0043b3ab:
        mov byte ptr [esp+11h],dl
    L_0043b3af:
        mov dword ptr [edi],eax
    L_0043b3b1:
        mov byte ptr [esp+20h],0
    L_0043b3b6:
        jmp asm_target_0043b283
    L_0043b3bb:
        mov al,byte ptr [esp+20h]
    L_0043b3bf:
        test al,al
    L_0043b3c1:
        je short L_0043b3ee
    L_0043b3c3:
        add dl,byte ptr [ebp+2C4h]
    L_0043b3c9:
        movzx edi,bl
    L_0043b3cc:
        imul edi,17h
    L_0043b3cf:
        movzx ecx,dl
    L_0043b3d2:
        mov eax,ecx
    L_0043b3d4:
        shr eax,3
    L_0043b3d7:
        add eax,ebp
    L_0043b3d9:
        lea edi,[edi+eax+154h]
    L_0043b3e0:
        and ecx,7
    L_0043b3e3:
        mov al,1
    L_0043b3e5:
        shl al,cl
    L_0043b3e7:
        or byte ptr [edi],al
    L_0043b3e9:
        jmp asm_target_0043b5d8
    L_0043b3ee:
        add dl,byte ptr [ebp+2C4h]
    L_0043b3f4:
        movzx edi,bl
    L_0043b3f7:
        imul edi,17h
    L_0043b3fa:
        movzx ecx,dl
    L_0043b3fd:
        mov eax,ecx
    L_0043b3ff:
        shr eax,3
    L_0043b402:
        add eax,ebp
    L_0043b404:
        lea edi,[edi+eax+154h]
    L_0043b40b:
        and ecx,7
    L_0043b40e:
        mov al,1
    L_0043b410:
        shl al,cl
    L_0043b412:
        mov cl,byte ptr [edi]
    L_0043b414:
        not al
    L_0043b416:
        and cl,al
    L_0043b418:
        mov byte ptr [edi],cl
    L_0043b41a:
        jmp asm_target_0043b5d8
    L_0043b41f:
        movzx ecx,bl
    L_0043b422:
        imul ecx,17h
    L_0043b425:
        mov byte ptr [ecx+ebp+164h],dl
    L_0043b42c:
        jmp asm_target_0043b5d8
    L_0043b431:
        movzx eax,dl
    L_0043b434:
        cmp eax,5Dh
    L_0043b437:
        ja asm_target_0043b5d8
    L_0043b43d:
        movzx eax,byte ptr [eax+43B738h]
    L_0043b444:
        jmp dword ptr [eax*4+43B718h]
    L_0043b44b:
        mov al,byte ptr [esp+20h]
    L_0043b44f:
        movzx ecx,bl
    L_0043b452:
        imul ecx,17h
    L_0043b455:
        mov byte ptr [ecx+ebp+165h],al
    L_0043b45c:
        jmp asm_target_0043b5d8
    L_0043b461:
        mov al,byte ptr [esp+20h]
    L_0043b465:
        movzx ecx,bl
    L_0043b468:
        imul ecx,17h
    L_0043b46b:
        movzx edx,al
    L_0043b46e:
        mov dword ptr [esp+24h],edx
    L_0043b472:
        lea edi,[ecx+ebp]
    L_0043b475:
        mov byte ptr [edi+169h],al
    L_0043b47b:
        fild dword ptr [esp+24h]
    L_0043b47f:
        fmul dword ptr [ebp+2C8h]
    L_0043b485:
        call asm_FUN_00463b2c_00463b2c
    L_0043b48a:
        test eax,eax
    L_0043b48c:
        jge short L_0043b4a3
    L_0043b48e:
        mov dl,byte ptr [esp+11h]
    L_0043b492:
        xor eax,eax
    L_0043b494:
        mov byte ptr [edi+16Ah],al
    L_0043b49a:
        mov byte ptr [esp+20h],al
    L_0043b49e:
        jmp asm_target_0043b5d8
    L_0043b4a3:
        cmp eax,7Fh
    L_0043b4a6:
        jle short L_0043b4ad
    L_0043b4a8:
        mov eax,7Fh
    L_0043b4ad:
        mov dl,byte ptr [esp+11h]
    L_0043b4b1:
        mov byte ptr [edi+16Ah],al
    L_0043b4b7:
        mov byte ptr [esp+20h],al
    L_0043b4bb:
        jmp asm_target_0043b5d8
    L_0043b4c0:
        mov cl,byte ptr [esp+20h]
    L_0043b4c4:
        movzx eax,bl
    L_0043b4c7:
        imul eax,17h
    L_0043b4ca:
        mov byte ptr [eax+ebp+167h],cl
    L_0043b4d1:
        jmp asm_target_0043b5d8
    L_0043b4d6:
        mov cl,byte ptr [esp+20h]
    L_0043b4da:
        movzx eax,bl
    L_0043b4dd:
        imul eax,17h
    L_0043b4e0:
        mov byte ptr [eax+ebp+168h],cl
    L_0043b4e7:
        jmp asm_target_0043b5d8
    L_0043b4ec:
        mov cl,byte ptr [esp+20h]
    L_0043b4f0:
        movzx eax,bl
    L_0043b4f3:
        imul eax,17h
    L_0043b4f6:
        mov byte ptr [eax+ebp+166h],cl
    L_0043b4fd:
        jmp asm_target_0043b5d8
    L_0043b502:
        mov edi,dword ptr [ebp+118h]
    L_0043b508:
        mov eax,dword ptr [ebp+138h]
    L_0043b50e:
        xor ecx,ecx
    L_0043b510:
        test edi,edi
    L_0043b512:
        jle short L_0043b530
    L_0043b514:
        add eax,18h
    L_0043b517:
        mov edi,dword ptr [eax-4]
    L_0043b51a:
        mov dword ptr [eax],edi
    L_0043b51c:
        mov edi,dword ptr [eax-14h]
    L_0043b51f:
        mov dword ptr [eax+4],edi
    L_0043b522:
        mov edi,dword ptr [ebp+118h]
    L_0043b528:
        inc ecx
    L_0043b529:
        add eax,20h
    L_0043b52c:
        cmp ecx,edi
    L_0043b52e:
        jl short L_0043b517
    L_0043b530:
        mov eax,dword ptr [ebp+124h]
    L_0043b536:
        mov ecx,dword ptr [ebp+128h]
    L_0043b53c:
        mov dword ptr [ebp+2ECh],eax
    L_0043b542:
        mov eax,dword ptr [ebp+12Ch]
    L_0043b548:
        mov dword ptr [ebp+2F0h],ecx
    L_0043b54e:
        mov ecx,dword ptr [ebp+130h]
    L_0043b554:
        mov dword ptr [ebp+2F4h],eax
    L_0043b55a:
        mov eax,dword ptr [ebp+134h]
    L_0043b560:
        mov dword ptr [ebp+2F8h],ecx
    L_0043b566:
        mov dword ptr [ebp+2FCh],eax
    L_0043b56c:
        jmp short L_0043b5d8
    L_0043b56e:
        mov edi,dword ptr [ebp+118h]
    L_0043b574:
        mov eax,dword ptr [ebp+138h]
    L_0043b57a:
        xor ecx,ecx
    L_0043b57c:
        test edi,edi
    L_0043b57e:
        jle short L_0043b59c
    L_0043b580:
        add eax,14h
    L_0043b583:
        mov edi,dword ptr [eax+4]
    L_0043b586:
        mov dword ptr [eax],edi
    L_0043b588:
        mov edi,dword ptr [eax+8]
    L_0043b58b:
        mov dword ptr [eax-10h],edi
    L_0043b58e:
        mov edi,dword ptr [ebp+118h]
    L_0043b594:
        inc ecx
    L_0043b595:
        add eax,20h
    L_0043b598:
        cmp ecx,edi
    L_0043b59a:
        jl short L_0043b583
    L_0043b59c:
        mov ecx,dword ptr [ebp+2ECh]
    L_0043b5a2:
        mov eax,dword ptr [ebp+2F0h]
    L_0043b5a8:
        mov dword ptr [ebp+124h],ecx
    L_0043b5ae:
        mov ecx,dword ptr [ebp+2F4h]
    L_0043b5b4:
        mov dword ptr [ebp+128h],eax
    L_0043b5ba:
        mov eax,dword ptr [ebp+2F8h]
    L_0043b5c0:
        mov dword ptr [ebp+12Ch],ecx
    L_0043b5c6:
        mov ecx,dword ptr [ebp+2FCh]
    L_0043b5cc:
        mov dword ptr [ebp+130h],eax
    L_0043b5d2:
        mov dword ptr [ebp+134h],ecx
    L_0043b5d8:
        mov al,byte ptr [esp+12h]
    L_0043b5dc:
        cmp al,0F0h
    L_0043b5de:
        jae short L_0043b606
    L_0043b5e0:
        mov ebp,dword ptr [ebp+13Ch]
    L_0043b5e6:
        test ebp,ebp
    L_0043b5e8:
        je short L_0043b606
    L_0043b5ea:
        mov byte ptr [esp+25h],dl
    L_0043b5ee:
        mov dl,byte ptr [esp+20h]
    L_0043b5f2:
        mov byte ptr [esp+24h],al
    L_0043b5f6:
        mov byte ptr [esp+26h],dl
    L_0043b5fa:
        mov eax,dword ptr [esp+24h]
    L_0043b5fe:
        push eax
    L_0043b5ff:
        push ebp
    L_0043b600:
        call dword ptr [data_00466298]
    L_0043b606:
        mov cl,byte ptr [esp+12h]
    L_0043b60a:
        mov byte ptr [esi+0Ch],cl
    L_0043b60d:
        xor edx,edx
    L_0043b60f:
        nop
    L_0043b610:
        mov eax,dword ptr [esi+14h]
    L_0043b613:
        mov cl,byte ptr [eax]
    L_0043b615:
        inc eax
    L_0043b616:
        mov dword ptr [esi+14h],eax
    L_0043b619:
        xor eax,eax
    L_0043b61b:
        mov al,cl
    L_0043b61d:
        shl edx,7
    L_0043b620:
        and eax,7Fh
    L_0043b623:
        add edx,eax
    L_0043b625:
        test cl,cl
    L_0043b627:
        js short L_0043b610
    L_0043b629:
        mov eax,dword ptr [esi+4]
    L_0043b62c:
        pop edi
    L_0043b62d:
        add eax,edx
    L_0043b62f:
        mov dword ptr [esi+4],eax
    L_0043b632:
        pop esi
    L_0043b633:
        pop ebp
    L_0043b634:
        pop ebx
    L_0043b635:
        add esp,0Ch
    L_0043b638:
        ret 8
    }
}

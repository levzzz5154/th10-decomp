#include "asm_encoding.hpp"
#include "asm_symbols.hpp"


// 0x00450220..0x0045046C: FUN_00450220
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00450220_00450220() {
    __asm {
    L_00450220:
        sub esp,10h
    L_00450223:
        push ebx
    L_00450224:
        mov ebx,ecx
    L_00450226:
        mov eax,dword ptr [ebx+4]
    L_00450229:
        mov ecx,dword ptr [esp+18h]
    L_0045022d:
        mov dword ptr [ebx+eax*4+0Ch],ecx
    L_00450231:
        mov edx,dword ptr [ebx+4]
    L_00450234:
        mov ecx,dword ptr [ebx+edx*4+0Ch]
    L_00450238:
        lea eax,[ebx+edx*4+0Ch]
    L_0045023c:
        cmp dword ptr [ecx],54504353h
    L_00450242:
        jne short L_0045024b
    L_00450244:
        cmp word ptr [ecx+4],1
    L_00450249:
        je short L_0045025b
    L_0045024b:
        mov dword ptr [eax],0
    L_00450251:
        or eax,0FFFFFFFFh
    L_00450254:
        pop ebx
    L_00450255:
        add esp,10h
    L_00450258:
        ret 4
    L_0045025b:
        mov eax,dword ptr [eax]
    L_0045025d:
        movzx ecx,word ptr [eax+6]
    L_00450261:
        mov edx,dword ptr [ebx+8]
    L_00450264:
        push ebp
    L_00450265:
        mov ebp,dword ptr [ebx+8Ch]
    L_0045026b:
        push esi
    L_0045026c:
        push edi
    L_0045026d:
        lea edi,[ecx+eax+24h]
    L_00450271:
        movzx eax,word ptr [eax+10h]
    L_00450275:
        add edx,eax
    L_00450277:
        mov dword ptr [esp+24h],edi
    L_0045027b:
        lea edi,[edi+eax*4]
    L_0045027e:
        mov eax,edx
    L_00450280:
        shl eax,3
    L_00450283:
        push eax
    L_00450284:
        mov dword ptr [esp+14h],edi
    L_00450288:
        mov dword ptr [ebx+8],edx
    L_0045028b:
        call asm_malloc_00452706
    L_00450290:
        add esp,4
    L_00450293:
        test ebp,ebp
    L_00450295:
        mov dword ptr [ebx+8Ch],eax
    L_0045029b:
        jne short L_004502fe
    L_0045029d:
        mov eax,dword ptr [ebx+8]
    L_004502a0:
        xor esi,esi
    L_004502a2:
        test eax,eax
    L_004502a4:
        jle asm_target_00450442
    L_004502aa:
        jmp short L_004502b0
    L_004502ac:
        mov edi,dword ptr [esp+10h]
    L_004502b0:
        mov edx,dword ptr [ebx+4]
    L_004502b3:
        mov eax,dword ptr [ebx+edx*4+0Ch]
    L_004502b7:
        mov ecx,dword ptr [esp+24h]
    L_004502bb:
        add eax,dword ptr [ecx]
    L_004502bd:
        mov edx,dword ptr [ebx+8Ch]
    L_004502c3:
        mov dword ptr [edx+esi*8+4],eax
    L_004502c7:
        mov eax,dword ptr [ebx+8Ch]
    L_004502cd:
        mov dword ptr [eax+esi*8],edi
    L_004502d0:
        mov eax,edi
    L_004502d2:
        lea edx,[eax+1]
    L_004502d5:
        mov cl,byte ptr [eax]
    L_004502d7:
        inc eax
    L_004502d8:
        test cl,cl
    L_004502da:
        jne short L_004502d5
    L_004502dc:
        sub eax,edx
    L_004502de:
        lea ecx,[edi+eax+1]
    L_004502e2:
        mov eax,dword ptr [ebx+8]
    L_004502e5:
        mov dword ptr [esp+10h],ecx
    L_004502e9:
        mov ecx,dword ptr [esp+24h]
    L_004502ed:
        inc esi
    L_004502ee:
        add ecx,4
    L_004502f1:
        cmp esi,eax
    L_004502f3:
        mov dword ptr [esp+24h],ecx
    L_004502f7:
        jl short L_004502ac
    L_004502f9:
        jmp asm_target_00450442
    L_004502fe:
        mov edx,dword ptr [ebx+4]
    L_00450301:
        mov ecx,dword ptr [ebx+edx*4+0Ch]
    L_00450305:
        movzx ecx,word ptr [ecx+10h]
    L_00450309:
        mov edx,dword ptr [ebx+8]
    L_0045030c:
        sub edx,ecx
    L_0045030e:
        test ebp,ebp
    L_00450310:
        lea ecx,[edx+edx]
    L_00450313:
        mov esi,ebp
    L_00450315:
        mov edi,eax
    L_00450317:
        mov dword ptr [esp+14h],edx
    L_0045031b:
        rep movsd
    L_0045031d:
        je short L_0045032c
    L_0045031f:
        push ebp
    L_00450320:
        call asm_free_00452422
    L_00450325:
        mov edx,dword ptr [esp+18h]
    L_00450329:
        add esp,4
    L_0045032c:
        mov eax,dword ptr [ebx+4]
    L_0045032f:
        mov ecx,dword ptr [ebx+eax*4+0Ch]
    L_00450333:
        cmp word ptr [ecx+10h],0
    L_00450338:
        mov dword ptr [esp+1Ch],0
    L_00450340:
        jbe asm_target_00450442
    L_00450346:
        jmp short L_00450350
    L_00450348:
        mov edx,dword ptr [esp+14h]
    L_0045034c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00450350:
        xor ebp,ebp
    L_00450352:
        test edx,edx
    L_00450354:
        jle short L_004503b3
    L_00450356:
        mov edx,dword ptr [ebx+8Ch]
    L_0045035c:
        mov dword ptr [esp+18h],edx
    L_00450360:
        mov eax,dword ptr [esp+18h]
    L_00450364:
        mov edx,dword ptr [esp+10h]
    L_00450368:
        mov edi,dword ptr [eax]
    L_0045036a:
        mov esi,edx
    L_0045036c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00450370:
        mov cl,byte ptr [esi]
    L_00450372:
        mov al,cl
    L_00450374:
        cmp cl,byte ptr [edi]
    L_00450376:
        jne short L_00450394
    L_00450378:
        test al,al
    L_0045037a:
        je short L_00450390
    L_0045037c:
        mov cl,byte ptr [esi+1]
    L_0045037f:
        mov al,cl
    L_00450381:
        cmp cl,byte ptr [edi+1]
    L_00450384:
        jne short L_00450394
    L_00450386:
        add esi,2
    L_00450389:
        add edi,2
    L_0045038c:
        test al,al
    L_0045038e:
        jne short L_00450370
    L_00450390:
        xor eax,eax
    L_00450392:
        jmp short L_00450399
    L_00450394:
        sbb eax,eax
    L_00450396:
        sbb eax,0FFFFFFFFh
    L_00450399:
        test eax,eax
    L_0045039b:
        jle short L_004503b7
    L_0045039d:
        mov ecx,dword ptr [esp+18h]
    L_004503a1:
        mov eax,dword ptr [esp+14h]
    L_004503a5:
        inc ebp
    L_004503a6:
        add ecx,8
    L_004503a9:
        cmp ebp,eax
    L_004503ab:
        mov dword ptr [esp+18h],ecx
    L_004503af:
        jl short L_00450360
    L_004503b1:
        jmp short L_004503b7
    L_004503b3:
        mov edx,dword ptr [esp+10h]
    L_004503b7:
        mov ecx,dword ptr [ebx+8]
    L_004503ba:
        dec ecx
    L_004503bb:
        cmp ecx,ebp
    L_004503bd:
        jle short L_004503da
    L_004503bf:
        nop
    L_004503c0:
        mov eax,dword ptr [ebx+8Ch]
    L_004503c6:
        mov esi,dword ptr [eax+ecx*8-8]
    L_004503ca:
        lea eax,[eax+ecx*8]
    L_004503cd:
        mov dword ptr [eax],esi
    L_004503cf:
        mov esi,dword ptr [eax-4]
    L_004503d2:
        dec ecx
    L_004503d3:
        cmp ecx,ebp
    L_004503d5:
        mov dword ptr [eax+4],esi
    L_004503d8:
        jg short L_004503c0
    L_004503da:
        mov ecx,dword ptr [ebx+4]
    L_004503dd:
        mov eax,dword ptr [ebx+ecx*4+0Ch]
    L_004503e1:
        mov ecx,dword ptr [esp+24h]
    L_004503e5:
        mov esi,dword ptr [ecx]
    L_004503e7:
        mov ecx,dword ptr [ebx+8Ch]
    L_004503ed:
        add eax,esi
    L_004503ef:
        mov dword ptr [ecx+ebp*8+4],eax
    L_004503f3:
        mov eax,dword ptr [ebx+8Ch]
    L_004503f9:
        mov dword ptr [eax+ebp*8],edx
    L_004503fc:
        mov eax,edx
    L_004503fe:
        lea esi,[eax+1]
    L_00450401:
        mov cl,byte ptr [eax]
    L_00450403:
        inc eax
    L_00450404:
        test cl,cl
    L_00450406:
        jne short L_00450401
    L_00450408:
        mov edi,dword ptr [esp+14h]
    L_0045040c:
        sub eax,esi
    L_0045040e:
        lea ecx,[edx+eax+1]
    L_00450412:
        mov edx,dword ptr [esp+24h]
    L_00450416:
        mov eax,dword ptr [esp+1Ch]
    L_0045041a:
        add edx,4
    L_0045041d:
        mov dword ptr [esp+24h],edx
    L_00450421:
        mov edx,dword ptr [ebx+4]
    L_00450424:
        mov dword ptr [esp+10h],ecx
    L_00450428:
        mov ecx,dword ptr [ebx+edx*4+0Ch]
    L_0045042c:
        movzx edx,word ptr [ecx+10h]
    L_00450430:
        inc edi
    L_00450431:
        inc eax
    L_00450432:
        cmp eax,edx
    L_00450434:
        mov dword ptr [esp+14h],edi
    L_00450438:
        mov dword ptr [esp+1Ch],eax
    L_0045043c:
        jl asm_target_00450348
    L_00450442:
        mov esi,dword ptr [ebx+4]
    L_00450445:
        lea eax,[esi+1]
    L_00450448:
        mov dword ptr [ebx+4],eax
    L_0045044b:
        mov eax,dword ptr [ebx+esi*4+0Ch]
    L_0045044f:
        cmp word ptr [eax+6],0
    L_00450454:
        je short L_00450461
    L_00450456:
        mov edx,dword ptr [ebx]
    L_00450458:
        add eax,24h
    L_0045045b:
        push eax
    L_0045045c:
        mov ecx,ebx
    L_0045045e:
        call dword ptr [edx+4]
    L_00450461:
        pop edi
    L_00450462:
        mov eax,esi
    L_00450464:
        pop esi
    L_00450465:
        pop ebp
    L_00450466:
        pop ebx
    L_00450467:
        add esp,10h
    L_0045046a:
        ret 4
    }
}

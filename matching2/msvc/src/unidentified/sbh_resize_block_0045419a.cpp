#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045419A..0x00454478: ___sbh_resize_block
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sbh_resize_block_0045419a() {
    __asm {
    L_0045419a:
        push ebp
    L_0045419b:
        mov ebp,esp
    L_0045419d:
        sub esp,0Ch
    L_004541a0:
        mov ecx,dword ptr [ebp+8]
    L_004541a3:
        mov eax,dword ptr [ecx+10h]
    L_004541a6:
        push ebx
    L_004541a7:
        push esi
    L_004541a8:
        mov esi,dword ptr [ebp+10h]
    L_004541ab:
        push edi
    L_004541ac:
        mov edi,dword ptr [ebp+0Ch]
    L_004541af:
        mov edx,edi
    L_004541b1:
        sub edx,dword ptr [ecx+0Ch]
    L_004541b4:
        add esi,17h
    L_004541b7:
        shr edx,0Fh
    L_004541ba:
        mov ecx,edx
    L_004541bc:
        imul ecx,204h
    L_004541c2:
        lea ecx,[ecx+eax+144h]
    L_004541c9:
        mov dword ptr [ebp-0Ch],ecx
    L_004541cc:
        mov ecx,dword ptr [edi-4]
    L_004541cf:
        and esi,0FFFFFFF0h
    L_004541d2:
        dec ecx
    L_004541d3:
        cmp esi,ecx
    L_004541d5:
        lea edi,[ecx+edi-4]
    L_004541d9:
        mov ebx,dword ptr [edi]
    L_004541db:
        mov dword ptr [ebp+10h],ecx
    L_004541de:
        mov dword ptr [ebp-4],ebx
    L_004541e1:
        jle asm_target_0045433c
    L_004541e7:
        test bl,1
    L_004541ea:
        jne asm_target_00454335
    L_004541f0:
        add ebx,ecx
    L_004541f2:
        cmp esi,ebx
    L_004541f4:
        jg asm_target_00454335
    L_004541fa:
        mov ecx,dword ptr [ebp-4]
    L_004541fd:
        sar ecx,4
    L_00454200:
        dec ecx
    L_00454201:
        cmp ecx,3Fh
    L_00454204:
        mov dword ptr [ebp-8],ecx
    L_00454207:
        jbe short L_0045420f
    L_00454209:
        push 3Fh
    L_0045420b:
        pop ecx
    L_0045420c:
        mov dword ptr [ebp-8],ecx
    L_0045420f:
        mov ebx,dword ptr [edi+4]
    L_00454212:
        cmp ebx,dword ptr [edi+8]
    L_00454215:
        jne short L_0045425a
    L_00454217:
        cmp ecx,20h
    L_0045421a:
        mov ebx,80000000h
    L_0045421f:
        jae short L_0045423b
    L_00454221:
        shr ebx,cl
    L_00454223:
        mov ecx,dword ptr [ebp-8]
    L_00454226:
        lea ecx,[ecx+eax+4]
    L_0045422a:
        not ebx
    L_0045422c:
        and dword ptr [eax+edx*4+44h],ebx
    L_00454230:
        dec byte ptr [ecx]
    L_00454232:
        jne short L_0045425a
    L_00454234:
        mov ecx,dword ptr [ebp+8]
    L_00454237:
        and dword ptr [ecx],ebx
    L_00454239:
        jmp short L_0045425a
    L_0045423b:
        add ecx,0FFFFFFE0h
    L_0045423e:
        shr ebx,cl
    L_00454240:
        mov ecx,dword ptr [ebp-8]
    L_00454243:
        lea ecx,[ecx+eax+4]
    L_00454247:
        not ebx
    L_00454249:
        and dword ptr [eax+edx*4+0C4h],ebx
    L_00454250:
        dec byte ptr [ecx]
    L_00454252:
        jne short L_0045425a
    L_00454254:
        mov ecx,dword ptr [ebp+8]
    L_00454257:
        and dword ptr [ecx+4],ebx
    L_0045425a:
        mov ecx,dword ptr [edi+8]
    L_0045425d:
        mov ebx,dword ptr [edi+4]
    L_00454260:
        mov dword ptr [ecx+4],ebx
    L_00454263:
        mov ecx,dword ptr [edi+4]
    L_00454266:
        mov edi,dword ptr [edi+8]
    L_00454269:
        mov dword ptr [ecx+8],edi
    L_0045426c:
        mov ecx,dword ptr [ebp+10h]
    L_0045426f:
        sub ecx,esi
    L_00454271:
        add dword ptr [ebp-4],ecx
    L_00454274:
        cmp dword ptr [ebp-4],0
    L_00454278:
        jle asm_target_00454323
    L_0045427e:
        mov edi,dword ptr [ebp-4]
    L_00454281:
        mov ecx,dword ptr [ebp+0Ch]
    L_00454284:
        sar edi,4
    L_00454287:
        dec edi
    L_00454288:
        cmp edi,3Fh
    L_0045428b:
        lea ecx,[ecx+esi-4]
    L_0045428f:
        jbe short L_00454294
    L_00454291:
        push 3Fh
    L_00454293:
        pop edi
    L_00454294:
        mov ebx,dword ptr [ebp-0Ch]
    L_00454297:
        lea ebx,[ebx+edi*8]
    L_0045429a:
        mov dword ptr [ebp+10h],ebx
    L_0045429d:
        mov ebx,dword ptr [ebx+4]
    L_004542a0:
        mov dword ptr [ecx+4],ebx
    L_004542a3:
        mov ebx,dword ptr [ebp+10h]
    L_004542a6:
        mov dword ptr [ecx+8],ebx
    L_004542a9:
        mov dword ptr [ebx+4],ecx
    L_004542ac:
        mov ebx,dword ptr [ecx+4]
    L_004542af:
        mov dword ptr [ebx+8],ecx
    L_004542b2:
        mov ebx,dword ptr [ecx+4]
    L_004542b5:
        cmp ebx,dword ptr [ecx+8]
    L_004542b8:
        jne short L_00454311
    L_004542ba:
        mov cl,byte ptr [edi+eax+4]
    L_004542be:
        mov byte ptr [ebp+13h],cl
    L_004542c1:
        inc cl
    L_004542c3:
        cmp edi,20h
    L_004542c6:
        mov byte ptr [edi+eax+4],cl
    L_004542ca:
        jae short L_004542e8
    L_004542cc:
        cmp byte ptr [ebp+13h],0
    L_004542d0:
        jne short L_004542e0
    L_004542d2:
        mov ecx,edi
    L_004542d4:
        mov ebx,80000000h
    L_004542d9:
        shr ebx,cl
    L_004542db:
        mov ecx,dword ptr [ebp+8]
    L_004542de:
        or dword ptr [ecx],ebx
    L_004542e0:
        lea eax,[eax+edx*4+44h]
    L_004542e4:
        mov ecx,edi
    L_004542e6:
        jmp short L_00454308
    L_004542e8:
        cmp byte ptr [ebp+13h],0
    L_004542ec:
        jne short L_004542fe
    L_004542ee:
        lea ecx,[edi-20h]
    L_004542f1:
        mov ebx,80000000h
    L_004542f6:
        shr ebx,cl
    L_004542f8:
        mov ecx,dword ptr [ebp+8]
    L_004542fb:
        or dword ptr [ecx+4],ebx
    L_004542fe:
        lea eax,[eax+edx*4+0C4h]
    L_00454305:
        lea ecx,[edi-20h]
    L_00454308:
        mov edx,80000000h
    L_0045430d:
        shr edx,cl
    L_0045430f:
        or dword ptr [eax],edx
    L_00454311:
        mov edx,dword ptr [ebp+0Ch]
    L_00454314:
        mov ecx,dword ptr [ebp-4]
    L_00454317:
        lea eax,[edx+esi-4]
    L_0045431b:
        mov dword ptr [eax],ecx
    L_0045431d:
        mov dword ptr [ecx+eax-4],ecx
    L_00454321:
        jmp short L_00454326
    L_00454323:
        mov edx,dword ptr [ebp+0Ch]
    L_00454326:
        lea eax,[esi+1]
    L_00454329:
        mov dword ptr [edx-4],eax
    L_0045432c:
        mov dword ptr [edx+esi-8],eax
    L_00454330:
        jmp asm_target_00454471
    L_00454335:
        xor eax,eax
    L_00454337:
        jmp asm_target_00454474
    L_0045433c:
        jge asm_target_00454471
    L_00454342:
        mov ebx,dword ptr [ebp+0Ch]
    L_00454345:
        sub dword ptr [ebp+10h],esi
    L_00454348:
        lea ecx,[esi+1]
    L_0045434b:
        mov dword ptr [ebx-4],ecx
    L_0045434e:
        lea ebx,[ebx+esi-4]
    L_00454352:
        mov esi,dword ptr [ebp+10h]
    L_00454355:
        sar esi,4
    L_00454358:
        dec esi
    L_00454359:
        cmp esi,3Fh
    L_0045435c:
        mov dword ptr [ebp+0Ch],ebx
    L_0045435f:
        mov dword ptr [ebx-4],ecx
    L_00454362:
        jbe short L_00454367
    L_00454364:
        push 3Fh
    L_00454366:
        pop esi
    L_00454367:
        test byte ptr [ebp-4],1
    L_0045436b:
        jne asm_target_004543f1
    L_00454371:
        mov esi,dword ptr [ebp-4]
    L_00454374:
        sar esi,4
    L_00454377:
        dec esi
    L_00454378:
        cmp esi,3Fh
    L_0045437b:
        jbe short L_00454380
    L_0045437d:
        push 3Fh
    L_0045437f:
        pop esi
    L_00454380:
        mov ecx,dword ptr [edi+4]
    L_00454383:
        cmp ecx,dword ptr [edi+8]
    L_00454386:
        jne short L_004543ca
    L_00454388:
        cmp esi,20h
    L_0045438b:
        mov ebx,80000000h
    L_00454390:
        jae short L_004543ab
    L_00454392:
        mov ecx,esi
    L_00454394:
        shr ebx,cl
    L_00454396:
        lea esi,[esi+eax+4]
    L_0045439a:
        not ebx
    L_0045439c:
        and dword ptr [eax+edx*4+44h],ebx
    L_004543a0:
        dec byte ptr [esi]
    L_004543a2:
        jne short L_004543c7
    L_004543a4:
        mov ecx,dword ptr [ebp+8]
    L_004543a7:
        and dword ptr [ecx],ebx
    L_004543a9:
        jmp short L_004543c7
    L_004543ab:
        lea ecx,[esi-20h]
    L_004543ae:
        shr ebx,cl
    L_004543b0:
        lea ecx,[esi+eax+4]
    L_004543b4:
        not ebx
    L_004543b6:
        and dword ptr [eax+edx*4+0C4h],ebx
    L_004543bd:
        dec byte ptr [ecx]
    L_004543bf:
        jne short L_004543c7
    L_004543c1:
        mov ecx,dword ptr [ebp+8]
    L_004543c4:
        and dword ptr [ecx+4],ebx
    L_004543c7:
        mov ebx,dword ptr [ebp+0Ch]
    L_004543ca:
        mov ecx,dword ptr [edi+8]
    L_004543cd:
        mov esi,dword ptr [edi+4]
    L_004543d0:
        mov dword ptr [ecx+4],esi
    L_004543d3:
        mov esi,dword ptr [edi+8]
    L_004543d6:
        mov ecx,dword ptr [edi+4]
    L_004543d9:
        mov dword ptr [ecx+8],esi
    L_004543dc:
        mov esi,dword ptr [ebp+10h]
    L_004543df:
        add esi,dword ptr [ebp-4]
    L_004543e2:
        mov dword ptr [ebp+10h],esi
    L_004543e5:
        sar esi,4
    L_004543e8:
        dec esi
    L_004543e9:
        cmp esi,3Fh
    L_004543ec:
        jbe short L_004543f1
    L_004543ee:
        push 3Fh
    L_004543f0:
        pop esi
    L_004543f1:
        mov ecx,dword ptr [ebp-0Ch]
    L_004543f4:
        lea ecx,[ecx+esi*8]
    L_004543f7:
        mov edi,dword ptr [ecx+4]
    L_004543fa:
        mov dword ptr [ebx+8],ecx
    L_004543fd:
        mov dword ptr [ebx+4],edi
    L_00454400:
        mov dword ptr [ecx+4],ebx
    L_00454403:
        mov ecx,dword ptr [ebx+4]
    L_00454406:
        mov dword ptr [ecx+8],ebx
    L_00454409:
        mov ecx,dword ptr [ebx+4]
    L_0045440c:
        cmp ecx,dword ptr [ebx+8]
    L_0045440f:
        jne short L_00454468
    L_00454411:
        mov cl,byte ptr [esi+eax+4]
    L_00454415:
        mov byte ptr [ebp+0Fh],cl
    L_00454418:
        inc cl
    L_0045441a:
        cmp esi,20h
    L_0045441d:
        mov byte ptr [esi+eax+4],cl
    L_00454421:
        jae short L_0045443f
    L_00454423:
        cmp byte ptr [ebp+0Fh],0
    L_00454427:
        jne short L_00454437
    L_00454429:
        mov ecx,esi
    L_0045442b:
        mov edi,80000000h
    L_00454430:
        shr edi,cl
    L_00454432:
        mov ecx,dword ptr [ebp+8]
    L_00454435:
        or dword ptr [ecx],edi
    L_00454437:
        lea eax,[eax+edx*4+44h]
    L_0045443b:
        mov ecx,esi
    L_0045443d:
        jmp short L_0045445f
    L_0045443f:
        cmp byte ptr [ebp+0Fh],0
    L_00454443:
        jne short L_00454455
    L_00454445:
        lea ecx,[esi-20h]
    L_00454448:
        mov edi,80000000h
    L_0045444d:
        shr edi,cl
    L_0045444f:
        mov ecx,dword ptr [ebp+8]
    L_00454452:
        or dword ptr [ecx+4],edi
    L_00454455:
        lea eax,[eax+edx*4+0C4h]
    L_0045445c:
        lea ecx,[esi-20h]
    L_0045445f:
        mov edx,80000000h
    L_00454464:
        shr edx,cl
    L_00454466:
        or dword ptr [eax],edx
    L_00454468:
        mov eax,dword ptr [ebp+10h]
    L_0045446b:
        mov dword ptr [ebx],eax
    L_0045446d:
        mov dword ptr [eax+ebx-4],eax
    L_00454471:
        xor eax,eax
    L_00454473:
        inc eax
    L_00454474:
        pop edi
    L_00454475:
        pop esi
    L_00454476:
        pop ebx
    L_00454477:
        leave
    L_00454478:
        ret
    }
}

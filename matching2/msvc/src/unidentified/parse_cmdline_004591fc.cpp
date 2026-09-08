#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004591FC..0x00459367: parse_cmdline
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_parse_cmdline_004591fc() {
    __asm {
    L_004591fc:
        push ebp
    L_004591fd:
        mov ebp,esp
    L_004591ff:
        push ecx
    L_00459200:
        push ebx
    L_00459201:
        mov ebx,dword ptr [ebp+0Ch]
    L_00459204:
        xor edx,edx
    L_00459206:
        cmp dword ptr [ebp+8],edx
    L_00459209:
        push edi
    L_0045920a:
        mov dword ptr [esi],edx
    L_0045920c:
        mov edi,ecx
    L_0045920e:
        mov dword ptr [ebx],1
    L_00459214:
        je short L_0045921f
    L_00459216:
        mov ecx,dword ptr [ebp+8]
    L_00459219:
        add dword ptr [ebp+8],4
    L_0045921d:
        mov dword ptr [ecx],edi
    L_0045921f:
        cmp byte ptr [eax],22h
    L_00459222:
        jne short L_00459232
    L_00459224:
        xor ecx,ecx
    L_00459226:
        test edx,edx
    L_00459228:
        sete cl
    L_0045922b:
        inc eax
    L_0045922c:
        mov edx,ecx
    L_0045922e:
        mov cl,22h
    L_00459230:
        jmp short L_0045925f
    L_00459232:
        inc dword ptr [esi]
    L_00459234:
        test edi,edi
    L_00459236:
        je short L_0045923d
    L_00459238:
        mov cl,byte ptr [eax]
    L_0045923a:
        mov byte ptr [edi],cl
    L_0045923c:
        inc edi
    L_0045923d:
        mov cl,byte ptr [eax]
    L_0045923f:
        movzx ebx,cl
    L_00459242:
        inc eax
    L_00459243:
        test byte ptr [ebx+497FA1h],4
    L_0045924a:
        je short L_00459258
    L_0045924c:
        inc dword ptr [esi]
    L_0045924e:
        test edi,edi
    L_00459250:
        je short L_00459257
    L_00459252:
        mov bl,byte ptr [eax]
    L_00459254:
        mov byte ptr [edi],bl
    L_00459256:
        inc edi
    L_00459257:
        inc eax
    L_00459258:
        test cl,cl
    L_0045925a:
        mov ebx,dword ptr [ebp+0Ch]
    L_0045925d:
        je short L_00459291
    L_0045925f:
        test edx,edx
    L_00459261:
        jne short L_0045921f
    L_00459263:
        cmp cl,20h
    L_00459266:
        je short L_0045926d
    L_00459268:
        cmp cl,9
    L_0045926b:
        jne short L_0045921f
    L_0045926d:
        test edi,edi
    L_0045926f:
        je short L_00459275
    L_00459271:
        mov byte ptr [edi-1],0
    L_00459275:
        and dword ptr [ebp-4],0
    L_00459279:
        cmp byte ptr [eax],0
    L_0045927c:
        je asm_target_00459358
    L_00459282:
        mov cl,byte ptr [eax]
    L_00459284:
        cmp cl,20h
    L_00459287:
        je short L_0045928e
    L_00459289:
        cmp cl,9
    L_0045928c:
        jne short L_00459294
    L_0045928e:
        inc eax
    L_0045928f:
        jmp short L_00459282
    L_00459291:
        dec eax
    L_00459292:
        jmp short L_00459275
    L_00459294:
        cmp byte ptr [eax],0
    L_00459297:
        je asm_target_00459358
    L_0045929d:
        cmp dword ptr [ebp+8],0
    L_004592a1:
        je short L_004592ac
    L_004592a3:
        mov ecx,dword ptr [ebp+8]
    L_004592a6:
        add dword ptr [ebp+8],4
    L_004592aa:
        mov dword ptr [ecx],edi
    L_004592ac:
        inc dword ptr [ebx]
    L_004592ae:
        xor ebx,ebx
    L_004592b0:
        inc ebx
    L_004592b1:
        xor edx,edx
    L_004592b3:
        jmp short L_004592b7
    L_004592b5:
        inc eax
    L_004592b6:
        inc edx
    L_004592b7:
        cmp byte ptr [eax],5Ch
    L_004592ba:
        je short L_004592b5
    L_004592bc:
        cmp byte ptr [eax],22h
    L_004592bf:
        jne short L_004592e7
    L_004592c1:
        test dl,1
    L_004592c4:
        jne short L_004592e5
    L_004592c6:
        cmp dword ptr [ebp-4],0
    L_004592ca:
        je short L_004592d8
    L_004592cc:
        lea ecx,[eax+1]
    L_004592cf:
        cmp byte ptr [ecx],22h
    L_004592d2:
        jne short L_004592d8
    L_004592d4:
        mov eax,ecx
    L_004592d6:
        jmp short L_004592da
    L_004592d8:
        xor ebx,ebx
    L_004592da:
        xor ecx,ecx
    L_004592dc:
        cmp dword ptr [ebp-4],ecx
    L_004592df:
        sete cl
    L_004592e2:
        mov dword ptr [ebp-4],ecx
    L_004592e5:
        shr edx,1
    L_004592e7:
        test edx,edx
    L_004592e9:
        je short L_004592f8
    L_004592eb:
        test edi,edi
    L_004592ed:
        je short L_004592f3
    L_004592ef:
        mov byte ptr [edi],5Ch
    L_004592f2:
        inc edi
    L_004592f3:
        inc dword ptr [esi]
    L_004592f5:
        dec edx
    L_004592f6:
        jne short L_004592eb
    L_004592f8:
        mov cl,byte ptr [eax]
    L_004592fa:
        test cl,cl
    L_004592fc:
        je short L_00459346
    L_004592fe:
        cmp dword ptr [ebp-4],0
    L_00459302:
        jne short L_0045930e
    L_00459304:
        cmp cl,20h
    L_00459307:
        je short L_00459346
    L_00459309:
        cmp cl,9
    L_0045930c:
        je short L_00459346
    L_0045930e:
        test ebx,ebx
    L_00459310:
        je short L_00459340
    L_00459312:
        test edi,edi
    L_00459314:
        je short L_0045932f
    L_00459316:
        movzx edx,cl
    L_00459319:
        test byte ptr [edx+497FA1h],4
    L_00459320:
        je short L_00459328
    L_00459322:
        mov byte ptr [edi],cl
    L_00459324:
        inc edi
    L_00459325:
        inc eax
    L_00459326:
        inc dword ptr [esi]
    L_00459328:
        mov cl,byte ptr [eax]
    L_0045932a:
        mov byte ptr [edi],cl
    L_0045932c:
        inc edi
    L_0045932d:
        jmp short L_0045933e
    L_0045932f:
        movzx ecx,cl
    L_00459332:
        test byte ptr [ecx+497FA1h],4
    L_00459339:
        je short L_0045933e
    L_0045933b:
        inc eax
    L_0045933c:
        inc dword ptr [esi]
    L_0045933e:
        inc dword ptr [esi]
    L_00459340:
        inc eax
    L_00459341:
        jmp asm_target_004592ae
    L_00459346:
        test edi,edi
    L_00459348:
        je short L_0045934e
    L_0045934a:
        mov byte ptr [edi],0
    L_0045934d:
        inc edi
    L_0045934e:
        inc dword ptr [esi]
    L_00459350:
        mov ebx,dword ptr [ebp+0Ch]
    L_00459353:
        jmp asm_target_00459279
    L_00459358:
        mov eax,dword ptr [ebp+8]
    L_0045935b:
        test eax,eax
    L_0045935d:
        je short L_00459362
    L_0045935f:
        and dword ptr [eax],0
    L_00459362:
        inc dword ptr [ebx]
    L_00459364:
        pop edi
    L_00459365:
        pop ebx
    L_00459366:
        leave
    L_00459367:
        ret
    }
}

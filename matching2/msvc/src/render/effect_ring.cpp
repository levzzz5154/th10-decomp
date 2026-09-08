#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004452F0..0x00445612: FUN_004452f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004452f0_004452f0() {
    __asm {
    L_004452f0:
        mov eax,dword ptr [edi+358h]
    L_004452f6:
        sub esp,28h
    L_004452f9:
        test eax,eax
    L_004452fb:
        je short L_00445310
    L_004452fd:
        push eax
    L_004452fe:
        call asm_free_00452422
    L_00445303:
        add esp,4
    L_00445306:
        mov dword ptr [edi+358h],0
    L_00445310:
        push ebx
    L_00445311:
        push ebp
    L_00445312:
        push esi
    L_00445313:
        push 4B0h
    L_00445318:
        call asm_malloc_00452706
    L_0044531d:
        mov ebx,eax
    L_0044531f:
        add esp,4
    L_00445322:
        mov ecx,4918B0h
    L_00445327:
        mov dword ptr [edi+358h],ebx
    L_0044532d:
        mov dword ptr [edi+398h],445620h
    L_00445337:
        mov dword ptr [edi+39Ch],445880h
    L_00445341:
        call asm_Rng_NextFloatSigned_0044bb90
    L_00445346:
        fmul dword ptr [data_00470c7c]
    L_0044534c:
        mov ecx,4918B0h
    L_00445351:
        fstp dword ptr [ebx+4A4h]
    L_00445357:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0044535c:
        fmul dword ptr [data_00470c7c]
    L_00445362:
        mov eax,ebx
    L_00445364:
        mov dword ptr [esp+10h],0C0490FDBh
    L_0044536c:
        lea esi,[ebx+1Ch]
    L_0044536f:
        fstp dword ptr [ebx+4A8h]
    L_00445375:
        fld dword ptr [edi+340h]
    L_0044537b:
        fadd dword ptr [edi+334h]
    L_00445381:
        fstp dword ptr [esp+1Ch]
    L_00445385:
        mov ecx,dword ptr [esp+1Ch]
    L_00445389:
        fld dword ptr [edi+344h]
    L_0044538f:
        fadd dword ptr [edi+338h]
    L_00445395:
        fstp dword ptr [esp+20h]
    L_00445399:
        mov edx,dword ptr [esp+20h]
    L_0044539d:
        fld dword ptr [edi+348h]
    L_004453a3:
        fadd dword ptr [edi+33Ch]
    L_004453a9:
        mov dword ptr [eax],ecx
    L_004453ab:
        mov dword ptr [eax+4],edx
    L_004453ae:
        mov dword ptr [ebx+0Ch],3F800000h
    L_004453b5:
        fstp dword ptr [esp+24h]
    L_004453b9:
        mov ecx,dword ptr [esp+24h]
    L_004453bd:
        mov dword ptr [eax+8],ecx
    L_004453c0:
        mov eax,3F000000h
    L_004453c5:
        mov ecx,4918B0h
    L_004453ca:
        mov dword ptr [ebx+14h],eax
    L_004453cd:
        mov dword ptr [ebx+18h],eax
    L_004453d0:
        call asm_Rng_NextFloatSigned_0044bb90
    L_004453d5:
        fmul dword ptr [data_00470c78]
    L_004453db:
        lea edx,[ebx+3A0h]
    L_004453e1:
        mov dword ptr [esp+14h],1Fh
    L_004453e9:
        fstp dword ptr [esp+0Ch]
    L_004453ed:
        TH10_NOP_LEA_ECX_DISP8()
    L_004453f0:
        fld dword ptr [esp+10h]
    L_004453f4:
        fcomp dword ptr [data_00470b18]
    L_004453fa:
        fnstsw ax
    L_004453fc:
        test ah,1
    L_004453ff:
        jne short L_0044540f
    L_00445401:
        fld dword ptr [esp+10h]
    L_00445405:
        fsub dword ptr [data_00470b14]
    L_0044540b:
        fstp dword ptr [esp+10h]
    L_0044540f:
        mov ebp,dword ptr [esp+10h]
    L_00445413:
        push 3F000000h
    L_00445418:
        push ebp
    L_00445419:
        lea ecx,[esp+24h]
    L_0044541d:
        mov dword ptr [esi+0Ch],3F800000h
    L_00445424:
        call asm_Vector2_SetPolar_004458b0
    L_00445429:
        fld dword ptr [esp+1Ch]
    L_0044542d:
        fadd dword ptr [data_00470b0c]
    L_00445433:
        xor ecx,ecx
    L_00445435:
        mov dword ptr [esi+8],0
    L_0044543c:
        fstp dword ptr [esi+14h]
    L_0044543f:
        fld dword ptr [esp+20h]
    L_00445443:
        fadd dword ptr [data_00470b0c]
    L_00445449:
        fstp dword ptr [esi+18h]
    L_0044544c:
        mov eax,dword ptr [data_004918b0]
    L_00445451:
        xor eax,9630h
    L_00445456:
        sub eax,6553h
    L_0044545b:
        mov cx,ax
    L_0044545e:
        shr cx,0Eh
    L_00445462:
        shl eax,2
    L_00445465:
        mov ebx,dword ptr [data_004918b4]
    L_0044546b:
        add ecx,eax
    L_0044546d:
        mov word ptr [data_004918b0],cx
    L_00445474:
        mov eax,dword ptr [data_004918b0]
    L_00445479:
        xor eax,9630h
    L_0044547e:
        xor ecx,ecx
    L_00445480:
        sub eax,6553h
    L_00445485:
        mov cx,ax
    L_00445488:
        shr cx,0Eh
    L_0044548c:
        shl eax,2
    L_0044548f:
        inc ebx
    L_00445490:
        add ecx,eax
    L_00445492:
        movzx eax,cx
    L_00445495:
        mov word ptr [data_004918b0],cx
    L_0044549c:
        mov ecx,eax
    L_0044549e:
        shl ecx,10h
    L_004454a1:
        or ecx,eax
    L_004454a3:
        inc ebx
    L_004454a4:
        test ecx,ecx
    L_004454a6:
        mov dword ptr [esp+18h],ecx
    L_004454aa:
        mov dword ptr [data_004918b4],ebx
    L_004454b0:
        fild dword ptr [esp+18h]
    L_004454b4:
        jge short L_004454bc
    L_004454b6:
        fadd dword ptr [data_00470b98]
    L_004454bc:
        mov eax,dword ptr [esp+0Ch]
    L_004454c0:
        fmul dword ptr [data_00470bec]
    L_004454c6:
        mov dword ptr [edx+84h],eax
    L_004454cc:
        xor ecx,ecx
    L_004454ce:
        fsub dword ptr [data_00470afc]
    L_004454d4:
        fmul dword ptr [data_00470bd0]
    L_004454da:
        fadd dword ptr [data_00470c28]
    L_004454e0:
        fstp dword ptr [edx]
    L_004454e2:
        mov eax,dword ptr [data_004918b0]
    L_004454e7:
        xor eax,9630h
    L_004454ec:
        sub eax,6553h
    L_004454f1:
        mov cx,ax
    L_004454f4:
        shr cx,0Eh
    L_004454f8:
        shl eax,2
    L_004454fb:
        mov ebx,dword ptr [data_004918b4]
    L_00445501:
        add ecx,eax
    L_00445503:
        mov word ptr [data_004918b0],cx
    L_0044550a:
        mov eax,dword ptr [data_004918b0]
    L_0044550f:
        xor eax,9630h
    L_00445514:
        xor ecx,ecx
    L_00445516:
        sub eax,6553h
    L_0044551b:
        mov cx,ax
    L_0044551e:
        shr cx,0Eh
    L_00445522:
        shl eax,2
    L_00445525:
        inc ebx
    L_00445526:
        add ecx,eax
    L_00445528:
        movzx eax,cx
    L_0044552b:
        mov word ptr [data_004918b0],cx
    L_00445532:
        mov ecx,eax
    L_00445534:
        shl ecx,10h
    L_00445537:
        or ecx,eax
    L_00445539:
        inc ebx
    L_0044553a:
        test ecx,ecx
    L_0044553c:
        mov dword ptr [esp+18h],ecx
    L_00445540:
        mov dword ptr [data_004918b4],ebx
    L_00445546:
        fild dword ptr [esp+18h]
    L_0044554a:
        jge short L_00445552
    L_0044554c:
        fadd dword ptr [data_00470b98]
    L_00445552:
        fmul dword ptr [data_00470bec]
    L_00445558:
        fsub dword ptr [data_00470afc]
    L_0044555e:
        fmul dword ptr [data_00470c74]
    L_00445564:
        fadd dword ptr [esp+0Ch]
    L_00445568:
        fst dword ptr [esp+0Ch]
    L_0044556c:
        fcomp dword ptr [data_00470c70]
    L_00445572:
        fnstsw ax
    L_00445574:
        test ah,5
    L_00445577:
        jp short L_00445583
    L_00445579:
        mov dword ptr [esp+0Ch],0BD888889h
    L_00445581:
        jmp short L_0044559c
    L_00445583:
        fld dword ptr [esp+0Ch]
    L_00445587:
        fcomp dword ptr [data_00470c78]
    L_0044558d:
        fnstsw ax
    L_0044558f:
        test ah,41h
    L_00445592:
        jne short L_0044559c
    L_00445594:
        mov dword ptr [esp+0Ch],3D888889h
    L_0044559c:
        mov eax,dword ptr [edx]
    L_0044559e:
        push eax
    L_0044559f:
        push ebp
    L_004455a0:
        mov ecx,esi
    L_004455a2:
        call asm_Vector2_SetPolar_004458b0
    L_004455a7:
        fld dword ptr [edi+340h]
    L_004455ad:
        fadd dword ptr [edi+334h]
    L_004455b3:
        mov eax,dword ptr [esp+14h]
    L_004455b7:
        fld dword ptr [edi+338h]
    L_004455bd:
        add esi,1Ch
    L_004455c0:
        fadd dword ptr [edi+344h]
    L_004455c6:
        add edx,4
    L_004455c9:
        fld dword ptr [edi+348h]
    L_004455cf:
        dec eax
    L_004455d0:
        fadd dword ptr [edi+33Ch]
    L_004455d6:
        mov dword ptr [esp+14h],eax
    L_004455da:
        fstp dword ptr [esp+30h]
    L_004455de:
        fxch
    L_004455e0:
        fadd dword ptr [esi-1Ch]
    L_004455e3:
        fstp dword ptr [esi-1Ch]
    L_004455e6:
        fadd dword ptr [esi-18h]
    L_004455e9:
        fstp dword ptr [esi-18h]
    L_004455ec:
        fld dword ptr [esp+30h]
    L_004455f0:
        fadd dword ptr [esi-14h]
    L_004455f3:
        fstp dword ptr [esi-14h]
    L_004455f6:
        fld dword ptr [esp+10h]
    L_004455fa:
        fadd dword ptr [data_00470b6c]
    L_00445600:
        fstp dword ptr [esp+10h]
    L_00445604:
        jne asm_target_004453f0
    L_0044560a:
        pop esi
    L_0044560b:
        pop ebp
    L_0044560c:
        xor eax,eax
    L_0044560e:
        pop ebx
    L_0044560f:
        add esp,28h
    L_00445612:
        ret
    }
}

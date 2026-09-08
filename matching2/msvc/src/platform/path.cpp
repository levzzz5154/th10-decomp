#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417010..0x00417038: ?Path_DecodeXor@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Path_DecodeXor_00417010() {
    __asm {
    L_00417010:
        push esi
    L_00417011:
        push edi
    L_00417012:
        mov edi,eax
    L_00417014:
        mov cl,77h
    L_00417016:
        mov dl,7
    L_00417018:
        mov esi,497D40h
    L_0041701d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00417020:
        mov al,byte ptr [edi]
    L_00417022:
        xor al,cl
    L_00417024:
        mov byte ptr [esi],al
    L_00417026:
        inc esi
    L_00417027:
        add cl,dl
    L_00417029:
        inc edi
    L_0041702a:
        add dl,10h
    L_0041702d:
        test al,al
    L_0041702f:
        jne short L_00417020
    L_00417031:
        pop edi
    L_00417032:
        mov eax,497D40h
    L_00417037:
        pop esi
    L_00417038:
        ret
    }
}

// 0x0043D2A0..0x0043D382: ?Path_FindBasenameSlot@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Path_FindBasenameSlot_0043d2a0() {
    __asm {
    L_0043d2a0:
        sub esp,84h
    L_0043d2a6:
        mov eax,dword ptr [data_00473660]
    L_0043d2ab:
        xor eax,esp
    L_0043d2ad:
        push ebp
    L_0043d2ae:
        push esi
    L_0043d2af:
        mov esi,ecx
    L_0043d2b1:
        push 2Fh
    L_0043d2b3:
        push esi
    L_0043d2b4:
        mov dword ptr [esp+90h],eax
    L_0043d2bb:
        xor ebp,ebp
    L_0043d2bd:
        call asm_strrchr_00452930
    L_0043d2c2:
        add esp,8
    L_0043d2c5:
        test eax,eax
    L_0043d2c7:
        jne short L_0043d2ec
    L_0043d2c9:
        push 5Ch
    L_0043d2cb:
        push esi
    L_0043d2cc:
        call asm_strrchr_00452930
    L_0043d2d1:
        add esp,8
    L_0043d2d4:
        test eax,eax
    L_0043d2d6:
        jne short L_0043d2ec
    L_0043d2d8:
        lea edx,[esp+8]
    L_0043d2dc:
        mov eax,esi
    L_0043d2de:
        sub edx,esi
    L_0043d2e0:
        mov cl,byte ptr [eax]
    L_0043d2e2:
        mov byte ptr [edx+eax],cl
    L_0043d2e5:
        inc eax
    L_0043d2e6:
        test cl,cl
    L_0043d2e8:
        jne short L_0043d2e0
    L_0043d2ea:
        jmp short L_0043d2fd
    L_0043d2ec:
        inc eax
    L_0043d2ed:
        lea edx,[esp+8]
    L_0043d2f1:
        sub edx,eax
    L_0043d2f3:
        mov cl,byte ptr [eax]
    L_0043d2f5:
        mov byte ptr [edx+eax],cl
    L_0043d2f8:
        inc eax
    L_0043d2f9:
        test cl,cl
    L_0043d2fb:
        jne short L_0043d2f3
    L_0043d2fd:
        mov eax,dword ptr [esp+90h]
    L_0043d304:
        push edi
    L_0043d305:
        mov edi,dword ptr [eax+1F84h]
    L_0043d30b:
        cmp byte ptr [edi],0
    L_0043d30e:
        je short L_0043d358
    L_0043d310:
        mov eax,edi
    L_0043d312:
        push ebx
    L_0043d313:
        lea esi,[esp+10h]
    L_0043d317:
        mov dl,byte ptr [eax]
    L_0043d319:
        mov bl,byte ptr [esi]
    L_0043d31b:
        mov cl,dl
    L_0043d31d:
        cmp dl,bl
    L_0043d31f:
        jne short L_0043d33f
    L_0043d321:
        test cl,cl
    L_0043d323:
        je short L_0043d33b
    L_0043d325:
        mov dl,byte ptr [eax+1]
    L_0043d328:
        mov bl,byte ptr [esi+1]
    L_0043d32b:
        mov cl,dl
    L_0043d32d:
        cmp dl,bl
    L_0043d32f:
        jne short L_0043d33f
    L_0043d331:
        add eax,2
    L_0043d334:
        add esi,2
    L_0043d337:
        test cl,cl
    L_0043d339:
        jne short L_0043d317
    L_0043d33b:
        xor eax,eax
    L_0043d33d:
        jmp short L_0043d344
    L_0043d33f:
        sbb eax,eax
    L_0043d341:
        sbb eax,0FFFFFFFFh
    L_0043d344:
        test eax,eax
    L_0043d346:
        je short L_0043d357
    L_0043d348:
        inc ebp
    L_0043d349:
        mov eax,ebp
    L_0043d34b:
        imul eax,34h
    L_0043d34e:
        mov cl,byte ptr [eax+edi]
    L_0043d351:
        add eax,edi
    L_0043d353:
        test cl,cl
    L_0043d355:
        jne short L_0043d313
    L_0043d357:
        pop ebx
    L_0043d358:
        mov ecx,ebp
    L_0043d35a:
        imul ecx,34h
    L_0043d35d:
        cmp byte ptr [ecx+edi],0
    L_0043d361:
        pop edi
    L_0043d362:
        jne short L_0043d368
    L_0043d364:
        xor eax,eax
    L_0043d366:
        jmp short L_0043d36a
    L_0043d368:
        mov eax,ebp
    L_0043d36a:
        mov ecx,dword ptr [esp+88h]
    L_0043d371:
        pop esi
    L_0043d372:
        pop ebp
    L_0043d373:
        xor ecx,esp
    L_0043d375:
        call asm_security_check_cookie_00458ea5
    L_0043d37a:
        add esp,84h
    L_0043d380:
        ret 4
    }
}

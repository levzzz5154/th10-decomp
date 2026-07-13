// 0043D2A0: FUN_0043d2a0
// Original size: 240 bytes, actual code: 90 instructions
extern "C" void _strrchr(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0043d2a0(void) {
    __asm {
        sub  esp,0x84
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebp
        push  esi
        mov  esi,ecx
        push  0x2f
        push  esi
        mov  DWORD PTR [esp+0x90],eax
        xor  ebp,ebp
        call _strrchr
        add  esp,0x8
        test  eax,eax
        jne loc_0043D2EC
        push  0x5c
        push  esi
        call _strrchr
        add  esp,0x8
        test  eax,eax
        jne loc_0043D2EC
        lea  edx,[esp+0x8]
        mov  eax,esi
        sub  edx,esi
    loc_0043D2E0:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_0043D2E0
        jmp loc_0043D2FD
    loc_0043D2EC:
        inc  eax
        lea  edx,[esp+0x8]
        sub  edx,eax
    loc_0043D2F3:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_0043D2F3
    loc_0043D2FD:
        mov  eax,DWORD PTR [esp+0x90]
        push  edi
        mov  edi,DWORD PTR [eax+0x1f84]
        cmp  BYTE PTR [edi],0x0
        je loc_0043D358
        mov  eax,edi
        push  ebx
    loc_0043D313:
        lea  esi,[esp+0x10]
    loc_0043D317:
        mov  dl,BYTE PTR [eax]
        mov  bl,BYTE PTR [esi]
        mov  cl,dl
        cmp  dl,bl
        jne loc_0043D33F
        test  cl,cl
        je loc_0043D33B
        mov  dl,BYTE PTR [eax+0x1]
        mov  bl,BYTE PTR [esi+0x1]
        mov  cl,dl
        cmp  dl,bl
        jne loc_0043D33F
        add  eax,0x2
        add  esi,0x2
        test  cl,cl
        jne loc_0043D317
    loc_0043D33B:
        xor  eax,eax
        jmp loc_0043D344
    loc_0043D33F:
        sbb  eax,eax
        sbb  eax,0xffffffff
    loc_0043D344:
        test  eax,eax
        je loc_0043D357
        inc  ebp
        mov  eax,ebp
        imul  eax,eax,0x34
        mov  cl,BYTE PTR [eax+edi*1]
        add  eax,edi
        test  cl,cl
        jne loc_0043D313
    loc_0043D357:
        pop  ebx
    loc_0043D358:
        mov  ecx,ebp
        imul  ecx,ecx,0x34
        cmp  BYTE PTR [ecx+edi*1],0x0
        pop  edi
        jne loc_0043D368
        xor  eax,eax
        jmp loc_0043D36A
    loc_0043D368:
        mov  eax,ebp
    loc_0043D36A:
        mov  ecx,DWORD PTR [esp+0x88]
        pop  esi
        pop  ebp
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x84
        ret  0x4
    }
}

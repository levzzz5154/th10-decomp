// 00439FF0: FUN_00439ff0
// Original size: 464 bytes, actual code: 135 instructions
extern "C" void FUN_0043a290(void);
extern "C" void FUN_0044b4d0(void);
extern "C" void FUN_0044b8e0(void);
extern "C" void _strrchr(void);
extern "C" void __security_check_cookie(void);
extern "C" void __stricmp(void);

extern "C" __declspec(naked) void FUN_00439ff0(void) {
    __asm {
        sub  esp,0x258
        mov  eax,ds:0x473660
        xor  eax,esp
        push  edi
        push  0x46f3ac
        push  0x1
        push  0x0
        mov  DWORD PTR [esp+0x264],eax
        call  DWORD PTR ds:0x466110
        mov  ds:0x497ba8,eax
        call  DWORD PTR ds:0x46610c
        cmp  eax,0xb7
        jne loc_0043A051
        push  0x46f394
        mov  edi,0x474f70
        call FUN_0044b8e0
        add  esp,0x4
        or   eax,0xffffffff
        pop  edi
        mov  ecx,DWORD PTR [esp+0x254]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x258
        ret
    loc_0043A051:
        xor  eax,eax
        mov  DWORD PTR [esp+0x4],0x44
        mov  ecx,0x10
        lea  edi,[esp+0x8]
        rep stosd
        push  0x105
        lea  eax,[esp+0x154]
        push  eax
        push  0x0
        call  DWORD PTR ds:0x4660dc
        push  0x105
        lea  ecx,[esp+0x4c]
        push  ecx
        call  DWORD PTR ds:0x466100
        lea  edx,[esp+0x4]
        push  edx
        call  DWORD PTR ds:0x466108
        mov  eax,DWORD PTR [esp+0x10]
        test  eax,eax
        je loc_0043A179
        push  esi
        push  0x2e
        push  eax
        call _strrchr
        mov  esi,eax
        mov  eax,DWORD PTR [esp+0x1c]
        add  esp,0x8
        push  eax
        call FUN_0044b4d0
        test  eax,eax
        je loc_0043A16E
        test  esi,esi
        je loc_0043A16E
        push  ebx
        push  0x46f38c
        push  esi
        call __stricmp
        add  esp,0x8
        test  eax,eax
        jne loc_0043A111
        nop
    loc_0043A0E0:
        mov  ecx,DWORD PTR [esp+0x18]
        push  ecx
        mov  edi,0x104
        lea  ebx,[esp+0x54]
        call FUN_0043a290
        mov  edx,ebx
        push  0x2e
        push  edx
        call _strrchr
        push  0x46f38c
        push  eax
        call __stricmp
        add  esp,0x10
        test  eax,eax
        je loc_0043A0E0
        jmp loc_0043A12A
    loc_0043A111:
        mov  eax,DWORD PTR [esp+0x18]
        lea  edx,[esp+0x50]
        sub  edx,eax
        jmp loc_0043A120
        nop
    loc_0043A120:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_0043A120
    loc_0043A12A:
        lea  esi,[esp+0x50]
        lea  eax,[esp+0x158]
    loc_0043A135:
        mov  dl,BYTE PTR [eax]
        mov  bl,BYTE PTR [esi]
        mov  cl,dl
        cmp  dl,bl
        jne loc_0043A15D
        test  cl,cl
        je loc_0043A159
        mov  dl,BYTE PTR [eax+0x1]
        mov  bl,BYTE PTR [esi+0x1]
        mov  cl,dl
        cmp  dl,bl
        jne loc_0043A15D
        add  eax,0x2
        add  esi,0x2
        test  cl,cl
        jne loc_0043A135
    loc_0043A159:
        xor  eax,eax
        jmp loc_0043A162
    loc_0043A15D:
        sbb  eax,eax
        sbb  eax,0xffffffff
    loc_0043A162:
        test  eax,eax
        pop  ebx
        je loc_0043A16E
        mov  BYTE PTR ds:0x492518,0x1
    loc_0043A16E:
        mov  eax,ds:0x491ff4
        and  eax,0xffffffbf
        pop  esi
        jmp loc_0043A181
    loc_0043A179:
        mov  eax,ds:0x491ff4
        or   eax,0x40
    loc_0043A181:
        mov  edx,DWORD PTR ds:0x497ba8
        mov  ecx,DWORD PTR [esp+0x258]
        mov  ds:0x491ff4,eax
        xor  eax,eax
        test  edx,edx
        setne al
        pop  edi
        xor  ecx,esp
        dec  eax
        call __security_check_cookie
        add  esp,0x258
        ret
    }
}

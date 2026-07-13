// 0042A200: FUN_0042a200
// Original size: 592 bytes, actual code: 138 instructions
extern "C" void FUN_00435dc0(void);
extern "C" void FUN_0044b0d0(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b4d0(void);
extern "C" void FUN_0044b6b0(void);
extern "C" void FUN_0044b790(void);
extern "C" void FUN_0044b7e0(void);
extern "C" void _free(void);
extern "C" void _malloc(void);
extern "C" void _sprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0042a200(void) {
    __asm {
        sub  esp,0x108
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x104],eax
        mov  eax,DWORD PTR [esp+0x10c]
        mov  edx,esi
        push  ebp
        sub  edx,eax
        push  edi
        mov  ecx,eax
        lea  edi,[edx+0x1d4]
        nop
    loc_0042A230:
        mov  dl,BYTE PTR [ecx]
        mov  BYTE PTR [edi+ecx*1],dl
        inc  ecx
        test  dl,dl
        jne loc_0042A230
        test  BYTE PTR ds:0x474ca0,0x20
        jne loc_0042A2AC
        push  eax
        lea  eax,[esp+0x10]
        push  0x46e644
        push  eax
        call _sprintf
        add  esp,0xc
        lea  ecx,[esp+0xc]
        push  ecx
        call FUN_0044b4d0
        test  eax,eax
        je loc_0042A293
        lea  edx,[esp+0xc]
        push  edx
        call FUN_0044b6b0
        test  eax,eax
        jne loc_0042A293
        mov  edi,0x24
        call FUN_0044b790
        mov  DWORD PTR [esi+0x14],eax
        cmp  DWORD PTR [eax],0x72303174
        jne loc_0042A28E
        cmp  WORD PTR [eax+0x4],0x5
        je loc_0042A29B
    loc_0042A28E:
        call FUN_0044b7e0
    loc_0042A293:
        or   eax,0xffffffff
        jmp loc_0042A3A9
    loc_0042A29B:
        mov  edi,DWORD PTR [eax+0x1c]
        call FUN_0044b790
        mov  ebp,eax
        call FUN_0044b7e0
        jmp loc_0042A2BE
    loc_0042A2AC:
        push  0x0
        lea  ecx,[esp+0xc]
        push  ecx
        call FUN_0044b360
        mov  DWORD PTR [esi+0x14],eax
        lea  ebp,[eax+0x24]
    loc_0042A2BE:
        mov  edx,DWORD PTR [esi+0x14]
        mov  eax,DWORD PTR [edx+0x20]
        push  eax
        call _malloc
        mov  DWORD PTR [esi+0x1c0],eax
        mov  eax,DWORD PTR [esi+0x14]
        mov  eax,DWORD PTR [eax+0x1c]
        add  esp,0x4
        push  eax
        push  0x400
        push  0xe1
        push  eax
        push  ebp
        mov  al,0xaa
        call FUN_0044b0d0
        mov  ecx,DWORD PTR [esi+0x14]
        mov  eax,DWORD PTR [ecx+0x1c]
        push  eax
        push  0x80
        push  0x7a
        push  eax
        push  ebp
        mov  al,0x3d
        call FUN_0044b0d0
        mov  eax,DWORD PTR [esi+0x14]
        mov  edx,DWORD PTR [eax+0x20]
        mov  ecx,DWORD PTR [esi+0x1c0]
        push  edx
        mov  edx,DWORD PTR [eax+0x1c]
        push  ecx
        push  edx
        push  ebp
        call FUN_00435dc0
        mov  eax,DWORD PTR [esi+0x1c0]
        mov  DWORD PTR [esi+0x18],eax
        add  eax,0x64
        xor  edi,edi
        push  ebx
        jmp loc_0042A330
        nop
    loc_0042A330:
        mov  ecx,DWORD PTR [esi+0x18]
        mov  ecx,DWORD PTR [ecx+0x4c]
        cmp  ecx,0x8
        jl loc_0042A340
        mov  ecx,0x6
    loc_0042A340:
        cmp  edi,ecx
        jge loc_0042A390
        movsx ecx,WORD PTR [eax]
        lea  edx,[ecx+ecx*8]
        mov  DWORD PTR [esi+edx*4+0xb0],eax
        movsx ecx,WORD PTR [eax]
        lea  ecx,[ecx+ecx*8]
        lea  edx,[eax+0x1c4]
        mov  DWORD PTR [esi+ecx*4+0xa0],edx
        movsx ecx,WORD PTR [eax]
        lea  edx,[ecx+ecx*8]
        mov  ebx,DWORD PTR [esi+edx*4+0xa0]
        lea  ecx,[esi+edx*4]
        mov  edx,DWORD PTR [eax+0x4]
        lea  edx,[edx+edx*2]
        lea  edx,[ebx+edx*2]
        mov  DWORD PTR [ecx+0xa8],edx
        mov  ecx,DWORD PTR [eax+0x8]
        lea  eax,[eax+ecx*1+0x1c4]
        inc  edi
        jmp loc_0042A330
    loc_0042A390:
        test  BYTE PTR ds:0x474ca0,0x20
        pop  ebx
        jne loc_0042A3A7
        test  ebp,ebp
        je loc_0042A3A7
        push  ebp
        call _free
        add  esp,0x4
    loc_0042A3A7:
        xor  eax,eax
    loc_0042A3A9:
        mov  ecx,DWORD PTR [esp+0x10c]
        pop  edi
        pop  ebp
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x108
        ret  0x4
    }
}

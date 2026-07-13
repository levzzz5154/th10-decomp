// 0043E3A0: FUN_0043e3a0
// Original size: 192 bytes, actual code: 67 instructions
extern "C" void FUN_0044d850(void);

extern "C" __declspec(naked) void FUN_0043e3a0(void) {
    __asm {
        sub  esp,0x20
        push  ebx
        mov  ebx,DWORD PTR ds:0x46623c
        push  ebp
        mov  ebp,DWORD PTR ds:0x46620c
        push  esi
        mov  DWORD PTR [esp+0xc],0x0
        mov  esi,0x1
        nop
    loc_0043E3C0:
        push  0xbf
        push  0xffffffff
        push  0x0
        push  0x49779c
        push  esi
        call  ebp
        mov  ecx,DWORD PTR ds:0x497798
        test  ecx,ecx
        jne loc_0043E3DF
        mov  DWORD PTR [esp+0xc],esi
    loc_0043E3DF:
        sub  eax,0x0
        je loc_0043E41F
        dec  eax
        jne loc_0043E446
        push  esi
        push  0x0
        push  0x0
        push  0x0
        lea  eax,[esp+0x20]
        push  eax
        call  ebx
        test  eax,eax
        je loc_0043E446
        nop
    loc_0043E400:
        cmp  DWORD PTR [esp+0x14],0x12
        jne loc_0043E40B
        mov  DWORD PTR [esp+0xc],esi
    loc_0043E40B:
        push  esi
        push  0x0
        push  0x0
        push  0x0
        lea  ecx,[esp+0x20]
        push  ecx
        call  ebx
        test  eax,eax
        jne loc_0043E400
        jmp loc_0043E446
    loc_0043E41F:
        test  ecx,ecx
        je loc_0043E446
        mov  eax,DWORD PTR [ecx+0x30]
        test  eax,eax
        je loc_0043E446
        mov  DWORD PTR [ecx+0x74],esi
        mov  edx,DWORD PTR ds:0x497798
        push  esi
        push  edx
        call FUN_0044d850
        mov  eax,ds:0x497798
        mov  DWORD PTR [eax+0x74],0x0
    loc_0043E446:
        mov  eax,DWORD PTR [esp+0xc]
        test  eax,eax
        je loc_0043E3C0
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0x20
        ret  0x4
    }
}

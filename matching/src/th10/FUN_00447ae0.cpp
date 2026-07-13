// 00447AE0: FUN_00447ae0
// Original size: 208 bytes, actual code: 62 instructions
extern "C" void FUN_004479d0(void);
extern "C" void _vsprintf(void);
extern "C" void __security_check_cookie(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00447ae0(void) {
    __asm {
        sub  esp,0x88
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        mov  DWORD PTR [esp+0x88],eax
        mov  al,BYTE PTR [esi+0x3a0]
        test  al,al
        push  ebp
        push  edi
        mov  ebp,0x11
        jbe loc_00447B09
        movzx ebp,al
    loc_00447B09:
        mov  ecx,DWORD PTR [esp+0xa0]
        lea  eax,[esp+0xa4]
        push  eax
        push  ecx
        lea  edx,[esp+0x18]
        push  edx
        call _vsprintf
        lea  eax,[esp+0x1c]
        add  esp,0xc
        lea  edx,[eax+0x1]
        nop
    loc_00447B30:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00447B30
        mov  ecx,DWORD PTR [esi+0x360]
        mov  edi,DWORD PTR [esi+0x394]
        shr  ecx,1
        and  ecx,0x1
        push  ecx
        sub  eax,edx
        mov  edx,DWORD PTR [esp+0xa0]
        lea  ecx,[ebp-0x1]
        imul  ecx,eax
        shr  ecx,1
        test  ecx,ecx
        mov  DWORD PTR [esp+0x10],ecx
        push  edx
        fild  DWORD PTR [esp+0x14]
        jge loc_00447B6D
        fadd  DWORD PTR ds:0x470b98
    loc_00447B6D:
        fsubr DWORD PTR [edi+0x34]
        call FUN_00463b2c
        mov  edx,DWORD PTR [edi+0x4]
        push  eax
        push  edx
        lea  ebx,[esp+0x20]
        mov  eax,ebp
        call FUN_004479d0
        mov  eax,DWORD PTR [esi+0x35c]
        mov  ecx,DWORD PTR [esp+0x90]
        pop  edi
        pop  ebp
        or   eax,0x1
        pop  ebx
        xor  ecx,esp
        mov  DWORD PTR [esi+0x35c],eax
        call __security_check_cookie
        add  esp,0x88
        ret
    }
}

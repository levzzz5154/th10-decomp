// 0044D440: FUN_0044d440
// Original size: 160 bytes, actual code: 62 instructions
extern "C" void FUN_0044d110(void);
extern "C" void FUN_0044d300(void);
extern "C" void FUN_0044d370(void);
extern "C" void FUN_0044d4e0(void);
extern "C" void FUN_0044d600(void);

extern "C" __declspec(naked) void FUN_0044d440(void) {
    __asm {
        push  ecx
        push  ebp
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [edi+0x4]
        xor  ebp,ebp
        cmp  eax,ebp
        jne loc_0044D459
        pop  edi
        mov  eax,0x800401f0
        pop  ebp
        pop  ecx
        ret  0x8
    loc_0044D459:
        push  esi
        call FUN_0044d370
        mov  esi,eax
        cmp  esi,ebp
        jne loc_0044D471
        pop  esi
        pop  edi
        mov  eax,0x80004005
        pop  ebp
        pop  ecx
        ret  0x8
    loc_0044D471:
        push  ebx
        lea  ebx,[esp+0x10]
        call FUN_0044d300
        cmp  eax,ebp
        pop  ebx
        jl loc_0044D4CA
        cmp  DWORD PTR [esp+0xc],ebp
        je loc_0044D498
        push  ebp
        push  esi
        mov  eax,edi
        call FUN_0044d110
        cmp  eax,ebp
        jl loc_0044D4CA
        call FUN_0044d600
    loc_0044D498:
        push  ebp
        mov  eax,edi
        mov  DWORD PTR [edi+0x1c],ebp
        mov  DWORD PTR [edi+0x14],ebp
        mov  DWORD PTR [edi+0x18],ebp
        call FUN_0044d4e0
        mov  eax,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x14]
        push  eax
        push  ecx
        push  ebp
        mov  DWORD PTR [edi+0x30],0x1
        mov  DWORD PTR [edi+0x20],ecx
        mov  DWORD PTR [edi+0x24],eax
        mov  DWORD PTR [edi+0x2c],ebp
        mov  edx,DWORD PTR [esi]
        push  esi
        call  DWORD PTR [edx+0x30]
    loc_0044D4CA:
        pop  esi
        pop  edi
        pop  ebp
        pop  ecx
        ret  0x8
    }
}

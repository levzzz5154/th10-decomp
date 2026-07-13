// 00405750: FUN_00405750
// Original size: 272 bytes, actual code: 75 instructions
extern "C" void FUN_00404ed0(void);
extern "C" void FUN_00405ac0(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_004492f0(void);

extern "C" __declspec(naked) void FUN_00405750(void) {
    __asm {
        mov  eax,DWORD PTR [edi+0x28]
        sub  esp,0xc
        push  esi
        xor  esi,esi
        cmp  eax,esi
        je loc_00405825
        dec  eax
        push  ebx
        push  ebp
        jne loc_0040581B
        mov  eax,DWORD PTR [edi+0x2c]
        mov  ebp,DWORD PTR ds:0x491c10
        push  eax
        mov  edx,ebp
        call FUN_004491c0
        mov  ebx,eax
        cmp  ebx,esi
        jne loc_00405793
        pop  ebp
        mov  DWORD PTR [edi+0x2c],esi
        pop  ebx
        mov  DWORD PTR [edi+0x28],esi
        mov  eax,0x1
        pop  esi
        add  esp,0xc
        ret
    loc_00405793:
        mov  eax,ds:0x4776f4
        test  BYTE PTR [eax+0x378c],0x1
        je loc_004057C1
        mov  eax,DWORD PTR [eax+0x3788]
        cmp  eax,0x5d
        jl loc_004057B1
        cmp  eax,0x60
        jle loc_004057B6
    loc_004057B1:
        cmp  eax,0x6d
        jne loc_004057C1
    loc_004057B6:
        fld  DWORD PTR [edi+0x34]
        fsub  DWORD PTR ds:0x470b0c
        jmp loc_004057DB
    loc_004057C1:
        mov  eax,ds:0x474c68
        fld  DWORD PTR [edi+0x34]
        cmp  eax,esi
        jne loc_004057D5
        fsub  DWORD PTR ds:0x470afc
        jmp loc_004057DB
    loc_004057D5:
        fsub  DWORD PTR ds:0x470d34
    loc_004057DB:
        mov  edx,DWORD PTR [edi+0x2c]
        fstp  DWORD PTR [edi+0x34]
        fld  DWORD PTR [edi+0x30]
        mov  ecx,DWORD PTR [edi+0x38]
        fadd  DWORD PTR ds:0x470b4c
        push  edx
        lea  esi,[esp+0x10]
        mov  edx,ebp
        fstp  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x18],ecx
        fld  DWORD PTR [edi+0x34]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esp+0x14]
        call FUN_004492f0
        mov  eax,DWORD PTR [ebx+0x40]
        mov  esi,edi
        mov  DWORD PTR [edi+0x3c],eax
        call FUN_00405ac0
    loc_0040581B:
        lea  esi,[edi+0x14]
        call FUN_00404ed0
        pop  ebp
        pop  ebx
    loc_00405825:
        mov  eax,0x1
        pop  esi
        add  esp,0xc
        ret
    }
}

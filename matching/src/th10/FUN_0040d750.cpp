// 0040D750: FUN_0040d750
// Original size: 224 bytes, actual code: 56 instructions
extern "C" void FUN_0040dc80(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0040d750(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [edi+0x58]
        test  esi,esi
        je loc_0040D7A2
        push  ebx
        nop
    loc_0040D760:
        mov  eax,DWORD PTR [esi]
        test  DWORD PTR [eax+0x2480],0x20000
        mov  ebx,DWORD PTR [esi+0x4]
        jne loc_0040D78E
        add  eax,0x103c
        push  eax
        call FUN_0040dc80
        test  eax,eax
        jne loc_0040D78E
        mov  esi,DWORD PTR [esi]
        and  DWORD PTR [esi+0x2480],0xfffffbff
        jmp loc_0040D79B
    loc_0040D78E:
        mov  ecx,DWORD PTR [esi]
        test  ecx,ecx
        je loc_0040D79B
        mov  eax,DWORD PTR [ecx]
        push  0x1
        call  DWORD PTR [eax+0x14]
    loc_0040D79B:
        test  ebx,ebx
        mov  esi,ebx
        jne loc_0040D760
        pop  ebx
    loc_0040D7A2:
        mov  edx,DWORD PTR [edi+0x44]
        mov  ecx,DWORD PTR [edi+0x4c]
        mov  DWORD PTR [edi+0x40],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        pop  esi
        fnstsw ax
        test  ah,0x41
        jne loc_0040D7E0
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0040D7E0
        fld  DWORD PTR [edi+0x48]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [edi+0x44],edx
        mov  eax,0x1
        fstp  DWORD PTR [edi+0x48]
        ret
    loc_0040D7E0:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [edi+0x48]
        fst  DWORD PTR [edi+0x48]
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x44],eax
        mov  eax,0x1
        ret
    }
}

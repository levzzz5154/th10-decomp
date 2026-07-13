// 0042B6F0: FUN_0042b6f0
// Original size: 144 bytes, actual code: 47 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0042b6f0(void) {
    __asm {
        push  esi
        mov  esi,eax
        push  edi
        add  esi,0x3e8
        mov  edi,0x2d3
        nop
    loc_0042B700:
        mov  al,BYTE PTR [esi+0x14]
        test  al,al
        je loc_0042B768
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR ds:0x470b0c
        fsubr DWORD PTR [esi-0x14]
        fstp  DWORD PTR [esi-0x14]
        mov  edx,DWORD PTR [esi-0x4]
        mov  ecx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [esi-0x8],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0042B750
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0042B750
        fld  DWORD PTR [esi]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi-0x4],edx
        fstp  DWORD PTR [esi]
        jmp loc_0042B75E
    loc_0042B750:
        fld  DWORD PTR [esi]
        fadd  DWORD PTR [ecx]
        fst  DWORD PTR [esi]
        call FUN_00463b2c
        mov  DWORD PTR [esi-0x4],eax
    loc_0042B75E:
        cmp  DWORD PTR [esi-0x4],0x3c
        jle loc_0042B768
        mov  BYTE PTR [esi+0x14],0x0
    loc_0042B768:
        add  esi,0x40
        dec  edi
        jne loc_0042B700
        pop  edi
        mov  eax,0x1
        pop  esi
        ret
    }
}

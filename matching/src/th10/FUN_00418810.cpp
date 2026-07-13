// 00418810: FUN_00418810
// Original size: 144 bytes, actual code: 42 instructions

extern "C" __declspec(naked) void FUN_00418810(void) {
    __asm {
        mov  dl,BYTE PTR ds:0x497d8c
        mov  ecx,0x1
        test  cl,dl
        jne loc_00418825
        or   DWORD PTR ds:0x497d8c,ecx
    loc_00418825:
        fld  DWORD PTR [eax]
        fadd  DWORD PTR ds:0x470b4c
        fstp  DWORD PTR ds:0x497d80
        fld  DWORD PTR [eax+0x4]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR ds:0x497d84
        mov  eax,DWORD PTR [eax+0x8]
        mov  ds:0x497d88,eax
        mov  eax,0x497d80
        ret
        mov  BYTE PTR ds:0x497c38,0x0
        mov  ecx,eax
        nop
    loc_00418860:
        mov  dl,BYTE PTR [eax]
        inc  eax
        test  dl,dl
        jne loc_00418860
        push  esi
        push  edi
        mov  edi,0x497c38
        sub  eax,ecx
        mov  esi,ecx
        dec  edi
    loc_00418873:
        mov  cl,BYTE PTR [edi+0x1]
        inc  edi
        test  cl,cl
        jne loc_00418873
        mov  ecx,eax
        shr  ecx,0x2
        rep movsd
        mov  ecx,eax
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        pop  edi
        mov  eax,0x497c38
        pop  esi
        ret
    }
}

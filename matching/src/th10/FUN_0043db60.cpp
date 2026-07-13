// 0043DB60: FUN_0043db60
// Original size: 304 bytes, actual code: 80 instructions
extern "C" void FUN_0043cc40(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0043db60(void) {
    __asm {
        or   eax,0xffffffff
        mov  DWORD PTR [ebx+0x620],eax
        mov  DWORD PTR [ebx+0x624],eax
        mov  DWORD PTR [ebx+0x628],eax
        mov  DWORD PTR [ebx+0x62c],eax
        mov  DWORD PTR [ebx+0x630],eax
        mov  DWORD PTR [ebx+0x634],eax
        mov  DWORD PTR [ebx+0x638],eax
        mov  DWORD PTR [ebx+0x63c],eax
        mov  DWORD PTR [ebx+0x640],eax
        mov  DWORD PTR [ebx+0x644],eax
        push  esi
        mov  DWORD PTR [ebx+0x648],eax
        mov  esi,0x492590
        mov  DWORD PTR [ebx+0x64c],eax
        call FUN_0043cc40
        mov  eax,DWORD PTR [ebx+0x610]
        test  eax,eax
        jne loc_0043DBC5
        or   eax,0xffffffff
        pop  esi
        ret
    loc_0043DBC5:
        cmp  DWORD PTR [ebx],0x0
        je loc_0043DC83
        push  edi
        lea  edi,[ebx+0x208]
        xor  esi,esi
        jmp loc_0043DBE0
        nop
    loc_0043DBE0:
        mov  edx,DWORD PTR [esi+0x4749c8]
        mov  edx,DWORD PTR [ebx+edx*4+0x8]
        mov  eax,DWORD PTR [ebx]
        mov  ecx,DWORD PTR [eax]
        push  edi
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x14]
        mov  eax,DWORD PTR [edi]
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x34]
        movsx ecx,WORD PTR [esi+0x4749cc]
        mov  eax,DWORD PTR [edi]
        mov  edx,DWORD PTR [eax]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x3c]
        add  esi,0x8
        add  edi,0x4
        cmp  esi,0x178
        jb loc_0043DBE0
        movsx edx,BYTE PTR ds:0x491d68
        mov  DWORD PTR [ebx+0x52c4],edx
        movsx eax,BYTE PTR ds:0x491d69
        test  eax,eax
        mov  DWORD PTR [ebx+0x52c8],eax
        pop  edi
        je loc_0043DC79
        fild  DWORD PTR [ebx+0x52c4]
        fmul  DWORD PTR ds:0x470b00
        fsubr DWORD PTR ds:0x470afc
        fld  st(0)
        fmulp st(1),st
        fld  st(0)
        fmul  st,st(1)
        fsubr DWORD PTR ds:0x470afc
        fmul  DWORD PTR ds:0x470b80
        call FUN_00463b2c
        fstp  st(0)
        mov  ecx,0xffffec78
        sub  ecx,eax
        mov  DWORD PTR [ebx+0x52cc],ecx
        xor  eax,eax
        pop  esi
        ret
    loc_0043DC79:
        mov  DWORD PTR [ebx+0x52cc],0xffffd8f0
    loc_0043DC83:
        xor  eax,eax
        pop  esi
        ret
    }
}

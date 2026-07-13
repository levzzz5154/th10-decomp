// 0044D4E0: FUN_0044d4e0
// Original size: 112 bytes, actual code: 34 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0044d4e0(void) {
    __asm {
        mov  ecx,DWORD PTR ds:0x497854
        test  ecx,ecx
        je loc_0044D537
        fild  DWORD PTR ds:0x497854
        mov  ecx,DWORD PTR [esp+0x4]
        mov  eax,DWORD PTR [eax+0x4]
        add  ecx,0x1388
        fmul  DWORD PTR ds:0x470b00
        mov  DWORD PTR [esp+0x4],ecx
        push  esi
        mov  esi,DWORD PTR [eax]
        fsubr DWORD PTR ds:0x470afc
        push  edi
        mov  edi,DWORD PTR [esi]
        fld  st(0)
        fmul  st,st(1)
        fsubr DWORD PTR ds:0x470afc
        fimul DWORD PTR [esp+0xc]
        call FUN_00463b2c
        fstp  st(0)
        sub  eax,0x1388
        push  eax
        push  esi
        call  DWORD PTR [edi+0x3c]
        pop  edi
        pop  esi
        ret  0x4
    loc_0044D537:
        mov  edx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [eax]
        push  0xffffd8f0
        push  eax
        call  DWORD PTR [ecx+0x3c]
        ret  0x4
    }
}

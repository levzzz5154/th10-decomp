// 004135D0: FUN_004135d0
// Original size: 240 bytes, actual code: 48 instructions
extern "C" void FUN_00401690(void);
extern "C" void FUN_004134b0(void);

extern "C" __declspec(naked) void FUN_004135d0(void) {
    __asm {
        sub  esp,0xc
        push  esi
        mov  esi,edi
        call FUN_004134b0
        cmp  DWORD PTR ds:0x491fb8,0xe
        je loc_0041366A
        mov  esi,DWORD PTR ds:0x4776e0
        fld  DWORD PTR [edi+0x34]
        test  esi,esi
        je loc_00413668
        fcom  DWORD PTR ds:0x470c30
        fnstsw ax
        test  ah,0x5
        jp loc_00413609
        mov  eax,0xff5050ff
        jmp loc_00413620
    loc_00413609:
        fcom  DWORD PTR ds:0x470c64
        fnstsw ax
        test  ah,0x5
        jp loc_0041361D
        mov  eax,0xffa0a0ff
        jmp loc_00413620
    loc_0041361D:
        or   eax,0xffffffff
    loc_00413620:
        push  ebx
        sub  esp,0x8
        fstp  QWORD PTR [esp]
        push  0x46d198
        lea  ebx,[esp+0x14]
        mov  DWORD PTR [esi+0x8974],eax
        mov  DWORD PTR [esp+0x14],0x44138000
        mov  DWORD PTR [esp+0x18],0x43eb0000
        mov  DWORD PTR [esp+0x1c],0x0
        call FUN_00401690
        mov  eax,ds:0x4776e0
        add  esp,0xc
        mov  DWORD PTR [eax+0x8974],0xffffffff
        pop  ebx
        jmp loc_0041366A
    loc_00413668:
        fstp  st(0)
    loc_0041366A:
        movzx ecx,BYTE PTR ds:0x491d66
        mov  eax,DWORD PTR [edi+0x20]
        inc  ecx
        add  eax,ecx
        mov  DWORD PTR [edi+0x20],eax
        mov  eax,0x1
        pop  esi
        add  esp,0xc
        ret
    }
}

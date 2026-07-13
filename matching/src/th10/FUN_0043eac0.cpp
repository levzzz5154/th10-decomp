// 0043EAC0: FUN_0043eac0
// Original size: 432 bytes, actual code: 108 instructions
extern "C" void FUN_0043EC76(void);
extern "C" void FUN_0043EC7A(void);
extern "C" void FUN_0043EC8E(void);
extern "C" void FUN_0043EC92(void);
extern "C" void FUN_0043EC96(void);
extern "C" void FUN_0043EC9A(void);
extern "C" void FUN_0043EC9E(void);
extern "C" void FUN_0043ECA2(void);
extern "C" void FUN_0043ECA6(void);
extern "C" void FUN_0043ECAA(void);
extern "C" void FUN_0044bb20(void);
extern "C" void FUN_0044bb90(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0043eac0(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        call FUN_00463b2c
        add  eax,0xffffd8f0
        cmp  eax,0x15
        ja loc_0043EC07
        jmp  DWORD PTR [eax*4+0x43ec10]
        fild  DWORD PTR [esi+0x30c]
        ret  0x4
        fild  DWORD PTR [esi+0x310]
        ret  0x4
        fild  DWORD PTR [esi+0x314]
        ret  0x4
        fild  DWORD PTR [esi+0x318]
        ret  0x4
        fld  DWORD PTR [esi+0x31c]
        ret  0x4
        fld  DWORD PTR [esi+0x320]
        ret  0x4
        fld  DWORD PTR [esi+0x324]
        ret  0x4
        fld  DWORD PTR [esi+0x328]
        ret  0x4
        fild  DWORD PTR [esi+0x32c]
        ret  0x4
        fild  DWORD PTR [esi+0x330]
        ret  0x4
        test  DWORD PTR [esi+0x35c],0x40000000
        je loc_0043EB51
        mov  ecx,0x4918a8
        call FUN_0044bb20
        ret  0x4
    loc_0043EB51:
        mov  ecx,0x4918b0
        call FUN_0044bb20
        ret  0x4
        test  DWORD PTR [esi+0x35c],0x40000000
        je loc_0043EB77
        mov  ecx,0x4918a8
        call FUN_0044bb90
        ret  0x4
    loc_0043EB77:
        mov  ecx,0x4918b0
        call FUN_0044bb90
        ret  0x4
        test  DWORD PTR [esi+0x35c],0x40000000
        je loc_0043EBA3
        mov  ecx,0x4918a8
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470b18
        ret  0x4
    loc_0043EBA3:
        mov  ecx,0x4918b0
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470b18
        ret  0x4
        fld  DWORD PTR [esi+0x334]
        ret  0x4
        fld  DWORD PTR [esi+0x338]
        ret  0x4
        fld  DWORD PTR [esi+0x33c]
        ret  0x4
        fld  DWORD PTR ds:0x491d7c
        ret  0x4
        fld  DWORD PTR ds:0x491d80
        ret  0x4
        fld  DWORD PTR ds:0x491d84
        ret  0x4
        fld  DWORD PTR ds:0x491da0
        ret  0x4
        fld  DWORD PTR ds:0x491da4
        ret  0x4
        fld  DWORD PTR ds:0x491da8
        ret  0x4
    loc_0043EC07:
        fld  DWORD PTR [esp+0x4]
        ret  0x4
        mov  edi,edi
        fsubp st(2),st
        inc  ebx
        add  bh,ah
        jmp FUN_00000043:0xeaf00043
        stc
        jmp FUN_00000043:0xeb020043
        or   ebp,ebx
        inc  ebx
        add  BYTE PTR [ebx+ebp*8],dl
        inc  ebx
        add  BYTE PTR ds:0x260043eb,bl
        jmp FUN_0043EC76
        add  BYTE PTR [edi],ch
        jmp FUN_0043EC7A
        add  BYTE PTR [ebx+ebp*8-0x14c7ffbd],al
        inc  ebx
        add  BYTE PTR [esi-0x15],bl
        inc  ebx
        add  BYTE PTR [esi-0x40ffbc15],dh
        jmp FUN_0043EC8E
        add  al,cl
        jmp FUN_0043EC92
        add  cl,dl
        jmp FUN_0043EC96
        add  dl,bl
        jmp FUN_0043EC9A
        add  bl,ah
        jmp FUN_0043EC9E
        add  ah,ch
        jmp FUN_0043ECA2
        add  ch,dh
        jmp FUN_0043ECA6
        add  dh,bh
        jmp FUN_0043ECAA
        add  ah,cl
    }
}

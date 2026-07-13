// 004445C0: FUN_004445c0
// Original size: 416 bytes, actual code: 114 instructions
extern "C" void FUN_00442670(void);
extern "C" void FUN_00444240(void);
extern "C" void D3DXVec3Transform(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004445c0(void) {
    __asm {
        sub  esp,0x4c
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x58]
        push  esi
        mov  esi,DWORD PTR [esp+0x60]
        push  edi
        push  ebp
        mov  eax,esi
        call FUN_00444240
        fld  DWORD PTR ds:0x491e78
        fsub  DWORD PTR ds:0x491e7c
        mov  eax,DWORD PTR [esi+0x35c]
        test  ah,ah
        fstp  DWORD PTR [esp+0x14]
        jns loc_004445F9
        mov  ebx,DWORD PTR [esi+0x300]
        jmp loc_004445FF
    loc_004445F9:
        mov  ebx,DWORD PTR [esi+0x2fc]
    loc_004445FF:
        mov  DWORD PTR [esp+0x10],ebx
        mov  esi,0x4978d3
        lea  edi,[esp+0x1c]
        add  ebp,0x3ada78
    loc_00444612:
        mov  eax,DWORD PTR [esp+0x60]
        add  eax,0x3ad0f0
        push  eax
        push  ebp
        push  edi
        call D3DXVec3Transform
        fld  DWORD PTR [edi]
        fsub  DWORD PTR ds:0x491d7c
        fld  DWORD PTR [edi+0x4]
        fsub  DWORD PTR ds:0x491d80
        fld  DWORD PTR [edi+0x8]
        fsub  DWORD PTR ds:0x491d84
        fld  st(0)
        fmul  st,st(1)
        fld  st(2)
        fmul  st,st(3)
        faddp st(1),st
        fld  st(3)
        fmul  st,st(4)
        faddp st(1),st
        fsqrt
        fstp  st(3)
        fstp  st(0)
        fstp  st(0)
        fld  DWORD PTR ds:0x491e78
        fcomp st(1)
        fnstsw ax
        test  ah,0x5
        jp loc_004446F7
        fsubr DWORD PTR ds:0x491e78
        fdiv  DWORD PTR [esp+0x14]
        fcom  DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x1
        jne loc_0044468F
        mov  eax,ds:0x491e90
        mov  cl,BYTE PTR [esp+0x13]
        mov  DWORD PTR [esi-0x3],eax
        mov  BYTE PTR [esi],cl
        jmp loc_004446FA
    loc_0044468F:
        movzx edx,bl
        mov  DWORD PTR [esp+0x18],edx
        fild  DWORD PTR [esp+0x18]
        fsub  DWORD PTR ds:0x491e80
        fmul  st,st(1)
        call FUN_00463b2c
        movzx edx,bh
        mov  DWORD PTR [esp+0x18],edx
        mov  cl,bl
        sub  cl,al
        fild  DWORD PTR [esp+0x18]
        mov  BYTE PTR [esi-0x3],cl
        fsub  DWORD PTR ds:0x491e84
        fmul  st,st(1)
        call FUN_00463b2c
        movzx edx,BYTE PTR [esp+0x12]
        mov  DWORD PTR [esp+0x18],edx
        mov  cl,bh
        sub  cl,al
        fild  DWORD PTR [esp+0x18]
        mov  BYTE PTR [esi-0x2],cl
        fsub  DWORD PTR ds:0x491e88
        fmul  st,st(1)
        call FUN_00463b2c
        mov  cx,WORD PTR [esp+0x12]
        mov  dl,cl
        sub  dl,al
        mov  BYTE PTR [esi-0x1],dl
        mov  BYTE PTR [esi],ch
        jmp loc_004446FA
    loc_004446F7:
        mov  DWORD PTR [esi-0x3],ebx
    loc_004446FA:
        add  esi,0x1c
        fstp  st(0)
        add  ebp,0x14
        add  edi,0x10
        cmp  esi,0x497943
        jl loc_00444612
        mov  eax,DWORD PTR [esp+0x64]
        mov  ecx,DWORD PTR [esp+0x60]
        push  0x2
        call FUN_00442670
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR ds:0x497920,0x3f800000
        mov  DWORD PTR ds:0x497904,0x3f800000
        mov  DWORD PTR ds:0x4978e8,0x3f800000
        mov  DWORD PTR ds:0x4978cc,0x3f800000
        pop  ebx
        add  esp,0x4c
        ret  0x8
    }
}

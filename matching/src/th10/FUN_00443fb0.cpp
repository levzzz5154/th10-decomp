// 00443FB0: FUN_00443fb0
// Original size: 656 bytes, actual code: 166 instructions
extern "C" void FUN_00442670(void);
extern "C" void FUN_00443b60(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00443fb0(void) {
    __asm {
        sub  esp,0x20
        mov  eax,edi
        call FUN_00443b60
        test  eax,eax
        je loc_00443FC5
        or   eax,0xffffffff
        add  esp,0x20
        ret
    loc_00443FC5:
        mov  eax,DWORD PTR [edi+0x35c]
        fld  DWORD PTR ds:0x491e78
        test  ah,ah
        fsub  DWORD PTR ds:0x491e7c
        jns loc_00443FE6
        mov  eax,DWORD PTR [edi+0x300]
        mov  DWORD PTR [esp],eax
        jmp loc_00443FEF
    loc_00443FE6:
        mov  ecx,DWORD PTR [edi+0x2fc]
        mov  DWORD PTR [esp],ecx
    loc_00443FEF:
        fld  DWORD PTR [edi+0x340]
        push  ebx
        fadd  DWORD PTR [edi+0x334]
        fld  DWORD PTR [edi+0x344]
        fadd  DWORD PTR [edi+0x338]
        fld  DWORD PTR [edi+0x348]
        fadd  DWORD PTR [edi+0x33c]
        fstp  DWORD PTR [esp+0x20]
        fxch  st(1)
        fadd  DWORD PTR [edi+0x34c]
        fstp  DWORD PTR [esp+0xc]
        fadd  DWORD PTR [edi+0x350]
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR [edi+0x354]
        fld  DWORD PTR [esp+0xc]
        fsub  DWORD PTR ds:0x491d7c
        fstp  DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [esp+0x18]
        fxch  st(1)
        mov  DWORD PTR [esp+0xc],edx
        fsub  DWORD PTR ds:0x491d80
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x10],eax
        fsub  DWORD PTR ds:0x491d84
        mov  eax,DWORD PTR [esi+0x73245c]
        test  eax,eax
        fstp  DWORD PTR [esp+0x20]
        mov  ecx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x14],ecx
        fld  DWORD PTR [esp+0x14]
        fmul  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x10]
        fmul  DWORD PTR [esp+0x10]
        faddp st(1),st
        fld  DWORD PTR [esp+0xc]
        fmul  DWORD PTR [esp+0xc]
        faddp st(1),st
        fsqrt
        je loc_00444128
        movzx eax,BYTE PTR [esi+0x73245a]
        movzx edx,BYTE PTR [esp+0x6]
        imul  eax,edx
        shr  eax,0x7
        cmp  eax,0x100
        jb loc_004440BA
        mov  eax,0xff
    loc_004440BA:
        movzx ecx,BYTE PTR [esp+0x5]
        mov  BYTE PTR [esp+0x6],al
        movzx eax,BYTE PTR [esi+0x732459]
        imul  eax,ecx
        shr  eax,0x7
        cmp  eax,0x100
        jb loc_004440DC
        mov  eax,0xff
    loc_004440DC:
        movzx edx,BYTE PTR [esp+0x4]
        mov  BYTE PTR [esp+0x5],al
        movzx eax,BYTE PTR [esi+0x732458]
        imul  eax,edx
        shr  eax,0x7
        cmp  eax,0x100
        jb loc_004440FE
        mov  eax,0xff
    loc_004440FE:
        movzx ecx,BYTE PTR [esp+0x7]
        mov  bl,al
        movzx eax,BYTE PTR [esi+0x73245b]
        imul  eax,ecx
        shr  eax,0x7
        cmp  eax,0x100
        mov  BYTE PTR [esp+0x4],bl
        jb loc_00444122
        mov  eax,0xff
    loc_00444122:
        mov  BYTE PTR [esp+0x7],al
        jmp loc_0044412C
    loc_00444128:
        mov  bl,BYTE PTR [esp+0x4]
    loc_0044412C:
        fld  DWORD PTR ds:0x491e78
        fcomp st(1)
        fnstsw ax
        test  ah,0x5
        jp loc_00444207
        fld  DWORD PTR ds:0x491e78
        fsub  st,st(1)
        fdivrp st(2),st
        fstp  st(0)
        fcom  DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x1
        jne loc_00444164
        fstp  st(0)
        mov  eax,0xffffffff
        pop  ebx
        add  esp,0x20
        ret
    loc_00444164:
        fld  DWORD PTR ds:0x491e80
        call FUN_00463b2c
        movzx edx,bl
        sub  edx,eax
        mov  DWORD PTR [esp+0x8],edx
        fild  DWORD PTR [esp+0x8]
        fmul  st,st(1)
        call FUN_00463b2c
        fld  DWORD PTR ds:0x491e84
        sub  bl,al
        mov  BYTE PTR ds:0x4978d0,bl
        call FUN_00463b2c
        mov  bl,BYTE PTR [esp+0x5]
        movzx ecx,bl
        sub  ecx,eax
        mov  DWORD PTR [esp+0x8],ecx
        fild  DWORD PTR [esp+0x8]
        fmul  st,st(1)
        call FUN_00463b2c
        fld  DWORD PTR ds:0x491e88
        sub  bl,al
        mov  BYTE PTR ds:0x4978d1,bl
        call FUN_00463b2c
        mov  bl,BYTE PTR [esp+0x6]
        movzx edx,bl
        sub  edx,eax
        mov  DWORD PTR [esp+0x8],edx
        fild  DWORD PTR [esp+0x8]
        fmul  st,st(1)
        call FUN_00463b2c
        fld  DWORD PTR ds:0x470afc
        sub  bl,al
        fsub  st,st(1)
        movzx eax,BYTE PTR [esp+0x7]
        mov  DWORD PTR [esp+0x8],eax
        mov  BYTE PTR ds:0x4978d2,bl
        fimul DWORD PTR [esp+0x8]
        call FUN_00463b2c
        mov  ds:0x4978d3,al
        mov  eax,ds:0x4978d0
        jmp loc_00444212
    loc_00444207:
        mov  eax,DWORD PTR [esp+0x4]
        fstp  st(0)
        mov  ds:0x4978d0,eax
    loc_00444212:
        mov  ds:0x4978ec,eax
        fstp  st(0)
        mov  ds:0x497908,eax
        mov  ds:0x497924,eax
        push  0x2
        mov  eax,edi
        mov  ecx,esi
        call FUN_00442670
        pop  ebx
        add  esp,0x20
        ret
    }
}

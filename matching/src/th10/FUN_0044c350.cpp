// 0044C350: FUN_0044c350
// Original size: 640 bytes, actual code: 197 instructions
extern "C" void FUN_00452ff0(void);

extern "C" __declspec(naked) void FUN_0044c350(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        dec  eax
        cmp  eax,0xf
        fdiv  DWORD PTR [esp+0x8]
        ja loc_0044C54A
        jmp  DWORD PTR [eax*4+0x44c550]
        fld  st(0)
        fmulp st(1),st
        ret  0x8
        fsubr DWORD PTR ds:0x470afc
        fld  st(0)
        fmulp st(1),st
        fsubr DWORD PTR ds:0x470afc
        ret  0x8
        fld  st(0)
        fmul  st,st(1)
        fmulp st(1),st
        ret  0x8
        fsubr DWORD PTR ds:0x470afc
        fld  st(0)
        fld  st(0)
        fmul  st,st(1)
        fmulp st(2),st
        fxch  st(1)
        fsubr DWORD PTR ds:0x470afc
        fstp  st(1)
        ret  0x8
        fld  st(0)
        fmul  st,st(1)
        fmul  st,st(1)
        fmulp st(1),st
        ret  0x8
        fsubr DWORD PTR ds:0x470afc
        fld  st(0)
        fld  st(0)
        fmul  st,st(1)
        fmul  st,st(2)
        fmulp st(2),st
        fxch  st(1)
        fsubr DWORD PTR ds:0x470afc
        fstp  st(1)
        ret  0x8
        fadd  st(0),st
        fcom  DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x5
        jp loc_0044C3EB
        fld  st(0)
        fmulp st(1),st
        fmul  DWORD PTR ds:0x470b0c
        ret  0x8
    loc_0044C3EB:
        fsubr DWORD PTR ds:0x470b08
        fld  st(0)
        fmulp st(1),st
        fsubr DWORD PTR ds:0x470b08
        fmul  DWORD PTR ds:0x470b0c
        ret  0x8
        fadd  st(0),st
        fcom  DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x5
        jp loc_0044C42C
        fsubr DWORD PTR ds:0x470afc
        fld  st(0)
        fmulp st(1),st
        fmul  DWORD PTR ds:0x470b0c
        fsubr DWORD PTR ds:0x470b0c
        ret  0x8
    loc_0044C42C:
        fsub  DWORD PTR ds:0x470afc
        fld  st(0)
        fmulp st(1),st
        fmul  DWORD PTR ds:0x470b0c
        fadd  DWORD PTR ds:0x470b0c
        ret  0x8
        fadd  st(0),st
        fcom  DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x5
        jp loc_0044C463
        fld  st(0)
        fmul  st,st(1)
        fmulp st(1),st
        fmul  DWORD PTR ds:0x470b0c
        ret  0x8
    loc_0044C463:
        fsubr DWORD PTR ds:0x470b08
        fld  st(0)
        fld  st(0)
        fmul  st,st(1)
        jmp loc_0044C4CD
        fadd  st(0),st
        fcom  DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x5
        jp loc_0044C48E
        fsubr DWORD PTR ds:0x470afc
        fld  st(0)
        fld  st(0)
        fmul  st,st(1)
        jmp loc_0044C4FF
    loc_0044C48E:
        fsub  DWORD PTR ds:0x470afc
        fld  st(0)
        fld  st(0)
        fmul  st,st(1)
        jmp loc_0044C522
        fadd  st(0),st
        fcom  DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x5
        jp loc_0044C4BF
        fld  st(0)
        fmul  st,st(1)
        fmul  st,st(1)
        fmulp st(1),st
        fmul  DWORD PTR ds:0x470b0c
        ret  0x8
    loc_0044C4BF:
        fsubr DWORD PTR ds:0x470b08
        fld  st(0)
        fld  st(0)
        fmul  st,st(1)
        fmul  st,st(2)
    loc_0044C4CD:
        fmulp st(2),st
        fxch  st(1)
        fsubr DWORD PTR ds:0x470b08
        fmul  DWORD PTR ds:0x470b0c
        fstp  st(1)
        ret  0x8
        fadd  st(0),st
        fcom  DWORD PTR ds:0x470afc
        fnstsw ax
        test  ah,0x5
        jp loc_0044C514
        fsubr DWORD PTR ds:0x470afc
        fld  st(0)
        fld  st(0)
        fmul  st,st(1)
        fmul  st,st(2)
    loc_0044C4FF:
        fmulp st(2),st
        fxch  st(1)
        fmul  DWORD PTR ds:0x470b0c
        fsubr DWORD PTR ds:0x470b0c
        fstp  st(1)
        ret  0x8
    loc_0044C514:
        fsub  DWORD PTR ds:0x470afc
        fld  st(0)
        fld  st(0)
        fmul  st,st(1)
        fmul  st,st(2)
    loc_0044C522:
        fmulp st(2),st
        fxch  st(1)
        fmul  DWORD PTR ds:0x470b0c
        fadd  DWORD PTR ds:0x470b0c
        fstp  st(1)
        ret  0x8
        fstp  st(0)
        fld  DWORD PTR ds:0x470b04
        ret  0x8
        fstp  st(0)
        fld  DWORD PTR ds:0x470afc
    loc_0044C54A:
        ret  0x8
        nop
        imul  eax,ebx,0xc3830044
        inc  esp
        add  BYTE PTR [edi+0x700044c3],ah
        ret
        inc  esp
        add  BYTE PTR [ebx+eax*8-0x3c4dffbc],cl
        inc  esp
        add  BYTE PTR [edx-0x3b],cl
        inc  esp
        add  BYTE PTR [edx-0x3b],cl
        inc  esp
        add  bh,cl
        ret
        inc  esp
        add  BYTE PTR [ebp-0x3c],al
        inc  esp
        add  BYTE PTR [edi+0x40044c4],bl
        les  eax,FWORD PTR [eax+eax*1+0x71]
        les  eax,FWORD PTR [eax+eax*1-0x1e]
        les  eax,FWORD PTR [eax+eax*1+0x37]
        lds  eax,FWORD PTR [eax+eax*1+0x42]
        lds  eax,FWORD PTR [eax+eax*1-0x27]
        push  es
        sub  esp,0x8
        fmul  DWORD PTR ds:0x470b44
        fstp  QWORD PTR [esp]
        call FUN_00452ff0
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [esi]
        fld  DWORD PTR [esi+0x4]
        fmul  DWORD PTR ds:0x470b44
        fstp  QWORD PTR [esp]
        call FUN_00452ff0
        fmul  DWORD PTR ds:0x470b00
        add  esp,0x8
        fstp  DWORD PTR [esi+0x4]
        ret
    }
}

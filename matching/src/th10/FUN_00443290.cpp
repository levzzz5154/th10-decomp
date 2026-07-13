// 00443290: FUN_00443290
// Original size: 2256 bytes, actual code: 104 instructions
extern "C" void FUN_00442670(void);

extern "C" __declspec(naked) void FUN_00443290(void) {
    __asm {
        sub  esp,0x8
        fld  DWORD PTR [eax+0x4c]
        mov  ecx,DWORD PTR [eax+0x35c]
        fmul  DWORD PTR [eax+0x3c]
        shr  ecx,0x12
        fld  DWORD PTR [eax+0x50]
        and  ecx,0x3
        sub  ecx,0x0
        fmul  DWORD PTR [eax+0x40]
        fst  DWORD PTR [esp]
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x4]
        je loc_00443335
        dec  ecx
        je loc_00443307
        dec  ecx
        jne loc_00443377
        fld  DWORD PTR [eax+0x334]
        fadd  DWORD PTR [eax+0x340]
        fadd  DWORD PTR [eax+0x34c]
        fsubrp st(1),st
        fst  DWORD PTR ds:0x4978f8
        fstp  DWORD PTR ds:0x4978c0
        fld  DWORD PTR [eax+0x334]
        fadd  DWORD PTR [eax+0x340]
    loc_004432F3:
        fadd  DWORD PTR [eax+0x34c]
        fst  DWORD PTR ds:0x497914
        fstp  DWORD PTR ds:0x4978dc
        jmp loc_00443379
    loc_00443307:
        fld  DWORD PTR [eax+0x334]
        fadd  DWORD PTR [eax+0x340]
        fadd  DWORD PTR [eax+0x34c]
        fst  DWORD PTR ds:0x4978f8
        fstp  DWORD PTR ds:0x4978c0
        fld  DWORD PTR [eax+0x334]
        fadd  DWORD PTR [eax+0x340]
        faddp st(1),st
        jmp loc_004432F3
    loc_00443335:
        fld  DWORD PTR [eax+0x34c]
        fadd  DWORD PTR [eax+0x340]
        fadd  DWORD PTR [eax+0x334]
        fld  st(1)
        fmul  DWORD PTR ds:0x470b0c
        fsubp st(1),st
        fstp  DWORD PTR ds:0x4978f8
        mov  ecx,DWORD PTR ds:0x4978f8
        mov  DWORD PTR ds:0x4978c0,ecx
        fadd  DWORD PTR ds:0x4978f8
        fst  DWORD PTR ds:0x497914
        fstp  DWORD PTR ds:0x4978dc
        jmp loc_00443379
    loc_00443377:
        fstp  st(0)
    loc_00443379:
        mov  ecx,DWORD PTR [eax+0x35c]
        shr  ecx,0x14
        and  ecx,0x3
        sub  ecx,0x0
        je loc_004433FE
        dec  ecx
        je loc_004433C9
        dec  ecx
        jne loc_0044343B
        fld  DWORD PTR [eax+0x350]
        fadd  DWORD PTR [eax+0x338]
        fadd  DWORD PTR [eax+0x344]
        fsub  DWORD PTR [esp]
        fst  DWORD PTR ds:0x4978e0
        fstp  DWORD PTR ds:0x4978c4
        fld  DWORD PTR [eax+0x350]
        fadd  DWORD PTR [eax+0x338]
        fadd  DWORD PTR [eax+0x344]
        jmp loc_0044342F
    loc_004433C9:
        fld  DWORD PTR [eax+0x350]
        fadd  DWORD PTR [eax+0x338]
        fadd  DWORD PTR [eax+0x344]
        fst  DWORD PTR ds:0x4978e0
        fstp  DWORD PTR ds:0x4978c4
        fld  DWORD PTR [eax+0x350]
        fadd  DWORD PTR [eax+0x338]
        fadd  DWORD PTR [esp]
        fadd  DWORD PTR [eax+0x344]
        jmp loc_0044342F
    loc_004433FE:
        fld  DWORD PTR [eax+0x350]
        fadd  DWORD PTR [eax+0x344]
        fadd  DWORD PTR [eax+0x338]
        fsub  DWORD PTR [esp+0x4]
        fstp  DWORD PTR ds:0x4978e0
        mov  edx,DWORD PTR ds:0x4978e0
        fld  DWORD PTR ds:0x4978e0
        mov  DWORD PTR ds:0x4978c4,edx
        fadd  DWORD PTR [esp]
    loc_0044342F:
        fst  DWORD PTR ds:0x497918
        fstp  DWORD PTR ds:0x4978fc
    loc_0044343B:
        fld  DWORD PTR [eax+0x350]
        mov  ecx,DWORD PTR [esp+0xc]
        fadd  DWORD PTR [eax+0x348]
        push  0x0
        fadd  DWORD PTR [eax+0x33c]
        fst  DWORD PTR ds:0x49791c
        fst  DWORD PTR ds:0x497900
        fst  DWORD PTR ds:0x4978e4
        fstp  DWORD PTR ds:0x4978c8
        call FUN_00442670
        add  esp,0x8
        ret  0x4
    }
}

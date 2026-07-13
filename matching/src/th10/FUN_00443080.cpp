// 00443080: FUN_00443080
// Original size: 528 bytes, actual code: 111 instructions
extern "C" void FUN_00442670(void);
extern "C" void FUN_00452ff0(void);

extern "C" __declspec(naked) void FUN_00443080(void) {
    __asm {
        sub  esp,0xc
        fld  DWORD PTR [esi+0x4c]
        mov  eax,DWORD PTR [esi+0x35c]
        fmul  DWORD PTR [esi+0x3c]
        shr  eax,0x12
        and  eax,0x3
        sub  eax,0x0
        fstp  DWORD PTR [esp]
        fld  DWORD PTR [esi+0x50]
        fmul  DWORD PTR [esi+0x40]
        fst  DWORD PTR [esp+0x4]
        fmul  DWORD PTR ds:0x470b0c
        fstp  DWORD PTR [esp+0x8]
        je loc_00443125
        dec  eax
        je loc_004430F0
        dec  eax
        jne loc_00443177
        fld  DWORD PTR [esi+0x334]
        fadd  DWORD PTR [esi+0x340]
        fadd  DWORD PTR [esi+0x34c]
        fsub  DWORD PTR [esp]
        fst  DWORD PTR ds:0x4978f8
        fstp  DWORD PTR ds:0x4978c0
        fld  DWORD PTR [esi+0x334]
        fadd  DWORD PTR [esi+0x340]
        fadd  DWORD PTR [esi+0x34c]
        jmp loc_0044316B
    loc_004430F0:
        fld  DWORD PTR [esi+0x334]
        fadd  DWORD PTR [esi+0x340]
        fadd  DWORD PTR [esi+0x34c]
        fst  DWORD PTR ds:0x4978f8
        fstp  DWORD PTR ds:0x4978c0
        fld  DWORD PTR [esi+0x334]
        fadd  DWORD PTR [esi+0x340]
        fadd  DWORD PTR [esp]
        fadd  DWORD PTR [esi+0x34c]
        jmp loc_0044316B
    loc_00443125:
        fld  DWORD PTR [esi+0x34c]
        sub  esp,0x8
        fadd  DWORD PTR [esi+0x340]
        fadd  DWORD PTR [esi+0x334]
        fld  DWORD PTR [esp+0x8]
        fmul  DWORD PTR ds:0x470b0c
        fsubp st(1),st
        fstp  QWORD PTR [esp]
        call FUN_00452ff0
        fstp  DWORD PTR ds:0x4978f8
        mov  eax,ds:0x4978f8
        fld  DWORD PTR ds:0x4978f8
        fadd  DWORD PTR [esp+0x8]
        add  esp,0x8
        mov  ds:0x4978c0,eax
    loc_0044316B:
        fst  DWORD PTR ds:0x497914
        fstp  DWORD PTR ds:0x4978dc
    loc_00443177:
        mov  eax,DWORD PTR [esi+0x35c]
        shr  eax,0x14
        and  eax,0x3
        sub  eax,0x0
        je loc_004431FA
        dec  eax
        je loc_004431C8
        dec  eax
        jne loc_00443246
        fld  DWORD PTR [esi+0x344]
        fadd  DWORD PTR [esi+0x350]
        fadd  DWORD PTR [esi+0x338]
        fsub  DWORD PTR [esp+0x4]
        fst  DWORD PTR ds:0x4978e0
        fstp  DWORD PTR ds:0x4978c4
        fld  DWORD PTR [esi+0x344]
        fadd  DWORD PTR [esi+0x350]
        fadd  DWORD PTR [esi+0x338]
        jmp loc_0044323A
    loc_004431C8:
        fld  DWORD PTR [esi+0x344]
        fadd  DWORD PTR [esi+0x350]
        fadd  DWORD PTR [esi+0x338]
        fst  DWORD PTR ds:0x4978e0
        fstp  DWORD PTR ds:0x4978c4
        fld  DWORD PTR [esi+0x344]
        fadd  DWORD PTR [esi+0x350]
        fadd  DWORD PTR [esi+0x338]
        jmp loc_00443236
    loc_004431FA:
        fld  DWORD PTR [esi+0x350]
        sub  esp,0x8
        fadd  DWORD PTR [esi+0x344]
        fadd  DWORD PTR [esi+0x338]
        fsub  DWORD PTR [esp+0x10]
        fstp  QWORD PTR [esp]
        call FUN_00452ff0
        fstp  DWORD PTR ds:0x4978e0
        mov  ecx,DWORD PTR ds:0x4978e0
        fld  DWORD PTR ds:0x4978e0
        add  esp,0x8
        mov  DWORD PTR ds:0x4978c4,ecx
    loc_00443236:
        fadd  DWORD PTR [esp+0x4]
    loc_0044323A:
        fst  DWORD PTR ds:0x497918
        fstp  DWORD PTR ds:0x4978fc
    loc_00443246:
        fld  DWORD PTR [esi+0x354]
        mov  ecx,DWORD PTR [esp+0x10]
        fadd  DWORD PTR [esi+0x348]
        push  0x1
        mov  eax,esi
        fadd  DWORD PTR [esi+0x33c]
        fst  DWORD PTR ds:0x49791c
        fst  DWORD PTR ds:0x497900
        fst  DWORD PTR ds:0x4978e4
        fstp  DWORD PTR ds:0x4978c8
        call FUN_00442670
        add  esp,0xc
        ret  0x4
    }
}

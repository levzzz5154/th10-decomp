// 0041D2C0: FUN_0041d2c0
// Original size: 272 bytes, actual code: 72 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0041d2c0(void) {
    __asm {
        sub  esp,0xc
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0x90]
        cmp  eax,DWORD PTR [esi+0xb4]
        jl loc_0041D2E0
        and  DWORD PTR [esi+0x404],0xffffffef
        jmp loc_0041D361
    loc_0041D2E0:
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [esi+0xa0]
        fadd  DWORD PTR [esi+0x48]
        fstp  DWORD PTR [esi+0x48]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [esi+0xa8]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [esi+0xac]
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [esi+0xb0]
        fstp  DWORD PTR [esp+0xc]
        fxch  st(1)
        fadd  DWORD PTR [esi+0x30]
        fstp  DWORD PTR [esi+0x30]
        fadd  DWORD PTR [esi+0x34]
        fstp  DWORD PTR [esi+0x34]
        fld  DWORD PTR [esp+0xc]
        fadd  DWORD PTR [esi+0x38]
        fstp  DWORD PTR [esi+0x38]
        fld  DWORD PTR [esi+0x30]
        fabs
        fcomp DWORD PTR ds:0x470c58
        fnstsw ax
        test  ah,0x41
        je loc_0041D356
        fld  DWORD PTR [esi+0x34]
        fabs
        fcomp DWORD PTR ds:0x470c58
        fnstsw ax
        test  ah,0x41
        jne loc_0041D361
    loc_0041D356:
        fld  DWORD PTR [esi+0x34]
        fld  DWORD PTR [esi+0x30]
        fpatan
        fstp  DWORD PTR [esi+0x3c]
    loc_0041D361:
        mov  edx,DWORD PTR [esi+0x90]
        mov  ecx,DWORD PTR [esi+0x98]
        mov  DWORD PTR [esi+0x8c],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0041D3AF
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0041D3AF
        fld  DWORD PTR [esi+0x94]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x90],edx
        fstp  DWORD PTR [esi+0x94]
        pop  esi
        add  esp,0xc
        ret
    loc_0041D3AF:
        fld  DWORD PTR [esi+0x94]
        fadd  DWORD PTR [ecx]
        fst  DWORD PTR [esi+0x94]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x90],eax
        pop  esi
        add  esp,0xc
        ret
    }
}

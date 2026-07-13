// 0044BF40: FUN_0044bf40
// Original size: 448 bytes, actual code: 28 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0044bf40(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR [esi+0xc]
        mov  DWORD PTR [esi],eax
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0044BF7E
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0044BF7E
        fld  DWORD PTR [esp+0x4]
        fadd  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esi+0x8]
        fld  DWORD PTR [esi+0x8]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x4],eax
        ret  0x4
    loc_0044BF7E:
        fld  DWORD PTR [esp+0x4]
        fmul  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esi+0x8]
        fld  DWORD PTR [esi+0x8]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x4],eax
        ret  0x4
    }
}

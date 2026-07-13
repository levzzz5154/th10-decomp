// 004223F0: FUN_004223f0
// Original size: 208 bytes, actual code: 69 instructions
extern "C" void FUN_00422ab0(void);
extern "C" void FUN_00422c80(void);
extern "C" void FUN_004236f0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004223f0(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x4]
        cmp  eax,0xd
        ja loc_00422450
        movzx eax,BYTE PTR [eax+0x4224b0]
        jmp  DWORD PTR [eax*4+0x4224a4]
        test  BYTE PTR ds:0x474ca0,0x20
        jne loc_00422450
        test  BYTE PTR ds:0x474e36,0x8
        jne loc_00422421
        test  BYTE PTR ds:0x491ff4,0x10
        je loc_00422450
    loc_00422421:
        mov  ecx,DWORD PTR ds:0x477810
        mov  eax,DWORD PTR [ecx+0x8]
        test  eax,eax
        je loc_00422450
        test  BYTE PTR [eax+0x4],0x2
        je loc_00422450
        cmp  DWORD PTR [ecx+0x14],0x1e
        jl loc_00422450
        push  esi
        call FUN_00422ab0
        jmp loc_00422450
        push  esi
        call FUN_00422c80
        jmp loc_00422450
        push  esi
        call FUN_004236f0
    loc_00422450:
        mov  edx,DWORD PTR [esi+0x14]
        mov  ecx,DWORD PTR [esi+0x1c]
        mov  DWORD PTR [esi+0x10],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0042248D
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0042248D
        fld  DWORD PTR [esi+0x18]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [esi+0x14],edx
        mov  eax,0x1
        fstp  DWORD PTR [esi+0x18]
        ret
    loc_0042248D:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [esi+0x18]
        fst  DWORD PTR [esi+0x18]
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x14],eax
        mov  eax,0x1
        ret
    }
}

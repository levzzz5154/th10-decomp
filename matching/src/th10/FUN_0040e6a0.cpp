// 0040E6A0: FUN_0040e6a0
// Original size: 208 bytes, actual code: 64 instructions
extern "C" void FUN_00448db0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0040e6a0(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [ebp+0x58]
        test  eax,eax
        je loc_0040E707
        push  ebx
        push  esi
        push  edi
        nop
    loc_0040E6B0:
        mov  esi,DWORD PTR [eax]
        mov  ebx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [esi+0x2480]
        test  al,0x50
        jne loc_0040E6C4
        test  ah,0xc0
        je loc_0040E6C8
    loc_0040E6C4:
        test  al,al
        jns loc_0040E6FE
    loc_0040E6C8:
        mov  eax,DWORD PTR [esi+0x2448]
        test  eax,eax
        jl loc_0040E6F4
        mov  ecx,DWORD PTR [esi+0x244c]
        mov  edx,DWORD PTR ds:0x477704
        push  eax
        lea  eax,[esp+0x18]
        push  eax
        mov  eax,DWORD PTR [edx+ecx*4+0x30]
        lea  edi,[esi+0x1068]
        push  eax
        call FUN_00448db0
    loc_0040E6F4:
        or   DWORD PTR [esi+0x2480],0x20000
    loc_0040E6FE:
        test  ebx,ebx
        mov  eax,ebx
        jne loc_0040E6B0
        pop  edi
        pop  esi
        pop  ebx
    loc_0040E707:
        mov  edx,DWORD PTR [ebp+0x44]
        mov  ecx,DWORD PTR [ebp+0x4c]
        mov  DWORD PTR [ebp+0x40],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0040E742
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0040E742
        fld  DWORD PTR [ebp+0x48]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [ebp+0x44],edx
        fstp  DWORD PTR [ebp+0x48]
        pop  ebp
        ret  0x4
    loc_0040E742:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebp+0x48]
        fst  DWORD PTR [ebp+0x48]
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x44],eax
        pop  ebp
        ret  0x4
    }
}

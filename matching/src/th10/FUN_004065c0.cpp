// 004065C0: FUN_004065c0
// Original size: 288 bytes, actual code: 83 instructions
extern "C" void FUN_00406240(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004065c0(void) {
    __asm {
        push  ecx
        push  ebx
        push  ebp
        xor  ebp,ebp
        lea  ebx,[esi+0x60]
        push  edi
        mov  DWORD PTR [esi+0x5c],ebp
        mov  DWORD PTR [esi+0x28],ebp
        mov  DWORD PTR [esi+0x24],ebp
        mov  DWORD PTR [esi+0x20],ebp
        mov  DWORD PTR [esi+0x1c],ebp
        mov  DWORD PTR [esi+0x18],ebp
        mov  DWORD PTR [esi+0x14],ebp
        mov  DWORD PTR [esi+0x40],ebp
        mov  DWORD PTR [esi+0x3c],ebp
        mov  DWORD PTR [esi+0x38],ebp
        mov  DWORD PTR [esi+0x34],ebp
        mov  DWORD PTR [esi+0x30],ebp
        mov  DWORD PTR [esi+0x2c],ebp
        lea  edi,[ebx+0x400]
        mov  DWORD PTR [esp+0xc],0x7d0
        mov  edi,edi
    loc_00406600:
        cmp  WORD PTR [edi+0x46],bp
        je loc_00406694
        mov  eax,ds:0x477810
        cmp  eax,ebp
        je loc_0040661F
        mov  eax,DWORD PTR [eax+0x58]
        test  al,0x2
        je loc_0040661F
        test  ah,0x4
        jne loc_00406629
    loc_0040661F:
        push  ebx
        call FUN_00406240
        test  eax,eax
        jne loc_00406694
    loc_00406629:
        mov  eax,DWORD PTR [edi+0x60]
        cmp  DWORD PTR [esi+eax*4+0x14],ebp
        je loc_0040663E
        mov  eax,DWORD PTR [esi+eax*4+0x2c]
        mov  DWORD PTR [eax+0x44c],ebx
        jmp loc_00406642
    loc_0040663E:
        mov  DWORD PTR [esi+eax*4+0x14],ebx
    loc_00406642:
        mov  ecx,DWORD PTR [edi+0x60]
        mov  DWORD PTR [esi+ecx*4+0x2c],ebx
        mov  DWORD PTR [edi+0x4c],ebp
        inc  DWORD PTR [esi+0x5c]
        mov  edx,DWORD PTR [edi-0x4]
        mov  ecx,DWORD PTR [edi+0x4]
        mov  DWORD PTR [edi-0x8],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00406686
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00406686
        fld  DWORD PTR [edi]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [edi-0x4],edx
        fstp  DWORD PTR [edi]
        jmp loc_00406694
    loc_00406686:
        fld  DWORD PTR [edi]
        fadd  DWORD PTR [ecx]
        fst  DWORD PTR [edi]
        call FUN_00463b2c
        mov  DWORD PTR [edi-0x4],eax
    loc_00406694:
        mov  eax,DWORD PTR [esp+0xc]
        add  ebx,0x7f0
        add  edi,0x7f0
        dec  eax
        mov  DWORD PTR [esp+0xc],eax
        jne loc_00406600
        pop  edi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        pop  ecx
        ret
    }
}

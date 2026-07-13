// 0042B780: FUN_0042b780
// Original size: 576 bytes, actual code: 145 instructions
extern "C" void FUN_00442f50(void);
extern "C" void FUN_00443080(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0042b780(void) {
    __asm {
        mov  al,ds:0x491d78
        sub  esp,0x10
        test  al,0x4
        push  ebx
        push  ebp
        push  esi
        lea  ebp,[edi+0x3c4]
        jne loc_0042B7C5
        mov  eax,ds:0x492378
        test  eax,eax
        je loc_0042B7C5
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        push  0x0
        push  0x1c
        mov  DWORD PTR ds:0x492378,0x0
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0xe4]
    loc_0042B7C5:
        mov  esi,DWORD PTR ds:0x477834
        mov  DWORD PTR [esp+0x18],0x2d3
    loc_0042B7D3:
        mov  al,BYTE PTR [ebp+0x38]
        test  al,al
        je loc_0042B97E
        cmp  DWORD PTR [ebp+0x20],0x8
        jge loc_0042B7F3
        fld  DWORD PTR ds:0x470bd0
        fdiv  DWORD PTR [ebp+0x24]
        fstp  DWORD PTR [esp+0xc]
        jmp loc_0042B7FB
    loc_0042B7F3:
        mov  DWORD PTR [esp+0xc],0x41000000
    loc_0042B7FB:
        movzx edx,BYTE PTR [ebp+0x39]
        mov  DWORD PTR [esp+0x14],edx
        fild  DWORD PTR [esp+0x14]
        fmul  DWORD PTR [esp+0xc]
        fmul  DWORD PTR ds:0x470b0c
        fsubr DWORD PTR [ebp+0xc]
        fadd  DWORD PTR ds:0x470b4c
        fstp  DWORD PTR [edi+0x358]
        fld  DWORD PTR [ebp+0x10]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [edi+0x35c]
        mov  eax,DWORD PTR [ebp+0x18]
        mov  DWORD PTR [edi+0x314],eax
        fld  DWORD PTR [esi+0x3c0]
        fsub  DWORD PTR [ebp+0xc]
        fld  DWORD PTR [esi+0x3c4]
        fsub  DWORD PTR [ebp+0x10]
        fld  st(0)
        fmul  st,st(1)
        fld  st(2)
        fmul  st,st(3)
        faddp st(1),st
        call FUN_00463b2c
        fstp  st(0)
        cmp  eax,0x1000
        fstp  st(0)
        jle loc_0042B86B
        mov  ebx,0xd0
        jmp loc_0042B895
    loc_0042B86B:
        cmp  eax,0x400
        jle loc_0042B890
        lea  ecx,[eax-0x400]
        shl  ecx,0x7
        mov  eax,0x2aaaaaab
        imul  ecx
        sar  edx,0x9
        mov  ecx,edx
        shr  ecx,0x1f
        lea  ebx,[edx+ecx*1+0x50]
        jmp loc_0042B895
    loc_0042B890:
        mov  ebx,0x50
    loc_0042B895:
        movzx eax,BYTE PTR [ebp+0x39]
        test  eax,eax
        lea  edx,[eax+ebp*1-0x1]
        mov  DWORD PTR [esp+0x10],edx
        jle loc_0042B97E
        lea  esi,[edi+0x18]
        mov  DWORD PTR [esp+0x14],eax
        jmp loc_0042B8B6
    loc_0042B8B2:
        mov  edx,DWORD PTR [esp+0x10]
    loc_0042B8B6:
        mov  ecx,DWORD PTR [ebp+0x20]
        cmp  ecx,0x34
        jl loc_0042B907
        mov  al,BYTE PTR [edx]
        cmp  al,0xa
        je loc_0042B907
        cmp  ecx,0x38
        jge loc_0042B8E8
        movzx edx,al
        mov  eax,DWORD PTR [edi+0x10]
        mov  ecx,DWORD PTR [eax+0x118]
        add  edx,0xcf
        imul  edx,edx,0x44
        add  edx,ecx
        mov  DWORD PTR [edi+0x3ac],edx
        jmp loc_0042B923
    loc_0042B8E8:
        mov  edx,DWORD PTR [edi+0x10]
        movzx ecx,al
        mov  eax,DWORD PTR [edx+0x118]
        add  ecx,0xd9
        imul  ecx,ecx,0x44
        add  ecx,eax
        mov  DWORD PTR [edi+0x3ac],ecx
        jmp loc_0042B923
    loc_0042B907:
        movzx eax,BYTE PTR [edx]
        mov  ecx,DWORD PTR [edi+0x10]
        mov  edx,DWORD PTR [ecx+0x118]
        add  eax,0xc4
        imul  eax,eax,0x44
        add  eax,edx
        mov  DWORD PTR [edi+0x3ac],eax
    loc_0042B923:
        mov  edx,DWORD PTR [edi+0x3ac]
        mov  ecx,DWORD PTR ds:0x491c10
        mov  BYTE PTR [edi+0x317],bl
        mov  eax,DWORD PTR [edx+0x34]
        mov  DWORD PTR [esi+0x4c],eax
        mov  eax,DWORD PTR [esi+0x35c]
        or   eax,0x8
        push  ecx
        mov  DWORD PTR [esi+0x35c],eax
        call FUN_00443080
        fld  DWORD PTR [esp+0xc]
        mov  ecx,DWORD PTR [esp+0x10]
        fadd  DWORD PTR [edi+0x358]
        mov  eax,DWORD PTR [esp+0x14]
        dec  ecx
        dec  eax
        fstp  DWORD PTR [edi+0x358]
        mov  DWORD PTR [esp+0x10],ecx
        mov  DWORD PTR [esp+0x14],eax
        jne loc_0042B8B2
        mov  esi,DWORD PTR ds:0x477834
    loc_0042B97E:
        mov  eax,DWORD PTR [esp+0x18]
        add  ebp,0x40
        dec  eax
        mov  DWORD PTR [esp+0x18],eax
        jne loc_0042B7D3
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        add  esp,0x10
        ret
    }
}

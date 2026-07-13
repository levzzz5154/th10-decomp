// 004297D0: FUN_004297d0
// Original size: 912 bytes, actual code: 142 instructions
extern "C" void FUN_0040ac20(void);
extern "C" void FUN_0042a8a0(void);
extern "C" void FUN_0042aa50(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004297d0(void) {
    __asm {
        mov  eax,ds:0x477810
        xor  edx,edx
        cmp  eax,edx
        je loc_00429A1E
        cmp  DWORD PTR [edi+0x10],edx
        push  esi
        jne loc_004298F6
        mov  ax,ds:0x474e5c
        mov  ecx,DWORD PTR ds:0x474e30
        mov  ds:0x474e5e,ax
        mov  eax,ds:0x491d78
        and  ecx,0x1f7
        test  ah,0x2
        mov  WORD PTR ds:0x474e5c,cx
        je loc_00429849
        mov  al,cl
        test  al,0x1
        je loc_00429842
        mov  ax,ds:0x474e5a
        inc  ax
        cmp  ax,0x8
        mov  ds:0x474e5a,ax
        jb loc_00429849
        or   cx,0x4
        mov  WORD PTR ds:0x474e5c,cx
        mov  WORD PTR ds:0x474e5a,0x8
        jmp loc_00429849
    loc_00429842:
        mov  WORD PTR ds:0x474e5a,dx
    loc_00429849:
        mov  ecx,0x474e30
        call FUN_0040ac20
        mov  eax,DWORD PTR [edi+0x1c8]
        cdq
        mov  ecx,0x1e
        idiv  ecx
        test  edx,edx
        jne loc_004298A8
        mov  edx,DWORD PTR ds:0x477708
        fld  DWORD PTR [edx+0x34]
        fadd  DWORD PTR ds:0x470b0c
        fcom  DWORD PTR ds:0x470c34
        fnstsw ax
        test  ah,0x1
        jne loc_0042988A
        fstp  st(0)
        mov  ecx,0xff
        jmp loc_00429892
    loc_0042988A:
        call FUN_00463b2c
        movzx ecx,al
    loc_00429892:
        mov  eax,DWORD PTR [edi+0x9c]
        mov  eax,DWORD PTR [eax]
        mov  edx,DWORD PTR [eax+0x6274]
        mov  BYTE PTR [edx],cl
        inc  DWORD PTR [eax+0x6274]
    loc_004298A8:
        mov  eax,DWORD PTR [edi+0x9c]
        mov  eax,DWORD PTR [eax]
        xor  ecx,ecx
        mov  cx,WORD PTR ds:0x474e64
        xor  edx,edx
        mov  dx,WORD PTR ds:0x474e62
        push  ecx
        push  edx
        mov  edx,DWORD PTR ds:0x474e5c
        call FUN_0042a8a0
        test  eax,eax
        je loc_00429A17
        mov  esi,DWORD PTR [edi+0x1d0]
        push  edi
        call FUN_0042aa50
        mov  DWORD PTR [edi+0x9c],eax
        inc  DWORD PTR [edi+0x1c8]
        pop  esi
        mov  eax,0x1
        ret
    loc_004298F6:
        cmp  DWORD PTR [edi+0x1d0],edx
        jl loc_00429A02
        mov  ax,ds:0x474e5c
        mov  ds:0x474e5e,ax
        mov  eax,DWORD PTR [edi+0x1d0]
        lea  ecx,[eax+eax*8]
        mov  esi,DWORD PTR [edi+ecx*4+0xb0]
        lea  ecx,[edi+ecx*4]
        push  ebx
        mov  ebx,DWORD PTR [esi+0x4]
        lea  eax,[eax+eax*8+0x2d]
        mov  eax,DWORD PTR [edi+eax*4]
        cmp  eax,ebx
        pop  ebx
        jge loc_004299CB
        mov  ecx,DWORD PTR [ecx+0xa4]
        mov  dx,WORD PTR [ecx]
        mov  WORD PTR ds:0x474e5c,dx
        mov  eax,DWORD PTR [edi+0x1d0]
        lea  eax,[eax+eax*8]
        mov  ecx,DWORD PTR [edi+eax*4+0xa4]
        mov  dx,WORD PTR [ecx+0x2]
        mov  WORD PTR ds:0x474e62,dx
        mov  eax,DWORD PTR [edi+0x1d0]
        lea  eax,[eax+eax*8]
        mov  ecx,DWORD PTR [edi+eax*4+0xa4]
        mov  dx,WORD PTR [ecx+0x4]
        mov  WORD PTR ds:0x474e64,dx
        mov  eax,DWORD PTR [edi+0x1d0]
        lea  eax,[eax+eax*8]
        mov  ecx,DWORD PTR [edi+eax*4+0xac]
        mov  dl,BYTE PTR [ecx]
        lea  eax,[edi+eax*4]
        mov  BYTE PTR [edi+0x1c4],dl
        add  DWORD PTR [eax+0xa4],0x6
        mov  eax,DWORD PTR [edi+0x1c8]
        cdq
        mov  ecx,0x1e
        idiv  ecx
        test  edx,edx
        jne loc_004299E0
        mov  eax,DWORD PTR [edi+0x1d0]
        lea  edx,[eax+eax*8]
        mov  ecx,DWORD PTR [edi+edx*4+0xac]
        lea  eax,[edi+edx*4+0xac]
        inc  ecx
        mov  DWORD PTR [eax],ecx
        jmp loc_004299E0
    loc_004299CB:
        mov  WORD PTR ds:0x474e5c,dx
        mov  WORD PTR ds:0x474e62,dx
        mov  WORD PTR ds:0x474e64,dx
    loc_004299E0:
        mov  eax,DWORD PTR [edi+0x1d0]
        add  eax,0x5
        lea  eax,[eax+eax*8]
        mov  ecx,DWORD PTR [edi+eax*4]
        lea  eax,[edi+eax*4]
        inc  ecx
        mov  DWORD PTR [eax],ecx
        inc  DWORD PTR [edi+0x1c8]
        pop  esi
        mov  eax,0x1
        ret
    loc_00429A02:
        mov  WORD PTR ds:0x474e5c,dx
        mov  WORD PTR ds:0x474e62,dx
        mov  WORD PTR ds:0x474e64,dx
    loc_00429A17:
        inc  DWORD PTR [edi+0x1c8]
        pop  esi
    loc_00429A1E:
        mov  eax,0x1
        ret
    }
}

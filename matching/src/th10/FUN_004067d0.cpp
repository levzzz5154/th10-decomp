// 004067D0: FUN_004067d0
// Original size: 1472 bytes, actual code: 374 instructions
extern "C" void FUN_00404f30(void);
extern "C" void FUN_00406d90(void);
extern "C" void FUN_00406DCF(void);
extern "C" void FUN_00408750(void);
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_0044bb20(void);
extern "C" void FUN_0044bc10(void);

extern "C" __declspec(naked) void FUN_004067d0(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [esp+0x8]
        sub  esp,0x14
        push  ebp
        mov  ebp,DWORD PTR [eax+0x10]
        push  esi
        push  edi
        xor  edi,edi
        xor  esi,esi
        jmp loc_004067F0
        nop
        mov  edi,edi
    loc_004067F0:
        cmp  WORD PTR [ebp+0x446],di
        je loc_004068AC
        add  ebp,0x7f0
        mov  edx,0x5
        cmp  WORD PTR [ebp+0x446],dx
        jne loc_00406814
        lea  ebp,[eax+0x60]
    loc_00406814:
        cmp  WORD PTR [ebp+0x446],di
        je loc_0040689C
        add  ebp,0x7f0
        cmp  WORD PTR [ebp+0x446],dx
        jne loc_0040682F
        lea  ebp,[eax+0x60]
    loc_0040682F:
        cmp  WORD PTR [ebp+0x446],di
        je loc_0040689F
        add  ebp,0x7f0
        cmp  WORD PTR [ebp+0x446],dx
        jne loc_0040684A
        lea  ebp,[eax+0x60]
    loc_0040684A:
        cmp  WORD PTR [ebp+0x446],di
        je loc_004068A4
        add  ebp,0x7f0
        cmp  WORD PTR [ebp+0x446],dx
        jne loc_00406865
        lea  ebp,[eax+0x60]
    loc_00406865:
        cmp  WORD PTR [ebp+0x446],di
        je loc_004068A9
        add  ebp,0x7f0
        cmp  WORD PTR [ebp+0x446],dx
        jne loc_00406880
        lea  ebp,[eax+0x60]
    loc_00406880:
        add  esi,edx
        cmp  esi,0x7d0
        jl loc_004067F0
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        add  esp,0x14
        ret  0x10
    loc_0040689C:
        inc  esi
        jmp loc_004068AC
    loc_0040689F:
        add  esi,0x2
        jmp loc_004068AC
    loc_004068A4:
        add  esi,0x3
        jmp loc_004068AC
    loc_004068A9:
        add  esi,0x4
    loc_004068AC:
        cmp  esi,0x7d0
        jl loc_004068C2
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        add  esp,0x14
        ret  0x10
    loc_004068C2:
        mov  ax,WORD PTR [ebx+0x1f6]
        cmp  ax,0x1
        mov  DWORD PTR [esp+0xc],0x0
        jle loc_004068F8
        fld  DWORD PTR [ebx+0x18]
        movsx eax,ax
        fld  st(0)
        mov  DWORD PTR [esp+0x10],eax
        fsub  DWORD PTR [ebx+0x1c]
        fimul DWORD PTR [esp+0x2c]
        fidiv DWORD PTR [esp+0x10]
        fsubr st,st(1)
        fstp  DWORD PTR [esp+0x10]
        fstp  st(0)
        jmp loc_004068FF
    loc_004068F8:
        mov  edx,DWORD PTR [ebx+0x18]
        mov  DWORD PTR [esp+0x10],edx
    loc_004068FF:
        mov  si,WORD PTR [ebx+0x1f8]
        movzx eax,si
        cmp  eax,0x8
        ja loc_00406A7F
        jmp  DWORD PTR [eax*4+0x406d58]
        test  BYTE PTR [ebx+0x1f4],0x1
        je loc_00406934
        lea  eax,[ecx+0x1]
        cdq
        sub  eax,edx
        sar  eax,1
        mov  DWORD PTR [esp+0x28],eax
        fild  DWORD PTR [esp+0x28]
        jmp loc_00406949
    loc_00406934:
        mov  eax,ecx
        cdq
        sub  eax,edx
        sar  eax,1
        mov  DWORD PTR [esp+0x28],eax
        fild  DWORD PTR [esp+0x28]
        fadd  DWORD PTR ds:0x470b0c
    loc_00406949:
        test  cl,0x1
        fmul  DWORD PTR [ebx+0x14]
        je loc_00406957
        fmul  DWORD PTR ds:0x470b60
    loc_00406957:
        cmp  si,di
        jne loc_00406960
        fadd  DWORD PTR [esp+0x30]
    loc_00406960:
        fadd  DWORD PTR [ebx+0x10]
        fstp  DWORD PTR [esp+0xc]
        jmp loc_00406A7F
        mov  eax,DWORD PTR [esp+0x30]
        mov  DWORD PTR [esp+0xc],eax
        fild  DWORD PTR [esp+0x28]
        movsx ecx,WORD PTR [ebx+0x1f4]
        mov  DWORD PTR [esp+0x28],ecx
        fmul  DWORD PTR ds:0x470b14
        fidiv DWORD PTR [esp+0x28]
        fadd  DWORD PTR [esp+0xc]
        fild  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR [ebx+0x14]
        faddp st(1),st
        fadd  DWORD PTR [ebx+0x10]
        fstp  DWORD PTR [esp+0xc]
        jmp loc_00406A7F
        mov  edx,DWORD PTR [esp+0x30]
        mov  DWORD PTR [esp+0xc],edx
        movsx eax,WORD PTR [ebx+0x1f4]
        mov  DWORD PTR [esp+0x30],eax
        fild  DWORD PTR [esp+0x30]
        fld  DWORD PTR ds:0x470b18
        fdiv  st,st(1)
        fadd  DWORD PTR [esp+0xc]
        fild  DWORD PTR [esp+0x28]
        fmul  DWORD PTR ds:0x470b14
        fdiv  st,st(2)
        faddp st(1),st
        fild  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR [ebx+0x14]
        faddp st(1),st
        fadd  DWORD PTR [ebx+0x10]
        fstp  DWORD PTR [esp+0xc]
        fstp  st(0)
        jmp loc_00406A7F
        fld  DWORD PTR [ebx+0x10]
        mov  ecx,0x4918b0
        fsub  DWORD PTR [ebx+0x14]
        call FUN_0044bb20
        fmulp st(1),st
        fadd  DWORD PTR [ebx+0x14]
        fstp  DWORD PTR [esp+0xc]
        jmp loc_00406A7F
        fld  DWORD PTR [ebx+0x18]
        mov  ecx,0x4918b0
        fsub  DWORD PTR [ebx+0x1c]
        call FUN_0044bb20
        movsx ecx,WORD PTR [ebx+0x1f4]
        fmulp st(1),st
        fadd  DWORD PTR [ebx+0x1c]
        fstp  DWORD PTR [esp+0x10]
        fild  DWORD PTR [esp+0x28]
        mov  DWORD PTR [esp+0x28],ecx
        fmul  DWORD PTR ds:0x470b14
        fidiv DWORD PTR [esp+0x28]
        fild  DWORD PTR [esp+0x2c]
        fmul  DWORD PTR [ebx+0x14]
        faddp st(1),st
        fadd  DWORD PTR [ebx+0x10]
        fstp  DWORD PTR [esp+0xc]
        jmp loc_00406A7F
        fld  DWORD PTR [ebx+0x10]
        mov  ecx,0x4918b0
        fsub  DWORD PTR [ebx+0x14]
        call FUN_0044bb20
        mov  ecx,0x4918b0
        fmulp st(1),st
        fadd  DWORD PTR [ebx+0x14]
        fstp  DWORD PTR [esp+0xc]
        fld  DWORD PTR [ebx+0x18]
        fsub  DWORD PTR [ebx+0x1c]
        call FUN_0044bb20
        fmulp st(1),st
        fadd  DWORD PTR [ebx+0x1c]
        fstp  DWORD PTR [esp+0x10]
    loc_00406A7F:
        or   DWORD PTR [ebp+0x0],0x1
        mov  WORD PTR [ebp+0x446],0x1
        mov  eax,DWORD PTR [ebp+0x408]
        test  al,0x1
        mov  esi,0xfff0bdc1
        mov  edx,0x476f78
        jne loc_00406AC1
        or   eax,0x1
        mov  DWORD PTR [ebp+0x3fc],edi
        mov  DWORD PTR [ebp+0x3f8],esi
        mov  DWORD PTR [ebp+0x400],edi
        mov  DWORD PTR [ebp+0x404],edx
        mov  DWORD PTR [ebp+0x408],eax
    loc_00406AC1:
        or   ecx,0xffffffff
        mov  DWORD PTR [ebp+0x3fc],edi
        mov  DWORD PTR [ebp+0x400],edi
        mov  DWORD PTR [ebp+0x3f8],ecx
        mov  eax,DWORD PTR [ebp+0x41c]
        test  al,0x1
        jne loc_00406B01
        or   eax,0x1
        mov  DWORD PTR [ebp+0x410],edi
        mov  DWORD PTR [ebp+0x40c],esi
        mov  DWORD PTR [ebp+0x414],edi
        mov  DWORD PTR [ebp+0x418],edx
        mov  DWORD PTR [ebp+0x41c],eax
    loc_00406B01:
        mov  edx,DWORD PTR [esp+0x10]
        mov  esi,DWORD PTR [esp+0xc]
        push  edi
        mov  DWORD PTR [ebp+0x40c],ecx
        mov  DWORD PTR [ebp+0x410],edi
        mov  DWORD PTR [ebp+0x414],edi
        push  esi
        mov  DWORD PTR [ebp+0x3d8],edx
        call FUN_0044bc10
        fstp  DWORD PTR [ebp+0x3e4]
        lea  eax,[ebx+0x4]
        mov  edx,DWORD PTR [eax]
        lea  edi,[ebp+0x3b4]
        mov  ecx,edi
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  edx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ecx+0x8],eax
        push  edx
        lea  ecx,[ebp+0x3c0]
        push  esi
        mov  DWORD PTR [ebp+0x3bc],0x3dcccccd
        call FUN_00408750
        mov  eax,DWORD PTR [ebx+0x1fc]
        mov  DWORD PTR [ebp+0x43c],eax
        mov  cx,WORD PTR [ebx+0x2]
        mov  eax,DWORD PTR [ebp+0x0]
        mov  WORD PTR [ebp+0x7ec],cx
        mov  dx,WORD PTR [ebx]
        and  eax,0xfffffff3
        mov  WORD PTR [ebp+0x7ea],dx
        or   eax,0x2
        mov  DWORD PTR [ebp+0x0],eax
        mov  DWORD PTR [ebp+0x454],0x0
        movsx ecx,WORD PTR [ebx]
        movsx eax,WORD PTR [ebx+0x2]
        add  eax,DWORD PTR [ecx*4+0x474170]
        mov  edx,DWORD PTR [esp+0x24]
        mov  ecx,DWORD PTR [edx+0x3e0b50]
        lea  esi,[ebp+0x8]
        push  ecx
        call FUN_00404f30
        movsx edx,WORD PTR [ebx]
        mov  eax,DWORD PTR [edx*4+0x4742c0]
        cmp  eax,0x4
        ja loc_00406C17
        jmp  DWORD PTR [eax*4+0x406d7c]
        movsx eax,WORD PTR [ebx+0x2]
        lea  ecx,[eax+eax*1+0x11]
        mov  DWORD PTR [ebp+0x438],ecx
        jmp loc_00406C17
        movsx edx,WORD PTR [ebx+0x2]
        mov  eax,DWORD PTR [edx*4+0x47432c]
        mov  DWORD PTR [ebp+0x438],eax
        jmp loc_00406C17
        mov  DWORD PTR [ebp+0x438],0xffffffff
        jmp loc_00406C17
        mov  DWORD PTR [ebp+0x438],0x1d
        jmp loc_00406C17
        mov  DWORD PTR [ebp+0x438],0x13
    loc_00406C17:
        movsx ecx,WORD PTR [ebx]
        mov  edx,DWORD PTR [ecx*4+0x474250]
        mov  DWORD PTR [ebp+0x460],edx
        mov  eax,DWORD PTR [ebx+0x204]
        mov  DWORD PTR [ebp+0x458],eax
        mov  DWORD PTR [ebp+0x434],0xa
        movsx ecx,WORD PTR [ebx]
        fld  DWORD PTR [ecx*4+0x4741e0]
        fst  DWORD PTR [ebp+0x3f4]
        fstp  DWORD PTR [ebp+0x3f0]
        mov  eax,DWORD PTR [ebx+0x1fc]
        test  al,0x2
        je loc_00406CB5
        mov  WORD PTR [ebp+0x30c],0x7
    loc_00406C66:
        mov  WORD PTR [ebp+0x446],0x2
        fld  DWORD PTR [ebp+0x3c0]
        fmul  DWORD PTR ds:0x470c40
        fld  DWORD PTR [ebp+0x3c4]
        fmul  DWORD PTR ds:0x470c40
        fld  DWORD PTR [ebp+0x3c8]
        fmul  DWORD PTR ds:0x470c40
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [edi]
        fsub  st,st(2)
        fstp  DWORD PTR [edi]
        fld  DWORD PTR [edi+0x4]
        fsub  st,st(1)
        fstp  DWORD PTR [edi+0x4]
        fstp  st(0)
        fstp  st(0)
        fld  DWORD PTR [edi+0x8]
        fsub  DWORD PTR [esp+0x1c]
        fstp  DWORD PTR [edi+0x8]
        jmp loc_00406CDC
    loc_00406CB5:
        test  al,0x4
        je loc_00406CC4
        mov  WORD PTR [ebp+0x30c],0x8
        jmp loc_00406C66
    loc_00406CC4:
        test  al,0x8
        je loc_00406CD3
        mov  WORD PTR [ebp+0x30c],0x9
        jmp loc_00406C66
    loc_00406CD3:
        mov  WORD PTR [ebp+0x30c],0x2
    loc_00406CDC:
        lea  esi,[ebx+0x20]
        lea  edi,[ebp+0x464]
        mov  ecx,0x6c
        rep movsd
        mov  edx,DWORD PTR [ebx+0x1fc]
        mov  DWORD PTR [ebp+0x440],edx
        mov  DWORD PTR [ebp+0x43c],0x0
        mov  eax,DWORD PTR [ebx+0x208]
        mov  ecx,ebp
        mov  DWORD PTR [ebp+0x45c],eax
        call FUN_00406d90
        lea  eax,[ebp+0x8]
        push  eax
        call FUN_0043ee30
        add  ebp,0x7f0
        cmp  WORD PTR [ebp+0x446],0x5
        jne loc_00406D43
        mov  eax,DWORD PTR [esp+0x24]
        pop  edi
        lea  ecx,[eax+0x60]
        pop  esi
        mov  DWORD PTR [eax+0x10],ecx
        xor  eax,eax
        pop  ebp
        add  esp,0x14
        ret  0x10
    loc_00406D43:
        mov  edx,DWORD PTR [esp+0x24]
        pop  edi
        pop  esi
        mov  DWORD PTR [edx+0x10],ebp
        xor  eax,eax
        pop  ebp
        add  esp,0x14
        ret  0x10
        nop
        sbb  DWORD PTR [ecx+0x40],ebp
        add  BYTE PTR [ecx],bl
        imul  eax,DWORD PTR [eax+0x0],0x40696c
        je FUN_00406DCF
        inc  eax
        add  BYTE PTR [esi-0x51ffbf97],ah
        imul  eax,DWORD PTR [eax+0x0],0x4069ee
        or   DWORD PTR [edx+0x40],ebp
        add  BYTE PTR [ebp+0x6a],cl
        inc  eax
        add  dl,dl
        imul  eax,DWORD PTR [eax+0x0],0xffffffe2
        imul  eax,DWORD PTR [eax+0x0],0xfffffff5
        imul  eax,DWORD PTR [eax+0x0],0x1
        ins  BYTE PTR es:[edi],dx
        inc  eax
        _emit 0
        _emit 0xd
        ins  BYTE PTR es:[edi],dx
        inc  eax
    }
}

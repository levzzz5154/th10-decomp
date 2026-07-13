// 00433EF0: FUN_00433ef0
// Original size: 2800 bytes, actual code: 752 instructions
extern "C" void FUN_00409e50(void);
extern "C" void FUN_00420a90(void);
extern "C" void FUN_00420b10(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_004349e0(void);
extern "C" void FUN_00434a20(void);
extern "C" void FUN_00434a80(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0043e460(void);
extern "C" void FUN_00447a50(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00449450(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00433ef0(void) {
    __asm {
        sub  esp,0x1c
        push  ebp
        mov  ebp,DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [ebp+0x20]
        cmp  eax,0x3
        ja loc_004349C1
        push  ebx
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x4349cc]
        cmp  DWORD PTR [ebp+0x2b4],0x1
        jne loc_00434101
        mov  DWORD PTR [ebp+0x2c],0x6
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_00433F38
        jg loc_00433F31
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00433F3F
    loc_00433F31:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00433F3F
    loc_00433F38:
        mov  DWORD PTR [ebp+0x24],0x0
    loc_00433F3F:
        mov  eax,DWORD PTR [ebp+0x440]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        jne loc_00433F82
        push  ebp
        mov  edi,0x5f
        call FUN_0042c670
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  eax,DWORD PTR [ecx+0x8994]
        push  0xf
        push  0x8
        push  eax
        lea  edi,[esp+0x28]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x5d0],edx
    loc_00433F82:
        push  ebp
        mov  edi,0x67
        call FUN_0042c670
        push  0x0
        lea  eax,[esp+0x34]
        push  eax
        mov  eax,0x46ed14
        mov  DWORD PTR [esp+0x20],0x0
        call FUN_0044b360
        test  eax,eax
        mov  DWORD PTR [ebp+0x5aac],eax
        je loc_00434803
        mov  ecx,DWORD PTR [esp+0x30]
        test  ecx,ecx
        jle loc_00434054
        lea  ecx,[ebp+0xe98]
        lea  edx,[ebp+0x698]
        lea  esi,[ebp+0x16d8]
        mov  DWORD PTR [esp+0x14],ecx
        mov  DWORD PTR [esp+0x10],edx
        lea  ebx,[ebx+0x0]
    loc_00433FE0:
        mov  cl,BYTE PTR [eax]
        cmp  cl,0x23
        je loc_00434043
        cmp  cl,0x40
        jne loc_00434043
        lea  ecx,[eax+0x1]
        mov  eax,DWORD PTR [esp+0x10]
        push  eax
        lea  edi,[esp+0x34]
        call FUN_00434a20
        mov  ecx,DWORD PTR [esp+0x14]
        push  ecx
        mov  ecx,eax
        call FUN_00434a20
        mov  ebx,0x8
        mov  edi,edi
    loc_00434010:
        push  esi
        lea  edi,[esp+0x34]
        mov  ecx,eax
        call FUN_00434a20
        add  esi,0x42
        dec  ebx
        jne loc_00434010
        mov  edi,DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x14]
        inc  edi
        add  edx,0x40
        add  ecx,0x42
        mov  DWORD PTR [esp+0x18],edi
        mov  DWORD PTR [esp+0x10],edx
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0043404C
    loc_00434043:
        lea  edx,[esp+0x30]
        call FUN_004349e0
    loc_0043404C:
        mov  ecx,DWORD PTR [esp+0x30]
        test  ecx,ecx
        jg loc_00433FE0
    loc_00434054:
        mov  ecx,DWORD PTR [esp+0x18]
        mov  eax,ecx
        xor  edi,edi
        cmp  eax,edi
        mov  DWORD PTR [ebp+0x2c],ecx
        je loc_00434072
        jg loc_0043406B
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00434075
    loc_0043406B:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00434075
    loc_00434072:
        mov  DWORD PTR [ebp+0x24],edi
    loc_00434075:
        lea  edx,[ebp+0x664]
        mov  DWORD PTR [ebp+0x58d8],edi
        mov  DWORD PTR [ebp+0x688],ecx
        mov  DWORD PTR [esp+0x30],edx
        jmp loc_00434090
        nop
    loc_00434090:
        mov  eax,ds:0x491fec
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [esp+0x18],eax
        call FUN_00449950
        mov  ebx,eax
        or   DWORD PTR [ebx+0x35c],0x40000000
        lea  ecx,[edi+0x27]
        push  ecx
        mov  ecx,DWORD PTR [esp+0x1c]
        push  ebx
        mov  DWORD PTR [ebx+0x20],0xf
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x14]
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x30]
        mov  edx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax],edx
        inc  edi
        add  eax,0x4
        cmp  edi,0x8
        mov  DWORD PTR [esp+0x30],eax
        jl loc_00434090
        xor  ecx,ecx
        mov  DWORD PTR [ebp+0x68c],ecx
        mov  DWORD PTR [ebp+0x690],ecx
        mov  DWORD PTR [ebp+0x694],ecx
        jmp loc_00434103
    loc_00434101:
        xor  ecx,ecx
    loc_00434103:
        mov  eax,DWORD PTR [ebp+0x2b4]
        cmp  eax,0xa
        jge loc_004342DD
        fild  DWORD PTR [ebp+0x58d8]
        lea  edx,[eax+eax*4]
        lea  edx,[edx*8-0x28]
        mov  DWORD PTR [esp+0x30],edx
        fmul  DWORD PTR ds:0x470ca0
        add  eax,eax
        lea  edi,[eax-0x2]
        cmp  edi,eax
        fsubr DWORD PTR ds:0x470c80
        mov  DWORD PTR [esp+0x20],0x42800000
        mov  DWORD PTR [esp+0x28],0x0
        fiadd DWORD PTR [esp+0x30]
        fstp  DWORD PTR [esp+0x24]
        jge loc_004342DD
        mov  eax,edi
        imul  eax,eax,0x42
        lea  edx,[eax+ebp*1+0xe98]
        lea  eax,[ebp+edi*4+0x614]
        mov  DWORD PTR [esp+0x18],edx
        mov  DWORD PTR [esp+0x30],eax
    loc_00434172:
        cmp  edi,DWORD PTR [ebp+0x688]
        jge loc_004342DD
        mov  ecx,DWORD PTR [ebp+0x14]
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [esp+0x14],ecx
        call FUN_00449950
        mov  ecx,DWORD PTR [esp+0x14]
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x35c]
        lea  edx,[edi+0xad]
        push  edx
        or   eax,0x40000000
        push  ebx
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],eax
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x10]
        mov  edx,esi
        call FUN_004489d0
        mov  ecx,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x30]
        mov  edx,ecx
        push  edx
        mov  edx,esi
        mov  DWORD PTR [eax],ecx
        call FUN_004491c0
        mov  ebx,eax
        test  ebx,ebx
        jne loc_004341EC
        mov  eax,DWORD PTR [esp+0x30]
        mov  DWORD PTR [eax],ebx
    loc_004341EC:
        mov  ecx,DWORD PTR ds:0x47783c
        mov  al,BYTE PTR [ecx+edi*1+0x1d892]
        test  al,al
        je loc_00434214
        mov  edx,DWORD PTR [esp+0x18]
        push  edx
        push  0xffffff
        push  esi
        mov  esi,ebx
        call FUN_00447a50
        add  esp,0xc
        jmp loc_0043422D
    loc_00434214:
        lea  eax,[edi+0x1]
        push  eax
        push  0x46ecf4
        push  0xffffff
        push  esi
        mov  esi,ebx
        call FUN_00447a50
        add  esp,0x10
    loc_0043422D:
        mov  eax,DWORD PTR [ebp+0x58d8]
        cmp  edi,eax
        jl loc_00434249
        add  eax,0xa
        cmp  edi,eax
        jge loc_00434249
        mov  eax,DWORD PTR [ebx+0x35c]
        or   eax,0x2
        jmp loc_00434252
    loc_00434249:
        mov  eax,DWORD PTR [ebx+0x35c]
        and  eax,0xfffffffd
    loc_00434252:
        mov  DWORD PTR [ebx+0x35c],eax
        cmp  edi,DWORD PTR [ebp+0x24]
        jne loc_0043426B
        fld  DWORD PTR [esp+0x20]
        fsub  QWORD PTR ds:0x470c98
        fstp  DWORD PTR [esp+0x20]
    loc_0043426B:
        push  0x0
        lea  edx,[ebx+0x334]
        push  0x4
        lea  ecx,[esp+0x28]
        mov  eax,ebx
        call FUN_00434a80
        mov  eax,DWORD PTR [ebp+0x24]
        cmp  edi,eax
        jne loc_00434295
        fld  DWORD PTR [esp+0x20]
        fadd  QWORD PTR ds:0x470c98
        fstp  DWORD PTR [esp+0x20]
    loc_00434295:
        mov  edx,DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x24]
        mov  esi,DWORD PTR [esp+0x30]
        fadd  DWORD PTR ds:0x470ca0
        xor  ecx,ecx
        cmp  edi,eax
        setne cl
        fstp  DWORD PTR [esp+0x24]
        add  edx,0x42
        mov  DWORD PTR [esp+0x18],edx
        add  esi,0x4
        mov  DWORD PTR [esp+0x30],esi
        add  ecx,0x2
        mov  WORD PTR [ebx+0x304],cx
        mov  edx,DWORD PTR [ebp+0x2b4]
        inc  edi
        shl  edx,1
        xor  ecx,ecx
        cmp  edi,edx
        jl loc_00434172
    loc_004342DD:
        cmp  DWORD PTR [ebp+0x2b4],0xa
        jl loc_004349BE
        mov  DWORD PTR [ebp+0x20],0x1
        mov  eax,DWORD PTR [ebp+0x2c0]
        test  al,0x1
        jne loc_00434324
        or   eax,0x1
        mov  DWORD PTR [ebp+0x2b4],ecx
        mov  DWORD PTR [ebp+0x2b0],0xfff0bdc1
        mov  DWORD PTR [ebp+0x2b8],ecx
        mov  DWORD PTR [ebp+0x2bc],0x476f78
        mov  DWORD PTR [ebp+0x2c0],eax
    loc_00434324:
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR [ebp+0x2b4],ecx
        mov  DWORD PTR [ebp+0x2b8],ecx
        mov  DWORD PTR [ebp+0x2b0],0xffffffff
        xor  eax,eax
        pop  ebp
        add  esp,0x1c
        ret  0x4
        mov  eax,DWORD PTR [ebp+0x2b4]
        and  eax,0x80000001
        jns loc_00434358
        dec  eax
        or   eax,0xfffffffe
        inc  eax
    loc_00434358:
        jne loc_004343F6
        mov  eax,DWORD PTR [ebp+0x68c]
        cmp  eax,0x8
        jge loc_004343F6
        lea  esi,[ebp+eax*4+0x664]
        call FUN_00449450
        mov  ecx,DWORD PTR ds:0x47783c
        mov  esi,eax
        mov  eax,DWORD PTR [ebp+0x690]
        mov  dl,BYTE PTR [eax+ecx*1+0x1d892]
        test  dl,dl
        jne loc_004343B8
        mov  ecx,DWORD PTR [ebp+0x694]
        test  ecx,ecx
        je loc_004343B8
        mov  edx,DWORD PTR [ebp+0x68c]
        mov  eax,DWORD PTR [edx*4+0x476fd8]
        mov  ecx,DWORD PTR ds:0x491c10
        push  eax
        push  0x8080ff
        push  ecx
        jmp loc_004343D8
    loc_004343B8:
        mov  edx,DWORD PTR [ebp+0x68c]
        lea  eax,[edx+eax*8]
        mov  edx,DWORD PTR ds:0x491c10
        imul  eax,eax,0x42
        lea  ecx,[eax+ebp*1+0x16d8]
        push  ecx
        push  0xffffff
        push  edx
    loc_004343D8:
        call FUN_00447a50
        mov  WORD PTR [esi+0x304],0x2
        mov  eax,DWORD PTR [ebp+0x68c]
        add  esp,0xc
        inc  eax
        mov  DWORD PTR [ebp+0x68c],eax
    loc_004343F6:
        cmp  DWORD PTR [ebp+0x2b4],0x4
        jle loc_004349BE
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
        pop  edi
        pop  esi
        pop  ebx
        xor  eax,eax
        pop  ebp
        add  esp,0x1c
        ret  0x4
        mov  eax,DWORD PTR [ebp+0x2b4]
        and  eax,0x80000001
        jns loc_0043442D
        dec  eax
        or   eax,0xfffffffe
        inc  eax
    loc_0043442D:
        jne loc_004344CD
        mov  eax,DWORD PTR [ebp+0x68c]
        cmp  eax,0x8
        jge loc_004344CD
        lea  esi,[ebp+eax*4+0x664]
        call FUN_00449450
        mov  ecx,DWORD PTR ds:0x47783c
        mov  esi,eax
        mov  eax,DWORD PTR [ebp+0x690]
        mov  dl,BYTE PTR [eax+ecx*1+0x1d892]
        xor  ebx,ebx
        test  dl,dl
        jne loc_0043448D
        cmp  DWORD PTR [ebp+0x694],ebx
        je loc_0043448D
        mov  edx,DWORD PTR [ebp+0x68c]
        mov  eax,DWORD PTR [edx*4+0x476fd8]
        mov  ecx,DWORD PTR ds:0x491c10
        push  eax
        push  0x8080ff
        push  ecx
        jmp loc_004344AD
    loc_0043448D:
        mov  edx,DWORD PTR [ebp+0x68c]
        lea  eax,[edx+eax*8]
        mov  edx,DWORD PTR ds:0x491c10
        imul  eax,eax,0x42
        lea  ecx,[eax+ebp*1+0x16d8]
        push  ecx
        push  0xffffff
        push  edx
    loc_004344AD:
        call FUN_00447a50
        mov  WORD PTR [esi+0x304],0x2
        mov  eax,DWORD PTR [ebp+0x68c]
        add  esp,0xc
        inc  eax
        mov  DWORD PTR [ebp+0x68c],eax
        jmp loc_004344CF
    loc_004344CD:
        xor  ebx,ebx
    loc_004344CF:
        mov  eax,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x24]
        mov  DWORD PTR [esi+0x4],eax
        test  BYTE PTR ds:0x474e36,0x10
        jne loc_004344EA
        test  BYTE PTR ds:0x474e34,0x10
        je loc_004344F3
    loc_004344EA:
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
    loc_004344F3:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x20
        test  al,cl
        jne loc_00434507
        test  BYTE PTR ds:0x474e34,al
        je loc_00434510
    loc_00434507:
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
    loc_00434510:
        mov  ecx,DWORD PTR [esi+0x4]
        cmp  ecx,DWORD PTR [esi]
        je loc_00434673
        push  ebx
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,DWORD PTR [ebp+0x58d8]
        mov  eax,DWORD PTR [esi]
        cmp  eax,ecx
        jl loc_00434541
        add  ecx,0xa
        cmp  eax,ecx
        jl loc_00434547
        add  eax,0xfffffff7
    loc_00434541:
        mov  DWORD PTR [ebp+0x58d8],eax
    loc_00434547:
        fild  DWORD PTR [ebp+0x58d8]
        mov  eax,DWORD PTR [ebp+0x688]
        xor  edi,edi
        cmp  eax,ebx
        fmul  DWORD PTR ds:0x470ca0
        mov  DWORD PTR [esp+0x20],0x42800000
        mov  DWORD PTR [esp+0x28],0x0
        fsubr DWORD PTR ds:0x470c80
        fstp  DWORD PTR [esp+0x24]
        jle loc_00434667
        lea  ebx,[ebp+0x614]
    loc_00434583:
        mov  edx,DWORD PTR [ebx]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        call FUN_004491c0
        mov  esi,eax
        test  esi,esi
        jne loc_00434599
        mov  DWORD PTR [ebx],eax
    loc_00434599:
        mov  eax,DWORD PTR [ebp+0x58d8]
        cmp  edi,eax
        jl loc_004345B5
        add  eax,0xa
        cmp  edi,eax
        jge loc_004345B5
        mov  eax,DWORD PTR [esi+0x35c]
        or   eax,0x2
        jmp loc_004345BE
    loc_004345B5:
        mov  eax,DWORD PTR [esi+0x35c]
        and  eax,0xfffffffd
    loc_004345BE:
        mov  DWORD PTR [esi+0x35c],eax
        cmp  edi,DWORD PTR [ebp+0x24]
        jne loc_004345D7
        fld  DWORD PTR [esp+0x20]
        fsub  QWORD PTR ds:0x470c98
        fstp  DWORD PTR [esp+0x20]
    loc_004345D7:
        fld  DWORD PTR [esi+0x338]
        fsub  DWORD PTR [esp+0x24]
        fabs
        fcomp DWORD PTR ds:0x470c64
        fnstsw ax
        test  ah,0x5
        jp loc_00434607
        push  0x0
        lea  edx,[esi+0x334]
        push  0x4
        lea  ecx,[esp+0x28]
        mov  eax,esi
        call FUN_00434a80
        jmp loc_00434621
    loc_00434607:
        mov  ecx,DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [esp+0x24]
        lea  eax,[esi+0x334]
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [esp+0x28]
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [eax+0x8],ecx
    loc_00434621:
        mov  eax,DWORD PTR [ebp+0x24]
        cmp  edi,eax
        jne loc_00434636
        fld  DWORD PTR [esp+0x20]
        fadd  QWORD PTR ds:0x470c98
        fstp  DWORD PTR [esp+0x20]
    loc_00434636:
        fld  DWORD PTR [esp+0x24]
        xor  edx,edx
        fadd  DWORD PTR ds:0x470ca0
        cmp  edi,eax
        setne dl
        add  ebx,0x4
        fstp  DWORD PTR [esp+0x24]
        add  edx,0x2
        mov  WORD PTR [esi+0x304],dx
        mov  eax,DWORD PTR [ebp+0x688]
        inc  edi
        cmp  edi,eax
        jl loc_00434583
    loc_00434667:
        mov  DWORD PTR [ebp+0x694],0x0
        xor  ebx,ebx
    loc_00434673:
        mov  eax,ds:0x474e36
        test  eax,0x1001
        je loc_004347FB
        lea  esi,[ebp+0x664]
        mov  edi,0x8
        mov  edi,edi
    loc_00434690:
        mov  eax,DWORD PTR [esi]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        cmp  eax,ebx
        je loc_004346D0
        cmp  DWORD PTR [eax+0x18],ebx
        mov  ecx,0x3
        mov  WORD PTR [eax+0x304],cx
        jne loc_004346D0
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,ebx
        je loc_004346D0
        lea  ebx,[ebx+0x0]
    loc_004346C0:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_004346C0
    loc_004346D0:
        add  esi,0x4
        dec  edi
        jne loc_00434690
        mov  eax,DWORD PTR [ebp+0x24]
        mov  DWORD PTR [ebp+0x690],eax
        mov  DWORD PTR [ebp+0x68c],ebx
        mov  eax,DWORD PTR [ebp+0x2c0]
        test  al,0x1
        jne loc_00434718
        or   eax,0x1
        mov  DWORD PTR [ebp+0x2b4],ebx
        mov  DWORD PTR [ebp+0x2b0],0xfff0bdc1
        mov  DWORD PTR [ebp+0x2b8],ebx
        mov  DWORD PTR [ebp+0x2bc],0x476f78
        mov  DWORD PTR [ebp+0x2c0],eax
    loc_00434718:
        mov  edx,DWORD PTR ds:0x47783c
        mov  DWORD PTR [ebp+0x2b4],ebx
        mov  DWORD PTR [ebp+0x2b8],ebx
        mov  DWORD PTR [ebp+0x2b0],0xffffffff
        mov  ecx,DWORD PTR [ebp+0x690]
        mov  al,BYTE PTR [ecx+edx*1+0x1d892]
        test  al,al
        jne loc_0043479B
        cmp  DWORD PTR [ebp+0x694],ebx
        jne loc_0043479B
        test  BYTE PTR ds:0x491d78,0x10
        mov  edx,0x46df98
        push  ebx
        mov  eax,0x492590
        je loc_0043477E
        push  0x4
        call FUN_0043e460
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR [ebp+0x694],0x1
        xor  eax,eax
        pop  ebp
        add  esp,0x1c
        ret  0x4
    loc_0043477E:
        push  0x3
        call FUN_0043e460
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR [ebp+0x694],0x1
        xor  eax,eax
        pop  ebp
        add  esp,0x1c
        ret  0x4
    loc_0043479B:
        mov  eax,DWORD PTR [ebp+0x24]
        shl  eax,0x6
        lea  ecx,[eax+ebp*1+0x698]
        push  ecx
        push  ebx
        call FUN_00420a90
        test  BYTE PTR ds:0x491d78,0x10
        je loc_004347CA
        push  ebx
        push  0x4
        mov  edx,0x46df98
        mov  eax,0x492590
        call FUN_0043e460
    loc_004347CA:
        push  ebx
        push  0x2
        mov  edx,0x46df98
        mov  eax,0x492590
        call FUN_0043e460
        mov  edx,DWORD PTR ds:0x47783c
        pop  edi
        pop  esi
        mov  BYTE PTR [edx+0x1d892],0x1
        mov  DWORD PTR [ebp+0x694],ebx
        pop  ebx
        xor  eax,eax
        pop  ebp
        add  esp,0x1c
        ret  0x4
    loc_004347FB:
        test  al,0xa
        je loc_004349BE
    loc_00434803:
        mov  eax,DWORD PTR [ebp+0x5aac]
        xor  ebx,ebx
        cmp  eax,ebx
        je loc_0043481E
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebp+0x5aac],ebx
    loc_0043481E:
        lea  eax,[ebp+0x24]
        mov  DWORD PTR [ebp+0x5aac],ebx
        call FUN_0044be70
        mov  eax,DWORD PTR [ebp+0x688]
        xor  esi,esi
        cmp  eax,ebx
        jle loc_00434855
        lea  edi,[ebp+0x614]
        mov  edi,edi
    loc_00434840:
        mov  eax,edi
        call FUN_00409e50
        mov  eax,DWORD PTR [ebp+0x688]
        inc  esi
        add  edi,0x4
        cmp  esi,eax
        jl loc_00434840
    loc_00434855:
        mov  esi,DWORD PTR ds:0x491c10
        lea  edx,[ebp+0x664]
        mov  DWORD PTR [esp+0x30],0x8
        nop
    loc_00434870:
        mov  ecx,DWORD PTR [edx]
        cmp  ecx,ebx
        je loc_004348D4
        mov  eax,DWORD PTR [esi+0x72dad4]
        cmp  eax,ebx
        je loc_0043488D
    loc_00434880:
        mov  edi,DWORD PTR [eax]
        cmp  DWORD PTR [edi],ecx
        je loc_004348A6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00434880
    loc_0043488D:
        mov  eax,DWORD PTR [esi+0x72dadc]
        cmp  eax,ebx
        je loc_004348D4
    loc_00434897:
        mov  edi,DWORD PTR [eax]
        cmp  DWORD PTR [edi],ecx
        je loc_004348A6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00434897
        jmp loc_004348D4
    loc_004348A6:
        mov  eax,DWORD PTR [eax]
        cmp  eax,ebx
        je loc_004348D4
        cmp  DWORD PTR [eax+0x18],ebx
        mov  ecx,0x1
        mov  WORD PTR [eax+0x304],cx
        jne loc_004348D4
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,ebx
        je loc_004348D4
    loc_004348C4:
        mov  edi,DWORD PTR [eax]
        mov  WORD PTR [edi+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_004348C4
    loc_004348D4:
        mov  eax,DWORD PTR [esp+0x30]
        add  edx,0x4
        dec  eax
        mov  DWORD PTR [esp+0x30],eax
        jne loc_00434870
        push  ebx
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  DWORD PTR [ebp+0x20],0x3
        mov  eax,DWORD PTR [ebp+0x2c0]
        test  al,0x1
        jne loc_0043492C
        or   eax,0x1
        mov  DWORD PTR [ebp+0x2b4],ebx
        mov  DWORD PTR [ebp+0x2b0],0xfff0bdc1
        mov  DWORD PTR [ebp+0x2b8],ebx
        mov  DWORD PTR [ebp+0x2bc],0x476f78
        mov  DWORD PTR [ebp+0x2c0],eax
    loc_0043492C:
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x2b4],ebx
        mov  DWORD PTR [ebp+0x2b8],ebx
        pop  ebx
        mov  DWORD PTR [ebp+0x2b0],0xffffffff
        xor  eax,eax
        pop  ebp
        add  esp,0x1c
        ret  0x4
        cmp  DWORD PTR [ebp+0x2b4],0xa
        jl loc_004349BE
        mov  esi,0x67
        mov  edi,ebp
        call FUN_0042c6d0
        mov  esi,0x8
        mov  ecx,0x5a
        mov  eax,ebp
        call FUN_0042c770
        mov  ecx,0x5b
        mov  eax,ebp
        call FUN_0042c770
        mov  esi,0x5f
        call FUN_0042c6d0
        lea  eax,[ebp+0x5d0]
        call FUN_00409e50
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c5c0
        push  0x46f018
        push  0x0
        call FUN_00420a90
        push  0x0
        push  0x0
        call FUN_00420b10
        lea  eax,[ebp+0x24]
        call FUN_0044be70
    loc_004349BE:
        pop  edi
        pop  esi
        pop  ebx
    loc_004349C1:
        xor  eax,eax
        pop  ebp
        add  esp,0x1c
        ret  0x4
        mov  edi,edi
        push  cs
        aas
        inc  ebx
        add  BYTE PTR [esi+0x43],al
        inc  ebx
        add  BYTE PTR [ebx],bl
        inc  esp
        inc  ebx
        add  BYTE PTR [esi+0x49],cl
        inc  ebx
        add  ah,cl
    }
}

// 00403C80: FUN_00403c80
// Original size: 2000 bytes, actual code: 526 instructions
extern "C" void FUN_00404610(void);
extern "C" void FUN_004049a0(void);
extern "C" void FUN_00404ed0(void);
extern "C" void FUN_00404f30(void);
extern "C" void FUN_00405040(void);
extern "C" void FUN_00405410(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00403c80(void) {
    __asm {
        sub  esp,0x8c
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x98]
        mov  eax,DWORD PTR [ebp+0x4c]
        mov  ecx,DWORD PTR [eax]
        cmp  ecx,DWORD PTR [ebp+0x3c]
        push  esi
        push  edi
        jg loc_0040426B
        mov  ebx,0xfff0bdc1
    loc_00403CA4:
        mov  edi,DWORD PTR [ebp+0x4c]
        movsx eax,WORD PTR [edi+0x4]
        cmp  eax,0xe
        ja loc_00404251
        jmp  DWORD PTR [eax*4+0x404390]
        mov  eax,DWORD PTR [ebp+0x48]
        test  al,0x1
        mov  edi,DWORD PTR [edi+0xc]
        mov  DWORD PTR [esp+0x10],edi
        jne loc_00403CE1
        xor  ecx,ecx
        or   eax,0x1
        mov  DWORD PTR [ebp+0x3c],ecx
        mov  DWORD PTR [ebp+0x38],ebx
        mov  DWORD PTR [ebp+0x40],ecx
        mov  DWORD PTR [ebp+0x44],0x476f78
        mov  DWORD PTR [ebp+0x48],eax
    loc_00403CE1:
        fild  DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebp+0x3c],edi
        dec  edi
        mov  DWORD PTR [ebp+0x38],edi
        fstp  DWORD PTR [ebp+0x40]
        mov  edx,DWORD PTR [ebp+0x4c]
        mov  ecx,DWORD PTR [edx+0x8]
        mov  eax,DWORD PTR [ebp+0x1c]
        add  eax,ecx
        mov  DWORD PTR [ebp+0x4c],eax
        jmp loc_0040425D
        lea  ecx,[ebp+0x2a4c]
        lea  eax,[ebp+0x2b3c]
        mov  edx,ecx
        mov  ebx,DWORD PTR [edx]
        mov  esi,eax
        mov  DWORD PTR [esi],ebx
        mov  ebx,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [esi+0x4],ebx
        mov  DWORD PTR [esi+0x8],edx
        mov  edx,DWORD PTR [edi+0x8]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [edi+0xc]
        mov  DWORD PTR [ebp+0x2a50],edx
        mov  edx,DWORD PTR [edi+0x10]
        mov  DWORD PTR [ebp+0x2a54],edx
        fld  DWORD PTR [ecx]
        fsub  DWORD PTR [eax]
        mov  ebx,0xfff0bdc1
        fstp  DWORD PTR [esp+0x74]
        fld  DWORD PTR [ecx+0x4]
        fsub  DWORD PTR [eax+0x4]
        fstp  DWORD PTR [esp+0x78]
        mov  edx,DWORD PTR [esp+0x78]
        fld  DWORD PTR [ecx+0x8]
        mov  ecx,DWORD PTR [esp+0x74]
        fsub  DWORD PTR [eax+0x8]
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],edx
        fstp  DWORD PTR [esp+0x7c]
        mov  ecx,DWORD PTR [esp+0x7c]
        mov  DWORD PTR [eax+0x8],ecx
        jmp loc_00404251
        mov  edx,DWORD PTR [edi+0x10]
        mov  eax,DWORD PTR [edi+0x14]
        mov  ecx,DWORD PTR [edi+0x18]
        mov  DWORD PTR [esp+0x68],edx
        mov  edx,DWORD PTR [edi+0x8]
        mov  DWORD PTR [ebp+0xe0],edx
        mov  DWORD PTR [esp+0x6c],eax
        mov  eax,DWORD PTR [edi+0xc]
        mov  DWORD PTR [esp+0x70],ecx
        mov  DWORD PTR [ebp+0xe4],eax
        lea  ecx,[ebp+0x2a4c]
        mov  eax,DWORD PTR [ecx]
        lea  edx,[ebp+0x9c]
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [ecx+0x4]
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edx+0x4],eax
        mov  eax,DWORD PTR [esp+0x68]
        mov  DWORD PTR [edx+0x8],ecx
        mov  ecx,DWORD PTR [esp+0x6c]
        lea  edx,[ebp+0xa8]
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [esp+0x70]
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [edx+0x8],eax
        jmp loc_00404086
        mov  ecx,DWORD PTR [edi+0x8]
        mov  DWORD PTR [ebp+0x2a58],ecx
        mov  edx,DWORD PTR [edi+0xc]
        mov  DWORD PTR [ebp+0x2a5c],edx
        mov  eax,DWORD PTR [edi+0x10]
        mov  DWORD PTR [ebp+0x2a60],eax
        jmp loc_00404251
        mov  ecx,DWORD PTR [edi+0x10]
        mov  edx,DWORD PTR [edi+0x14]
        mov  eax,DWORD PTR [edi+0x18]
        mov  DWORD PTR [esp+0x5c],ecx
        mov  ecx,DWORD PTR [edi+0x8]
        mov  DWORD PTR [ebp+0x94],ecx
        mov  DWORD PTR [esp+0x60],edx
        mov  edx,DWORD PTR [edi+0xc]
        mov  DWORD PTR [esp+0x64],eax
        mov  DWORD PTR [ebp+0x98],edx
        lea  eax,[ebp+0x2a58]
        mov  edx,DWORD PTR [eax]
        lea  ecx,[ebp+0x50]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x4],edx
        mov  edx,DWORD PTR [esp+0x5c]
        mov  DWORD PTR [ecx+0x8],eax
        mov  eax,DWORD PTR [esp+0x60]
        lea  ecx,[ebp+0x5c]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [esp+0x64]
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [ecx+0x8],edx
        jmp loc_00404182
        mov  eax,DWORD PTR [edi+0x8]
        mov  DWORD PTR [ebp+0x2a64],eax
        mov  ecx,DWORD PTR [edi+0xc]
        mov  DWORD PTR [ebp+0x2a68],ecx
        mov  edx,DWORD PTR [edi+0x10]
        mov  DWORD PTR [ebp+0x2a6c],edx
        jmp loc_00404251
        mov  eax,DWORD PTR [edi+0x8]
        mov  DWORD PTR [ebp+0x2a94],eax
        jmp loc_00404251
        mov  ecx,DWORD PTR [edi+0x8]
        movzx edx,cl
        mov  DWORD PTR [ebp+0x2b60],ecx
        movzx eax,BYTE PTR [ebp+0x2b61]
        movzx ecx,BYTE PTR [ebp+0x2b62]
        mov  DWORD PTR [esp+0x10],edx
        movzx edx,BYTE PTR [ebp+0x2b63]
        fild  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x10],eax
        fstp  DWORD PTR [ebp+0x2b50]
        fild  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x10],ecx
        fstp  DWORD PTR [ebp+0x2b54]
        fild  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x10],edx
        fstp  DWORD PTR [ebp+0x2b58]
        fild  DWORD PTR [esp+0x10]
        fstp  DWORD PTR [ebp+0x2b5c]
        mov  eax,DWORD PTR [edi+0xc]
        mov  DWORD PTR [ebp+0x2b48],eax
        mov  ecx,DWORD PTR [edi+0x10]
        mov  DWORD PTR [ebp+0x2b4c],ecx
        jmp loc_00404251
        movzx edx,BYTE PTR [edi+0x13]
        movzx eax,BYTE PTR [edi+0x12]
        movzx ecx,BYTE PTR [edi+0x11]
        mov  DWORD PTR [esp+0x10],edx
        movzx edx,BYTE PTR [edi+0x10]
        fild  DWORD PTR [esp+0x10]
        sub  esp,0x10
        mov  DWORD PTR [esp+0x20],eax
        mov  eax,DWORD PTR [edi+0x18]
        fstp  DWORD PTR [esp+0xc]
        lea  esi,[esp+0x90]
        fild  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x20],ecx
        mov  ecx,DWORD PTR [edi+0x14]
        fstp  DWORD PTR [esp+0x8]
        fild  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x20],edx
        fstp  DWORD PTR [esp+0x4]
        fild  DWORD PTR [esp+0x20]
        fstp  DWORD PTR [esp]
        push  eax
        push  ecx
        call FUN_00405040
        mov  edx,DWORD PTR [edi+0x8]
        mov  DWORD PTR [ebp+0x16c],edx
        mov  eax,DWORD PTR [edi+0xc]
        lea  esi,[ebp+0x2b48]
        lea  edi,[ebp+0xe8]
        mov  ecx,0x7
        rep movsd
        lea  edi,[ebp+0x104]
        mov  ecx,0x7
        lea  esi,[esp+0x80]
        rep movsd
        mov  DWORD PTR [ebp+0x170],eax
        mov  eax,DWORD PTR [ebp+0x168]
        xor  ecx,ecx
        test  al,0x1
        jne loc_00403FAF
        or   eax,0x1
        mov  DWORD PTR [ebp+0x15c],ecx
        mov  DWORD PTR [ebp+0x158],ebx
        mov  DWORD PTR [ebp+0x160],ecx
        mov  DWORD PTR [ebp+0x164],0x476f78
        mov  DWORD PTR [ebp+0x168],eax
    loc_00403FAF:
        mov  DWORD PTR [ebp+0x15c],ecx
        mov  DWORD PTR [ebp+0x160],ecx
        mov  DWORD PTR [ebp+0x158],0xffffffff
        jmp loc_00404251
        mov  ecx,DWORD PTR [edi+0x10]
        mov  edx,DWORD PTR [edi+0x14]
        mov  eax,DWORD PTR [edi+0x18]
        mov  DWORD PTR [esp+0x44],ecx
        mov  ecx,DWORD PTR [edi+0x1c]
        mov  DWORD PTR [esp+0x48],edx
        mov  edx,DWORD PTR [edi+0x20]
        mov  DWORD PTR [esp+0x4c],eax
        mov  eax,DWORD PTR [edi+0x24]
        mov  DWORD PTR [esp+0x20],ecx
        mov  ecx,DWORD PTR [edi+0x28]
        mov  DWORD PTR [esp+0x24],edx
        mov  edx,DWORD PTR [edi+0x2c]
        mov  DWORD PTR [esp+0x28],eax
        mov  eax,DWORD PTR [edi+0x30]
        mov  DWORD PTR [esp+0x2c],ecx
        mov  ecx,DWORD PTR [edi+0x8]
        mov  DWORD PTR [esp+0x30],edx
        mov  DWORD PTR [esp+0x34],eax
        mov  DWORD PTR [ebp+0xe0],ecx
        lea  edx,[ebp+0x2a4c]
        mov  ecx,DWORD PTR [edx]
        lea  eax,[ebp+0x9c]
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [eax+0x4],ecx
        mov  ecx,DWORD PTR [esp+0x44]
        mov  DWORD PTR [eax+0x8],edx
        mov  edx,DWORD PTR [esp+0x48]
        lea  eax,[ebp+0xb4]
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [esp+0x4c]
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [eax+0x8],ecx
        mov  eax,DWORD PTR [esp+0x20]
        mov  ecx,DWORD PTR [esp+0x24]
        lea  edx,[ebp+0xa8]
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [esp+0x28]
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [edx+0x8],eax
        mov  edx,DWORD PTR [esp+0x2c]
        mov  eax,DWORD PTR [esp+0x30]
        lea  ecx,[ebp+0xc0]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [esp+0x34]
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [ebp+0xe4],0x8
        mov  DWORD PTR [ecx+0x8],edx
    loc_00404086:
        mov  eax,DWORD PTR [ebp+0xdc]
        xor  ecx,ecx
        test  al,0x1
        jne loc_004040B7
        mov  DWORD PTR [ebp+0xd0],ecx
        mov  DWORD PTR [ebp+0xcc],ebx
        mov  DWORD PTR [ebp+0xd4],ecx
        or   eax,0x1
        mov  DWORD PTR [ebp+0xd8],0x476f78
        mov  DWORD PTR [ebp+0xdc],eax
    loc_004040B7:
        mov  DWORD PTR [ebp+0xd0],ecx
        mov  DWORD PTR [ebp+0xd4],ecx
        mov  DWORD PTR [ebp+0xcc],0xffffffff
        jmp loc_00404251
        mov  eax,DWORD PTR [edi+0x10]
        mov  ecx,DWORD PTR [edi+0x14]
        mov  edx,DWORD PTR [edi+0x18]
        mov  DWORD PTR [esp+0x38],eax
        mov  eax,DWORD PTR [edi+0x1c]
        mov  DWORD PTR [esp+0x3c],ecx
        mov  ecx,DWORD PTR [edi+0x20]
        mov  DWORD PTR [esp+0x40],edx
        mov  edx,DWORD PTR [edi+0x24]
        mov  DWORD PTR [esp+0x50],eax
        mov  eax,DWORD PTR [edi+0x28]
        mov  DWORD PTR [esp+0x54],ecx
        mov  ecx,DWORD PTR [edi+0x2c]
        mov  DWORD PTR [esp+0x58],edx
        mov  edx,DWORD PTR [edi+0x30]
        mov  DWORD PTR [esp+0x14],eax
        mov  eax,DWORD PTR [edi+0x8]
        mov  DWORD PTR [esp+0x18],ecx
        mov  DWORD PTR [esp+0x1c],edx
        mov  DWORD PTR [ebp+0x94],eax
        lea  ecx,[ebp+0x2a58]
        mov  eax,DWORD PTR [ecx]
        lea  edx,[ebp+0x50]
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [ecx+0x4]
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edx+0x4],eax
        mov  eax,DWORD PTR [esp+0x38]
        mov  DWORD PTR [edx+0x8],ecx
        mov  ecx,DWORD PTR [esp+0x3c]
        lea  edx,[ebp+0x68]
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [esp+0x40]
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [edx+0x8],eax
        mov  edx,DWORD PTR [esp+0x50]
        mov  eax,DWORD PTR [esp+0x54]
        lea  ecx,[ebp+0x5c]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [esp+0x58]
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [ecx+0x8],edx
        mov  ecx,DWORD PTR [esp+0x14]
        mov  edx,DWORD PTR [esp+0x18]
        lea  eax,[ebp+0x74]
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [ebp+0x98],0x8
        mov  DWORD PTR [eax+0x8],ecx
    loc_00404182:
        mov  eax,DWORD PTR [ebp+0x90]
        xor  ecx,ecx
        test  al,0x1
        jne loc_004041B3
        mov  DWORD PTR [ebp+0x84],ecx
        mov  DWORD PTR [ebp+0x80],ebx
        mov  DWORD PTR [ebp+0x88],ecx
        or   eax,0x1
        mov  DWORD PTR [ebp+0x8c],0x476f78
        mov  DWORD PTR [ebp+0x90],eax
    loc_004041B3:
        mov  DWORD PTR [ebp+0x84],ecx
        mov  DWORD PTR [ebp+0x88],ecx
        mov  DWORD PTR [ebp+0x80],0xffffffff
        jmp loc_00404251
        mov  dl,BYTE PTR [edi+0x8]
        mov  BYTE PTR [ebp+0x20],dl
        mov  eax,DWORD PTR [ebp+0x34]
        xor  ecx,ecx
        test  al,0x1
        jne loc_004041F3
        or   eax,0x1
        mov  DWORD PTR [ebp+0x28],ecx
        mov  DWORD PTR [ebp+0x24],ebx
        mov  DWORD PTR [ebp+0x2c],ecx
        mov  DWORD PTR [ebp+0x30],0x476f78
        mov  DWORD PTR [ebp+0x34],eax
    loc_004041F3:
        mov  DWORD PTR [ebp+0x28],ecx
        mov  DWORD PTR [ebp+0x2c],ecx
        mov  DWORD PTR [ebp+0x24],0xffffffff
        jmp loc_00404251
        mov  eax,DWORD PTR [edi+0x8]
        mov  ds:0x4923a8,eax
        jmp loc_00404251
        mov  eax,DWORD PTR [edi+0xc]
        test  eax,eax
        jl loc_00404231
        mov  ecx,DWORD PTR [edi+0x8]
        mov  edx,DWORD PTR [ebp+0x178]
        imul  ecx,ecx,0x3ac
        lea  esi,[ecx+ebp*1+0x180]
        push  edx
        call FUN_00404f30
        jmp loc_00404251
    loc_00404231:
        mov  eax,DWORD PTR [edi+0x8]
        imul  eax,eax,0x3ac
        mov  ecx,DWORD PTR [eax+ebp*1+0x4dc]
        lea  eax,[eax+ebp*1+0x180]
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x35c],ecx
    loc_00404251:
        mov  eax,DWORD PTR [ebp+0x4c]
        movsx ecx,WORD PTR [eax+0x6]
        add  ecx,eax
        mov  DWORD PTR [ebp+0x4c],ecx
    loc_0040425D:
        mov  edx,DWORD PTR [ebp+0x4c]
        mov  eax,DWORD PTR [edx]
        cmp  eax,DWORD PTR [ebp+0x3c]
        jle loc_00403CA4
    loc_0040426B:
        mov  edx,DWORD PTR [ebp+0x3c]
        mov  ecx,DWORD PTR [ebp+0x44]
        mov  DWORD PTR [ebp+0x38],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_004042A4
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_004042A4
        fld  DWORD PTR [ebp+0x40]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [ebp+0x3c],edx
        fstp  DWORD PTR [ebp+0x40]
        jmp loc_004042B4
    loc_004042A4:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebp+0x40]
        fst  DWORD PTR [ebp+0x40]
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x3c],eax
    loc_004042B4:
        mov  eax,DWORD PTR [ebp+0x94]
        test  eax,eax
        je loc_004042E0
        lea  eax,[ebp+0x50]
        lea  edi,[esp+0x14]
        call FUN_00404610
        mov  edx,DWORD PTR [eax]
        lea  ecx,[ebp+0x2a58]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],eax
    loc_004042E0:
        mov  eax,DWORD PTR [ebp+0xe0]
        test  eax,eax
        je loc_0040430F
        lea  eax,[ebp+0x9c]
        lea  edi,[esp+0x14]
        call FUN_00404610
        mov  edx,DWORD PTR [eax]
        lea  ecx,[ebp+0x2a4c]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],eax
    loc_0040430F:
        mov  eax,DWORD PTR [ebp+0x16c]
        test  eax,eax
        je loc_0040433B
        lea  ecx,[esp+0x80]
        push  ecx
        lea  ebx,[ebp+0xe8]
        call FUN_004049a0
        lea  edi,[ebp+0x2b48]
        mov  ecx,0x7
        mov  esi,eax
        rep movsd
    loc_0040433B:
        mov  al,BYTE PTR [ebp+0x20]
        test  al,al
        je loc_0040437F
        movzx eax,al
        dec  eax
        jne loc_0040437F
        fld  DWORD PTR [ebp+0x2c]
        lea  esi,[ebp+0x24]
        fmul  DWORD PTR ds:0x470cb0
        fsub  DWORD PTR ds:0x470b18
        fsin
        fmul  DWORD PTR ds:0x470cac
        fstp  DWORD PTR [ebp+0x2a88]
        call FUN_00404ed0
        cmp  DWORD PTR [ebp+0x28],0x200
        jl loc_0040437F
        push  0x0
        mov  eax,esi
        call FUN_00405410
    loc_0040437F:
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0x8c
        ret  0x4
        mov  edi,edi
        mov  ah,0x42
        inc  eax
        add  BYTE PTR [ebx+0x200403c],bh
        cmp  eax,0x3d730040
        inc  eax
        add  ch,dl
        cmp  eax,0x3df50040
        inc  eax
        add  BYTE PTR [ecx+0x3e],dl
        inc  eax
        add  BYTE PTR [ecx+0x3e],dh
        inc  eax
        add  BYTE PTR [edi+0x3e],bh
        inc  eax
        add  bh,ch
        ds inc eax
        add  dl,cl
        aas
        inc  eax
        add  dl,dl
        inc  eax
        inc  eax
        add  dh,cl
        inc  ecx
        inc  eax
        add  BYTE PTR [edx],al
        inc  edx
        inc  eax
        add  BYTE PTR [edx+eax*2],cl
        inc  eax
        add  ah,cl
        int3
        int3
        int3
        mov  DWORD PTR [edx+0x1eec],0x1
        push  esi
        push  edi
        mov  edi,DWORD PTR [ecx]
        lea  esi,[edx+0x1ef0]
        mov  DWORD PTR [esi],edi
        mov  edi,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [esi+0x4],edi
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esi+0x8],ecx
        mov  ecx,DWORD PTR [eax]
        add  edx,0x1efc
        mov  DWORD PTR [edx],ecx
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [edx+0x4],ecx
        mov  eax,DWORD PTR [eax+0x8]
        pop  edi
        mov  DWORD PTR [edx+0x8],eax
        pop  esi
        ret
    }
}

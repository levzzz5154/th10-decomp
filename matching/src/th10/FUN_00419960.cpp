// 00419960: FUN_00419960
// Original size: 1504 bytes, actual code: 465 instructions
extern "C" void FUN_00418d00(void);
extern "C" void FUN_00419040(void);
extern "C" void FUN_004198c0(void);
extern "C" void FUN_00419f40(void);
extern "C" void FUN_0041a050(void);
extern "C" void FUN_0041a0a0(void);
extern "C" void FUN_0041ab10(void);
extern "C" void FUN_0044b360(void);
extern "C" void _free(void);
extern "C" void operator_new(void);
extern "C" void _malloc(void);
extern "C" void FUN_00452730(void);
extern "C" void _atol(void);
extern "C" void _strrchr(void);
extern "C" void _strncpy(void);
extern "C" void _atof(void);

extern "C" __declspec(naked) void FUN_00419960(void) {
    __asm {
        sub  esp,0x24
        push  esi
        push  0x1
        lea  eax,[esp+0x34]
        push  eax
        mov  eax,DWORD PTR [esp+0x38]
        mov  DWORD PTR [esp+0xc],0xffffffff
        mov  DWORD PTR [esp+0x10],0x0
        call FUN_0044b360
        mov  esi,eax
        test  esi,esi
        mov  DWORD PTR [esp+0x18],esi
        jne loc_00419998
        or   eax,0xffffffff
        pop  esi
        add  esp,0x24
        ret  0xc
    loc_00419998:
        push  ebx
        push  ebp
        push  edi
        push  0x1000
        call _malloc
        mov  edi,eax
        push  0x1000
        mov  DWORD PTR [esp+0x24],edi
        call _malloc
        mov  ebp,eax
        push  0x1000
        mov  DWORD PTR [esp+0x24],ebp
        call _malloc
        mov  ecx,DWORD PTR [esp+0x48]
        add  esp,0xc
        test  ecx,ecx
        mov  ebx,eax
        mov  eax,esi
        jle loc_00419ACB
        mov  esi,edi
        sub  esi,ebp
        mov  ecx,ebp
        sub  ecx,edi
        mov  DWORD PTR [esp+0x28],esi
        mov  DWORD PTR [esp+0x2c],ecx
        jmp loc_004199F2
    loc_004199EA:
        mov  eax,DWORD PTR [esp+0x20]
        mov  esi,DWORD PTR [esp+0x28]
    loc_004199F2:
        push  0x1000
        lea  ecx,[esp+0x40]
        push  ecx
        push  edi
        call FUN_00419f40
        mov  DWORD PTR [esp+0x20],eax
        mov  eax,ebp
    loc_00419A08:
        mov  cl,BYTE PTR [esi+eax*1]
        mov  BYTE PTR [eax],cl
        inc  eax
        test  cl,cl
        jne loc_00419A08
        push  0x3a
        push  ebp
        call FUN_00452730
        add  esp,0x8
        test  eax,eax
        jne loc_00419A25
        mov  eax,ebp
        jmp loc_00419A45
    loc_00419A25:
        lea  ecx,[eax+0x1]
        mov  esi,ebx
        sub  esi,ecx
        nop
    loc_00419A30:
        mov  dl,BYTE PTR [ecx]
        mov  BYTE PTR [esi+ecx*1],dl
        inc  ecx
        test  dl,dl
        jne loc_00419A30
        mov  BYTE PTR [eax],dl
        mov  eax,ebp
        call FUN_0041a0a0
        mov  eax,ebx
    loc_00419A45:
        call FUN_0041a0a0
        mov  eax,edi
        nop
    loc_00419A50:
        mov  cl,BYTE PTR [eax]
        mov  edx,DWORD PTR [esp+0x2c]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_00419A50
        push  0x3a
        push  ebp
        call FUN_00452730
        add  esp,0x8
        test  eax,eax
        jne loc_00419A71
        mov  eax,ebp
        jmp loc_00419A8D
    loc_00419A71:
        lea  ecx,[eax+0x1]
        mov  esi,ebx
        sub  esi,ecx
    loc_00419A78:
        mov  dl,BYTE PTR [ecx]
        mov  BYTE PTR [esi+ecx*1],dl
        inc  ecx
        test  dl,dl
        jne loc_00419A78
        mov  BYTE PTR [eax],dl
        mov  eax,ebp
        call FUN_0041a0a0
        mov  eax,ebx
    loc_00419A8D:
        call FUN_0041a0a0
        mov  edi,0x46d658
        mov  esi,ebp
        mov  ecx,0x8
        xor  eax,eax
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419AF2
        mov  edi,0x46d654
        mov  esi,ebx
        mov  ecx,0x4
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        je loc_00419F25
        mov  eax,DWORD PTR [esp+0x38]
        call FUN_00419040
        mov  edi,DWORD PTR [esp+0x1c]
    loc_00419AC7:
        mov  esi,DWORD PTR [esp+0x24]
    loc_00419ACB:
        push  edi
        call _free
        push  ebp
        call _free
        push  ebx
        call _free
        push  esi
        call _free
        add  esp,0x10
        pop  edi
        pop  ebp
        pop  ebx
        xor  eax,eax
        pop  esi
        add  esp,0x24
        ret  0xc
    loc_00419AF2:
        mov  edi,0x46d64c
        mov  esi,ebp
        mov  ecx,0x6
        xor  eax,eax
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419B33
        push  ebx
        call _atol
        add  esp,0x4
        test  eax,eax
        mov  DWORD PTR [esp+0x10],eax
        mov  DWORD PTR [esp+0x14],0x0
        jle loc_00419B26
        cmp  eax,0x8
        jl loc_00419F25
    loc_00419B26:
        mov  DWORD PTR [esp+0x10],0xffffffff
        jmp loc_00419F25
    loc_00419B33:
        mov  edi,0x46d640
        mov  esi,ebp
        mov  ecx,0x9
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419B52
        mov  DWORD PTR [esp+0x10],0xffffffff
        jmp loc_00419F25
    loc_00419B52:
        mov  edi,0x46d638
        mov  esi,ebp
        mov  ecx,0x5
        xor  eax,eax
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419F25
        mov  eax,DWORD PTR [esp+0x10]
        test  eax,eax
        jle loc_00419F25
        cmp  DWORD PTR [esp+0x14],0xff
        jl loc_00419B8B
        mov  DWORD PTR [esp+0x10],0xffffffff
        jmp loc_00419F25
    loc_00419B8B:
        push  0x88
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_00419BA7
        mov  edx,eax
        call FUN_00418d00
        mov  ebp,eax
        jmp loc_00419BA9
    loc_00419BA7:
        xor  ebp,ebp
    loc_00419BA9:
        mov  ecx,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x3c]
        inc  ecx
        test  eax,eax
        mov  DWORD PTR [esp+0x14],ecx
        mov  DWORD PTR [ebp+0x18],0x0
        jle loc_00419E83
        jmp loc_00419BD0
        nop
        mov  edi,edi
    loc_00419BD0:
        mov  esi,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x20]
        push  0x1000
        lea  ecx,[esp+0x40]
        push  ecx
        push  esi
        call FUN_00419f40
        mov  DWORD PTR [esp+0x20],eax
        mov  eax,esi
        mov  esi,DWORD PTR [esp+0x18]
        mov  edi,esi
        call FUN_0041a050
        mov  edi,0x46d610
        mov  ecx,0x4
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419C5A
        push  0x2c
        push  ebx
        call FUN_00452730
        mov  esi,eax
        add  esp,0x8
        test  esi,esi
        je loc_00419E77
        mov  BYTE PTR [esi],0x0
        mov  eax,ebx
        inc  esi
        call FUN_0041a0a0
        mov  eax,esi
        call FUN_0041a0a0
        push  ebx
        call _atol
        mov  DWORD PTR [esp+0x34],eax
        fild  DWORD PTR [esp+0x34]
        push  esi
        fstp  DWORD PTR [ebp+0x0]
        call _atol
        mov  DWORD PTR [esp+0x38],eax
        fild  DWORD PTR [esp+0x38]
        add  esp,0x8
        fstp  DWORD PTR [ebp+0x4]
        jmp loc_00419E77
    loc_00419C5A:
        mov  eax,DWORD PTR [esp+0x18]
        mov  edi,0x46d608
        mov  esi,eax
        mov  ecx,0x5
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419CB0
        push  0x22
        push  ebx
        call FUN_00452730
        mov  esi,eax
        add  esp,0x8
        test  esi,esi
        je loc_00419E77
        inc  esi
        push  0x22
        push  esi
        call _strrchr
        add  esp,0x8
        test  eax,eax
        je loc_00419E83
        push  0x41
        mov  BYTE PTR [eax],0x0
        lea  eax,[ebp+0x1c]
        push  esi
        push  eax
        call _strncpy
        add  esp,0xc
        jmp loc_00419E77
    loc_00419CB0:
        mov  edi,0x46d600
        mov  esi,eax
        mov  ecx,0x6
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419CD3
        push  ebx
        call _atol
        add  esp,0x4
        mov  DWORD PTR [ebp+0x60],eax
        jmp loc_00419E77
    loc_00419CD3:
        mov  edi,0x46d5f8
        mov  esi,eax
        mov  ecx,0x5
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419CF6
        push  ebx
        call _atol
        add  esp,0x4
        mov  DWORD PTR [ebp+0x6c],eax
        jmp loc_00419E77
    loc_00419CF6:
        mov  edi,0x46d5f0
        mov  esi,eax
        mov  ecx,0x5
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419D1E
        push  0x3d
        push  0x4744b0
        mov  edx,ebx
        call FUN_004198c0
        mov  DWORD PTR [ebp+0x68],eax
        jmp loc_00419E77
    loc_00419D1E:
        mov  edi,0x46d5e8
        mov  esi,eax
        mov  ecx,0x6
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419D46
        push  0x3
        push  0x474494
        mov  edx,ebx
        call FUN_004198c0
        mov  DWORD PTR [ebp+0x64],eax
        jmp loc_00419E77
    loc_00419D46:
        mov  edi,0x46d5e0
        mov  esi,eax
        mov  ecx,0x7
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419D69
        push  ebx
        call _atol
        add  esp,0x4
        mov  DWORD PTR [ebp+0x70],eax
        jmp loc_00419E77
    loc_00419D69:
        mov  edi,0x46d5d8
        mov  esi,eax
        mov  ecx,0x6
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419DBF
        push  ebx
        call _atof
        fcom  DWORD PTR ds:0x470c40
        add  esp,0x4
        fst  DWORD PTR [ebp+0x7c]
        fnstsw ax
        test  ah,0x41
        jne loc_00419DA2
        fstp  st(0)
        mov  DWORD PTR [ebp+0x7c],0x40800000
        jmp loc_00419E77
    loc_00419DA2:
        fcomp DWORD PTR ds:0x470c60
        fnstsw ax
        test  ah,0x5
        jp loc_00419E77
        mov  DWORD PTR [ebp+0x7c],0xc0800000
        jmp loc_00419E77
    loc_00419DBF:
        mov  edi,0x46d5d0
        mov  esi,eax
        mov  ecx,0x6
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419E42
        push  0x2c
        push  ebx
        call FUN_00452730
        mov  esi,eax
        add  esp,0x8
        test  esi,esi
        je loc_00419E77
        mov  BYTE PTR [esi],0x0
        mov  eax,ebx
        inc  esi
        call FUN_0041a0a0
        push  ebx
        call _atol
        push  0x2c
        push  esi
        mov  BYTE PTR [ebp+0x86],al
        mov  edi,esi
        call FUN_00452730
        mov  esi,eax
        add  esp,0xc
        test  esi,esi
        je loc_00419E77
        mov  eax,edi
        mov  BYTE PTR [esi],0x0
        call FUN_0041a0a0
        push  edi
        call _atol
        mov  BYTE PTR [ebp+0x85],al
        add  esp,0x4
        lea  eax,[esi+0x1]
        call FUN_0041a0a0
        push  eax
        call _atol
        add  esp,0x4
        mov  BYTE PTR [ebp+0x84],al
        jmp loc_00419E77
    loc_00419E42:
        mov  edi,0x46d5c8
        mov  esi,eax
        mov  ecx,0x6
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00419E65
        push  ebx
        call _atol
        add  esp,0x4
        mov  BYTE PTR [ebp+0x87],al
        jmp loc_00419E77
    loc_00419E65:
        mov  esi,eax
        mov  edi,0x46d5c4
        mov  ecx,0x4
        xor  eax,eax
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        je loc_00419E83
    loc_00419E77:
        mov  eax,DWORD PTR [esp+0x3c]
        test  eax,eax
        jg loc_00419BD0
    loc_00419E83:
        lea  eax,[ebp+0x1c]
        lea  edx,[eax+0x1]
        nop
    loc_00419E90:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00419E90
        sub  eax,edx
        test  eax,eax
        mov  DWORD PTR [esp+0x30],eax
        fild  DWORD PTR [esp+0x30]
        jge loc_00419EAB
        fadd  DWORD PTR ds:0x470b98
    loc_00419EAB:
        fmul  DWORD PTR [ebp+0x7c]
        mov  eax,DWORD PTR [esp+0x10]
        lea  ecx,[eax+eax*2+0x6]
        mov  eax,DWORD PTR [esp+0x38]
        fmul  DWORD PTR ds:0x470c5c
        lea  edx,[ebp+0xc]
        lea  eax,[eax+ecx*4]
        fstp  DWORD PTR [ebp+0x80]
        call FUN_0041ab10
        mov  eax,DWORD PTR [esp+0x40]
        test  eax,eax
        jne loc_00419F21
        push  0x88
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_00419EF3
        mov  edx,eax
        call FUN_00418d00
        jmp loc_00419EF5
    loc_00419EF3:
        xor  eax,eax
    loc_00419EF5:
        lea  edx,[eax+0xc]
        mov  edi,eax
        mov  ecx,0x22
        mov  esi,ebp
        rep movsd
        mov  DWORD PTR [edx],eax
        xor  eax,eax
        mov  DWORD PTR [edx+0x4],eax
        mov  DWORD PTR [edx+0x8],eax
        mov  eax,DWORD PTR [esp+0x10]
        lea  ecx,[eax+eax*2+0x1e]
        mov  eax,DWORD PTR [esp+0x38]
        lea  eax,[eax+ecx*4]
        call FUN_0041ab10
    loc_00419F21:
        mov  ebp,DWORD PTR [esp+0x18]
    loc_00419F25:
        mov  eax,DWORD PTR [esp+0x3c]
        test  eax,eax
        mov  edi,DWORD PTR [esp+0x1c]
        jg loc_004199EA
        jmp loc_00419AC7
    }
}

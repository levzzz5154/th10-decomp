// 00429B60: FUN_00429b60
// Original size: 1696 bytes, actual code: 535 instructions
extern "C" void FUN_004359b0(void);
extern "C" void FUN_0044b220(void);
extern "C" void FUN_0044b620(void);
extern "C" void _free(void);
extern "C" void _malloc(void);
extern "C" void FUN_00452abc(void);
extern "C" void _sprintf(void);
extern "C" void _localtime(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00429b60(void) {
    __asm {
        sub  esp,0x124
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        push  ebp
        push  esi
        mov  DWORD PTR [esp+0x12c],eax
        mov  eax,DWORD PTR [esp+0x134]
        push  edi
        mov  edi,ecx
        xor  ebp,ebp
        mov  esi,edx
        mov  edx,DWORD PTR [edi+0x18]
        mov  DWORD PTR [esp+0x28],edi
        mov  DWORD PTR [esp+0x24],ebp
        mov  DWORD PTR [esp+0x1c],ebp
        mov  ecx,eax
    loc_00429B96:
        mov  bl,BYTE PTR [ecx]
        inc  ecx
        mov  BYTE PTR [edx],bl
        inc  edx
        test  bl,bl
        jne loc_00429B96
        lea  edx,[eax+0x1]
    loc_00429BA3:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00429BA3
        sub  eax,edx
        cmp  eax,0x8
        jge loc_00429BBE
    loc_00429BB1:
        mov  ecx,DWORD PTR [edi+0x18]
        mov  BYTE PTR [eax+ecx*1],0x20
        inc  eax
        cmp  eax,0x8
        jl loc_00429BB1
    loc_00429BBE:
        push  0x46e650
        call FUN_00452abc
        push  esi
        lea  edx,[esp+0x38]
        push  0x46e644
        push  edx
        call _sprintf
        add  esp,0x10
        xor  eax,eax
        lea  ecx,[edi+0x40]
        mov  DWORD PTR [esp+0x14],ebp
        mov  ebx,0x64
        mov  DWORD PTR [esp+0x20],eax
        lea  ebp,[edi+0x1c]
        mov  DWORD PTR [esp+0x10],ecx
    loc_00429BF4:
        mov  ecx,DWORD PTR [ebp+0x0]
        test  ecx,ecx
        je loc_00429CC6
        mov  edx,DWORD PTR [esp+0x24]
        test  edx,edx
        jne loc_00429C0B
        mov  DWORD PTR [esp+0x24],eax
    loc_00429C0B:
        mov  DWORD PTR [ecx+0x8],0x0
        mov  ecx,DWORD PTR [esp+0x10]
        mov  esi,DWORD PTR [ecx]
        add  ebx,0x1c4
        test  esi,esi
        mov  DWORD PTR [esp+0x1c],eax
        je loc_00429CC2
        lea  ebx,[ebx+0x0]
    loc_00429C30:
        mov  ecx,DWORD PTR [esi]
        mov  edx,DWORD PTR [ecx+0x5460]
        sub  edx,ecx
        mov  eax,0x2aaaaaab
        imul  edx
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        lea  edx,[eax+eax*2]
        mov  eax,DWORD PTR [ecx+0x6274]
        lea  edx,[eax+edx*2]
        sub  edx,ecx
        mov  edi,DWORD PTR [ebp+0x0]
        lea  ebx,[ebx+edx*1-0x5464]
        mov  edx,DWORD PTR [ecx+0x5460]
        sub  edx,ecx
        mov  eax,0x2aaaaaab
        imul  edx
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  edx,DWORD PTR [ecx+0x6274]
        lea  eax,[eax+eax*2]
        lea  eax,[edx+eax*2]
        sub  eax,ecx
        mov  ecx,DWORD PTR [edi+0x8]
        sub  eax,0x5464
        add  ecx,eax
        mov  DWORD PTR [edi+0x8],ecx
        mov  eax,DWORD PTR [esi]
        mov  ecx,DWORD PTR [eax+0x5460]
        mov  edi,DWORD PTR [ebp+0x0]
        sub  ecx,eax
        mov  eax,0x2aaaaaab
        imul  ecx
        mov  ecx,edx
        shr  ecx,0x1f
        add  ecx,edx
        add  DWORD PTR [edi+0x4],ecx
        mov  esi,DWORD PTR [esi+0x4]
        test  esi,esi
        jne loc_00429C30
        mov  eax,DWORD PTR [esp+0x20]
        mov  edi,DWORD PTR [esp+0x28]
    loc_00429CC2:
        inc  DWORD PTR [esp+0x14]
    loc_00429CC6:
        mov  edx,DWORD PTR [esp+0x10]
        inc  eax
        add  edx,0xc
        add  ebp,0x4
        cmp  eax,0x8
        mov  DWORD PTR [esp+0x20],eax
        mov  DWORD PTR [esp+0x10],edx
        jl loc_00429BF4
        mov  edx,DWORD PTR [edi+0x18]
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [edx+0x4c],eax
        mov  ecx,DWORD PTR [edi+0x18]
        mov  edx,DWORD PTR ds:0x474c44
        mov  eax,ds:0x477708
        mov  DWORD PTR [ecx+0x10],edx
        fld  QWORD PTR [eax+0x24]
        fdiv  QWORD PTR [eax+0x2c]
        mov  eax,DWORD PTR [edi+0x18]
        push  ebx
        fmul  DWORD PTR ds:0x470b44
        fsubr DWORD PTR ds:0x470b44
        fstp  DWORD PTR [eax+0x48]
        call _malloc
        mov  esi,DWORD PTR [edi+0x18]
        mov  ebp,eax
        mov  ecx,0x19
        mov  edi,ebp
        rep movsd
        mov  ecx,DWORD PTR [esp+0x2c]
        lea  eax,[ecx+0x40]
        mov  DWORD PTR [esp+0x14],eax
        lea  eax,[ecx+0x1c]
        add  esp,0x4
        mov  DWORD PTR [esp+0x14],ebp
        mov  ebx,0x64
        mov  DWORD PTR [esp+0x2c],eax
        mov  DWORD PTR [esp+0x18],0x8
        nop
    loc_00429D50:
        mov  esi,DWORD PTR [eax]
        test  esi,esi
        je loc_00429E31
        lea  edi,[ebx+ebp*1]
        mov  ecx,0x71
        rep movsd
        mov  ecx,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ecx]
        add  ebx,0x1c4
        test  eax,eax
        mov  DWORD PTR [esp+0x20],eax
        je loc_00429DE3
        jmp loc_00429D80
    loc_00429D7A:
        mov  eax,DWORD PTR [esp+0x20]
        mov  edi,edi
    loc_00429D80:
        mov  ebp,DWORD PTR [eax]
        mov  ecx,DWORD PTR [ebp+0x5460]
        sub  ecx,ebp
        mov  eax,0x2aaaaaab
        imul  ecx
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  edx,DWORD PTR [esp+0x14]
        lea  ecx,[eax+eax*2]
        shl  ecx,1
        mov  eax,ecx
        shr  ecx,0x2
        lea  edi,[edx+ebx*1]
        mov  esi,ebp
        rep movsd
        mov  ecx,eax
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [ebp+0x5460]
        sub  ecx,ebp
        mov  eax,0x2aaaaaab
        imul  ecx
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  edx,DWORD PTR [esp+0x20]
        lea  ecx,[eax+eax*2]
        mov  eax,DWORD PTR [edx+0x4]
        test  eax,eax
        lea  ebx,[ebx+ecx*2]
        mov  DWORD PTR [esp+0x20],eax
        jne loc_00429D7A
        mov  ebp,DWORD PTR [esp+0x14]
    loc_00429DE3:
        mov  eax,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [eax]
        test  edx,edx
        je loc_00429E31
        nop
    loc_00429DF0:
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [eax+0x6274]
        sub  ecx,eax
        sub  ecx,0x5464
        lea  edi,[ebx+ebp*1]
        mov  ebp,ecx
        shr  ecx,0x2
        lea  esi,[eax+0x5464]
        rep movsd
        mov  ecx,ebp
        mov  ebp,DWORD PTR [esp+0x14]
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [eax+0x6274]
        mov  edx,DWORD PTR [edx+0x4]
        sub  ecx,eax
        test  edx,edx
        lea  ebx,[ebx+ecx*1-0x5464]
        jne loc_00429DF0
    loc_00429E31:
        mov  eax,DWORD PTR [esp+0x2c]
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0x18]
        add  eax,0x4
        add  edx,0xc
        dec  ecx
        mov  DWORD PTR [esp+0x2c],eax
        mov  DWORD PTR [esp+0x10],edx
        mov  DWORD PTR [esp+0x18],ecx
        jne loc_00429D50
        lea  edx,[esp+0x18]
        push  edx
        push  ebx
        push  ebp
        call FUN_004359b0
        push  ebp
        mov  edi,eax
        call _free
        mov  esi,DWORD PTR [esp+0x1c]
        add  esp,0x4
        push  esi
        push  0x80
        push  0x7a
        push  esi
        push  edi
        mov  al,0x3d
        call FUN_0044b220
        push  esi
        push  0x400
        push  0xe1
        push  esi
        push  edi
        mov  al,0xaa
        call FUN_0044b220
        mov  ebp,DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [ebp+0x14]
        mov  DWORD PTR [eax+0x20],ebx
        mov  ecx,DWORD PTR [ebp+0x14]
        mov  DWORD PTR [ecx+0x1c],esi
        mov  eax,DWORD PTR [ebp+0x14]
        mov  edx,DWORD PTR [eax+0x1c]
        add  edx,0x24
        mov  DWORD PTR [eax+0xc],edx
        lea  eax,[esp+0x30]
        push  eax
        call FUN_0044b620
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_00429F3A
        mov  edx,DWORD PTR [ebp+0x14]
        mov  ebx,DWORD PTR ds:0x4660d4
        push  0x0
        lea  ecx,[esp+0x1c]
        push  ecx
        push  0x24
        push  edx
        push  eax
        call  ebx
        cmp  DWORD PTR [esp+0x18],0x24
        je loc_00429F00
        mov  eax,ds:0x474c38
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_00429F00:
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_00429F3A
        push  0x0
        lea  ecx,[esp+0x1c]
        push  ecx
        push  esi
        push  edi
        push  eax
        call  ebx
        cmp  esi,DWORD PTR [esp+0x18]
        je loc_00429F3A
        mov  edx,DWORD PTR ds:0x474c38
        push  edx
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_00429F3A:
        test  edi,edi
        je loc_00429F47
        push  edi
        call _free
        add  esp,0x4
    loc_00429F47:
        push  0xffff
        call _malloc
        mov  ebx,eax
        xor  eax,eax
        mov  ecx,0x3fff
        mov  edi,ebx
        rep stosd
        stos  WORD PTR es:[edi],ax
        stos  BYTE PTR es:[edi],al
        lea  esi,[ebx+0xc]
        push  0x46e5e0
        push  esi
        mov  DWORD PTR [ebx],0x52455355
        mov  BYTE PTR [ebx+0x8],0x0
        call _sprintf
        push  0x46e5d8
        add  esi,eax
        push  0x46e5c8
        push  esi
        call _sprintf
        add  esi,eax
        mov  eax,DWORD PTR [ebp+0x18]
        push  eax
        push  0x46e5bc
        push  esi
        call _sprintf
        mov  ecx,DWORD PTR [ebp+0x18]
        add  ecx,0xc
        push  ecx
        add  esi,eax
        call _localtime
        mov  edx,DWORD PTR [eax+0x4]
        mov  ecx,DWORD PTR [eax+0x8]
        push  edx
        mov  edx,DWORD PTR [eax+0xc]
        push  ecx
        mov  ecx,DWORD PTR [eax+0x10]
        mov  eax,DWORD PTR [eax+0x14]
        push  edx
        inc  ecx
        push  ecx
        cdq
        mov  ecx,0x64
        idiv  ecx
        push  edx
        push  0x46e59c
        push  esi
        call _sprintf
        add  esi,eax
        mov  eax,DWORD PTR [ebp+0x18]
        mov  ecx,DWORD PTR [eax+0x50]
        mov  edi,DWORD PTR [eax+0x54]
        lea  edx,[ecx+ecx*2]
        add  edx,edi
        mov  eax,DWORD PTR [edx*4+0x4746dc]
        add  esp,0x44
        push  eax
        push  0x46e590
        push  esi
        call _sprintf
        mov  ecx,DWORD PTR [ebp+0x18]
        mov  edx,DWORD PTR [ecx+0x58]
        add  esi,eax
        mov  eax,DWORD PTR [edx*4+0x4746f4]
        push  eax
        push  0x46e584
        push  esi
        call _sprintf
        mov  edx,DWORD PTR [ebp+0x18]
        add  esi,eax
        mov  eax,DWORD PTR [edx+0x5c]
        mov  ecx,0x7
        add  esp,0x18
        cmp  eax,ecx
        jle loc_0042A04D
        cmp  DWORD PTR [esp+0x24],ecx
        jne loc_0042A03D
        push  0x46e570
        push  esi
        call _sprintf
        add  esp,0x8
        jmp loc_0042A08E
    loc_0042A03D:
        push  0x46e55c
        push  esi
        call _sprintf
        add  esp,0x8
        jmp loc_0042A08E
    loc_0042A04D:
        mov  eax,DWORD PTR [esp+0x24]
        mov  edx,DWORD PTR [esp+0x1c]
        cmp  eax,edx
        jne loc_0042A07E
        cmp  eax,ecx
        jne loc_0042A06D
        push  0x46e54c
        push  esi
        call _sprintf
        add  esp,0x8
        jmp loc_0042A08E
    loc_0042A06D:
        push  eax
        push  0x46e540
        push  esi
        call _sprintf
        add  esp,0xc
        jmp loc_0042A08E
    loc_0042A07E:
        push  edx
        push  eax
        push  0x46e52c
        push  esi
        call _sprintf
        add  esp,0x10
    loc_0042A08E:
        add  esi,eax
        mov  eax,DWORD PTR [ebp+0x18]
        mov  ecx,DWORD PTR [eax+0x10]
        push  ecx
        push  0x46e520
        push  esi
        call _sprintf
        mov  edx,DWORD PTR [ebp+0x18]
        fld  DWORD PTR [edx+0x48]
        add  esp,0x4
        fstp  QWORD PTR [esp]
        add  esi,eax
        push  0x46e50c
        push  esi
        call _sprintf
        lea  esi,[esi+eax*1+0x1]
        mov  eax,esi
        sub  eax,ebx
        add  esp,0x10
        and  eax,0x80000003
        jns loc_0042A0D2
        dec  eax
        or   eax,0xfffffffc
        inc  eax
    loc_0042A0D2:
        je loc_0042A0DD
        mov  ecx,0x4
        sub  ecx,eax
        add  esi,ecx
    loc_0042A0DD:
        mov  eax,ds:0x474c38
        sub  esi,ebx
        cmp  eax,0xffffffff
        mov  DWORD PTR [ebx+0x4],esi
        je loc_0042A11F
        push  0x0
        lea  edx,[esp+0x20]
        push  edx
        push  esi
        push  ebx
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x1c]
        je loc_0042A11F
        mov  eax,ds:0x474c38
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0042A11F:
        xor  eax,eax
        mov  ecx,0x3fff
        mov  edi,ebx
        rep stosd
        stos  WORD PTR es:[edi],ax
        stos  BYTE PTR es:[edi],al
        push  0x46e4f8
        lea  esi,[ebx+0xc]
        push  esi
        mov  DWORD PTR [ebx],0x52455355
        mov  BYTE PTR [ebx+0x8],0x1
        call _sprintf
        lea  esi,[esi+eax*1+0x1]
        mov  eax,esi
        sub  eax,ebx
        add  esp,0x8
        and  eax,0x80000003
        jns loc_0042A15C
        dec  eax
        or   eax,0xfffffffc
        inc  eax
    loc_0042A15C:
        je loc_0042A167
        mov  ecx,0x4
        sub  ecx,eax
        add  esi,ecx
    loc_0042A167:
        mov  eax,ds:0x474c38
        sub  esi,ebx
        cmp  eax,0xffffffff
        mov  DWORD PTR [ebx+0x4],esi
        je loc_0042A1A9
        push  0x0
        lea  edx,[esp+0x20]
        push  edx
        push  esi
        push  ebx
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp+0x1c]
        je loc_0042A1A9
        mov  eax,ds:0x474c38
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0042A1A9:
        push  ebx
        call _free
        mov  eax,ds:0x474c38
        add  esp,0x4
        cmp  eax,0xffffffff
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        je loc_0042A1D8
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0042A1D8:
        mov  ecx,DWORD PTR [esp+0x120]
        xor  ecx,esp
        xor  eax,eax
        call __security_check_cookie
        add  esp,0x124
        ret  0x4
    }
}

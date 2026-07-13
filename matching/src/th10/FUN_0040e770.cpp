// 0040E770: FUN_0040e770
// Original size: 16304 bytes, actual code: 4735 instructions
extern "C" void FUN_00401d20(void);
extern "C" void FUN_004050d0(void);
extern "C" void FUN_00405410(void);
extern "C" void FUN_004073e0(void);
extern "C" void FUN_00408100(void);
extern "C" void FUN_00408210(void);
extern "C" void FUN_00409280(void);
extern "C" void FUN_00409c00(void);
extern "C" void FUN_0040c9a0(void);
extern "C" void FUN_0040cea0(void);
extern "C" void FUN_0040cf40(void);
extern "C" void FUN_0040cf60(void);
extern "C" void FUN_0040cf90(void);
extern "C" void FUN_0040cfb0(void);
extern "C" void FUN_0040e6a0(void);
extern "C" void FUN_00412720(void);
extern "C" void FUN_00412a00(void);
extern "C" void FUN_00412a10(void);
extern "C" void FUN_00412aa0(void);
extern "C" void FUN_00412db0(void);
extern "C" void FUN_00412ed0(void);
extern "C" void FUN_00413170(void);
extern "C" void FUN_00415db0(void);
extern "C" void FUN_00418810(void);
extern "C" void FUN_0041c510(void);
extern "C" void FUN_0041c7d0(void);
extern "C" void FUN_0041c800(void);
extern "C" void FUN_0041c850(void);
extern "C" void FUN_00426660(void);
extern "C" void FUN_0043c8b0(void);
extern "C" void FUN_0043dd10(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_00448e30(void);
extern "C" void FUN_00449450(void);
extern "C" void FUN_00449590(void);
extern "C" void FUN_004495e0(void);
extern "C" void FUN_00449630(void);
extern "C" void FUN_0044b9e0(void);
extern "C" void FUN_0044bb20(void);
extern "C" void FUN_0044bb90(void);
extern "C" void FUN_0044bc70(void);
extern "C" void FUN_0044fdb0(void);
extern "C" void FUN_0044fe40(void);
extern "C" void FUN_0044ff00(void);
extern "C" void FUN_00450070(void);
extern "C" void D3DXVec3Project(void);
extern "C" void __security_check_cookie(void);
extern "C" void FUN_00463b2c(void);
extern "C" void FUN_EA171DAE(void);

extern "C" __declspec(naked) void FUN_0040e770(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        sub  esp,0x2c4
        mov  eax,ds:0x473660
        xor  eax,ebp
        push  ebx
        mov  ebx,ecx
        mov  edx,DWORD PTR [ebx+0x14d8]
        mov  DWORD PTR [esp+0x2c4],eax
        mov  eax,DWORD PTR [edx+0x4]
        push  esi
        mov  esi,DWORD PTR [eax+0x4]
        xor  eax,eax
        mov  ax,WORD PTR [esi+0x4]
        movsx ecx,ax
        add  ecx,0xffffff00
        cmp  ecx,0xb4
        push  edi
        mov  DWORD PTR [esp+0x30],ebx
        mov  DWORD PTR [esp+0x1c],esi
        mov  DWORD PTR [esp+0x10],eax
        ja loc_00411D18
        movzx ecx,BYTE PTR [ecx+0x411ee0]
        jmp  DWORD PTR [ecx*4+0x411d30]
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x10]
        test  eax,eax
        jne loc_00411D18
        mov  eax,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [eax+0x10]
        add  eax,0x4
        cdq
        and  edx,0x3
        add  eax,edx
        mov  esi,eax
        xor  eax,eax
        mov  ecx,0x10
        lea  edi,[esp+0x248]
        rep stosd
        mov  eax,DWORD PTR [ebx+0x1444]
        mov  edi,DWORD PTR [esp+0x1c]
        sar  esi,0x2
        test  eax,0x40000
        mov  DWORD PTR [esp+0x18],esi
        jne loc_0040E859
        mov  edx,DWORD PTR [edi+esi*4+0x10]
        mov  ecx,DWORD PTR [ebx+0x2c]
        push  edx
        push  0x1
        mov  eax,ebx
        mov  DWORD PTR [esp+0x18],ecx
        call FUN_00412aa0
        fadd  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x30]
        mov  DWORD PTR [esp+0x10],eax
        fstp  DWORD PTR [esp+0x248]
        mov  ecx,DWORD PTR [edi+esi*4+0x14]
        push  ecx
        push  0x2
        mov  eax,ebx
        call FUN_00412aa0
        fadd  DWORD PTR [esp+0x10]
        jmp loc_0040E8FC
    loc_0040E859:
        mov  eax,DWORD PTR [edi+esi*4+0x10]
        mov  edx,DWORD PTR [ebx+0x2c]
        push  eax
        push  0x1
        mov  eax,ebx
        mov  DWORD PTR [esp+0x18],edx
        call FUN_00412aa0
        fadd  DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [edi+esi*4+0x14]
        mov  ecx,DWORD PTR [ebx+0x30]
        push  edx
        fstp  DWORD PTR [esp+0x28]
        push  0x2
        mov  eax,ebx
        mov  DWORD PTR [esp+0x18],ecx
        call FUN_00412aa0
        fadd  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x34]
        xor  ebx,ebx
        mov  esi,0x491c28
        fstp  DWORD PTR [esp+0x28]
        mov  DWORD PTR [esp+0x2c],eax
        call FUN_00401d20
        push  0x474df0
        push  0x491dc8
        push  0x491e08
        push  0x491e48
        lea  ecx,[esp+0x34]
        push  ecx
        lea  edx,[esp+0x25c]
        push  edx
        call D3DXVec3Project
        fld  DWORD PTR [esp+0x248]
        fsub  DWORD PTR ds:0x470b4c
        mov  esi,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x250],ebx
        mov  ebx,DWORD PTR [esp+0x30]
        fstp  DWORD PTR [esp+0x248]
        fld  DWORD PTR [esp+0x24c]
        fsub  DWORD PTR ds:0x470b48
    loc_0040E8FC:
        mov  edi,DWORD PTR [esp+0x1c]
    loc_0040E900:
        mov  ecx,DWORD PTR [ebx+0x14d8]
        fstp  DWORD PTR [esp+0x24c]
        mov  eax,DWORD PTR [edi+esi*4+0x18]
        mov  edx,DWORD PTR [ecx+0x4]
        push  eax
        push  0x3
        call FUN_0044ff00
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  DWORD PTR [esp+0x25c],eax
        mov  eax,DWORD PTR [edi+esi*4+0x1c]
        mov  edx,DWORD PTR [ecx+0x4]
        push  eax
        push  0x4
        call FUN_0044ff00
        mov  DWORD PTR [esp+0x254],eax
        mov  esi,DWORD PTR [edi+esi*4+0x20]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  esi
        push  0x5
        call FUN_0044ff00
        lea  esi,[ebx+0xfc]
        mov  ecx,0x8
        lea  edi,[esp+0x268]
        mov  DWORD PTR [esp+0x258],eax
        rep movsd
        jmp loc_0040ECFB
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x10]
        test  eax,eax
        jne loc_00411D18
        mov  eax,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [eax+0x10]
        add  eax,0x4
        cdq
        and  edx,0x3
        add  eax,edx
        mov  esi,eax
        xor  eax,eax
        mov  ecx,0x10
        lea  edi,[esp+0x248]
        rep stosd
        mov  edi,DWORD PTR [esp+0x1c]
        sar  esi,0x2
        mov  ecx,DWORD PTR [edi+esi*4+0x10]
        push  ecx
        push  0x1
        mov  eax,ebx
        call FUN_00412aa0
        mov  edx,DWORD PTR [edi+esi*4+0x14]
        push  edx
        fstp  DWORD PTR [esp+0x24c]
        push  0x2
        mov  eax,ebx
        call FUN_00412aa0
        jmp loc_0040E900
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x10]
        test  eax,eax
        jne loc_00411D18
        mov  eax,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [eax+0x10]
        add  eax,0x4
        cdq
        and  edx,0x3
        add  eax,edx
        mov  esi,eax
        xor  eax,eax
        mov  ecx,0x10
        lea  edi,[esp+0x248]
        rep stosd
        mov  edi,DWORD PTR [esp+0x1c]
        sar  esi,0x2
        mov  ecx,DWORD PTR [edi+esi*4+0x10]
        push  ecx
        push  0x1
        mov  eax,ebx
        call FUN_00412aa0
        mov  edx,DWORD PTR [edi+esi*4+0x14]
        fadd  DWORD PTR ds:0x491d7c
        push  edx
        push  0x2
        mov  eax,ebx
        fstp  DWORD PTR [esp+0x250]
        call FUN_00412aa0
        mov  eax,DWORD PTR [edi+esi*4+0x18]
        fadd  DWORD PTR ds:0x491d80
        push  eax
        push  0x3
        mov  eax,ebx
        fstp  DWORD PTR [esp+0x254]
        call FUN_00412aa0
        fstp  DWORD PTR [esp+0x250]
        mov  eax,DWORD PTR [edi+esi*4+0x1c]
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        push  eax
        push  0x4
        call FUN_0044ff00
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [esp+0x25c],eax
        mov  eax,DWORD PTR [edi+esi*4+0x20]
        push  eax
        push  0x5
        call FUN_0044ff00
        mov  esi,DWORD PTR [edi+esi*4+0x24]
        mov  DWORD PTR [esp+0x254],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  esi
        push  0x6
        call FUN_0044ff00
        mov  edx,DWORD PTR ds:0x477704
        mov  DWORD PTR [esp+0x258],eax
        lea  esi,[ebx+0xfc]
        mov  ecx,0x8
        lea  edi,[esp+0x268]
        rep movsd
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  esi,DWORD PTR [esp+0x264]
        add  ecx,0x14
        push  ecx
        or   esi,0x1
        push  edx
        lea  eax,[esp+0x250]
        mov  DWORD PTR [esp+0x26c],esi
        call FUN_0040cfb0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [eax+0x10]
        test  ecx,ecx
        jne loc_00411D18
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [ecx+0x10]
        add  eax,0x4
        cdq
        and  edx,0x3
        add  eax,edx
        mov  edx,DWORD PTR [ebx+0x2c]
        mov  esi,eax
        xor  eax,eax
        mov  ecx,0x10
        lea  edi,[esp+0x248]
        rep stosd
        mov  edi,DWORD PTR [esp+0x1c]
        sar  esi,0x2
        mov  eax,DWORD PTR [edi+esi*4+0x10]
        push  eax
        push  0x1
        mov  eax,ebx
        mov  DWORD PTR [esp+0x18],edx
        call FUN_00412aa0
        mov  edx,DWORD PTR [edi+esi*4+0x14]
        fadd  DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [ebx+0x30]
        push  edx
        push  0x2
        mov  eax,ebx
        fstp  DWORD PTR [esp+0x250]
        mov  DWORD PTR [esp+0x18],ecx
        call FUN_00412aa0
        mov  eax,DWORD PTR [edi+esi*4+0x18]
        fadd  DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        push  eax
        fstp  DWORD PTR [esp+0x250]
        push  0x3
        call FUN_0044ff00
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [esp+0x25c],eax
        mov  eax,DWORD PTR [edi+esi*4+0x1c]
        push  eax
        push  0x4
        call FUN_0044ff00
        mov  esi,DWORD PTR [edi+esi*4+0x20]
        mov  DWORD PTR [esp+0x254],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  esi
        push  0x5
        call FUN_0044ff00
        mov  DWORD PTR [esp+0x258],eax
        mov  eax,DWORD PTR [esp+0x1c]
        add  eax,0x14
        lea  esi,[ebx+0xfc]
        mov  ecx,0x8
        lea  edi,[esp+0x268]
        rep movsd
        mov  ecx,DWORD PTR ds:0x477704
        push  eax
        push  ecx
        lea  eax,[esp+0x250]
        mov  DWORD PTR [esp+0x268],0x1
        call FUN_0040cfb0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x10]
        test  eax,eax
        jne loc_00411D18
        mov  eax,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [eax+0x10]
        add  eax,0x4
        cdq
        and  edx,0x3
        add  eax,edx
        mov  esi,eax
        xor  eax,eax
        mov  ecx,0x10
        lea  edi,[esp+0x248]
        rep stosd
        mov  edi,DWORD PTR [esp+0x1c]
        sar  esi,0x2
        mov  ecx,DWORD PTR [edi+esi*4+0x10]
        push  ecx
        push  0x1
        mov  eax,ebx
        call FUN_00412aa0
        mov  edx,DWORD PTR [edi+esi*4+0x14]
        push  edx
        fstp  DWORD PTR [esp+0x24c]
        push  0x2
        mov  eax,ebx
        call FUN_00412aa0
        mov  eax,DWORD PTR [edi+esi*4+0x18]
        fstp  DWORD PTR [esp+0x24c]
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        push  eax
        push  0x3
        call FUN_0044ff00
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [esp+0x25c],eax
        mov  eax,DWORD PTR [edi+esi*4+0x1c]
        push  eax
        push  0x4
        call FUN_0044ff00
        mov  esi,DWORD PTR [edi+esi*4+0x20]
        mov  DWORD PTR [esp+0x254],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  esi
        push  0x5
        call FUN_0044ff00
        lea  esi,[ebx+0xfc]
        mov  ecx,0x8
        lea  edi,[esp+0x268]
        mov  DWORD PTR [esp+0x258],eax
        rep movsd
        mov  DWORD PTR [esp+0x260],0x1
    loc_0040ECFB:
        mov  eax,DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR ds:0x477704
        add  eax,0x14
        push  eax
        push  ecx
        lea  eax,[esp+0x250]
        call FUN_0040cfb0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  DWORD PTR [ebx+0xe8],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        mov  DWORD PTR [esp+0x1c],esi
        call FUN_0044fdb0
        lea  esi,[ebx+esi*4+0xc0]
        mov  edi,eax
        call FUN_00449630
        test  edi,edi
        jl loc_00411D18
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  edx,DWORD PTR [ebx+0xe8]
        mov  ecx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [ecx+edx*4+0x30]
        push  0x5
        push  eax
        push  ecx
        lea  edi,[esp+0x50]
        call FUN_00448e30
        mov  edx,DWORD PTR [eax]
        mov  eax,DWORD PTR [esp+0x18]
        test  eax,eax
        mov  DWORD PTR [esi],edx
        jne loc_0040EDE5
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  DWORD PTR [ebx+0xf0],eax
        mov  eax,DWORD PTR [ebx+0xe8]
        mov  DWORD PTR [ebx+0xec],eax
    loc_0040EDE5:
        call FUN_00449450
        mov  ecx,DWORD PTR [esp+0x18]
        jmp loc_0040F103
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+esi*4+0x30]
        push  0x6
        push  eax
        push  edx
        lea  edi,[esp+0x1c]
        call FUN_00448e30
        jmp loc_0040EE5B
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+esi*4+0x30]
        push  0x6
        push  eax
        push  edx
        lea  edi,[esp+0x1c]
        call FUN_00448d00
    loc_0040EE5B:
        lea  esi,[esp+0x10]
        call FUN_00449450
        mov  esi,eax
        test  DWORD PTR [ebx+0x1444],0x40000
        jne loc_0040EEA7
        lea  eax,[ebx+0x2c]
        call FUN_00418810
        mov  ecx,DWORD PTR [eax]
        add  esi,0x340
        mov  DWORD PTR [esi],ecx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [esi+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [esi+0x8],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_0040EEA7:
        add  ebx,0x2c
        mov  ecx,DWORD PTR [ebx]
        add  esi,0x340
        mov  DWORD PTR [esi],ecx
        mov  edx,DWORD PTR [ebx+0x4]
        mov  DWORD PTR [esi+0x4],edx
        mov  eax,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esi+0x8],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x1
        mov  esi,eax
        call FUN_0044fdb0
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+esi*4+0x30]
        push  0x6
        push  eax
        push  edx
        lea  edi,[esp+0x1c]
        call FUN_00448e30
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        push  0x6
        push  eax
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [eax+esi*4+0x30]
        push  ecx
        lea  edi,[esp+0x1c]
        call FUN_00448e30
        mov  esi,edi
        call FUN_00449450
        mov  esi,eax
        test  DWORD PTR [ebx+0x1444],0x40000
        jne loc_0040EF88
        lea  eax,[ebx+0x2c]
        call FUN_00418810
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esi+0x340]
        mov  DWORD PTR [edx],ecx
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [edx+0x4],ecx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [edx+0x8],eax
        jmp loc_0040EFA1
    loc_0040EF88:
        lea  ecx,[ebx+0x2c]
        mov  eax,DWORD PTR [ecx]
        lea  edx,[esi+0x340]
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x4],eax
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edx+0x8],ecx
    loc_0040EFA1:
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2c]
        or   DWORD PTR [esi+0x35c],0x4
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        mov  DWORD PTR [esp+0x1c],esi
        call FUN_0044fdb0
        mov  edi,eax
        lea  esi,[ebx+esi*4+0xc0]
        mov  DWORD PTR [esp+0x10],edi
        call FUN_00449630
        mov  edx,DWORD PTR [ebx+0xe8]
        mov  eax,ds:0x477704
        mov  eax,DWORD PTR [eax+edx*4+0x30]
        push  0x5
        push  edi
        push  eax
        lea  edi,[esp+0x58]
        call FUN_00448e30
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esi],ecx
        call FUN_00449450
        mov  ecx,DWORD PTR [esp+0x18]
        test  ecx,ecx
        jne loc_0040F04C
        fld  DWORD PTR [eax+0x50]
        fmul  DWORD PTR [eax+0x40]
        fstp  DWORD PTR [ebx+0x13a4]
        fld  DWORD PTR [eax+0x4c]
        fmul  DWORD PTR [eax+0x3c]
        fstp  DWORD PTR [ebx+0x13a8]
    loc_0040F04C:
        test  BYTE PTR [ebx+0x1444],0x10
        je loc_0040F05C
        mov  eax,esi
        call FUN_004495e0
    loc_0040F05C:
        mov  eax,DWORD PTR [esp+0x18]
        test  eax,eax
        jne loc_00411D18
        mov  eax,DWORD PTR [ebx+0x1444]
        mov  edx,DWORD PTR [ebx+0xe8]
        or   eax,0x1000
        mov  DWORD PTR [ebx+0x1444],eax
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebx+0xf4],eax
        mov  DWORD PTR [ebx+0xf0],eax
        mov  DWORD PTR [ebx+0xf8],0x0
        mov  DWORD PTR [ebx+0xec],edx
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        lea  esi,[ebx+eax*4+0xc0]
        mov  DWORD PTR [esp+0x10],eax
        call FUN_00449630
        mov  edx,DWORD PTR [ebx+0xf4]
        mov  eax,DWORD PTR [ebx+0xe8]
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+eax*4+0x30]
        push  0x5
        add  edx,0x5
        push  edx
        push  eax
        lea  edi,[esp+0x54]
        call FUN_00448e30
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [esi],eax
        call FUN_00449450
        mov  ecx,DWORD PTR [esp+0x10]
    loc_0040F103:
        test  ecx,ecx
        jne loc_0040F11F
        fld  DWORD PTR [eax+0x50]
        fmul  DWORD PTR [eax+0x40]
        fstp  DWORD PTR [ebx+0x13a4]
        fld  DWORD PTR [eax+0x4c]
        fmul  DWORD PTR [eax+0x3c]
        fstp  DWORD PTR [ebx+0x13a8]
    loc_0040F11F:
        test  BYTE PTR [ebx+0x1444],0x10
        je loc_00411D18
        mov  eax,esi
        call FUN_004495e0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        cmp  ax,0x118
        lea  esi,[ebx+0x58]
        je loc_0040F159
        lea  esi,[ebx+0x84]
    loc_0040F159:
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fld  DWORD PTR [esp+0x18]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F191
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esi],ecx
    loc_0040F191:
        fcom  QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F1A3
        fstp  DWORD PTR [esi+0x4]
        jmp loc_0040F1A5
    loc_0040F1A3:
        fstp  st(0)
    loc_0040F1A5:
        mov  eax,DWORD PTR [esi+0x28]
        and  eax,0xfffffffe
        mov  DWORD PTR [esi+0x28],eax
        fld  DWORD PTR [ebx+0x84]
        fadd  DWORD PTR [ebx+0x58]
        add  ebx,0x2c
        fstp  DWORD PTR [esp+0x24]
        mov  edx,DWORD PTR [esp+0x24]
        fld  DWORD PTR [ebx+0x5c]
        fadd  DWORD PTR [ebx+0x30]
        fstp  DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [esp+0x28]
        fld  DWORD PTR [ebx+0x60]
        fadd  DWORD PTR [ebx+0x34]
        mov  DWORD PTR [ebx],edx
        mov  DWORD PTR [ebx+0x4],eax
        xor  eax,eax
        fstp  DWORD PTR [esp+0x2c]
        mov  ecx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [ebx+0x8],ecx
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        cmp  ax,0x128
        lea  esi,[ebx+0x58]
        je loc_0040F20C
        lea  esi,[ebx+0x84]
    loc_0040F20C:
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x30]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR [esi]
        xor  eax,eax
        fstp  DWORD PTR [esi]
        fld  DWORD PTR [esp+0x30]
        fadd  DWORD PTR [esi+0x4]
        fstp  DWORD PTR [esi+0x4]
        fadd  DWORD PTR [esi+0x8]
        fstp  DWORD PTR [esi+0x8]
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        cmp  ax,0x119
        lea  edi,[ebx+0x58]
        je loc_0040F33C
        lea  edi,[ebx+0x84]
        lea  esi,[ebx+0x188]
    loc_0040F28C:
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  DWORD PTR [esi+0x44],eax
        mov  eax,ds:0x491c14
        lea  edx,[esi+0x18]
        mov  DWORD PTR [edx],eax
        mov  ecx,DWORD PTR ds:0x491c18
        mov  DWORD PTR [edx+0x4],ecx
        mov  eax,ds:0x491c1c
        mov  DWORD PTR [edx+0x8],eax
        mov  edx,DWORD PTR ds:0x491c14
        lea  ecx,[esi+0x24]
        mov  DWORD PTR [ecx],edx
        mov  eax,ds:0x491c18
        mov  DWORD PTR [ecx+0x4],eax
        mov  edx,DWORD PTR ds:0x491c1c
        mov  DWORD PTR [ecx+0x8],edx
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x1
        call FUN_0044fdb0
        fld  DWORD PTR [esp+0x18]
        fcomp QWORD PTR ds:0x470d58
        mov  DWORD PTR [esi+0x48],eax
        mov  eax,edi
        mov  edx,DWORD PTR [eax]
        mov  ecx,esi
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],eax
        fnstsw ax
        test  ah,0x41
        jne loc_0040F347
        fld  DWORD PTR [esp+0x18]
        jmp loc_0040F34A
    loc_0040F33C:
        lea  esi,[ebx+0x13c]
        jmp loc_0040F28C
    loc_0040F347:
        fld  DWORD PTR [edi+0x4]
    loc_0040F34A:
        fld  DWORD PTR [esp+0x1c]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F361
        fld  DWORD PTR [esp+0x1c]
        jmp loc_0040F363
    loc_0040F361:
        fld  DWORD PTR [edi]
    loc_0040F363:
        fstp  DWORD PTR [esp+0x24]
        mov  edx,DWORD PTR [esp+0x24]
        lea  ecx,[esi+0xc]
        mov  DWORD PTR [ecx],edx
        fstp  DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [esp+0x28]
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [esp+0x2c],0x0
        mov  edx,DWORD PTR [esp+0x2c]
        mov  eax,esi
        mov  DWORD PTR [ecx+0x8],edx
        call FUN_004050d0
        and  DWORD PTR [edi+0x28],0xfffffffe
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        cmp  ax,0x11c
        lea  esi,[ebx+0x58]
        je loc_0040F3BB
        lea  esi,[ebx+0x84]
    loc_0040F3BB:
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x1c]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F42D
        mov  eax,DWORD PTR [ebx+0x1444]
        test  ah,0x8
        je loc_0040F422
        fld  DWORD PTR [esp+0x1c]
        push  ecx
        fsub  DWORD PTR ds:0x470b94
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        fsubr DWORD PTR ds:0x470b94
        push  ecx
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        fstp  DWORD PTR [esp+0x1c]
    loc_0040F422:
        mov  eax,DWORD PTR [esp+0x1c]
        push  eax
        push  esi
        call FUN_00413170
    loc_0040F42D:
        fld  DWORD PTR [esp+0x18]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F445
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esi+0x18],ecx
    loc_0040F445:
        and  DWORD PTR [esi+0x28],0xfffffffe
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        cmp  ax,0x11d
        lea  edi,[ebx+0x58]
        je loc_0040F4F9
        lea  edi,[ebx+0x84]
        lea  esi,[ebx+0x210]
    loc_0040F479:
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        fld  DWORD PTR [esp+0x1c]
        fcomp QWORD PTR ds:0x470d58
        mov  DWORD PTR [esi+0x38],eax
        cmp  eax,0x7
        fnstsw ax
        je loc_0040F52F
        test  ah,0x41
        jne loc_0040F504
        mov  eax,DWORD PTR [ebx+0x1444]
        fld  DWORD PTR [esp+0x1c]
        test  ah,0x8
        je loc_0040F507
        fsub  DWORD PTR ds:0x470b94
        push  ecx
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        fsubr DWORD PTR ds:0x470b94
        push  ecx
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        jmp loc_0040F507
    loc_0040F4F9:
        lea  esi,[ebx+0x1d4]
        jmp loc_0040F479
    loc_0040F504:
        fld  DWORD PTR [edi+0x1c]
    loc_0040F507:
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x18]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F526
        fld  DWORD PTR [esp+0x18]
        fstp  DWORD PTR [esp+0x14]
        jmp loc_0040F569
    loc_0040F526:
        fld  DWORD PTR [edi+0x18]
        fstp  DWORD PTR [esp+0x14]
        jmp loc_0040F569
    loc_0040F52F:
        test  ah,0x41
        jne loc_0040F53E
        mov  edx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x10],edx
        jmp loc_0040F546
    loc_0040F53E:
        mov  DWORD PTR [esp+0x10],0x0
    loc_0040F546:
        fld  DWORD PTR [esp+0x18]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F561
        mov  eax,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x14],eax
        jmp loc_0040F569
    loc_0040F561:
        mov  DWORD PTR [esp+0x14],0x0
    loc_0040F569:
        mov  ecx,DWORD PTR [edi+0x1c]
        mov  edx,DWORD PTR [edi+0x18]
        mov  DWORD PTR [esp+0x30],ecx
        fld  DWORD PTR [esp+0x30]
        fsub  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x34],edx
        fabs
        fcomp DWORD PTR ds:0x470b18
        fnstsw ax
        test  ah,0x1
        jne loc_0040F5BB
        fld  DWORD PTR [esp+0x30]
        fcomp DWORD PTR [esp+0x10]
        fnstsw ax
        test  ah,0x5
        jp loc_0040F5AD
        fld  DWORD PTR [esp+0x30]
        fadd  DWORD PTR ds:0x470b14
        fstp  DWORD PTR [esp+0x30]
        jmp loc_0040F5BB
    loc_0040F5AD:
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470b14
        fstp  DWORD PTR [esp+0x10]
    loc_0040F5BB:
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  DWORD PTR [esi+0x34],eax
        mov  eax,ds:0x491c20
        mov  DWORD PTR [esi+0x10],eax
        mov  ecx,DWORD PTR ds:0x491c24
        mov  DWORD PTR [esi+0x14],ecx
        mov  edx,DWORD PTR ds:0x491c20
        mov  ecx,DWORD PTR [esp+0x30]
        mov  DWORD PTR [esi+0x18],edx
        mov  edx,DWORD PTR [esp+0x34]
        jmp loc_0040FC07
        cmp  ax,0x120
        lea  esi,[ebx+0x58]
        je loc_0040F604
        lea  esi,[ebx+0x84]
    loc_0040F604:
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x30]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        test  BYTE PTR [esi+0x28],0x1
        jne loc_0040F672
        mov  eax,esi
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esi+0xc]
        mov  DWORD PTR [edx],ecx
        mov  ecx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [edx+0x8],eax
    loc_0040F672:
        fld  DWORD PTR [esp+0x18]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F68E
        mov  ecx,DWORD PTR [esp+0x18]
        push  ecx
        push  esi
        call FUN_00413170
    loc_0040F68E:
        fld  DWORD PTR [esp+0x1c]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F6A6
        mov  edx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esi+0x18],edx
    loc_0040F6A6:
        fld  DWORD PTR [esp+0x30]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F6BE
        mov  eax,DWORD PTR [esp+0x30]
        mov  DWORD PTR [esi+0x20],eax
    loc_0040F6BE:
        fld  DWORD PTR [esp+0x10]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F6D6
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0x24],ecx
    loc_0040F6D6:
        or   DWORD PTR [esi+0x28],0x1
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        cmp  ax,0x121
        lea  ecx,[ebx+0x58]
        je loc_0040F700
        lea  ecx,[ebx+0x84]
    loc_0040F700:
        cmp  ax,0x121
        mov  DWORD PTR [esp+0x18],ecx
        lea  edi,[ebx+0x1d4]
        je loc_0040F789
        lea  edi,[ebx+0x210]
        lea  esi,[ebx+0x288]
    loc_0040F71C:
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x30]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x4
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x5
        call FUN_0044fe40
        fld  DWORD PTR [esp+0x10]
        fcomp QWORD PTR ds:0x470d58
        mov  ecx,DWORD PTR [esp+0x18]
        fnstsw ax
        test  ah,0x41
        jne loc_0040F791
        fld  DWORD PTR [esp+0x10]
        jmp loc_0040F794
    loc_0040F789:
        lea  esi,[ebx+0x24c]
        jmp loc_0040F71C
    loc_0040F791:
        fld  DWORD PTR [ecx+0x18]
    loc_0040F794:
        fld  DWORD PTR [esp+0x30]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F7AB
        fld  DWORD PTR [esp+0x30]
        jmp loc_0040F7AE
    loc_0040F7AB:
        fld  DWORD PTR [ecx+0x1c]
    loc_0040F7AE:
        mov  eax,DWORD PTR [ecx+0x18]
        fstp  DWORD PTR [esp+0x3c]
        mov  edx,DWORD PTR [ecx+0x1c]
        fstp  DWORD PTR [esp+0x40]
        mov  DWORD PTR [esp+0x34],eax
        mov  DWORD PTR [esp+0x30],edx
        fcom  QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        je loc_0040F7D6
        fstp  st(0)
        fld  DWORD PTR [ecx+0x24]
    loc_0040F7D6:
        fld  DWORD PTR [esp+0x1c]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F7ED
        fld  DWORD PTR [esp+0x1c]
        jmp loc_0040F7F0
    loc_0040F7ED:
        fld  DWORD PTR [ecx+0x20]
    loc_0040F7F0:
        mov  eax,DWORD PTR [ecx+0x24]
        fstp  DWORD PTR [esp+0x24]
        mov  edx,DWORD PTR [ecx+0x20]
        mov  DWORD PTR [esp+0x20],eax
        fstp  DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  DWORD PTR [esp+0x1c],edx
        mov  edx,DWORD PTR [eax+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x1
        mov  DWORD PTR [esp+0x14],eax
        call FUN_0044fdb0
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [edi+0x34],ecx
        mov  edx,DWORD PTR ds:0x491c20
        mov  ebx,eax
        mov  DWORD PTR [edi+0x10],edx
        mov  eax,ds:0x491c24
        mov  DWORD PTR [edi+0x14],eax
        mov  ecx,DWORD PTR ds:0x491c20
        mov  eax,DWORD PTR [esp+0x30]
        mov  DWORD PTR [edi+0x18],ecx
        mov  edx,DWORD PTR ds:0x491c24
        mov  ecx,DWORD PTR [esp+0x34]
        mov  DWORD PTR [edi],eax
        mov  eax,DWORD PTR [esp+0x40]
        mov  DWORD PTR [edi+0x1c],edx
        mov  edx,DWORD PTR [esp+0x3c]
        mov  DWORD PTR [edi+0xc],eax
        mov  eax,edi
        mov  DWORD PTR [edi+0x38],ebx
        mov  DWORD PTR [edi+0x4],ecx
        mov  DWORD PTR [edi+0x8],edx
        call FUN_00412db0
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0x34],ecx
        mov  edx,DWORD PTR ds:0x491c20
        mov  DWORD PTR [esi+0x10],edx
        mov  eax,ds:0x491c24
        mov  DWORD PTR [esi+0x14],eax
        mov  ecx,DWORD PTR ds:0x491c20
        mov  eax,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esi+0x18],ecx
        mov  edx,DWORD PTR ds:0x491c24
        mov  ecx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [esi],eax
        mov  eax,DWORD PTR [esp+0x28]
        mov  DWORD PTR [esi+0x1c],edx
        mov  edx,DWORD PTR [esp+0x24]
        mov  DWORD PTR [esi+0xc],eax
        mov  eax,esi
        mov  DWORD PTR [esi+0x38],ebx
        mov  DWORD PTR [esi+0x4],ecx
        mov  DWORD PTR [esi+0x8],edx
        call FUN_00412db0
        mov  eax,DWORD PTR [esp+0x18]
        mov  edx,eax
        mov  esi,DWORD PTR [edx]
        lea  ecx,[eax+0xc]
        mov  DWORD PTR [ecx],esi
        mov  esi,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ecx+0x4],esi
        mov  DWORD PTR [ecx+0x8],edx
        or   DWORD PTR [eax+0x28],0x1
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        cmp  ax,0x12a
        lea  esi,[ebx+0x58]
        je loc_0040F90D
        lea  esi,[ebx+0x84]
    loc_0040F90D:
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fld  DWORD PTR [esp+0x10]
        fcomp QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F946
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0xc],eax
    loc_0040F946:
        fcom  QWORD PTR ds:0x470d58
        fnstsw ax
        test  ah,0x41
        jne loc_0040F958
        fstp  DWORD PTR [esi+0x10]
        jmp loc_0040F95A
    loc_0040F958:
        fstp  st(0)
    loc_0040F95A:
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+0x10]
        add  edx,0x1068
        mov  eax,DWORD PTR [edx]
        add  ebx,0x58
        mov  DWORD PTR [ebx],eax
        mov  ecx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ebx+0x4],ecx
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ebx+0x8],edx
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [eax+0x10]
        add  ecx,0x1068
        mov  edx,DWORD PTR [ecx]
        add  ebx,0x84
        mov  DWORD PTR [ebx],edx
        mov  eax,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [ebx+0x4],eax
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [ebx+0x8],ecx
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        or   DWORD PTR [ebx+0x1444],0x200
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [ebx+0x13ac]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [ebx+0x13b0]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [ebx+0x13b4]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [ebx+0x13b8]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        and  DWORD PTR [ebx+0x1444],0xfffffdff
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fld  st(0)
        fmul  st,st(1)
        fstp  DWORD PTR [ebx+0x1454]
        jmp loc_00411D16
        cmp  ax,0x124
        lea  edi,[ebx+0x58]
        je loc_0040FACB
        lea  edi,[ebx+0x84]
        lea  esi,[ebx+0x210]
    loc_0040FA99:
        fld  DWORD PTR [ebx+0x13b4]
        mov  ecx,0x4918b0
        fmul  DWORD PTR ds:0x470d40
        fld  DWORD PTR [ebx+0x13ac]
        fsub  st,st(1)
        fcomp DWORD PTR [ebx+0x2c]
        fnstsw ax
        test  ah,0x41
        jne loc_0040FAD3
        fstp  st(0)
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470d50
        jmp loc_0040FB39
    loc_0040FACB:
        lea  esi,[ebx+0x1d4]
        jmp loc_0040FA99
    loc_0040FAD3:
        fadd  DWORD PTR [ebx+0x13ac]
        fcomp DWORD PTR [ebx+0x2c]
        fnstsw ax
        test  ah,0x5
        jp loc_0040FAF6
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470b18
        fmul  DWORD PTR ds:0x470cc4
        jmp loc_0040FB2A
    loc_0040FAF6:
        fld  DWORD PTR [ebx+0x2c]
        mov  edx,DWORD PTR ds:0x477834
        fcomp DWORD PTR [edx+0x3c0]
        fnstsw ax
        test  ah,0x5
        jp loc_0040FB19
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470b94
        jmp loc_0040FB39
    loc_0040FB19:
        call FUN_0044bb90
        fmul  DWORD PTR ds:0x470b18
        fmul  DWORD PTR ds:0x470b0c
    loc_0040FB2A:
        fadd  DWORD PTR ds:0x470b18
        push  ecx
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
    loc_0040FB39:
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [ebx+0x13b8]
        fmul  DWORD PTR ds:0x470d40
        fld  DWORD PTR [ebx+0x13b0]
        fsub  st,st(1)
        fcomp DWORD PTR [ebx+0x30]
        fnstsw ax
        test  ah,0x41
        jne loc_0040FB65
        fstp  st(0)
        fld  DWORD PTR [esp+0x1c]
        fabs
        jmp loc_0040FB7D
    loc_0040FB65:
        fadd  DWORD PTR [ebx+0x13b0]
        fcomp DWORD PTR [ebx+0x30]
        fnstsw ax
        test  ah,0x5
        jp loc_0040FB81
        fld  DWORD PTR [esp+0x1c]
        fabs
        fchs
    loc_0040FB7D:
        fstp  DWORD PTR [esp+0x1c]
    loc_0040FB81:
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        cmp  eax,0x7
        mov  DWORD PTR [esi+0x38],eax
        mov  DWORD PTR [esp+0x14],0x0
        je loc_0040FBAB
        mov  eax,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x10],eax
        jmp loc_0040FBB3
    loc_0040FBAB:
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x10],ecx
    loc_0040FBB3:
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        mov  DWORD PTR [esp+0x24],edx
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x28]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  DWORD PTR [esi+0x34],eax
        mov  eax,ds:0x491c20
        mov  DWORD PTR [esi+0x10],eax
        mov  ecx,DWORD PTR ds:0x491c24
        mov  DWORD PTR [esi+0x14],ecx
        mov  edx,DWORD PTR ds:0x491c20
        mov  ecx,DWORD PTR [esp+0x24]
        mov  DWORD PTR [esi+0x18],edx
        mov  edx,DWORD PTR [esp+0x28]
    loc_0040FC07:
        mov  eax,ds:0x491c24
        mov  DWORD PTR [esi+0x1c],eax
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi],ecx
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esi+0x4],edx
        mov  DWORD PTR [esi+0x8],eax
        mov  eax,esi
        mov  DWORD PTR [esi+0xc],ecx
        call FUN_00412db0
        and  DWORD PTR [edi+0x28],0xfffffffe
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x30]
        mov  edx,DWORD PTR [ebx+0x13c4]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  DWORD PTR [esp+0x10],edx
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x0
        call FUN_0044fdb0
        fild  DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR ds:0x47770c
        mov  DWORD PTR [ecx+eax*8+0x9e98],esi
        fdivr DWORD PTR [esp+0x30]
        fstp  DWORD PTR [ecx+eax*8+0x9e94]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [ebx+0xb0]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [ebx+0xb4]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [ebx+0xb8]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [ebx+0xbc]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ecx,DWORD PTR [ebx+0x1444]
        or   ecx,eax
        mov  al,cl
        test  al,0x10
        mov  DWORD PTR [ebx+0x1444],ecx
        je loc_00411D18
        lea  esi,[ebx+0xc0]
        mov  edi,0xa
    loc_0040FD61:
        mov  eax,esi
        call FUN_004495e0
        add  esi,0x4
        dec  edi
        jne loc_0040FD61
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ecx,DWORD PTR [ebx+0x1444]
        not  eax
        and  ecx,eax
        mov  al,cl
        test  al,0x10
        mov  DWORD PTR [ebx+0x1444],ecx
        jne loc_00411D18
        lea  esi,[ebx+0xc0]
        mov  edi,0xa
    loc_0040FDB4:
        mov  eax,esi
        call FUN_00449590
        add  esi,0x4
        dec  edi
        jne loc_0040FDB4
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  ecx,0xc
        xor  eax,eax
        lea  edi,[ebx+0x13d0]
        rep stosd
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x1444]
        test  ah,ah
        jns loc_0040FE28
        cmp  esi,0x1
        jne loc_0040FE1E
        mov  esi,0xa
        jmp loc_0040FE28
    loc_0040FE1E:
        cmp  esi,0x4
        jne loc_0040FE28
        mov  esi,0xb
    loc_0040FE28:
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  DWORD PTR [ebx+esi*4+0x13cc],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [ebx+0x1400]
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebx+0x1404],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        lea  eax,[ebx+0x2c]
        lea  edi,[ebx+0x13cc]
        call FUN_0040c9a0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ecx,DWORD PTR [ebx+0x1444]
        test  ch,ch
        jns loc_0040FF08
        cmp  eax,0x1
        jne loc_0040FEFE
        mov  eax,0xa
        mov  DWORD PTR [ebx+0x13cc],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_0040FEFE:
        cmp  eax,0x4
        jne loc_0040FF08
        mov  eax,0xb
    loc_0040FF08:
        mov  DWORD PTR [ebx+0x13cc],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        xor  esi,esi
        push  esi
        call FUN_0044fdb0
        mov  DWORD PTR [ebx+0x13c0],eax
        mov  DWORD PTR [ebx+0x13c4],eax
        mov  eax,ds:0x47770c
        mov  DWORD PTR [eax+0x9e94],esi
        mov  DWORD PTR [eax+0x9e98],esi
        mov  DWORD PTR [eax+0x9e9c],esi
        mov  DWORD PTR [eax+0x9ea0],esi
        mov  DWORD PTR [eax+0x9ea4],esi
        mov  DWORD PTR [eax+0x9ea8],esi
        mov  DWORD PTR [eax+0x9eac],esi
        mov  DWORD PTR [eax+0x9eb0],esi
        mov  ecx,DWORD PTR [ebx+0x13c0]
        mov  DWORD PTR [ebx+0x13c8],ecx
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        test  eax,eax
        jge loc_0040FFE0
        mov  eax,DWORD PTR [ebx+0x1444]
        test  ah,ah
        jns loc_0040FFBF
        mov  edx,DWORD PTR [ebx+0x1450]
        mov  eax,ds:0x477704
        mov  DWORD PTR [eax+edx*4+0x10],0x0
    loc_0040FFBF:
        and  DWORD PTR [ebx+0x1444],0xffff7fff
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_0040FFE0:
        mov  ecx,DWORD PTR [ebx+0x1444]
        mov  edx,DWORD PTR ds:0x477704
        or   ecx,0x8000
        mov  DWORD PTR [ebx+0x1444],ecx
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  DWORD PTR [edx+eax*4+0x10],ecx
        mov  DWORD PTR [ebx+0x1450],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        push  eax
        lea  eax,[ebx+0x141c]
        call FUN_00405410
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        push  eax
        lea  eax,[ebx+0x1430]
        call FUN_00405410
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x477704
        push  eax
        call FUN_0040e6a0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x474c74
        cmp  eax,0x4
        ja loc_00411D18
        jmp  DWORD PTR [eax*4+0x411f98]
        push  0x1
    loc_004100B2:
        mov  edx,DWORD PTR [edx+0x4]
        call FUN_0044fdb0
        mov  esi,eax
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a10
        mov  DWORD PTR [eax],esi
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        push  0x2
        jmp loc_004100B2
        push  0x3
        jmp loc_004100B2
        push  0x4
        jmp loc_004100B2
        mov  eax,ds:0x474c74
        cmp  eax,0x4
        ja loc_00411D18
        jmp  DWORD PTR [eax*4+0x411fac]
        mov  eax,DWORD PTR [edx+0x4]
        jmp loc_0041194C
    loc_00410107:
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x3
        jmp loc_00411951
    loc_00410114:
        mov  ecx,0x4
        jmp loc_00411909
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x4
        jmp loc_00411951
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  edx,esi
        imul  edx,edx,0x210
        add  edx,ebx
        xor  eax,eax
        lea  edi,[edx+0x2c4]
        mov  ecx,0x84
        rep stosd
        mov  ecx,0x1
        mov  WORD PTR [edx+0x4b8],cx
        mov  WORD PTR [edx+0x4ba],cx
        mov  DWORD PTR [edx+0x2d4],eax
        mov  DWORD PTR [edx+0x2dc],0x40000000
        mov  DWORD PTR [edx+0x4c4],0x7
        mov  DWORD PTR [edx+0x4c8],0x18
        mov  DWORD PTR [edx+0x4c0],0x203
        lea  ecx,[esi+esi*2+0x4d1]
        lea  edx,[esi+esi*2]
        mov  DWORD PTR [ebx+ecx*4],eax
        mov  DWORD PTR [ebx+edx*4+0x1348],eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x0
        call FUN_0044fdb0
        imul  esi,esi,0x210
        imul  eax,eax,0x210
        lea  edi,[eax+ebx*1+0x2c4]
        lea  esi,[esi+ebx*1+0x2c4]
        mov  ecx,0x84
        rep movsd
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        lea  ecx,[eax+eax*2+0x4d1]
        imul  eax,eax,0x210
        fld  DWORD PTR [ebx+ecx*4]
        fadd  DWORD PTR [ebx+0x2c]
        fstp  DWORD PTR [esp+0x24]
        fld  DWORD PTR [ebx+ecx*4+0x4]
        fadd  DWORD PTR [ebx+0x30]
        mov  esi,DWORD PTR [esp+0x24]
        lea  ecx,[ebx+ecx*4]
        fstp  DWORD PTR [esp+0x28]
        lea  edx,[eax+ebx*1]
        fld  DWORD PTR [ecx+0x8]
        lea  ecx,[edx+0x2c8]
        fadd  DWORD PTR [ebx+0x34]
        mov  eax,ecx
        mov  DWORD PTR [eax],esi
        mov  esi,DWORD PTR [esp+0x28]
        fstp  DWORD PTR [esp+0x2c]
        mov  DWORD PTR [eax+0x4],esi
        mov  esi,DWORD PTR [esp+0x2c]
        fld  DWORD PTR ds:0x470b04
        mov  DWORD PTR [eax+0x8],esi
        fld  DWORD PTR [ebx+0x1454]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_004102B2
        mov  eax,ds:0x477834
        fld  DWORD PTR [ecx+0x4]
        fsub  DWORD PTR [eax+0x3c4]
        fld  DWORD PTR [ecx]
        fsub  DWORD PTR [eax+0x3c0]
        fld  st(0)
        fmul  st,st(1)
        fld  st(2)
        fmul  st,st(3)
        faddp st(1),st
        fld  DWORD PTR [ebx+0x1454]
        fcompp
        fnstsw ax
        fstp  st(0)
        test  ah,0x41
        fstp  st(0)
        jp loc_00411D18
    loc_004102B2:
        mov  ecx,DWORD PTR ds:0x4776f0
        lea  eax,[edx+0x2c4]
        push  ecx
        call FUN_004073e0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        imul  eax,eax,0x210
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        push  0x1
        lea  esi,[eax+ebx*1]
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x2c4],ax
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x2c6],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        lea  edx,[esi+esi*2+0x4d1]
        fstp  DWORD PTR [ebx+edx*4]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        lea  eax,[esi+esi*2]
        fstp  DWORD PTR [ebx+eax*4+0x1348]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        imul  eax,eax,0x210
        mov  edx,DWORD PTR [ebx+0x14d8]
        lea  esi,[eax+ebx*1]
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        mov  ecx,0x2
        fstp  DWORD PTR [esi+0x2d4]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2d8]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        imul  eax,eax,0x210
        mov  edx,DWORD PTR [ebx+0x14d8]
        lea  esi,[eax+ebx*1]
        mov  eax,DWORD PTR [edx+0x4]
    loc_00410408:
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2dc]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2e0]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        imul  eax,eax,0x210
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        push  0x1
        lea  esi,[eax+ebx*1]
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4b8],ax
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4ba],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,ds:0x474c74
        test  eax,eax
        jne loc_004104BC
        mov  ecx,0x1
        jmp loc_004104D7
    loc_004104BC:
        cmp  eax,0x1
        jne loc_004104C8
        mov  ecx,0x2
        jmp loc_004104D7
    loc_004104C8:
        cmp  eax,0x2
        mov  ecx,0x3
        je loc_004104D7
        mov  ecx,0x4
    loc_004104D7:
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        call FUN_0044fe40
        imul  esi,esi,0x210
        fstp  DWORD PTR [esi+ebx*1+0x2dc]
        mov  eax,ds:0x474c74
        add  esi,ebx
        test  eax,eax
        jne loc_00410504
        mov  ecx,0x5
        jmp loc_0041051F
    loc_00410504:
        cmp  eax,0x1
        jne loc_00410510
        mov  ecx,0x6
        jmp loc_0041051F
    loc_00410510:
        cmp  eax,0x2
        mov  ecx,0x7
        je loc_0041051F
        mov  ecx,0x8
    loc_0041051F:
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2e0]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,ds:0x474c74
        test  eax,eax
        jne loc_00410563
        push  0x1
        jmp loc_00410577
    loc_00410563:
        cmp  eax,0x1
        jne loc_0041056C
        push  0x2
        jmp loc_00410577
    loc_0041056C:
        cmp  eax,0x2
        jne loc_00410575
        push  0x3
        jmp loc_00410577
    loc_00410575:
        push  0x4
    loc_00410577:
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        call FUN_0044fdb0
        imul  esi,esi,0x210
        add  esi,ebx
        mov  WORD PTR [esi+0x4b8],ax
        mov  eax,ds:0x474c74
        test  eax,eax
        jne loc_004105A1
        push  0x5
        jmp loc_004105B5
    loc_004105A1:
        cmp  eax,0x1
        jne loc_004105AA
        push  0x6
        jmp loc_004105B5
    loc_004105AA:
        cmp  eax,0x2
        jne loc_004105B3
        push  0x7
        jmp loc_004105B5
    loc_004105B3:
        push  0x8
    loc_004105B5:
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4ba],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ecx,DWORD PTR ds:0x474c98
        cmp  ecx,0x200
        jge loc_004106DA
        imul  eax,eax,0x210
        cmp  ecx,0xfffffe00
        jmp loc_00410738
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ecx,DWORD PTR ds:0x474c98
        cmp  ecx,0x258
        jl loc_00410678
        mov  edx,DWORD PTR [ebx+0x14d8]
        imul  eax,eax,0x210
        lea  esi,[eax+ebx*1]
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x9
        call FUN_0044fe40
        mov  ecx,0xa
        fstp  DWORD PTR [esi+0x2dc]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2e0]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_00410678:
        cmp  ecx,0xc8
        jl loc_004106D2
        mov  edx,DWORD PTR [ebx+0x14d8]
        imul  eax,eax,0x210
        lea  esi,[eax+ebx*1]
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x7
        call FUN_0044fe40
        mov  ecx,0x8
        fstp  DWORD PTR [esi+0x2dc]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2e0]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_004106D2:
        cmp  ecx,0xffffff38
        jl loc_0041072C
    loc_004106DA:
        mov  edx,DWORD PTR [ebx+0x14d8]
        imul  eax,eax,0x210
        lea  esi,[eax+ebx*1]
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x5
        call FUN_0044fe40
        mov  ecx,0x6
        fstp  DWORD PTR [esi+0x2dc]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2e0]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_0041072C:
        imul  eax,eax,0x210
        cmp  ecx,0xfffffda8
    loc_00410738:
        mov  edx,DWORD PTR [ebx+0x14d8]
        lea  esi,[eax+ebx*1]
        mov  eax,DWORD PTR [edx+0x4]
        jl loc_00410408
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2dc]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x4
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2e0]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x30]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x4
        call FUN_0044fe40
        fild  DWORD PTR ds:0x474c98
        imul  esi,esi,0x210
        fadd  DWORD PTR ds:0x470d4c
        fld  DWORD PTR [esp+0x18]
        fsub  DWORD PTR [esp+0x10]
        fmulp st(1),st
        lea  eax,[esi+ebx*1]
        fmul  DWORD PTR ds:0x470d48
        fadd  DWORD PTR [esp+0x10]
        fstp  DWORD PTR [eax+0x2dc]
        fild  DWORD PTR ds:0x474c98
        fadd  DWORD PTR ds:0x470d4c
        fxch  st(1)
        fsub  DWORD PTR [esp+0x30]
        fmulp st(1),st
        fmul  DWORD PTR ds:0x470d48
        fadd  DWORD PTR [esp+0x30]
        fstp  DWORD PTR [eax+0x2e0]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ecx,DWORD PTR ds:0x474c98
        cmp  ecx,0x200
        jge loc_00410949
        imul  eax,eax,0x210
        cmp  ecx,0xfffffe00
        jmp loc_004109A3
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ecx,DWORD PTR ds:0x474c98
        cmp  ecx,0x258
        jl loc_004108EB
        mov  ecx,DWORD PTR [ebx+0x14d8]
        imul  eax,eax,0x210
        mov  edx,DWORD PTR [ecx+0x4]
        push  0x9
        lea  esi,[eax+ebx*1]
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4b8],ax
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0xa
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4ba],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_004108EB:
        cmp  ecx,0xc8
        jl loc_00410941
        mov  ecx,DWORD PTR [ebx+0x14d8]
        imul  eax,eax,0x210
        mov  edx,DWORD PTR [ecx+0x4]
        push  0x7
        lea  esi,[eax+ebx*1]
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4b8],ax
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x8
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4ba],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_00410941:
        cmp  ecx,0xffffff38
        jl loc_00410997
    loc_00410949:
        mov  ecx,DWORD PTR [ebx+0x14d8]
        imul  eax,eax,0x210
        mov  edx,DWORD PTR [ecx+0x4]
        push  0x5
        lea  esi,[eax+ebx*1]
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4b8],ax
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x6
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4ba],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_00410997:
        imul  eax,eax,0x210
        cmp  ecx,0xfffffda8
    loc_004109A3:
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        lea  esi,[eax+ebx*1]
        jl loc_004109ED
        push  0x3
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4b8],ax
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x4
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4ba],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_004109ED:
        push  0x1
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4b8],ax
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  WORD PTR [esi+0x4ba],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  edi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  DWORD PTR [esp+0x30],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x3
        call FUN_0044fdb0
        mov  DWORD PTR [esp+0x10],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x4
        call FUN_0044fdb0
        imul  esi,esi,0x210
        mov  edx,DWORD PTR ds:0x474c98
        mov  ecx,eax
        mov  eax,DWORD PTR [esp+0x10]
        sub  eax,edi
        add  edx,0x400
        imul  eax,edx
        cdq
        and  edx,0x7ff
        add  eax,edx
        sar  eax,0xb
        add  eax,edi
        mov  WORD PTR [esi+ebx*1+0x4b8],ax
        mov  edx,DWORD PTR ds:0x474c98
        add  esi,ebx
        mov  eax,ecx
        mov  ecx,DWORD PTR [esp+0x30]
        sub  eax,ecx
        add  edx,0x400
        imul  eax,edx
        cdq
        and  edx,0x7ff
        add  eax,edx
        sar  eax,0xb
        add  eax,ecx
        mov  WORD PTR [esi+0x4ba],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        imul  esi,esi,0x210
        mov  WORD PTR [esi+ebx*1+0x4bc],ax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        imul  eax,eax,0x210
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        push  0x1
        lea  esi,[eax+ebx*1]
        call FUN_0044fdb0
        mov  DWORD PTR [esi+0x4c4],eax
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  DWORD PTR [esi+0x4c8],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        imul  esi,esi,0x16
        mov  ecx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ecx+0x4]
        lea  edi,[esi+eax*1]
        lea  eax,[edi+edi*2]
        push  0x2
        lea  esi,[ebx+eax*8]
        call FUN_0044fdb0
        mov  DWORD PTR [esi+0x2f8],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x3
        call FUN_0044fdb0
        mov  DWORD PTR [esi+0x2f4],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x4
        call FUN_0044fdb0
        mov  DWORD PTR [esi+0x2ec],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x5
        call FUN_0044fdb0
        mov  DWORD PTR [esi+0x2f0],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x6
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x2e4]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x7
        call FUN_0044fe40
        lea  ecx,[edi+edi*2+0x5d]
        fstp  DWORD PTR [ebx+ecx*8]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        push  0x0
        lea  eax,[ebx+0x11c]
        call FUN_00405410
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  DWORD PTR [esp+0x10],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  edi,DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x10]
        push  esi
        mov  esi,DWORD PTR [ebx+0x14d8]
        add  edi,0x20
        mov  edx,eax
        call FUN_00412720
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  edx,DWORD PTR [ebx+0x14d8]
        add  eax,0x24a
        add  esi,0x18
        shl  eax,0x4
        mov  DWORD PTR [eax+edx*1],esi
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  ebx,DWORD PTR ds:0x4776f0
        push  0x1
        call FUN_00408210
        mov  eax,ds:0x47781c
        mov  ebx,0x1
        call FUN_0041c850
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  ecx,DWORD PTR [ebx+0x2c]
        push  ecx
        mov  ebx,eax
        mov  esi,0x492590
        call FUN_0043dd10
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  esi,eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x0
        push  esi
        push  eax
        push  0x0
        call FUN_0044fdb0
        push  eax
        push  0x1
        mov  ebx,0x31
        call FUN_0043c8b0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  edi,DWORD PTR ds:0x47770c
        mov  esi,eax
        call FUN_00415db0
        mov  ebx,DWORD PTR ds:0x4776f0
        push  0x0
        call FUN_00408210
        mov  eax,ds:0x47781c
        xor  ebx,ebx
        call FUN_0041c850
        mov  edx,DWORD PTR ds:0x477704
        push  edx
        call FUN_0040e6a0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x47770c
        mov  eax,DWORD PTR [eax+0x9eb8]
        test  eax,eax
        je loc_00411D18
        mov  ecx,DWORD PTR [eax+0x78]
        test  ecx,ecx
        jne loc_00411D18
        or   eax,0xffffffff
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x10]
        test  eax,eax
        je loc_00411D18
        or   eax,0xffffffff
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        lea  ecx,[esi+0x20]
        mov  esi,DWORD PTR [esi+0x1c]
        xor  edi,edi
        test  esi,esi
        mov  al,0x77
        mov  BYTE PTR [esp+0x3b],0x7
        mov  DWORD PTR [esp+0x30],esi
        jle loc_00410EC8
        lea  esi,[esp+0x248]
        sub  ecx,esi
        mov  DWORD PTR [esp+0x10],ecx
        nop
    loc_00410EA0:
        mov  ecx,DWORD PTR [esp+0x10]
        lea  esi,[esp+edi*1+0x248]
        mov  cl,BYTE PTR [ecx+esi*1]
        xor  cl,al
        mov  BYTE PTR [esi],cl
        mov  cl,BYTE PTR [esp+0x3b]
        add  al,cl
        add  cl,0x10
        mov  BYTE PTR [esp+0x3b],cl
        mov  ecx,DWORD PTR [esp+0x30]
        inc  edi
        cmp  edi,ecx
        jl loc_00410EA0
    loc_00410EC8:
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  edx,DWORD PTR [esp+0x1c]
        mov  esi,eax
        movsx eax,WORD PTR [edx+0x4]
        sub  eax,0x165
        je loc_00410F00
        dec  eax
        je loc_00410EF4
        dec  eax
        jne loc_00410F06
        mov  eax,ds:0x474c74
        lea  esi,[esi+eax*1-0x2]
        jmp loc_00410F06
    loc_00410EF4:
        mov  ecx,DWORD PTR ds:0x474c74
        lea  esi,[esi+ecx*1-0x1]
        jmp loc_00410F06
    loc_00410F00:
        add  esi,DWORD PTR ds:0x474c74
    loc_00410F06:
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0x1
        mov  DWORD PTR [esp+0x14],eax
        call FUN_0044fdb0
        push  eax
        mov  eax,ds:0x4776f4
        lea  edx,[esp+0x24c]
        push  edx
        push  esi
        push  eax
        call FUN_00409280
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x4776f4
        call FUN_00409c00
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x4776f4
        or   DWORD PTR [eax+0x378c],0x8
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  esi,DWORD PTR ds:0x4776f4
        call FUN_0040cea0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  edx,DWORD PTR [edx+0x4]
        push  0x0
        call FUN_0044fdb0
        mov  esi,DWORD PTR [ebx+0x1444]
        shl  eax,0x13
        xor  eax,esi
        and  eax,0x80000
        mov  ecx,esi
        xor  ecx,eax
        mov  DWORD PTR [ebx+0x1444],ecx
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  eax,eax
        cmp  WORD PTR [esp+0x10],0x1af
        mov  ecx,0x77
        lea  edi,[esp+0x50]
        rep stosd
        jne loc_0041101E
        lea  esi,[ebx+0x2e4]
        mov  ecx,0x6c
        lea  edi,[esp+0x7c]
        rep movsd
    loc_0041101E:
        fld  DWORD PTR [ebx+0x1344]
        push  0x0
        fadd  DWORD PTR [ebx+0x2c]
        fstp  DWORD PTR [esp+0x28]
        mov  ecx,DWORD PTR [esp+0x28]
        fld  DWORD PTR [ebx+0x1348]
        mov  DWORD PTR [esp+0x54],ecx
        fadd  DWORD PTR [ebx+0x30]
        fstp  DWORD PTR [esp+0x2c]
        mov  eax,DWORD PTR [esp+0x2c]
        fld  DWORD PTR [ebx+0x134c]
        mov  DWORD PTR [esp+0x58],eax
        fadd  DWORD PTR [ebx+0x34]
        fstp  DWORD PTR [esp+0x30]
        mov  ecx,DWORD PTR [esp+0x30]
        mov  DWORD PTR [esp+0x5c],ecx
        mov  edx,DWORD PTR [edx+0x4]
        call FUN_0044fdb0
        mov  WORD PTR [esp+0x74],ax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x1
        call FUN_0044fdb0
        mov  WORD PTR [esp+0x76],ax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x5c]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x70]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x4
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x64]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x5
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x60]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x6
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x68]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x7
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x6c]
        mov  ecx,DWORD PTR [esp+0x78]
        mov  esi,DWORD PTR ds:0x47781c
        or   ecx,0x1
        push  0x0
        lea  edi,[esp+0x54]
        mov  DWORD PTR [esp+0x7c],ecx
        call FUN_0041c510
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  eax,eax
        mov  ecx,0x7e
        lea  edi,[esp+0x50]
        rep stosd
        xor  ecx,ecx
        mov  eax,ebx
        mov  DWORD PTR [esp+0x7c],0x41000000
        call FUN_00412a10
        cmp  WORD PTR [esi+0x4],0x1b0
        mov  DWORD PTR [esp+0x10],eax
        jne loc_0041117C
        lea  esi,[ebx+0x2e4]
        mov  ecx,0x6c
        lea  edi,[esp+0x98]
        rep movsd
    loc_0041117C:
        fld  DWORD PTR [ebx+0x1344]
        push  0x1
        fadd  DWORD PTR [ebx+0x2c]
        fstp  DWORD PTR [esp+0x28]
        mov  edx,DWORD PTR [esp+0x28]
        fld  DWORD PTR [ebx+0x1348]
        mov  DWORD PTR [esp+0x54],edx
        fadd  DWORD PTR [ebx+0x30]
        fstp  DWORD PTR [esp+0x2c]
        mov  eax,DWORD PTR [esp+0x2c]
        fld  DWORD PTR [ebx+0x134c]
        mov  DWORD PTR [esp+0x58],eax
        fadd  DWORD PTR [ebx+0x34]
        mov  eax,DWORD PTR [ebx+0x14d8]
        fstp  DWORD PTR [esp+0x30]
        mov  ecx,DWORD PTR [esp+0x30]
        mov  DWORD PTR [esp+0x5c],ecx
        mov  edx,DWORD PTR [eax+0x4]
        call FUN_0044fdb0
        mov  WORD PTR [esp+0x90],ax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x2
        call FUN_0044fdb0
        mov  WORD PTR [esp+0x92],ax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x68]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x4
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x74]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x5
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x70]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x6
        call FUN_0044fdb0
        mov  DWORD PTR [esp+0x80],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x7
        call FUN_0044fdb0
        mov  DWORD PTR [esp+0x84],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x8
        call FUN_0044fdb0
        mov  DWORD PTR [esp+0x88],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [eax+0x4]
        push  0x9
        call FUN_0044fdb0
        mov  DWORD PTR [esp+0x8c],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0xa
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x78]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  edx,DWORD PTR [ebx+0x4]
        push  0xb
        call FUN_0044fdb0
        mov  esi,DWORD PTR ds:0x47781c
        or   eax,0x2
        push  0x1
        lea  edi,[esp+0x54]
        mov  DWORD PTR [esp+0x98],eax
        call FUN_0041c510
        mov  ecx,DWORD PTR [esp+0x10]
        test  ecx,ecx
        je loc_00411D18
        mov  edx,ecx
        mov  DWORD PTR [edx],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  eax,eax
        cmp  WORD PTR [esp+0x10],0x1b1
        mov  ecx,0x77
        lea  edi,[esp+0x50]
        rep stosd
        jne loc_0041131C
        lea  esi,[ebx+0x2e4]
        mov  ecx,0x6c
        lea  edi,[esp+0x7c]
        rep movsd
    loc_0041131C:
        fld  DWORD PTR [ebx+0x1344]
        fadd  DWORD PTR [ebx+0x2c]
        fstp  DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [esp+0x24]
        fld  DWORD PTR [ebx+0x1348]
        mov  DWORD PTR [esp+0x50],eax
        fadd  DWORD PTR [ebx+0x30]
        mov  eax,ebx
        fstp  DWORD PTR [esp+0x28]
        mov  ecx,DWORD PTR [esp+0x28]
        fld  DWORD PTR [ebx+0x134c]
        mov  DWORD PTR [esp+0x54],ecx
        fadd  DWORD PTR [ebx+0x34]
        xor  ecx,ecx
        fstp  DWORD PTR [esp+0x2c]
        mov  edx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [esp+0x58],edx
        call FUN_00412a00
        mov  WORD PTR [esp+0x74],ax
        mov  ecx,0x1
        mov  eax,ebx
        call FUN_00412a00
        mov  WORD PTR [esp+0x76],ax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x5c]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x70]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x4
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x64]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x5
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x60]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x6
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x68]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x7
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x6c]
        mov  ecx,DWORD PTR [esp+0x78]
        mov  esi,DWORD PTR ds:0x47781c
        and  ecx,0xfffffffe
        push  0x0
        lea  edi,[esp+0x54]
        mov  DWORD PTR [esp+0x7c],ecx
        call FUN_0041c510
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        lea  edx,[esp+0x50]
        call FUN_0040cf40
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a10
        cmp  WORD PTR [esi+0x4],0x1b2
        mov  DWORD PTR [esp+0x10],eax
        jne loc_00411469
        lea  esi,[ebx+0x2e4]
        mov  ecx,0x6c
        lea  edi,[esp+0x98]
        rep movsd
    loc_00411469:
        fld  DWORD PTR [ebx+0x1344]
        fadd  DWORD PTR [ebx+0x2c]
        fstp  DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [esp+0x24]
        fld  DWORD PTR [ebx+0x1348]
        mov  DWORD PTR [esp+0x50],eax
        fadd  DWORD PTR [ebx+0x30]
        mov  eax,ebx
        fstp  DWORD PTR [esp+0x28]
        mov  ecx,DWORD PTR [esp+0x28]
        fld  DWORD PTR [ebx+0x134c]
        mov  DWORD PTR [esp+0x54],ecx
        fadd  DWORD PTR [ebx+0x34]
        mov  ecx,0x1
        fstp  DWORD PTR [esp+0x2c]
        mov  edx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [esp+0x58],edx
        call FUN_00412a00
        mov  WORD PTR [esp+0x90],ax
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_00412a00
        mov  WORD PTR [esp+0x92],ax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x3
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x68]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x4
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x74]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x5
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x70]
        mov  ecx,0x6
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esp+0x80],eax
        mov  ecx,0x7
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esp+0x84],eax
        mov  ecx,0x8
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esp+0x88],eax
        mov  ecx,0x9
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esp+0x8c],eax
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0xa
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x78]
        mov  ecx,0xb
        mov  eax,ebx
        call FUN_00412a00
        mov  esi,DWORD PTR ds:0x47781c
        and  eax,0xfffffffd
        push  0x1
        lea  edi,[esp+0x54]
        mov  DWORD PTR [esp+0x98],eax
        call FUN_0041c510
        mov  ecx,DWORD PTR [esp+0x10]
        test  ecx,ecx
        je loc_00411D18
        mov  DWORD PTR [ecx],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  ecx,eax
        mov  eax,ds:0x47781c
        call FUN_0040cf90
        mov  esi,eax
        test  esi,esi
        je loc_00411D18
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x24]
        mov  edx,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x24]
        add  esi,0x24
        mov  DWORD PTR [esi],eax
        mov  ecx,edx
        mov  DWORD PTR [esp+0x28],edx
        mov  DWORD PTR [esp+0x2c],0x0
        mov  edx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [esi+0x4],ecx
        mov  DWORD PTR [esi+0x8],edx
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  ecx,eax
        mov  eax,ds:0x47781c
        call FUN_0040cf90
        mov  esi,eax
        test  esi,esi
        je loc_00411D18
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0x28],eax
        lea  eax,[esp+0x24]
        mov  ecx,esi
        mov  DWORD PTR [esp+0x2c],0x0
        call FUN_0040cf60
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  ecx,eax
        mov  eax,ds:0x47781c
        call FUN_0040cf90
        mov  esi,eax
        test  esi,esi
        je loc_00411D18
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x48]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  ecx,eax
        mov  eax,ds:0x47781c
        call FUN_0040cf90
        mov  esi,eax
        test  esi,esi
        je loc_00411D18
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x44]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  ecx,eax
        mov  eax,ds:0x47781c
        call FUN_0040cf90
        mov  esi,eax
        test  esi,esi
        je loc_00411D18
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x3c]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  ecx,eax
        mov  eax,ds:0x47781c
        call FUN_0040cf90
        mov  esi,eax
        test  esi,esi
        je loc_00411D18
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esi+0x440]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  esi,DWORD PTR [esp+0x10]
        mov  eax,ds:0x4776f0
        push  0x0
        push  0x1
        add  ebx,0x2c
        push  esi
        call FUN_00408100
        mov  eax,ds:0x47781c
        push  0x1
        push  esi
        call FUN_0041c800
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  esi,DWORD PTR [esp+0x10]
        mov  eax,ds:0x4776f0
        push  0x0
        push  0x0
        add  ebx,0x2c
        push  esi
        call FUN_00408100
        mov  eax,ds:0x47781c
        push  0x0
        push  esi
        call FUN_0041c800
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  ecx,eax
        mov  eax,0x474c40
        call FUN_00412ed0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x474c98
        cmp  eax,0x200
        jl loc_004118D4
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x2
        jmp loc_00411951
    loc_004118D4:
        xor  ecx,ecx
        cmp  eax,0xfffffe00
        mov  eax,DWORD PTR [edx+0x4]
        jg loc_00411951
        jmp loc_0041190C
        mov  eax,ds:0x474c98
        cmp  eax,0x258
        jge loc_00410114
        cmp  eax,0xc8
        jge loc_00410107
        cmp  eax,0xffffff38
        jl loc_00411942
        mov  ecx,0x2
    loc_00411909:
        mov  eax,DWORD PTR [edx+0x4]
    loc_0041190C:
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        xor  ecx,ecx
        call FUN_00450070
        mov  edx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax],edx
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_00411942:
        cmp  eax,0xfffffe70
        mov  eax,DWORD PTR [edx+0x4]
        jl loc_00411987
    loc_0041194C:
        mov  ecx,0x1
    loc_00411951:
        call FUN_0044fe40
    loc_00411956:
        mov  ebx,DWORD PTR [ebx+0x14d8]
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x4]
        xor  ecx,ecx
        call FUN_00450070
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax],ecx
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_00411987:
        xor  ecx,ecx
        jmp loc_0041190C
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x1
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x30]
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        xor  ecx,ecx
        call FUN_00450070
        fild  DWORD PTR ds:0x474c98
        fadd  DWORD PTR ds:0x470d4c
        fld  DWORD PTR [esp+0x30]
        fsub  DWORD PTR [esp+0x10]
        fmulp st(1),st
        fmul  DWORD PTR ds:0x470d48
        fadd  DWORD PTR [esp+0x10]
        fstp  DWORD PTR [eax]
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x474c98
        cmp  eax,0x200
        jge loc_00411AB8
        xor  ecx,ecx
        cmp  eax,0xfffffe00
        mov  eax,ebx
    loc_00411A15:
        call FUN_00412a10
        mov  esi,eax
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esi],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x474c98
        cmp  eax,0x258
        jl loc_00411A7A
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a10
        mov  esi,eax
        mov  ecx,0x4
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esi],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_00411A7A:
        cmp  eax,0xc8
        jl loc_00411AB1
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a10
        mov  esi,eax
        mov  ecx,0x3
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esi],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_00411AB1:
        cmp  eax,0xffffff38
        jl loc_00411AE8
    loc_00411AB8:
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a10
        mov  esi,eax
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esi],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_00411AE8:
        xor  ecx,ecx
        cmp  eax,0xfffffe70
        mov  eax,ebx
        jl loc_00411A15
        call FUN_00412a10
        mov  esi,eax
        mov  ecx,0x1
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esi],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  ecx,0x1
        mov  eax,ebx
        call FUN_00412a00
        mov  esi,eax
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_00412a00
        mov  edi,eax
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a10
        mov  edx,DWORD PTR ds:0x474c98
        mov  ecx,eax
        add  edx,0x400
        mov  eax,edi
        sub  eax,esi
        imul  eax,edx
        cdq
        and  edx,0x7ff
        add  eax,edx
        sar  eax,0xb
        add  eax,esi
        mov  DWORD PTR [ecx],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  ecx,DWORD PTR ds:0x47770c
        mov  DWORD PTR [ecx+0x9e90],eax
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,ds:0x47781c
        call FUN_0041c7d0
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  esi,DWORD PTR [ebx+0x1444]
        shl  eax,0x14
        xor  eax,esi
        and  eax,0x100000
        mov  ecx,esi
        xor  ecx,eax
        mov  DWORD PTR [ebx+0x1444],ecx
        mov  ecx,0x1
        mov  eax,ebx
        call FUN_00412a00
        mov  edx,DWORD PTR [ebx+0xf4]
        mov  DWORD PTR [ebx+0x1448],eax
        and  DWORD PTR [ebx+0x1444],0xffdfffff
        mov  DWORD PTR [ebx+0x144c],edx
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  eax,DWORD PTR [edx+0x4]
        xor  ecx,ecx
        call FUN_0044fe40
        fstp  DWORD PTR ds:0x476f78
        xor  eax,eax
        pop  edi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x2c0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
        mov  esi,DWORD PTR ds:0x477834
        mov  eax,DWORD PTR [edx+0x4]
        mov  ecx,0x1
        add  esi,0x3c0
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0x14d8]
        mov  edi,DWORD PTR ds:0x477834
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        add  edi,0x3c0
        call FUN_0044fe40
        fsubr DWORD PTR [edi+0x4]
        fld  DWORD PTR [esi]
        fsub  DWORD PTR [esp+0x10]
        fpatan
        jmp loc_00411956
        mov  eax,ds:0x474c74
        test  eax,eax
        jne loc_00411CC2
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esp+0x10],eax
        fild  DWORD PTR [esp+0x10]
        jmp loc_00411D07
    loc_00411CC2:
        cmp  eax,0x1
        jne loc_00411CDA
        mov  ecx,eax
        mov  eax,ebx
        call FUN_00412a00
        mov  DWORD PTR [esp+0x10],eax
        fild  DWORD PTR [esp+0x10]
        jmp loc_00411D07
    loc_00411CDA:
        cmp  eax,0x2
        mov  eax,ebx
        jne loc_00411CF5
        mov  ecx,0x2
        call FUN_00412a00
        mov  DWORD PTR [esp+0x10],eax
        fild  DWORD PTR [esp+0x10]
        jmp loc_00411D07
    loc_00411CF5:
        mov  ecx,0x3
        call FUN_00412a00
        mov  DWORD PTR [esp+0x10],eax
        fild  DWORD PTR [esp+0x10]
    loc_00411D07:
        mov  ebx,DWORD PTR [ebx+0x14d8]
        mov  eax,DWORD PTR [ebx+0x4]
        fld  DWORD PTR [eax]
        fsub  st,st(1)
        fstp  DWORD PTR [eax]
    loc_00411D16:
        fstp  st(0)
    loc_00411D18:
        mov  ecx,DWORD PTR [esp+0x2cc]
        pop  edi
        pop  esi
        xor  ecx,ebp
        xor  eax,eax
        pop  ebx
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    }
}

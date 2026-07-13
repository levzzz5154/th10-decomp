// 0042CDF0: FUN_0042cdf0
// Original size: 1296 bytes, actual code: 386 instructions
extern "C" void FUN_00409e50(void);
extern "C" void FUN_00420a90(void);
extern "C" void FUN_00420b10(void);
extern "C" void FUN_00420c00(void);
extern "C" void FUN_004294a0(void);
extern "C" void FUN_004296f0(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0042d300(void);
extern "C" void FUN_0042d420(void);
extern "C" void FUN_0042d920(void);
extern "C" void FUN_0042f540(void);
extern "C" void FUN_00430320(void);
extern "C" void FUN_004306a0(void);
extern "C" void FUN_00430a60(void);
extern "C" void FUN_00430ff0(void);
extern "C" void FUN_00431410(void);
extern "C" void FUN_004315c0(void);
extern "C" void FUN_00431ba0(void);
extern "C" void FUN_00431ee0(void);
extern "C" void FUN_004329f0(void);
extern "C" void FUN_00432cb0(void);
extern "C" void FUN_00433230(void);
extern "C" void FUN_00433570(void);
extern "C" void FUN_00433b30(void);
extern "C" void FUN_00433ef0(void);
extern "C" void FUN_004493e0(void);
extern "C" void FUN_0044be20(void);
extern "C" void _free(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0042cdf0(void) {
    __asm {
    loc_0042CDF0:
        push  ebx
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x1c]
        cmp  eax,0x1
        push  esi
        push  edi
        je loc_0042CE02
        cmp  eax,0x2
        jne loc_0042CE25
    loc_0042CE02:
        mov  ecx,DWORD PTR ds:0x474ca4
        mov  eax,ds:0x474e30
        inc  ecx
        test  eax,0x160b
        mov  DWORD PTR ds:0x474ca4,ecx
        je loc_0042CE3E
        mov  DWORD PTR ds:0x474ca4,0x0
    loc_0042CE25:
        mov  edi,DWORD PTR ds:0x491c00
    loc_0042CE2B:
        mov  eax,DWORD PTR [ebx+0x1c]
        cmp  eax,0x10
        ja loc_0042D19F
        jmp  DWORD PTR [eax*4+0x42d214]
    loc_0042CE3E:
        cmp  DWORD PTR ds:0x474ca4,0x384
        jl loc_0042CE25
        mov  eax,ds:0x474ca0
        mov  ecx,DWORD PTR ds:0x474ca8
        and  eax,0xffffffbf
        or   eax,0x20
        mov  ds:0x474ca0,eax
        mov  eax,DWORD PTR [ecx*4+0x476ff8]
        mov  edx,0x477710
        sub  edx,eax
        mov  edi,edi
    loc_0042CE70:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_0042CE70
        push  0x477710
        call FUN_004296f0
        mov  edx,DWORD PTR ds:0x474ca8
        inc  edx
        and  edx,0x80000003
        mov  esi,eax
        jns loc_0042CE9A
        dec  edx
        or   edx,0xfffffffc
        inc  edx
    loc_0042CE9A:
        mov  DWORD PTR ds:0x474ca8,edx
        xor  eax,eax
        lea  ecx,[esi+0xb0]
    loc_0042CEA8:
        cmp  DWORD PTR [ecx],0x0
        jne loc_0042CEB6
        inc  eax
        add  ecx,0x24
        cmp  eax,0x8
        jl loc_0042CEA8
    loc_0042CEB6:
        lea  ecx,[eax+eax*2]
        mov  ds:0x474c7c,eax
        mov  ds:0x474c80,eax
        mov  DWORD PTR ds:0x491fb8,0xc
        mov  eax,DWORD PTR [esi+0x18]
        mov  edx,DWORD PTR [eax+0x50]
        shl  ecx,0x4
        add  ecx,0x474788
        mov  DWORD PTR ds:0x474c68,edx
        mov  edx,DWORD PTR ds:0x474c74
        mov  DWORD PTR ds:0x477848,ecx
        mov  ecx,DWORD PTR [eax+0x54]
        mov  DWORD PTR ds:0x474c6c,ecx
        mov  DWORD PTR ds:0x474c78,edx
        mov  eax,DWORD PTR [eax+0x58]
        push  esi
        mov  ds:0x474c74,eax
        call FUN_004294a0
        push  esi
        call _free
        mov  eax,DWORD PTR [ebx+0x1c]
        xor  ecx,ecx
        add  esp,0x4
        cmp  eax,0x1
        setne cl
        mov  DWORD PTR ds:0x474ca4,0x0
        mov  edi,ecx
        mov  DWORD PTR ds:0x491c00,edi
        jmp loc_0042CE2B
        mov  esi,DWORD PTR ds:0x491c10
        mov  edx,DWORD PTR [esi+0x3ad084]
        mov  eax,esi
        call FUN_004493e0
        mov  edx,DWORD PTR [esi+0x3ad088]
        mov  eax,esi
        call FUN_004493e0
        mov  edx,DWORD PTR [esi+0x3ad074]
        mov  eax,esi
        call FUN_004493e0
        mov  edx,DWORD PTR [esi+0x3ad078]
        mov  eax,esi
        call FUN_004493e0
        mov  edx,DWORD PTR [esi+0x3ad06c]
        mov  eax,esi
        call FUN_004493e0
        mov  esi,DWORD PTR ds:0x4776e0
        add  esi,0x89a4
        mov  eax,esi
        call FUN_00409e50
        cmp  edi,0x3
        mov  DWORD PTR [esi],0x0
        jne loc_0042D00A
        lea  eax,[ebx+0x24]
        mov  DWORD PTR [ebx+0x2c],0xa
        mov  ecx,DWORD PTR [eax+0x8]
        test  ecx,ecx
        je loc_0042CFB9
        jg loc_0042CFB3
        dec  ecx
        mov  DWORD PTR [eax],ecx
        jmp loc_0042CFBF
    loc_0042CFB3:
        xor  ecx,ecx
        mov  DWORD PTR [eax],ecx
        jmp loc_0042CFBF
    loc_0042CFB9:
        mov  DWORD PTR [eax],0x0
    loc_0042CFBF:
        call FUN_0044be20
        mov  ecx,0xf
        mov  eax,ebx
        call FUN_0042c5c0
        push  ebx
        mov  edi,0x5b
        call FUN_0042c670
        mov  esi,0x9
        mov  ecx,edi
        mov  eax,ebx
        call FUN_0042c770
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,DWORD PTR [eax+0x4]
        or   ecx,0x2
        mov  DWORD PTR ds:0x491c00,0x1
        mov  DWORD PTR [eax+0x4],ecx
        push  ebx
        call FUN_00432cb0
        jmp loc_0042D19F
    loc_0042D00A:
        test  BYTE PTR ds:0x474ca0,0x20
        jne loc_0042D030
        push  0x46f018
        push  0x0
        call FUN_00420a90
        push  0x0
        push  0x0
        call FUN_00420b10
        mov  edi,DWORD PTR ds:0x491c00
        jmp loc_0042D03C
    loc_0042D030:
        mov  edx,DWORD PTR ds:0x474c78
        mov  DWORD PTR ds:0x474c74,edx
    loc_0042D03C:
        mov  ecx,DWORD PTR ds:0x474ca0
        and  ecx,0xffffffdf
        test  edi,edi
        mov  DWORD PTR ds:0x474ca0,ecx
        jne loc_0042D06F
        mov  ecx,0x1
        mov  eax,ebx
        call FUN_0042c5c0
        mov  DWORD PTR ds:0x491c00,0x1
    loc_0042D065:
        call FUN_0042d300
        jmp loc_0042D19F
    loc_0042D06F:
        cmp  edi,0x1
        jne loc_0042D0C7
        cmp  DWORD PTR ds:0x474c74,0x4
        jne loc_0042D09F
        mov  eax,DWORD PTR [ebx+0x2c]
        test  eax,eax
        je loc_0042D098
        cmp  eax,edi
        jg loc_0042D08E
        dec  eax
        mov  DWORD PTR [ebx+0x24],eax
        jmp loc_0042D09F
    loc_0042D08E:
        mov  eax,0x1
        mov  DWORD PTR [ebx+0x24],eax
        jmp loc_0042D09F
    loc_0042D098:
        mov  DWORD PTR [ebx+0x24],0x1
    loc_0042D09F:
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_0042c5c0
        push  ebx
        mov  edi,0x5b
        call FUN_0042c670
        mov  eax,DWORD PTR [ebx+0x10]
        or   DWORD PTR [eax+0x4],0x2
        call FUN_0042d420
        jmp loc_0042D19F
    loc_0042D0C7:
        cmp  edi,0x2
        jne loc_0042D065
        lea  eax,[ebx+0x24]
        mov  DWORD PTR [ebx+0x2c],0xa
        mov  ecx,DWORD PTR [eax+0x8]
        test  ecx,ecx
        je loc_0042D0F0
        cmp  ecx,0x3
        jg loc_0042D0E7
        dec  ecx
        mov  DWORD PTR [eax],ecx
        jmp loc_0042D0F6
    loc_0042D0E7:
        mov  ecx,0x3
        mov  DWORD PTR [eax],ecx
        jmp loc_0042D0F6
    loc_0042D0F0:
        mov  DWORD PTR [eax],0x3
    loc_0042D0F6:
        call FUN_0044be20
        mov  ecx,0xc
        mov  eax,ebx
        call FUN_0042c5c0
        push  ebx
        mov  edi,0x5b
        call FUN_0042c670
        mov  esi,0x9
        mov  ecx,edi
        mov  eax,ebx
        call FUN_0042c770
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,DWORD PTR [eax+0x4]
        or   ecx,0x2
        mov  DWORD PTR ds:0x491c00,0x1
        mov  DWORD PTR [eax+0x4],ecx
        push  ebx
        call FUN_004315c0
        jmp loc_0042D19F
        push  ebx
        call FUN_0042d920
        jmp loc_0042D19F
        call FUN_0042f540
        jmp loc_0042D19F
        mov  eax,ds:0x491ff4
        shr  eax,0xc
        not  eax
        and  eax,0x1
        or   eax,0x2
        mov  ds:0x491fb8,eax
        call FUN_00420c00
        jmp loc_0042D19F
        push  ebx
        call FUN_00430320
        jmp loc_0042D19F
        push  ebx
        call FUN_004306a0
        jmp loc_0042D19F
        push  ebx
        call FUN_00430a60
        jmp loc_0042D19F
        push  ebx
        call FUN_00430ff0
        jmp loc_0042D19F
        push  ebx
        call FUN_00433ef0
        jmp loc_0042D19F
        push  ebx
        call FUN_00431ee0
        jmp loc_0042D19F
        push  ebx
        call FUN_00433570
    loc_0042D19F:
        mov  edx,DWORD PTR [ebx+0x2b4]
        mov  ecx,DWORD PTR [ebx+0x2bc]
        mov  DWORD PTR [ebx+0x2b0],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_0042D1F1
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_0042D1F1
        fld  DWORD PTR [ebx+0x2b8]
        pop  edi
        fadd  DWORD PTR ds:0x470afc
        inc  edx
        pop  esi
        mov  DWORD PTR [ebx+0x2b4],edx
        fstp  DWORD PTR [ebx+0x2b8]
        mov  eax,0x1
        pop  ebx
        ret
    loc_0042D1F1:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebx+0x2b8]
        fst  DWORD PTR [ebx+0x2b8]
        call FUN_00463b2c
        pop  edi
        mov  DWORD PTR [ebx+0x2b4],eax
        pop  esi
        mov  eax,0x1
        pop  ebx
        ret
    }
}

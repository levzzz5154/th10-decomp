// 00418190: FUN_00418190
// Original size: 1664 bytes, actual code: 461 instructions
extern "C" void FUN_00402440(void);
extern "C" void FUN_00404450(void);
extern "C" void FUN_00404530(void);
extern "C" void FUN_004045b0(void);
extern "C" void FUN_00404ed0(void);
extern "C" void FUN_00405410(void);
extern "C" void FUN_00405ed0(void);
extern "C" void FUN_00409e50(void);
extern "C" void FUN_00409f90(void);
extern "C" void FUN_0040ac90(void);
extern "C" void FUN_0040cfb0(void);
extern "C" void FUN_00413bc0(void);
extern "C" void FUN_00417040(void);
extern "C" void FUN_00417770(void);
extern "C" void FUN_00418a00(void);
extern "C" void FUN_00420b10(void);
extern "C" void FUN_00424d90(void);
extern "C" void FUN_00426f70(void);
extern "C" void FUN_0042a450(void);
extern "C" void FUN_0043c8b0(void);
extern "C" void FUN_0043e460(void);
extern "C" void FUN_0044c150(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00418190(void) {
    __asm {
        sub  esp,0x40
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  edi,DWORD PTR [esp+0x54]
        mov  eax,DWORD PTR [edi+0x14]
        xor  ebp,ebp
        cmp  eax,ebp
        jne loc_0041840B
        test  BYTE PTR [edi+0x58],0x8
        je loc_004181DC
        mov  esi,0x492254
        call FUN_0044c150
        mov  eax,ds:0x491ff4
        shr  eax,0xc
        not  eax
        pop  edi
        and  eax,0x1
        pop  esi
        or   eax,0x2
        pop  ebp
        mov  ds:0x491fb8,eax
        mov  eax,0x1
        pop  ebx
        add  esp,0x40
        ret  0x4
    loc_004181DC:
        mov  ecx,DWORD PTR ds:0x4776e8
        push  ecx
        call FUN_00404450
        mov  esi,DWORD PTR ds:0x4776e4
        cmp  esi,ebp
        je loc_0041821C
        call FUN_00404530
        mov  eax,ds:0x4776e8
        call FUN_004045b0
        or   DWORD PTR [edi+0x58],0x800
        mov  eax,ds:0x47770c
        add  eax,0x9e14
        call FUN_00409e50
        jmp loc_00418622
    loc_0041821C:
        mov  ebx,DWORD PTR [edi+0x58]
        mov  esi,DWORD PTR ds:0x4776f0
        and  ebx,0xfffff7ff
        mov  DWORD PTR [edi+0x58],ebx
        call FUN_00405ed0
        mov  esi,DWORD PTR ds:0x477834
        call FUN_00424d90
        mov  edi,DWORD PTR ds:0x477818
        mov  edx,DWORD PTR ds:0x477704
        xor  eax,eax
        mov  ecx,0x873a8
        add  edi,0x14
        push  edx
        rep stosd
        call FUN_00409f90
        mov  eax,ds:0x47781c
        call FUN_00417770
        mov  ebx,DWORD PTR ds:0x477838
        mov  DWORD PTR ds:0x474c88,ebp
        mov  DWORD PTR ds:0x474c8c,ebp
        call FUN_0042a450
        xor  eax,eax
        mov  ecx,0x10
        lea  edi,[esp+0x10]
        rep stosd
        mov  eax,ds:0x477704
        push  0x46d278
        push  eax
        lea  eax,[esp+0x18]
        call FUN_0040cfb0
        mov  edi,DWORD PTR ds:0x47770c
        call FUN_00413bc0
        mov  eax,ds:0x477830
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        mov  esi,0x2
        je loc_004182BD
        or   DWORD PTR [ecx+0x4],esi
    loc_004182BD:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_004182C9
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_004182C9:
        mov  eax,ds:0x477834
        mov  ecx,DWORD PTR [eax+0x8]
        or   DWORD PTR [ecx+0x4],esi
        mov  ecx,DWORD PTR [eax+0xc]
        mov  edi,DWORD PTR [ecx+0x4]
        or   edi,esi
        push  eax
        mov  DWORD PTR [ecx+0x4],edi
        call FUN_00426f70
        mov  eax,ds:0x4776f0
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_004182F4
        or   DWORD PTR [ecx+0x4],esi
    loc_004182F4:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_00418300
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_00418300:
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_0041830F
        or   DWORD PTR [ecx+0x4],esi
    loc_0041830F:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_0041831B
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_0041831B:
        mov  eax,ds:0x477818
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_0041832A
        or   DWORD PTR [ecx+0x4],esi
    loc_0041832A:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_00418336
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_00418336:
        mov  eax,ds:0x47781c
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_00418345
        or   DWORD PTR [ecx+0x4],esi
    loc_00418345:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_00418351
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_00418351:
        mov  ecx,DWORD PTR ds:0x4776fc
        mov  eax,DWORD PTR [ecx+0x8]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,DWORD PTR [ecx+0xc]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,ds:0x4776ec
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_00418372
        or   DWORD PTR [ecx+0x4],esi
    loc_00418372:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_0041837E
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_0041837E:
        mov  ecx,DWORD PTR ds:0x477840
        mov  eax,DWORD PTR [ecx+0x8]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,DWORD PTR [ecx+0xc]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,ds:0x4776f4
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_0041839F
        or   DWORD PTR [ecx+0x4],esi
    loc_0041839F:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_004183A9
        or   DWORD PTR [ecx+0x4],esi
    loc_004183A9:
        mov  eax,DWORD PTR [eax+0x37ac]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,ds:0x477814
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_004183C1
        or   DWORD PTR [ecx+0x4],esi
    loc_004183C1:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_004183CD
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_004183CD:
        test  BYTE PTR ds:0x474ca0,0x20
        jne loc_004183E6
        mov  ecx,DWORD PTR ds:0x477848
        mov  edx,DWORD PTR [ecx+0x24]
        push  edx
        push  ebp
        call FUN_00420b10
    loc_004183E6:
        mov  esi,DWORD PTR ds:0x4776e0
        lea  eax,[esi+0x89a0]
        call FUN_00409e50
        add  esi,0x89a4
        mov  eax,esi
        call FUN_00409e50
        mov  DWORD PTR [esi],ebp
        jmp loc_0041861E
    loc_0041840B:
        cmp  eax,0x1e
        jne loc_00418622
        mov  eax,DWORD PTR [edi+0x58]
        test  ah,0x8
        je loc_00418622
        mov  esi,DWORD PTR ds:0x4776f0
        and  eax,0xfffff7ff
        mov  DWORD PTR [edi+0x58],eax
        call FUN_00405ed0
        mov  esi,DWORD PTR ds:0x477834
        call FUN_00424d90
        mov  edi,DWORD PTR ds:0x477818
        xor  eax,eax
        mov  ecx,0x873a8
        add  edi,0x14
        rep stosd
        mov  eax,ds:0x477704
        push  eax
        call FUN_00409f90
        mov  eax,ds:0x47781c
        call FUN_00417770
        mov  ebx,DWORD PTR ds:0x477838
        mov  DWORD PTR ds:0x474c88,ebp
        mov  DWORD PTR ds:0x474c8c,ebp
        call FUN_0042a450
        xor  eax,eax
        mov  ecx,0x10
        lea  edi,[esp+0x10]
        rep stosd
        mov  ecx,DWORD PTR ds:0x477704
        push  0x46d278
        push  ecx
        lea  eax,[esp+0x18]
        call FUN_0040cfb0
        mov  edi,DWORD PTR ds:0x47770c
        call FUN_00413bc0
        mov  eax,ds:0x477830
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        mov  esi,0x2
        je loc_004184BD
        or   DWORD PTR [ecx+0x4],esi
    loc_004184BD:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_004184C9
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_004184C9:
        mov  eax,ds:0x477834
        mov  ecx,DWORD PTR [eax+0x8]
        or   DWORD PTR [ecx+0x4],esi
        mov  ecx,DWORD PTR [eax+0xc]
        mov  edi,DWORD PTR [ecx+0x4]
        or   edi,esi
        push  eax
        mov  DWORD PTR [ecx+0x4],edi
        call FUN_00426f70
        mov  eax,ds:0x4776f0
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_004184F4
        or   DWORD PTR [ecx+0x4],esi
    loc_004184F4:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_00418500
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_00418500:
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_0041850F
        or   DWORD PTR [ecx+0x4],esi
    loc_0041850F:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_0041851B
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_0041851B:
        mov  eax,ds:0x477818
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_0041852A
        or   DWORD PTR [ecx+0x4],esi
    loc_0041852A:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_00418536
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_00418536:
        mov  eax,ds:0x47781c
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_00418545
        or   DWORD PTR [ecx+0x4],esi
    loc_00418545:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_00418551
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_00418551:
        mov  ecx,DWORD PTR ds:0x4776fc
        mov  eax,DWORD PTR [ecx+0x8]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,DWORD PTR [ecx+0xc]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,ds:0x4776ec
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_00418572
        or   DWORD PTR [ecx+0x4],esi
    loc_00418572:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_0041857E
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_0041857E:
        mov  ecx,DWORD PTR ds:0x477840
        mov  eax,DWORD PTR [ecx+0x8]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,DWORD PTR [ecx+0xc]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,ds:0x4776f4
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_0041859F
        or   DWORD PTR [ecx+0x4],esi
    loc_0041859F:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_004185A9
        or   DWORD PTR [ecx+0x4],esi
    loc_004185A9:
        mov  eax,DWORD PTR [eax+0x37ac]
        or   DWORD PTR [eax+0x4],esi
        mov  eax,ds:0x477814
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebp
        je loc_004185C1
        or   DWORD PTR [ecx+0x4],esi
    loc_004185C1:
        mov  ecx,DWORD PTR [eax+0xc]
        cmp  ecx,ebp
        je loc_004185CD
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],esi
    loc_004185CD:
        test  BYTE PTR ds:0x491d78,0x10
        mov  edx,0x46df98
        push  ebp
        mov  eax,0x492590
        je loc_004185E5
        push  0x4
        jmp loc_004185E7
    loc_004185E5:
        push  0x3
    loc_004185E7:
        call FUN_0043e460
        mov  edx,DWORD PTR ds:0x477848
        mov  eax,DWORD PTR [edx+0x24]
        push  eax
        push  ebp
        call FUN_00420b10
        mov  esi,DWORD PTR ds:0x4776e0
        add  esi,0x89a4
        mov  eax,esi
        call FUN_00409e50
        mov  eax,DWORD PTR [esp+0x54]
        push  ebp
        add  eax,0x10
        mov  DWORD PTR [esi],ebp
        call FUN_00405410
    loc_0041861E:
        mov  edi,DWORD PTR [esp+0x54]
    loc_00418622:
        mov  esi,DWORD PTR ds:0x4776e4
        cmp  esi,ebp
        je loc_00418648
        test  BYTE PTR [esi+0x2a18],0x8
        je loc_00418648
        cmp  esi,ebp
        je loc_00418648
        push  esi
        call FUN_00402440
        push  esi
        call _free
        add  esp,0x4
    loc_00418648:
        mov  eax,DWORD PTR [edi+0x58]
        test  al,0x4
        je loc_00418666
        or   eax,0x80
        mov  DWORD PTR [edi+0x58],eax
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        add  esp,0x40
        ret  0x4
    loc_00418666:
        mov  esi,0x492254
        call FUN_0044c150
        test  BYTE PTR ds:0x474ca0,0x20
        je loc_004186D7
        test  DWORD PTR ds:0x474e30,0x160b
        jne loc_0041868B
        test  BYTE PTR [edi+0x58],0x70
        je loc_004186A7
    loc_0041868B:
        mov  ecx,DWORD PTR ds:0x491ff4
        and  ecx,0x1000
        neg  ecx
        sbb  ecx,ecx
        and  ecx,0xfffffffe
        add  ecx,0x4
        mov  DWORD PTR ds:0x491fb8,ecx
    loc_004186A7:
        mov  eax,DWORD PTR [edi+0x14]
        cmp  eax,0xb7c
        jne loc_004186C4
        push  ebp
        push  ebp
        push  ebp
        push  0x3c
        push  0x5
        mov  ebx,0x2b
        call FUN_0043c8b0
        jmp loc_004186D7
    loc_004186C4:
        cmp  eax,0xbb8
        jne loc_004186D7
        push  0x4
        mov  eax,0x491c28
        call FUN_0040ac90
    loc_004186D7:
        mov  esi,DWORD PTR ds:0x47770c
        call FUN_00417040
        mov  eax,DWORD PTR [edi+0x58]
        test  al,0x10
        jne loc_004186F1
        test  al,0x20
        jne loc_004186F1
        test  al,0x40
        je loc_00418700
    loc_004186F1:
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x3
        pop  ebx
        add  esp,0x40
        ret  0x4
    loc_00418700:
        mov  edx,DWORD PTR ds:0x477838
        cmp  DWORD PTR [edx+0x10],0x1
        je loc_00418740
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        lea  edx,[ecx+eax*2]
        add  edx,eax
        mov  eax,ds:0x47783c
        imul  edx,edx,0x437c
        mov  ecx,DWORD PTR [edx+eax*1+0x4cc]
        cmp  ecx,0xcdfe5ff
        lea  eax,[edx+eax*1+0x4cc]
        jge loc_00418740
        inc  ecx
        mov  DWORD PTR [eax],ecx
    loc_00418740:
        mov  ecx,DWORD PTR ds:0x477704
        cmp  DWORD PTR [ecx+0x10],ebp
        jne loc_00418769
        mov  edx,DWORD PTR ds:0x47770c
        cmp  DWORD PTR [edx+0x9eb8],ebp
        jne loc_00418769
        cmp  DWORD PTR [edi+0x14],0x5a
        jl loc_00418769
        mov  eax,0x474c40
        call FUN_00418a00
    loc_00418769:
        mov  ecx,DWORD PTR ds:0x474c88
        mov  eax,ds:0x474c8c
        inc  ecx
        inc  eax
        lea  esi,[edi+0x10]
        mov  DWORD PTR ds:0x474c88,ecx
        mov  ds:0x474c8c,eax
        call FUN_00404ed0
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        add  esp,0x40
        ret  0x4
    }
}

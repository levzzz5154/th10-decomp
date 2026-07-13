// 00417870: FUN_00417870
// Original size: 1040 bytes, actual code: 268 instructions
extern "C" void FUN_00402640(void);
extern "C" void FUN_00405410(void);
extern "C" void FUN_004056b0(void);
extern "C" void FUN_00406060(void);
extern "C" void FUN_00408c90(void);
extern "C" void FUN_00409e20(void);
extern "C" void FUN_0040af90(void);
extern "C" void FUN_0040d6b0(void);
extern "C" void FUN_00413a20(void);
extern "C" void FUN_00414830(void);
extern "C" void FUN_00417800(void);
extern "C" void FUN_00418b80(void);
extern "C" void FUN_00419090(void);
extern "C" void FUN_0041aed0(void);
extern "C" void FUN_0041c290(void);
extern "C" void FUN_00420a90(void);
extern "C" void FUN_00420c00(void);
extern "C" void FUN_00421070(void);
extern "C" void FUN_00421300(void);
extern "C" void FUN_00422360(void);
extern "C" void FUN_00425020(void);
extern "C" void FUN_00429610(void);
extern "C" void FUN_0042a6a0(void);
extern "C" void FUN_0042b660(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);

extern "C" __declspec(naked) void FUN_00417870(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [ebp+0x58]
        push  esi
        or   eax,0x4
        push  edi
        mov  DWORD PTR [ebp+0x58],eax
        mov  bl,0x80
    loc_00417883:
        mov  eax,ds:0x491c10
        mov  ecx,DWORD PTR [eax]
        xor  edi,edi
        cmp  ecx,edi
        jge loc_00417895
        cmp  DWORD PTR [eax+0x4],edi
        jl loc_004178AB
    loc_00417895:
        test  BYTE PTR ds:0x491ff4,bl
        jne loc_00417B3E
        push  0x1
        call  DWORD PTR ds:0x4660ac
        jmp loc_00417883
    loc_004178AB:
        cmp  DWORD PTR ds:0x491fc4,edi
        mov  DWORD PTR ds:0x476f78,0x3f800000
        mov  DWORD PTR ds:0x474c88,edi
        mov  DWORD PTR ds:0x474c8c,edi
        je loc_004179E9
        cmp  DWORD PTR ds:0x474c7c,0x7
        jne loc_004178E2
        mov  eax,0x4
        mov  ds:0x474c74,eax
        jmp loc_004178E7
    loc_004178E2:
        mov  eax,ds:0x474c74
    loc_004178E7:
        mov  ecx,DWORD PTR ds:0x474c68
        imul  eax,eax,0xf0
        mov  edx,DWORD PTR ds:0x474c6c
        mov  esi,DWORD PTR ds:0x47783c
        lea  edx,[edx+ecx*2]
        add  edx,ecx
        imul  edx,edx,0x437c
        add  edx,esi
        mov  ecx,DWORD PTR [eax+edx*1+0x18]
        add  eax,edx
        mov  DWORD PTR ds:0x474c40,ecx
        movsx edx,BYTE PTR [eax+0x1d]
        test  BYTE PTR ds:0x474ca0,0x8
        mov  DWORD PTR ds:0x474c94,edx
        jne loc_00417931
        mov  DWORD PTR ds:0x474c90,edi
    loc_00417931:
        push  0xc350
        mov  ecx,0x474c40
        mov  DWORD PTR ds:0x474c44,edi
        call FUN_00418b80
        test  BYTE PTR ds:0x474ca0,0x10
        jne loc_0041795B
        mov  DWORD PTR ds:0x474c70,0x2
        jmp loc_00417976
    loc_0041795B:
        mov  eax,ds:0x474cac
        cmp  eax,edi
        jne loc_00417970
        mov  DWORD PTR ds:0x474c70,0x9
        jmp loc_00417976
    loc_00417970:
        dec  eax
        mov  ds:0x474c70,eax
    loc_00417976:
        mov  eax,ds:0x474c7c
        mov  ecx,DWORD PTR ds:0x474ca0
        dec  eax
        neg  eax
        sbb  eax,eax
        and  eax,0x50
        and  ecx,0xfffffffb
        mov  ds:0x474c48,ax
        mov  DWORD PTR ds:0x474ca0,ecx
        cmp  DWORD PTR [ebp+0x5c],edi
        jne loc_004179CC
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        lea  edx,[ecx+eax*2]
        add  edx,eax
        imul  edx,edx,0x437c
        mov  ecx,DWORD PTR [edx+esi*1+0x4c8]
        cmp  ecx,0x1869f
        lea  eax,[edx+esi*1+0x4c8]
        jge loc_004179CC
        inc  ecx
        mov  DWORD PTR [eax],ecx
    loc_004179CC:
        mov  al,ds:0x474ca0
        and  al,0x8
        neg  al
        mov  DWORD PTR ds:0x474c9c,edi
        sbb  eax,eax
        and  eax,0xfffffe00
        mov  ds:0x474c98,eax
        jmp loc_004179FB
    loc_004179E9:
        mov  eax,ds:0x474c44
        cmp  eax,DWORD PTR ds:0x474c40
        jle loc_004179FB
        mov  ds:0x474c40,eax
    loc_004179FB:
        push  0x4187c0
        mov  DWORD PTR ds:0x474c50,0x9
        call FUN_00449ed0
        mov  ecx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        mov  ebx,0xfffffffd
        and  eax,ebx
        push  ecx
        mov  edi,0xa
        mov  DWORD PTR [esi+0x20],ebp
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449ae0
        push  0x4187d0
        mov  DWORD PTR [ebp+0x8],esi
        call FUN_00449ed0
        mov  esi,eax
        and  DWORD PTR [esi+0x4],ebx
        mov  edx,DWORD PTR ds:0x491be4
        push  edx
        mov  edi,0x4
        mov  DWORD PTR [esi+0x20],ebp
        call FUN_00449b70
        mov  eax,ds:0x477848
        mov  DWORD PTR [ebp+0xc],esi
        lea  edi,[ebp+0x24]
        mov  ecx,0xd
        mov  esi,0x491d48
        rep movsd
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x4],ecx
        test  BYTE PTR ds:0x474ca0,0x2
        jne loc_00417AF5
        mov  edx,DWORD PTR [ebp+0x5c]
        push  0x477710
        push  edx
        call FUN_00429610
        test  eax,eax
        je loc_00417B3C
        mov  eax,ds:0x477848
        mov  ecx,DWORD PTR [eax+0x4]
        push  0x0
        push  ecx
        call FUN_00402640
        test  eax,eax
        je loc_00417B3C
        call FUN_00414830
        test  eax,eax
        je loc_00417B3C
        call FUN_00425020
        test  eax,eax
        je loc_00417B3C
        call FUN_00406060
        test  eax,eax
        je loc_00417B3C
        call FUN_0041aed0
        test  eax,eax
        je loc_00417B3C
        call FUN_0041c290
        test  eax,eax
        je loc_00417B3C
        call FUN_00422360
        test  eax,eax
        je loc_00417B3C
        call FUN_00419090
        test  eax,eax
        je loc_00417B3C
        call FUN_0042b660
        jmp loc_00417B1C
    loc_00417AF5:
        mov  ebx,DWORD PTR ds:0x477838
        call FUN_0042a6a0
        mov  edx,DWORD PTR ds:0x47770c
        push  edx
        call FUN_00413a20
        mov  eax,ds:0x477848
        mov  ecx,DWORD PTR [eax+0x4]
        push  0x0
        push  ecx
        call FUN_00402640
    loc_00417B1C:
        test  eax,eax
        je loc_00417B3C
        test  BYTE PTR ds:0x474ca0,0x9
        jne loc_00417B81
        mov  edx,DWORD PTR ds:0x477848
        mov  eax,DWORD PTR [edx+0xc]
        push  eax
        call FUN_0040d6b0
        test  eax,eax
        jne loc_00417B8B
    loc_00417B3C:
        xor  edi,edi
    loc_00417B3E:
        mov  esi,DWORD PTR [ebp+0x58]
        or   esi,0x8
        push  0x491c28
        mov  DWORD PTR [ebp+0x58],esi
        call FUN_00421300
        mov  DWORD PTR ds:0x492264,edi
        mov  DWORD PTR ds:0x492260,0x1
        mov  eax,DWORD PTR [ebp+0x8]
        cmp  eax,edi
        je loc_00417B6C
        or   DWORD PTR [eax+0x4],0x2
    loc_00417B6C:
        mov  ebp,DWORD PTR [ebp+0xc]
        cmp  ebp,edi
        je loc_00417B77
        or   DWORD PTR [ebp+0x4],0x2
    loc_00417B77:
        pop  edi
        pop  esi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        ret  0x4
    loc_00417B81:
        mov  eax,ds:0x477704
        call FUN_00417800
    loc_00417B8B:
        call FUN_0040af90
        test  eax,eax
        je loc_00417B3C
        call FUN_004056b0
        test  eax,eax
        je loc_00417B3C
        call FUN_00408c90
        test  eax,eax
        je loc_00417B3C
        test  BYTE PTR ds:0x474ca0,0x20
        jne loc_00417BD8
        call FUN_00420c00
        mov  ecx,DWORD PTR ds:0x477848
        mov  edx,DWORD PTR [ecx+0x10]
        push  edx
        xor  esi,esi
        push  esi
        call FUN_00420a90
        mov  eax,ds:0x477848
        mov  ecx,DWORD PTR [eax+0x14]
        push  ecx
        push  0x1
        call FUN_00420a90
        jmp loc_00417BDA
    loc_00417BD8:
        xor  esi,esi
    loc_00417BDA:
        mov  eax,ds:0x477708
        fld  QWORD PTR ds:0x470b70
        fstp  QWORD PTR [eax+0x2c]
        push  esi
        fld  QWORD PTR ds:0x470b70
        fstp  QWORD PTR [eax+0x24]
        lea  eax,[ebp+0x10]
        call FUN_00405410
        cmp  DWORD PTR ds:0x494518,esi
        je loc_00417C12
    loc_00417C02:
        push  0x10
        call  DWORD PTR ds:0x4660ac
        cmp  DWORD PTR ds:0x494518,esi
        jne loc_00417C02
    loc_00417C12:
        cmp  DWORD PTR ds:0x474c84,esi
        je loc_00417C20
        mov  DWORD PTR ds:0x474c8c,esi
    loc_00417C20:
        push  0x491c28
        mov  DWORD PTR ds:0x474c84,esi
        call FUN_00421070
        and  DWORD PTR [ebp+0x58],0xfffffffb
        and  DWORD PTR ds:0x474ca0,0xfffffff4
        mov  eax,ebp
        mov  DWORD PTR ds:0x492264,esi
        mov  DWORD PTR ds:0x492260,0x1
        mov  DWORD PTR ds:0x4918a4,esi
        call FUN_00409e20
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        ret  0x4
    }
}

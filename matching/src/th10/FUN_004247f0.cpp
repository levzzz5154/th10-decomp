// 004247F0: FUN_004247f0
// Original size: 1440 bytes, actual code: 314 instructions
extern "C" void FUN_00404f30(void);
extern "C" void FUN_00426520(void);
extern "C" void FUN_00426f70(void);
extern "C" void FUN_00447280(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);
extern "C" void FUN_0044b810(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004247f0(void) {
    __asm {
        mov  eax,ds:0x474c68
        sub  esp,0xc
        push  ebp
        xor  ebp,ebp
        cmp  eax,ebp
        mov  eax,0x46e42c
        je loc_00424809
        mov  eax,0x46e420
    loc_00424809:
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        mov  ecx,0x8
        call FUN_00447280
        cmp  eax,ebp
        mov  DWORD PTR [ebx+0x10],eax
        jne loc_0042483B
        push  0x46e3ec
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        or   eax,0xffffffff
        pop  ebp
        add  esp,0xc
        ret
    loc_0042483B:
        mov  eax,ds:0x491bf0
        cmp  eax,ebp
        push  esi
        je loc_00424D4A
        mov  DWORD PTR [ebx+0x45c],eax
        mov  DWORD PTR ds:0x491bf0,ebp
    loc_00424855:
        push  edi
        push  0x426500
        call FUN_00449ed0
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edx,0xfffffffd
        push  eax
        mov  edi,0x10
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],edx
        call FUN_00449ae0
        push  0x426510
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  ecx,DWORD PTR ds:0x491be4
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        push  ecx
        mov  edi,0x16
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449b70
        mov  edx,DWORD PTR [ebx+0x10]
        mov  DWORD PTR [ebx+0xc],esi
        lea  esi,[ebx+0x14]
        push  edx
        xor  eax,eax
        call FUN_00404f30
        mov  esi,DWORD PTR [ebx+0x45c]
        mov  DWORD PTR [ebx+0x3c0],ebp
        mov  DWORD PTR [ebx+0x3c4],0x43c80000
        mov  DWORD PTR [ebx+0x3cc],ebp
        mov  DWORD PTR [ebx+0x3d0],0x9c40
        fld  DWORD PTR [esi+0x10]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [ebx+0x3d4],eax
        fld  DWORD PTR [esi+0x14]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [ebx+0x3d8],eax
        fld  DWORD PTR [esi+0x18]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [ebx+0x3dc],eax
        fld  DWORD PTR [esi+0x1c]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [ebx+0x3e0],eax
        lea  eax,[ebx+0x436c]
        mov  ecx,0x21
        jmp loc_00424940
        nop
    loc_00424940:
        mov  edx,DWORD PTR [ebx+0x3cc]
        mov  DWORD PTR [eax],edx
        mov  edx,DWORD PTR [ebx+0x3d0]
        mov  DWORD PTR [eax+0x4],edx
        add  eax,0x8
        dec  ecx
        jne loc_00424940
        mov  eax,DWORD PTR [ebx+0x470]
        test  al,0x1
        mov  edx,0xfff0bdc1
        mov  ecx,0x476f78
        jne loc_0042498C
        or   eax,0x1
        mov  DWORD PTR [ebx+0x464],ebp
        mov  DWORD PTR [ebx+0x460],edx
        mov  DWORD PTR [ebx+0x468],ebp
        mov  DWORD PTR [ebx+0x46c],ecx
        mov  DWORD PTR [ebx+0x470],eax
    loc_0042498C:
        mov  DWORD PTR [ebx+0x468],0xbf800000
        mov  DWORD PTR [ebx+0x460],0xfffffffe
        or   esi,0xffffffff
        mov  DWORD PTR [ebx+0x464],esi
        mov  edi,DWORD PTR ds:0x474c68
        mov  edi,DWORD PTR [edi*4+0x476fb8]
        mov  eax,DWORD PTR [ebx+0x45c]
        mov  DWORD PTR [eax+0x4],edi
        mov  edi,DWORD PTR ds:0x474c68
        mov  edi,DWORD PTR [edi*4+0x476fb0]
        mov  eax,DWORD PTR [ebx+0x45c]
        mov  DWORD PTR [eax+0xc],edi
        mov  edi,DWORD PTR ds:0x474c68
        mov  edi,DWORD PTR [edi*4+0x476fa0]
        mov  eax,DWORD PTR [ebx+0x45c]
        mov  DWORD PTR [eax+0x8],edi
        mov  eax,DWORD PTR [ebx+0x45c]
        fld  DWORD PTR [eax+0x4]
        mov  eax,0x40a00000
        fmul  DWORD PTR ds:0x470b0c
        mov  DWORD PTR [ebx+0x424],eax
        fst  DWORD PTR [ebx+0x420]
        fstp  DWORD PTR [ebx+0x41c]
        mov  edi,DWORD PTR ds:0x474c68
        fld  DWORD PTR [edi*4+0x476fb0]
        mov  DWORD PTR [ebx+0x430],eax
        fmul  DWORD PTR ds:0x470b0c
        fst  DWORD PTR [ebx+0x42c]
        fstp  DWORD PTR [ebx+0x428]
        mov  edi,DWORD PTR ds:0x474c68
        fld  DWORD PTR [edi*4+0x476fa8]
        mov  DWORD PTR [ebx+0x43c],eax
        fmul  DWORD PTR ds:0x470b0c
        lea  eax,[ebx+0x404]
        fst  DWORD PTR [ebx+0x438]
        fstp  DWORD PTR [ebx+0x434]
        fld  DWORD PTR [ebx+0x3c0]
        fsub  DWORD PTR [ebx+0x41c]
        fstp  DWORD PTR [esp+0xc]
        mov  edi,DWORD PTR [esp+0xc]
        fld  DWORD PTR [ebx+0x3c4]
        fsub  DWORD PTR [ebx+0x420]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [ebx+0x3c8]
        fsub  DWORD PTR [ebx+0x424]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax+0x4],edi
        fstp  DWORD PTR [esp+0x14]
        mov  edi,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x8],edi
        fld  DWORD PTR [ebx+0x41c]
        fadd  DWORD PTR [ebx+0x3c0]
        lea  eax,[ebx+0x410]
        fstp  DWORD PTR [esp+0xc]
        mov  edi,DWORD PTR [esp+0xc]
        fld  DWORD PTR [ebx+0x420]
        fadd  DWORD PTR [ebx+0x3c4]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [ebx+0x424]
        fadd  DWORD PTR [ebx+0x3c8]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax+0x4],edi
        fstp  DWORD PTR [esp+0x14]
        mov  edi,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x8],edi
        fld  DWORD PTR [ebx+0x3c0]
        fsub  DWORD PTR [ebx+0x428]
        lea  eax,[ebx+0x4324]
        fstp  DWORD PTR [esp+0xc]
        mov  edi,DWORD PTR [esp+0xc]
        fld  DWORD PTR [ebx+0x3c4]
        fsub  DWORD PTR [ebx+0x42c]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [ebx+0x3c8]
        fsub  DWORD PTR [ebx+0x430]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax+0x4],edi
        fstp  DWORD PTR [esp+0x14]
        mov  edi,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x8],edi
        fld  DWORD PTR [ebx+0x428]
        fadd  DWORD PTR [ebx+0x3c0]
        lea  eax,[ebx+0x4330]
        fstp  DWORD PTR [esp+0xc]
        mov  edi,DWORD PTR [esp+0xc]
        fld  DWORD PTR [ebx+0x42c]
        fadd  DWORD PTR [ebx+0x3c4]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [ebx+0x430]
        fadd  DWORD PTR [ebx+0x3c8]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax+0x4],edi
        fstp  DWORD PTR [esp+0x14]
        mov  edi,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x8],edi
        fld  DWORD PTR [ebx+0x3c0]
        fsub  DWORD PTR [ebx+0x434]
        lea  eax,[ebx+0x433c]
        fstp  DWORD PTR [esp+0xc]
        mov  edi,DWORD PTR [esp+0xc]
        fld  DWORD PTR [ebx+0x3c4]
        fsub  DWORD PTR [ebx+0x438]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [ebx+0x3c8]
        fsub  DWORD PTR [ebx+0x43c]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax+0x4],edi
        fstp  DWORD PTR [esp+0x14]
        mov  edi,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x8],edi
        fld  DWORD PTR [ebx+0x434]
        fadd  DWORD PTR [ebx+0x3c0]
        lea  eax,[ebx+0x4348]
        fstp  DWORD PTR [esp+0xc]
        mov  edi,DWORD PTR [esp+0xc]
        fld  DWORD PTR [ebx+0x438]
        fadd  DWORD PTR [ebx+0x3c4]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [ebx+0x43c]
        fadd  DWORD PTR [ebx+0x3c8]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax+0x4],edi
        fstp  DWORD PTR [esp+0x14]
        mov  edi,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x8],edi
        fld  DWORD PTR [ebx+0x3c0]
        fsub  DWORD PTR [ebx+0x434]
        lea  eax,[ebx+0x4354]
        fstp  DWORD PTR [esp+0xc]
        mov  edi,DWORD PTR [esp+0xc]
        fld  DWORD PTR [ebx+0x3c4]
        fsub  DWORD PTR [ebx+0x438]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [ebx+0x3c8]
        fsub  DWORD PTR [ebx+0x43c]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax+0x4],edi
        fstp  DWORD PTR [esp+0x14]
        mov  edi,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x8],edi
        fld  DWORD PTR [ebx+0x434]
        fadd  DWORD PTR [ebx+0x3c0]
        lea  eax,[ebx+0x4360]
        fstp  DWORD PTR [esp+0xc]
        mov  edi,DWORD PTR [esp+0xc]
        fld  DWORD PTR [ebx+0x438]
        fadd  DWORD PTR [ebx+0x3c4]
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [ebx+0x43c]
        fadd  DWORD PTR [ebx+0x3c8]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax+0x4],edi
        fstp  DWORD PTR [esp+0x14]
        mov  edi,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x8],edi
        mov  eax,DWORD PTR [ebx+0x484]
        test  al,0x1
        pop  edi
        jne loc_00424CD7
        or   eax,0x1
        mov  DWORD PTR [ebx+0x478],ebp
        mov  DWORD PTR [ebx+0x474],edx
        mov  DWORD PTR [ebx+0x47c],ebp
        mov  DWORD PTR [ebx+0x480],ecx
        mov  DWORD PTR [ebx+0x484],eax
    loc_00424CD7:
        mov  DWORD PTR [ebx+0x478],ebp
        mov  DWORD PTR [ebx+0x47c],ebp
        mov  DWORD PTR [ebx+0x474],esi
        mov  eax,DWORD PTR [ebx+0x431c]
        test  al,0x1
        jne loc_00424D14
        or   eax,0x1
        mov  DWORD PTR [ebx+0x4310],ebp
        mov  DWORD PTR [ebx+0x430c],edx
        mov  DWORD PTR [ebx+0x4314],ebp
        mov  DWORD PTR [ebx+0x4318],ecx
        mov  DWORD PTR [ebx+0x431c],eax
    loc_00424D14:
        mov  DWORD PTR [ebx+0x4310],0x78
        mov  DWORD PTR [ebx+0x4314],0x42f00000
        mov  DWORD PTR [ebx+0x430c],0x77
        push  ebx
        mov  DWORD PTR [ebx+0x4308],0x1e
        call FUN_00426f70
        pop  esi
        xor  eax,eax
        pop  ebp
        add  esp,0xc
        ret
    loc_00424D4A:
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        lea  edx,[ecx+eax*2]
        add  edx,eax
        mov  eax,DWORD PTR [edx*4+0x476fc0]
        mov  esi,ebx
        call FUN_00426520
        test  eax,eax
        je loc_00424855
        push  0x46e3ec
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        pop  esi
        or   eax,0xffffffff
        pop  ebp
        add  esp,0xc
        ret
    }
}

// 00426360: FUN_00426360
// Original size: 448 bytes, actual code: 98 instructions
extern "C" void FUN_00427c50(void);
extern "C" void FUN_0043bda0(void);
extern "C" void FUN_004451c0(void);

extern "C" __declspec(naked) void FUN_00426360(void) {
    __asm {
        sub  esp,0x14
        push  edi
        mov  edi,eax
        cmp  DWORD PTR [edi+0x458],0x2
        je loc_004264EF
        fld  DWORD PTR [edi+0x3c0]
        mov  ecx,DWORD PTR ds:0x491c10
        fadd  DWORD PTR ds:0x470b4c
        push  ebx
        push  esi
        fstp  DWORD PTR [edi+0x354]
        fld  DWORD PTR [edi+0x3c4]
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [edi+0x358]
        mov  eax,DWORD PTR [edi+0x3c8]
        mov  DWORD PTR [edi+0x35c],eax
        lea  eax,[edi+0x14]
        call FUN_004451c0
        lea  esi,[edi+0x3334]
        mov  ebx,0x4
        mov  edi,edi
    loc_004263C0:
        mov  eax,DWORD PTR [esi]
        test  eax,eax
        je loc_004263CE
        lea  ecx,[esi-0x94]
        call  eax
    loc_004263CE:
        add  esi,0x98
        dec  ebx
        jne loc_004263C0
        mov  eax,ds:0x477810
        test  eax,eax
        je loc_004264ED
        mov  cl,BYTE PTR [eax+0x54]
        test  cl,cl
        jns loc_004264ED
        mov  ecx,DWORD PTR ds:0x477704
        test  ecx,ecx
        je loc_004264ED
        mov  eax,ds:0x47770c
        test  eax,eax
        je loc_004264ED
        mov  edx,DWORD PTR [ecx+0x10]
        test  edx,edx
        jne loc_004264ED
        mov  ecx,DWORD PTR [eax+0x9eb8]
        test  ecx,ecx
        jne loc_004264ED
        mov  ecx,DWORD PTR ds:0x477830
        mov  eax,DWORD PTR [ecx+0x4]
        test  eax,eax
        jne loc_004264ED
        mov  eax,ds:0x474c58
        test  eax,eax
        je loc_004264ED
        fld  DWORD PTR [edi+0x3c0]
        push  ecx
        fadd  DWORD PTR ds:0x470cbc
        mov  DWORD PTR [esp+0x10],eax
        fsub  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esp]
        call FUN_00427c50
        fstp  DWORD PTR [esp+0x10]
        push  ecx
        fild  DWORD PTR [esp+0x10]
        fmul  DWORD PTR ds:0x470cb8
        fadd  DWORD PTR [esp+0x14]
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [edi+0x3c4]
        fadd  DWORD PTR ds:0x470cb4
        fsub  DWORD PTR ds:0x470be8
        fstp  DWORD PTR [esp]
        call FUN_00427c50
        fst  DWORD PTR [esp+0x14]
        mov  ebx,0x80000000
        fadd  DWORD PTR ds:0x470b08
        lea  edi,[esp+0x10]
        fstp  DWORD PTR [esp+0x1c]
        call FUN_0043bda0
        fld  DWORD PTR [esp+0x10]
        or   ebx,0xffffffff
        fsub  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x18]
        fsub  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [esp+0x18]
        fld  DWORD PTR [esp+0x14]
        fsub  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x1c]
        fsub  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [esp+0x1c]
        call FUN_0043bda0
    loc_004264ED:
        pop  esi
        pop  ebx
    loc_004264EF:
        mov  eax,0x1
        pop  edi
        add  esp,0x14
        ret
    }
}

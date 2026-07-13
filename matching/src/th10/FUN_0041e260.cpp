// 0041E260: FUN_0041e260
// Original size: 624 bytes, actual code: 163 instructions
extern "C" void FUN_0041bb00(void);
extern "C" void FUN_0041f800(void);
extern "C" void FUN_0043e710(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_0041e260(void) {
    __asm {
        sub  esp,0x30
        push  esi
        mov  edx,ecx
        mov  eax,DWORD PTR [edx+0x3c]
        push  0x40c00000
        xor  esi,esi
        push  eax
        lea  ecx,[esp+0x24]
        mov  DWORD PTR [esp+0x10],edx
        mov  DWORD PTR [esp+0x14],esi
        mov  DWORD PTR [esp+0xc],0x40c00000
        call FUN_0041f800
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [edx+0x24]
        mov  ecx,DWORD PTR [edx+0x2c]
        mov  DWORD PTR [esp+0x30],ecx
        mov  DWORD PTR [esp+0x24],esi
        fstp  DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [esp+0x28]
        fld  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x10],eax
        fadd  DWORD PTR [edx+0x28]
        mov  eax,DWORD PTR [esp+0x30]
        mov  DWORD PTR [esp+0x18],eax
        fstp  DWORD PTR [esp+0x2c]
        mov  ecx,DWORD PTR [esp+0x2c]
        fld  DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x14],ecx
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x20]
        fadd  st(0),st
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR ds:0x470cd8
        fcomp DWORD PTR [edx+0x40]
        fnstsw ax
        test  ah,0x5
        jp loc_0041E4B1
        mov  esi,DWORD PTR ds:0x491c10
        push  ebx
        push  ebp
        push  edi
    loc_0041E2F4:
        mov  edi,DWORD PTR [esp+0x18]
        movsx ebx,WORD PTR [edx+0x44a]
        mov  ecx,DWORD PTR ds:0x47781c
        mov  ebp,DWORD PTR [ecx+0x458]
        inc  edi
        mov  DWORD PTR [esp+0x18],edi
        lea  ebx,[ebx+ebx*1+0x11]
        call FUN_00449950
        mov  edi,eax
        mov  edx,DWORD PTR [edi+0x35c]
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR ds:0x470b4c
        or   edx,0x40000000
        mov  DWORD PTR [edi+0x35c],edx
        mov  edx,DWORD PTR [esp+0x24]
        xor  esi,esi
        mov  DWORD PTR [edi+0x20],esi
        fstp  DWORD PTR [edi+0x340]
        mov  ecx,ebp
        fld  DWORD PTR [esp+0x20]
        mov  DWORD PTR [edi+0x348],edx
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [edi+0x344]
        call FUN_0043e710
        lea  eax,[edi+0x4]
        mov  DWORD PTR [eax+0x4],esi
        mov  DWORD PTR [eax+0x8],esi
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [eax],edi
        mov  ecx,DWORD PTR [esi+0x72dad4]
        test  ecx,ecx
        jne loc_0041E386
        mov  DWORD PTR [esi+0x72dad4],eax
        jmp loc_0041E3A2
    loc_0041E386:
        mov  ecx,DWORD PTR [esi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_0041E39C
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_0041E39C:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_0041E3A2:
        mov  DWORD PTR [esi+0x72dad8],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        inc  ecx
        mov  eax,ecx
        test  eax,eax
        mov  DWORD PTR [esi+0x732454],ecx
        jne loc_0041E3C2
        inc  eax
        mov  DWORD PTR [esi+0x732454],eax
    loc_0041E3C2:
        mov  eax,DWORD PTR [esi+0x732454]
        mov  DWORD PTR [edi],eax
        mov  eax,DWORD PTR [esp+0x44]
        test  eax,eax
        je loc_0041E450
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b40
        fnstsw ax
        test  ah,0x41
        jnp loc_0041E450
        fld  DWORD PTR [esp+0x1c]
        fsub  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b3c
        fnstsw ax
        test  ah,0x1
        je loc_0041E450
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x41
        jnp loc_0041E450
        fld  DWORD PTR [esp+0x20]
        fsub  DWORD PTR ds:0x470bcc
        fcomp DWORD PTR ds:0x470b38
        fnstsw ax
        test  ah,0x1
        je loc_0041E450
        mov  eax,ds:0x477818
        push  0x3f19999a
        push  0xbfc90fdb
        push  0xffffffff
        push  0x8
        lea  ecx,[esp+0x2c]
        call FUN_0041bb00
        mov  esi,DWORD PTR ds:0x491c10
    loc_0041E450:
        fld  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x14]
        fadd  DWORD PTR [esp+0x28]
        mov  edx,ecx
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esp+0x20]
        fadd  DWORD PTR [esp+0x2c]
        fstp  DWORD PTR [esp+0x20]
        fld  DWORD PTR [esp+0x24]
        fadd  DWORD PTR [esp+0x30]
        fstp  DWORD PTR [esp+0x24]
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470cd8
        fst  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470d1c
        fcomp DWORD PTR [ecx+0x40]
        fnstsw ax
        test  ah,0x5
        jnp loc_0041E2F4
        mov  eax,DWORD PTR [esp+0x18]
        pop  edi
        pop  ebp
        pop  ebx
        mov  DWORD PTR [edx+0xc],0x1
        pop  esi
        add  esp,0x30
        ret  0x4
    loc_0041E4B1:
        mov  eax,esi
        mov  DWORD PTR [edx+0xc],0x1
        pop  esi
        add  esp,0x30
        ret  0x4
    }
}

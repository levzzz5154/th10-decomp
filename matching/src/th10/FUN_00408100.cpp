// 00408100: FUN_00408100
// Original size: 272 bytes, actual code: 74 instructions
extern "C" void FUN_00408030(void);
extern "C" void FUN_004086b0(void);
extern "C" void FUN_0041bb00(void);

extern "C" __declspec(naked) void FUN_00408100(void) {
    __asm {
        sub  esp,0x18
        push  ebp
        push  esi
        mov  esi,eax
        push  edi
        add  esi,0x60
        mov  ebp,0x7d0
    loc_00408110:
        mov  ax,WORD PTR [esi+0x446]
        test  ax,ax
        je loc_004081EC
        cmp  ax,0x3
        je loc_004081EC
        mov  eax,DWORD PTR [esp+0x30]
        test  eax,eax
        je loc_0040813D
        mov  eax,DWORD PTR [esi+0x4]
        test  eax,eax
        jne loc_004081EC
    loc_0040813D:
        fld  DWORD PTR [esi+0x3b4]
        lea  edi,[esi+0x3b4]
        fsub  DWORD PTR [ebx]
        fstp  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x18]
        fld  DWORD PTR [esi+0x3b8]
        mov  DWORD PTR [esp+0xc],eax
        fsub  DWORD PTR [ebx+0x4]
        fstp  DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [esp+0x1c]
        fld  DWORD PTR [esi+0x3bc]
        mov  DWORD PTR [esp+0x10],ecx
        fsub  DWORD PTR [ebx+0x8]
        fstp  DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [esp+0x20]
        fld  DWORD PTR [esi+0x3f0]
        mov  DWORD PTR [esp+0x14],edx
        fmul  DWORD PTR ds:0x470b0c
        fadd  DWORD PTR [esp+0x28]
        fld  DWORD PTR [esp+0x10]
        fmul  DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0xc]
        fmul  DWORD PTR [esp+0xc]
        faddp st(1),st
        fld  st(1)
        fmul  st,st(2)
        fcompp
        fnstsw ax
        fstp  st(0)
        test  ah,0x5
        jnp loc_004081EC
        call FUN_00408030
        push  0x40000000
        push  0x40000000
        mov  ecx,edi
        call FUN_004086b0
        test  eax,eax
        jne loc_004081EC
        mov  eax,DWORD PTR [esp+0x2c]
        test  eax,eax
        je loc_004081EC
        mov  eax,ds:0x477818
        push  0x3f19999a
        push  0xbfc90fdb
        push  0xffffffff
        push  0x8
        call FUN_0041bb00
    loc_004081EC:
        add  esi,0x7f0
        dec  ebp
        jne loc_00408110
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        add  esp,0x18
        ret  0xc
    }
}

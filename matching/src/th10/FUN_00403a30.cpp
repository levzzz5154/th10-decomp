// 00403A30: FUN_00403a30
// Original size: 592 bytes, actual code: 156 instructions
extern "C" void FUN_00403090(void);
extern "C" void FUN_004215a0(void);
extern "C" void FUN_00442f50(void);
extern "C" void FUN_004451c0(void);

extern "C" __declspec(naked) void FUN_00403a30(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x18]
        mov  ebx,DWORD PTR [ebp+0x18]
        push  edi
        mov  edi,0x491d7c
        mov  DWORD PTR ds:0x491fac,edi
        call FUN_004215a0
        mov  edx,DWORD PTR ds:0x491fac
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        add  edx,0xcc
        push  edx
        push  eax
        call  DWORD PTR [ecx+0xbc]
        mov  eax,ds:0x491c10
        mov  DWORD PTR ds:0x491fb0,0x0
        mov  BYTE PTR [eax+0x3ada6c],0x1
        mov  ax,WORD PTR [ebx]
        test  ax,ax
        jl loc_00403C75
        push  esi
        jmp loc_00403A90
        nop
    loc_00403A90:
        mov  edx,DWORD PTR [ebp+0x14]
        movsx ecx,ax
        mov  esi,DWORD PTR [edx+ecx*4]
        movsx eax,BYTE PTR [esi+0x2]
        cmp  eax,DWORD PTR [esp+0x24]
        jne loc_00403C64
        mov  ecx,DWORD PTR [ebx+0x4]
        mov  edx,DWORD PTR [ebx+0x8]
        mov  eax,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x10],ecx
        mov  ecx,DWORD PTR [ebp+0x1ee0]
        mov  DWORD PTR [esp+0x14],edx
        mov  DWORD PTR [esp+0x18],eax
        push  ecx
        mov  eax,0x491d7c
        lea  edx,[esp+0x14]
        mov  ecx,esi
        call FUN_00403090
        test  eax,eax
        je loc_00403AE2
        inc  DWORD PTR [ebp+0x2a10]
        jmp loc_00403C64
    loc_00403AE2:
        mov  dl,BYTE PTR [esi+0x3]
        or   dl,0x2
        lea  ebp,[esi+0x1c]
        mov  BYTE PTR [esi+0x3],dl
        mov  ax,WORD PTR [ebp+0x0]
        test  ax,ax
        jl loc_00403C4F
        jmp loc_00403B00
        nop
    loc_00403B00:
        movsx edi,WORD PTR [ebp+0x6]
        mov  esi,DWORD PTR [esp+0x20]
        imul  edi,edi,0x3ac
        add  edi,DWORD PTR [esi+0x17c]
        test  ax,ax
        jne loc_00403C3A
        mov  ecx,DWORD PTR [edi+0x35c]
        mov  edx,ecx
        and  edx,0x3c00000
        cmp  edx,0x1000000
        jb loc_00403BB1
        fld  DWORD PTR [ebp+0x8]
        fadd  DWORD PTR [ebx+0x4]
        fstp  DWORD PTR [edi+0x340]
        fld  DWORD PTR [ebp+0xc]
        fadd  DWORD PTR [ebx+0x8]
        fstp  DWORD PTR [edi+0x344]
        fld  DWORD PTR [ebp+0x10]
        fadd  DWORD PTR [ebx+0xc]
        fstp  DWORD PTR [edi+0x348]
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebp+0x14]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00403B81
        fld  DWORD PTR [ebp+0x14]
        mov  eax,DWORD PTR [edi+0x394]
        fdiv  DWORD PTR [eax+0x34]
        or   ecx,0x8
        mov  DWORD PTR [edi+0x35c],ecx
        fstp  DWORD PTR [edi+0x3c]
    loc_00403B81:
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebp+0x18]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00403BB1
        fld  DWORD PTR [ebp+0x18]
        mov  ecx,DWORD PTR [edi+0x394]
        fdiv  DWORD PTR [ecx+0x30]
        mov  eax,DWORD PTR [edi+0x35c]
        or   eax,0x8
        mov  DWORD PTR [edi+0x35c],eax
        fstp  DWORD PTR [edi+0x40]
    loc_00403BB1:
        mov  edx,DWORD PTR [edi+0x35c]
        mov  eax,ds:0x492378
        and  edx,0x3c00000
        cmp  edx,0x2000000
        jne loc_00403BF8
        cmp  eax,0x1
        je loc_00403C27
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        push  0x1
        push  0x1c
        mov  DWORD PTR ds:0x492378,0x1
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0xe4]
        jmp loc_00403C23
    loc_00403BF8:
        test  eax,eax
        je loc_00403C27
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        push  0x0
        push  0x1c
        mov  DWORD PTR ds:0x492378,0x0
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0xe4]
    loc_00403C23:
        mov  esi,DWORD PTR [esp+0x20]
    loc_00403C27:
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,edi
        call FUN_004451c0
        inc  DWORD PTR [esi+0x2a14]
    loc_00403C3A:
        movsx eax,WORD PTR [ebp+0x2]
        add  ebp,eax
        mov  ax,WORD PTR [ebp+0x0]
        test  ax,ax
        jge loc_00403B00
        jmp loc_00403C53
    loc_00403C4F:
        mov  esi,DWORD PTR [esp+0x20]
    loc_00403C53:
        mov  eax,DWORD PTR [esi+0x2a0c]
        mov  ebp,DWORD PTR [esp+0x20]
        inc  eax
        mov  DWORD PTR [esi+0x2a0c],eax
    loc_00403C64:
        mov  ax,WORD PTR [ebx+0x10]
        add  ebx,0x10
        test  ax,ax
        jge loc_00403A90
        pop  esi
    loc_00403C75:
        pop  edi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0xc
        ret  0x8
    }
}

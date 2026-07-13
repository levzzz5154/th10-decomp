// 0043DDF0: FUN_0043ddf0
// Original size: 1456 bytes, actual code: 421 instructions
extern "C" void FUN_0043d2a0(void);
extern "C" void FUN_0043d7d0(void);
extern "C" void FUN_0043d950(void);
extern "C" void FUN_0043dab0(void);
extern "C" void FUN_0044cf20(void);
extern "C" void FUN_0044d110(void);
extern "C" void FUN_0044d440(void);
extern "C" void FUN_0044d4e0(void);
extern "C" void FUN_0044d550(void);
extern "C" void FUN_0044d5b0(void);
extern "C" void FUN_0044d5d0(void);
extern "C" void FUN_0044dad0(void);
extern "C" void FUN_0044dca0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0043ddf0(void) {
    __asm {
        sub  esp,0xc
        push  ebp
        mov  ebp,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [ebp+0x610]
        test  eax,eax
        jne loc_0043DE0B
        xor  eax,eax
        pop  ebp
        add  esp,0xc
        ret  0x4
    loc_0043DE0B:
        push  ebx
        push  edi
        lea  ebx,[ebp+0x1f88]
        mov  DWORD PTR [esp+0x10],ebx
        push  esi
    loc_0043DE18:
        mov  eax,DWORD PTR [ebx]
        dec  eax
        cmp  eax,0x7
        mov  edi,0x1
        jmp loc_0043DE30
        nop
        nop
    loc_0043DE30:
        mov  DWORD PTR [esp+0x20],0x0
        ja loc_0043E212
        jmp  DWORD PTR [eax*4+0x43e37c]
        mov  eax,DWORD PTR [ebp+0x5208]
        test  eax,eax
        je loc_0043E0E5
        mov  ecx,DWORD PTR [ebp+0x52c4]
        push  ecx
        call FUN_0044d4e0
        jmp loc_0043E0E5
        test  BYTE PTR ds:0x491d78,0x10
        je loc_0043DE94
        mov  eax,DWORD PTR [ebx+0x8]
        test  eax,eax
        jne loc_0043E20F
        mov  esi,ebp
        call FUN_0043dab0
        mov  edx,DWORD PTR [ebx+0x4]
        lea  eax,[ebx+0xc]
        push  edx
        call FUN_0043d7d0
        mov  DWORD PTR [esp+0x20],edi
        jmp loc_0043E0E5
    loc_0043DE94:
        mov  ecx,DWORD PTR [ebx+0x4]
        lea  eax,[ebx+0xc]
        push  ecx
        mov  esi,ebp
        call FUN_0043d7d0
        mov  DWORD PTR [esp+0x20],edi
        jmp loc_0043E0E5
        test  BYTE PTR ds:0x491d78,0x10
        je loc_0043DF6B
        mov  eax,DWORD PTR [ebx+0x4]
        test  eax,eax
        jl loc_0043DF6B
        mov  ecx,DWORD PTR [ebx+0x8]
        test  ecx,ecx
        jne loc_0043DEDE
        mov  esi,ebp
        call FUN_0043d950
        test  eax,eax
        je loc_0043E20F
        jmp loc_0043E0E5
    loc_0043DEDE:
        cmp  ecx,0x2
        jne loc_0043DF03
        mov  edi,DWORD PTR [ebp+0x5208]
        test  edi,edi
        je loc_0043E20F
        call FUN_0044dad0
        test  eax,eax
        jge loc_0043E20F
        jmp loc_0043E0E5
    loc_0043DF03:
        cmp  ecx,0x5
        jne loc_0043DF54
        mov  eax,DWORD PTR [ebp+0x5208]
        mov  ecx,DWORD PTR [eax+0x4]
        test  ecx,ecx
        je loc_0043DF22
        mov  edx,DWORD PTR [eax+0x10]
        test  edx,edx
        ja loc_0043DF20
        xor  ecx,ecx
        jmp loc_0043DF22
    loc_0043DF20:
        mov  ecx,DWORD PTR [ecx]
    loc_0043DF22:
        mov  edx,DWORD PTR [eax+0xc]
        mov  eax,DWORD PTR [edx+0x90]
        mov  edi,DWORD PTR [eax+0x1c]
        xor  edx,edx
        test  edi,edi
        setne dl
        mov  eax,edx
        push  eax
        push  ecx
    loc_0043DF39:
        mov  DWORD PTR [ebx+0x4],eax
        mov  eax,DWORD PTR [ebp+0x5208]
        call FUN_0044d110
        test  eax,eax
        jge loc_0043E20F
        jmp loc_0043E0E5
    loc_0043DF54:
        cmp  ecx,0x7
        je loc_0043E17A
        cmp  ecx,0x14
        jl loc_0043E20F
        jmp loc_0043E0E5
    loc_0043DF6B:
        mov  ecx,DWORD PTR [ebp+0x5208]
        test  ecx,ecx
        je loc_0043E0E5
        mov  eax,DWORD PTR [ebx+0x8]
        test  eax,eax
        je loc_0043E204
        cmp  eax,edi
        je loc_0043E123
        cmp  eax,0x2
        je loc_0043E13E
        cmp  eax,0x3
        jne loc_0043DFD9
        mov  eax,DWORD PTR [ecx+0x4]
        test  eax,eax
        jne loc_0043DFA5
        xor  esi,esi
        jmp loc_0043DFB2
    loc_0043DFA5:
        mov  edx,DWORD PTR [ecx+0x10]
        test  edx,edx
        ja loc_0043DFB0
        xor  esi,esi
        jmp loc_0043DFB2
    loc_0043DFB0:
        mov  esi,DWORD PTR [eax]
    loc_0043DFB2:
        mov  edi,ecx
        call FUN_0044dad0
        mov  eax,DWORD PTR [ebp+0x5208]
        mov  ecx,DWORD PTR [eax+0xc]
        mov  edx,DWORD PTR [ecx+0x90]
        mov  ecx,DWORD PTR [edx+0x1c]
        xor  eax,eax
        test  ecx,ecx
        setne al
        push  eax
        push  esi
        jmp loc_0043DF39
    loc_0043DFD9:
        cmp  eax,0x4
        je loc_0043E17A
        cmp  eax,0x7
        jl loc_0043E20F
        jmp loc_0043E0E5
        mov  eax,DWORD PTR [ebp+0x5208]
        test  eax,eax
        je loc_0043E0E5
        mov  eax,DWORD PTR [ebx+0x8]
        test  eax,eax
        je loc_0043E204
        cmp  eax,edi
        jne loc_0043E033
        mov  eax,DWORD PTR [ebp+0x618]
        test  eax,eax
        je loc_0043E0E5
        mov  ecx,DWORD PTR [ebp+0x614]
        push  0x0
        push  0x0
        push  0x12
        push  ecx
        call  DWORD PTR ds:0x466210
        jmp loc_0043E20F
    loc_0043E033:
        cmp  eax,0x2
        je loc_0043E18D
        cmp  eax,0x3
        je loc_0043E1C7
        cmp  eax,0xa
        jne loc_0043E20F
        jmp loc_0043E0E5
        mov  eax,DWORD PTR [ebp+0x5208]
        test  eax,eax
        je loc_0043E0E5
        mov  eax,DWORD PTR [ebx+0x8]
        test  eax,eax
        je loc_0043E204
        cmp  eax,edi
        jne loc_0043E20F
        jmp loc_0043E0E5
        mov  esi,DWORD PTR ds:0x497798
        fild  DWORD PTR [ebx+0x4]
        test  esi,esi
        je loc_0043E0E3
        fmul  DWORD PTR ds:0x470b1c
        mov  DWORD PTR [esi+0x1c],edi
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x14],eax
        mov  DWORD PTR [esi+0x18],eax
        jmp loc_0043E0E5
        cmp  BYTE PTR ds:0x491d63,0x1
        jne loc_0043E0E5
        mov  ecx,DWORD PTR [ebp+0x5208]
        mov  eax,DWORD PTR [ecx+0x74]
        test  eax,eax
        jne loc_0043E212
        test  ecx,ecx
        je loc_0043E0E5
        call FUN_0044d5b0
        jmp loc_0043E0E5
        cmp  BYTE PTR ds:0x491d63,0x1
        jne loc_0043E0E5
        mov  eax,DWORD PTR [ebp+0x5208]
        mov  ecx,DWORD PTR [eax+0x74]
        test  ecx,ecx
        jne loc_0043E212
        test  eax,eax
        je loc_0043E0E5
        call FUN_0044d5d0
        jmp loc_0043E0E5
    loc_0043E0E3:
        fstp  st(0)
    loc_0043E0E5:
        xor  eax,eax
        lea  edx,[ebx+0x10c]
        nop
    loc_0043E0F0:
        cmp  DWORD PTR [ebx],0x0
        je loc_0043E112
        mov  esi,edx
        mov  edi,ebx
        inc  eax
        mov  ecx,0x43
        add  ebx,0x10c
        add  edx,0x10c
        cmp  eax,0x1f
        rep movsd
        jl loc_0043E0F0
    loc_0043E112:
        mov  eax,DWORD PTR [esp+0x20]
        test  eax,eax
        je loc_0043E212
        jmp loc_0043DE18
    loc_0043E123:
        mov  esi,DWORD PTR [ebp+0x5208]
        mov  eax,DWORD PTR [esi+0x74]
        test  eax,eax
        jne loc_0043E212
        call FUN_0044cf20
        jmp loc_0043E20F
    loc_0043E13E:
        mov  eax,DWORD PTR [ebx+0x4]
        test  eax,eax
        jl loc_0043E151
        shl  eax,0x8
        lea  ecx,[eax+ebp*1+0x4108]
        jmp loc_0043E154
    loc_0043E151:
        lea  ecx,[ebx+0xc]
    loc_0043E154:
        push  ebp
        call FUN_0043d2a0
        mov  ecx,eax
        mov  eax,DWORD PTR [ebp+0x1f84]
        imul  ecx,ecx,0x34
        add  ecx,eax
        mov  eax,DWORD PTR [ebp+0x5208]
        mov  esi,DWORD PTR [eax+0xc]
        call FUN_0044dca0
        jmp loc_0043E20F
    loc_0043E17A:
        mov  eax,DWORD PTR [ebp+0x5208]
        push  edi
        push  0x0
        call FUN_0044d440
        jmp loc_0043E20F
    loc_0043E18D:
        mov  edx,DWORD PTR [ebp+0x618]
        push  0x100
        push  edx
        call  DWORD PTR ds:0x46611c
        test  eax,eax
        je loc_0043E1BB
        mov  eax,DWORD PTR [ebp+0x614]
        push  0x0
        push  0x0
        push  0x12
        push  eax
        call  DWORD PTR ds:0x466210
        dec  DWORD PTR [ebx+0x8]
        jmp loc_0043E20F
    loc_0043E1BB:
        mov  DWORD PTR [ebp+0x618],0x0
        jmp loc_0043E20F
    loc_0043E1C7:
        mov  ecx,DWORD PTR [ebp+0x618]
        mov  esi,DWORD PTR ds:0x4660cc
        push  ecx
        call  esi
        mov  edx,DWORD PTR [ebp+0x520c]
        push  edx
        call  esi
        mov  ecx,DWORD PTR [ebp+0x5208]
        xor  esi,esi
        cmp  ecx,esi
        mov  DWORD PTR [ebp+0x618],esi
        je loc_0043E1FC
        mov  eax,DWORD PTR [ecx]
        push  edi
        call  DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x5208],esi
    loc_0043E1FC:
        mov  DWORD PTR [ebp+0x5208],esi
        jmp loc_0043E20F
    loc_0043E204:
        mov  edi,DWORD PTR [ebp+0x5208]
        call FUN_0044d550
    loc_0043E20F:
        inc  DWORD PTR [ebx+0x8]
    loc_0043E212:
        mov  al,ds:0x491d64
        test  al,al
        jne loc_0043E22B
        mov  ecx,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [ecx]
        pop  esi
        pop  edi
        pop  ebx
        pop  ebp
        add  esp,0xc
        ret  0x4
    loc_0043E22B:
        lea  edx,[ebp+0x680]
        mov  DWORD PTR [esp+0x10],0x0
        lea  ebx,[ebp+0x650]
        mov  DWORD PTR [esp+0x20],edx
    loc_0043E243:
        mov  esi,DWORD PTR [ebx-0x30]
        test  esi,esi
        jl loc_0043E36B
        mov  edi,DWORD PTR [ebx]
        test  edi,edi
        mov  DWORD PTR [ebx-0x30],0xffffffff
        jge loc_0043E279
        mov  eax,DWORD PTR [ebp+esi*4+0x208]
        test  eax,eax
        je loc_0043E26E
        mov  esi,eax
        mov  eax,DWORD PTR [esi]
        push  esi
        call  DWORD PTR [eax+0x48]
    loc_0043E26E:
        mov  DWORD PTR [ebx],0x0
        jmp loc_0043E348
    loc_0043E279:
        xor  eax,eax
        test  edi,edi
        jle loc_0043E28D
        mov  ecx,DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [ebx]
    loc_0043E285:
        add  eax,DWORD PTR [ecx]
        add  ecx,0x4
        dec  edx
        jne loc_0043E285
    loc_0043E28D:
        cdq
        idiv  edi
        mov  DWORD PTR [ebx],0x0
        mov  edi,eax
        mov  eax,DWORD PTR [ebp+esi*4+0x208]
        test  eax,eax
        je loc_0043E348
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        mov  eax,DWORD PTR [ebp+esi*4+0x208]
        mov  edx,DWORD PTR [eax]
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x34]
        mov  eax,DWORD PTR [ebp+esi*4+0x208]
        mov  ecx,DWORD PTR [eax]
        push  edi
        push  eax
        call  DWORD PTR [ecx+0x40]
        mov  eax,ds:0x497858
        test  eax,eax
        mov  eax,DWORD PTR [ebp+esi*4+0x208]
        je loc_0043E32A
        fild  DWORD PTR ds:0x497858
        movsx edx,WORD PTR [esi*8+0x4749cc]
        mov  edi,DWORD PTR [eax]
        add  edx,0x1388
        fmul  DWORD PTR ds:0x470b00
        mov  DWORD PTR [esp+0x18],edx
        fsubr DWORD PTR ds:0x470afc
        fld  st(0)
        fmul  st,st(1)
        fmul  st,st(1)
        fsubr DWORD PTR ds:0x470afc
        fimul DWORD PTR [esp+0x18]
        call FUN_00463b2c
        fstp  st(0)
        sub  eax,0x1388
        push  eax
        mov  eax,DWORD PTR [ebp+esi*4+0x208]
        push  eax
        call  DWORD PTR [edi+0x3c]
        jmp loc_0043E335
    loc_0043E32A:
        mov  ecx,DWORD PTR [eax]
        push  0xffffd8f0
        push  eax
        call  DWORD PTR [ecx+0x3c]
    loc_0043E335:
        mov  esi,DWORD PTR [ebp+esi*4+0x208]
        mov  edx,DWORD PTR [esi]
        push  0x0
        push  0x0
        push  0x0
        push  esi
        call  DWORD PTR [edx+0x30]
    loc_0043E348:
        mov  eax,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x20]
        inc  eax
        add  edx,0x200
        add  ebx,0x4
        cmp  eax,0xc
        mov  DWORD PTR [esp+0x10],eax
        mov  DWORD PTR [esp+0x20],edx
        jl loc_0043E243
    loc_0043E36B:
        mov  eax,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [eax]
        pop  esi
        pop  edi
        pop  ebx
        pop  ebp
        add  esp,0xc
        ret  0x4
    }
}

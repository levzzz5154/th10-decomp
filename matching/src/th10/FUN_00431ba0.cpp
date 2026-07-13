// 00431BA0: FUN_00431ba0
// Original size: 832 bytes, actual code: 230 instructions
extern "C" void FUN_00401630(void);
extern "C" void _localtime(void);

extern "C" __declspec(naked) void FUN_00431ba0(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [ebp+0x20]
        sub  eax,0x2
        push  esi
        push  edi
        je loc_00431D9D
        sub  eax,0x2
        jne loc_00431ECA
        mov  eax,DWORD PTR [ebp+0x59dc]
        mov  ecx,DWORD PTR [ebp+eax*4+0x59e4]
        mov  edi,DWORD PTR [ecx+0x18]
        mov  ecx,DWORD PTR [ebp+0x2b4]
        mov  esi,0xa
        cmp  ecx,esi
        mov  DWORD PTR [esp+0x10],0x42a00000
        mov  DWORD PTR [esp+0x14],0x42a00000
        mov  DWORD PTR [esp+0x18],0x0
        jge loc_00431C1E
        fld  DWORD PTR ds:0x470c1c
        imul  eax,eax,0xf
        fsub  DWORD PTR [ebp+0x2b8]
        mov  DWORD PTR [esp+0x20],eax
        fimul DWORD PTR [esp+0x20]
        fmul  DWORD PTR ds:0x470c18
        fadd  DWORD PTR ds:0x470c28
        fstp  DWORD PTR [esp+0x14]
    loc_00431C1E:
        mov  edx,DWORD PTR ds:0x4776e0
        lea  eax,[edi+0xc]
        push  eax
        mov  DWORD PTR [edx+0x8988],0x1
        call _localtime
        fld  DWORD PTR [edi+0x48]
        push  ecx
        mov  ecx,DWORD PTR [edi+0x5c]
        fstp  QWORD PTR [esp]
        mov  edx,DWORD PTR [ecx*4+0x474744]
        mov  ecx,DWORD PTR [edi+0x58]
        push  edx
        mov  edx,DWORD PTR [ecx*4+0x4746f4]
        mov  ecx,DWORD PTR [edi+0x50]
        push  edx
        mov  edx,DWORD PTR [edi+0x54]
        lea  ecx,[ecx+ecx*2]
        add  ecx,edx
        mov  edx,DWORD PTR [ecx*4+0x4746dc]
        mov  ecx,DWORD PTR [eax+0x4]
        push  edx
        mov  edx,DWORD PTR [eax+0x8]
        push  ecx
        mov  ecx,DWORD PTR [eax+0xc]
        push  edx
        mov  edx,DWORD PTR [eax+0x10]
        mov  eax,DWORD PTR [eax+0x14]
        push  ecx
        inc  edx
        push  edx
        cdq
        mov  ecx,0x64
        idiv  ecx
        mov  eax,ds:0x4776e0
        lea  ebx,[esp+0x34]
        push  edx
        mov  edx,DWORD PTR [ebp+0x59dc]
        push  edi
        inc  edx
        push  edx
        push  0x46efb0
        push  eax
        call FUN_00401630
        mov  eax,DWORD PTR [ebp+0x2b4]
        add  esp,0x38
        cmp  eax,esi
        jl loc_00431EB1
        mov  DWORD PTR [esp+0x10],0x435c0000
        mov  DWORD PTR [esp+0x14],0x43000000
        mov  esi,0x1
        mov  DWORD PTR [esp+0x20],0x24
        nop
    loc_00431CD0:
        mov  ebx,DWORD PTR [ebp+0x24]
        xor  edx,edx
        lea  ecx,[esi-0x1]
        cmp  ebx,ecx
        mov  ecx,DWORD PTR ds:0x4776e0
        setne dl
        dec  edx
        and  edx,0x7f7e80
        add  edx,0xff808080
        mov  DWORD PTR [ecx+0x8974],edx
        mov  eax,DWORD PTR [ebp+0x59dc]
        mov  edx,DWORD PTR [ebp+eax*4+0x59e4]
        mov  eax,DWORD PTR [esp+0x20]
        add  eax,edx
        mov  edx,DWORD PTR [eax+0xb0]
        test  edx,edx
        jne loc_00431D2F
        mov  edx,DWORD PTR [esi*4+0x47471c]
        push  edx
        push  0x46f008
        push  ecx
        lea  ebx,[esp+0x1c]
        call FUN_00401630
        add  esp,0xc
        jmp loc_00431D75
    loc_00431D2F:
        cmp  esi,0x6
        jge loc_00431D53
        mov  eax,DWORD PTR [eax+0xd4]
        test  eax,eax
        je loc_00431D53
        mov  edx,DWORD PTR [eax+0x1b4]
        mov  eax,DWORD PTR [eax+0xc]
        push  edx
        mov  edx,DWORD PTR [esi*4+0x47471c]
        push  eax
        push  edx
        jmp loc_00431D63
    loc_00431D53:
        mov  eax,DWORD PTR [edi+0x60]
        mov  edx,DWORD PTR [edi+0x10]
        push  eax
        mov  eax,DWORD PTR [esi*4+0x47471c]
        push  edx
        push  eax
    loc_00431D63:
        push  0x46ef68
        lea  ebx,[esp+0x20]
        push  ecx
        call FUN_00401630
        add  esp,0x14
    loc_00431D75:
        fld  DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x20]
        fadd  DWORD PTR ds:0x470c0c
        inc  esi
        add  ecx,0x24
        cmp  esi,0x8
        fstp  DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x20],ecx
        jl loc_00431CD0
        jmp loc_00431EB1
    loc_00431D9D:
        mov  ecx,DWORD PTR ds:0x4776e0
        lea  edx,[ebp+0x59e4]
        mov  DWORD PTR [esp+0x10],0x42680000
        mov  DWORD PTR [esp+0x14],0x42a00000
        mov  DWORD PTR [esp+0x18],0x0
        mov  DWORD PTR [ecx+0x8988],0x1
        xor  edi,edi
        mov  DWORD PTR [esp+0x20],edx
        jmp loc_00431DE0
    loc_00431DD3:
        mov  ecx,DWORD PTR ds:0x4776e0
        nop
    loc_00431DE0:
        mov  esi,DWORD PTR [ebp+0x24]
        mov  edx,DWORD PTR [esp+0x20]
        xor  eax,eax
        cmp  esi,edi
        setne al
        dec  eax
        and  eax,0x7f7e80
        add  eax,0xff808080
        mov  DWORD PTR [ecx+0x8974],eax
        mov  eax,DWORD PTR [edx]
        test  eax,eax
        je loc_00431E7B
        mov  esi,DWORD PTR [eax+0x18]
        lea  eax,[esi+0xc]
        push  eax
        call _localtime
        fld  DWORD PTR [esi+0x48]
        push  ecx
        mov  ecx,DWORD PTR [esi+0x5c]
        fstp  QWORD PTR [esp]
        mov  edx,DWORD PTR [ecx*4+0x474744]
        mov  ecx,DWORD PTR [esi+0x58]
        push  edx
        mov  edx,DWORD PTR [ecx*4+0x4746f4]
        mov  ecx,DWORD PTR [esi+0x50]
        push  edx
        mov  edx,DWORD PTR [esi+0x54]
        lea  ecx,[ecx+ecx*2]
        add  ecx,edx
        mov  edx,DWORD PTR [ecx*4+0x4746dc]
        mov  ecx,DWORD PTR [eax+0x4]
        push  edx
        mov  edx,DWORD PTR [eax+0x8]
        push  ecx
        mov  ecx,DWORD PTR [eax+0xc]
        push  edx
        mov  edx,DWORD PTR [eax+0x10]
        mov  eax,DWORD PTR [eax+0x14]
        push  ecx
        inc  edi
        inc  edx
        push  edx
        cdq
        mov  ecx,0x64
        idiv  ecx
        lea  ebx,[esp+0x34]
        push  edx
        mov  edx,DWORD PTR ds:0x4776e0
        push  esi
        push  edi
        push  0x46efb0
        push  edx
        call FUN_00401630
        add  esp,0x38
        jmp loc_00431E8F
    loc_00431E7B:
        inc  edi
        push  edi
        push  0x46ef74
        push  ecx
        lea  ebx,[esp+0x1c]
        call FUN_00401630
        add  esp,0xc
    loc_00431E8F:
        fld  DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x20]
        fadd  DWORD PTR ds:0x470c08
        add  ecx,0x4
        cmp  edi,0x19
        mov  DWORD PTR [esp+0x20],ecx
        fstp  DWORD PTR [esp+0x14]
        jl loc_00431DD3
    loc_00431EB1:
        mov  eax,ds:0x4776e0
        mov  DWORD PTR [eax+0x8974],0xffffffff
        mov  DWORD PTR [eax+0x8988],0x0
    loc_00431ECA:
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}

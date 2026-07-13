// 00433B30: FUN_00433b30
// Original size: 960 bytes, actual code: 260 instructions
extern "C" void FUN_00401630(void);
extern "C" void _localtime(void);

extern "C" __declspec(naked) void FUN_00433b30(void) {
    __asm {
        sub  esp,0x10
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [esi+0x20]
        sub  eax,0x2
        push  edi
        je loc_00433DBF
        dec  eax
        jne loc_00433EDC
        mov  eax,DWORD PTR [esi+0x2b4]
        mov  edi,DWORD PTR [esi+0x59dc]
        mov  ebp,0xa
        cmp  eax,ebp
        mov  DWORD PTR [esp+0x14],0x42680000
        mov  DWORD PTR [esp+0x18],0x43700000
        mov  DWORD PTR [esp+0x1c],0x0
        jge loc_00433BAF
        fld  DWORD PTR ds:0x470c1c
        mov  eax,edi
        fsub  DWORD PTR [esi+0x2b8]
        imul  eax,eax,0xf
        add  eax,0x50
        mov  DWORD PTR [esp+0x10],eax
        fild  DWORD PTR [esp+0x10]
        fsub  DWORD PTR ds:0x470bfc
        fmulp st(1),st
        fmul  DWORD PTR ds:0x470c18
        fadd  DWORD PTR ds:0x470bfc
        fstp  DWORD PTR [esp+0x18]
    loc_00433BAF:
        mov  ecx,DWORD PTR ds:0x477838
        mov  esi,DWORD PTR [ecx+0x18]
        lea  edx,[esi+0xc]
        push  edx
        call _localtime
        fld  DWORD PTR [esi+0x48]
        mov  edx,DWORD PTR [esi+0x58]
        push  ecx
        mov  ecx,DWORD PTR ds:0x474764
        fstp  QWORD PTR [esp]
        push  ecx
        mov  ecx,DWORD PTR [edx*4+0x4746f4]
        push  ecx
        mov  ecx,DWORD PTR [esi+0x50]
        lea  edx,[ecx+ecx*2]
        add  edx,DWORD PTR [esi+0x54]
        mov  ecx,DWORD PTR [edx*4+0x4746dc]
        mov  edx,DWORD PTR [eax+0x4]
        push  ecx
        mov  ecx,DWORD PTR [eax+0x8]
        push  edx
        mov  edx,DWORD PTR [eax+0xc]
        push  ecx
        mov  ecx,DWORD PTR [eax+0x10]
        mov  eax,DWORD PTR [eax+0x14]
        push  edx
        inc  ecx
        push  ecx
        cdq
        mov  ecx,0x64
        idiv  ecx
        inc  edi
        lea  ebx,[esp+0x38]
        push  edx
        mov  edx,DWORD PTR ds:0x4776e0
        push  0x46e354
        push  edi
        push  0x46efb0
        push  edx
        call FUN_00401630
        mov  edi,DWORD PTR [esp+0x5c]
        mov  eax,DWORD PTR [edi+0x2b4]
        add  esp,0x38
        cmp  eax,ebp
        jl loc_00433EC3
        mov  eax,ds:0x4746d8
        lea  edx,[eax+0x1]
    loc_00433C41:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00433C41
        sub  eax,edx
        lea  ecx,[edi+0x58dc]
        push  ecx
        mov  ebp,eax
        mov  eax,ds:0x4776e0
        push  0x46e1c8
        or   esi,0xffffffff
        push  eax
        lea  ebx,[esp+0x20]
        mov  DWORD PTR [esp+0x20],0x42e00000
        mov  DWORD PTR [esp+0x24],0x43700000
        mov  DWORD PTR [esp+0x28],0x0
        mov  DWORD PTR [eax+0x8974],esi
        call FUN_00401630
        mov  eax,DWORD PTR [edi+0x58e8]
        lea  edx,[eax+eax*8]
        mov  DWORD PTR [esp+0x30],edx
        fild  DWORD PTR [esp+0x30]
        add  esp,0xc
        cmp  eax,0x8
        fadd  DWORD PTR ds:0x470c14
        fstp  DWORD PTR [esp+0x14]
        jne loc_00433CB9
        fld  DWORD PTR [esp+0x14]
        fsub  DWORD PTR ds:0x470c10
        fstp  DWORD PTR [esp+0x14]
    loc_00433CB9:
        mov  eax,ds:0x4776e0
        push  0x46e1c4
        push  eax
        lea  ebx,[esp+0x1c]
        mov  DWORD PTR [eax+0x8974],0xffffff00
        call FUN_00401630
        mov  eax,ds:0x4776e0
        mov  DWORD PTR [eax+0x8974],esi
        add  esp,0x8
        xor  esi,esi
        test  ebp,ebp
        mov  DWORD PTR [esp+0x14],0x43540000
        mov  DWORD PTR [esp+0x18],0x43b40000
        mov  DWORD PTR [esp+0x1c],0x0
        jle loc_00433DB0
        jmp loc_00433D10
        nop
    loc_00433D10:
        mov  edx,DWORD PTR [edi+0x58f4]
        xor  ecx,ecx
        cmp  edx,esi
        setne cl
        dec  ecx
        and  ecx,0x7f7e80
        add  ecx,0xff808080
        mov  DWORD PTR [eax+0x8974],ecx
        lea  ecx,[ebp-0x3]
        cmp  esi,ecx
        jge loc_00433D43
        mov  edx,DWORD PTR ds:0x4746d8
        movsx ecx,BYTE PTR [edx+esi*1]
        jmp loc_00433D59
    loc_00433D43:
        jne loc_00433D4C
        mov  ecx,0x81
        jmp loc_00433D59
    loc_00433D4C:
        xor  ecx,ecx
        lea  edx,[ebp-0x2]
        cmp  esi,edx
        setne cl
        add  ecx,0x7f
    loc_00433D59:
        push  ecx
        push  0x46e1c0
        lea  ebx,[esp+0x1c]
        push  eax
        call FUN_00401630
        xor  edx,edx
        mov  eax,esi
        mov  ecx,0xd
        div  ecx
        add  esp,0xc
        cmp  edx,0xc
        jne loc_00433D94
        fld  DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x14],0x43540000
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esp+0x18]
        jmp loc_00433DA2
    loc_00433D94:
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR ds:0x470c0c
        fstp  DWORD PTR [esp+0x14]
    loc_00433DA2:
        mov  eax,ds:0x4776e0
        inc  esi
        cmp  esi,ebp
        jl loc_00433D10
    loc_00433DB0:
        mov  DWORD PTR [eax+0x8974],0xffffffff
        jmp loc_00433EC8
    loc_00433DBF:
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [esp+0x14],0x42680000
        mov  DWORD PTR [esp+0x18],0x42a00000
        mov  DWORD PTR [esp+0x1c],0x0
        mov  DWORD PTR [ecx+0x8988],0x1
        xor  edi,edi
        lea  ebp,[esi+0x59e4]
        jmp loc_00433DF7
    loc_00433DF1:
        mov  ecx,DWORD PTR ds:0x4776e0
    loc_00433DF7:
        mov  eax,DWORD PTR [esi+0x24]
        xor  edx,edx
        cmp  eax,edi
        setne dl
        dec  edx
        and  edx,0x7f7e80
        add  edx,0xff808080
        mov  DWORD PTR [ecx+0x8974],edx
        mov  eax,DWORD PTR [ebp+0x0]
        test  eax,eax
        je loc_00433E95
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
        lea  ebx,[esp+0x38]
        push  edx
        mov  edx,DWORD PTR ds:0x4776e0
        push  esi
        push  edi
        push  0x46efb0
        push  edx
        call FUN_00401630
        mov  esi,DWORD PTR [esp+0x5c]
        add  esp,0x38
        jmp loc_00433EA9
    loc_00433E95:
        inc  edi
        push  edi
        push  0x46ef74
        push  ecx
        lea  ebx,[esp+0x20]
        call FUN_00401630
        add  esp,0xc
    loc_00433EA9:
        fld  DWORD PTR [esp+0x18]
        add  ebp,0x4
        cmp  edi,0x19
        fadd  DWORD PTR ds:0x470c08
        fstp  DWORD PTR [esp+0x18]
        jl loc_00433DF1
    loc_00433EC3:
        mov  eax,ds:0x4776e0
    loc_00433EC8:
        mov  DWORD PTR [eax+0x8974],0xffffffff
        mov  DWORD PTR [eax+0x8988],0x0
    loc_00433EDC:
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        add  esp,0x10
        ret  0x4
    }
}

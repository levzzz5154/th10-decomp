// 00422660: FUN_00422660
// Original size: 1072 bytes, actual code: 299 instructions
extern "C" void FUN_00401630(void);
extern "C" void FUN_004224c0(void);
extern "C" void _localtime(void);

extern "C" __declspec(naked) void FUN_00422660(void) {
    __asm {
        mov  ecx,DWORD PTR ds:0x4776e0
        sub  esp,0x10
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [ecx+0x8988],0x1
        mov  eax,DWORD PTR [ebp+0x4]
        add  eax,0xfffffff6
        cmp  eax,0x9
        push  esi
        push  edi
        ja loc_00422A52
        movzx eax,BYTE PTR [eax+0x422a7c]
        jmp  DWORD PTR [eax*4+0x422a6c]
        lea  edx,[ebp+0x1ec]
        mov  DWORD PTR [esp+0x14],0x42400000
        mov  DWORD PTR [esp+0x18],0x42800000
        mov  DWORD PTR [esp+0x1c],0x0
        xor  edi,edi
        mov  DWORD PTR [esp+0x24],edx
        nop
    loc_004226C0:
        mov  esi,DWORD PTR [ebp+0x24]
        mov  edx,DWORD PTR [esp+0x24]
        xor  eax,eax
        cmp  esi,edi
        setne al
        dec  eax
        and  eax,0x7f7e80
        add  eax,0xff808080
        mov  DWORD PTR [ecx+0x8974],eax
        mov  eax,DWORD PTR [edx]
        test  eax,eax
        je loc_0042274C
        mov  esi,DWORD PTR [eax+0x18]
        lea  eax,[esi+0xc]
        push  eax
        call _localtime
        mov  ecx,DWORD PTR [esi+0x5c]
        mov  edx,DWORD PTR [ecx*4+0x474744]
        mov  ecx,DWORD PTR [esi+0x58]
        push  edx
        mov  edx,DWORD PTR [ecx*4+0x474708]
        mov  ecx,DWORD PTR [esi+0x50]
        push  edx
        mov  edx,DWORD PTR [esi+0x54]
        lea  ecx,[ecx+ecx*2]
        add  ecx,edx
        mov  edx,DWORD PTR [ecx*4+0x4746dc]
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
        lea  ebx,[esp+0x2c]
        push  edx
        mov  edx,DWORD PTR ds:0x4776e0
        push  esi
        push  edi
        push  0x46e19c
        push  edx
        call FUN_00401630
        add  esp,0x2c
        jmp loc_00422760
    loc_0042274C:
        inc  edi
        push  edi
        push  0x46e174
        push  ecx
        lea  ebx,[esp+0x20]
        call FUN_00401630
        add  esp,0xc
    loc_00422760:
        fld  DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0x24]
        fadd  DWORD PTR ds:0x470c08
        add  ecx,0x4
        cmp  edi,0x19
        mov  DWORD PTR [esp+0x24],ecx
        mov  ecx,DWORD PTR ds:0x4776e0
        fstp  DWORD PTR [esp+0x18]
        jl loc_004226C0
        jmp loc_00422A48
        mov  eax,DWORD PTR [ebp+0x14]
        cmp  eax,0xa
        mov  edi,DWORD PTR [ebp+0x24]
        mov  DWORD PTR [esp+0x1c],0x0
        mov  DWORD PTR [esp+0x24],edi
        mov  DWORD PTR [esp+0x10],eax
        jge loc_004227D4
        fild  DWORD PTR [esp+0x24]
        fmul  DWORD PTR ds:0x470c08
        fadd  DWORD PTR ds:0x470bc8
        fld  DWORD PTR ds:0x470b4c
        fsub  st,st(1)
        fimul DWORD PTR [esp+0x10]
        fmul  DWORD PTR ds:0x470c18
        fadd  st,st(1)
        fstp  DWORD PTR [esp+0x18]
        fstp  st(0)
        jmp loc_004227DC
    loc_004227D4:
        mov  DWORD PTR [esp+0x18],0x43600000
    loc_004227DC:
        mov  edx,DWORD PTR [esp+0x18]
        sub  esp,0xc
        mov  eax,esp
        mov  DWORD PTR [esp+0x20],0x42cc0000
        mov  ecx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [esp+0x28]
        mov  DWORD PTR [eax+0x4],edx
        push  ebp
        mov  DWORD PTR [eax+0x8],ecx
        call FUN_004224c0
        mov  edx,DWORD PTR ds:0x477838
        mov  esi,DWORD PTR [edx+0x18]
        lea  eax,[esi+0xc]
        push  eax
        mov  DWORD PTR [esp+0x18],0x42400000
        call _localtime
        mov  ecx,DWORD PTR ds:0x474c7c
        mov  edx,DWORD PTR [ecx*4+0x474744]
        mov  ecx,DWORD PTR [esi+0x58]
        mov  ebx,DWORD PTR [esi+0x54]
        push  edx
        mov  edx,DWORD PTR [ecx*4+0x474708]
        mov  ecx,DWORD PTR [esi+0x50]
        push  edx
        lea  ecx,[ecx+ecx*2]
        add  ecx,ebx
        mov  edx,DWORD PTR [ecx*4+0x4746dc]
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
        inc  edi
        lea  ebx,[esp+0x2c]
        push  edx
        mov  edx,DWORD PTR ds:0x4776e0
        push  edi
        push  0x46e148
        push  edx
        call FUN_00401630
        mov  ecx,DWORD PTR ds:0x4776e0
        add  esp,0x28
        jmp loc_00422A52
        mov  eax,DWORD PTR [ebp+0x24]
        push  0x46e12c
        push  ecx
        lea  ebx,[esp+0x1c]
        mov  DWORD PTR [esp+0x1c],0x42400000
        mov  DWORD PTR [esp+0x24],0x0
        mov  DWORD PTR [esp+0x2c],eax
        mov  DWORD PTR [esp+0x20],0x42800000
        call FUN_00401630
        fild  DWORD PTR [esp+0x2c]
        mov  eax,DWORD PTR [ebp+0x1e8]
        add  esp,0x8
        test  eax,eax
        fmul  DWORD PTR ds:0x470c0c
        mov  DWORD PTR [esp+0x14],0x42960000
        fadd  DWORD PTR ds:0x470c80
        fstp  DWORD PTR [esp+0x18]
        jne loc_004228FB
        mov  edx,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x18]
        sub  esp,0xc
        mov  ecx,esp
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [esp+0x28]
        mov  DWORD PTR [ecx+0x4],eax
        push  ebp
        mov  DWORD PTR [ecx+0x8],edx
        call FUN_004224c0
        jmp loc_00422903
    loc_004228FB:
        mov  DWORD PTR [esp+0x24],0xffffffff
    loc_00422903:
        mov  DWORD PTR [esp+0x14],0x42400000
        mov  DWORD PTR [esp+0x18],0x42c00000
        xor  esi,esi
        jmp loc_00422920
        nop
        mov  edi,edi
    loc_00422920:
        mov  edx,DWORD PTR [esp+0x24]
        mov  ebx,DWORD PTR ds:0x4776e0
        xor  eax,eax
        cmp  esi,edx
        setne al
        mov  edi,DWORD PTR ds:0x47783c
        dec  eax
        and  eax,0x7f7e80
        add  eax,0xff808080
        mov  DWORD PTR [ebx+0x8974],eax
        mov  ecx,DWORD PTR ds:0x474c68
        mov  edx,DWORD PTR ds:0x474c6c
        lea  eax,[edx+ecx*2]
        add  eax,ecx
        mov  ecx,DWORD PTR ds:0x474c74
        imul  eax,eax,0x437c
        lea  ecx,[ecx+ecx*4]
        lea  ecx,[esi+ecx*2]
        lea  ecx,[ecx+ecx*2]
        shl  ecx,0x3
        lea  edx,[ecx+eax*1]
        mov  ebp,DWORD PTR [edx+edi*1+0x28]
        add  edx,edi
        test  ebp,ebp
        je loc_00422A0A
        lea  eax,[eax+edi*1+0x8]
        lea  eax,[ecx+eax*1+0x20]
        push  eax
        call _localtime
        mov  ecx,DWORD PTR ds:0x474c68
        mov  edx,DWORD PTR ds:0x474c6c
        mov  ebp,DWORD PTR ds:0x47783c
        lea  edx,[edx+ecx*2]
        add  edx,ecx
        mov  ecx,DWORD PTR ds:0x474c74
        imul  edx,edx,0x437c
        add  edx,ebp
        lea  ecx,[ecx+ecx*4]
        lea  ecx,[esi+ecx*2]
        lea  ecx,[ecx+ecx*2]
        lea  ecx,[edx+ecx*8]
        movsx edx,BYTE PTR [ecx+0x1c]
        mov  edx,DWORD PTR [edx*4+0x47471c]
        push  edx
        mov  edx,DWORD PTR [eax+0xc]
        push  edx
        mov  edx,DWORD PTR [eax+0x10]
        mov  eax,DWORD PTR [eax+0x14]
        inc  esi
        inc  edx
        push  edx
        cdq
        mov  edi,0x64
        idiv  edi
        movsx eax,BYTE PTR [ecx+0x1d]
        add  ecx,0x1e
        lea  ebx,[esp+0x24]
        push  edx
        mov  edx,DWORD PTR [ecx-0x6]
        push  eax
        mov  eax,ds:0x4776e0
        push  edx
        push  ecx
        push  esi
        push  0x46e108
        push  eax
        call FUN_00401630
        add  esp,0x2c
        jmp loc_00422A2B
    loc_00422A0A:
        movsx ecx,BYTE PTR [edx+0x1d]
        mov  eax,DWORD PTR [edx+0x18]
        push  ecx
        push  eax
        add  edx,0x1e
        push  edx
        inc  esi
        push  esi
        push  0x46e0e8
        push  ebx
        lea  ebx,[esp+0x2c]
        call FUN_00401630
        add  esp,0x18
    loc_00422A2B:
        cmp  esi,0xa
        fld  DWORD PTR [esp+0x18]
        fadd  DWORD PTR ds:0x470c0c
        fstp  DWORD PTR [esp+0x18]
        jl loc_00422920
        mov  ecx,DWORD PTR ds:0x4776e0
    loc_00422A48:
        mov  DWORD PTR [ecx+0x8974],0xffffffff
    loc_00422A52:
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR [ecx+0x8988],0x0
        mov  eax,0x1
        pop  ebx
        add  esp,0x10
        ret  0x4
    }
}

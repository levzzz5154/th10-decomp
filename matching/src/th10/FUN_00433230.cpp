// 00433230: FUN_00433230
// Original size: 832 bytes, actual code: 228 instructions
extern "C" void FUN_00401630(void);
extern "C" void _localtime(void);

extern "C" __declspec(naked) void FUN_00433230(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [eax+0x20]
        sub  esp,0xc
        sub  ecx,0x2
        jne loc_0043355F
        push  ebx
        mov  ebx,DWORD PTR ds:0x4776e0
        push  ebp
        push  esi
        push  edi
        mov  edi,DWORD PTR ds:0x474c74
        xor  esi,esi
        imul  edi,edi,0xf0
        mov  DWORD PTR [esp+0x10],0x42400000
        mov  DWORD PTR [esp+0x14],0x43200000
        mov  DWORD PTR [esp+0x18],0x0
        mov  DWORD PTR [ebx+0x8988],0x1
        mov  ebp,0xff
        jmp loc_00433290
    loc_00433284:
        mov  ebx,DWORD PTR ds:0x4776e0
        mov  eax,DWORD PTR [esp+0x20]
        mov  edi,edi
    loc_00433290:
        mov  ecx,DWORD PTR [eax+0x58ec]
        test  ecx,ecx
        je loc_004332B1
        mov  eax,ebp
        shl  eax,0x8
        or   eax,ebp
        shl  eax,0x8
        or   eax,0xff0000ff
        mov  DWORD PTR [ebx+0x8974],eax
        jmp loc_004332C9
    loc_004332B1:
        mov  edx,DWORD PTR [eax+0x24]
        xor  ecx,ecx
        cmp  edx,esi
        sete  cl
        dec  ecx
        and  ecx,0xff404041
        dec  ecx
        mov  DWORD PTR [ebx+0x8974],ecx
    loc_004332C9:
        mov  ecx,DWORD PTR ds:0x474c68
        mov  edx,DWORD PTR ds:0x474c6c
        lea  eax,[edx+ecx*2]
        mov  edx,DWORD PTR ds:0x47783c
        add  eax,ecx
        imul  eax,eax,0x437c
        lea  ecx,[edi+eax*1]
        add  ecx,edx
        cmp  DWORD PTR [ecx+0x28],0x0
        je loc_0043337A
        lea  eax,[eax+edx*1+0x8]
        lea  edx,[edi+eax*1+0x20]
        push  edx
        call _localtime
        mov  ecx,DWORD PTR ds:0x474c68
        mov  edx,DWORD PTR ds:0x474c6c
        lea  edx,[edx+ecx*2]
        add  edx,ecx
        mov  ecx,DWORD PTR ds:0x47783c
        imul  edx,edx,0x437c
        add  edx,edi
        add  ecx,edx
        movsx edx,BYTE PTR [ecx+0x1c]
        fld  DWORD PTR [ecx+0x2c]
        mov  edx,DWORD PTR [edx*4+0x47471c]
        push  ecx
        inc  esi
        add  ecx,0x1e
        fstp  QWORD PTR [esp]
        push  edx
        mov  edx,DWORD PTR [eax+0x4]
        push  edx
        mov  edx,DWORD PTR [eax+0x8]
        push  edx
        mov  edx,DWORD PTR [eax+0xc]
        push  edx
        mov  edx,DWORD PTR [eax+0x10]
        mov  eax,DWORD PTR [eax+0x14]
        inc  edx
        push  edx
        movsx edx,BYTE PTR [ecx-0x1]
        add  eax,0x76c
        push  eax
        mov  eax,DWORD PTR [ecx-0x6]
        push  edx
        push  eax
        push  ecx
        mov  ecx,DWORD PTR ds:0x4776e0
        push  esi
        push  0x46ee84
        push  ecx
        lea  ebx,[esp+0x48]
        call FUN_00401630
        add  esp,0x38
        jmp loc_004333A4
    loc_0043337A:
        movsx edx,BYTE PTR [ecx+0x1d]
        fld  DWORD PTR [ecx+0x2c]
        mov  eax,DWORD PTR [ecx+0x18]
        sub  esp,0x8
        add  ecx,0x1e
        inc  esi
        fstp  QWORD PTR [esp]
        push  edx
        push  eax
        push  ecx
        push  esi
        push  0x46ee50
        push  ebx
        lea  ebx,[esp+0x30]
        call FUN_00401630
        add  esp,0x20
    loc_004333A4:
        fld  DWORD PTR [esp+0x14]
        sub  ebp,0x10
        fadd  DWORD PTR ds:0x470c0c
        add  edi,0x18
        cmp  ebp,0x5f
        fstp  DWORD PTR [esp+0x14]
        jg loc_00433284
        mov  edi,DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [edi+0x58ec]
        test  eax,eax
        jne loc_0043355B
        mov  eax,ds:0x4746d8
        lea  edx,[eax+0x1]
        jmp loc_004333E0
        nop
    loc_004333E0:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_004333E0
        fild  DWORD PTR [edi+0x24]
        sub  eax,edx
        lea  ecx,[edi+0x58dc]
        push  ecx
        fmul  DWORD PTR ds:0x470c0c
        mov  ebp,eax
        mov  eax,ds:0x4776e0
        push  0x46e1c8
        fadd  DWORD PTR ds:0x470c24
        or   esi,0xffffffff
        push  eax
        lea  ebx,[esp+0x1c]
        fstp  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x1c],0x42a80000
        mov  DWORD PTR [esp+0x24],0x0
        mov  DWORD PTR [eax+0x8974],esi
        call FUN_00401630
        mov  eax,DWORD PTR [edi+0x58e8]
        lea  edx,[eax+eax*8]
        mov  DWORD PTR [esp+0x2c],edx
        fild  DWORD PTR [esp+0x2c]
        add  esp,0xc
        cmp  eax,0x8
        fadd  DWORD PTR ds:0x470c20
        fstp  DWORD PTR [esp+0x10]
        jne loc_00433463
        fld  DWORD PTR [esp+0x10]
        fsub  DWORD PTR ds:0x470c10
        fstp  DWORD PTR [esp+0x10]
    loc_00433463:
        mov  eax,ds:0x4776e0
        push  0x46e1c4
        push  eax
        lea  ebx,[esp+0x18]
        mov  DWORD PTR [eax+0x8974],0xffffff00
        call FUN_00401630
        mov  eax,ds:0x4776e0
        mov  DWORD PTR [eax+0x8974],esi
        add  esp,0x8
        xor  esi,esi
        test  ebp,ebp
        mov  DWORD PTR [esp+0x10],0x43540000
        mov  DWORD PTR [esp+0x14],0x43b40000
        mov  DWORD PTR [esp+0x18],0x0
        jle loc_00433551
    loc_004334B1:
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
        jge loc_004334E4
        mov  edx,DWORD PTR ds:0x4746d8
        movsx ecx,BYTE PTR [edx+esi*1]
        jmp loc_004334FA
    loc_004334E4:
        jne loc_004334ED
        mov  ecx,0x81
        jmp loc_004334FA
    loc_004334ED:
        xor  ecx,ecx
        lea  edx,[ebp-0x2]
        cmp  esi,edx
        setne cl
        add  ecx,0x7f
    loc_004334FA:
        push  ecx
        push  0x46e1c0
        lea  ebx,[esp+0x18]
        push  eax
        call FUN_00401630
        xor  edx,edx
        mov  eax,esi
        mov  ecx,0xd
        div  ecx
        add  esp,0xc
        cmp  edx,0xc
        jne loc_00433535
        fld  DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x10],0x43540000
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esp+0x14]
        jmp loc_00433543
    loc_00433535:
        fld  DWORD PTR [esp+0x10]
        fadd  DWORD PTR ds:0x470c0c
        fstp  DWORD PTR [esp+0x10]
    loc_00433543:
        mov  eax,ds:0x4776e0
        inc  esi
        cmp  esi,ebp
        jl loc_004334B1
    loc_00433551:
        mov  DWORD PTR [eax+0x8974],0xffffffff
    loc_0043355B:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
    loc_0043355F:
        mov  eax,0x1
        add  esp,0xc
        ret  0x4
    }
}

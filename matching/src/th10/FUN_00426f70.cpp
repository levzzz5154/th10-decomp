// 00426F70: FUN_00426f70
// Original size: 2528 bytes, actual code: 651 instructions
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00448e30(void);
extern "C" void FUN_00449470(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00426f70(void) {
    __asm {
        sub  esp,0x38
        mov  cx,WORD PTR ds:0x474c48
        movsx edx,cx
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x3
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x44]
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cmp  cx,0x64
        push  esi
        push  edi
        mov  DWORD PTR [esp+0x4c],eax
        mov  ebx,0x4000000
        jl loc_004270E6
        lea  esi,[ebp+0x330c]
        mov  DWORD PTR [esp+0x10],0x4
    loc_00426FB7:
        mov  ecx,DWORD PTR [esi]
        test  ecx,ecx
        je loc_0042702F
        mov  edx,DWORD PTR ds:0x491c10
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_00426FDD
        nop
    loc_00426FD0:
        mov  edi,DWORD PTR [eax]
        cmp  DWORD PTR [edi],ecx
        je loc_00426FF6
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00426FD0
    loc_00426FDD:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_0042702F
    loc_00426FE7:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00426FF6
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00426FE7
        jmp loc_0042702F
    loc_00426FF6:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_0042702F
        mov  edx,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   edx,ebx
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],edx
        jne loc_0042702F
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0042702F
        jmp loc_00427020
        lea  ebx,[ebx+0x0]
    loc_00427020:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],ebx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00427020
    loc_0042702F:
        mov  DWORD PTR [esi],0x0
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        lea  edx,[ecx+eax*2]
        add  eax,edx
        cmp  eax,0x5
        ja loc_004270CC
        jmp  DWORD PTR [eax*4+0x427930]
        mov  eax,DWORD PTR [ebp+0x10]
        push  0xf
        push  0x14
        push  eax
        lea  edi,[esp+0x3c]
        call FUN_00448e30
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esi],ecx
        jmp loc_004270CC
        mov  edx,DWORD PTR [ebp+0x10]
        push  0xf
        push  0x15
        push  edx
        lea  edi,[esp+0x40]
        call FUN_00448e30
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [esi],eax
        jmp loc_004270CC
        lea  edi,[esp+0x38]
        jmp loc_004270BB
        mov  eax,DWORD PTR [ebp+0x10]
        push  0xf
        push  0x14
        push  eax
        lea  edi,[esp+0x48]
        call FUN_00448e30
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esi],ecx
        jmp loc_004270CC
        mov  edx,DWORD PTR [ebp+0x10]
        push  0xf
        push  0x15
        push  edx
        lea  edi,[esp+0x4c]
        call FUN_00448e30
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [esi],eax
        jmp loc_004270CC
        lea  edi,[esp+0x44]
    loc_004270BB:
        mov  ecx,DWORD PTR [ebp+0x10]
        push  0xf
        push  0x16
        push  ecx
        call FUN_00448e30
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [esi],edx
    loc_004270CC:
        mov  eax,DWORD PTR [esp+0x10]
        add  esi,0x98
        dec  eax
        mov  DWORD PTR [esp+0x10],eax
        jne loc_00426FB7
        jmp loc_00427169
    loc_004270E6:
        mov  ebx,DWORD PTR ds:0x491c10
        lea  edx,[ebp+0x330c]
        mov  esi,0x4
    loc_004270F7:
        mov  ecx,DWORD PTR [edx]
        test  ecx,ecx
        je loc_00427160
        mov  eax,DWORD PTR [ebx+0x72dad4]
        test  eax,eax
        je loc_00427114
    loc_00427107:
        mov  edi,DWORD PTR [eax]
        cmp  DWORD PTR [edi],ecx
        je loc_0042712F
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00427107
    loc_00427114:
        mov  eax,DWORD PTR [ebx+0x72dadc]
        test  eax,eax
        je loc_00427160
        mov  edi,edi
    loc_00427120:
        mov  edi,DWORD PTR [eax]
        cmp  DWORD PTR [edi],ecx
        je loc_0042712F
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00427120
        jmp loc_00427160
    loc_0042712F:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00427160
        mov  edi,DWORD PTR [eax+0x18]
        test  edi,edi
        mov  ecx,0x1
        mov  WORD PTR [eax+0x304],cx
        jne loc_00427160
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00427160
        nop
    loc_00427150:
        mov  edi,DWORD PTR [eax]
        mov  WORD PTR [edi+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00427150
    loc_00427160:
        add  edx,0x98
        dec  esi
        jne loc_004270F7
    loc_00427169:
        mov  eax,DWORD PTR [esp+0x4c]
        cmp  eax,0x5
        jl loc_0042717B
        mov  eax,0x4
        mov  DWORD PTR [esp+0x4c],eax
    loc_0042717B:
        cmp  DWORD PTR [ebp+0x3500],eax
        je loc_00427924
        xor  esi,esi
        test  eax,eax
        mov  DWORD PTR [esp+0x10],esi
        jle loc_00427857
        jmp loc_004271A0
        nop
        mov  edi,edi
    loc_004271A0:
        mov  ecx,DWORD PTR [ebp+0x3cc]
        mov  eax,esi
        imul  eax,eax,0x98
        lea  edi,[eax+ebp*1]
        mov  DWORD PTR [edi+0x32dc],ecx
        mov  edx,DWORD PTR [ebp+0x3d0]
        mov  DWORD PTR [edi+0x32e0],edx
        mov  ecx,DWORD PTR [edi+0x3308]
        test  ecx,ecx
        je loc_0042723F
        mov  edx,DWORD PTR ds:0x491c10
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_004271ED
        nop
    loc_004271E0:
        mov  ebx,DWORD PTR [eax]
        cmp  DWORD PTR [ebx],ecx
        je loc_00427206
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004271E0
    loc_004271ED:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_0042723F
    loc_004271F7:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00427206
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004271F7
        jmp loc_0042723F
    loc_00427206:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_0042723F
        mov  ebx,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        mov  edx,0x4000000
        or   ebx,edx
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],ebx
        jne loc_0042723F
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0042723F
        nop
    loc_00427230:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00427230
    loc_0042723F:
        mov  DWORD PTR [edi+0x3308],0x0
        mov  DWORD PTR [edi+0x3328],esi
        mov  eax,ds:0x474c68
        sub  eax,0x0
        je loc_0042764E
        dec  eax
        jne loc_00427833
        mov  eax,ds:0x474c6c
        sub  eax,0x0
        je loc_0042749B
        dec  eax
        je loc_00427381
        dec  eax
        jne loc_00427833
        mov  eax,DWORD PTR [esp+0x4c]
        mov  eax,DWORD PTR [eax*4+0x476f7c]
        mov  edx,DWORD PTR [ebp+0x45c]
        add  eax,esi
        lea  ecx,[eax+eax*2]
        fld  DWORD PTR [edx+ecx*4+0x20]
        lea  esi,[edx+ecx*4+0x20]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x32e4],eax
        fld  DWORD PTR [esi+0x4]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x32e8],eax
        mov  eax,DWORD PTR [ebp+0x4474]
        test  eax,eax
        je loc_004272D7
        mov  eax,DWORD PTR [edi+0x32a0]
        test  eax,eax
        jne loc_0042730B
    loc_004272D7:
        mov  eax,DWORD PTR [ebp+0x3cc]
        mov  esi,DWORD PTR [edi+0x32e4]
        mov  ecx,DWORD PTR [edi+0x32e8]
        mov  edx,DWORD PTR [ebp+0x3d0]
        add  eax,esi
        add  ecx,edx
        mov  DWORD PTR [edi+0x32d4],eax
        mov  DWORD PTR [edi+0x32d8],ecx
        mov  DWORD PTR [edi+0x32ec],eax
        mov  DWORD PTR [edi+0x32f0],ecx
    loc_0042730B:
        mov  esi,DWORD PTR ds:0x491c10
        mov  ebx,DWORD PTR [ebp+0x10]
        call FUN_00449950
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x35c]
        push  0x13
        or   eax,0x40000000
        push  esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x20],0xf
        mov  DWORD PTR [esi+0x35c],eax
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x14]
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [edi+0x3308],eax
        mov  eax,DWORD PTR [ebp+0x4474]
        test  eax,eax
        je loc_00427372
        mov  esi,0x3
        lea  eax,[edi+0x3308]
        call FUN_00449470
    loc_00427372:
        mov  DWORD PTR [edi+0x3330],0x427ad0
        jmp loc_0042782F
    loc_00427381:
        mov  ecx,DWORD PTR [esp+0x4c]
        mov  eax,DWORD PTR [ecx*4+0x476f7c]
        add  eax,esi
        lea  edx,[eax+eax*2]
        mov  eax,DWORD PTR [ebp+0x45c]
        fld  DWORD PTR [eax+edx*4+0x20]
        lea  eax,[eax+edx*4+0x20]
        fmul  DWORD PTR ds:0x470b44
        mov  DWORD PTR [esp+0x18],eax
        lea  ebx,[edi+0x32e4]
        call FUN_00463b2c
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [ebx],eax
        fld  DWORD PTR [ecx+0x4]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  edx,DWORD PTR [esp+0x4c]
        mov  DWORD PTR [ebx+0x4],eax
        mov  eax,DWORD PTR [edx*4+0x476f7c]
        mov  ecx,DWORD PTR [ebp+0x45c]
        add  eax,esi
        lea  eax,[eax+eax*2]
        fld  DWORD PTR [ecx+eax*4+0x98]
        lea  eax,[ecx+eax*4+0x98]
        fmul  DWORD PTR ds:0x470b44
        mov  DWORD PTR [esp+0x18],eax
        lea  esi,[edi+0x32ec]
        call FUN_00463b2c
        mov  edx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esi],eax
        fld  DWORD PTR [edx+0x4]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [esi+0x4],eax
        mov  eax,DWORD PTR [ebp+0x4474]
        test  eax,eax
        jne loc_00427427
        mov  esi,ebx
    loc_00427427:
        mov  eax,DWORD PTR [esi]
        mov  ecx,DWORD PTR [ebp+0x3cc]
        mov  ebx,DWORD PTR [esi+0x4]
        mov  esi,DWORD PTR ds:0x491c10
        add  eax,ecx
        mov  ecx,DWORD PTR [ebp+0x3d0]
        add  ecx,ebx
        mov  DWORD PTR [edi+0x32d4],eax
        mov  DWORD PTR [edi+0x32d8],ecx
        mov  ebx,DWORD PTR [ebp+0x10]
        call FUN_00449950
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x35c]
        push  0x12
        or   edx,0x40000000
        push  esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x20],0xf
        mov  DWORD PTR [esi+0x35c],edx
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x1c]
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [edi+0x3308],eax
        jmp loc_0042782F
    loc_0042749B:
        mov  eax,DWORD PTR [ebp+0x4474]
        test  eax,eax
        jne loc_004274E8
        mov  ecx,DWORD PTR [esp+0x4c]
        mov  eax,DWORD PTR [ecx*4+0x476f7c]
        add  eax,esi
        lea  edx,[eax+eax*2]
        mov  eax,DWORD PTR [ebp+0x45c]
        fld  DWORD PTR [eax+edx*4+0x20]
        lea  ebx,[eax+edx*4+0x20]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x32e4],eax
        fld  DWORD PTR [ebx+0x4]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x32e8],eax
    loc_004274E8:
        mov  ecx,DWORD PTR [esp+0x4c]
        mov  eax,DWORD PTR [ecx*4+0x476f7c]
        add  eax,esi
        lea  edx,[eax+eax*2]
        mov  eax,DWORD PTR [ebp+0x45c]
        fld  DWORD PTR [eax+edx*4+0x98]
        lea  ebx,[eax+edx*4+0x98]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x32ec],eax
        fld  DWORD PTR [ebx+0x4]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  ecx,DWORD PTR ds:0x477834
        mov  DWORD PTR [edi+0x32f0],eax
        mov  eax,esi
        shl  eax,0x6
        mov  edx,DWORD PTR [eax+ecx*1+0x43ac]
        mov  DWORD PTR [esp+0x18],eax
        mov  DWORD PTR [edi+0x32d4],edx
        mov  eax,DWORD PTR [eax+ecx*1+0x43b0]
        mov  DWORD PTR [edi+0x32d8],eax
        mov  eax,DWORD PTR [ebp+0x4474]
        test  eax,eax
        je loc_004275D3
        mov  eax,DWORD PTR [edi+0x32a0]
        test  eax,eax
        jne loc_004275D3
        test  esi,esi
        jne loc_004275BB
        mov  ecx,DWORD PTR [esp+0x4c]
        mov  eax,DWORD PTR [ecx*4+0x476f7c]
        lea  edx,[eax+eax*2]
        mov  eax,DWORD PTR [ebp+0x45c]
        fld  DWORD PTR [eax+edx*4+0x98]
        lea  esi,[eax+edx*4+0x98]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x32e4],eax
        fld  DWORD PTR [esi+0x4]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x32e8],eax
        jmp loc_004275D3
    loc_004275BB:
        mov  ecx,DWORD PTR [edi+0x324c]
        mov  DWORD PTR [edi+0x32e4],ecx
        mov  edx,DWORD PTR [edi+0x3250]
        mov  DWORD PTR [edi+0x32e8],edx
    loc_004275D3:
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [edi+0x3330],0x427950
        mov  ebx,DWORD PTR [ebp+0x10]
        call FUN_00449950
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x35c]
        push  0x11
        or   edx,0x40000000
        push  esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x20],0xf
        mov  DWORD PTR [esi+0x35c],edx
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x20]
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x20]
        mov  DWORD PTR [edi+0x3308],eax
        mov  eax,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [eax+ebp*1+0x436c]
        mov  DWORD PTR [edi+0x32dc],ecx
        mov  edx,DWORD PTR [eax+ebp*1+0x4370]
        mov  DWORD PTR [edi+0x32e0],edx
        jmp loc_0042782F
    loc_0042764E:
        mov  eax,DWORD PTR [esp+0x4c]
        mov  eax,DWORD PTR [eax*4+0x476f7c]
        mov  edx,DWORD PTR [ebp+0x45c]
        add  eax,esi
        lea  ecx,[eax+eax*2]
        fld  DWORD PTR [edx+ecx*4+0x20]
        lea  eax,[edx+ecx*4+0x20]
        fmul  DWORD PTR ds:0x470b44
        mov  DWORD PTR [esp+0x18],eax
        lea  ebx,[edi+0x32e4]
        call FUN_00463b2c
        mov  DWORD PTR [ebx],eax
        mov  eax,DWORD PTR [esp+0x18]
        fld  DWORD PTR [eax+0x4]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  ecx,DWORD PTR [esp+0x4c]
        mov  DWORD PTR [ebx+0x4],eax
        mov  eax,DWORD PTR [ecx*4+0x476f7c]
        add  eax,esi
        lea  edx,[eax+eax*2]
        mov  eax,DWORD PTR [ebp+0x45c]
        fld  DWORD PTR [eax+edx*4+0x98]
        lea  eax,[eax+edx*4+0x98]
        fmul  DWORD PTR ds:0x470b44
        mov  DWORD PTR [esp+0x18],eax
        call FUN_00463b2c
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edi+0x32ec],eax
        fld  DWORD PTR [ecx+0x4]
        fmul  DWORD PTR ds:0x470b44
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x32f0],eax
        mov  eax,DWORD PTR [ebp+0x4474]
        test  eax,eax
        je loc_004276F9
        lea  ebx,[edi+0x32ec]
    loc_004276F9:
        mov  ecx,DWORD PTR [ebx]
        mov  eax,DWORD PTR [ebp+0x3cc]
        mov  edx,DWORD PTR [ebx+0x4]
        add  eax,ecx
        mov  ecx,DWORD PTR [ebp+0x3d0]
        add  ecx,edx
        mov  DWORD PTR [edi+0x32d4],eax
        mov  DWORD PTR [edi+0x32d8],ecx
        mov  DWORD PTR [edi+0x32dc],eax
        mov  DWORD PTR [edi+0x32e0],ecx
        mov  eax,ds:0x474c6c
        sub  eax,0x0
        je loc_004277E1
        dec  eax
        je loc_00427791
        dec  eax
        jne loc_00427833
        mov  esi,DWORD PTR ds:0x491c10
        mov  ebx,DWORD PTR [ebp+0x10]
        call FUN_00449950
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x35c]
        push  0x13
        or   edx,0x40000000
        push  esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x20],0xf
        mov  DWORD PTR [esi+0x35c],edx
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x24]
        call FUN_004489d0
        mov  edx,DWORD PTR [esp+0x24]
        mov  DWORD PTR [edi+0x3308],edx
        jmp loc_0042782F
    loc_00427791:
        mov  esi,DWORD PTR ds:0x491c10
        mov  ebx,DWORD PTR [ebp+0x10]
        call FUN_00449950
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x35c]
        push  0x12
        or   edx,0x40000000
        push  esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x20],0xf
        mov  DWORD PTR [esi+0x35c],edx
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x28]
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x28]
        mov  DWORD PTR [edi+0x3308],eax
        jmp loc_0042782F
    loc_004277E1:
        mov  esi,DWORD PTR ds:0x491c10
        mov  ebx,DWORD PTR [ebp+0x10]
        call FUN_00449950
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x35c]
        push  0x11
        or   edx,0x40000000
        push  esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x20],0xf
        mov  DWORD PTR [esi+0x35c],edx
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x2c]
        call FUN_004489d0
        mov  ecx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [edi+0x3308],ecx
    loc_0042782F:
        mov  esi,DWORD PTR [esp+0x10]
    loc_00427833:
        mov  eax,DWORD PTR [esp+0x4c]
        inc  esi
        cmp  esi,eax
        mov  DWORD PTR [edi+0x32a0],0x2
        mov  DWORD PTR [esp+0x10],esi
        jl loc_004271A0
        cmp  esi,0x4
        jge loc_004278FD
    loc_00427857:
        mov  ebx,DWORD PTR ds:0x491c10
        mov  edx,esi
        imul  edx,edx,0x98
        mov  edi,0x4
        lea  edx,[edx+ebp*1+0x3308]
        sub  edi,esi
    loc_00427873:
        mov  ecx,DWORD PTR [edx]
        test  ecx,ecx
        mov  DWORD PTR [edx-0x68],0x0
        je loc_004278F0
        mov  eax,DWORD PTR [ebx+0x72dad4]
        test  eax,eax
        je loc_0042789D
        lea  ebx,[ebx+0x0]
    loc_00427890:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_004278B6
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00427890
    loc_0042789D:
        mov  eax,DWORD PTR [ebx+0x72dadc]
        test  eax,eax
        je loc_004278F0
    loc_004278A7:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_004278B6
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004278A7
        jmp loc_004278F0
    loc_004278B6:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_004278F0
        mov  esi,DWORD PTR [eax+0x18]
        test  esi,esi
        mov  ecx,0x1
        mov  WORD PTR [eax+0x304],cx
        jne loc_004278F0
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_004278F0
        jmp loc_004278E0
        nop
        nop
    loc_004278E0:
        mov  esi,DWORD PTR [eax]
        mov  WORD PTR [esi+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004278E0
    loc_004278F0:
        add  edx,0x98
        dec  edi
        jne loc_00427873
    loc_004278FD:
        mov  ecx,DWORD PTR [esp+0x4c]
        mov  eax,0x1
        mov  DWORD PTR [ebp+0x3500],ecx
        mov  DWORD PTR [ebp+0x332c],eax
        mov  DWORD PTR [ebp+0x33c4],eax
        mov  DWORD PTR [ebp+0x345c],eax
        mov  DWORD PTR [ebp+0x34f4],eax
    loc_00427924:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0x38
        ret  0x4
        mov  edi,edi
        push  ebp
        jo FUN_00427975
        add  BYTE PTR [eax+esi*2+0x42],ch
        add  BYTE PTR [ebx-0x76ffbd90],al
        jo FUN_00427981
        add  BYTE PTR [eax-0x48ffbd90],ah
        jo FUN_00427989
        add  ah,cl
    }
}

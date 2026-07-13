// 004250B0: FUN_004250b0
// Original size: 1664 bytes, actual code: 451 instructions
extern "C" void FUN_0043e710(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00449210(void);
extern "C" void FUN_004492f0(void);
extern "C" void FUN_00449350(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004250b0(void) {
    __asm {
        sub  esp,0x18
        mov  al,ds:0x474e5c
        push  ebx
        mov  cl,al
        push  ebp
        xor  ebp,ebp
        xor  ebx,ebx
        and  cl,0x50
        cmp  cl,0x50
        push  esi
        mov  DWORD PTR [esp+0x10],ebp
        mov  DWORD PTR [esp+0xc],ebx
        mov  esi,0x1
        jne loc_004250E5
        mov  DWORD PTR [edi+0x454],0x5
        jmp loc_00425169
    loc_004250E5:
        mov  dl,al
        and  dl,0x60
        cmp  dl,0x60
        jne loc_004250FB
        mov  DWORD PTR [edi+0x454],0x7
        jmp loc_00425169
    loc_004250FB:
        mov  cl,al
        and  cl,0x90
        cmp  cl,0x90
        jne loc_00425111
        mov  DWORD PTR [edi+0x454],0x6
        jmp loc_00425169
    loc_00425111:
        mov  dl,al
        and  dl,0xa0
        cmp  dl,0xa0
        jne loc_00425127
        mov  DWORD PTR [edi+0x454],0x8
        jmp loc_00425169
    loc_00425127:
        test  al,0x20
        je loc_00425137
        mov  DWORD PTR [edi+0x454],0x2
        jmp loc_00425169
    loc_00425137:
        test  al,0x10
        je loc_00425143
        mov  DWORD PTR [edi+0x454],esi
        jmp loc_00425169
    loc_00425143:
        test  al,0x40
        je loc_00425153
        mov  DWORD PTR [edi+0x454],0x3
        jmp loc_00425169
    loc_00425153:
        test  al,al
        jns loc_00425163
        mov  DWORD PTR [edi+0x454],0x4
        jmp loc_00425169
    loc_00425163:
        mov  DWORD PTR [edi+0x454],ebp
    loc_00425169:
        mov  eax,ds:0x477704
        cmp  eax,ebp
        je loc_004251CA
        cmp  DWORD PTR [eax+0x60],ebp
        je loc_004251CA
        cmp  DWORD PTR [edi+0x48c],0x4
        jl loc_004251CA
        mov  eax,ds:0x474e5c
        shr  eax,0x2
        and  eax,esi
        mov  DWORD PTR [edi+0x4474],eax
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        lea  edx,[ecx+eax*2]
        add  edx,eax
        cmp  edx,0x5
        jne loc_004251DA
        test  BYTE PTR ds:0x474e5c,0x4
        je loc_004251B6
        mov  DWORD PTR [edi+0x4308],ebp
        jmp loc_004251DA
    loc_004251B6:
        mov  eax,DWORD PTR [edi+0x4308]
        cmp  eax,0x1e
        jge loc_004251DA
        inc  eax
        mov  DWORD PTR [edi+0x4308],eax
        jmp loc_004251DA
    loc_004251CA:
        mov  DWORD PTR [edi+0x4474],ebp
        mov  DWORD PTR [edi+0x4308],0x1e
    loc_004251DA:
        cmp  DWORD PTR [edi+0x4474],ebp
        je loc_004252D0
        cmp  DWORD PTR [edi+0x329c],ebp
        jne loc_0042524B
        mov  eax,ds:0x4776f0
        mov  esi,DWORD PTR ds:0x491c10
        mov  ebx,DWORD PTR [eax+0x3e0b50]
        call FUN_00449950
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x35c]
        push  0x160
        or   edx,0x40000000
        push  esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x20],0x9
        mov  DWORD PTR [esi+0x35c],edx
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        mov  ebx,esi
        lea  eax,[esp+0x14]
        call FUN_004489d0
        mov  ecx,DWORD PTR [esp+0x14]
        mov  ebx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [edi+0x329c],ecx
    loc_0042524B:
        mov  eax,DWORD PTR [edi+0x454]
        dec  eax
        cmp  eax,0x7
        ja loc_004253B2
        jmp  DWORD PTR [eax*4+0x4256e8]
        mov  ebp,DWORD PTR [edi+0x3d8]
        jmp loc_00425373
        mov  ebp,DWORD PTR [edi+0x3d8]
        neg  ebp
        jmp loc_00425373
        mov  ebx,DWORD PTR [edi+0x3d8]
        neg  ebx
        mov  DWORD PTR [esp+0xc],ebx
        jmp loc_004253B2
        mov  ebx,DWORD PTR [edi+0x3d8]
        mov  DWORD PTR [esp+0xc],ebx
        jmp loc_004253B2
        mov  ebp,DWORD PTR [edi+0x3e0]
        neg  ebp
        jmp loc_0042536D
        mov  ebx,DWORD PTR [edi+0x3e0]
        mov  ebp,ebx
        neg  ebp
        jmp loc_0042536F
        mov  ebp,DWORD PTR [edi+0x3e0]
        mov  ebx,ebp
        neg  ebx
        jmp loc_0042536F
        mov  ebp,DWORD PTR [edi+0x3e0]
        jmp loc_0042536D
    loc_004252D0:
        mov  edx,DWORD PTR [edi+0x329c]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        call FUN_004491c0
        test  eax,eax
        je loc_004252F8
        mov  eax,DWORD PTR [edi+0x329c]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_00449210
    loc_004252F8:
        mov  DWORD PTR [edi+0x329c],0x0
        mov  eax,DWORD PTR [edi+0x454]
        dec  eax
        cmp  eax,0x7
        ja loc_004253B2
        jmp  DWORD PTR [eax*4+0x425708]
        mov  ebp,DWORD PTR [edi+0x3d4]
        jmp loc_00425373
        mov  ebp,DWORD PTR [edi+0x3d4]
        neg  ebp
        jmp loc_00425373
        mov  ebx,DWORD PTR [edi+0x3d4]
        neg  ebx
        mov  DWORD PTR [esp+0xc],ebx
        jmp loc_004253B2
        mov  ebx,DWORD PTR [edi+0x3d4]
        mov  DWORD PTR [esp+0xc],ebx
        jmp loc_004253B2
        mov  ebp,DWORD PTR [edi+0x3dc]
        neg  ebp
        jmp loc_0042536D
        mov  ebx,DWORD PTR [edi+0x3dc]
        mov  ebp,ebx
        neg  ebp
        jmp loc_0042536F
        mov  ebp,DWORD PTR [edi+0x3dc]
        mov  ebx,ebp
        neg  ebx
        jmp loc_0042536F
        mov  ebp,DWORD PTR [edi+0x3dc]
    loc_0042536D:
        mov  ebx,ebp
    loc_0042536F:
        mov  DWORD PTR [esp+0xc],ebx
    loc_00425373:
        test  ebp,ebp
        mov  DWORD PTR [esp+0x10],ebp
        jge loc_004253B0
        mov  eax,DWORD PTR [edi+0x44c]
        test  eax,eax
        jl loc_004253AE
        mov  ecx,DWORD PTR [edi+0x10]
        lea  eax,[edi+0x14]
        mov  ebx,0x1
        call FUN_0043e710
        mov  ebx,DWORD PTR [esp+0xc]
    loc_00425399:
        test  ebp,ebp
        jle loc_004253D4
        mov  eax,DWORD PTR [edi+0x44c]
        test  eax,eax
        jg loc_004253D2
        mov  ebx,0x3
        jmp loc_004253E5
    loc_004253AE:
        test  ebp,ebp
    loc_004253B0:
        jne loc_00425399
    loc_004253B2:
        mov  eax,DWORD PTR [edi+0x44c]
        test  eax,eax
        jge loc_004253DE
        mov  ecx,DWORD PTR [edi+0x10]
        lea  eax,[edi+0x14]
        mov  ebx,0x2
        call FUN_0043e710
        mov  ebx,DWORD PTR [esp+0xc]
        jmp loc_004253D6
    loc_004253D2:
        test  ebp,ebp
    loc_004253D4:
        jne loc_004253F4
    loc_004253D6:
        mov  eax,DWORD PTR [edi+0x44c]
        test  eax,eax
    loc_004253DE:
        jle loc_004253F4
        mov  ebx,0x4
    loc_004253E5:
        mov  ecx,DWORD PTR [edi+0x10]
        lea  eax,[edi+0x14]
        call FUN_0043e710
        mov  ebx,DWORD PTR [esp+0xc]
    loc_004253F4:
        fild  DWORD PTR [esp+0x10]
        mov  DWORD PTR [edi+0x44c],ebp
        mov  DWORD PTR [edi+0x450],ebx
        fmul  DWORD PTR ds:0x476f78
        call FUN_00463b2c
        fild  DWORD PTR [esp+0xc]
        mov  DWORD PTR [edi+0x3f0],eax
        fmul  DWORD PTR ds:0x476f78
        call FUN_00463b2c
        mov  ecx,DWORD PTR [edi+0x3f0]
        mov  esi,DWORD PTR [edi+0x3d0]
        mov  DWORD PTR [edi+0x3f4],eax
        mov  eax,DWORD PTR [edi+0x3cc]
        mov  edx,DWORD PTR [edi+0x3f4]
        add  eax,ecx
        add  esi,edx
        cmp  eax,0xffffb820
        mov  DWORD PTR [edi+0x3cc],eax
        mov  DWORD PTR [edi+0x3d0],esi
        mov  ecx,esi
        jge loc_00425467
        mov  DWORD PTR [edi+0x3cc],0xffffb820
        jmp loc_00425478
    loc_00425467:
        cmp  eax,0x47e0
        jle loc_00425478
        mov  DWORD PTR [edi+0x3cc],0x47e0
    loc_00425478:
        cmp  ecx,0xc80
        jge loc_0042548C
        mov  DWORD PTR [edi+0x3d0],0xc80
        jmp loc_0042549E
    loc_0042548C:
        cmp  ecx,0xa8c0
        jle loc_0042549E
        mov  DWORD PTR [edi+0x3d0],0xa8c0
    loc_0042549E:
        fild  DWORD PTR [edi+0x3cc]
        mov  edx,DWORD PTR ds:0x491c10
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [edi+0x3c0]
        fild  DWORD PTR [edi+0x3d0]
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [edi+0x3c4]
        mov  eax,DWORD PTR [edi+0x329c]
        push  eax
        call FUN_004491c0
        test  eax,eax
        jne loc_004254E0
        mov  DWORD PTR [edi+0x329c],eax
        jmp loc_00425520
    loc_004254E0:
        fld  DWORD PTR [edi+0x3c0]
        mov  edx,DWORD PTR [edi+0x329c]
        fadd  DWORD PTR ds:0x470b4c
        mov  ecx,DWORD PTR [edi+0x3c8]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        fstp  DWORD PTR [esp+0x1c]
        lea  esi,[esp+0x1c]
        fld  DWORD PTR [edi+0x3c4]
        mov  DWORD PTR [esp+0x24],ecx
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esp+0x20]
        call FUN_004492f0
    loc_00425520:
        mov  eax,DWORD PTR [edi+0x4474]
        test  eax,eax
        jne loc_004255A1
        test  ebx,ebx
        jne loc_00425532
        test  ebp,ebp
        je loc_004255A1
    loc_00425532:
        mov  ecx,DWORD PTR [edi+0x3500]
        mov  eax,0x20
        shl  ecx,0x3
        cmp  ecx,eax
        jge loc_00425584
        lea  ecx,[edi+0x446c]
        lea  ebx,[ebx+0x0]
    loc_00425550:
        mov  edx,DWORD PTR [edi+0x3500]
        shl  edx,0x6
        mov  esi,DWORD PTR [edx+edi*1+0x436c]
        lea  edx,[edx+edi*1+0x436c]
        mov  DWORD PTR [ecx],esi
        mov  edx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  edx,DWORD PTR [edi+0x3500]
        dec  eax
        shl  edx,0x3
        sub  ecx,0x8
        cmp  eax,edx
        jg loc_00425550
        test  eax,eax
        jle loc_004255A1
    loc_00425584:
        lea  ecx,[edi+eax*8+0x4370]
        jmp loc_00425590
        nop
    loc_00425590:
        mov  edx,DWORD PTR [ecx-0xc]
        mov  DWORD PTR [ecx-0x4],edx
        mov  edx,DWORD PTR [ecx-0x8]
        mov  DWORD PTR [ecx],edx
        add  ecx,0xfffffff8
        dec  eax
        jne loc_00425590
    loc_004255A1:
        mov  eax,DWORD PTR [edi+0x3cc]
        mov  DWORD PTR [edi+0x436c],eax
        mov  ecx,DWORD PTR [edi+0x3d0]
        mov  DWORD PTR [edi+0x4370],ecx
        lea  ebx,[edi+0x32e0]
        mov  DWORD PTR [esp+0x10],0x4
    loc_004255C7:
        mov  eax,DWORD PTR [ebx-0x40]
        test  eax,eax
        lea  ecx,[ebx-0x40]
        je loc_004256C9
        mov  eax,DWORD PTR [edi+0x4474]
        test  eax,eax
        lea  esi,[ebx+0xc]
        jne loc_004255E5
        lea  esi,[ebx+0x4]
    loc_004255E5:
        mov  edx,DWORD PTR [edi+0x3cc]
        mov  eax,DWORD PTR [esi]
        mov  ebp,DWORD PTR [esi+0x4]
        add  eax,edx
        mov  edx,DWORD PTR [edi+0x3d0]
        add  edx,ebp
        mov  DWORD PTR [ebx-0xc],eax
        mov  DWORD PTR [ebx-0x8],edx
        mov  eax,DWORD PTR [ebx+0x50]
        test  eax,eax
        je loc_00425609
        call  eax
    loc_00425609:
        mov  eax,DWORD PTR [ebx+0x4c]
        test  eax,eax
        jne loc_00425676
        mov  edx,DWORD PTR [edi+0x4308]
        cmp  edx,0x1e
        jl loc_00425688
        mov  ebp,DWORD PTR [ebx-0xc]
        mov  ecx,DWORD PTR [ebx-0x4]
        mov  esi,DWORD PTR [ebx]
        mov  eax,ebp
        sub  eax,ecx
        mov  ecx,DWORD PTR [ebx-0x8]
        imul  eax,edx
        sub  ecx,esi
        mov  esi,eax
        imul  ecx,edx
        mov  eax,0x51eb851f
        imul  esi
        sar  edx,0x5
        mov  esi,edx
        shr  esi,0x1f
        add  esi,edx
        mov  eax,0x51eb851f
        imul  ecx
        sar  edx,0x5
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        test  esi,esi
        jne loc_0042565E
        test  eax,eax
        je loc_0042566C
    loc_0042565E:
        mov  edx,DWORD PTR [ebx-0x4]
        mov  ecx,DWORD PTR [ebx]
        add  edx,esi
        mov  DWORD PTR [ebx-0x4],edx
        add  ecx,eax
        jmp loc_00425686
    loc_0042566C:
        mov  DWORD PTR [ebx-0x4],ebp
        mov  edx,DWORD PTR [ebx-0x8]
        mov  DWORD PTR [ebx],edx
        jmp loc_00425688
    loc_00425676:
        mov  DWORD PTR [ebx+0x4c],0x0
        mov  eax,DWORD PTR [ebx-0xc]
        mov  DWORD PTR [ebx-0x4],eax
        mov  ecx,DWORD PTR [ebx-0x8]
    loc_00425686:
        mov  DWORD PTR [ebx],ecx
    loc_00425688:
        fild  DWORD PTR [ebx-0x4]
        mov  edx,DWORD PTR [ebx+0x28]
        mov  ebp,DWORD PTR ds:0x491c10
        push  edx
        fmul  DWORD PTR ds:0x470b00
        lea  esi,[esp+0x1c]
        mov  edx,ebp
        mov  DWORD PTR [esp+0x24],0x0
        fstp  DWORD PTR [esp+0x1c]
        fild  DWORD PTR [ebx]
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [esp+0x20]
        call FUN_00449350
        mov  eax,DWORD PTR [ebx+0x2c]
        push  eax
        mov  edx,ebp
        call FUN_00449350
    loc_004256C9:
        mov  eax,DWORD PTR [esp+0x10]
        add  ebx,0x98
        dec  eax
        mov  DWORD PTR [esp+0x10],eax
        jne loc_004255C7
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0x18
        ret
    }
}

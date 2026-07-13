// 00413BC0: FUN_00413bc0
// Original size: 1968 bytes, actual code: 543 instructions
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_0043e710(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_00413bc0(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [edi+0x8]
        test  eax,eax
        mov  ecx,0x2
        je loc_00413BD0
        or   DWORD PTR [eax+0x4],ecx
    loc_00413BD0:
        mov  eax,DWORD PTR [edi+0xc]
        test  eax,eax
        je loc_00413BDA
        or   DWORD PTR [eax+0x4],ecx
    loc_00413BDA:
        mov  eax,DWORD PTR [edi+0x9e58]
        test  eax,eax
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        jne loc_00413C38
        mov  ebp,DWORD PTR [edi+0x9ec8]
        call FUN_00449950
        mov  ebx,eax
        mov  edx,DWORD PTR [ebx+0x35c]
        push  0x0
        or   edx,0x40000000
        push  ebx
        mov  ecx,ebp
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],edx
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0xc]
        mov  edx,esi
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0xc]
        mov  DWORD PTR [edi+0x9e58],eax
    loc_00413C38:
        mov  eax,DWORD PTR [edi+0x9e5c]
        test  eax,eax
        jne loc_00413C83
        mov  ebp,DWORD PTR [edi+0x9ec8]
        call FUN_00449950
        mov  ebx,eax
        mov  edx,DWORD PTR [ebx+0x35c]
        push  0x1
        or   edx,0x40000000
        push  ebx
        mov  ecx,ebp
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],edx
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0xc]
        mov  edx,esi
        call FUN_004489d0
    loc_00413C83:
        test  BYTE PTR [edi+0x36c],0x1
        jne loc_00413D86
        mov  esi,0x14
        lea  ebp,[edi+0x24c8]
        mov  DWORD PTR [esp+0xc],0xa
        jmp loc_00413CB0
        nop
        nop
    loc_00413CB0:
        mov  ecx,DWORD PTR [edi+0x9ec8]
        lea  ebx,[esi-0xa]
        lea  eax,[ebp-0x24b8]
        call FUN_0043e710
        mov  ecx,DWORD PTR [edi+0x9ec8]
        mov  ebx,esi
        mov  eax,ebp
        call FUN_0043e710
        mov  eax,DWORD PTR [esp+0xc]
        inc  esi
        add  ebp,0x3ac
        dec  eax
        mov  DWORD PTR [esp+0xc],eax
        jne loc_00413CB0
        xor  esi,esi
        lea  ebp,[edi+0x4980]
        nop
    loc_00413CF0:
        mov  ecx,DWORD PTR [edi+0x9ec8]
        lea  ebx,[esi+0x1e]
        mov  eax,ebp
        call FUN_0043e710
        inc  esi
        add  ebp,0x3ac
        cmp  esi,0x9
        jl loc_00413CF0
        xor  esi,esi
        lea  ebp,[edi+0x6a8c]
    loc_00413D14:
        mov  ecx,DWORD PTR [edi+0x9ec8]
        lea  ebx,[esi+0x2f]
        mov  eax,ebp
        call FUN_0043e710
        inc  esi
        add  ebp,0x3ac
        cmp  esi,0x4
        jl loc_00413D14
        xor  esi,esi
        lea  ebp,[edi+0x793c]
        jmp loc_00413D40
        lea  ebx,[ebx+0x0]
    loc_00413D40:
        mov  ecx,DWORD PTR [edi+0x9ec8]
        lea  ebx,[esi+0x50]
        mov  eax,ebp
        call FUN_0043e710
        inc  esi
        add  ebp,0x3ac
        cmp  esi,0x2
        jl loc_00413D40
        xor  esi,esi
        lea  ebp,[edi+0x8094]
    loc_00413D64:
        mov  ecx,DWORD PTR [edi+0x9ec8]
        lea  ebx,[esi+0x33]
        mov  eax,ebp
        call FUN_0043e710
        inc  esi
        add  ebp,0x3ac
        cmp  esi,0x7
        jl loc_00413D64
        mov  esi,DWORD PTR ds:0x491c10
    loc_00413D86:
        mov  ecx,DWORD PTR ds:0x474c70
        xor  edx,edx
        test  ecx,ecx
        jle loc_00413DB0
        lea  eax,[edi+0x4cdc]
        mov  edx,ecx
        lea  ebx,[ebx+0x0]
    loc_00413DA0:
        or   DWORD PTR [eax],0x2
        add  eax,0x3ac
        dec  ecx
        jne loc_00413DA0
        cmp  edx,0x9
        jge loc_00413DD1
    loc_00413DB0:
        mov  ecx,edx
        imul  ecx,ecx,0x3ac
        lea  eax,[ecx+edi*1+0x4cdc]
        mov  ecx,0x9
        sub  ecx,edx
    loc_00413DC6:
        and  DWORD PTR [eax],0xfffffffd
        add  eax,0x3ac
        dec  ecx
        jne loc_00413DC6
    loc_00413DD1:
        movsx eax,WORD PTR ds:0x474c48
        cdq
        mov  ecx,0x14
        idiv  ecx
        imul  edx,edx,0x64
        mov  ecx,eax
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x3
        mov  ebx,edx
        shr  ebx,0x1f
        add  ebx,edx
        lea  edx,[ecx+0x8]
        mov  ecx,DWORD PTR [edi+0x9ec8]
        lea  eax,[edi+0x6a8c]
        call FUN_0043e5a0
        mov  eax,ebx
        cdq
        mov  ecx,0xa
        idiv  ecx
        mov  ecx,DWORD PTR [edi+0x9ec8]
        mov  ebx,edx
        lea  edx,[eax+0x8]
        lea  eax,[edi+0x71e4]
        call FUN_0043e5a0
        mov  ecx,DWORD PTR [edi+0x9ec8]
        lea  edx,[ebx+0x8]
        lea  eax,[edi+0x7590]
        call FUN_0043e5a0
        cmp  DWORD PTR ds:0x491fb8,0x8
        je loc_00413F87
        test  BYTE PTR ds:0x474ca0,0x20
        jne loc_00413F94
        mov  ebp,DWORD PTR [edi+0x9e80]
        call FUN_00449950
        mov  ebx,eax
        mov  ecx,DWORD PTR [ebx+0x35c]
        or   ecx,0x40000000
        xor  esi,esi
        push  esi
        mov  DWORD PTR [ebx+0x35c],ecx
        push  ebx
        mov  ecx,ebp
        mov  DWORD PTR [ebx+0x20],0xf
        call FUN_00449870
        lea  eax,[ebx+0x4]
        mov  DWORD PTR [eax+0x4],esi
        mov  DWORD PTR [eax+0x8],esi
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [eax],ebx
        mov  ecx,DWORD PTR [esi+0x72dad4]
        test  ecx,ecx
        jne loc_00413EAC
        mov  DWORD PTR [esi+0x72dad4],eax
        jmp loc_00413EC8
    loc_00413EAC:
        mov  ecx,DWORD PTR [esi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_00413EC2
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_00413EC2:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_00413EC8:
        mov  DWORD PTR [esi+0x72dad8],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        inc  ecx
        mov  eax,ecx
        test  eax,eax
        mov  DWORD PTR [esi+0x732454],ecx
        jne loc_00413EE8
        inc  eax
        mov  DWORD PTR [esi+0x732454],eax
    loc_00413EE8:
        mov  eax,DWORD PTR [esi+0x732454]
        mov  DWORD PTR [ebx],eax
        mov  ebp,DWORD PTR [edi+0x9e80]
        call FUN_00449950
        mov  ebx,eax
        mov  ecx,DWORD PTR [ebx+0x35c]
        or   ecx,0x40000000
        push  0x1
        mov  DWORD PTR [ebx+0x35c],ecx
        push  ebx
        mov  ecx,ebp
        mov  DWORD PTR [ebx+0x20],0xf
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[ebx+0x4]
        xor  ecx,ecx
        mov  DWORD PTR [eax],ebx
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x8],ecx
        cmp  DWORD PTR [esi+0x72dad4],ecx
        jne loc_00413F43
        mov  DWORD PTR [esi+0x72dad4],eax
        jmp loc_00413F5F
    loc_00413F43:
        mov  ecx,DWORD PTR [esi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_00413F59
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_00413F59:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_00413F5F:
        mov  DWORD PTR [esi+0x72dad8],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        inc  ecx
        mov  eax,ecx
        test  eax,eax
        mov  DWORD PTR [esi+0x732454],ecx
        jne loc_00413F7F
        inc  eax
        mov  DWORD PTR [esi+0x732454],eax
    loc_00413F7F:
        mov  eax,DWORD PTR [esi+0x732454]
        mov  DWORD PTR [ebx],eax
    loc_00413F87:
        test  BYTE PTR ds:0x474ca0,0x20
        je loc_0041402B
    loc_00413F94:
        mov  ebx,DWORD PTR [edi+0x9ec8]
        call FUN_00449950
        mov  esi,eax
        mov  ecx,DWORD PTR [esi+0x35c]
        or   ecx,0x40000000
        push  0x71
        mov  DWORD PTR [esi+0x35c],ecx
        push  esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x20],0xf
        call FUN_00449870
        mov  ecx,DWORD PTR ds:0x491c10
        lea  eax,[esi+0x4]
        xor  ebp,ebp
        mov  DWORD PTR [eax],esi
        mov  DWORD PTR [eax+0x4],ebp
        mov  DWORD PTR [eax+0x8],ebp
        cmp  DWORD PTR [ecx+0x72dad4],ebp
        jne loc_00413FE7
        mov  DWORD PTR [ecx+0x72dad4],eax
        jmp loc_00414003
    loc_00413FE7:
        mov  edx,DWORD PTR [ecx+0x72dad8]
        mov  ebx,DWORD PTR [edx+0x4]
        cmp  ebx,ebp
        je loc_00413FFD
        mov  DWORD PTR [eax+0x4],ebx
        mov  ebx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ebx+0x8],eax
    loc_00413FFD:
        mov  DWORD PTR [edx+0x4],eax
        mov  DWORD PTR [eax+0x8],edx
    loc_00414003:
        mov  DWORD PTR [ecx+0x72dad8],eax
        mov  edx,DWORD PTR [ecx+0x732454]
        inc  edx
        mov  eax,edx
        cmp  eax,ebp
        mov  DWORD PTR [ecx+0x732454],edx
        jne loc_00414023
        inc  eax
        mov  DWORD PTR [ecx+0x732454],eax
    loc_00414023:
        mov  ecx,DWORD PTR [ecx+0x732454]
        mov  DWORD PTR [esi],ecx
    loc_0041402B:
        mov  edx,DWORD PTR ds:0x4776e0
        mov  ecx,DWORD PTR [edx+0x8994]
        lea  eax,[edi+0x9a48]
        xor  ebx,ebx
        call FUN_0043e710
        cmp  DWORD PTR ds:0x474c7c,0x1
        jne loc_0041410D
        mov  eax,ds:0x477810
        mov  ecx,DWORD PTR [eax+0x5c]
        test  ecx,ecx
        jne loc_0041410D
        mov  eax,ds:0x474c90
        test  eax,eax
        jne loc_0041410D
        mov  esi,DWORD PTR ds:0x491c10
        mov  ebp,DWORD PTR [edi+0x9ec8]
        call FUN_00449950
        mov  ebx,eax
        mov  ecx,DWORD PTR [ebx+0x35c]
        or   ecx,0x40000000
        push  0x4f
        mov  DWORD PTR [ebx+0x35c],ecx
        push  ebx
        mov  ecx,ebp
        mov  DWORD PTR [ebx+0x20],0xf
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[ebx+0x4]
        xor  ecx,ecx
        mov  DWORD PTR [eax],ebx
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x8],ecx
        cmp  DWORD PTR [esi+0x72dad4],ecx
        jne loc_004140C7
        mov  DWORD PTR [esi+0x72dad4],eax
        jmp loc_004140E3
    loc_004140C7:
        mov  ecx,DWORD PTR [esi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_004140DD
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_004140DD:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_004140E3:
        mov  DWORD PTR [esi+0x72dad8],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        inc  ecx
        mov  eax,ecx
        test  eax,eax
        mov  DWORD PTR [esi+0x732454],ecx
        jne loc_00414103
        inc  eax
        mov  DWORD PTR [esi+0x732454],eax
    loc_00414103:
        mov  eax,DWORD PTR [esi+0x732454]
        mov  DWORD PTR [ebx],eax
        jmp loc_00414113
    loc_0041410D:
        mov  esi,DWORD PTR ds:0x491c10
    loc_00414113:
        mov  eax,ds:0x491fc4
        test  eax,eax
        je loc_00414240
        mov  ecx,DWORD PTR [edi+0x9ec8]
        mov  ebp,DWORD PTR ds:0x474c74
        mov  DWORD PTR [esp+0xc],ecx
        call FUN_00449950
        mov  ebx,eax
        mov  ecx,DWORD PTR [ebx+0x35c]
        or   ecx,0x40000000
        add  ebp,0x66
        push  ebp
        mov  DWORD PTR [ebx+0x35c],ecx
        mov  ecx,DWORD PTR [esp+0x10]
        push  ebx
        mov  DWORD PTR [ebx+0x20],0xf
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[ebx+0x4]
        xor  ecx,ecx
        mov  DWORD PTR [eax],ebx
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x8],ecx
        cmp  DWORD PTR [esi+0x72dad4],ecx
        jne loc_00414181
        mov  DWORD PTR [esi+0x72dad4],eax
        jmp loc_0041419D
    loc_00414181:
        mov  ecx,DWORD PTR [esi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_00414197
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_00414197:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_0041419D:
        mov  DWORD PTR [esi+0x72dad8],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        inc  ecx
        mov  eax,ecx
        test  eax,eax
        mov  DWORD PTR [esi+0x732454],ecx
        jne loc_004141BD
        inc  eax
        mov  DWORD PTR [esi+0x732454],eax
    loc_004141BD:
        mov  eax,DWORD PTR [esi+0x732454]
        mov  DWORD PTR [ebx],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        test  ecx,ecx
        mov  DWORD PTR [edi+0x9e50],ecx
        je loc_00414240
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_004141ED
        nop
    loc_004141E0:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00414206
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004141E0
    loc_004141ED:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_00414240
    loc_004141F7:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00414206
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004141F7
        jmp loc_00414240
    loc_00414206:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00414240
        mov  edx,DWORD PTR [eax+0x18]
        test  edx,edx
        mov  ecx,0x3
        mov  WORD PTR [eax+0x304],cx
        jne loc_00414240
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00414240
        jmp loc_00414230
        nop
        nop
    loc_00414230:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00414230
    loc_00414240:
        mov  ebx,DWORD PTR ds:0x474c74
        mov  ebp,DWORD PTR [edi+0x9ec8]
        call FUN_00449950
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x35c]
        add  ebx,0x6b
        push  ebx
        or   edx,0x40000000
        push  esi
        mov  ecx,ebp
        mov  DWORD PTR [esi+0x20],0xf
        mov  DWORD PTR [esi+0x35c],edx
        call FUN_00449870
        mov  ecx,DWORD PTR ds:0x491c10
        lea  eax,[esi+0x4]
        xor  edx,edx
        mov  DWORD PTR [eax],esi
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [eax+0x8],edx
        cmp  DWORD PTR [ecx+0x72dad4],edx
        jne loc_0041429B
        mov  DWORD PTR [ecx+0x72dad4],eax
        jmp loc_004142B7
    loc_0041429B:
        mov  edx,DWORD PTR [ecx+0x72dad8]
        mov  ebx,DWORD PTR [edx+0x4]
        test  ebx,ebx
        je loc_004142B1
        mov  DWORD PTR [eax+0x4],ebx
        mov  ebx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ebx+0x8],eax
    loc_004142B1:
        mov  DWORD PTR [edx+0x4],eax
        mov  DWORD PTR [eax+0x8],edx
    loc_004142B7:
        mov  DWORD PTR [ecx+0x72dad8],eax
        mov  edx,DWORD PTR [ecx+0x732454]
        inc  edx
        xor  ebx,ebx
        mov  eax,edx
        cmp  eax,ebx
        mov  DWORD PTR [ecx+0x732454],edx
        jne loc_004142D9
        inc  eax
        mov  DWORD PTR [ecx+0x732454],eax
    loc_004142D9:
        mov  eax,DWORD PTR [ecx+0x732454]
        mov  DWORD PTR [esi],eax
        mov  edx,DWORD PTR [edi+0x9e50]
        cmp  edx,ebx
        mov  eax,DWORD PTR [ecx+0x732454]
        mov  DWORD PTR [edi+0x9e54],eax
        je loc_00414362
        mov  eax,DWORD PTR [ecx+0x72dad4]
        cmp  eax,ebx
        je loc_0041430E
    loc_00414301:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],edx
        je loc_00414330
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00414301
    loc_0041430E:
        mov  ecx,DWORD PTR [ecx+0x72dadc]
        cmp  ecx,ebx
        je loc_00414362
    loc_00414318:
        mov  eax,DWORD PTR [ecx]
        cmp  DWORD PTR [eax],edx
        je loc_00414334
        mov  ecx,DWORD PTR [ecx+0x4]
        cmp  ecx,ebx
        jne loc_00414318
        pop  esi
        pop  ebp
        mov  DWORD PTR [edi+0x9e90],ebx
        pop  ebx
        pop  ecx
        ret
    loc_00414330:
        mov  eax,DWORD PTR [eax]
        jmp loc_00414336
    loc_00414334:
        mov  eax,DWORD PTR [ecx]
    loc_00414336:
        cmp  eax,ebx
        je loc_00414362
        cmp  DWORD PTR [eax+0x18],ebx
        mov  ecx,0x3
        mov  WORD PTR [eax+0x304],cx
        jne loc_00414362
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,ebx
        je loc_00414362
    loc_00414352:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00414352
    loc_00414362:
        pop  esi
        pop  ebp
        mov  DWORD PTR [edi+0x9e90],ebx
        pop  ebx
        pop  ecx
        ret
    }
}

// 00431EE0: FUN_00431ee0
// Original size: 1968 bytes, actual code: 540 instructions
extern "C" void FUN_004088c0(void);
extern "C" void FUN_00409e50(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0042c8c0(void);
extern "C" void FUN_00432690(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00449250(void);
extern "C" void FUN_0044b010(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_00431ee0(void) {
    __asm {
        push  ecx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [ebp+0x20]
        cmp  eax,0x3
        push  esi
        mov  esi,0x1
        ja loc_00432672
        push  ebx
        push  edi
        mov  ebx,0x6
        jmp  DWORD PTR [eax*4+0x432680]
        mov  eax,ebx
        xor  edi,edi
        cmp  eax,edi
        mov  DWORD PTR [ebp+0x2c],ebx
        je loc_00431F20
        jg loc_00431F19
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00431F23
    loc_00431F19:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00431F23
    loc_00431F20:
        mov  DWORD PTR [ebp+0x24],edi
    loc_00431F23:
        mov  DWORD PTR [ebp+0x104],0x5
        mov  eax,DWORD PTR [ebp+0x104]
        cmp  eax,edi
        je loc_00431F4E
        cmp  eax,esi
        jg loc_00431F44
        dec  eax
        mov  DWORD PTR [ebp+0xfc],eax
        jmp loc_00431F54
    loc_00431F44:
        mov  eax,esi
        mov  DWORD PTR [ebp+0xfc],eax
        jmp loc_00431F54
    loc_00431F4E:
        mov  DWORD PTR [ebp+0xfc],esi
    loc_00431F54:
        mov  edx,DWORD PTR [ebp+0xfc]
        mov  DWORD PTR [ebp+0x1cc],esi
        call FUN_004088c0
        mov  ecx,eax
        add  ecx,0x9
        mov  eax,0x66666667
        imul  ecx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  ecx,[edx+eax*1+0x1]
        mov  eax,ecx
        cmp  eax,edi
        mov  DWORD PTR [ebp+0x1dc],ecx
        je loc_00431F9E
        jg loc_00431F94
        dec  eax
        mov  DWORD PTR [ebp+0x1d4],eax
        jmp loc_00431FA4
    loc_00431F94:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x1d4],eax
        jmp loc_00431FA4
    loc_00431F9E:
        mov  DWORD PTR [ebp+0x1d4],edi
    loc_00431FA4:
        mov  DWORD PTR [ebp+0x2a4],esi
        mov  edx,DWORD PTR [ebp+0x43c]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        call FUN_004491c0
        test  eax,eax
        jne loc_00431FEC
        push  ebp
        mov  edi,0x5e
        call FUN_0042c670
        mov  eax,ds:0x4776e0
        mov  eax,DWORD PTR [eax+0x8994]
        push  0xf
        push  0x8
        push  eax
        lea  edi,[esp+0x24]
        call FUN_00448d00
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x5d0],ecx
    loc_00431FEC:
        push  ebp
        mov  edi,0x66
        call FUN_0042c670
        mov  ecx,esi
        mov  eax,ebp
        call FUN_0042c620
        mov  ecx,DWORD PTR [ebp+0x24]
        mov  eax,0x55555556
        imul  ecx
        mov  eax,edx
        shr  eax,0x1f
        lea  edi,[edx+eax*1+0x98]
        push  ebp
        call FUN_0042c670
        mov  edi,DWORD PTR [ebp+0x24]
        add  edi,0x9a
        push  ebp
        call FUN_0042c670
        mov  edi,DWORD PTR [ebp+0xfc]
        add  edi,0xa0
        push  ebp
        call FUN_0042c670
        push  ebp
        mov  edi,0xa8
        call FUN_0042c670
        push  ebp
        mov  edi,0xa9
        call FUN_0042c670
        push  ebp
        mov  edi,0xaa
        call FUN_0042c670
        push  ebp
        mov  edi,0xab
        call FUN_0042c670
        push  ebp
        mov  edi,0xa5
        call FUN_0042c670
        push  ebp
        mov  edi,0xa6
        call FUN_0042c670
        push  ebp
        mov  edi,0xa7
        call FUN_0042c670
        push  ebp
        mov  edi,0xac
        call FUN_0042c670
        cmp  DWORD PTR [ebp+0x2b4],ebx
        jle loc_00432670
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
        pop  edi
        pop  ebx
        pop  esi
        mov  eax,0x1
        pop  ebp
        pop  ecx
        ret  0x4
        mov  ecx,DWORD PTR [ebp+0x24]
        mov  DWORD PTR [ebp+0x28],ecx
        mov  edx,DWORD PTR [ebp+0xfc]
        lea  ebx,[ebp+0xfc]
        mov  DWORD PTR [ebx+0x4],edx
        mov  eax,DWORD PTR [ebp+0x1d4]
        mov  DWORD PTR [ebp+0x1d8],eax
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_004320EF
        test  BYTE PTR ds:0x474e34,al
        je loc_0043210F
    loc_004320EF:
        push  0xffffffff
        mov  eax,ebx
        call FUN_0044bea0
        mov  ecx,DWORD PTR [ebp+0x56c]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        mov  edi,0x2
        call FUN_00449250
    loc_0043210F:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x20
        test  al,cl
        jne loc_00432123
        test  BYTE PTR ds:0x474e34,al
        je loc_00432142
    loc_00432123:
        push  esi
        mov  eax,ebx
        call FUN_0044bea0
        mov  edx,DWORD PTR [ebp+0x570]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        mov  edi,0x2
        call FUN_00449250
    loc_00432142:
        mov  eax,DWORD PTR [ebx+0x4]
        cmp  eax,DWORD PTR [ebx]
        je loc_004321E9
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  esi,DWORD PTR [ebp+0x100]
        add  esi,0xa0
        mov  edi,ebp
        call FUN_0042c6d0
        mov  edi,DWORD PTR [ebx]
        add  edi,0xa0
        push  ebp
        call FUN_0042c670
        mov  eax,DWORD PTR [ebp+0x1d4]
        test  eax,eax
        jle loc_004321BF
        mov  eax,DWORD PTR [ebp+0x1dc]
        test  eax,eax
        je loc_004321AE
        cmp  eax,0x1
        jg loc_004321A1
        dec  eax
        mov  DWORD PTR [ebp+0x1d4],eax
        jmp loc_004321B8
    loc_004321A1:
        mov  eax,0x1
        mov  DWORD PTR [ebp+0x1d4],eax
        jmp loc_004321B8
    loc_004321AE:
        mov  DWORD PTR [ebp+0x1d4],0x1
    loc_004321B8:
        mov  ecx,ebp
        call FUN_00432690
    loc_004321BF:
        mov  edx,DWORD PTR [ebx]
        call FUN_004088c0
        mov  ecx,eax
        add  ecx,0x9
        mov  eax,0x66666667
        imul  ecx
        sar  edx,0x2
        mov  ecx,edx
        shr  ecx,0x1f
        lea  edx,[edx+ecx*1+0x1]
        mov  DWORD PTR [ebp+0x1dc],edx
        mov  esi,0x1
    loc_004321E9:
        test  BYTE PTR ds:0x474e36,0x40
        jne loc_004321FB
        test  BYTE PTR ds:0x474e34,0x40
        je loc_0043221C
    loc_004321FB:
        push  0xffffffff
        lea  eax,[ebp+0x24]
        call FUN_0044bea0
        mov  eax,DWORD PTR [ebp+0x564]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        mov  edi,0x2
        call FUN_00449250
    loc_0043221C:
        mov  al,ds:0x474e36
        test  al,al
        js loc_0043222E
        mov  al,ds:0x474e34
        test  al,al
        jns loc_0043224E
    loc_0043222E:
        push  esi
        lea  eax,[ebp+0x24]
        call FUN_0044bea0
        mov  ecx,DWORD PTR [ebp+0x568]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        mov  edi,0x2
        call FUN_00449250
    loc_0043224E:
        mov  edx,DWORD PTR [ebp+0x28]
        cmp  edx,DWORD PTR [ebp+0x24]
        je loc_004322EA
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,DWORD PTR [ebp+0x28]
        mov  eax,0x55555556
        imul  ecx
        mov  ecx,edx
        shr  ecx,0x1f
        add  ecx,edx
        mov  edx,DWORD PTR [ebp+0x24]
        mov  eax,0x55555556
        imul  edx
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cmp  eax,ecx
        je loc_004322BA
        lea  esi,[ecx+0x98]
        mov  edi,ebp
        call FUN_0042c6d0
        mov  ecx,DWORD PTR [ebp+0x24]
        mov  eax,0x55555556
        imul  ecx
        mov  ecx,edx
        shr  ecx,0x1f
        lea  edi,[edx+ecx*1+0x98]
        push  ebp
        call FUN_0042c670
    loc_004322BA:
        mov  esi,DWORD PTR [ebp+0x28]
        add  esi,0x9a
        mov  edi,ebp
        call FUN_0042c6d0
        mov  edi,DWORD PTR [ebp+0x24]
        add  edi,0x9a
        push  ebp
        call FUN_0042c670
        mov  eax,DWORD PTR [ebp+0x1d4]
        test  eax,eax
        jle loc_004322EA
        mov  ecx,ebp
        call FUN_00432690
    loc_004322EA:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_0043237F
        mov  eax,DWORD PTR [ebp+0x1d4]
        test  eax,eax
        jne loc_00432339
        xor  esi,esi
        lea  ebx,[ebp+0x5d4]
        nop
    loc_00432310:
        mov  edx,DWORD PTR ds:0x4776e0
        mov  eax,DWORD PTR [edx+0x899c]
        push  0xf
        lea  ecx,[esi+0x17]
        push  ecx
        push  eax
        lea  edi,[esp+0x1c]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebx],edx
        inc  esi
        add  ebx,0x4
        cmp  esi,0xa
        jl loc_00432310
    loc_00432339:
        lea  esi,[ebp+0x1d4]
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
        cmp  DWORD PTR [esi],0x0
        jne loc_00432367
        lea  esi,[ebp+0x5d4]
        mov  edi,0xa
    loc_00432358:
        mov  eax,esi
        call FUN_00409e50
        add  esi,0x4
        dec  edi
        jne loc_00432358
        jmp loc_0043236E
    loc_00432367:
        mov  ecx,ebp
        call FUN_00432690
    loc_0043236E:
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_0043237F:
        cmp  DWORD PTR [ebp+0xfc],0x4
        jne loc_004324D4
        cmp  DWORD PTR [ebp+0x24],0x2
        jne loc_004324D4
        mov  eax,ds:0x474e36
        xor  ebx,ebx
        test  eax,0x160b
        je loc_004323B0
        mov  DWORD PTR ds:0x4979a4,ebx
        mov  DWORD PTR ds:0x4979a0,ebx
    loc_004323B0:
        mov  ecx,0x40
        mov  esi,0x497e90
        mov  edi,0x497d90
        mov  edx,0x497e90
        rep movsd
        call FUN_0044b010
        test  eax,eax
        je loc_004324B6
        xor  eax,eax
        jmp loc_004323E0
        nop
        mov  edi,edi
    loc_004323E0:
        mov  cl,BYTE PTR [eax+0x497e90]
        mov  dl,BYTE PTR [eax+0x497d90]
        xor  dl,cl
        and  dl,cl
        mov  cl,BYTE PTR [eax+0x497e91]
        mov  BYTE PTR [eax+0x4979a8],dl
        mov  dl,BYTE PTR [eax+0x497d91]
        xor  dl,cl
        and  dl,cl
        mov  cl,BYTE PTR [eax+0x497e92]
        mov  BYTE PTR [eax+0x4979a9],dl
        mov  dl,BYTE PTR [eax+0x497d92]
        xor  dl,cl
        and  dl,cl
        mov  cl,BYTE PTR [eax+0x497e93]
        mov  BYTE PTR [eax+0x4979aa],dl
        mov  dl,BYTE PTR [eax+0x497d93]
        xor  dl,cl
        and  dl,cl
        mov  BYTE PTR [eax+0x4979ab],dl
        add  eax,0x4
        cmp  eax,0x100
        jl loc_004323E0
        mov  eax,ds:0x4979a4
        cmp  eax,0x16
        jb loc_00432468
        mov  eax,ds:0x47783c
        call FUN_0042c8c0
        push  ebx
        mov  edi,0x2c
        mov  ecx,0x492590
        call FUN_0043dc90
        jmp loc_004324B0
    loc_00432468:
        mov  ecx,DWORD PTR [eax*4+0x46ef10]
        mov  dl,BYTE PTR [ecx+0x4979a8]
        test  dl,dl
        jns loc_00432487
        inc  eax
        mov  ds:0x4979a4,eax
        mov  DWORD PTR ds:0x4979a0,ebx
        jmp loc_004324B6
    loc_00432487:
        xor  cl,cl
        xor  eax,eax
        jmp loc_00432490
        nop
    loc_00432490:
        mov  dl,BYTE PTR [eax+0x4979a8]
        or   dl,BYTE PTR [eax+0x4979aa]
        add  eax,0x3
        or   dl,BYTE PTR [eax+0x4979a6]
        or   cl,dl
        cmp  eax,0x39
        jl loc_00432490
        test  cl,cl
        jns loc_004324B6
    loc_004324B0:
        mov  DWORD PTR ds:0x4979a4,ebx
    loc_004324B6:
        mov  eax,ds:0x4979a0
        inc  eax
        cmp  eax,0x12c
        mov  ds:0x4979a0,eax
        jle loc_004324D4
        mov  DWORD PTR ds:0x4979a4,ebx
        mov  DWORD PTR ds:0x4979a0,ebx
    loc_004324D4:
        test  BYTE PTR ds:0x474e36,0xa
        je loc_00432670
        mov  ecx,0x3
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  esi,DWORD PTR [ebp+0xfc]
        add  esi,0xa0
        mov  edi,ebp
        call FUN_0042c6d0
        mov  esi,DWORD PTR [ebp+0x24]
        add  esi,0x9a
        call FUN_0042c6d0
        mov  ecx,DWORD PTR [ebp+0x24]
        mov  eax,0x55555556
        imul  ecx
        mov  eax,edx
        shr  eax,0x1f
        lea  esi,[edx+eax*1+0x98]
        call FUN_0042c6d0
        mov  esi,0xa8
        call FUN_0042c6d0
        mov  esi,0xa9
        call FUN_0042c6d0
        mov  esi,0xaa
        call FUN_0042c6d0
        mov  esi,0xab
        call FUN_0042c6d0
        mov  esi,0xa5
        call FUN_0042c6d0
        mov  esi,0xa6
        call FUN_0042c6d0
        mov  esi,0xa7
        call FUN_0042c6d0
        mov  esi,0xac
        call FUN_0042c6d0
        mov  esi,DWORD PTR ds:0x491c10
        add  ebp,0x5d4
        mov  edx,0xa
        mov  edi,0x1
    loc_004325A0:
        mov  ecx,DWORD PTR [ebp+0x0]
        test  ecx,ecx
        je loc_00432602
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_004325BE
    loc_004325B1:
        mov  ebx,DWORD PTR [eax]
        cmp  DWORD PTR [ebx],ecx
        je loc_004325D7
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004325B1
    loc_004325BE:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_00432602
    loc_004325C8:
        mov  ebx,DWORD PTR [eax]
        cmp  DWORD PTR [ebx],ecx
        je loc_004325D7
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004325C8
        jmp loc_00432602
    loc_004325D7:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_00432602
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        mov  WORD PTR [eax+0x304],di
        jne loc_00432602
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00432602
    loc_004325F2:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],di
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004325F2
    loc_00432602:
        add  ebp,0x4
        dec  edx
        jne loc_004325A0
        pop  edi
        pop  ebx
        pop  esi
        mov  eax,0x1
        pop  ebp
        pop  ecx
        ret  0x4
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jl loc_00432670
        mov  esi,0x66
        mov  edi,ebp
        call FUN_0042c6d0
        mov  esi,0x8
        mov  ecx,0x5a
        mov  eax,ebp
        call FUN_0042c770
        mov  ecx,0x5b
        mov  eax,ebp
        call FUN_0042c770
        mov  esi,0x5e
        call FUN_0042c6d0
        lea  eax,[ebp+0x5d0]
        call FUN_00409e50
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c5c0
        lea  eax,[ebp+0x24]
        call FUN_0044be70
    loc_00432670:
        pop  edi
        pop  ebx
    loc_00432672:
        pop  esi
        mov  eax,0x1
        pop  ebp
        pop  ecx
        ret  0x4
        nop
        push  es
        pop  ds
        inc  ebx
        add  BYTE PTR [ebp-0x45ffbce0],dl
        and  BYTE PTR [ebx+0x0],al
        _emit 0x15
        es inc ebx
    }
}

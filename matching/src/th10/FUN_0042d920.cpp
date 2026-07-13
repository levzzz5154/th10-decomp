// 0042D920: FUN_0042d920
// Original size: 3200 bytes, actual code: 950 instructions
extern "C" void FUN_0040ace0(void);
extern "C" void FUN_00427c70(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c730(void);
extern "C" void FUN_0042c750(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0042e5a0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00449250(void);
extern "C" void FUN_00449670(void);
extern "C" void FUN_0044be20(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_0042d920(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [ebp+0x20]
        cmp  eax,0x4
        ja loc_0042E577
        push  ebx
        push  esi
        push  edi
        mov  esi,0x6
        xor  ebx,ebx
        jmp  DWORD PTR [eax*4+0x42e580]
        mov  eax,esi
        cmp  eax,ebx
        mov  DWORD PTR [ebp+0x2c],esi
        je loc_0042D95A
        jg loc_0042D953
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_0042D95D
    loc_0042D953:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_0042D95D
    loc_0042D95A:
        mov  DWORD PTR [ebp+0x24],ebx
    loc_0042D95D:
        push  ebp
        mov  edi,0x1
        call FUN_0042c670
        mov  edi,ebp
        call FUN_0042e5a0
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c620
        cmp  DWORD PTR [ebp+0x2b4],esi
        jle loc_0042E574
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
        mov  eax,DWORD PTR [ebp+0x2c8]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        mov  edi,0x3
        call FUN_00449250
        mov  al,ds:0x491d6a
        cmp  al,bl
        mov  esi,DWORD PTR ds:0x491c10
        jne loc_0042DA66
        mov  ecx,DWORD PTR [ebp+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042D9D5
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042D9D5:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042D9F3
        mov  ecx,0x1f
    loc_0042D9E1:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042DA4D
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042D9E1
    loc_0042D9F3:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042D9F7:
        push  0x2e
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DA1A
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DA1A:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DA42
        mov  ecx,0x20
        jmp loc_0042DA30
        nop
        nop
    loc_0042DA30:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042DA57
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DA30
    loc_0042DA42:
        mov  DWORD PTR [esp+0x14],ebx
        push  0x2f
        jmp loc_0042DB8D
    loc_0042DA4D:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042D9F7
    loc_0042DA57:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        push  0x2f
        jmp loc_0042DB8D
    loc_0042DA66:
        cmp  al,0x1
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        jne loc_0042DB13
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DA86
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DA86:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DAA4
        mov  ecx,0x1f
    loc_0042DA92:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042DAFD
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DA92
    loc_0042DAA4:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042DAA8:
        push  0x30
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DACB
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DACB:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DAF2
        mov  ecx,0x20
        jmp loc_0042DAE0
        nop
    loc_0042DAE0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042DB07
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DAE0
    loc_0042DAF2:
        mov  DWORD PTR [esp+0x14],ebx
        push  0x31
        jmp loc_0042DB8D
    loc_0042DAFD:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042DAA8
    loc_0042DB07:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        push  0x31
        jmp loc_0042DB8D
    loc_0042DB13:
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DB22
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DB22:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DB42
        mov  ecx,0x1f
        mov  edi,edi
    loc_0042DB30:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042DBB8
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DB30
    loc_0042DB42:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042DB46:
        push  0x2c
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DB69
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DB69:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DB87
        mov  ecx,0x20
    loc_0042DB75:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042DBC2
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DB75
    loc_0042DB87:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042DB8B:
        push  0x2d
    loc_0042DB8D:
        lea  eax,[esp+0x18]
        call FUN_00449670
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x11
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c770
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_0042DBB8:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042DB46
    loc_0042DBC2:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042DB8B
        mov  edx,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x24]
        mov  DWORD PTR [esi+0x4],edx
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_0042DBE9
        test  BYTE PTR ds:0x474e34,al
        je loc_0042DBF2
    loc_0042DBE9:
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
    loc_0042DBF2:
        test  BYTE PTR ds:0x474e36,0x20
        jne loc_0042DC04
        test  BYTE PTR ds:0x474e34,0x20
        je loc_0042DC0D
    loc_0042DC04:
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
    loc_0042DC0D:
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR [esi]
        xor  ebx,ebx
        cmp  eax,ecx
        je loc_0042DC55
        push  ebx
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,DWORD PTR [ebp+0x2c8]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        mov  edi,0x3
        call FUN_00449250
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x7
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c770
    loc_0042DC55:
        test  BYTE PTR ds:0x474e36,0xa
        mov  eax,DWORD PTR [ebp+0x24]
        je loc_0042DCCB
        cmp  eax,0x5
        je loc_0042E27B
        push  ebx
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,DWORD PTR [ebp+0x2c]
        cmp  eax,ebx
        je loc_0042DC96
        cmp  eax,0x5
        jg loc_0042DC8C
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_0042DC9D
    loc_0042DC8C:
        mov  eax,0x5
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_0042DC9D
    loc_0042DC96:
        mov  DWORD PTR [ebp+0x24],0x5
    loc_0042DC9D:
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c750
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x7
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c770
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_0042DCCB:
        cmp  eax,0x2
        jne loc_0042DCF1
        push  0x3c
        lea  ecx,[ebp+0x2b0]
        call FUN_00427c70
        test  eax,eax
        je loc_0042DCF1
        push  ebx
        mov  edi,0x4
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_0042DCF1:
        mov  eax,0x40
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,0x1f
        je loc_0042DEF6
        mov  eax,DWORD PTR [ebp+0x24]
        sub  eax,ebx
        je loc_0042DD8B
        dec  eax
        je loc_0042DD58
        dec  eax
        jne loc_0042DEF6
        cmp  BYTE PTR ds:0x491d69,0x5
        jge loc_0042DD40
        mov  edi,ebp
        mov  BYTE PTR ds:0x491d69,bl
        call FUN_0042e5a0
        jmp loc_0042DEF6
    loc_0042DD40:
        mov  al,ds:0x491d69
        add  al,0xfb
        mov  edi,ebp
        mov  ds:0x491d69,al
        call FUN_0042e5a0
        jmp loc_0042DEF6
    loc_0042DD58:
        cmp  BYTE PTR ds:0x491d68,0x5
        jge loc_0042DD73
        mov  edi,ebp
        mov  BYTE PTR ds:0x491d68,bl
        call FUN_0042e5a0
        jmp loc_0042DEF6
    loc_0042DD73:
        mov  al,ds:0x491d68
        add  al,0xfb
        mov  edi,ebp
        mov  ds:0x491d68,al
        call FUN_0042e5a0
        jmp loc_0042DEF6
    loc_0042DD8B:
        mov  al,ds:0x491d6a
        cmp  al,bl
        jbe loc_0042DE42
        dec  al
        cmp  al,bl
        mov  ds:0x491d6a,al
        jne loc_0042DF66
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DDBF
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DDBF:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DDE6
        jmp loc_0042DDD0
        nop
        nop
    loc_0042DDD0:
        mov  ecx,DWORD PTR [eax]
        cmp  WORD PTR [ecx+0x38a],di
        je loc_0042DF4A
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DDD0
    loc_0042DDE6:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042DDEA:
        push  0x2e
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  ecx,DWORD PTR [ebp+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DE0D
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DE0D:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DE37
        jmp loc_0042DE20
        nop
        nop
    loc_0042DE20:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],0x20
        je loc_0042DF57
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DE20
    loc_0042DE37:
        mov  DWORD PTR [esp+0x14],ebx
        push  0x2f
        jmp loc_0042DEDD
    loc_0042DE42:
        mov  BYTE PTR ds:0x491d6a,0x2
    loc_0042DE49:
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DE61
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DE61:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DE86
        jmp loc_0042DE70
        lea  ebx,[ebx+0x0]
    loc_0042DE70:
        mov  ecx,DWORD PTR [eax]
        cmp  WORD PTR [ecx+0x38a],di
        je loc_0042E007
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DE70
    loc_0042DE86:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042DE8A:
        push  0x2c
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  ecx,DWORD PTR [ebp+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DEAD
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DEAD:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DED7
        jmp loc_0042DEC0
        nop
        nop
    loc_0042DEC0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],0x20
        je loc_0042E014
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DEC0
    loc_0042DED7:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042DEDB:
        push  0x2d
    loc_0042DEDD:
        lea  eax,[esp+0x18]
        call FUN_00449670
        push  ebx
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_0042DEF6:
        mov  eax,0x80
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_0042E255
        mov  eax,DWORD PTR [ebp+0x24]
        sub  eax,ebx
        je loc_0042E044
        dec  eax
        je loc_0042E021
        dec  eax
        jne loc_0042E255
        mov  al,ds:0x491d69
        add  al,0x5
        cmp  al,0x64
        mov  ds:0x491d69,al
        jle loc_0042DF3E
        mov  BYTE PTR ds:0x491d69,0x64
    loc_0042DF3E:
        mov  edi,ebp
        call FUN_0042e5a0
        jmp loc_0042E255
    loc_0042DF4A:
        mov  edx,DWORD PTR [eax]
        mov  eax,DWORD PTR [edx]
        mov  DWORD PTR [esp+0x14],eax
        jmp loc_0042DDEA
    loc_0042DF57:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        push  0x2f
        jmp loc_0042DEDD
    loc_0042DF66:
        cmp  al,0x1
        jne loc_0042DE49
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DF86
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DF86:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DFA2
        nop
    loc_0042DF90:
        mov  ecx,DWORD PTR [eax]
        cmp  WORD PTR [ecx+0x38a],di
        je loc_0042DFEE
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DF90
    loc_0042DFA2:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042DFA6:
        push  0x30
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  ecx,DWORD PTR [ebp+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042DFC9
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042DFC9:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042DFE3
    loc_0042DFD0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],0x20
        je loc_0042DFF8
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042DFD0
    loc_0042DFE3:
        mov  DWORD PTR [esp+0x14],ebx
        push  0x31
        jmp loc_0042DEDD
    loc_0042DFEE:
        mov  edx,DWORD PTR [eax]
        mov  eax,DWORD PTR [edx]
        mov  DWORD PTR [esp+0x14],eax
        jmp loc_0042DFA6
    loc_0042DFF8:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        push  0x31
        jmp loc_0042DEDD
    loc_0042E007:
        mov  edx,DWORD PTR [eax]
        mov  eax,DWORD PTR [edx]
        mov  DWORD PTR [esp+0x14],eax
        jmp loc_0042DE8A
    loc_0042E014:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042DEDB
    loc_0042E021:
        mov  al,ds:0x491d68
        add  al,0x5
        cmp  al,0x64
        mov  ds:0x491d68,al
        jle loc_0042E038
        mov  BYTE PTR ds:0x491d68,0x64
    loc_0042E038:
        mov  edi,ebp
        call FUN_0042e5a0
        jmp loc_0042E255
    loc_0042E044:
        mov  al,ds:0x491d6a
        cmp  al,0x2
        jae loc_0042E056
        inc  al
        mov  ds:0x491d6a,al
        jmp loc_0042E05C
    loc_0042E056:
        mov  BYTE PTR ds:0x491d6a,bl
    loc_0042E05C:
        push  ebx
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  edx,DWORD PTR [ebp+0x2c8]
        mov  al,ds:0x491d6a
        cmp  al,bl
        push  edx
        mov  edx,esi
        jne loc_0042E11B
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E091
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E091:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E0B2
        mov  ecx,0x1f
        nop
    loc_0042E0A0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E102
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E0A0
    loc_0042E0B2:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042E0B6:
        push  0x2e
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E0D9
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E0D9:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E0F7
        mov  ecx,0x20
    loc_0042E0E5:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E10C
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E0E5
    loc_0042E0F7:
        mov  DWORD PTR [esp+0x14],ebx
        push  0x2f
        jmp loc_0042E24C
    loc_0042E102:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042E0B6
    loc_0042E10C:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        push  0x2f
        jmp loc_0042E24C
    loc_0042E11B:
        cmp  al,0x1
        jne loc_0042E1BB
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E132
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E132:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E152
        mov  ecx,0x1f
        mov  edi,edi
    loc_0042E140:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E1A2
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E140
    loc_0042E152:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042E156:
        push  0x30
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E179
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E179:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E197
        mov  ecx,0x20
    loc_0042E185:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E1AC
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E185
    loc_0042E197:
        mov  DWORD PTR [esp+0x14],ebx
        push  0x31
        jmp loc_0042E24C
    loc_0042E1A2:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042E156
    loc_0042E1AC:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        push  0x31
        jmp loc_0042E24C
    loc_0042E1BB:
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E1CA
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E1CA:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E1F6
        mov  ecx,0x1f
        jmp loc_0042E1E0
        nop
        nop
    loc_0042E1E0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E2B4
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E1E0
    loc_0042E1F6:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042E1FA:
        push  0x2c
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E21D
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E21D:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E246
        mov  ecx,0x20
        nop
    loc_0042E230:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E2C1
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E230
    loc_0042E246:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042E24A:
        push  0x2d
    loc_0042E24C:
        lea  eax,[esp+0x18]
        call FUN_00449670
    loc_0042E255:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_0042E574
        mov  eax,DWORD PTR [ebp+0x24]
        sub  eax,0x3
        je loc_0042E4F6
        dec  eax
        je loc_0042E2CE
        dec  eax
        jne loc_0042E574
    loc_0042E27B:
        mov  esi,0x6
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c770
        mov  edi,0xb
    loc_0042E291:
        push  ebx
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,0x4
        mov  eax,ebp
        call FUN_0042c620
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_0042E2B4:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042E1FA
    loc_0042E2C1:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042E24A
    loc_0042E2CE:
        mov  edi,ebp
        mov  BYTE PTR ds:0x491d68,0x64
        mov  BYTE PTR ds:0x491d69,0x50
        mov  BYTE PTR ds:0x491d6a,bl
        call FUN_0042e5a0
        mov  edx,DWORD PTR [ebp+0x2c8]
        mov  al,ds:0x491d6a
        cmp  al,bl
        push  edx
        mov  edx,esi
        jne loc_0042E39B
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E30E
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E30E:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E332
        mov  ecx,0x1f
        lea  ebx,[ebx+0x0]
    loc_0042E320:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E382
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E320
    loc_0042E332:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042E336:
        push  0x2e
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E359
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E359:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E377
        mov  ecx,0x20
    loc_0042E365:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E38C
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E365
    loc_0042E377:
        mov  DWORD PTR [esp+0x14],ebx
        push  0x2f
        jmp loc_0042E4BD
    loc_0042E382:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042E336
    loc_0042E38C:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        push  0x2f
        jmp loc_0042E4BD
    loc_0042E39B:
        cmp  al,0x1
        jne loc_0042E43B
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E3B2
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E3B2:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E3D2
        mov  ecx,0x1f
        mov  edi,edi
    loc_0042E3C0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E422
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E3C0
    loc_0042E3D2:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042E3D6:
        push  0x30
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E3F9
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E3F9:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E417
        mov  ecx,0x20
    loc_0042E405:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E42C
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E405
    loc_0042E417:
        mov  DWORD PTR [esp+0x14],ebx
        push  0x31
        jmp loc_0042E4BD
    loc_0042E422:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042E3D6
    loc_0042E42C:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        push  0x31
        jmp loc_0042E4BD
    loc_0042E43B:
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E44A
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E44A:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E472
        mov  ecx,0x1f
        jmp loc_0042E460
        nop
        nop
    loc_0042E460:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E4E2
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E460
    loc_0042E472:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042E476:
        push  0x2c
        lea  eax,[esp+0x18]
        call FUN_00449670
        mov  edx,DWORD PTR [ebp+0x2c8]
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E499
        mov  DWORD PTR [ebp+0x2c8],ebx
    loc_0042E499:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E4B7
        mov  ecx,0x20
    loc_0042E4A5:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042E4EC
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E4A5
    loc_0042E4B7:
        mov  DWORD PTR [esp+0x14],ebx
    loc_0042E4BB:
        push  0x2d
    loc_0042E4BD:
        lea  eax,[esp+0x18]
        call FUN_00449670
        push  ebx
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_0042E4E2:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042E476
    loc_0042E4EC:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x14],ecx
        jmp loc_0042E4BB
    loc_0042E4F6:
        mov  esi,0x6
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c770
        mov  edi,0xa
        jmp loc_0042E291
        cmp  DWORD PTR [ebp+0x2b4],0xa
        jl loc_0042E574
        mov  eax,DWORD PTR [ebp+0x24]
        sub  eax,0x3
        lea  esi,[ebp+0x24]
        je loc_0042E561
        sub  eax,0x2
        jne loc_0042E574
        mov  ecx,0x5a
        mov  eax,ebp
        call FUN_0042c730
        mov  ecx,0x5b
        mov  eax,ebp
        call FUN_0042c730
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c5c0
        mov  eax,esi
        call FUN_0044be70
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_0042E561:
        mov  ecx,0x5
        mov  eax,ebp
        call FUN_0042c5c0
        mov  eax,esi
        call FUN_0044be20
    loc_0042E574:
        pop  edi
        pop  esi
        pop  ebx
    loc_0042E577:
        mov  eax,0x1
        pop  ebp
        ret  0x4
        inc  edx
        fld  DWORD PTR [edx+0x0]
        jnp loc_0042E55F
        inc  edx
        add  ah,cl
        fild  DWORD PTR [edx+0x0]
        je loc_0042E573
        inc  edx
        add  BYTE PTR [ecx],dl
        in   eax,0x42
        add  ah,cl
    }
}

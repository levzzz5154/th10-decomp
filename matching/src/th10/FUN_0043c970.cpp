// 0043C970: FUN_0043c970
// Original size: 400 bytes, actual code: 120 instructions
extern "C" void FUN_0044a000(void);
extern "C" void FUN_0044a030(void);

extern "C" __declspec(naked) void FUN_0043c970(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        cmp  ebp,0x8
        ja loc_0043CA78
        push  edi
        jmp  DWORD PTR [ebp*4+0x43cad8]
        mov  eax,0x43bd40
    loc_0043C98B:
        push  esi
        mov  edi,0xe
        call FUN_0044a000
        mov  DWORD PTR [esi+0x8],eax
        mov  eax,0x43c1a0
        push  esi
        mov  edi,ebx
        call FUN_0044a030
        mov  DWORD PTR [esi+0xc],eax
        jmp loc_0043CA77
        mov  eax,0x43c550
        jmp loc_0043CA69
        mov  eax,0x43c230
    loc_0043C9BD:
        push  esi
        mov  edi,0xe
        call FUN_0044a000
        mov  DWORD PTR [esi+0x8],eax
        push  esi
        mov  eax,0x43c2c0
        mov  edi,ebx
        call FUN_0044a030
        mov  DWORD PTR [esi+0xc],eax
        jmp loc_0043CA77
        mov  DWORD PTR [esi+0x18],0xff
        mov  eax,0x43bd40
        jmp loc_0043C9BD
        mov  eax,0x43c230
        jmp loc_0043C98B
        push  esi
        mov  eax,0x43c460
        mov  edi,0xe
        call FUN_0044a000
        mov  DWORD PTR [esi+0x8],eax
        mov  eax,0x43c500
        push  esi
        mov  edi,ebx
        call FUN_0044a030
        mov  DWORD PTR [esi+0xc],eax
        jmp loc_0043CA77
        push  esi
        mov  eax,0x43c310
        mov  edi,0xe
        call FUN_0044a000
        mov  DWORD PTR [esi+0x8],eax
        mov  eax,0x43c3c0
        push  esi
        mov  edi,ebx
        call FUN_0044a030
        mov  DWORD PTR [esi+0xc],eax
        jmp loc_0043CA77
        push  esi
        mov  eax,0x43c310
        mov  edi,0xe
        call FUN_0044a000
        mov  DWORD PTR [esi+0x8],eax
        mov  eax,0x43c410
        push  esi
        mov  edi,ebx
        call FUN_0044a030
        mov  DWORD PTR [esi+0xc],eax
        jmp loc_0043CA77
        mov  eax,0x43c710
    loc_0043CA69:
        mov  edi,0xe
        push  esi
        call FUN_0044a000
        mov  DWORD PTR [esi+0x8],eax
    loc_0043CA77:
        pop  edi
    loc_0043CA78:
        mov  eax,DWORD PTR [esi+0x8]
        mov  DWORD PTR [eax+0x10],0x43c870
        mov  eax,DWORD PTR [esi+0x40]
        xor  ecx,ecx
        test  al,0x1
        jne loc_0043CAA5
        or   eax,0x1
        mov  DWORD PTR [esi+0x34],ecx
        mov  DWORD PTR [esi+0x30],0xfff0bdc1
        mov  DWORD PTR [esi+0x38],ecx
        mov  DWORD PTR [esi+0x3c],0x476f78
        mov  DWORD PTR [esi+0x40],eax
    loc_0043CAA5:
        mov  edx,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esi+0x34],ecx
        mov  DWORD PTR [esi+0x38],ecx
        mov  ecx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esi+0x30],0xffffffff
        mov  DWORD PTR [esi+0x1c],ecx
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],edx
        mov  DWORD PTR [esi+0x24],eax
        mov  DWORD PTR [esi+0x28],ecx
        pop  ebp
        ret  0x14
        nop
        xchg  cl,cl
        inc  ebx
        add  BYTE PTR [esi-0x47ffbc37],ch
        leave
        inc  ebx
        add  al,ah
        leave
        inc  ebx
        add  ch,dh
        leave
        inc  ebx
        add  dh,ch
        leave
        inc  ebx
        add  BYTE PTR [edx],bl
        retf  0x43
        aas
        retf  0x43
        fs retf 0x43
    }
}

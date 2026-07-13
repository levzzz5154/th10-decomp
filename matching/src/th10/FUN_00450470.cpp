// 00450470: FUN_00450470
// Original size: 320 bytes, actual code: 64 instructions

extern "C" __declspec(naked) void FUN_00450470(void) {
    __asm {
        push  ecx
        push  ebx
        mov  ebx,DWORD PTR [eax+0x8]
        push  ebp
        push  esi
        xor  ebp,ebp
        dec  ebx
        push  edi
        js loc_004504DB
        mov  eax,DWORD PTR [eax+0x8c]
        mov  DWORD PTR [esp+0x10],eax
    loc_00450487:
        mov  ecx,DWORD PTR [esp+0x10]
        mov  eax,ebx
        sub  eax,ebp
        cdq
        sub  eax,edx
        mov  edi,eax
        sar  edi,1
        add  edi,ebp
        mov  esi,DWORD PTR [ecx+edi*8]
        mov  ecx,DWORD PTR [esp+0x18]
        nop
    loc_004504A0:
        mov  dl,BYTE PTR [ecx]
        mov  al,dl
        cmp  dl,BYTE PTR [esi]
        jne loc_004504C4
        test  al,al
        je loc_004504C0
        mov  dl,BYTE PTR [ecx+0x1]
        mov  al,dl
        cmp  dl,BYTE PTR [esi+0x1]
        jne loc_004504C4
        add  ecx,0x2
        add  esi,0x2
        test  al,al
        jne loc_004504A0
    loc_004504C0:
        xor  eax,eax
        jmp loc_004504C9
    loc_004504C4:
        sbb  eax,eax
        sbb  eax,0xffffffff
    loc_004504C9:
        test  eax,eax
        je loc_004504E5
        jge loc_004504D4
        lea  ebx,[edi-0x1]
        jmp loc_004504D7
    loc_004504D4:
        lea  ebp,[edi+0x1]
    loc_004504D7:
        cmp  ebp,ebx
        jle loc_00450487
    loc_004504DB:
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        pop  ecx
        ret  0x4
    loc_004504E5:
        mov  eax,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [eax+edi*8+0x4]
        pop  edi
        pop  esi
        pop  ebp
        add  eax,0x10
        pop  ebx
        pop  ecx
        ret  0x4
    }
}

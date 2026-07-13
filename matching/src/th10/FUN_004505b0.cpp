// 004505B0: FUN_004505b0
// Original size: 224 bytes, actual code: 81 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_004505b0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x1000]
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        push  esi
        lea  esi,[ecx+ebp*1]
        cmp  esi,0x1000
        jl loc_004505CF
        pop  esi
        or   eax,0xffffffff
        pop  ebp
        ret  0x8
    loc_004505CF:
        test  dl,dl
        je loc_004505DD
        mov  BYTE PTR [ecx+eax*1],dl
        add  DWORD PTR [eax+0x1000],0x4
    loc_004505DD:
        mov  esi,DWORD PTR [esp+0x10]
        push  edi
        mov  edi,DWORD PTR [eax+0x1000]
        mov  ecx,ebp
        mov  edx,ecx
        shr  ecx,0x2
        add  edi,eax
        rep movsd
        mov  ecx,edx
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [eax+0x1000]
        pop  edi
        add  ecx,ebp
        pop  esi
        mov  DWORD PTR [eax+0x1000],ecx
        xor  eax,eax
        pop  ebp
        ret  0x8
        mov  edx,DWORD PTR [eax+0x1000]
        sub  edx,ecx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        jns loc_00450626
        or   eax,0xffffffff
        pop  ebp
        ret  0x4
    loc_00450626:
        push  esi
        push  edi
        mov  DWORD PTR [eax+0x1000],edx
        lea  esi,[edx+eax*1]
        mov  edx,ecx
        shr  ecx,0x2
        mov  edi,ebp
        rep movsd
        mov  ecx,edx
        and  ecx,0x3
        test  bl,bl
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        pop  edi
        pop  esi
        je loc_00450684
        mov  edx,DWORD PTR [eax+0x1000]
        add  edx,0xfffffffc
        mov  ecx,edx
        mov  DWORD PTR [eax+0x1000],edx
        mov  al,BYTE PTR [ecx+eax*1]
        cmp  al,0x66
        je loc_00450674
        cmp  al,0x69
        jne loc_00450684
        cmp  bl,0x66
        jne loc_00450684
        fild  DWORD PTR [ebp+0x0]
        xor  eax,eax
        fstp  DWORD PTR [ebp+0x0]
        pop  ebp
        ret  0x4
    loc_00450674:
        cmp  bl,0x69
        jne loc_00450684
        fld  DWORD PTR [ebp+0x0]
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x0],eax
    loc_00450684:
        xor  eax,eax
        pop  ebp
        ret  0x4
    }
}

// 0044BB20: FUN_0044bb20
// Original size: 112 bytes, actual code: 37 instructions

extern "C" __declspec(naked) void FUN_0044bb20(void) {
    __asm {
        push  ecx
        xor  eax,eax
        mov  ax,WORD PTR [ecx]
        xor  ax,0x9630
        xor  edx,edx
        push  esi
        xor  esi,esi
        sub  eax,0x6553
        mov  dx,ax
        shr  dx,0xe
        shl  eax,0x2
        add  edx,eax
        mov  eax,edx
        xor  eax,0x9630
        sub  eax,0x6553
        mov  si,ax
        shr  si,0xe
        shl  eax,0x2
        mov  WORD PTR [ecx],dx
        add  eax,esi
        mov  esi,DWORD PTR [ecx+0x4]
        add  esi,0x2
        mov  WORD PTR [ecx],ax
        mov  DWORD PTR [ecx+0x4],esi
        movzx ecx,dx
        movzx edx,ax
        shl  ecx,0x10
        or   ecx,edx
        test  ecx,ecx
        mov  DWORD PTR [esp+0x4],ecx
        fild  DWORD PTR [esp+0x4]
        jge loc_0044BB84
        fadd  DWORD PTR ds:0x470b98
    loc_0044BB84:
        fmul  DWORD PTR ds:0x470bf0
        pop  esi
        pop  ecx
        ret
    }
}

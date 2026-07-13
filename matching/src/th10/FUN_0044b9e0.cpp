// 0044B9E0: FUN_0044b9e0
// Original size: 160 bytes, actual code: 56 instructions

extern "C" __declspec(naked) void FUN_0044b9e0(void) {
    __asm {
        xor  eax,eax
        mov  ax,WORD PTR [ecx]
        xor  ax,0x9630
        xor  edx,edx
        push  esi
        xor  esi,esi
        sub  eax,0x6553
        mov  dx,ax
        shl  eax,0x2
        shr  dx,0xe
        add  edx,eax
        mov  eax,edx
        xor  eax,0x9630
        sub  eax,0x6553
        mov  si,ax
        shr  si,0xe
        shl  eax,0x2
        mov  WORD PTR [ecx],dx
        add  esi,eax
        add  DWORD PTR [ecx+0x4],0x2
        mov  WORD PTR [ecx],si
        movzx eax,dx
        movzx ecx,si
        shl  eax,0x10
        or   eax,ecx
        pop  esi
        ret
    }
}

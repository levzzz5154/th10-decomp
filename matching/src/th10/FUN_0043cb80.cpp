// 0043CB80: FUN_0043cb80
// Original size: 192 bytes, actual code: 32 instructions

extern "C" __declspec(naked) void FUN_0043cb80(void) {
    __asm {
        xor  eax,eax
        test  edi,edi
        je loc_0043CBD7
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
        movzx eax,dx
        mov  WORD PTR [ecx],si
        movzx ecx,si
        shl  eax,0x10
        or   eax,ecx
        xor  edx,edx
        div  edi
        pop  esi
        mov  eax,edx
    loc_0043CBD7:
        ret
    }
}

// 0042B9C0: FUN_0042b9c0
// Original size: 2464 bytes, actual code: 70 instructions

extern "C" __declspec(naked) void FUN_0042b9c0(void) {
    __asm {
        mov  ecx,DWORD PTR [esi+0x14]
        xor  edx,edx
        cmp  ecx,0x2d0
        jl loc_0042B9D0
        mov  DWORD PTR [esi+0x14],edx
    loc_0042B9D0:
        mov  ecx,DWORD PTR [esi+0x14]
        shl  ecx,0x6
        push  ebx
        lea  ecx,[ecx+esi*1+0x3c4]
        xor  ebx,ebx
        cmp  eax,edx
        mov  BYTE PTR [ecx+0x38],0x1
        jl loc_0042BA62
        je loc_0042BA08
        push  ebp
        jmp loc_0042B9F0
        nop
    loc_0042B9F0:
        cdq
        mov  ebp,0xa
        idiv  ebp
        inc  ebx
        test  eax,eax
        mov  BYTE PTR [ebx+ecx*1-0x1],dl
        jne loc_0042B9F0
        xor  edx,edx
        test  ebx,ebx
        pop  ebp
        jne loc_0042BA10
    loc_0042BA08:
        mov  BYTE PTR [ecx],0x0
    loc_0042BA0B:
        mov  ebx,0x1
    loc_0042BA10:
        mov  eax,DWORD PTR [esp+0x8]
        mov  BYTE PTR [ecx+0x39],bl
        mov  DWORD PTR [ecx+0x18],eax
        mov  eax,DWORD PTR [ecx+0x2c]
        test  al,0x1
        pop  ebx
        jne loc_0042BA3C
        or   eax,0x1
        mov  DWORD PTR [ecx+0x20],edx
        mov  DWORD PTR [ecx+0x1c],0xfff0bdc1
        mov  DWORD PTR [ecx+0x24],edx
        mov  DWORD PTR [ecx+0x28],0x476f78
        mov  DWORD PTR [ecx+0x2c],eax
    loc_0042BA3C:
        mov  DWORD PTR [ecx+0x20],edx
        mov  DWORD PTR [ecx+0x24],edx
        mov  DWORD PTR [ecx+0x1c],0xffffffff
        mov  edx,DWORD PTR [edi]
        add  ecx,0xc
        mov  DWORD PTR [ecx],edx
        mov  eax,DWORD PTR [edi+0x4]
        mov  DWORD PTR [ecx+0x4],eax
        mov  edx,DWORD PTR [edi+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        inc  DWORD PTR [esi+0x14]
        ret  0x4
    loc_0042BA62:
        mov  BYTE PTR [ecx],0xa
        jmp loc_0042BA0B
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [eax+0x4c],ecx
        or   DWORD PTR [eax+0x35c],0x8
        ret  0x4
    }
}

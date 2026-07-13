// 00427B50: FUN_00427b50
// Original size: 256 bytes, actual code: 61 instructions

extern "C" __declspec(naked) void FUN_00427b50(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        add  edx,0x350c
        xor  eax,eax
        nop
    loc_00427B60:
        test  BYTE PTR [edx+0x68],0x1
        je loc_00427B75
        inc  eax
        add  edx,0x6c
        cmp  eax,0x20
        jl loc_00427B60
        mov  eax,edx
        pop  ebp
        ret  0x14
    loc_00427B75:
        push  esi
        push  edi
        xor  eax,eax
        mov  ecx,0x1b
        mov  edi,edx
        rep stosd
        or   DWORD PTR [edx+0x68],0x3
        lea  esi,[edx+0x18]
        mov  edi,esi
        mov  ecx,0xb
        rep stosd
        mov  eax,DWORD PTR [ebp+0x0]
        mov  DWORD PTR [esi],eax
        mov  ecx,DWORD PTR [ebp+0x4]
        mov  DWORD PTR [esi+0x4],ecx
        mov  eax,DWORD PTR [ebp+0x8]
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esi+0x8],eax
        mov  eax,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edx],ecx
        mov  DWORD PTR [edx+0x4],eax
        mov  eax,DWORD PTR [edx+0x54]
        pop  edi
        xor  ecx,ecx
        test  al,0x1
        pop  esi
        jne loc_00427BD5
        or   eax,0x1
        mov  DWORD PTR [edx+0x48],ecx
        mov  DWORD PTR [edx+0x44],0xfff0bdc1
        mov  DWORD PTR [edx+0x4c],ecx
        mov  DWORD PTR [edx+0x50],0x476f78
        mov  DWORD PTR [edx+0x54],eax
    loc_00427BD5:
        mov  eax,DWORD PTR [esp+0x14]
        fild  DWORD PTR [esp+0x14]
        mov  DWORD PTR [edx+0x48],eax
        dec  eax
        mov  DWORD PTR [edx+0x44],eax
        fstp  DWORD PTR [edx+0x4c]
        mov  eax,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edx+0x58],eax
        mov  DWORD PTR [edx+0x5c],ecx
        mov  DWORD PTR [edx+0x60],0xf423f
        mov  DWORD PTR [edx+0x64],0x4
        mov  eax,edx
        pop  ebp
        ret  0x14
    }
}

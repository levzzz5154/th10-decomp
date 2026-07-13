// 0042ADD0: FUN_0042add0
// Original size: 144 bytes, actual code: 41 instructions

extern "C" __declspec(naked) void FUN_0042add0(void) {
    __asm {
        xor  eax,eax
        push  esi
        push  edi
        mov  edi,edx
        mov  ecx,0x112
        rep stosd
        mov  WORD PTR [edx+0x2],ax
        mov  WORD PTR [edx],0x5453
        mov  DWORD PTR [edx+0x8],0x448
        mov  ecx,DWORD PTR ds:0x46e354
        lea  eax,[edx+0xc]
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR ds:0x46e358
        mov  DWORD PTR [eax+0x4],ecx
        mov  cl,BYTE PTR ds:0x46e35c
        mov  BYTE PTR [eax+0x8],cl
        add  edx,0x46
        mov  esi,0x200
        jmp loc_0042AE20
        nop
        jmp loc_0042AE20
        nop
    loc_0042AE20:
        mov  eax,ds:0x4918b0
        mov  edi,DWORD PTR ds:0x4918b4
        xor  eax,0x9630
        sub  eax,0x6553
        xor  ecx,ecx
        mov  cx,ax
        shr  cx,0xe
        shl  eax,0x2
        add  edx,0x2
        add  ecx,eax
        inc  edi
        dec  esi
        mov  WORD PTR ds:0x4918b0,cx
        mov  DWORD PTR ds:0x4918b4,edi
        mov  WORD PTR [edx-0x2],cx
        jne loc_0042AE20
        pop  edi
        pop  esi
        ret
    }
}

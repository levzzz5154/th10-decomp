// 0041A0A0: FUN_0041a0a0
// Original size: 128 bytes, actual code: 52 instructions

extern "C" __declspec(naked) void FUN_0041a0a0(void) {
    __asm {
        push  esi
        push  edi
    loc_0041A0A2:
        mov  cl,BYTE PTR [eax]
        cmp  cl,0x20
        je loc_0041A0B8
        cmp  cl,0x9
        je loc_0041A0B8
        cmp  cl,0xa
        je loc_0041A0B8
        cmp  cl,0xd
        jne loc_0041A0D6
    loc_0041A0B8:
        mov  ecx,eax
        lea  esi,[ecx+0x1]
        nop
    loc_0041A0C0:
        mov  dl,BYTE PTR [ecx]
        inc  ecx
        test  dl,dl
        jne loc_0041A0C0
        sub  ecx,esi
        test  ecx,ecx
        jle loc_0041A0A2
        lea  esi,[eax+0x1]
        mov  edi,eax
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        jmp loc_0041A0A2
    loc_0041A0D6:
        mov  ecx,eax
        lea  esi,[ecx+0x1]
        jmp loc_0041A0E0
        nop
    loc_0041A0E0:
        mov  dl,BYTE PTR [ecx]
        inc  ecx
        test  dl,dl
        jne loc_0041A0E0
        sub  ecx,esi
        lea  edx,[ecx-0x1]
        test  edx,edx
        pop  edi
        pop  esi
        jl loc_0041A111
    loc_0041A0F2:
        mov  cl,BYTE PTR [edx+eax*1]
        cmp  cl,0x20
        je loc_0041A109
        cmp  cl,0x9
        je loc_0041A109
        cmp  cl,0xa
        je loc_0041A109
        cmp  cl,0xd
        jne loc_0041A111
    loc_0041A109:
        dec  edx
        mov  BYTE PTR [edx+eax*1+0x1],0x0
        jns loc_0041A0F2
    loc_0041A111:
        ret
    }
}

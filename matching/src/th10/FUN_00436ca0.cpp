// 00436CA0: FUN_00436ca0
// Original size: 256 bytes, actual code: 26 instructions

extern "C" __declspec(naked) void FUN_00436ca0(void) {
    __asm {
        mov  eax,ecx
        shr  eax,0x14
        mov  edx,ecx
        and  eax,0xf
        shr  edx,0xc
        shl  eax,0x4
        and  edx,0xf
        or   eax,edx
        mov  edx,DWORD PTR [esi+0x120]
        shr  ecx,0x4
        and  ecx,0xf
        shl  eax,0x4
        push  edi
        mov  edi,DWORD PTR [esi+0x10c]
        or   eax,ecx
        xor  ecx,ecx
        test  edi,edi
        jle loc_00436CE6
    loc_00436CD3:
        mov  WORD PTR [edx],ax
        mov  edi,DWORD PTR [esi+0x10c]
        add  ecx,0x2
        add  edx,0x2
        cmp  ecx,edi
        jl loc_00436CD3
    loc_00436CE6:
        pop  edi
        ret
    }
}

// 00442FE0: FUN_00442fe0
// Original size: 160 bytes, actual code: 47 instructions

extern "C" __declspec(naked) void FUN_00442fe0(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  edi,DWORD PTR [eax+0x72dacc]
        mov  esi,edx
        lea  ebx,[edx+0x1c]
        mov  ecx,0x7
        rep movsd
        mov  edi,DWORD PTR [eax+0x72dacc]
        add  edi,0x1c
        mov  esi,ebx
        lea  ebp,[edx+0x38]
        mov  ecx,0x7
        rep movsd
        mov  edi,DWORD PTR [eax+0x72dacc]
        add  edi,0x38
        mov  esi,ebp
        mov  ecx,0x7
        rep movsd
        mov  edi,DWORD PTR [eax+0x72dacc]
        add  edi,0x54
        mov  esi,ebx
        mov  ecx,0x7
        rep movsd
        mov  edi,DWORD PTR [eax+0x72dacc]
        add  edi,0x70
        mov  esi,ebp
        mov  ecx,0x7
        rep movsd
        mov  edi,DWORD PTR [eax+0x72dacc]
        lea  esi,[edx+0x54]
        add  edi,0x8c
        mov  ecx,0x7
        rep movsd
        mov  edx,DWORD PTR [eax+0x72dacc]
        mov  ecx,DWORD PTR [eax+0x3adac8]
        pop  edi
        add  edx,0xa8
        pop  esi
        inc  ecx
        pop  ebp
        mov  DWORD PTR [eax+0x72dacc],edx
        mov  DWORD PTR [eax+0x3adac8],ecx
        xor  eax,eax
        pop  ebx
        ret
    }
}

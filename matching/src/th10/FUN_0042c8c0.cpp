// 0042C8C0: FUN_0042c8c0
// Original size: 96 bytes, actual code: 27 instructions

extern "C" __declspec(naked) void FUN_0042c8c0(void) {
    __asm {
        mov  ecx,0x1010101
        mov  DWORD PTR [eax+0x1d882],ecx
        mov  DWORD PTR [eax+0x1d886],ecx
        push  esi
        mov  DWORD PTR [eax+0x1d88a],ecx
        push  edi
        mov  DWORD PTR [eax+0x1d88e],ecx
        lea  esi,[eax+0x4e9]
        mov  edi,0x6
        lea  ebx,[ebx+0x0]
    loc_0042C8F0:
        mov  eax,esi
        mov  edx,0x4
        jmp loc_0042C900
        nop
    loc_0042C900:
        mov  ecx,0x6
    loc_0042C905:
        mov  BYTE PTR [eax],0x1
        add  eax,0x8
        dec  ecx
        jne loc_0042C905
        dec  edx
        jne loc_0042C900
        add  esi,0x437c
        dec  edi
        jne loc_0042C8F0
        pop  edi
        pop  esi
        ret
    }
}

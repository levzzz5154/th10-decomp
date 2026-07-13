// 0042C6D0: FUN_0042c6d0
// Original size: 96 bytes, actual code: 25 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_0042c6d0(void) {
    __asm {
        mov  eax,DWORD PTR [edi+esi*4+0x2c4]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        xor  ecx,ecx
        cmp  eax,ecx
        je loc_0042C71B
        push  ebx
        cmp  DWORD PTR [eax+0x18],ecx
        mov  edx,0x1
        mov  WORD PTR [eax+0x304],dx
        jne loc_0042C712
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,ecx
        je loc_0042C712
    loc_0042C702:
        mov  ebx,DWORD PTR [eax]
        mov  WORD PTR [ebx+0x304],dx
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ecx
        jne loc_0042C702
    loc_0042C712:
        mov  DWORD PTR [edi+esi*4+0x2c4],ecx
        pop  ebx
        ret
    loc_0042C71B:
        mov  DWORD PTR [edi+esi*4+0x2c4],ecx
        ret
    }
}

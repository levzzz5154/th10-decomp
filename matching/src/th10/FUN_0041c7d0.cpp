// 0041C7D0: FUN_0041c7d0
// Original size: 48 bytes, actual code: 19 instructions

extern "C" __declspec(naked) void FUN_0041c7d0(void) {
    __asm {
        mov  eax,DWORD PTR [eax+0x18]
        test  eax,eax
        je loc_0041C7F9
        push  ebx
        mov  edx,0x1
        nop
    loc_0041C7E0:
        cmp  DWORD PTR [eax+0xc],edx
        mov  ecx,DWORD PTR [eax+0x8]
        je loc_0041C7F2
        mov  bl,BYTE PTR [eax+0x50]
        test  bl,bl
        jne loc_0041C7F2
        mov  BYTE PTR [eax+0x50],dl
    loc_0041C7F2:
        test  ecx,ecx
        mov  eax,ecx
        jne loc_0041C7E0
        pop  ebx
    loc_0041C7F9:
        xor  eax,eax
        ret
    }
}

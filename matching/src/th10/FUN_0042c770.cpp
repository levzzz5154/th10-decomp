// 0042C770: FUN_0042c770
// Original size: 224 bytes, actual code: 20 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_0042c770(void) {
    __asm {
        mov  eax,DWORD PTR [eax+ecx*4+0x2c4]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_0042C7B0
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        mov  WORD PTR [eax+0x304],si
        jne loc_0042C7B0
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0042C7B0
        nop
    loc_0042C7A0:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],si
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0042C7A0
    loc_0042C7B0:
        ret
    }
}

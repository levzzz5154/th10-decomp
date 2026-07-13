// 0040C4D0: FUN_0040c4d0
// Original size: 112 bytes, actual code: 21 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_0040c4d0(void) {
    __asm {
        mov  eax,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_0040C510
        mov  edx,DWORD PTR [eax+0x18]
        test  edx,edx
        mov  ecx,0x3
        mov  WORD PTR [eax+0x304],cx
        jne loc_0040C510
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0040C510
        nop
    loc_0040C500:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040C500
    loc_0040C510:
        ret
    }
}

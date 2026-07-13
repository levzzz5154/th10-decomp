// 0040C480: FUN_0040c480
// Original size: 80 bytes, actual code: 21 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_0040c480(void) {
    __asm {
        mov  eax,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_0040C4C0
        mov  edx,DWORD PTR [eax+0x18]
        test  edx,edx
        mov  ecx,0x2
        mov  WORD PTR [eax+0x304],cx
        jne loc_0040C4C0
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0040C4C0
        nop
    loc_0040C4B0:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040C4B0
    loc_0040C4C0:
        ret
    }
}

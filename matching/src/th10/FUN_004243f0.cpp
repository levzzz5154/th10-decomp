// 004243F0: FUN_004243f0
// Original size: 144 bytes, actual code: 21 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_004243f0(void) {
    __asm {
        mov  eax,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_00424430
        mov  edx,DWORD PTR [eax+0x18]
        test  edx,edx
        mov  ecx,0x6
        mov  WORD PTR [eax+0x304],cx
        jne loc_00424430
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00424430
        nop
    loc_00424420:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00424420
    loc_00424430:
        ret
    }
}

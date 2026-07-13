// 00409E50: FUN_00409e50
// Original size: 320 bytes, actual code: 21 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00409e50(void) {
    __asm {
        mov  eax,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_00409E90
        mov  edx,DWORD PTR [eax+0x18]
        test  edx,edx
        mov  ecx,0x1
        mov  WORD PTR [eax+0x304],cx
        jne loc_00409E90
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_00409E90
        nop
    loc_00409E80:
        mov  edx,DWORD PTR [eax]
        mov  WORD PTR [edx+0x304],cx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00409E80
    loc_00409E90:
        ret
    }
}

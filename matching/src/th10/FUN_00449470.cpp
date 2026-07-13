// 00449470: FUN_00449470
// Original size: 288 bytes, actual code: 21 instructions
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_00449470(void) {
    __asm {
        mov  eax,DWORD PTR [eax]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        je loc_004494B0
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        mov  WORD PTR [eax+0x304],si
        jne loc_004494B0
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_004494B0
        jmp loc_004494A0
        nop
    loc_004494A0:
        mov  ecx,DWORD PTR [eax]
        mov  WORD PTR [ecx+0x304],si
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004494A0
    loc_004494B0:
        ret
    }
}

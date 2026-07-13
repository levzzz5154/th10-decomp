// 00444580: FUN_00444580
// Original size: 64 bytes, actual code: 12 instructions
extern "C" void FUN_00442670(void);
extern "C" void FUN_00444240(void);

extern "C" __declspec(naked) void FUN_00444580(void) {
    __asm {
        push  edi
        mov  eax,esi
        call FUN_00444240
        push  0x0
        mov  eax,esi
        mov  ecx,edi
        call FUN_00442670
        mov  DWORD PTR ds:0x497920,0x3f800000
        mov  DWORD PTR ds:0x497904,0x3f800000
        mov  DWORD PTR ds:0x4978e8,0x3f800000
        mov  DWORD PTR ds:0x4978cc,0x3f800000
        ret
    }
}

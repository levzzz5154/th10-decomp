// 00449A90: FUN_00449a90
// Original size: 16 bytes, actual code: 5 instructions

extern "C" __declspec(naked) void FUN_00449a90(void) {
    __asm {
        xor  ecx,ecx
        mov  DWORD PTR [eax+0x8],ecx
        mov  DWORD PTR [eax+0xc],ecx
        mov  DWORD PTR [eax+0x10],ecx
        ret
    }
}

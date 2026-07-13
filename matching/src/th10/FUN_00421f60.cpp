// 00421F60: FUN_00421f60
// Original size: 64 bytes, actual code: 7 instructions

extern "C" __declspec(naked) void FUN_00421f60(void) {
    __asm {
        mov  ecx,DWORD PTR ds:0x474c44
        mov  DWORD PTR [eax+0x9e78],ecx
        mov  eax,ecx
        cmp  DWORD PTR ds:0x474c40,eax
        jge loc_00421F7B
        mov  ds:0x474c40,eax
    loc_00421F7B:
        ret
    }
}

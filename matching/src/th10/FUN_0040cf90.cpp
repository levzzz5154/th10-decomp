// 0040CF90: FUN_0040cf90
// Original size: 32 bytes, actual code: 10 instructions

extern "C" __declspec(naked) void FUN_0040cf90(void) {
    __asm {
        mov  eax,DWORD PTR [eax+0x18]
        test  eax,eax
        je loc_0040CFA3
    loc_0040CF97:
        cmp  DWORD PTR [eax+0x54],ecx
        je loc_0040CFA5
        mov  eax,DWORD PTR [eax+0x8]
        test  eax,eax
        jne loc_0040CF97
    loc_0040CFA3:
        xor  eax,eax
    loc_0040CFA5:
        ret
    }
}

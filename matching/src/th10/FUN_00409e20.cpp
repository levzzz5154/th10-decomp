// 00409E20: FUN_00409e20
// Original size: 48 bytes, actual code: 11 instructions

extern "C" __declspec(naked) void FUN_00409e20(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x8]
        test  ecx,ecx
        mov  edx,0x2
        je loc_00409E2F
        or   DWORD PTR [ecx+0x4],edx
    loc_00409E2F:
        mov  ecx,DWORD PTR [eax+0xc]
        test  ecx,ecx
        je loc_00409E3B
        mov  eax,ecx
        or   DWORD PTR [eax+0x4],edx
    loc_00409E3B:
        ret
    }
}

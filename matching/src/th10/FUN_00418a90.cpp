// 00418A90: FUN_00418a90
// Original size: 240 bytes, actual code: 7 instructions

extern "C" __declspec(naked) void FUN_00418a90(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x50]
        inc  ecx
        cmp  ecx,0xa
        mov  DWORD PTR [eax+0x50],ecx
        jl loc_00418AA3
        mov  DWORD PTR [eax+0x50],0x9
    loc_00418AA3:
        ret
    }
}

// 0040AC90: FUN_0040ac90
// Original size: 80 bytes, actual code: 8 instructions

extern "C" __declspec(naked) void FUN_0040ac90(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x3cc]
        test  ch,0x10
        jne loc_0040ACA8
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [eax+0x390],ecx
        ret  0x4
    loc_0040ACA8:
        mov  DWORD PTR [eax+0x390],0x2
        ret  0x4
    }
}

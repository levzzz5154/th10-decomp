// 00412ED0: FUN_00412ed0
// Original size: 288 bytes, actual code: 7 instructions

extern "C" __declspec(naked) void FUN_00412ed0(void) {
    __asm {
        cmp  DWORD PTR [eax+0x44],ecx
        mov  DWORD PTR [eax+0x44],ecx
        je loc_00412EDF
        mov  DWORD PTR [eax+0x4c],0x0
    loc_00412EDF:
        ret
        mov  eax,DWORD PTR [eax+0x58]
        ret
    }
}

// 00438590: FUN_00438590
// Original size: 288 bytes, actual code: 96 instructions
extern "C" void FUN_004386b0(void);
extern "C" void _free(void);
extern "C" void FUN_004624e5(void);

extern "C" __declspec(naked) void FUN_00438590(void) {
    __asm {
        cmp  DWORD PTR [ecx+0x18],0x10
        mov  eax,DWORD PTR [esp+0x4]
        mov  DWORD PTR [ecx+0x14],eax
        jb loc_004385A7
        mov  ecx,DWORD PTR [ecx+0x4]
        mov  BYTE PTR [ecx+eax*1],0x0
        ret  0x4
    loc_004385A7:
        mov  BYTE PTR [ecx+eax*1+0x4],0x0
        ret  0x4
    }
}

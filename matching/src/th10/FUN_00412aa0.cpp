// 00412AA0: FUN_00412aa0
// Original size: 32 bytes, actual code: 7 instructions
extern "C" void FUN_0044ff80(void);

extern "C" __declspec(naked) void FUN_00412aa0(void) {
    __asm {
        mov  ecx,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [eax+0x14d8]
        mov  eax,DWORD PTR [eax+0x4]
        push  ecx
        mov  ecx,DWORD PTR [esp+0x8]
        call FUN_0044ff80
        ret  0x8
    }
}

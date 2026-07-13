// 00413170: FUN_00413170
// Original size: 144 bytes, actual code: 6 instructions
extern "C" void FUN_0044bc70(void);

extern "C" __declspec(naked) void FUN_00413170(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x8]
        push  eax
        call FUN_0044bc70
        mov  ecx,DWORD PTR [esp+0x4]
        fstp  DWORD PTR [ecx+0x1c]
        ret  0x8
    }
}

// 0044D710: FUN_0044d710
// Original size: 32 bytes, actual code: 11 instructions
extern "C" void FUN_0044d730(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0044d710(void) {
    __asm {
        push  esi
        mov  esi,ecx
        call FUN_0044d730
        test  BYTE PTR [esp+0x8],0x1
        je loc_0044D728
        push  esi
        call _free
        add  esp,0x4
    loc_0044D728:
        mov  eax,esi
        pop  esi
        ret  0x4
    }
}

// 0044CF00: FUN_0044cf00
// Original size: 32 bytes, actual code: 11 instructions
extern "C" void FUN_0044d080(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0044cf00(void) {
    __asm {
        push  esi
        mov  esi,ecx
        call FUN_0044d080
        test  BYTE PTR [esp+0x8],0x1
        je loc_0044CF18
        push  esi
        call _free
        add  esp,0x4
    loc_0044CF18:
        mov  eax,esi
        pop  esi
        ret  0x4
    }
}

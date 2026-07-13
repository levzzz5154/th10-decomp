// 00435320: FUN_00435320
// Original size: 32 bytes, actual code: 11 instructions
extern "C" void FUN_00435340(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00435320(void) {
    __asm {
        push  esi
        mov  esi,ecx
        call FUN_00435340
        test  BYTE PTR [esp+0x8],0x1
        je loc_00435338
        push  esi
        call _free
        add  esp,0x4
    loc_00435338:
        mov  eax,esi
        pop  esi
        ret  0x4
    }
}

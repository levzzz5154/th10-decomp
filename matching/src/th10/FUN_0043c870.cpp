// 0043C870: FUN_0043c870
// Original size: 64 bytes, actual code: 12 instructions
extern "C" void FUN_0043cb00(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0043c870(void) {
    __asm {
        push  esi
        mov  esi,ecx
        test  esi,esi
        je loc_0043C886
        push  esi
        call FUN_0043cb00
        push  esi
        call _free
        add  esp,0x4
    loc_0043C886:
        xor  eax,eax
        pop  esi
        ret
    }
}

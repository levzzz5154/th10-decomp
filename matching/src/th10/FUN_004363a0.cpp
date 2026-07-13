// 004363A0: FUN_004363a0
// Original size: 32 bytes, actual code: 11 instructions
extern "C" void FUN_004363c0(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_004363a0(void) {
    __asm {
        push  esi
        mov  esi,ecx
        call FUN_004363c0
        test  BYTE PTR [esp+0x8],0x1
        je loc_004363B8
        push  esi
        call _free
        add  esp,0x4
    loc_004363B8:
        mov  eax,esi
        pop  esi
        ret  0x4
    }
}

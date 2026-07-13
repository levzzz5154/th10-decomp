// 0040CC50: FUN_0040cc50
// Original size: 32 bytes, actual code: 12 instructions
extern "C" void FUN_0040dae0(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040cc50(void) {
    __asm {
        push  esi
        mov  esi,ecx
        push  esi
        call FUN_0040dae0
        test  BYTE PTR [esp+0x8],0x1
        je loc_0040CC69
        push  esi
        call _free
        add  esp,0x4
    loc_0040CC69:
        mov  eax,esi
        pop  esi
        ret  0x4
    }
}

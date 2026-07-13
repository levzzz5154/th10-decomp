// 00427C50: FUN_00427c50
// Original size: 32 bytes, actual code: 6 instructions
extern "C" void FUN_00452ff0(void);

extern "C" __declspec(naked) void FUN_00427c50(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        sub  esp,0x8
        fstp  QWORD PTR [esp]
        call FUN_00452ff0
        add  esp,0x8
        ret  0x4
    }
}

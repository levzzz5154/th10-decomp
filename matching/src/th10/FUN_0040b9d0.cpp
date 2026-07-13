// 0040B9D0: FUN_0040b9d0
// Original size: 32 bytes, actual code: 8 instructions
extern "C" void FUN_0040b7b0(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040b9d0(void) {
    __asm {
        test  esi,esi
        je loc_0040B9E1
        push  esi
        call FUN_0040b7b0
        push  esi
        call _free
        pop  ecx
    loc_0040B9E1:
        ret
    }
}

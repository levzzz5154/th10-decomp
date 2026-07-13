// 00418150: FUN_00418150
// Original size: 64 bytes, actual code: 8 instructions
extern "C" void FUN_00417c80(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00418150(void) {
    __asm {
        test  esi,esi
        je loc_00418161
        push  esi
        call FUN_00417c80
        push  esi
        call _free
        pop  ecx
    loc_00418161:
        ret
    }
}

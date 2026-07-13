// 0042CDB0: FUN_0042cdb0
// Original size: 64 bytes, actual code: 8 instructions
extern "C" void FUN_0042cb60(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0042cdb0(void) {
    __asm {
        test  esi,esi
        je loc_0042CDC1
        push  esi
        call FUN_0042cb60
        push  esi
        call _free
        pop  ecx
    loc_0042CDC1:
        ret
    }
}

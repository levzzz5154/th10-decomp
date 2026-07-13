// 004297B0: FUN_004297b0
// Original size: 32 bytes, actual code: 8 instructions
extern "C" void FUN_004294a0(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_004297b0(void) {
    __asm {
        test  esi,esi
        je loc_004297C1
        push  esi
        call FUN_004294a0
        push  esi
        call _free
        pop  ecx
    loc_004297C1:
        ret
    }
}

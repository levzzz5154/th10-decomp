// 0x0045370E..0x0045371A: store the argument in the per-thread data block at
// +0x14.

extern "C" void* __cdecl asm_getptd_00456357(void);

extern "C" void __cdecl unassigned_0045370e(int value) {
    *(int*)((char*)asm_getptd_00456357() + 0x14) = value;
}

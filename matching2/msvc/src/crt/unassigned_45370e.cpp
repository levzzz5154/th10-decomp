// 0x0045370E..0x0045371A: store the argument in the per-thread data block at
// +0x14.

extern "C" void* __cdecl crt_getptd(void);

extern "C" void __cdecl unassigned6(int value) {
    *(int*)((char*)crt_getptd() + 0x14) = value;
}

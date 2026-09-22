extern "C" unsigned int data_00499304;
extern "C" unsigned int data_00499300;

// 0x00458C25..0x00458C38: Set the masked CRT flag when enabled.
extern "C" void __cdecl asm_unassigned_00458c25(unsigned int enabled) {
    data_00499300 = enabled ? data_00499304 : 0;
}

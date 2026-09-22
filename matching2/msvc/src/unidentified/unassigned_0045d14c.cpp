extern "C" unsigned int data_00497f98;
extern "C" unsigned int data_004980a4;

// 0x0045D14C..0x0045D15B: Return the active CRT flag mask.
extern "C" unsigned int __cdecl asm_unassigned_0045d14c() {
    return data_00497f98 ? data_004980a4 : 0;
}

extern "C" unsigned int data_00499344;
extern "C" unsigned int data_00499330;
extern "C" int __cdecl asm_sbh_heap_init_00453c52(unsigned int size);

extern "C" int __cdecl asm_unassigned_00454863(unsigned int size) {
    if (data_00499344 == 3) {
        if (size <= 0x3F8) {
            data_00499330 = size;
            return 1;
        }
        return 0;
    }
    if (data_00499344 == 1 && size > 0 && size <= 0x3F8 && asm_sbh_heap_init_00453c52(size)) {
        data_00499330 = size;
        data_00499344 = 3;
        return 1;
    }
    return 0;
}

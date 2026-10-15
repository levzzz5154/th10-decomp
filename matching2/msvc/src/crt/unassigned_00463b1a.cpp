extern "C" void* (__stdcall *data_004661d4)(void*);
extern "C" int (__stdcall *data_004661d8)(const void*, unsigned int);
extern "C" int (__stdcall *data_00466184)(const void*);

extern "C" void* __stdcall asm_unassigned_00463b1a(void* filter) {
    return data_004661d4(filter);
}
extern "C" int __stdcall asm_unassigned_00463b20(const void* pointer, unsigned int size) {
    return data_004661d8(pointer, size);
}
extern "C" int __stdcall asm_unassigned_00463b26(const void* pointer) {
    return data_00466184(pointer);
}

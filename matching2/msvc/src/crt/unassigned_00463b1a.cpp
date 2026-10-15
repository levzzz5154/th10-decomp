extern "C" void* (__stdcall *imp_SetUnhandledExceptionFilter)(void*);
extern "C" int (__stdcall *imp_IsBadReadPtr)(const void*, unsigned int);
extern "C" int (__stdcall *imp_IsBadCodePtr)(const void*);

extern "C" void* __stdcall asm_unassigned_00463b1a(void* filter) {
    return imp_SetUnhandledExceptionFilter(filter);
}
extern "C" int __stdcall asm_unassigned_00463b20(const void* pointer, unsigned int size) {
    return imp_IsBadReadPtr(pointer, size);
}
extern "C" int __stdcall asm_unassigned_00463b26(const void* pointer) {
    return imp_IsBadCodePtr(pointer);
}

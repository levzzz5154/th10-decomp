extern "C" int (__cdecl *data_00477360)(unsigned int);

extern "C" int __cdecl asm_callnewh_00455737(unsigned int size) {
    int (__cdecl *handler)(unsigned int) = data_00477360;
    if (handler && handler(size)) return 1;
    return 0;
}

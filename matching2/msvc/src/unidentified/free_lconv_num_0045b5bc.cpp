extern "C" void** data_00473ad4;
extern "C" void* data_00473aa4;
extern "C" void* data_00473aa8;
extern "C" void* data_00473aac;
extern "C" void __cdecl asm_free_00452422(void*);

extern "C" void __cdecl asm_free_lconv_num_0045b5bc(void** values) {
    if (values) {
        void* value = values[0];
        if (value != data_00473ad4[0] && value != data_00473aa4) asm_free_00452422(value);
        value = values[1];
        if (value != data_00473ad4[1] && value != data_00473aa8) asm_free_00452422(value);
        value = values[2];
        if (value != data_00473ad4[2] && value != data_00473aac) asm_free_00452422(value);
    }
}

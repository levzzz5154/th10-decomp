extern "C" void** g_crt_lconv_ptrs;
extern "C" void* g_crt_lconv_num_a;
extern "C" void* g_crt_lconv_num_b;
extern "C" void* g_crt_lconv_num_c;
extern "C" void __cdecl asm_free_00452422(void*);

extern "C" void __cdecl asm_free_lconv_num_0045b5bc(void** values) {
    if (values) {
        void* value = values[0];
        if (value != g_crt_lconv_ptrs[0] && value != g_crt_lconv_num_a) asm_free_00452422(value);
        value = values[1];
        if (value != g_crt_lconv_ptrs[1] && value != g_crt_lconv_num_b) asm_free_00452422(value);
        value = values[2];
        if (value != g_crt_lconv_ptrs[2] && value != g_crt_lconv_num_c) asm_free_00452422(value);
    }
}

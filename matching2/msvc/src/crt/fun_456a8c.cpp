extern "C" unsigned int g_crt_decimal_ptr_a;
extern "C" unsigned int g_crt_decimal_ptr_b;
extern "C" unsigned int g_crt_decimal_ptr_c;
extern "C" unsigned int g_crt_decimal_ptr_d;
extern "C" unsigned int g_crt_decimal_ptr_e;
extern "C" unsigned int g_crt_decimal_ptr_f;

// 0x00456A8C..0x00456AC3: Install the CRT floating-point conversion hooks.
extern "C" void __cdecl asm_FUN_00456a8c_00456a8c() {
    g_crt_decimal_ptr_a = 0x0045df97;
    g_crt_decimal_ptr_b = 0x0045dc17;
    g_crt_decimal_ptr_c = 0x0045dc7c;
    g_crt_decimal_ptr_d = 0x0045dbdb;
    g_crt_decimal_ptr_e = 0x0045dc62;
    g_crt_decimal_ptr_f = 0x0045df97;
}

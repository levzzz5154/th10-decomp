extern "C" unsigned int g_crt_thread_id;

// 0x00456AC4..0x00456AD3: Replace a global value and return its old value.
extern "C" unsigned int __cdecl asm_FUN_00456ac4_00456ac4(unsigned int value) {
    unsigned int previous = g_crt_thread_id;
    g_crt_thread_id = value;
    return previous;
}

extern "C" unsigned int crt_libcmt_secfail_user_handler;

// 0x0045F3A4..0x0045F3B3: Replace a global value and return its old value.
extern "C" unsigned int __cdecl crt_helper_45f3a4(unsigned int value) {
    unsigned int previous = crt_libcmt_secfail_user_handler;
    crt_libcmt_secfail_user_handler = value;
    return previous;
}

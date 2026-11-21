extern "C" unsigned int crt_libcmt_secfail_user_handler;

// 0x0045F3C0..0x0045F3CF: Replace a global value and return its old value.
extern "C" unsigned int __cdecl crt_helper_45f3c0(unsigned int value) {
    unsigned int previous = crt_libcmt_secfail_user_handler;
    crt_libcmt_secfail_user_handler = value;
    return previous;
}

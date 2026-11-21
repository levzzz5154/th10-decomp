extern "C" int __cdecl crt_security_error_handler(int mode, int flags);

extern "C" int __cdecl crt_unassigned_45f3b4() {
    return crt_security_error_handler(1, 0);
}

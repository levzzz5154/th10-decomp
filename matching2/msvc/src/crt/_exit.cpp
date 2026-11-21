extern "C" void __cdecl crt_doexit(int code, int quick, int return_to_caller);

extern "C" void __cdecl crt_exit_4576fd(int code) {
    crt_doexit(code, 1, 0);
}

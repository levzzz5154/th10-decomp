extern "C" void __cdecl crt_doexit(int code, int quick, int return_to_caller);

extern "C" void __cdecl crt_cexit() {
    crt_doexit(0, 0, 1);
}
